////////////////////////////////////////////////////////////////////////////////
/**
\file
  \brief \ru CommentRep - это класс, представляющий текст в рамке на выносной линии.
         \en CommentRep class presents a text in a frame on a leader line. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_COMMENTREP_H
#define __VSN_COMMENTREP_H

#include <string>

#include <vsn_geometryrep.h>
#include <vsn_wireframegeometry.h>
#include <vsn_global.h>

namespace VSN {

class CommentGeometry;
class Font;
//------------------------------------------------------------------------------
/** \brief \ru CommentRep - это класс, представляющий текст в рамке на выносной линии.
           \en CommentRep class presents a text in a frame on a leader line. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS CommentRep : public GeometryRep
{
    VSN_OBJECT(CommentRep)
public:
    enum class FrameBorder
    {
        NoneBorder,
        BottomBorder,
        Border,
    };
public:
    /// \ru Конструктор по умолчанию. \en Default consructor. \~
    CommentRep(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~CommentRep();
public:
    /** \brief \ru Инициализировать объект по двум параметрам. \en Initializes object by two parameters. \~
               \param[in] first  - \ru Положение начала выносной линии.
                                   \en Position of leader line start. \~
               \param[in] second - \ru Положение текста.
                                   \en Text position. \~
    */
    void Init(const MbCartPoint3D& first, const MbCartPoint3D& second);
    /** \brief \ru Инициализировать объект по двум параметрам. \en Initializes object by two parameters. \~
               \param[in] pointers - \ru Список начальных положений выносных линий.
                                     \en List of start positions of leader lines. \~
               \param[in] textPos  - \ru Положение текста.
                                     \en Text position. \~
    */
    void Init(const std::vector<MbCartPoint3D>& pointers, const MbCartPoint3D& textPos);
    /// \ru Добавить выносную линию. \en Add the leader line. \~
    void AddLeader(const MbCartPoint3D & targetPosition);
    /// \ru Получить кол-во линий выноски. \en Get the number of leaders.\~
    size_t CountLeaders() const;
    /// \ru Получить позицию линии выноски. \en Get the position of the leader.\~
    MbCartPoint3D GetLeader(size_t index) const;
    /// \ru Изменить позицию линии выноски. \en Change the position of the leader.\~
    void ChangeLeader(size_t index, const MbCartPoint3D & point);
    /// \ru Получить текст. \en Get text.\~
    WString GetText() const;
    /// \ru Задать текст. \en Sets text. \~
    void SetText(const WString & text);
    /// \ru Задать текст. \en Sets text. \~
    void SetText(const std::wstring & text);
    /// \ru Очистить текст. \en Clears text. \~
    void ClearText();
    /// \ru Задать шрифт текста. \en Set font of text.\~
    void SetFont(const Font& font);
    /// \ru Получить шрифт текста. \en Get font of text.\~
    const Font GetFont() const;
    // \ru Установить направление текста. \en Set text direction.
    void SetTextDirection(TextDirection dir);
    // \ru Получить направление текста. \en Get text direction.
    TextDirection GetTextDirection() const;
    /// \ru Скрыть линии. \en Hide lines. \~
    void HideLines();
    /// \ru Показать линии. \en Show lines. \~
    void ShowLines();
    /// \ru Получить пересечение текста комментария с экраном. \en Get text intersection with screen. \~
    int GetViewportIntersection(const Viewport & viewport);
    // \ru Получить цвет текста. \en Get text color.
    void SetTextColor(Color color);
    // \ru Получить цвет текста. \en Get text color.
    Color GetTextColor();
    // \ru Изменить позицию текста. \en Change text position. \~
    void SetTextPosition(const MbCartPoint3D & textPos);
    // \ru Получить позицию текста. \en Get text position. \~
    MbCartPoint3D GetTextPosition() const;
    /// \ru Изменить тип наконечника линий выноски. \en Set leader lines tip type.
    void SetTipType(CommentTip tip);
    /// \ru Получить тип наконечника линий выноски. \en Get leader lines tip type.
    CommentTip GetTipType() const;
    // \ru Изменить цвет Линий. \en Set rect color.
    void SetLineColor(Color color);
    // \ru Получить цвет рамки. \en Get rect color.
    Color GetLineColor();
    // \ru Изменить тип рамки. \en Set border type.\~
    void  SetFrameBorder(FrameBorder type);
    // \ru Получить тип рамки. \en Get border type.\~
    FrameBorder GetFrameBorder() const;
    // \ru Задать положение точки привязки выносной линии. \en Set leader linking point alignment
    void  SetTextAlignment(OriginHAlign h, OriginVAlign v);
    // \ru Получить положение точки привязки выносной линии. \en Get leader linking point alignment
    void  GetTextAlignment(OriginHAlign& h, OriginVAlign& v);
    // \ru Автоматическое размещение точки привязки выносной линии. \en Automatic leader linking point alignment
    void SetTextAutoAlignment(bool autoAlignment);
    // \ru Включено ли автоматическое размещение точки привязки выносной линии. \en Checks automatic leader linking point alignment
    bool IsTextAutoAlignment();
    /// \ru Установить отступы текста внутри от границ. \en Set the margins of the text inside from the borders. \~
    void SetMargin(const MbRect& margin);
    /// \ru Получить отступы текста внутри от границ. \en Get the margins of the text inside from the borders. \~
    const MbRect& GetMargin() const;
    /// \ru Получить размер рамки текста. \en Get text rectangle size. \~
    void GetTextRectSize(double& width, double& height) const;
    /// \ru Сделать текст масштабируемым. \en NO TRANSLATION.\~
    void SetScalable(bool value);
    /// \ru Узнать являеться ли текст масштабируемым \en NO TRANSLATION.\~
    bool IsScalable() const;
private:
    VSN_DISABLE_COPY(CommentRep)
};

} // namespace VSN

#endif /* __VSN_COMMENT_H */
