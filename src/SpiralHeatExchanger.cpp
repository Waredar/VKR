#include "SpiralHeatExchanger.h"
#include <math.h>

using namespace std;

SpiralHeatExchanger::SpiralHeatExchanger()
{

};

SpiralHeatExchanger::SpiralHeatExchanger(const Fluid& hot, const Fluid& cold, const Wall& wallProperties, const Geometry& geom)
    : hotFluid(hot), coldFluid(cold), wallProperties(wallProperties), geo(geom)
{

};

CalculationResult SpiralHeatExchanger::calculate()
{
    CalculationResult result;

    string err = validateInputs();
    if (!err.empty()) {
        result.error_message = err;
        return result;
    }

    result.Q_required = hotFluid.G * hotFluid.cp * std::abs(hotFluid.t_in - hotFluid.t_out);
    result.LMTD_required = calculateLMTD(hotFluid.t_in, hotFluid.t_out, coldFluid.t_in, coldFluid.t_out);

    double f_hot = hotFluid.G / (hotFluid.rho * hotFluid.max_velocity);
    double f_cold = coldFluid.G / (coldFluid.rho * coldFluid.max_velocity);

    double be_hot = f_hot / geo.width_hot;
    double be_cold = f_cold / geo.width_cold;

    double be_min = std::max(be_hot, be_cold);

    auto it = std::find_if(standard_width.begin(), standard_width.end(),
        [&](double h) {
            if (h < be_min) return false;
            if (!geo.auto_width) {
                if (h < geo.width_min || h > geo.width_max) return false;
            }
            return true;
        });

    if (it == standard_width.end()) {
        if (geo.auto_width) {
            result.error_message = "Требуемая ширина канала превышает максимальный стандартный размер";
        }
        else {
            int be_min_mm = static_cast<int>(round(be_min * 1000));
            result.error_message = "В заданном диапазоне ширины нет подходящего стандартного значения"
                " (минимально необходимая: "
                + std::to_string(be_min_mm) + " мм)";
        }
        return result;
    }
    double be = *it;

    double d_eq_cold = 2.0 * geo.width_cold * be / (geo.width_cold + be);
    double d_eq_hot = 2.0 * geo.width_hot * be / (geo.width_hot + be);

    result.velocity_cold = coldFluid.G / (coldFluid.rho * geo.width_cold * be);
    result.Re_cold = result.velocity_cold * d_eq_cold * coldFluid.rho / coldFluid.viscosity;

    result.velocity_hot = hotFluid.G / (hotFluid.rho * geo.width_hot * be);
    result.Re_hot = result.velocity_hot * d_eq_hot * hotFluid.rho / hotFluid.viscosity;

    double k = 0.0;
    double k_old = -1.0;
    double Dc = 0.0;

    const int MAX_ITER = 500;
    int iter = 0;

    while (iter++ < MAX_ITER)
    {
        double alpha_cold = calculateAlpha(coldFluid, result.velocity_cold, d_eq_cold, Dc);
        double alpha_hot = calculateAlpha(hotFluid, result.velocity_hot, d_eq_hot, Dc);

        if (alpha_cold <= 0.0 || alpha_hot <= 0.0) {
            result.error_message = "Коэффициент теплоотдачи обратился в ноль — проверьте входные данные";
            return result;
        }

        k = 1.0 / (
            1.0 / alpha_hot +
            wallProperties.thickness / wallProperties.lambda +
            1.0 / alpha_cold +
            wallProperties.fouling_factor
            );

        double A = result.Q_required / (k * result.LMTD_required);
        double L = A / (2.0 * be);

        double t = wallProperties.thickness + std::max(geo.width_cold, geo.width_hot);
        double x = ((geo.d_inner / t) - 1.0) / 2.0;

        int N = static_cast<int>(ceil(sqrt(2.0 * L / PI / t + x * x) - x));
        if (N % 2 == 1)
            N += 1;

        Dc = geo.d_inner + t + 2.0 * N * t;

        if (k_old > 0.0 && std::abs(k - k_old) / k_old < Eps)
        {
            result.alpha_cold = alpha_cold;
            result.alpha_hot = alpha_hot;
            result.channel_width = be;
            result.A = A;
            result.channel_length = L;
            result.turns = N;
            result.K = k;
            result.D = Dc;
            break;
        }

        k_old = k;

        if (iter == MAX_ITER) {
            result.error_message = "Итерационный расчёт не сошёлся за " + std::to_string(MAX_ITER) + " итераций";
            return result;
        }
    }

    result.Q_real = result.K * result.LMTD_required * (2.0 * result.channel_width * result.channel_length);
    result.t_hot_out_real = hotFluid.t_in - result.Q_real / (hotFluid.G * hotFluid.cp);
    result.t_cold_out_real = coldFluid.t_in + result.Q_real / (coldFluid.G * coldFluid.cp);
    result.LMTD_real = calculateLMTD(hotFluid.t_in, result.t_hot_out_real,
        coldFluid.t_in, result.t_cold_out_real);

    double inlet_area_hot = hotFluid.G / (hotFluid.rho * result.velocity_hot);
    double inlet_area_cold = coldFluid.G / (coldFluid.rho * result.velocity_cold);
    double inlet_area_max = std::max(inlet_area_hot, inlet_area_cold);
    result.inlet_D = sqrt(inlet_area_max / PI) * 2.0;

    double lambda_cold = 0.3164 / pow(result.Re_cold, 0.25);
    double lambda_hot = 0.3164 / pow(result.Re_hot, 0.25);

    double d_eq_cold_final = 2.0 * geo.width_cold * result.channel_width / (geo.width_cold + result.channel_width);
    double d_eq_hot_final = 2.0 * geo.width_hot * result.channel_width / (geo.width_hot + result.channel_width);

    double dp_cold = lambda_cold * (result.channel_length / d_eq_cold_final)
        * (coldFluid.rho * result.velocity_cold * result.velocity_cold / 2.0);
    double dp_hot = lambda_hot * (result.channel_length / d_eq_hot_final)
        * (hotFluid.rho * result.velocity_hot * result.velocity_hot / 2.0);

    result.power_cold = coldFluid.G * dp_cold / (coldFluid.rho * n);
    result.power_hot = hotFluid.G * dp_hot / (hotFluid.rho * n);

    result.geometry = geo;
    result.wall = wallProperties;

    return result;
}


