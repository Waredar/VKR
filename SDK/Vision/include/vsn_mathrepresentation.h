////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс MathRepresentation является вспомогательным классом и представляет 
             API для управления геометрией.
         \en MathRepresentation class is an auxiliary class and represents API to control geometry. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_MATHREPRESENTATION_H
#define __VSN_MATHREPRESENTATION_H

#include <vsn_mathgeometry.h>
#include <vsn_geometryrep.h>
#include <vsn_global.h>

class MbItem;

namespace VSN {

class MathRepresentationPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс MathRepresentation является вспомогательным классом и представляет API для управления геометрией.
           \en MathRepresentation class is an auxiliary class and represents API to control geometry. \~
  \details \ru MathRepresentation создает MathGeometry и содержит его указатель на протяжение всей своей жизни.
               MathRepresentation представляет ряд полезных функций для управления своей геометрией. \n.
           \en MathRepresentation class creates MathGeometry and contains its pointer during its whole existing.
               MathRepresentation class presents a set of useful functions to control its geometry. \n \~
  \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS MathRepresentation : public GeometryRep
{
    VSN_OBJECT(MathRepresentation);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit MathRepresentation(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor.
    ~MathRepresentation() override;
public:
    /// \ru Вернуть значение флага отображать вершины. \en Returns flag value of the vertices displaying. \~
    bool IsVerticesDisplaying() const;
    /// \ru Установить значение флага отображать вершины. \en Set flag value to vertices displaying. \~
    void SetVerticesDisplaying(bool bDisplay);

    /// \ru Вернуть размер отображения вершин. \en Returns vertex display size. \~
    float GetSizeVertices() const;
    /// \ru Установить размер отображения вершин. \en Set vertex display size. \~
    void SetSizeVertices(float size);

    /// \ru Получить тип построения сетки. \en Get a build type. \~
    CommandType GetBuildType() const;
    /// \ru Задать тип построения сетки. \en Change a build type. \~
    void SetBuildType(CommandType type);

    /// \ru Вернуть точность для вычисления шага при триангуляции поверхностей и граней. \en Returns accuracy to calculate step when triangulating surfaces and faces. \~
    double GetVisualSag() const;
    /// \ru Установить точность для вычисления шага при триангуляции поверхностей и граней. \en Returns accuracy to calculate step when triangulating surfaces and faces. \~
    void SetVisualSag(double sag, bool bRebuildMesh);

    /// \ru Вернуть  указатель на математическое точное представление MbItem. \en Returns a pointer to math precise representation of MbItem. \~
    const MbItem* GetMathItem() const;
    /// \ru Установить указатель на математическое точное представление MbItem. \en Sets a pointer to math precise representation of MbItem. \~
    void SetMathItem(const MbItem* pItem, double sag = Math::visualSag);
    /// \ru Перестроить геометрию по измененному MbItem. \en Rebuild geometry by modified MbItem. \~
    void RebuildGeometry();
private:
    VSN_DECLARE_EX_PRIVATE(MathRepresentation);
};

} // namespace VSN

#endif /* __VSN_MATHREPRESENTATION_H */
