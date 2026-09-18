////////////////////////////////////////////////////////////////////////////////
/**
\file Внимание. Интерфейс не устоявшийся
  \brief \ru Инструмент логирования
           Использование:
           vsnDebug("Текст для отладки");
           vsnCritical("Еще один текст для отладки");

           Вывод в output:
           debug: D:\Development\VisionWork\Examples\Qt\01_Background\background.cpp(177) : Текст для отладки
           critical: D:\Development\VisionWork\Examples\Qt\01_Background\background.cpp(178) : Еще один текст для отладки
         \en Logging tools \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_MESSAGELOGGER_H
#define __VSN_MESSAGELOGGER_H

#include <tool_cstring.h>
#include <string>
#include <vsn_global.h>

namespace VSN {

enum ELevel
{
    el_notset = -1,
    el_trace,
    el_debug,
    el_info,
    el_warning,
    el_error,
    el_critical,
    el_fatal,
};

/* MessageLogContext */
class MessageLogContext
{
public:
    MessageLogContext() noexcept = default;
    MessageLogContext(const char* fileName, int lineNumber, const char* functionName, const char* categoryName) noexcept
        : m_line(lineNumber), m_file(fileName), m_function(functionName), m_category(categoryName) {}
private:
    MessageLogContext& CopyFrom(const MessageLogContext& logContext) noexcept;
public:
    int m_version = 2;
    int m_line = 0;
    const char* m_file = nullptr;
    const char* m_function = nullptr;
    const char* m_category = nullptr;
private:
    VSN_DISABLE_COPY(MessageLogContext)
};

//------------------------------------------------------------------------------
/** \brief \ru Расширенный инструмент логирования.
           \en NO TRANSLATION. \~
    \ingroup Vision_Tools
*/
// ---
class VSN_CLASS MessageLogger
{
public:
    MessageLogger(const char* file, int line);
public:
    // трассировка
    void Trace(const char* msg) const;
    // отладка
    void Debug(const char* msg, ...) const;
    // информация
    void Info(const char* msg) const;
    // предупреждение
    void Warning(const char* msg, ...) const;
    // ошибка
    void Error(const char* msg) const;
    // критическая ошибка
    void Critical(const char* msg) const;
public:
    // установка порога записи
    void SetLevel(ELevel level);
    // общая функция логирования
    void Log(ELevel level, const char* msg) const;
    // фатальная ошибка
    void Fatal(const char* msg, ...) const;
private:
    MessageLogContext m_context;
};

#define vsnTrace      VSN::MessageLogger(__FILE__, __LINE__).Trace
#define vsnDebug      VSN::MessageLogger(__FILE__, __LINE__).Debug
#define vsnInfo       VSN::MessageLogger(__FILE__, __LINE__).Info
#define vsnWarning    VSN::MessageLogger(__FILE__, __LINE__).Warning
#define vsnError      VSN::MessageLogger(__FILE__, __LINE__).Error
#define vsnCritical   VSN::MessageLogger(__FILE__, __LINE__).Critical
#define vsnFatal      VSN::MessageLogger(__FILE__, __LINE__).Fatal

} // namespace VSN

#endif // __VSN_MESSAGELOGGER_H
