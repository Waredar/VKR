////////////////////////////////////////////////////////////////////////////////
/**
\file
  \brief \ru Класс ConeRep является вспомогательным классом и представляет API 
             для управления геометрией ConeGeometry.
         \en ConeRep class is an auxiliary class and presents API to control
             ConeGeometry geometry. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_CONEREP_H
#define __VSN_CONEREP_H

#include <vsn_geometryrep.h>

namespace VSN {

//------------------------------------------------------------------------------
/** \brief \ru Класс ConeRep является вспомогательным классом и представляет API
               для управления геометрией ConeGeometry. 
           \en ConeRep class is an auxiliary class and presents API to control
               ConeGeometry geometry. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS ConeRep : public GeometryRep
{
    VSN_OBJECT(ConeRep);
    VSN_PROP_READ_WRITE(polyStep, GetPolygonStep, SetPolygonStep);
    VSN_PROP_READ_WRITE_NOTIFY(radius, GetRadius, SetRadius, OnRadiusModified);
    VSN_PROP_READ_WRITE_NOTIFY(height, GetHeight, SetHeight, OnHeightModified);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit ConeRep(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~ConeRep();
public:
    /// \ru Вернуть высоту конуса. \en Returns cone height. \~
    float GetHeight() const;
    /// \ru Вернуть радиус конуса. \en Returns cone radius. \~
    float GetRadius() const;
    /// \ru Вернуть шаг полигона. \en Returns polygon step. \~
    int GetPolygonStep() const;
    /// \ru Задать шаг полигона (должен быть больше нуля). \en Sets polygon step that must be greater than zero. \~
    void SetPolygonStep(int polyStep);
public:
    /// \ru Задать радиус конуса (должен быть больше нуля). \en Sets cone radius that must be greater than zero. \~
    VSN_SLOT(Public, SetRadius, void SetRadius(float radius))
    /// \ru Задать высоту конуса (должна быть больше нуля). \en Sets cone height that must be greater than zero. \~
    VSN_SLOT(Public, SetHeight, void SetHeight(float height))
public:
    VSN_SIGNAL(Public, OnRadiusModified, void OnRadiusModified(float radius), radius)
    VSN_SIGNAL(Public, OnHeightModified, void OnHeightModified(float height), height)
private:
    VSN_DISABLE_COPY(ConeRep);
};

} // namespace VSN

#endif /* __VSN_CONEREP_H */

