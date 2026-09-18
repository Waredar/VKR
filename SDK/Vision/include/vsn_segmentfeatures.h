////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Функции узла сцены.
           \en Scene segment features. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_SEGMENTFEATURES_H
#define __VSN_SEGMENTFEATURES_H

#include <vsn_feature.h>

namespace VSN {

typedef uint64 SectionPlaneId;

namespace Features
{
    class ScreenPlaneOnlyPrivate;
    //------------------------------------------------------------------------------
    /** \brief  \ru Экранная ориентация сегмента сцены.
                \en Screen only orientation. \~

        \details \ru Модификатор который доворачивает сегмент до экранных координат(XY).\n
                 \en The Feature that rotate the scene segment to the screen orientation(XY). \~

        \ingroup Features
    */
    // ---
    class VSN_CLASS ScreenPlaneOnly : public Feature
    {
    public:
        ScreenPlaneOnly(Node* pParent = nullptr);
        ~ScreenPlaneOnly();
    private:
        VSN_DECLARE_EX_PRIVATE(ScreenPlaneOnly);
    };

    class NoScalablePrivate;
    //------------------------------------------------------------------------------
    /** \brief  \ru Не масштабируемый сегмент сцены.
                \en No scalable segment. \~

        \details \ru Модификатор который делайт узел сцены не масштабируемым.\n
                 \en The Feature that makes scene segment not scalable. \~

        \ingroup Features
    */
    // ---
    class VSN_CLASS NoScalable : public Feature
    {
    public:
        NoScalable(Node* pParent = nullptr);
        ~NoScalable();
    private:
        VSN_DECLARE_EX_PRIVATE(NoScalable);
    };

    class DoubleSidedLightingPrivate;
    //------------------------------------------------------------------------------
    /** \brief  \ru Двустороннее освещение
                \en Double-Side Lighting. \~

        \details \ru Модификатор который включает двустороннее освещение у объекта.\n
                 \en The Feature that turns on double-side lighting of the object. \~

        \ingroup Features
    */
    // ---
    class VSN_CLASS DoubleSidedLighting : public Feature
    {
    public:
        DoubleSidedLighting(Node* pParent = nullptr);
        ~DoubleSidedLighting();
    private:
        VSN_DECLARE_EX_PRIVATE(DoubleSidedLighting);
    };

    class FaceCullingPrivate;
    //------------------------------------------------------------------------------
    /** \brief  \ru Режим отображения полигонов
                \en Polygon display mode. \~

    \details \ru Включает отображение только передних или задных граний.\n
             \en This feature turns on the rendering front or back faces only. \~

    \ingroup Features
    */
    // ---
    class VSN_CLASS FaceCulling : public Feature
    {
    public:
        FaceCulling( bool back, Node* pParent = nullptr);
        ~FaceCulling();
    private:
        VSN_DECLARE_EX_PRIVATE(FaceCulling);
    };

    class RenderModePrivate;
    //------------------------------------------------------------------------------
    /** \brief  \ru Режим отображения одного сегмента сцены
                \en Polygon display mode to only one segment. \~

    \ingroup Features
    */
    // ---
    class VSN_CLASS RenderMode : public Feature
    {
    public:
        RenderMode( VSN::RenderMode, Node* pParent = nullptr);
        ~RenderMode();
    private:
        VSN_DECLARE_EX_PRIVATE(RenderMode);
    };

    class SectionPlanesPrivate;
    //------------------------------------------------------------------------------
    /** \brief  \ru Плоскости сечения одного сегмента сцены
                \en Section planes of only one segment. \~

    \details \ru Включает отсечение одного сегмента сцены определенными плоскостями.\n
             \en Turn on cutting only one segment with some section planes. \~

    \ingroup Features
    */
    // ---
    class VSN_CLASS SectionPlanes : public Feature
    {
    public:
        SectionPlanes(SectionPlaneId id, Node* pParent = nullptr);
        SectionPlanes(const ObjectSet<SectionPlaneId>& ids, Node* pParent = nullptr);
        ~SectionPlanes();
    private:
        VSN_DECLARE_EX_PRIVATE(SectionPlanes);
    };

} // namespace Features

} // namespace VSN

#endif // __VSN_SEGMENTFEATURES_H
