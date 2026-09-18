///////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru ПространствоИмен GLProxy для шлюзирования вызовов OpenGL функций.
         \en GLProxy NameSpace for gating OpenGL function calls. \~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_GLFIXEDFUNCTIONSPROXY_H
#define __VSN_GLFIXEDFUNCTIONSPROXY_H

#include <vsn_global.h>
#include <vector>

namespace VSN {

class OpenGLFunctionListInterface;
class OpenGLExtraFunctionListInterface;


//------------------------------------------------------------------------------
/** \brief \ru ПространствоИмен GLProxy для шлюзирования вызовов OpenGL функций.
           \en GLProxy NameSpace for gating OpenGL function calls. \~
     \details \ru ПространствоИмен GLProxy содержит функции, которые оборачия функции OpenGL:
                - кешируют данные, такие как переменные шейдеров, для подстановки в шейдера для CoreProfile
                    вместо FixedFunctions в CompatibilityProfile контекста OpenGL
                - подменяют некоторые FixedFunctions фитчи на шейдерные
                - собариют вызовы функций для оптимизации, отслеживанию при отладке и профайлинге
              \en GLProxy NameSpace contains functions which wrapping OpenGL functions:
                - caching data such as shaders' variables for substituting at the shaders for CoreProfile
                    instead of FixedFunctions at CompatibilityProfile of OpenGL context
                - exchange some FixedFunctions' features with shaders'
                - collect functions' invocations to optimize, catch and profile \n \~
    \ingroup Vision_Geometry
*/
// ---
namespace GLProxy {

/// \ru Инициализировать. \en Initialize.
VSN_FUNC_EX bool Init();

/// \ru Освободить ресурсы. \en Release resources.
VSN_FUNC_EX void Free();

/// \ru Получить инициализорованна. \en Get initialized.
bool IsInitialized();

/// \ru Получить использование FixedFunctions. \en Get usage of FixedFunctions.
VSN_FUNC_EX bool GetFixedFunctionsUsage();
/// \ru Установить использование FixedFunctions. \en Set usage of FixedFunctions.
VSN_FUNC_EX void SetFixedFunctionsUsage(bool);

/// \ru . \en .
VSN_FUNC_EX void SetRendererUsage(bool); 

/// \ru Установить цвет. \en Set color.
void glColor4f(float, float, float, float);

/// \ru Установить семантику матрицы для использования. \en Set matrix semantics for using.
VSN_FUNC_EX void glMatrixMode(uint32_t);
/// \ru Загрузить матрицу из float-ов. \en Load matrix from float-s.
void glLoadMatrixf(const float[16]);
/// \ru Загрузить матрицу из double-ов. \en Load matrix from double-s.
void glLoadMatrixd(const double[16]);
/// \ru Перемножить матрицу с float-ами. \en Multiply matrix with float-s.
void glMultMatrixf(const float[16]);
/// \ru Перемножить матрицу с double-ами. \en Multiply matrix with double-s.
void glMultMatrixd(const double[16]);
/// \ru Загрузить единичную матрицу. \en Load indentity matrix.
VSN_FUNC_EX void glLoadIdentity();

/// \ru Установить ортогональную в проективную матрицу. \en Set orthogonal one into projective matrix.
void glOrtho(double, double, double, double, double, double);

/// \ru Добавить матрицу. \en Append matrix.
void glPushMatrix();
/// \ru Удалить матрицу. \en Delete matrix.
void glPopMatrix();

/// \ru Добавить атрибут. \en Append attribute.
void glPushAttrib(uint32_t);
/// \ru Удалить атрибут. \en Delete attribute.
void glPopAttrib();

/// \ru Установить модель шейдинга. \en Set shading model.
void glShadeModel(uint32_t);

/// \ru Установить текстурные параметры. \en Set texture parameters.
void glTexEnvf(uint32_t, uint32_t, float);

/// \ru Отрисовать индексированную геометрию. \en Draw indexed geometry.
VSN_FUNC_EX void glDrawElements(OpenGLFunctionListInterface*, uint32_t, uint32_t, uint32_t, const void*);
/// \ru Отрисовать геометрию. \en Draw geometry.
VSN_FUNC_EX void glDrawArrays(OpenGLFunctionListInterface*, uint32_t, int32_t, uint64_t);
VSN_FUNC_EX void glDrawElementsInstanced(OpenGLFunctionListInterface*, OpenGLExtraFunctionListInterface* pExtraFunc,
    unsigned int mode, int count, unsigned int type, const void* indices, int instancecount);

/// \ru . \en .
VSN_FUNC_EX void SetCurrentShaderProgramID(uint32_t);
uint32_t GetCurrentShaderProgramID();

//int32_t glGetUniformLocation(uint32_t, const char*);
//void glUniformMatrix4fv(int32_t, uint64_t, bool, const float*);

/// \ru . \en .
bool AddProxyShaderProgramID(uint32_t id);
/// \ru . \en .
bool DelProxyShaderProgramID(uint32_t id);
const std::vector<uint32_t>& GetProxyShaderProgramIDs();

/// \ru . \en .
void glBufferData(uint32_t, uint64_t, const void*, uint32_t);

/// \ru . \en .
void SwitchDrawCalls(bool);

/// \ru . \en .
VSN_FUNC_EX void SetBufferID(uint32_t);
/// \ru . \en .
uint32_t GetBufferID();

} // namespace GLProxy
} // namespace VSN

#endif // __VSN_GLFIXEDFUNCTIONSPROXY_H
