////////////////////////////////////////////////////////////////////////////////
/**
\file
\brief \ru Класс TriadRep служит для построения геометрии трех осей.
       \en TriadRep class used for building a geometry of three axes. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_TRIADREP_H
#define __VSN_TRIADREP_H

#include <vsn_geometryrep.h>

namespace VSN {

namespace Experiment
{

class TriadRepPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс TriadRep представляет геометрию трех осей.
           \en TriadRep class presents geometry as a three axis. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS TriadRep : public GeometryRep
{
    VSN_OBJECT(TriadRep)
public:
    enum TriadStyle
    {
        Flat,
        Volume
    };
    enum Orientation
    {
        Left,
        Right
    };
    enum TriadElement
    {
        AxisX = (1 << 0),
        AxisY = (1 << 1),
        AxisZ = (1 << 2),
        OriginBall = (1 << 3),
        Axises = (AxisX | AxisY | AxisZ),
        AllAxises = (Axises),
        All = (Axises | OriginBall)
    };
    VSN_DECLARE_FLAGS(TriadElements, TriadElement)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    TriadRep(TriadStyle style = Flat, TriadElements elementsMask = All, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~TriadRep();
public:
    /// \ru Получить тип осей. \en NO TRANSLATION \~
    TriadStyle GetTriadStyle() const;
    /// \ru Задать тип осей. \en NO TRANSLATION \~
    void SetTriadStyle(TriadStyle style);

    /// \ru Получить составляющие элементы. \en NO TRANSLATION \~
    TriadElements GetTriadElements() const;
    /// \ru Выбрать составляющие элементы. \en NO TRANSLATION \~
    void SetTriadElements(TriadElements elementsMask);

    /// \ru Получить цвет элемента. \en NO TRANSLATION \~
    Color GetElementColor(TriadElement element) const;
    /// \ru Задать цвет элементов. \en NO TRANSLATION \~
    void SetElementsColor(TriadElements elementsMask, Color color);

    /// \ru Получить длину оси. \en NO TRANSLATION \~
    float GetAxisLineLength(TriadElement axis = AxisX) const;
    /// \ru Получить радиус оси. \en NO TRANSLATION \~
    float GetAxisLineRadius(TriadElement axis = AxisX) const;
    /// \ru Получить высоту наконечника оси. \en NO TRANSLATION \~
    float GetAxisHeadLength(TriadElement axis = AxisX) const;
    /// \ru Получить радиус наконечника оси. \en NO TRANSLATION \~
    float GetAxisHeadRadius(TriadElement axis = AxisX) const;
    /// \ru Получить радиус маркера начала координат. \en NO TRANSLATION \~
    float GetOriginBallRadius() const;

    /// \ru Задать длины осей. \en NO TRANSLATION \~
    void SetAxisesLineLength(float length, TriadElements axises = AllAxises);
    /// \ru Задать радиусы осей. \en NO TRANSLATION \~
    void SetAxisesLineRadius(float radius, TriadElements axises = AllAxises);
    /// \ru Задать высоты наконечников осей. \en NO TRANSLATION \~
    void SetAxisesHeadLength(float length, TriadElements axises = AllAxises);
    /// \ru Задать радиусы наконечников осей. \en NO TRANSLATION \~
    void SetAxisesHeadRadius(float radius, TriadElements axises = AllAxises);
    /// \ru Задать радиус маркера начала координат. \en NO TRANSLATION \~
    void SetOriginBallRadius(float radius);

    /// \ru Получить маску видимости подписей осей. \en NO TRANSLATION \~
    TriadElements GetVisibleAxisLabels() const;
    /// \ru Получить масштаб надписи оси. \en NO TRANSLATION \~
    float GetAxisLabelScale(TriadElement axis = AxisX) const;
    /// \ru Задать видимость подписей осей. \en NO TRANSLATION \~
    void SetVisibleAxisLabels(TriadElements axises);
    /// \ru Задать масштаб надписей осей. \en NO TRANSLATION \~
    void SetAxisLabelsScale(float scale, TriadElements axises = AllAxises);

    /// \ru Получить ориентацию системы координат. \en NO TRANSLATION \~
    Orientation GetOrientation() const;
    /// \ru Задать ориентацию системы координат. \en NO TRANSLATION \~
    void SetOrientation(Orientation orientation);

    /// \ru Получить масштабный коэффициент системы координат. \en NO TRANSLATION \~
    float GetScale() const;
    /// \ru Задать масштабный коэффициент системы координат. \en NO TRANSLATION \~
    void SetScale(float scale);
public: // signals
    /// \ru Сигнал будет генерирован при изменении габарита сегмента. \en Signal will be generated when modifying segment size. \~
    VSN_SIGNAL(Public, OnGeometryModified, void OnGeometryModified())
private:
    VSN_DISABLE_COPY(TriadRep);
    VSN_DECLARE_EX_PRIVATE(TriadRep);
};

} //namespace Experiment

} // namespace VSN

#endif //__VSN_TRIADREP_H
