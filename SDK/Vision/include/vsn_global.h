////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Глобальные объявления типов и определения.
         \en Global type declarations and defines. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_GLOBAL_H
#define __VSN_GLOBAL_H

#if defined(M_E) && !defined(_MATH_DEFINES_DEFINED)
#define _MATH_DEFINES_DEFINED
#endif

#include <string>
#include <math_define.h>
#include <algorithm>
#include <system_cpp_standard.h>

#define VSN_NAMESPACE VSN
#define VSN_BEGIN_NAMESPACE namespace VSN_NAMESPACE {
#define VSN_END_NAMESPACE }
#define VSN_USE_NAMESPACE using namespace VSN_NAMESPACE;

# define VSN_MNG_NAMESPACE(name) name

namespace VSN {

#ifdef _MSC_VER
#if defined ( _BUILDVISIONDLL )
#define VSN_CLASS         __declspec( dllexport )
#define VSN_FUNC(retType) __declspec( dllexport ) retType CALL_DECLARATION
#define VSN_FUNC_EX       __declspec( dllexport ) // \ru для KNOWN_OBJECTS_RW_REF_OPERATORS_EX и KNOWN_OBJECTS_RW_PTR_OPERATORS_EX \en for KNOWN_OBJECTS_RW_REF_OPERATORS_EX and KNOWN_OBJECTS_RW_PTR_OPERATORS_EX 
#else
#define VSN_CLASS         __declspec( dllimport )
#define VSN_FUNC(retType) __declspec( dllimport ) retType CALL_DECLARATION
#define VSN_FUNC_EX       __declspec( dllimport ) 
#endif
#else // _MSC_VER
#define VSN_CLASS
#define VSN_FUNC(retType) retType
#define VSN_FUNC_EX
#endif


#define VSN_MAXINT INT_MAX
#define VSN_DELETE_AND_NULL(x) { if(x) {delete x; x = nullptr;} }

// avoid warning about unused parameter
#define VSN_UNUSED(x) ((void) x)

#define VSN_DISABLE_COPY(Class) \
    Class(const Class &); \
    Class &operator=(const Class &);

#define VSN_DECLARE_PRIVATE(Class) Class##Private* vsn_d_ptr; \
inline Class##Private& vsn_d() { return *vsn_d_ptr; static_assert(std::is_base_of<Class, std::remove_reference<decltype(*this)>::type>::value, "This must be a derived of class"); } \
inline const Class##Private& vsn_d() const { return *vsn_d_ptr; } \
friend class Class##Private;

#define VSN_DECLARE_PUBLIC(Class) \
friend class Class; \
Class* vsn_p_ptr; \
inline void setPublic(Class* ptr) { vsn_p_ptr = ptr; } \
inline Class& vsn_p() { return *vsn_p_ptr; static_assert(std::is_base_of<Class##Private, std::remove_reference<decltype(*this)>::type>::value, "This must be a derived of private-class"); } \
inline const Class& vsn_p() const { return *vsn_p_ptr; }
#define VSN_INIT_PRIVATE(Class) \
vsn_d_ptr = new Class##Private(); vsn_d_ptr->setPublic(this);
#define VSN_D(Class) Class##Private& d = vsn_d();
#define VSN_P(Class) Class& p = vsn_p();
#define VSN_FINI_PRIVATE() \
if (vsn_d_ptr != nullptr) { delete vsn_d_ptr; vsn_d_ptr = nullptr; }

#define VSN_DECLARE_EX_PRIVATE(Class) inline Class##Private& vsn_d() { return reinterpret_cast<Class##Private &>(*vsn_d_ptr); static_assert(std::is_base_of<Class, std::remove_reference<decltype(*this)>::type>::value, "This must be a derived of class"); } \
inline const Class##Private& vsn_d() const { return reinterpret_cast<const Class##Private &>(*vsn_d_ptr); } \
friend class Class##Private;

#define VSN_DECLARE_EX_PUBLIC(Class) \
friend class Class; \
inline Class& vsn_p() { return reinterpret_cast<Class &>(*vsn_p_ptr); static_assert(std::is_base_of<Class##Private, std::remove_reference<decltype(*this)>::type>::value, "This must be a derived of private-class"); } \
inline const Class& vsn_p() const { return reinterpret_cast<Class &>(*vsn_p_ptr); }

#define VSN_2EXD(Class) Class##Private* d = (Class##Private*)vsn_d();

#define VSN_DECLARE_2EX_PRIVATE(Class) inline Class##Private* vsn_d() { return (Class##Private*)(vsn_d_ptr); static_assert(std::is_base_of<Class, std::remove_reference<decltype(*this)>::type>::value, "This must be a derived of class"); } \
inline const Class##Private* vsn_d() const { return (const Class##Private*)(vsn_d_ptr); } \
friend class Class##Private;

typedef void(*FunctionPtr)();

VSN_FUNC(void) vsn_Assert(const char* assertion, const char* file, int line);
VSN_FUNC(void) vsn_Assert_X(const char* where, const char* what, const char* file, int line);

#if defined(_DEBUG)
#   define VSN_ASSERT(cond) \
        if (!(cond)) vsn_Assert(#cond, __FILE__, __LINE__); else static_cast<void>(0)
#else
#   define VSN_ASSERT(cond) static_cast<void>(false && (cond))
#endif

#if defined(_DEBUG)
#   define VSN_ASSERT_X(cond, where, what) \
        if (!(cond)) vsn_Assert_X(where, what, __FILE__, __LINE__); else static_cast<void>(0)
#else
#    define VSN_ASSERT_X(cond, where, what) static_cast<void>(false && (cond))
#endif

#if defined(__GNUC__) || defined(__clang__)
//#   define VSN_DECL_DEPRECATE_DECLARE __attribute__((deprecated(text)))
#   define VSN_DECL_DEPRECATE_DECLARE(text)
#elif defined(_MSC_VER)
#   define VSN_DECL_DEPRECATE_DECLARE(text) __declspec( deprecated(text) )
#else
#   define VSN_DECL_DEPRECATE_DECLARE(text)
#endif

#if defined(VSN_NO_DEPRECATED)
#  undef VSN_DEPRECATED_X
#elif !defined(VSN_NO_DEPRECATED_WARNINGS)
#  define VSN_DEPRECATED_X(text) VSN_DECL_DEPRECATE_DECLARE(text)
#else
#  define VSN_DEPRECATED_X(text)
#endif

typedef int64                   vlonglong;
typedef uint64                  vulonglong;
typedef unsigned char           vuchar;
typedef unsigned short          vushort;
typedef unsigned long           vulong;

typedef int16_t                 vint16;
typedef uint16_t                vuint16;

typedef int32_t                 vint32;
typedef uint32_t                vuint32;

typedef long long               vint64;
typedef unsigned long long      vuint64;

using vintptr = std::conditional<sizeof(void*) == 4, vint32, vint64>::type;
using vptrdiff = vintptr;
using vuintptr = std::conditional<sizeof(void*) == 4, vuint32, vuint64>::type;

template <class T1, class T2>
using ObjectPair = std::pair<T1, T2>;

#define VSN_SETUP_RES(name) \
    do { extern int VSN_MNG_NAMESPACE(vSetupResources_ ## name) ();       \
        VSN_MNG_NAMESPACE(vSetupResources_ ## name) (); } while (0)
#define VSN_CLEANUP_RES(name) \
    do { extern int VSN_MNG_NAMESPACE(vCleanupResources_ ## name) ();    \
        VSN_MNG_NAMESPACE(vCleanupResources_ ## name) (); } while (0)

VSN_FUNC(std::string) vsn_GetEnv(const char* name);
VSN_FUNC(bool) vsn_IsEnvVariableIsSet(const char* name);

VSN_FUNC(void) vsnBadAlloc();
#define VSN_CHECK_PTR(p) do { if (!(p)) vsnBadAlloc(); } while (false)

} // namespace VSN

extern "C" {
    /** \brief \ru Получить информацию о версии файла c3dvision.
             \en Get information about the c3dvision file version. \~
    \details \ru Функция копирует в указанный буфер строку с информацией о версии файла c3d. \n
             \en The function copies a string with information about the c3d file version to the specified buffer. \n \~
    \param[in] buffer     - \ru Указатель на начало буфера.
                            \en Pointer to the beginning of the buffer. \~
    \param[in] bufferSize - \ru Размер буфера, в символах.
                            \en The size of the buffer in characters. \~
    \return \ru Возвращает количество скопированных символов, без учета null-символа. Если buffer == c3d_null возвращается необходимый размер буфера без учета null-символа.
            \en Returns the number of copied characters, excluding the null character. If buffer = = c3d_null returns the required buffer size without the null character. \~
    */
    VSN_FUNC(size_t) C3DVisionVersion(char* buffer, size_t bufferSize);
}

#if defined(WIN32) && defined(_DEBUG)
#define BEGIN_MEMSTATE_LEAK_CHECK { \
                                      _CrtMemState s1, s2, s3; \
                                      _CrtMemCheckpoint(&s1);

#define END_MEMSTATEDEF_LEAK_CHECK    _CrtMemCheckpoint(&s2); \
                                      if (_CrtMemDifference(&s3, &s1, &s2)) \
                                      { \
                                         _CrtMemDumpStatistics(&s3); \
                                         _CrtMemDumpAllObjectsSince(&s1); \
                                      } \
                                   }
#else // WIN32
#define BEGIN_MEMSTATE_LEAK_CHECK
#define END_MEMSTATEDEF_LEAK_CHECK
#endif // WIN32

#include <vsn_logger.h>

#endif //__VSN_GLOBAL_H

