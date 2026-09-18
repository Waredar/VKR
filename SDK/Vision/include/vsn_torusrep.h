////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс TorusRep является вспомогательным классом и представляет API
               для управления геометрией TorusGeometry.
    \en TorusRep class is an auxiliary class and presents API to control
        TorusGeometry geometry. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_TORUSREP_H
#define __VSN_TORUSREP_H

#include <vsn_geometryrep.h>

namespace VSN {

//------------------------------------------------------------------------------
/** \brief \ru Класс TorusRep является вспомогательным классом и представляет API
            для управления геометрией TorusGeometry.
           \en TorusRep class is an auxiliary class and presents API to control
               TorusGeometry geometry. \~
    \ingroup Vision_Geometry
*/
class VSN_CLASS TorusRep : public GeometryRep
{
    VSN_OBJECT(TorusRep)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit TorusRep(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~TorusRep();
public:
    /// \ru Вернуть радиус тора. \en Returns torus radius.
    float GetMajorRadius() const;
    /// \ru Вернуть радиус трубки тора. \en Returns torus tube radius.
    float GetMinorRadius() const;
    /// \ru Вернуть шаг колец тора. \en Returns rings step.
    int GetRingStep() const;
    /// \ru Вернуть шаг колец тора. \en Returns slices step.
    int GetSliceStep() const;
    /// \ru Задать количество колец тора (должно быть больше нуля). \en Sets rings step that must be greater than zero.
    void SetRingStep(int ringStep);
    /// \ru Задать количество сегментов тора (должно быть больше нуля). \en Sets slices step that must be greater than zero.
    void SetSliceStep(int sliceStep);
public:
    /// \ru Задать радиус тора (должен быть больше нуля). \en Sets torus radius that must be greater than zero.
    VSN_SLOT(Public, SetMajorRadius, void SetMajorRadius(float radius))
    /// \ru Задать радиус трубки тора (должна быть больше нуля). \en Sets torus tube radius that must be greater than zero.
    VSN_SLOT(Public, SetMinorRadius, void SetMinorRadius(float radius))
public:
    /// \ru Этот синал будет сгенерирован при изменении радиуса тора. \en The signal will be generated when modifying torus radius. \~
    VSN_SIGNAL(Public, OnMajorRadiusModified, void OnMajorRadiusModified(float radius), radius)
    /// \ru Этот синал будет сгенерирован при изменении радиуса трубки тора. \en The signal will be generated when modifying torus tube radius. \~
    VSN_SIGNAL(Public, OnMinorRadiusModified, void OnMinorRadiusModified(float radius), radius)
private:
    VSN_DISABLE_COPY(TorusRep);
};

} // namespace VSN

#endif /* __VSN_TORUSREP_H */
