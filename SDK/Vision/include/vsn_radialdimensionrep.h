////////////////////////////////////////////////////////////////////////////////
/**
\file
  \brief \ru Класс RadialDimensionRep является вспомогательным классом и представляет API 
             для управления геометрией RadialDimensionGeometry.
         \en RadialDimensionRep class is an auxiliary class and presents API to control
             RadialDimensionGeometry geometry. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_RADIALDIMENSIONREP_H
#define __VSN_RADIALDIMENSIONREP_H

#include <cur_arc3d.h>
#include <vsn_dimensionrep.h>

namespace VSN {

//------------------------------------------------------------------------------
/** \brief \ru Класс RadialDimensionRep является вспомогательным классом и представляет API 
               для управления геометрией RadialDimensionGeometry.
           \en RadialDimensionRep class is an auxiliary class and presents API to control
               RadialDimensionGeometry geometry. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS RadialDimensionRep : public DimensionRep
{
    VSN_OBJECT(RadialDimensionRep)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    explicit RadialDimensionRep(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. 
    virtual ~RadialDimensionRep();
public:
    /// \ru Определить диаметральный размер для измерения. \en Defines diametrical size to measure. \~
    void SetMeasuredGeometry(const MbArc3D& circle);
    /// \ru Установить позицию текста 2D - размера. \en Sets position of 2D size text. \~
    void SetTextPosition(const MbCartPoint3D& textPos);
private:
    VSN_DISABLE_COPY(RadialDimensionRep)
};

} // namespace VSN

#endif /* __VSN_RADIALDIMENSIONREP_H */
