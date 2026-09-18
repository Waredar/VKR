#include "CalcResultSerializer.h"

#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QTextDocument>
#include <QPrinter>
#include <QPageSize>
#include <QPageLayout>
#include <QMarginsF>


static void w(QTextStream& out, const QString& key, double val)
{
    out << key << "=" << QString::number(val, 'g', 15) << "\n";
}

static void w(QTextStream& out, const QString& key, int val)
{
    out << key << "=" << val << "\n";
}

static void w(QTextStream& out, const QString& key, const std::string& val)
{
    out << key << "=" << QString::fromStdString(val) << "\n";
}

static double rd(const QMap<QString, QString>& m, const QString& key, double def = 0.0)
{
    auto it = m.find(key);
    return (it != m.end()) ? it->toDouble() : def;
}

static int ri(const QMap<QString, QString>& m, const QString& key, int def = 0)
{
    auto it = m.find(key);
    return (it != m.end()) ? it->toInt() : def;
}

static std::string rs(const QMap<QString, QString>& m, const QString& key)
{
    auto it = m.find(key);
    return (it != m.end()) ? it->toStdString() : std::string{};
}

QString CalcResultSerializer::save(const CalculationResult& r, const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return QString("Не удалось открыть файл для записи: %1").arg(filePath);

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    out << "[SpiralHX_Calculation]\n";

    w(out, "Q_required", r.Q_required);
    w(out, "LMTD_required", r.LMTD_required);
    w(out, "Q_real", r.Q_real);
    w(out, "LMTD_real", r.LMTD_real);
    w(out, "K", r.K);
    w(out, "alpha_hot", r.alpha_hot);
    w(out, "alpha_cold", r.alpha_cold);

    w(out, "velocity_hot", r.velocity_hot);
    w(out, "velocity_cold", r.velocity_cold);
    w(out, "Re_hot", r.Re_hot);
    w(out, "Re_cold", r.Re_cold);
    w(out, "t_hot_out_real", r.t_hot_out_real);
    w(out, "t_cold_out_real", r.t_cold_out_real);
    w(out, "power_hot", r.power_hot);
    w(out, "power_cold", r.power_cold);

    w(out, "A", r.A);
    w(out, "channel_length", r.channel_length);
    w(out, "channel_width", r.channel_width);
    w(out, "turns", r.turns);
    w(out, "D", r.D);
    w(out, "inlet_D", r.inlet_D);

    w(out, "geom.width_hot", r.geometry.width_hot);
    w(out, "geom.width_cold", r.geometry.width_cold);
    w(out, "geom.d_inner", r.geometry.d_inner);
    w(out, "geom.shell_thickness", r.geometry.shell_thickness);
    w(out, "geom.cover_thickness", r.geometry.cover_thickness);

    w(out, "wall.lambda", r.wall.lambda);
    w(out, "wall.thickness", r.wall.thickness);
    w(out, "wall.fouling_factor", r.wall.fouling_factor);

    w(out, "gasket_thickness", r.gasket_thickness);
    w(out, "nozzle_shell_thickness", r.nozzle_shell_thickness);
    w(out, "nozzle_shell_length", r.nozzle_shell_length);

    w(out, "flange.name", r.selected_flange.name);
    w(out, "flange.inner_d", r.selected_flange.inner_d);
    w(out, "flange.outer_d", r.selected_flange.outer_d);
    w(out, "flange.bolt_circle_d", r.selected_flange.bolt_circle_d);
    w(out, "flange.flange_thickness", r.selected_flange.flange_thickness);
    w(out, "flange.bolt_d", r.selected_flange.bolt_d);
    w(out, "flange.bolt_count", r.selected_flange.bolt_count);

    w(out, "sf.name", r.shell_flange.name);
    w(out, "sf.inner_d", r.shell_flange.inner_d);
    w(out, "sf.outer_d", r.shell_flange.outer_d);
    w(out, "sf.bolt_circle_d", r.shell_flange.bolt_circle_d);
    w(out, "sf.flange_thickness", r.shell_flange.flange_thickness);
    w(out, "sf.bolt_d", r.shell_flange.bolt_d);
    w(out, "sf.bolt_count", r.shell_flange.bolt_count);

    return {};
}


