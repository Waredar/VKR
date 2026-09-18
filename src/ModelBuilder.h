#pragma once

#include "solid.h"
#include "assembly.h"
#include "SpiralHeatExchanger.h"
#include <vector>
#include <functional>
#include <QString>

class ModelBuilder {
public:
    using ProgressCallback = std::function<void(int, int, const QString&)>;

    void setProgressCallback(ProgressCallback cb) { m_progressCallback = cb; }

    SPtr<MbAssembly> BuildModel(const CalculationResult& res);

private:
    ProgressCallback m_progressCallback;

    void reportProgress(int step, int total, const QString& description) {
        if (m_progressCallback)
            m_progressCallback(step, total, description);
    }

private:
    MbSolid* CreateSpiral(double d_inner, double turns, double thickness,
        double gap_1, double gap_2, double channel_width, bool is_second_spiral);

    MbSolid* CreateSpiralDivider(double d_inner, double thickness,
        double channel_width, double gap_1, double gap_2, bool is_second);

    MbSolid* CreateShell(double d_in_shell, double shell_thickness,
        double channel_width, double gasket_length, double hole_diameter);

    MbSolid* CreateNozzle(const MbPlacement3D& placement,
        double d_in, double wall_thickness, double pipe_len,
        double flange_d, double flange_thickness,
        double hole_pcd, int num_holes, double hole_d, double f);

    MbSolid* CreateShellFlange(double d_in_shell, double shell_thickness,
        double channel_width, double gasket_length,
        int hole_count, double d_hole, double flange_width, double flange_height);

    MbSolid* CreateGasket(double d_in_shell, double r_start,
        double gasket_length, double nozzle_d_in);

    MbSolid* CreateCover(double d_in_shell, double r_in,
        double shell_thickness, double cap_thickness,
        double flange_height,
        int hole_count, double d_hole,
        double nozzle_d_in, double nozzle_wall, double nozzle_len,
        double nozzle_flange_d, double nozzle_flange_t,
        double nozzle_hole_pcd, int nozzle_num_holes, double nozzle_hole_d,
        double nozzle_chamfer);

    SPtr<MbAssembly> AssembleHeatExchanger(
        MbSolid* resultBody,
        MbSolid* gasket1, MbSolid* gasket2,
        MbSolid* cover1, MbSolid* cover2,
        double d_in_shell, double s_tck,
        double channel_width, double gasket_length,
        double flange_height);
};