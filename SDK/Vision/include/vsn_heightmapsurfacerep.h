////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс HeightMapSurfaceRep обеспечивает обработку данных карты высот,
               связанной с поверхностью, и позволяет отобразить карту высот в виде поверхности 
           \en NO TRANSLATION. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_HEIGHTMAPSURFACEREP_H
#define __VSN_HEIGHTMAPSURFACEREP_H

#include <vsn_image.h>
#include <vsn_geometryrep.h>
#include <vsn_global.h>

namespace VSN {

class HeightMapSurfaceRepPrivate;
//------------------------------------------------------------------------------
/** \brief  \ru Класс HeightMapSurfaceRep обеспечивает обработку данных карты высот, 
                связанной с поверхностью, и позволяет отобразить карту высот в виде поверхности
            \en NO TRANSLATION. \~
    \details \ru Поскольку карты высот не содержат значений для осей X или Z, эти значения должны быть заданы
                 отдельно с ипользованием свойств minXValue, maxXValue, minZValue и maxZValue. Х - значение, соответствующее
                 изображению горизонтального направления,  Z - значение по вертикали. Установка любого из этих
                 свойств запускает асинхронное повторное разрешение любой существующей карты высот \n
            \en  NO TRANSLATION. \n \~
    \ingroup Vision_Image
*/
// ---
class VSN_CLASS HeightMapSurfaceRep final : public GeometryRep
{
    VSN_OBJECT(HeightMapSurfaceRep);
    VSN_PROPERTY_NOTIFY(data, OnHeightMapModified);
public:
    /// \ru Конструктор по умолчанию \en Default constructor. \~
    explicit HeightMapSurfaceRep(Node* parent = nullptr);
    /// \ru Конструктор с заданным изображением и родителем \en NO TRANSLATION. \~
    explicit HeightMapSurfaceRep(unsigned char* data, int width, int height, Node* parent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~HeightMapSurfaceRep();
public:
    void SetHeightMap(unsigned char* data, int width, int height);
public: // signals group
    /// \ru Этот сигнал будет генерирован при модификации изображения карты высот \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, OnHeightMapModified, void OnHeightMapModified(unsigned char* data), data);
private:
    VSN_DISABLE_COPY(HeightMapSurfaceRep);
    VSN_DECLARE_EX_PRIVATE(HeightMapSurfaceRep);
};

} // namespace VSN

#endif /* __VSN_HEIGHTMAPSURFACEREP_H */