CalculationResult CalcResultSerializer::load(const QString& filePath, QString& outError)
{
    CalculationResult r{};
    outError.clear();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        outError = QString("Не удалось открыть файл: %1").arg(filePath);
        return r;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    QString firstLine = in.readLine().trimmed();
    if (firstLine != "[SpiralHX_Calculation]") {
        outError = "Файл не является файлом расчёта SpiralHX.";
        return r;
    }

    QMap<QString, QString> m;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty() || line.startsWith('#')) continue;
        int eq = line.indexOf('=');
        if (eq < 0) continue;
        m[line.left(eq).trimmed()] = line.mid(eq + 1).trimmed();
    }

    r.Q_required = rd(m, "Q_required");
    r.LMTD_required = rd(m, "LMTD_required");
    r.Q_real = rd(m, "Q_real");
    r.LMTD_real = rd(m, "LMTD_real");
    r.K = rd(m, "K");
    r.alpha_hot = rd(m, "alpha_hot");
    r.alpha_cold = rd(m, "alpha_cold");

    r.velocity_hot = rd(m, "velocity_hot");
    r.velocity_cold = rd(m, "velocity_cold");
    r.Re_hot = rd(m, "Re_hot");
    r.Re_cold = rd(m, "Re_cold");
    r.t_hot_out_real = rd(m, "t_hot_out_real");
    r.t_cold_out_real = rd(m, "t_cold_out_real");
    r.power_hot = rd(m, "power_hot");
    r.power_cold = rd(m, "power_cold");

    r.A = rd(m, "A");
    r.channel_length = rd(m, "channel_length");
    r.channel_width = rd(m, "channel_width");
    r.turns = rd(m, "turns");
    r.D = rd(m, "D");
    r.inlet_D = rd(m, "inlet_D");

    r.geometry.width_hot = rd(m, "geom.width_hot");
    r.geometry.width_cold = rd(m, "geom.width_cold");
    r.geometry.d_inner = rd(m, "geom.d_inner");
    r.geometry.shell_thickness = rd(m, "geom.shell_thickness");
    r.geometry.cover_thickness = rd(m, "geom.cover_thickness");

    r.wall.lambda = rd(m, "wall.lambda");
    r.wall.thickness = rd(m, "wall.thickness");
    r.wall.fouling_factor = rd(m, "wall.fouling_factor");

    r.gasket_thickness = rd(m, "gasket_thickness", 0.003);
    r.nozzle_shell_thickness = rd(m, "nozzle_shell_thickness", 4.0);
    r.nozzle_shell_length = rd(m, "nozzle_shell_length", 150.0);

    r.selected_flange.name = rs(m, "flange.name");
    r.selected_flange.inner_d = rd(m, "flange.inner_d");
    r.selected_flange.outer_d = rd(m, "flange.outer_d");
    r.selected_flange.bolt_circle_d = rd(m, "flange.bolt_circle_d");
    r.selected_flange.flange_thickness = rd(m, "flange.flange_thickness");
    r.selected_flange.bolt_d = rd(m, "flange.bolt_d");
    r.selected_flange.bolt_count = ri(m, "flange.bolt_count");

    r.shell_flange.name = rs(m, "sf.name");
    r.shell_flange.inner_d = rd(m, "sf.inner_d");
    r.shell_flange.outer_d = rd(m, "sf.outer_d");
    r.shell_flange.bolt_circle_d = rd(m, "sf.bolt_circle_d");
    r.shell_flange.flange_thickness = rd(m, "sf.flange_thickness");
    r.shell_flange.bolt_d = rd(m, "sf.bolt_d");
    r.shell_flange.bolt_count = ri(m, "sf.bolt_count");

    return r;
}