double SpiralHeatExchanger::calculateLMTD(double t_hot_in, double t_hot_out,
    double t_cold_in, double t_cold_out) const
{
    double dt1 = std::abs(t_hot_in - t_cold_out);
    double dt2 = std::abs(t_hot_out - t_cold_in);

    if (std::abs(dt1 - dt2) < 1e-9)
        return dt1;

    double larger = std::max(dt1, dt2);
    double smaller = std::min(dt1, dt2);
    return (larger - smaller) / log(larger / smaller);
}

double SpiralHeatExchanger::calculateAlpha(const Fluid& f, double velocity,
    double d_eq, double Dc) const
{
    if (velocity <= 0.0)
        return 0.0;

    double Re = velocity * d_eq * f.rho / f.viscosity;
    if (Re <= ReConst1)
        return 0.0;

    double Pr = f.cp * f.viscosity / f.lambda;
    double a_coof = calculateAlphaCoof(d_eq, Dc);
    double Nu = 0.023 * pow(Re, 0.8) * pow(Pr, 0.4) * a_coof;

    return Nu * f.lambda / d_eq;
}

double SpiralHeatExchanger::calculateAlphaCoof(double de, double Dc) const
{
    if (Dc <= 0.0)
        return 1.1;

    return 1.0 + 3.54 * de / Dc;
}

std::string SpiralHeatExchanger::validateInputs()
{
    if (hotFluid.G <= 0 || coldFluid.G <= 0)
        return "Массовый расход должен быть положительным";
    if (hotFluid.t_in <= hotFluid.t_out)
        return "Температура входа горячей среды должна быть выше выхода";
    if (coldFluid.t_in >= coldFluid.t_out)
        return "Температура входа холодной среды должна быть ниже выхода";

    return "";
}