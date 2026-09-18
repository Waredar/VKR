////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс HeightMapSurfaceGeometry обеспечивает обработку данных карты высот, 
               связанных с поверхностью, и позволяет отобразить карту высот в виде поверхности. 
           \en NO TRANSLATION. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_HEIGHTMAPSURFACEGEOMETRY_H
#define __VSN_HEIGHTMAPSURFACEGEOMETRY_H

#include <vsn_image.h>
#include <vsn_meshgeometry.h>
#include <vsn_global.h>

namespace VSN {

class HeightMapSurfaceGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief  \ru Класс HeightMapSurfaceGeometry обеспечивает обработку данных карты высот, 
                связанных с поверхностью, и позволяет отобразить карту высот в виде поверхности.
            \en NO TRANSLATION. \~
    \details \ru Поскольку карты высот не содержат значений для осей X или Z, эти значения должны быть заданы
                 отдельно с использованием свойств minXValue, maxXValue, minZValue и maxZValue. Х - значение, соответствующее
                 изображению горизонтального направления, Z - значение по вертикали. Установка любого из этих
                 свойств запускает асинхронное повторное разрешение любой существующей карты высот. \n
            \en  NO TRANSLATION. \n \~
    \ingroup Vision_Image
*/
// ---
class VSN_CLASS HeightMapSurfaceGeometry final: public MeshGeometry
{
    VSN_OBJECT(HeightMapSurfaceGeometry);
    VSN_PROPERTY_NOTIFY(data, OnHeightMapModified)
public:
    /// \ru Конструктор по умолчанию \en Default constructor. \~
    explicit HeightMapSurfaceGeometry(Node* parent = nullptr);
    /// \ru Конструктор с заданным изображением и родителем \en NO TRANSLATION. \~
    explicit HeightMapSurfaceGeometry(unsigned char* data, int width, int height, Node* parent = nullptr);
    /// \ru Деструктор \en Destructor. \~
    virtual ~HeightMapSurfaceGeometry();
public:
    void SetHeightMap(unsigned char* data, int width, int height);
public: // signals group
    /// \ru Этот сигнал будет генерирован при модификации изображения карты высот \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, OnHeightMapModified, void OnHeightMapModified(unsigned char* data), data);
private:
    VSN_DISABLE_COPY(HeightMapSurfaceGeometry);
    VSN_DECLARE_EX_PRIVATE(HeightMapSurfaceGeometry);
};

} // namespace VSN

#endif /* __VSN_HEIGHTMAPSURFACEGEOMETRY_H */
