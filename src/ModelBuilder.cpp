#include "ModelBuilder.h"

#include <action_general.h>
#include <action_solid.h>

#include <templ_s_array.h>
#include <templ_rp_array.h>
#include <templ_sptr.h>

#include <mb_cart_point.h>
#include <mb_cart_point3d.h>
#include <mb_matrix3d.h>
#include <mb_placement3d.h>
#include <mb_axis3d.h>
#include <surf_cylinder_surface.h>

#include <cur_line_segment.h>
#include <cur_nurbs.h>
#include <cur_cubic_spline.h>
#include <cur_contour.h>
#include <cur_arc.h>

#include <surface.h>
#include <surf_plane.h>

#include <name_item.h>
#include <creator.h>
#include <solid.h>

#include "assembly.h"
#include <constraint.h>
#include "gcm_types.h"
#include <attr_product.h>

#include <last.h>

using namespace std;
using namespace c3d;

SPtr<MbAssembly> ModelBuilder::BuildModel(const CalculationResult& res)
{
    SPtr<MbAssembly> result;

    if (res.geometry.d_inner <= 0 || res.turns <= 0 || res.A <= 0)
        return result;

    double t = res.turns;
    double din = res.geometry.d_inner * 1000.0;
    double tck = res.wall.thickness * 1000.0;
    double w = res.channel_width * 1000.0;
    double gap_1 = res.geometry.width_hot * 1000.0;
    double gap_2 = res.geometry.width_cold * 1000.0;
    double s_tck = res.geometry.shell_thickness * 1000.0;

    double r_in = din / 2.0;
    double step_per_turn = (tck * 2.0) + gap_1 + gap_2;
    double r_end_axis = r_in + (tck / 2.0) + (step_per_turn * t);
    double r_outer_metal = r_end_axis + (tck / 2.0) + step_per_turn / 4.0;
    double d_in_shell = r_outer_metal * 2.0;

    double nozzle_d_in = res.selected_flange.inner_d;
    double nozzle_flange_d = res.selected_flange.outer_d;
    double nozzle_flange_t = res.selected_flange.flange_thickness;
    double nozzle_hole_pcd = res.selected_flange.bolt_circle_d;
    double nozzle_hole_d = res.selected_flange.bolt_d;
    int    nozzle_num_holes = res.selected_flange.bolt_count;
    double nozzle_chamfer = 8.0;

    double nozzle_wall = res.nozzle_shell_thickness;
    double nozzle_len = res.nozzle_shell_length;

    const int    sf_hole_count = res.shell_flange.bolt_count;
    const double sf_d_hole = res.shell_flange.bolt_d;
    const double sf_flange_width = res.shell_flange.flange_thickness;
    const double sf_flange_height = (res.shell_flange.outer_d - res.shell_flange.inner_d) / 2.0;

    const double gasket_length = res.gasket_thickness * 1000.0;

    const int totalSteps = 12;
    int step = 0;

    reportProgress(step++, totalSteps, "Создание первой спирали...");
    MbSolid* spiral1 = CreateSpiral(din, t, tck, gap_1, gap_2, w, false);

    reportProgress(step++, totalSteps, "Создание второй спирали...");
    MbSolid* spiral2 = CreateSpiral(din, t, tck, gap_1, gap_2, w, true);

    reportProgress(step++, totalSteps, "Создание центральных перегородок...");
    MbSolid* kern1 = CreateSpiralDivider(din, tck, w, gap_1, gap_2, false);
    MbSolid* kern2 = CreateSpiralDivider(din, tck, w, gap_1, gap_2, true);

    reportProgress(step++, totalSteps, "Создание корпуса...");
    MbSolid* shell = CreateShell(d_in_shell, s_tck, w, gasket_length, nozzle_d_in);

    reportProgress(step++, totalSteps, "Создание фланцев корпуса...");
    MbSolid* flange1 = CreateShellFlange(d_in_shell, s_tck, w, gasket_length,
        sf_hole_count, sf_d_hole, sf_flange_width, sf_flange_height);
    MbSolid* gasket1 = CreateGasket(d_in_shell, r_in, gasket_length, nozzle_d_in);
    MbSolid* gasket2 = CreateGasket(d_in_shell, r_in, gasket_length, nozzle_d_in);

    MbSNameMaker symNames(ct_SymmetrySolid, MbSNameMaker::i_SideNone);
    MbPlacement3D plSym;
    SolidSPtr flange2Result;
    ::SymmetrySolid(*flange1, cm_Copy,
        MbSymmetrySolidParams(plSym, symNames, ts_neutral),
        flange2Result);
    MbSolid* flange2 = flange2Result.detach();

    reportProgress(step++, totalSteps, "Создание патрубков...");
    double R_ext = r_outer_metal + s_tck;
    double overlap = 2.0;

    MbPlacement3D posForward(
        MbVector3D(0, 1, 0), MbVector3D(0, 0, 1),
        MbCartPoint3D(R_ext - overlap, 0, 0));
    MbSolid* nozzle1 = CreateNozzle(posForward,
        nozzle_d_in, nozzle_wall, nozzle_len,
        nozzle_flange_d, nozzle_flange_t,
        nozzle_hole_pcd, nozzle_num_holes, nozzle_hole_d, nozzle_chamfer);

    MbPlacement3D posBackward(
        MbVector3D(0, -1, 0), MbVector3D(0, 0, 1),
        MbCartPoint3D(-(R_ext - overlap), 0, 0));
    MbSolid* nozzle2 = CreateNozzle(posBackward,
        nozzle_d_in, nozzle_wall, nozzle_len,
        nozzle_flange_d, nozzle_flange_t,
        nozzle_hole_pcd, nozzle_num_holes, nozzle_hole_d, nozzle_chamfer);

    reportProgress(step++, totalSteps, "Объединение тел корпуса...");
    RPArray<MbSolid> parts;
    if (spiral1) parts.Add(spiral1);
    if (spiral2) parts.Add(spiral2);
    if (kern1)   parts.Add(kern1);
    if (kern2)   parts.Add(kern2);
    if (shell)   parts.Add(shell);
    if (flange1) parts.Add(flange1);
    if (flange2) parts.Add(flange2);
    if (nozzle1) parts.Add(nozzle1);
    if (nozzle2) parts.Add(nozzle2);

    MbSolid* bodyPtr = nullptr;
    MbSNameMaker names(ct_BooleanSolid, MbSNameMaker::i_SideNone, 0);
    ::UnionSolid(parts, cm_Same, true, names, false, bodyPtr);

    reportProgress(step++, totalSteps, "Создание крышек...");
    double cap_thickness = res.geometry.cover_thickness * 1000.0;

    MbSolid* cap1 = CreateCover(d_in_shell, r_in, s_tck, cap_thickness,
        sf_flange_height, sf_hole_count, sf_d_hole,
        nozzle_d_in, nozzle_wall, nozzle_len,
        nozzle_flange_d, nozzle_flange_t,
        nozzle_hole_pcd, nozzle_num_holes, nozzle_hole_d, nozzle_chamfer);

    reportProgress(step++, totalSteps, "Создание крышек...");
    MbSolid* cap2 = CreateCover(d_in_shell, r_in, s_tck, cap_thickness,
        sf_flange_height, sf_hole_count, sf_d_hole,
        nozzle_d_in, nozzle_wall, nozzle_len,
        nozzle_flange_d, nozzle_flange_t,
        nozzle_hole_pcd, nozzle_num_holes, nozzle_hole_d, nozzle_chamfer);

    reportProgress(step++, totalSteps, "Сборка теплообменника...");
    result = AssembleHeatExchanger(
        bodyPtr, gasket1, gasket2, cap1, cap2,
        d_in_shell, s_tck, w, gasket_length, sf_flange_height);

    reportProgress(totalSteps, totalSteps, "Готово");
    return result;
}

