////////////////////////////////////////////////////////////////////////////////
/**
\file
  \brief \ru Класс BoxRep является вспомогательным классом и представляет API 
             для управления геометрией BoxGeometry.
         \en BoxRep class is an auxiliary class and presents API to control
             BoxGeometry geometry. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_BOXREP_H
#define __VSN_BOXREP_H

#include <vsn_geometryrep.h>

namespace VSN {
//------------------------------------------------------------------------------
/** \brief \ru Класс BoxRep является вспомогательным классом и представляет API 
               для управления геометрией BoxGeometry.
           \en BoxRep class is an auxiliary class and presents API to control
               BoxGeometry geometry. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS BoxRep : public GeometryRep
{
    VSN_OBJECT(BoxRep);
    VSN_PROP_READ_WRITE_NOTIFY(width,  GetWidth,  SetWidth,  OnWidthModified);
    VSN_PROP_READ_WRITE_NOTIFY(length, GetLength, SetLength, OnLengthModified);
    VSN_PROP_READ_WRITE_NOTIFY(height, GetHeight, SetHeight, OnHeightModified);
public:
    explicit BoxRep(Node* pParent = nullptr);
    virtual ~BoxRep();
public:
    /// \ru Вернуть ширину параллелепипеда. \en Returns box width.
    float GetWidth() const;
    /// \ru Вернуть длину параллелепипеда. \en Returns box length.
    float GetLength() const;
    /// \ru Вернуть высоту параллелепипеда. \en Returns box height.
    float GetHeight() const;
public:
    /// \ru Задать ширину параллелепипеда. \en Sets box width.
    VSN_SLOT(Public, SetWidth, void SetWidth(float width))
    /// \ru Задать длину параллелепипеда. \en Sets box length.
    VSN_SLOT(Public, SetLength, void SetLength(float length))
    /// \ru Задать высоту параллелепипеда. \en Sets box height.
    VSN_SLOT(Public, SetHeight, void SetHeight(float height))
public:
    /// \ru Модификация ширины параллелепипеда. \en Modifies box width.
    VSN_SIGNAL(Public, OnWidthModified,  void OnWidthModified(float width), width)
    /// \ru Модификация длины параллелепипеда. \en Modifies box length.
    VSN_SIGNAL(Public, OnLengthModified, void OnLengthModified(float length), length)
    /// \ru Модификация высоты параллелепипеда. \en Modifies box height.
    VSN_SIGNAL(Public, OnHeightModified, void OnHeightModified(float height), height)
private:
    VSN_DISABLE_COPY(BoxRep);
};

} // namespace VSN

#endif /* __VSN_BOXREP_H */

