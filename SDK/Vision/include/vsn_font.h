///////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс для выбора шрифта, используемого при отрисовке текста на сцене.
         \en A class for choosing a font used to draw a text on the scene. \~
*/

///////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_FONT_H
#define __VSN_FONT_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <vsn_global.h>

namespace VSN {

class FontPrivate;
//----------------------------------------------------------------------------
//
/** \brief \ru Класс для выбора шрифта, используемого при отрисовке текста на сцене.
           \en A class for choosing a font used to draw a text on the scene. \~
  \details \ru Класс Font определяет собой шрифт, используемый для отображения текста.
               Экземпляр шрифта определяется следующим набором атрибутов:
                   - Семейство - это определенный дизайн символов, разработанный художником.
                   В классе Font представляет собой строку символов, обычно на английском языке,
                   которая описывает семейство шрифта (например, «Times New Roman», «Arial»,
                   «Helvetica» и т. д.). При поиске подходящего шрифта указанная строка просто
                   проверяется на строгое совпадение с соответствующим полем в файле шрифта.
                   - Размер.
                   - Стиль начертания символов задается комбинацией двух флагов: жирный и курсив.

               Подходящий шрифт ищется среди системных шрифтов и шрифтов, зарегистрированных
               в графической библиотеке Vision (см. класс FontRegistry).

               При недоступности шрифта с указанными семейством и стилем будет использован шрифт
               по умолчанию. Проверить доступность выбранного шрифта можно с помощью функции Font::IsValid().

               Класс Font поддерживает только векторные шрифты.

               На платформе Windows есть возможность конвертации в дескриптор логического шрифта
               Windows (HFONT) и обратно с помощью функций Font::ToHFont() и Font::FromHFont().
           \en Class Font determines the font used to display the text.
               A font instance is determined by the following set of attributes:
                   - The family is a certain design of symbols developed by an artist.
                   In the Font class it is a string of characters, usually in English,
                   which describes the font family (for example, Times New Roman, Arial,
                   "Helvetica", etc.).When searching for a suitable font, the indicated line is simply
                   checked for strict coincidence with the corresponding field in the font file.
                   - Size.
                   - The style of the description of the characters is set by a combination of two flags: fat and italics.

               The appropriate font is searched among the system fonts and fonts registered
               In the Vision Graphic Library (see FontRegistry class).

               If the font with the indicated family and style is inaccessable, the default font will be used.
               You can check the availability of the selected font using the Font :: ISVALID () function.

               The FONT class supports only vector fonts.

               The Windows platform has the possibility of converting to a logical font descriptor
               Windows (HFONT) and vice versa using Font::ToHFont () and Font::FromHFont (). \~
  \ingroup Vision_Font
*/
// ---
class VSN_CLASS Font
{
public:
    /// \ru Конструктор с параметрами. \en Constructor with parameters \~
    Font(const std::wstring& family, uint fontSize, bool bold = false, bool italic = false);
    /// \ru Конструктор копирования. \en Copy constructor \~
    Font(const Font& other);
    /// \ru Конструктор перемещения. \en Move constructor \~
    Font(Font&& other);
    /// \ru Деструктор. \en Destructor.\~
    ~Font();
public:
    /// \ru Оператор присвоения. \en Assignment operator.\~
    Font& operator=(const Font& other);
    /// \ru Оператор присваивания перемещением. \en Move assignment operator.\~
    Font& operator=(const Font&& other);
public:
    /** \brief \ru Проверка доступности шрифта в графической библиотеке Vision.
               \en Check of the accessibility of the font in the Vision graphics library. \~
      \details \ru Возвращает true, если удается найти шрифт с указанными атрибутами.
               \en Returns true if a font with the specified attributes was found. \~
    */
    bool IsValid() const;
    /** \brief \ru Проверка признака системного шрифта.
               \en Check for system font. \~
      \details \ru Возвращает true, если такой шрифт доступен в графической библиотеке Vision
                   и является системным.
               \en Returns true if such a font is available in the Vision graphic library
                   and it is a system font. \~
    */
    bool IsSystem() const;
    /// \ru Получение имени семейства шрифта. \en Obtaining the name of the font family. \~
    const std::wstring& GetFamilyName() const;
    /// \ru Задание имени семейства шрифта. \en Setting the name of the font family. \~
    void SetFamilyName(const std::wstring & family);
    /// \ru Получение размера шрифта. \en Obtaining the font size. \~
    uint GetSize() const;
    /// \ru Задание размера шрифта. \en Setting the font size. \~
    void SetSize(uint fontSize);
    /// \ru Получение признака жирности шрифта. \en Obtaining a sign of font fatness. \~
    bool IsBold() const;
    /// \ru Задание признака жирности шрифта. \en Setting a sign of font fatness. \~
    void SetBold(bool bold);
    /// \ru Получение признака курсива шрифта. \en Obtaining a sign of font italics. \~
    bool IsItalic() const;
    /// \ru Задание признака курсива шрифта. \en Setting a sign of font italics. \~
    void SetItalic(bool italic);
#ifdef _WIN32
    /** \brief \ru Преобразовать в шрифт Windows.
               \en Convert to Windows font \~
      \details \ru Функция доступна только для платформы Windows.
               \en The method is only available on Windows. \~
    */
    HFONT ToHFont();
#endif
public:
    /// \ru Получить шрифт по умолчанию (Arial). \en Get the default font (arial). \~
    static Font Default();
#ifdef _WIN32
    /** \brief \ru Получить шрифт через существующий дескриптор шрифта HFONT.
               \en Get a font through the existing HFONT font descriptor. \~
      \details \ru Функция доступна только для платформы Windows.
               \en The method is only available on Windows. \~
    */
    static Font FromHFont(HFONT fontHandle);
#endif
private:
    VSN_DECLARE_PRIVATE(Font)
};

} // namespace VSN

#endif /* __VSN_FONT_H */
