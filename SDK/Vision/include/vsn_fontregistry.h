///////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс для работы с реестром шрифтов.
         \en Class for working with a font registry. \~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_FONTREGISTRY_H
#define __VSN_FONTREGISTRY_H

#ifdef _WIN32
#include <windows.h>
#endif
#include <vsn_global.h>

namespace VSN {

class FontRegistryPrivate;
//----------------------------------------------------------------------------
//
/** \brief \ru Класс для работы с реестром шрифтов.
           \en Class for working with a font registry. \~
    \details \ru Класс FontRegistry содержит шрифты, доступные для использования в графической библиотеке Vision.
                 Он автоматически формирует свой список на основе шрифтов, найденных в данной системе, а также
                 дополнительно позволяет зарегистрировать пользовательские шрифты.

                 Класс FontRegistry поддерживает только векторные шрифты.

                 Каждый зарегистрированный шрифт определяется следующим набором атрибутов:
                   - Семейство - это определенный дизайн символов, разработанный художником.
                   В классе FontRegistry представляет собой строку символов, обычно на английском языке,
                   которая описывает семейство шрифта (например, «Times New Roman», «Arial»,
                   «Helvetica» и т. д.). При поиске подходящего шрифта указанная строка просто
                   проверяется на строгое совпадение с соответствующим полем в файле шрифта.
                   - Стиль начертания символов задается комбинацией двух флагов: жирный и курсив.

                 Класс не имеет публичного конструктора и для доступа к его методам требуется использовать
                 функцию FontRegistry::Instance().

                 Для регистрации собственных шрифтов в классе FontRegistry имеется функция FontRegistry::RegisterFont().
                 Если в зарегистрированном вручную шрифте больше нет необходимости, то для него следует вызвать
                 функцию FontRegistry::UnregisterFont() для освобождения занимаемой им памяти.

                 Для получения экземпляра шрифта из FontRegistry используется класс Font.
             \en The FontRegistry class contains fonts available for use in the Vision graphic library.
                 It automatically forms its list on the basis of fonts found in this system, as well as
                 additionally, it allows you to register user fonts.

                 FontRegistry class supports only vector fonts.

                 Each registered font is determined by the following set of attributes:
                   - The family is a certain design of symbols developed by an artist.
                   FontRegistry is a string of symbols, usually in English,
                   which describes the font family (for example, Times New Roman, Arial,
                   "Helvetica", etc.).When searching for a suitable font, the indicated line is simply
                   It is checked for strict coincidence with the corresponding field in the font file.
                   - The style of the description of the characters is set by a combination of two flags: fat and italics.

                 The class does not have a public constructor and to access its methods you have to use
                 FontRegistry::Instance () function.

                 To register your own fonts in the FontRegistry class, there is a FontRegistry::RegisterFont() function.
                 If the hand-registered font is no longer needed, you should call
                 FontRegistry::UnregisterFont () function to release its memory.

                 To obtain a font from FontRegistry, Font class is used. \~
  \ingroup Vision_Font
*/
// ---
class VSN_CLASS FontRegistry
{
public:
    /// \ru Получение экземпляра реестра. \en Get an instance of the registry. \~
    static FontRegistry& Instance();
    /// \ru Деструктор. \en Destructor.\~
    virtual ~FontRegistry();
public:
    /** \brief \ru Получение списка зарегистрированных в графической библиотеке Vision семейств.
               \en Obtaining a list of families registered in the Vision graphic library. \~
      \details \ru Возвращает список как системных, так и зарегистрированных вручную
                   с помощью функции FontRegistry::RegisterFont() семейств. Для определения того, является ли шрифт системным, используется функция FontRegistry::IsSystem().
               \en Returns a list of both system and manually registered (Using the FontRegistry::RegisterFont()) font families.
                   To determine whether the font is a system font, the FontRegistry::IsSystem() function is used. \~
    */
    const std::set<std::wstring>& GetFamilies() const;

    /** \brief \ru Проверка доступности шрифта в графической библиотеке Vision.
               \en Check of the accessibility of the font in the Vision graphics library. \~
      \details \ru Возвращает true, если удается найти шрифт с указанными атрибутами.
               \en Returns true if a font with the specified attributes was found. \~
    */
    bool CheckFont(const std::wstring& family, bool bold, bool italic) const;
    /** \brief \ru Проверка признака системного шрифта.
               \en Check for system font. \~
      \details \ru Возвращает true, если такой шрифт доступен в графической библиотеке Vision
                   и является системным.
               \en Returns true if such a font is available in the Vision graphic library
                   and it is a system font. \~
    */
    bool IsSystem(const std::wstring& family, bool bold, bool italic) const;
    /** \brief \ru Регистрация нового шрифта в графической библиотеке Vision из потока.
               \en Registration of a new font in the Vision graphic library from the stream. \~
      \details \ru При успешной регистрации функция возвращает имя зарегистрированного семейства.
                   В случае ошибки возвращается пустая строка. Через переменные bold и italic
                   возвращается информация о стиле начертания символов.
               \en If registration was successful, the function returns the name of the registered family.
                   In the case of an error, an empty line is returned. Through variables bold and italic
                   Information is returned about the style of the symbols. \~
    */
    const std::wstring RegisterFont(std::istream& in, bool& bold, bool& italic);
    /** \brief \ru Регистрация нового шрифта в графической библиотеке Vision с использованием пути к файлу.
               \en Registration of a new font in the Vision graphic library using a file path. \~
      \details \ru При успешной регистрации функция возвращает имя зарегистрированного семейства.
                   В случае ошибки возвращается пустая строка. Через переменные bold и italic возвращается
                   информация о стиле начертания символов.
               \en If registration was successful, the function returns the name of the registered family.
                   In the case of an error, an empty line is returned. Through variables bold and italic
                   Information is returned about the style of the symbols. \~
    */
    const std::wstring RegisterFont(const std::wstring& file, bool& bold, bool& italic);
#ifdef _WIN32
    /** \brief \ru Регистрация нового шрифта в графической библиотеке Vision
                   с использованием существующего дескриптора HFONT.
               \en Registration of a new font in the Vision graphic library
                   using the existing HFONT descriptor. \~
      \details \ru Функция доступна только для платформы Windows.
               \en The method is only available on Windows \~
    */
    const std::wstring RegisterFont(HFONT fontHandle, bool& bold, bool& italic);
#endif
    /** \brief \ru Отмена регистрации шрифта в графической библиотеке Vision и
                   освобождение выделенной для него памяти.
               \en Cancellation of the font registration in the Vision graphics library and
                   the release of memory allocated for it. \~
    */
    bool UnregisterFont(const std::wstring& family);
private:
    /** \brief \ru Приватный конструктор по умолчанию.
               \en Private default constructor. \~
      \details \ru Для доступа к классу FontRegistry используйте функцию FontRegistry::Instance().
               \en To access the Fontregistry class, use the Fontregistry::Instance () function. \~
    */
    FontRegistry();
private:
    VSN_DISABLE_COPY(FontRegistry)
    VSN_DECLARE_PRIVATE(FontRegistry)
};

} // namespace VSN

#endif /* __VSN_FONTREGISTRY_H */
