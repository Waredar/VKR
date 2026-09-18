///////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Визуальные свойства материала с трафаретом.
         \en Visual properties of the stencil material. \~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PATTERNMATERIAL_H
#define __VSN_PATTERNMATERIAL_H

#include <vsn_material.h>

namespace VSN {

class PatternMaterialPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Визуальные свойства материала с трафаретом.
           \en Visual properties of the stencil material. \~
    \details \ru Класс PatternMaterial позволяет задавать визуальные параметры материала с трафаретом. \n.
             \en Material class allows setting visual parameters of the stencil material. \n \~
*/
// ---
class VSN_CLASS PatternMaterial : public Material
{
public:
    /// \ru Встроенные паттерны. \en Built-in patterns.
    enum Pattern
    {
        VerticalLines,
        HorizontalLines,
        Chess,
        Points,
        PointsInverted
    };
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    PatternMaterial(Pattern pattern = Points, int size = 1);
    /**
    \brief \ru Конструктор по диффузному цвету. \en Constructor by diffuse color. \~
        \details \ru Конструктор задает диффузный цвет; цвет фона по умолчанию темно-серый.
                 \en The constructor sets diffuse color; the default ambient color is dark grey.
    */
    PatternMaterial(const Color& color, Pattern pattern = Points, int size = 1);
    /// \ru Деструктор. \en Destructor.
    virtual ~PatternMaterial();
public:
    /// \ru Выполнить инициализацию материала для отрисовки. \en Initializes material for rendering.
    virtual void glPerform(FaceSide faceSide = FaceSide::FrontAndBack);
    /// \ru Освободить материал. \en Release the material.
    virtual void Release();
public:
    /// \ru Оператор присвоения. \en Assignment operator.
    PatternMaterial& operator = (const PatternMaterial& mat);
    /// \ru Вернуть true, если материал эквивалентен. \en True if material is equivalent.
    bool operator == (const PatternMaterial&) const;
public:
    /// \ru Вернуть текущий паттерн. \en Return current pattern.
    const Pattern GetPattern() const;
    /// \ru Вернуть текущий размер паттерна. \en Return current pattern size.
    int GetPatternSize() const;
    /// \ru Задать паттерн. \en Set current pattern.
    void SetPattern(Pattern pattern, int size = 1);
private:
    VSN_DECLARE_PRIVATE(PatternMaterial)
};

} // namespace VSN

#endif /* __VSN_PATTERNMATERIAL_H */