MbSolid* ModelBuilder::CreateSpiral(double d_inner, double turns, double thickness,
    double gap_1, double gap_2, double channel_width, bool is_second_spiral)
{
    double r_start = d_inner / 2.0;
    double step_per_turn = (thickness * 2.0) + gap_1 + gap_2;
    double radial_correction = (gap_2 - gap_1) / 2.0;
    double current_r_start = is_second_spiral ? (r_start + radial_correction) : r_start;
    double phase_shift = is_second_spiral ? M_PI : 0.0;

    size_t points_per_turn = 64;
    size_t total_points = static_cast<size_t>(points_per_turn * turns) + 1;

    SArray<MbCartPoint> points(total_points, 1);
    double delta_phi = M_PI2 / (double)points_per_turn;

    for (size_t i = 0; i < total_points; ++i) {
        double phi = i * delta_phi;
        double r = current_r_start + (thickness / 2.0) + (step_per_turn * phi / M_PI2);
        points.push_back(MbCartPoint(r * cos(phi + phase_shift), r * sin(phi + phase_shift)));
    }

    MbPlacement3D place;
    SPtr<MbCurve> spiral(MbCubicSpline::Create(points, false));
    SPtr<MbContour> contour(new MbContour);
    contour->AddSegment(spiral);

    double t_end = spiral->GetTMax();
    MbCartPoint p_end;
    MbVector tangent;
    spiral->GetLimitPoint(2, p_end);
    spiral->Tangent(t_end, tangent);
    tangent.Normalize();

    double r_target = r_start + (step_per_turn * (turns + 0.5)) + thickness;
    double b = 2.0 * (p_end.x * tangent.x + p_end.y * tangent.y);
    double c = (p_end.x * p_end.x + p_end.y * p_end.y) - (r_target * r_target);
    double D = b * b - 4.0 * c;
    double tail_length = (D >= 0) ? (-b + sqrt(D)) / 2.0 : (thickness + gap_1);

    contour->AddSegment(new MbLineSegment(p_end,
        MbCartPoint(p_end.x + tangent.x * tail_length, p_end.y + tangent.y * tail_length)));

    RPArray<MbContour> contours(1, 1);
    contours.push_back(contour);
    SPtr<MbSurface> surface(new MbPlane(place));
    MbSweptData curvesData(*surface, contours);

    ExtrusionValues extrudeParams;
    extrudeParams.side1.scalarValue = channel_width / 2;
    extrudeParams.side1.way = sw_scalarValue;
    extrudeParams.side2.scalarValue = channel_width / 2;
    extrudeParams.side2.way = sw_scalarValue;
    extrudeParams.thickness1 = thickness / 2.0;
    extrudeParams.thickness2 = thickness / 2.0;

    MbSNameMaker snMakerExtrude(ct_CurveExtrusionSolid, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    MbSolid* surfaceSolid = nullptr;
    ::ExtrusionSolid(curvesData, place.Normal(), nullptr, nullptr, false,
        extrudeParams, snMakerExtrude, cNames, surfaceSolid);

    return surfaceSolid;
}

MbSolid* ModelBuilder::CreateSpiralDivider(double d_inner, double thickness,
    double channel_width, double gap_1, double gap_2, bool is_second)
{
    double radial_correction = (gap_2 - gap_1) / 2.0;

    SArray<MbCartPoint> rectPoints(4, 1);

    if (is_second) {
        double x_start = d_inner / 2.0 + thickness;
        double x_end = -(d_inner / 2.0 + radial_correction) - thickness / 2;
        rectPoints.push_back(MbCartPoint(x_start, 0));
        rectPoints.push_back(MbCartPoint(x_start, -thickness / 2.0));
        rectPoints.push_back(MbCartPoint(x_end, -thickness / 2.0));
        rectPoints.push_back(MbCartPoint(x_end, 0));
    }
    else {
        double x_start = d_inner / 2.0 + thickness / 2;
        double x_end = -(d_inner / 2.0 + radial_correction) - thickness;
        rectPoints.push_back(MbCartPoint(x_start, 0));
        rectPoints.push_back(MbCartPoint(x_start, thickness / 2.0));
        rectPoints.push_back(MbCartPoint(x_end, thickness / 2.0));
        rectPoints.push_back(MbCartPoint(x_end, 0));
    }

    SPtr<MbContour> contour(new MbContour());
    for (size_t i = 0; i < 4; ++i)
        contour->AddSegment(new MbLineSegment(rectPoints[i], rectPoints[(i + 1) % 4]));

    MbPlacement3D place;
    RPArray<MbContour> contours(1, 1);
    contours.push_back(contour);
    SPtr<MbSurface> surface(new MbPlane(place));
    MbSweptData curvesData(*surface, contours);

    ExtrusionValues extrudeParams;
    extrudeParams.side1.scalarValue = channel_width / 2;
    extrudeParams.side1.way = sw_scalarValue;
    extrudeParams.side2.scalarValue = channel_width / 2;
    extrudeParams.side2.way = sw_scalarValue;

    MbSolid* dividerSolid = nullptr;
    MbSNameMaker snMaker(ct_CurveExtrusionSolid, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);
    ::ExtrusionSolid(curvesData, place.Normal(), nullptr, nullptr, false,
        extrudeParams, snMaker, cNames, dividerSolid);

    return dividerSolid;
}

MbSolid* ModelBuilder::CreateShell(double d_in_shell, double shell_thickness,
    double channel_width, double gasket_length, double hole_diameter)
{
    double r_mid = d_in_shell / 2.0 + shell_thickness / 2.0;

    SPtr<MbArc> circle(new MbArc(r_mid));
    SPtr<MbContour> contour(new MbContour());
    contour->AddSegment(circle);

    RPArray<MbContour> contours(1, 1);
    contours.push_back(contour);

    MbPlacement3D place;
    SPtr<MbSurface> surface(new MbPlane(place));
    MbSweptData curvesData(*surface, contours);

    ExtrusionValues extrudeParams;
    extrudeParams.side1.scalarValue = channel_width / 2 + gasket_length;
    extrudeParams.side1.way = sw_scalarValue;
    extrudeParams.side2.scalarValue = channel_width / 2 + gasket_length;
    extrudeParams.side2.way = sw_scalarValue;
    extrudeParams.thickness1 = shell_thickness / 2.0;
    extrudeParams.thickness2 = shell_thickness / 2.0;

    MbSNameMaker snMaker(ct_CurveExtrusionSolid, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    MbSolid* shellSolid = nullptr;
    ::ExtrusionSolid(curvesData, place.Normal(), nullptr, nullptr, false,
        extrudeParams, snMaker, cNames, shellSolid);

    if (shellSolid == nullptr || hole_diameter <= 0)
        return shellSolid;

    MbPlacement3D holePlace;
    holePlace.Rotate(MbAxis3D::yAxis, M_PI_2);

    MbSNameMaker snHole(ct_ElementarySolid, MbSNameMaker::i_SideNone, 1);
    MbElementarySolidParams cylParams(snHole);

    double halfLength = r_mid + shell_thickness / 2.0 + 10.0;
    cylParams.InitCylinder(holePlace, hole_diameter / 2.0, halfLength, halfLength);

    MbElementarySolidResults results;
    if (::ElementarySolid(cylParams, results) != rt_Success)
        return shellSolid;

    SolidSPtr holeTool(results.DetachSolid());
    if (!holeTool)
        return shellSolid;

    MbSNameMaker boolSnMaker(ct_BooleanSolid, MbSNameMaker::i_SideNone, 0);
    MbBooleanOperationParams pDiff(bo_Difference, true, boolSnMaker);
    SolidSPtr shellPtr(shellSolid);
    SolidSPtr boolResult;

    if (::BooleanResult(shellPtr, cm_Same, holeTool, cm_Copy, pDiff, boolResult) == rt_Success && boolResult) {
        shellPtr = nullptr;
        shellSolid = boolResult.detach();
    }
    else {
        shellSolid = shellPtr.detach();
    }

    return shellSolid;
}

MbSolid* ModelBuilder::CreateNozzle(const MbPlacement3D& placement,
    double d_in, double wall_thickness, double pipe_len,
    double flange_d, double flange_thickness,
    double hole_pcd, int num_holes, double hole_d, double f)
{
    double r_pipe_mid = (d_in + wall_thickness) / 2.0;
    SPtr<MbArc> pipeCircle(new MbArc(MbCartPoint(0, 0), r_pipe_mid));

    SPtr<MbContour> pipeContour(new MbContour());
    pipeContour->AddSegment(pipeCircle);

    RPArray<MbContour> pipeContours(1, 1);
    pipeContours.push_back(pipeContour);

    SPtr<MbSurface> pipeSurface(new MbPlane(placement));
    MbSweptData pipeData(*pipeSurface, pipeContours);

    ExtrusionValues pipeParams;
    pipeParams.side1.scalarValue = pipe_len;
    pipeParams.side1.way = sw_scalarValue;
    pipeParams.thickness1 = wall_thickness / 2.0;
    pipeParams.thickness2 = wall_thickness / 2.0;

    MbSNameMaker snPipe(ct_CurveExtrusionSolid, MbSNameMaker::i_SideNone, 1);
    MbSolid* pipeSolid = nullptr;
    ::ExtrusionSolid(pipeData, placement.Normal(), nullptr, nullptr, false,
        pipeParams, snPipe, PArray<MbSNameMaker>(0, 1, false), pipeSolid);

    MbPlacement3D flangePlace(placement);
    MbVector3D offset = flangePlace.Normal();
    offset *= (pipe_len - flange_thickness);
    flangePlace.Move(offset);

    double flange_width = (flange_d - d_in) / 2.0;
    double r_flange_mid = (d_in + flange_width) / 2.0;

    SPtr<MbArc> flangeCircle(new MbArc(MbCartPoint(0, 0), r_flange_mid));
    SPtr<MbContour> flangeContour(new MbContour());
    flangeContour->AddSegment(flangeCircle);

    RPArray<MbContour> flangeContours(1, 1);
    flangeContours.push_back(flangeContour);

    SPtr<MbSurface> flangeSurface(new MbPlane(flangePlace));
    MbSweptData flangeData(*flangeSurface, flangeContours);

    ExtrusionValues flangeParams;
    flangeParams.side1.scalarValue = flange_thickness;
    flangeParams.side1.way = sw_scalarValue;
    flangeParams.thickness1 = flange_width / 2.0;
    flangeParams.thickness2 = flange_width / 2.0;

    MbSNameMaker snFlange(ct_CurveExtrusionSolid, MbSNameMaker::i_SideNone, 2);
    MbSolid* flangeSolid = nullptr;
    ::ExtrusionSolid(flangeData, flangePlace.Normal(), nullptr, nullptr, false,
        flangeParams, snFlange, PArray<MbSNameMaker>(0, 1, false), flangeSolid);

    MbSolid* nozzleBody = nullptr;
    RPArray<MbSolid> parts(2, 1);
    parts.Add(pipeSolid);
    parts.Add(flangeSolid);
    MbSNameMaker snUnion(ct_BooleanSolid, MbSNameMaker::i_SideNone, 10);
    ::UnionSolid(parts, cm_Same, true, snUnion, false, nozzleBody);

    if (nozzleBody && num_holes > 0) {
        RPArray<MbContour> holeContours(num_holes, 1);
        double angle_step = M_PI2 / (double)num_holes;

        for (int i = 0; i < num_holes; ++i) {
            double angle = i * angle_step;
            double x = (hole_pcd / 2.0) * cos(angle);
            double y = (hole_pcd / 2.0) * sin(angle);

            MbArc* holeCircle = new MbArc(MbCartPoint(x, y), hole_d / 2.0);
            MbContour* cnt = new MbContour();
            cnt->AddSegment(holeCircle);
            holeContours.push_back(cnt);
        }

        MbPlacement3D holePlace(flangePlace);
        holePlace.Move(placement.Normal() * -1.0);

        SPtr<MbSurface> holeSurf(new MbPlane(holePlace));
        MbSweptData holeData(*holeSurf, holeContours);

        ExtrusionValues holeParams;
        holeParams.side1.scalarValue = flange_thickness + 2.0;
        holeParams.side1.way = sw_scalarValue;

        MbSNameMaker snHoles(ct_CurveExtrusionSolid, MbSNameMaker::i_SideNone, 3);
        MbSolid* holesTool = nullptr;
        ::ExtrusionSolid(holeData, holePlace.Normal(), nullptr, nullptr, false,
            holeParams, snHoles, PArray<MbSNameMaker>(0, 1, false), holesTool);

        if (holesTool) {
            MbSNameMaker bNames(ct_BooleanSolid, MbSNameMaker::i_SideNone, 20);
            MbBooleanOperationParams bParams(bo_Difference, true, bNames);
            SolidSPtr solid1(nozzleBody);
            SolidSPtr solid2(holesTool);
            SolidSPtr resultBody;
            if (::BooleanResult(solid1, cm_Same, solid2, cm_Same, bParams, resultBody) == rt_Success)
                if (resultBody != nullptr)
                    nozzleBody = resultBody.detach();
        }
    }

    //MbSNameMaker chamferNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);
    //SmoothValues params;
    //params.distance1 = f;
    //params.distance2 = f;
    //params.form = st_Chamfer;
    //params.prolong = true;
    //params.smoothCorner = SmoothValues::ec_uniform;

    //RPArray<MbCurveEdge> allEdges(4, 1);
    //nozzleBody->GetEdges(allEdges);
    //c3d::EdgesSPtrVector initCurves;
    //initCurves.emplace_back(allEdges[9]);
    //SolidSPtr pResult;
    //::ChamferSolid(*nozzleBody, cm_Copy, MbShellChamferParams(initCurves, params, chamferNames), pResult);

    //nozzleBody = pResult.detach();

    return nozzleBody;
}

MbSolid* ModelBuilder::CreateShellFlange(double d_in_shell, double shell_thickness,
    double channel_width, double gasket_length,
    int hole_count, double d_hole, double flange_width, double flange_height)
{
    double r_outer = d_in_shell / 2.0 + shell_thickness;
    double r_flange_mid = r_outer + flange_height / 2;

    SPtr<MbArc> circle1(new MbArc(r_flange_mid));
    SPtr<MbContour> contour(new MbContour());
    contour->AddSegment(circle1);

    RPArray<MbContour> contours(1, 1);
    contours.push_back(contour);

    MbPlacement3D place;
    SPtr<MbSurface> surface(new MbPlane(place));
    MbSweptData curvesData(*surface, contours);

    ExtrusionValues extrudeParams;
    extrudeParams.side1.scalarValue = channel_width / 2 + gasket_length;
    extrudeParams.side1.way = sw_scalarValue;
    extrudeParams.side2.scalarValue = -channel_width / 2 - gasket_length + flange_width;
    extrudeParams.side2.way = sw_scalarValue;
    extrudeParams.thickness1 = flange_height / 2;
    extrudeParams.thickness2 = flange_height / 2;

    MbSNameMaker snMaker(ct_CurveExtrusionSolid, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    MbSolid* flangeSolid = nullptr;
    ::ExtrusionSolid(curvesData, place.Normal(), nullptr, nullptr, false,
        extrudeParams, snMaker, cNames, flangeSolid);

    if (flangeSolid && hole_count > 0) {
        double angle_step = M_PI2 / (double)hole_count;
        double hole_pcd = r_flange_mid;

        RPArray<MbContour> holeContours(hole_count, 1);
        for (int i = 0; i < hole_count; ++i) {
            double angle = i * angle_step;
            MbArc* hc = new MbArc(MbCartPoint(hole_pcd * cos(angle), hole_pcd * sin(angle)), d_hole / 2.0);
            MbContour* cnt = new MbContour();
            cnt->AddSegment(hc);
            holeContours.push_back(cnt);
        }

        MbPlacement3D holePlace(place);
        holePlace.Move(place.Normal() * (channel_width / 2 + gasket_length));

        SPtr<MbSurface> holeSurf(new MbPlane(holePlace));
        MbSweptData holeData(*holeSurf, holeContours);

        ExtrusionValues holeParams;
        holeParams.side1.way = sw_scalarValue;
        holeParams.side1.scalarValue = flange_width;

        MbSNameMaker snHoles(ct_CurveExtrusionSolid, MbSNameMaker::i_SideNone, 3);
        MbSolid* holesTool = nullptr;
        ::ExtrusionSolid(holeData, holePlace.Normal() * -1.0, nullptr, nullptr, false,
            holeParams, snHoles, PArray<MbSNameMaker>(0, 1, false), holesTool);

        if (holesTool) {
            SolidSPtr resultBody;
            MbSNameMaker bNames(ct_BooleanSolid, MbSNameMaker::i_SideNone, 20);
            MbBooleanOperationParams bParams(bo_Difference, true, bNames);
            SolidSPtr solid1(flangeSolid);
            SolidSPtr solid2(holesTool);
            if (::BooleanResult(solid1, cm_Same, solid2, cm_Same, bParams, resultBody) == rt_Success)
                flangeSolid = resultBody.detach();
        }
    }

    return flangeSolid;
}

MbSolid* ModelBuilder::CreateGasket(double d_in_shell, double r_start,
    double gasket_length, double nozzle_d_in)
{
    double r_outer_metal = d_in_shell / 2.0;

    MbPlacement3D place;

    SPtr<MbArc>     circle(new MbArc(r_outer_metal));
    SPtr<MbContour> contour(new MbContour());
    contour->AddSegment(circle);

    RPArray<MbContour> contours(1, 1);
    contours.push_back(contour);

    SPtr<MbSurface> surface(new MbPlane(place));
    MbSweptData     curvesData(*surface, contours);

    ExtrusionValues extrudeParams;
    extrudeParams.side1.scalarValue = gasket_length;
    extrudeParams.side1.way = sw_scalarValue;
    extrudeParams.side2.scalarValue = 0.0;
    extrudeParams.side2.way = sw_scalarValue;

    MbSNameMaker          snMaker(ct_CurveExtrusionSolid, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker>  cNames(0, 1, false);

    MbSolid* gasketSolid = nullptr;
    MbResultType res = ::ExtrusionSolid(curvesData, place.Normal(),
        nullptr, nullptr, false,
        extrudeParams, snMaker, cNames,
        gasketSolid);
    if (!gasketSolid)
        return nullptr;

    if (nozzle_d_in > 0.0)
    {
        double r_hole = r_start / 2.0;
        double z_mid = gasket_length / 2.0;
        double halfLen = gasket_length / 2.0 + 1.0;

        MbPlacement3D cylPlace;
        cylPlace.Move(MbVector3D(0.0, r_hole, z_mid));

        MbSNameMaker snCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 1);
        MbElementarySolidParams cylParams(snCyl);
        cylParams.InitCylinder(cylPlace, nozzle_d_in / 2.0, halfLen, halfLen);

        MbElementarySolidResults cylResults;
        if (::ElementarySolid(cylParams, cylResults) == rt_Success)
        {
            MbSolid* holeTool = cylResults.GetResultSolid();

            SolidSPtr resultBody;
            MbSNameMaker bNames(ct_BooleanSolid, MbSNameMaker::i_SideNone, 20);
            MbBooleanOperationParams bParams(bo_Difference, true, bNames);
            SolidSPtr solid1(gasketSolid);
            SolidSPtr solid2(holeTool);
            if (::BooleanResult(solid1, cm_Same, solid2, cm_Same,
                bParams, resultBody) == rt_Success)
                gasketSolid = resultBody.detach();
        }
    }

    return gasketSolid;
}

MbSolid* ModelBuilder::CreateCover(double d_in_shell, double r_in,
    double shell_thickness, double cap_thickness,
    double flange_height,
    int hole_count, double d_hole,
    double nozzle_d_in, double nozzle_wall, double nozzle_len,
    double nozzle_flange_d, double nozzle_flange_t,
    double nozzle_hole_pcd, int nozzle_num_holes, double nozzle_hole_d,
    double nozzle_chamfer)
{
    double r_outer = d_in_shell / 2.0 + shell_thickness;
    double r_cap = r_outer + flange_height;

    MbPlacement3D place;

    SPtr<MbArc>     circle(new MbArc(r_cap));
    SPtr<MbContour> contour(new MbContour());
    contour->AddSegment(circle);

    RPArray<MbContour> contours(1, 1);
    contours.push_back(contour);

    SPtr<MbSurface> surface(new MbPlane(place));
    MbSweptData     curvesData(*surface, contours);

    ExtrusionValues extrudeParams;
    extrudeParams.side1.scalarValue = cap_thickness;
    extrudeParams.side1.way = sw_scalarValue;
    extrudeParams.side2.scalarValue = 0.0;
    extrudeParams.side2.way = sw_scalarValue;

    MbSNameMaker         snMaker(ct_CurveExtrusionSolid, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    MbSolid* capSolid = nullptr;
    ::ExtrusionSolid(curvesData, place.Normal(), nullptr, nullptr, false,
        extrudeParams, snMaker, cNames, capSolid);

    if (!capSolid) return nullptr;

    if (hole_count > 0)
    {
        double angle_step = M_PI2 / (double)hole_count;
        RPArray<MbContour> holeContours(hole_count, 1);

        for (int i = 0; i < hole_count; ++i)
        {
            double angle = i * angle_step;
            double hole_r = r_outer + flange_height / 2.0;
            MbArc* hc = new MbArc(MbCartPoint(hole_r * cos(angle), hole_r * sin(angle)), d_hole / 2.0);
            MbContour* cnt = new MbContour();
            cnt->AddSegment(hc);
            holeContours.push_back(cnt);
        }

        MbPlacement3D holePlace(place);
        holePlace.Move(place.Normal() * -1.0);

        SPtr<MbSurface> holeSurf(new MbPlane(holePlace));
        MbSweptData holeData(*holeSurf, holeContours);

        ExtrusionValues holeParams;
        holeParams.side1.scalarValue = cap_thickness + 2.0;
        holeParams.side1.way = sw_scalarValue;

        MbSNameMaker snHoles(ct_CurveExtrusionSolid, MbSNameMaker::i_SideNone, 1);
        MbSolid* holesTool = nullptr;
        ::ExtrusionSolid(holeData, holePlace.Normal(), nullptr, nullptr, false,
            holeParams, snHoles, PArray<MbSNameMaker>(0, 1, false), holesTool);

        if (holesTool)
        {
            MbSNameMaker             bNames(ct_BooleanSolid, MbSNameMaker::i_SideNone, 20);
            MbBooleanOperationParams bParams(bo_Difference, true, bNames);
            SolidSPtr solid1(capSolid);
            SolidSPtr solid2(holesTool);
            SolidSPtr resultBody;
            if (::BooleanResult(solid1, cm_Same, solid2, cm_Same, bParams, resultBody) == rt_Success && resultBody)
            {
                solid1 = nullptr;
                capSolid = resultBody.detach();
            }
            else
            {
                capSolid = solid1.detach();
            }
        }
    }

    if (nozzle_d_in > 0.0)
    {
        double r_hole = r_in / 2.0;
        double z_mid = cap_thickness / 2.0;
        double halfLen = cap_thickness / 2.0 + 1.0;

        MbPlacement3D cylPlace;
        cylPlace.Move(MbVector3D(0.0, r_hole, z_mid));

        MbSNameMaker             snCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 2);
        MbElementarySolidParams  cylParams(snCyl);
        cylParams.InitCylinder(cylPlace, nozzle_d_in / 2.0, halfLen, halfLen);

        MbElementarySolidResults cylResults;
        if (::ElementarySolid(cylParams, cylResults) == rt_Success)
        {
            SolidSPtr holeTool(cylResults.DetachSolid());
            if (holeTool)
            {
                MbSNameMaker             bNames(ct_BooleanSolid, MbSNameMaker::i_SideNone, 21);
                MbBooleanOperationParams bParams(bo_Difference, true, bNames);
                SolidSPtr solid1(capSolid);
                SolidSPtr resultBody;
                if (::BooleanResult(solid1, cm_Same, holeTool, cm_Copy, bParams, resultBody) == rt_Success && resultBody)
                {
                    solid1 = nullptr;
                    capSolid = resultBody.detach();
                }
                else
                {
                    capSolid = solid1.detach();
                }
            }
        }

        MbVector3D    axisX(1.0, 0.0, 0.0);
        MbVector3D    axisY(0.0, 1.0, 0.0);
        MbCartPoint3D nozzleOrigin(0.0, r_hole, 0);

        MbPlacement3D nozzlePlace(axisX, axisY, nozzleOrigin);
        MbSolid* nozzle = CreateNozzle(nozzlePlace,
            nozzle_d_in, nozzle_wall, nozzle_len,
            nozzle_flange_d, nozzle_flange_t,
            nozzle_hole_pcd, nozzle_num_holes, nozzle_hole_d,
            nozzle_chamfer);

        if (nozzle)
        {
            RPArray<MbSolid> parts(2, 1);
            parts.Add(capSolid);
            parts.Add(nozzle);
            MbSolid* united = nullptr;
            MbSNameMaker snUnion(ct_BooleanSolid, MbSNameMaker::i_SideNone, 30);
            ::UnionSolid(parts, cm_Same, true, snUnion, false, united);
            if (united) capSolid = united;
        }
    }

    return capSolid;
}

static MbFace* FindCylindricalFace(MbSolid* solid, double radius, double tol = 1.0)
{
    for (size_t i = 0; i < solid->GetFacesCount(); ++i)
    {
        MbFace* face = solid->GetFace(i);
        if (!face) continue;
        const MbSurface& surf = face->GetSurface().GetSurface();
        if (surf.IsA() == st_CylinderSurface)
        {
            const MbCylinderSurface& cyl = static_cast<const MbCylinderSurface&>(surf);
            if (fabs(cyl.GetRadius() - radius) < tol)
                return face;
        }
    }
    return nullptr;
}

static MbFace* FindPlanarFaceAtZ(MbSolid* solid, double z, double tol = 1.0)
{
    for (size_t i = 0; i < solid->GetFacesCount(); ++i)
    {
        MbFace* face = solid->GetFace(i);
        if (!face) continue;
        const MbSurface& surf = face->GetSurface().GetSurface();
        if (surf.IsA() == st_Plane)
        {
            const MbPlane& plane = static_cast<const MbPlane&>(surf);

            MbVector3D normal;
            plane._Normal(0.0, 0.0, normal);
            if (fabs(fabs(normal.z) - 1.0) > 0.01)
                continue;

            MbCartPoint3D origin;
            plane._PointOn(0.0, 0.0, origin);
            if (fabs(origin.z - z) < tol)
                return face;
        }
    }
    return nullptr;
}

SPtr<MbAssembly> ModelBuilder::AssembleHeatExchanger(
    MbSolid* resultBody,
    MbSolid* gasket1,
    MbSolid* gasket2,
    MbSolid* cover1,
    MbSolid* cover2,
    double d_in_shell,
    double s_tck,
    double channel_width,
    double gasket_length,
    double flange_height)
{
    const double L = channel_width / 2.0 + gasket_length;
    const MbVector3D axX(1, 0, 0);
    const MbVector3D axYp(0, 1, 0);
    const MbVector3D axYm(0, -1, 0);
    SPtr<MbInstance> compBody(
        new MbInstance(*resultBody, MbPlacement3D()));
    SPtr<MbInstance> compGasket1(
        new MbInstance(*gasket1,
            MbPlacement3D(axX, axYp, MbCartPoint3D(0, 0, channel_width / 2))));
    SPtr<MbInstance> compGasket2(
        new MbInstance(*gasket2,
            MbPlacement3D(axX, axYm, MbCartPoint3D(0, 0, -channel_width / 2))));
    SPtr<MbInstance> compCover1(
        new MbInstance(*cover1,
            MbPlacement3D(axX, axYp, MbCartPoint3D(0, 0, L))));
    SPtr<MbInstance> compCover2(
        new MbInstance(*cover2,
            MbPlacement3D(axX, axYm, MbCartPoint3D(0, 0, -L))));
    std::vector<SPtr<MbInstance>> parts;
    parts.push_back(compBody);
    parts.push_back(compGasket1);
    parts.push_back(compGasket2);
    parts.push_back(compCover1);
    parts.push_back(compCover2);

    SPtr<MbAssembly> assm(new MbAssembly(parts));

    {
        const double r_shell_outer = d_in_shell / 2.0 + s_tck;
        const double r_gasket_outer = d_in_shell / 2.0;
        const double r_cover_outer = d_in_shell / 2.0 + s_tck + flange_height;

        MbFace* fBodyCyl = FindCylindricalFace(resultBody, r_shell_outer);

        MbFace* fBodyFlatTop = FindPlanarFaceAtZ(resultBody, L);
        MbFace* fBodyFlatBot = FindPlanarFaceAtZ(resultBody, -L);

        MbFace* fG1CylNear = FindCylindricalFace(gasket1, r_gasket_outer);
        MbFace* fG1FlatNear = FindPlanarFaceAtZ(gasket1, gasket_length);
        MbFace* fG1FlatFar = FindPlanarFaceAtZ(gasket1, 0);

        MbFace* fG2CylNear = FindCylindricalFace(gasket2, r_gasket_outer);
        MbFace* fG2FlatNear = FindPlanarFaceAtZ(gasket2, gasket_length);
        MbFace* fG2FlatFar = FindPlanarFaceAtZ(gasket2, 0);

        MbFace* fCov1Cyl = FindCylindricalFace(cover1, r_cover_outer);
        MbFace* fCov1Flat = FindPlanarFaceAtZ(cover1, 0.0);

        MbFace* fCov2Cyl = FindCylindricalFace(cover2, r_cover_outer);
        MbFace* fCov2Flat = FindPlanarFaceAtZ(cover2, 0.0);

        if (fBodyCyl && fG1CylNear) {
            MtGeomArgument argA(fBodyCyl, compBody);
            MtGeomArgument argB(fG1CylNear, compGasket1);
            assm->AddConstraint(GCM_CONCENTRIC, argA, argB);
        }
        if (fBodyFlatTop && fG1FlatNear) {
            MtGeomArgument argA(fBodyFlatTop, compBody);
            MtGeomArgument argB(fG1FlatNear, compGasket1);
            assm->AddConstraint(GCM_DISTANCE, argA, argB, 0);
        }

        if (fBodyCyl && fG2CylNear) {
            MtGeomArgument argA(fBodyCyl, compBody);
            MtGeomArgument argB(fG2CylNear, compGasket2);
            assm->AddConstraint(GCM_CONCENTRIC, argA, argB);
        }
        if (fBodyFlatBot && fG2FlatNear) {
            MtGeomArgument argA(fBodyFlatBot, compBody);
            MtGeomArgument argB(fG2FlatNear, compGasket2);
            assm->AddConstraint(GCM_DISTANCE, argA, argB, 0.0);
        }

        if (fG1FlatFar && fCov1Cyl) {
            MtGeomArgument argA(fG1CylNear, compGasket1);
            MtGeomArgument argB(fCov1Cyl, compCover1);
            assm->AddConstraint(GCM_CONCENTRIC, argA, argB);
        }
        if (fG1FlatFar && fCov1Flat) {
            MtGeomArgument argA(fG1FlatNear, compGasket1);
            MtGeomArgument argB(fCov1Flat, compCover1);
            assm->AddConstraint(GCM_DISTANCE, argA, argB, 0.0);
        }

        if (fG2FlatFar && fCov2Cyl) {
            MtGeomArgument argA(fG2CylNear, compGasket2);
            MtGeomArgument argB(fCov2Cyl, compCover2);
            assm->AddConstraint(GCM_CONCENTRIC, argA, argB);
        }
        if (fG2FlatNear && fCov2Flat) {
            MtGeomArgument argA(fG2FlatNear, compGasket2);
            MtGeomArgument argB(fCov2Flat, compCover2);
            assm->AddConstraint(GCM_DISTANCE, argA, argB, 0.0);
        }
    }

    assm->EvaluateConstraints();
    compBody->AddAttribute(MbProductInfo(false, " ", "Корпус", " "));
    compGasket1->AddAttribute(MbProductInfo(false, " ", "Прокладка", " "));
    compGasket2->AddAttribute(MbProductInfo(false, " ", "Прокладка", " "));
    compCover1->AddAttribute(MbProductInfo(false, " ", "Крышка", " "));
    compCover2->AddAttribute(MbProductInfo(false, " ", "Крышка", " "));
    assm->AddAttribute(MbProductInfo(false, " ", "Спиральный теплообменник", " "));

    return assm;
}