static QString cell(const QString& label, const QString& value,
    const QString& color = {})
{
    QString valStyle = color.isEmpty()
        ? "font-weight:600;"
        : QString("font-weight:600;color:%1;").arg(color);

    return QString(
        "<tr>"
        "<td style='padding:4px 12px 4px 4px;color:#444;'>%1</td>"
        "<td style='padding:4px 4px 4px 4px;%2'>%3</td>"
        "</tr>")
        .arg(label, valStyle, value);
}

static QString hotColdCell(const QString& label,
    const QString& hot, const QString& cold,
    const QString& unit = {})
{
    QString val = QString(
        "<span style='color:#cc2200;font-weight:600;'>%1</span>"
        " / "
        "<span style='color:#0055cc;font-weight:600;'>%2</span>%3")
        .arg(hot, cold,
            unit.isEmpty() ? QString() : QString("&nbsp;%1").arg(unit));
    return cell(label, val);
}

static QString sectionHeader(const QString& title)
{
    return QString(
        "<tr><td colspan='2' style='"
        "padding:10px 4px 4px 4px;"
        "font-size:11pt;"
        "font-weight:bold;"
        "color:#1a3a5c;"
        "border-bottom:2px solid #1a3a5c;"
        "'>%1</td></tr>")
        .arg(title);
}

