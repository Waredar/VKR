////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс GeometryFactory представляет фабрику представлений геометрических
             объектов, а также генерацию готовой сцены для последующей отрисовки.
         \en GeometryFactory class presents a factory of geometric object representations,
             and also generates the prepared scene for the next rendering. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_GEOMERTYFACTORY_H
#define __VSN_GEOMERTYFACTORY_H

#include <mb_placement3d.h>
#include <mb_variables.h>

#include <vsn_boxrep.h>
#include <vsn_sketch.h>
#include <vsn_conerep.h>
#include <vsn_torusrep.h>
#include <vsn_sphererep.h>
#include <vsn_commentrep.h>
#include <vsn_cylinderrep.h>
#include <vsn_rectanglerep.h>
#include <vsn_labelgeometry.h>
#include <vsn_angledimensionrep.h>
#include <vsn_lineardimensionrep.h>
#include <vsn_mathrepresentation.h>
#include <vsn_radialdimensionrep.h>
#include <vsn_diameterdimensionrep.h>

#include <vsn_triadrep.h>
#include <vsn_namespace.h>
#include <vsn_global.h>

class MbItem;
class MbPlaneInstance;

namespace VSN {

class SceneSegment;
//------------------------------------------------------------------------------
/** \brief \ru Класс GeometryFactory представляет фабрику представлений геометрических
               объектов, а также генерацию готовой сцены для последующей отрисовки.
           \en GeometryFactory class presents a factory of geometric object representations and
               also generates the prepared scene for the next rendering. \~
  \details \ru GeometryFactory имеет две группы функций. Первая группа работает непосредственно с математическими
               объектами и тем самым обеспечивает глубокую интеграцию с математическим ядром. Вторая группа
               генерирует представления простых объектов, таких как куб, цилиндр, сфера и др., т.е. где 
               полигональная модель рассчитывается не с помощью математического ядра, а самими визуальными
               объектами. \n.
           \en GeometryFactory class has two function groups. The first one directly operates with math objects
               providing a deep integration with the math kernel. The second one generates representations
               of such simple objects as cube, cylinder, sphere, etc., i.e. a polygonal model is computed
               with not a math kernel, but with visual objects themselves. \n \~
    \ingroup Vision_Node
*/
// ---
class VSN_CLASS GeometryFactory
{
public:
    /// \ru Получить экземпляр фабрики. \en Returns the factory instance. \~
    static GeometryFactory* Instance();
    /// \ru Деструктор. \en Destructor. \~ 
    ~GeometryFactory();
protected:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit GeometryFactory();
public: /// \ru Группа функций, работающая с математическим ядром. \en Group functions operating with the math kernel. \~
    /// \ru Получить графическое представление от MbItem. \en Returns the graphic representation using MbItem. \~
    GeometryRep* CreateMathRep(const MbItem* pItem, CommandType buildType = CommandType::Threaded,  double sag = Math::visualSag);
    /// \ru Создать графическое представление эскиза. \en Returns the graphic representation of sketch. \~
    MathSketch* CreateMathSketch(MbPlaneInstance* instance, SceneSegment* pParent = nullptr);
public: /// \ru Группа функций, генерирующая простые представления вручную. \en Function group generates simple representations manually. \~
    /// \ru Создать представление сферы. \en Creates a sphere representation. \~
    SphereRep* CreateSphere(float radius, float deviation = 60.0f, Node* pParent = nullptr) const;
    /// \ru Создать представление конуса. \en Creates a cone representation. \~
    ConeRep* CreateCone(float radius, float height, Node* pParent = nullptr) const;
    /// \ru Создать представление цилиндра. \en Creates a cylinder representation. \~
    CylinderRep* CreateCylinder(float radius, float height, Node* pParent = nullptr) const;
    /// \ru Создать представление тора. \en Creates a torus representation. \~
    TorusRep* CreateTorus(float majorRadius, float minorRadius, Node* pParent = nullptr) const;
    /// \ru Создать представление параллелепипеда. \en Creates a parallelepiped representation. \~
    BoxRep* CreateBox(float width, float length, float height, Node* pParent = nullptr) const;
    /// \ru Создать представление прямоугольника. \en Creates a rectangle representation. \~
    RectangleRep* CreateRectangle(float width, float height, Node* pParent = nullptr) const;
    /// \ru Создать линейный размер. \en Creates a linear size. \~
    LinearDimensionRep* CreateLinearDimension(Node* pParent = nullptr) const;
    /// \ru Создать угловой размер. \en Creates an angle size. \~
    AngleDimensionRep* CreateAngleDimension(Node* pParent = nullptr) const;
    /// \ru Создать комментарий. \en Creates a comment. \~
    CommentRep * CreateComment(const std::wstring& text, Node* pParent = nullptr) const;
    /// \ru Создать диаметральный размер. \en Creates a diameter size. \~
    DiameterDimensionRep* CreateDiameterDimension(Node* pParent = nullptr) const;
    /// \ru Создать радиальный размер. \en Creates a radial size. \~
    RadialDimensionRep*  CreateRadialDimension(Node* pParent = nullptr) const;
    /// \ru Создать оси системы координат. \en Creates axes of the coordinate system. \~
    Experiment::TriadRep* CreateTriad(Experiment::TriadRep::TriadStyle style = Experiment::TriadRep::Flat, Experiment::TriadRep::TriadElements elementsMask = Experiment::TriadRep::All, Node* pParent = nullptr) const;
    /// \ru Создать текст. \en Creates a text.
    LabelGeometry* CreateText(const WString& text, int fontSize = 10, const MbPlacement3D& placement = {}) const;
private:
    VSN_DISABLE_COPY(GeometryFactory);
    friend class MathRepresentation;
};

} // namespace VSN

#endif /* __VSN_GEOMERTYFACTORY_H */
