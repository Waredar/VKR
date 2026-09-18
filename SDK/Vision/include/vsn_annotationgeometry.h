////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru AnnotationGeometry является родительским классом геометрии, от которого наследуются 
             геометрические проедставления, такие как размеры, label, и.д.
         \en AnnotationGeometry class is a parent geometry class that is inherited by 
             such geometric representations as sizes, lables, etc. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_ANNOTATIONGEOMETRY_H
#define __VSN_ANNOTATIONGEOMETRY_H

#include <vsn_meshgeometry.h>
#include <vsn_global.h>

namespace VSN {
class AnnotationGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru AnnotationGeometry является родительским классом геометрии, от которого наследуются 
               геометрические представления, такие как размеры, label, и.д.
           \en AnnotationGeometry class is a parent geometry class that is inherited by 
               such geometric representations as sizes, lables, etc. \~
  \details \ru AnnotationGeometry обеспечивает однородный доступ к базовому функционалу и 
               имеет функцию проверки аннотативных объектов. \n.
           \en AnnotationGeometry class provides a uniform access to the basic functional, 
               and has a function to check annotative objects. \n \~
  \ingroup NO GROUP
*/
// ---
class VSN_CLASS AnnotationGeometry : public MeshGeometry
{
    VSN_OBJECT(AnnotationGeometry)
public:
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~AnnotationGeometry() override;
public:
    /// \ru Проверить, является ли геометрия аннотативной. \en Checks if geometry is annotative. \~
    bool IsAnnotation() const override;
protected:
    /// \ru Конструктор для внутреннего использования. \en Constructor for inner use.
    AnnotationGeometry(AnnotationGeometryPrivate& dd, Node* pParent = nullptr);
    VSN_DECLARE_EX_PRIVATE(AnnotationGeometry)
};

} // namespace VSN

#endif /* __VSN_ANNOTATIONGEOMETRY_H */