QString CalcResultSerializer::buildHtmlReport(const CalculationResult& r)
{
    auto n = [](double v, int dec = 2) { return QString::number(v, 'f', dec); };

    QString rows;

    rows += sectionHeader("ТЕПЛОФИЗИКА");
    rows += cell("Требуемая тепловая мощность:",
        n(r.Q_required / 1000.0, 2) + "&nbsp;кВт");
    rows += cell("LMTD (средний температурный напор):",
        n(r.LMTD_real, 2) + "&nbsp;&deg;C");
    rows += cell("Коэффициент теплопередачи K:",
        n(r.K, 1) + "&nbsp;Вт/(м&sup2;&middot;К)");
    rows += hotColdCell("Коэффициент теплоотдачи (гор / хол):",
        n(r.alpha_hot, 1), n(r.alpha_cold, 1),
        "Вт/(м&sup2;&middot;К)");
    rows += cell("Теплопроводность стенки:",
        n(r.wall.lambda, 1) + "&nbsp;Вт/(м&middot;К)");
    rows += hotColdCell("Температура на выходе (гор / хол):",
        n(r.t_hot_out_real, 1), n(r.t_cold_out_real, 1),
        "&deg;C");

    rows += sectionHeader("ГИДРОДИНАМИКА");
    rows += hotColdCell("Скорость среды (гор / хол):",
        n(r.velocity_hot, 2), n(r.velocity_cold, 2), "м/с");
    rows += hotColdCell("Число Рейнольдса Re (гор / хол):",
        QString::number(static_cast<int>(r.Re_hot)),
        QString::number(static_cast<int>(r.Re_cold)));

    rows += sectionHeader("ГЕОМЕТРИЯ ТЕПЛООБМЕННИКА");
    rows += cell("Наружный диаметр корпуса:",
        n(r.D * 1000.0, 1) + "&nbsp;мм");
    rows += cell("Поверхность теплообмена:",
        n(r.A, 3) + "&nbsp;м&sup2;");
    rows += cell("Количество витков:",
        n(r.turns, 0));
    rows += cell("Длина канала:",
        n(r.channel_length, 2) + "&nbsp;м");
    rows += cell("Ширина листа (b):",
        n(r.channel_width * 1000.0, 1) + "&nbsp;мм");
    rows += hotColdCell("Ширина канала (гор / хол):",
        n(r.geometry.width_hot * 1000.0, 1),
        n(r.geometry.width_cold * 1000.0, 1), "мм");
    rows += cell("Внутренний диаметр спирали:",
        n(r.geometry.d_inner * 1000.0, 1) + "&nbsp;мм");
    rows += cell("Толщина стенки разделителя:",
        n(r.wall.thickness * 1000.0, 1) + "&nbsp;мм");
    rows += cell("Толщина обечайки:",
        n(r.geometry.shell_thickness * 1000.0, 1) + "&nbsp;мм");
    rows += cell("Толщина крышки:",
        n(r.geometry.cover_thickness * 1000.0, 1) + "&nbsp;мм");
    rows += cell("Толщина прокладки:",
        n(r.gasket_thickness * 1000.0, 1) + "&nbsp;мм");

    rows += sectionHeader("ПАТРУБКИ И ФЛАНЦЫ");
    rows += cell("Расчётный диаметр входного отверстия:",
        n(r.inlet_D * 1000.0, 1) + "&nbsp;мм");
    rows += cell("Толщина стенки патрубка:",
        n(r.nozzle_shell_thickness, 1) + "&nbsp;мм");
    rows += cell("Длина патрубка:",
        n(r.nozzle_shell_length, 1) + "&nbsp;мм");

    if (!r.selected_flange.name.empty()) {
        const auto& f = r.selected_flange;
        rows += cell("Фланец патрубка:",
            QString::fromStdString(f.name));
        rows += cell("&nbsp;&nbsp;Внутренний / наружный диаметр:",
            n(f.inner_d, 1) + " / " + n(f.outer_d, 1) + "&nbsp;мм");
        rows += cell("&nbsp;&nbsp;Диаметр болтовой окружности:",
            n(f.bolt_circle_d, 1) + "&nbsp;мм");
        rows += cell("&nbsp;&nbsp;Толщина фланца:",
            n(f.flange_thickness, 1) + "&nbsp;мм");
        rows += cell("&nbsp;&nbsp;Болты:",
            "M" + n(f.bolt_d, 0) + " × " +
            QString::number(f.bolt_count) + "&nbsp;шт.");
    }

    if (!r.shell_flange.name.empty()) {
        const auto& sf = r.shell_flange;
        rows += cell("Фланец обечайки:",
            QString::fromStdString(sf.name));
        rows += cell("&nbsp;&nbsp;Внутренний / наружный диаметр:",
            n(sf.inner_d, 1) + " / " + n(sf.outer_d, 1) + "&nbsp;мм");
        rows += cell("&nbsp;&nbsp;Диаметр болтовой окружности:",
            n(sf.bolt_circle_d, 1) + "&nbsp;мм");
        rows += cell("&nbsp;&nbsp;Толщина фланца:",
            n(sf.flange_thickness, 1) + "&nbsp;мм");
        rows += cell("&nbsp;&nbsp;Болты:",
            "M" + n(sf.bolt_d, 0) + " × " +
            QString::number(sf.bolt_count) + "&nbsp;шт.");
    }

    return QString(R"(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8"/>
<style>
  body  { font-family: Arial, sans-serif; font-size: 10pt;
          color: #222; margin: 0; padding: 0; }
  .header { background:#1a3a5c; color:white; padding:16px 20px 12px 20px;
             margin-bottom:12px; }
  .header h1 { margin:0; font-size:15pt; letter-spacing:1px; }
  .header p  { margin:4px 0 0; font-size:9pt; color:#b0c8e8; }
  table { width:100%; border-collapse:collapse; }
  td    { vertical-align:top; }
  .footer { margin-top:20px; font-size:8pt; color:#888;
             border-top:1px solid #ccc; padding-top:6px; }
</style>
</head>
<body>
<div class="header">
  <h1>Спиральный теплообменник — результаты расчёта</h1>
  <p>SpiralHX</p>
</div>
<table>
%1
</table>
<div class="footer">Документ сформирован автоматически программой SpiralHX</div>
</body>
</html>
)").arg(rows);
}

QString CalcResultSerializer::savePdf(const CalculationResult& r,
    const QString& filePath)
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageOrientation(QPageLayout::Portrait);
    printer.setPageMargins(QMarginsF(15.0, 15.0, 15.0, 15.0),
        QPageLayout::Millimeter);

    QTextDocument doc;
    doc.setDefaultFont(QFont("Arial", 10));
    doc.setHtml(buildHtmlReport(r));

    doc.print(&printer);
    return {};
}