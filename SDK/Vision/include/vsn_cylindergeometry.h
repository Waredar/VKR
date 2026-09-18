////////////////////////////////////////////////////////////////////////////////
/**
\file
   \brief \ru Класс CylinderGeometry представляет геометрию в виде цилиндра.
          \en CylinderGeometry class presents geometry as a cylinder. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_CYLINDERGEOMETRY_H
#define __VSN_CYLINDERGEOMETRY_H

#include <vsn_meshgeometry.h>

namespace VSN {

class CylinderGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс CylinderGeometry представляет геометрию в виде цилиндра.
           \en CylinderGeometry class presents geometry as a cylinder. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS CylinderGeometry : public MeshGeometry
{
    VSN_OBJECT(CylinderGeometry);
    VSN_PROP_READ_WRITE(polyStep, GetSpaceStep, SetSpaceStep);
    VSN_PROP_READ_WRITE_NOTIFY(radius, GetRadius, SetRadius, OnRadiusModified);
    VSN_PROP_READ_WRITE_NOTIFY(height, GetHeight, SetHeight, OnHeightModified);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    CylinderGeometry(Node* pParent = nullptr);
    /// \ru Конструктор по радиусу, высоте и направлению оси Z. \en Constructor by radius, height and Z-axis direction. \~
    CylinderGeometry(float radius, float height, int sag = 60, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~CylinderGeometry();
public:
    /// \ru Вернуть высоту цилиндра. \en Returns cylinder height. \~
    float GetHeight() const;
    /// \ru Вернуть радиус цилиндра. \en Returns cylinder radius. \~
    float GetRadius() const;
    /// \ru Вернуть шаг полигона. \en Returns polygon step. \~
    int GetSpaceStep() const;
    /// \ru Задать шаг полигона (должен быть больше нуля). \en Sets polygon step that must be greater than zero. \~
    void SetSpaceStep(int polyStep);

    /// \ru Определить, замкнут ли цилиндр. \en Defines if cylinder is closed. \~
    bool IsClosed() const;
    /// \ru Установить флаг замкнутости цилиндра. \en Sets flag of cylinder closure. \~
    void SetClose(bool clouse);
public:
    /// \ru Задать радиус цилиндра. \en Sets cylinder radius. \~
    VSN_SLOT(Public, SetRadius, void SetRadius(float radius))
    /// \ru Задать высоту цилиндра. \en Sets cylinder height. \~
    VSN_SLOT(Public, SetHeight, void SetHeight(float height))
public:
    /// \ru Этот синал будет сгенерирован при изменении радиуса цилиндра. \en The signal will be generated when modifying cylinder radius. \~
    VSN_SIGNAL(Public, OnRadiusModified, void OnRadiusModified(float radius), radius)
    /// \ru Этот синал будет сгенерирован при изменении высоты цилиндра. \en The signal will be generated when modifying cylinder height. \~
    VSN_SIGNAL(Public, OnHeightModified, void OnHeightModified(float height), height)
public:
    /// \ru Вернуть габаритный куб. \en Returns bounding box. \~
    virtual const BoundingBox& GetBoundingBox() const override;
    /// \ru Обновить геометрию по новым данным. \en Updates geometry by new data. \~
    virtual void UpdateGeometry() override;
private:
    /// \ru Отрисовать сферу с помощью OpenGL. \en Renders sphere with OpenGL. \~
    virtual void OpenGLDraw(const RenderState& state) override;
private:
    VSN_DISABLE_COPY(CylinderGeometry);
    VSN_DECLARE_EX_PRIVATE(CylinderGeometry);
};

} // namespace VSN

#endif /* __VSN_CYLINDERGEOMETRY_H */
