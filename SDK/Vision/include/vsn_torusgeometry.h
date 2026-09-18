////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс TorusGeometry представляет геометрию в виде тора.
           \en TorusGeometry class presents geometry as a torus. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_TORUSGEOMETRY_H
#define __VSN_TORUSGEOMETRY_H

#include <vsn_meshgeometry.h>

namespace VSN {

class TorusGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс TorusGeometry представляет геометрию в виде тора.
           \en TorusGeometry class presents geometry as a torus. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS TorusGeometry : public MeshGeometry
{
    VSN_OBJECT(TorusGeometry);

public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    TorusGeometry(Node* pParent = nullptr);
    /// \ru Конструктор по радиусу тора, радиусу трубки тора по направлению оси Z. \en Constructor by radius of torus, radius of torus tube by Z-axis direction. \~
    TorusGeometry(float majorRadius, float minorRadius, float angle1 = 0.0f, float angle2 = M_PI2, int rings = 10, int slices = 10, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~TorusGeometry();
public:
    /// \ru Вернуть радиус тора. \en Returns torus radius. \~
    float GetMajorRadius() const;
    /// \ru Вернуть радиус трубки тора. \en Returns torus tube radius. \~
    float GetMinorRadius() const;
    /// \ru Вернуть шаг колец тора. \en Returns rings step. \~
    int GetRingStep() const;
    /// \ru Вернуть шаг сегментов тора. \en Returns slices step. \~
    int GetSliceStep() const;
    /// \ru Вернуть угол начала тора. \en Return the angle of the beginning of the torus.\~
    float GetAngle1() const;
    /// \ru Вернуть угол конца тора. \en Return the angle of the end of the torus.\~
    float GetAngle2() const;

    /// \ru Задать шаг колец тора (должен быть больше нуля). \en Sets rings step that must be greater than zero. \~
    void SetRingStep(int ringStep);
    /// \ru Задать шаг сегментов тора (должен быть больше нуля). \en Sets slices step that must be greater than zero. \~
    void SetSliceStep(int sliceStep);
    /// \ru Задать угол начала тора. \en Sets the angle of the beginning of the torus.\~
    void SetAngle1(float angle);
    /// \ru Задать угол конца тора. \en Sets the angle of the end of the torus.\~
    void SetAngle2(float angle);
public:
    /// \ru Задать радиус цилиндра. \en Sets cylinder radius. \~
    VSN_SLOT(Public, SetMajorRadius, void SetMajorRadius(float radius))
    /// \ru Задать высоту цилиндра. \en Sets cylinder height. \~
    VSN_SLOT(Public, SetMinorRadius, void SetMinorRadius(float radius))
public:
    /// \ru Этот синал будет сгенерирован при изменении радиуса тора. \en The signal will be generated when modifying torus radius. \~
    VSN_SIGNAL(Public, OnMajorRadiusModified, void OnMajorRadiusModified(float radius), radius)
    /// \ru Этот синал будет сгенерирован при изменении радиуса трубки тора. \en The signal will be generated when modifying torus tube radius. \~
    VSN_SIGNAL(Public, OnMinorRadiusModified, void OnMinorRadiusModified(float radius), radius)
public:
    /// \ru Вернуть габаритный куб. \en Returns bounding box. \~
    virtual const BoundingBox& GetBoundingBox() const override;
    /// \ru Обновить геометрию по новым данным. \en Updates geometry by new data. \~
    virtual void UpdateGeometry() override;
private:
    /// \ru Отрисовать сферу с помощью OpenGL. \en Renders sphere with OpenGL. \~
    virtual void OpenGLDraw(const RenderState& state) override;
private:
    VSN_DISABLE_COPY(TorusGeometry);
    VSN_DECLARE_EX_PRIVATE(TorusGeometry);
};

} // namespace VSN

#endif /* __VSN_TORUSGEOMETRY_H */
