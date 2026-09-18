////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс RenderPostProcess позволяет выполнить финальную постобработку сцены шейдером.
           \en RenderPostProcess class allows you to perform the final post-processing of the scene with a shader. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_RENDERPOSTPROCESS_H
#define __VSN_RENDERPOSTPROCESS_H

#include <vsn_matrix3d.h>
#include <vsn_global.h>
#include <vsn_namespace.h>

namespace VSN {

class Texture2D;
class Texture3D;
class ColorsArray;
class RenderPostProcessPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс RenderPostProcess позволяет выполнить финальную постобработку сцены шейдером.
           \en RenderPostProcess class allows you to perform the final post-processing of the scene with a shader.
    \details \ru В шейдер передаются значения для следующих переменных: \n
               uniform sampler2D VSN_SCENE_COLOR_TEXTURE - текстура с обрабатываемой сценой \n
               uniform sampler2D VSN_SCENE_DEPTH_TEXTURE - текстура, содержащая буфер глубины сцены \n
               varying vec2 VSN_TEXCOORD - текстурные координаты \n
               uniform mat4 VSN_VIEW_PROJECTION - произведение проекционной и видовой матриц \n
               uniform mat4 VSN_INV_VIEW_PROJECTION - матрица, обратная к VSN_VIEW_PROJECTION \n
               uniform vec2 VSN_SCREEN_SIZE - ширина и высота экрана \n
               uniform vec2 VSN_INV_SCREEN_SIZE - инвертированные ширина и высота экрана \n
             \en Values for the following variables are passed to the shader: \n
               uniform sampler2D VSN_SCENE_COLOR_TEXTURE - texture with processed scene \n
               uniform sampler2D VSN_SCENE_DEPTH_TEXTURE - texture containing scene depth buffer \n
               varying vec2 VSN_TEXCOORD - texture coordinates \n
               uniform mat4 VSN_VIEW_PROJECTION - product of projection and view matrices \n
               uniform mat4 VSN_INV_VIEW_PROJECTION - matrix inverse to VSN_VIEW_PROJECTION \n
               uniform vec2 VSN_SCREEN_SIZE - screen width and height \n
               uniform vec2 VSN_INV_SCREEN_SIZE - inverted screen width and height \~
*/
// ---
class VSN_CLASS RenderPostProcess
{
public:
    /// \ru Конструктор. \en Constructor. \~
    explicit RenderPostProcess(std::istream& pixelShader);
    /// \ru Конструктор. \en Constructor. \~
    explicit RenderPostProcess(std::istream& vertexShader, std::istream& pixelShader);
    /// \ru Деструктор. \en Destructor. \~
    ~RenderPostProcess();
public:
    /// \ru Вернуть ошибки при компиляции. \en Get compilation errors. \~
    std::string GetErrorString() const;
    /// \ru Проверить успешность компиляции. \en Check compilation success. \~
    bool IsValid() const;
public:
    /// \ru Добавить текстуру \en Add texture. \~
    void AddTexture(const std::string& name, ColorsArray* colorsArray);
    /// \ru Добавить текстуру \en Add texture. \~
    void AddTexture(const std::string& name, Texture2D* texture);
    /// \ru Добавить текстуру \en Add texture. \~
    void AddTexture(const std::string& name, Texture3D* texture);
    /// \ru Добавить матрицу \en Add matrix. \~
    void AddMatrix(const std::string& name, const Matrix3DF& matrix);

    /// \ru Добавить значение для установки в шейдер. \en Add value to set into shader. \~
    void AddUniformValue(const std::string& name, int value);
    void AddUniformValue(const std::string& name, float value);

    /// \ru Добавить массив для установки в шейдер. Семантика как у glUniform{1|2|3|4}{f|i|}v \en Add array to set into shader. Same semantics as glUniform{1|2|3|4}{f|i|}v. \~
    void AddUniformArray(const std::string& name, const AttrUnitSizes components, const int* data, int count);
    void AddUniformArray(const std::string& name, AttrUnitSizes components, const float* data, int count);
protected:
    VSN_DECLARE_PRIVATE(RenderPostProcess);
};

} // namespace VSN

#endif /* __VSN_RENDERPOSTPROCESS_H */
