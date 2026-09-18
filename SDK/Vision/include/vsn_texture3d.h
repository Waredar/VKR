////////////////////////////////////////////////////////////////////////////////
/**
\file
  \brief \ru Класс Texture3D для обработки 3D-текстур. Используется для создания 
             текстур "на лету" или для изменения существующих текстурных ресурсов.
         \en Texture3D class is for processing 3D textures. The class is used
             to create textures on the fly or to change the existing texture resources. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_TEXTURE3D_H
#define __VSN_TEXTURE3D_H

#include <vsn_global.h>
#include <vsn_size.h>
#include <vsn_image.h>
#include <vsn_namespace.h>
#include <string>

namespace VSN {

class Texture3DPrivate;
class Image;

//------------------------------------------------------------------------------
/** \brief \ru Класс Texture3D для обработки 3D-текстур. Используется для создания текстур "на лету" 
               или для изменения существующих текстурных ресурсов. 
           \en Texture3D class is for processing 3D textures. The class is used to create textures
               on the fly or to change the existing texture resources. \~
           \details \ru  \n
                    \en  \n \~
*/
// ---
class VSN_CLASS Texture3D
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    Texture3D();
    /// \ru Конструктор копирования. \en Copy constructor. \~
    Texture3D(const Texture3D& other) = delete;
    /// \ru Деструктор. \en Destructor. \~
    virtual ~Texture3D();
public:
    /// \ru Активировать текстуру. \en Activates texture. \~
    void OGLBindTexture();
public:
    /// \ru Инициализировать, используя Image. \en Initializes using Image. \~
    bool  Init(const std::vector<const Image*>& imageArray);
    /// \ru Инициализировать, используя битовую карту. \en Initializes using bit map. \~
    bool  Init(TextureFormat format, SizeI size, const std::vector<const unsigned char *>& pBitsArray);
    /// \ru Вернуть ширину текстуры. \en Returns texture width. \~
    uint  GetWidth() const;
    /// \ru Вернуть высоту текстуры. \en Returns texture height. \~
    uint  GetHeight() const;
    /// \ru Вернуть глубину текстуры. \en Returns texture depth. \~
    uint  GetDepth() const;
    /// \ru Вернуть идентификатор текстуры. \en Returns texture identifier. \~
    uint  GetUniqueKey() const;
    /// \ru Узнать о наличии альфа-канала. \en Checks if alpha channel exists. \~
    bool HasAlphaChannel() const;
    /// \ru Узнать состояние текстуры. \en Checks texture state. \~
    bool IsLoaded() const;
public: // texture parameters
    /// \ru Задать фильтры растеризации. \en Sets rasterization filters. \~
    void SetFilters(TextureFilter min, TextureFilter max);
    /// \ru Задать значение анизотропного фильтра. \en Sets value of anisotropic filter. \~
    void SetAnisotropic(float value);
    /// \ru Задать параметры повтора текстуры. \en Sets parameters of texture repeat. \~
    void SetWrap(TextureWrap s, TextureWrap t,TextureWrap r);
public:
    /// \ru Оператор копирования. \en Copy operator. \~
    Texture3D& operator = (const Texture3D& other) = delete;
private:
    VSN_DECLARE_PRIVATE(Texture3D)
};

} // namespace VSN

#endif /* __VSN_TEXTURE3D_H */
