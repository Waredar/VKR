#ifndef __VSN_PLANEMARKER_H
#define __VSN_PLANEMARKER_H

#include <vsn_global.h>

namespace VSN {

/// \ru Идентификатор иконки \en NO TRANSLATION. \~
enum class MarkerID : int
{
    unknown = 0,
    labelX,
    labelY,
    labelZ,
    rect,
    circle,
    lastId = circle,
};

class Image;
class Canvas;
class PlaneMarkerPrivate;

//------------------------------------------------------------------------------
/** \brief  \ru Класс PlaneMarker позволяет отображать иконкци на сцене.
            \en NO TRANSLATION. \~
    \details \ru Этот класс предоставляет инструменты для создания отображаемой иконки средствами вижена.
                 А так же предоставляет возможность загрусить отображаемое изображение из битовой карты.\n
             \en NO TRANSLATION. \n \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS PlaneMarker
{
public:
    /// \ru Конструктор \en NO TRANSLATION. \~
    PlaneMarker();
    /// \ru Конструктор \en NO TRANSLATION. \~
    PlaneMarker(const Image & img);
    /// \ru Деструктор \en NO TRANSLATION. \~
    virtual ~PlaneMarker();
    PlaneMarker(const PlaneMarker&) = delete;
    /// \ru Идентификатор иконки \en NO TRANSLATION. \~
    MarkerID GetId() const;
    /// \ru Инструмент для рисования маркера средствами вижена \en NO TRANSLATION. \~
    Canvas &      GetCanvas();
    /// \ru Получить изображение маркера. \en NO TRANSLATION. \~
    const Image & GetImage() const;
    /// \ru Идентификатор иконки \en NO TRANSLATION. \~
    operator MarkerID() const { return GetId(); }
private:
    friend class MarkersStore;
    PlaneMarker(MarkerID id);
    VSN_DECLARE_PRIVATE(PlaneMarker)
};

} // namespace VSN

#endif // __VSN_PLANEMARKER_H