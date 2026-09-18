#pragma once

#include <string>
#include <vector>

struct Fluid
{
    double G;          // массовый расход [кг/с]
    double rho;        // плотность [кг/м3]
    double cp;         // теплоёмкость [Дж/(кг·К)]
    double lambda;     // теплопроводность [Вт/(м·К)]
    double viscosity;  // динамическая вязкость [Па·с]

    double t_in;       // входная температура
    double t_out;      // выходная температура

    double max_velocity; // допустимая скорость
};

struct Wall
{
    double lambda;
    double thickness;
    double fouling_factor;
};

struct Geometry
{
    double width_hot;
    double width_cold;

    double d_inner;
    double shell_thickness;
    double cover_thickness;

    bool   auto_width = true;
    double width_min = 0.0;
    double width_max = 9999.0;
};

struct Flange {
    std::string name;
    double inner_d;
    double outer_d;
    double bolt_circle_d;
    double flange_thickness;
    double bolt_d;
    int bolt_count;
};


struct CalculationResult
{
    std::string error_message;

    double Q_required;
    double LMTD_required;

    double velocity_hot;
    double velocity_cold;

    double Re_hot;
    double Re_cold;

    double alpha_hot;
    double alpha_cold;
    double K;

    double Q_real;
    double t_hot_out_real;
    double t_cold_out_real;
    double LMTD_real;

    double power_hot;
    double power_cold;

    double A;
    double channel_length;
    double channel_width;
    double turns;
    double D;

    Geometry geometry;
    Wall wall;
    Flange selected_flange;
    Flange shell_flange;
    double inlet_D;
    double gasket_thickness = 0.003;
    double nozzle_shell_thickness = 4.0;
    double nozzle_shell_length = 150.0;

};

class SpiralHeatExchanger
{
public:
    SpiralHeatExchanger();
    SpiralHeatExchanger(const Fluid& hot, const Fluid& cold, const Wall& wallProperties, const Geometry& geom);

    void setHotFluid(const Fluid& hot) { hotFluid = hot; };
    void setColdFluid(const Fluid& cold) { coldFluid = cold; };
    void setWall(const Wall& wall) { wallProperties = wall; };
    void setGeometry(const Geometry& geom) { geo = geom; };


    CalculationResult calculate();

private:
    std::string validateInputs();

    double calculateLMTD(double t_hot_in, double t_hot_out, double t_cold_in, double t_cold_out) const;
    double calculateAlpha(const Fluid& f, double velocity, double d_eq, double Dc) const;
    double calculateAlphaCoof(double de, double Dc) const;

    Fluid hotFluid;
    Fluid coldFluid;
    Wall wallProperties;
    Geometry geo;


    const std::vector<double> standard_width = { 0.2, 0.32, 0.5, 0.8, 1.0, 1.1, 1.25, 1.5 };
    const double ReConst1 = 10000.0;
    const double ReConst2 = 2300.0;
    const double Eps = 1e-6;
    const double g = 9.81;
    const double n = 0.7;
    const double PI = 3.14159265358979323846;
};