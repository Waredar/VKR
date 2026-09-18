////////////////////////////////////////////////////////////////////////////////
/**
\file
\brief \ru Классы Material и SelectionMaterial для работы с визуальными свойствами материала.
       \en Material class and SelectionMaterial class for working with visual properties of the material. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_MATERIAL_H
#define __VSN_MATERIAL_H

#include <string>
#include <unordered_map>

#include <attr_color.h>
#include <attribute_container.h>
#include <attr_elementary_attribute.h>

#include <vsn_color.h>
#include <vsn_feature.h>
#include <vsn_node.h>

#include <vsn_global.h>

namespace VSN {

class Texture2D;
class MaterialPrivate;
class OpenGLContextInterface;
class Geometry;
//------------------------------------------------------------------------------
/** \brief   \ru Визуальные свойства материала.
             \en Visual properties of the material. \~
    \details \ru Класс Material позволяет задавать визуальные параметры материала.
             \en Material class allows setting visual parameters of the material. \~
*/
//---
class VSN_CLASS Material : public Feature
{
    VSN_OBJECT(Material)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    Material();
    /**
    \brief \ru Конструктор по диффузному цвету. \en Constructor by diffuse color. \~
        \details \ru Конструктор задает диффузный цвет; цвет фона по умолчанию темно-серый.
                 \en The constructor sets diffuse color; the default ambient color is dark grey.
    */
    Material(const Color& color, float opacity = 1.f);
    /**
    \brief \ru Конструктор по диффузному цвету. \en Constructor by diffuse color.  \~
        \param[in] name - \ru Строковое имя материала.
                          \en String name of the material. \~
        \param[in] pDiffuseColor - \ru Цвет диффузии материала.
                                   \en Diffuse color of the material. \~
        \details \ru Конструктор задает имя материала и диффузный цвет; цвет фона по умолчанию темно-серый.
                 \en The constructor sets material name and diffuse color; the default ambient color is dark grey.
    */
    Material(const String& name, const float* pDiffuseColor);
    /// \ru Конструктор по текстуре и имени материала. \en Constructor by texture and material name.
    Material(Texture2D* pTexture, const String& name = String());
    /// \ru Конструктор копирования. \en Copy constructor.
    Material(const Material& material);
    virtual ~Material();
public:
    static const Material& GetDefaultMaterial();
    static void SetDefaultMaterial(const Material& material);
public:
    /// \ru Задать другое значение материала. \en Sets other material value.
    void CopyFrom(const Material& material);
    /// \ru Вернуть true, если этот материал не применяется. \en True if material is not used.
    bool IsMaterialUnused() const;
    /// \ru Вернуть true, если материал представлен текстурой. \en True if material is represented by texture.
    bool IsMaterialPresentedTexture() const;
    /// \ru Вернуть цветовое значение общего фона. \en Returns the ambient color value.
    Color GetAmbient() const;
    /// \ru Задать цвет общего фона. \en Sets ambient color.
    void SetAmbient(const Color& ambient);

    /// \ru Вернуть цветовое значение диффузии. \en Returns diffuse color value.
    Color GetDiffuse() const;
    /// \ru Задать цвет диффузии. \en Sets diffuse color.
    void SetDiffuse(const Color& diffuse);

    /// \ru Вернуть значение зеркальности. \en Returns specular value.
    Color GetSpecular() const;
    /// \ru Задать значение зеркальности. \en Sets specular value.
    void SetSpecular(const Color& specular);

    /// \ru Вернуть значение излучения. \en Returns emission value.
    Color GetEmission() const;
    /// \ru Задать значение излучения. \en Sets emission value.
    void SetEmission(const Color& emission);

    /// \ru Вернуть значение блеска. \en Returns shininess value.
    float GetShininess() const;
    /// \ru Задать значение блеска. Принимает значения [0, 128]. \en Sets shininess value. Only shininess values in the range [0, 128] are accepted.
    void SetShininess(float shininess);

    /// \ru Вернуть идентификатор текстуры. \en Returns texture identifier.
    uint GetTextureID() const;

    /// \ru Вернуть true, если текстура загружена. \en True if texture is loaded.
    bool IsTextureLoaded() const;

    /// \ru Вернуть true, если материал является прозрачным. \en True if material is transparent.
    bool IsTransparent() const;
    /// \ru Вернуть значение непрозрачности. \ru Returns opacity value.
    float GetOpacity() const;
    /// \ru Задать непрозрачность. \ru Sets opacity.
    void SetOpacity(float opacity);

    /// \ru Вернуть количество геометрии, использующей этот материал. \en Return a count of the geometric objects which use the material.
    size_t GetUseCount() const;

    /// \ru Выключить освещение объектов с данным материалом. \ru The objects with this material are not lighting
    void ExcludeFromLighting();
    /// \ru Включить освещение объектов с данным материалом. \ru The objects with this material are not lighting
    void IncludeToLighting();
    /// \ru Исключены ли, объекты  с данным материалом, из освещения ? \ru Are excluded the objects with this material from lighting ?
    bool IsExcludedFromLighting() const;

    /// \ru Вернуть указатель на текстуру. \en Returns pointer to the texture.
    Texture2D* GetTexture() const;
    /// \ru Установить новую текстуру. \en Sets new texture.
    void SetTexture(Texture2D* pTexture);
    /// \ru Вернуть хэш, собранный из всех составляющих. \en Returns hash composed from all components.
    uint GetHashMaterial() const;
public:
    /// \ru Удалить текстуру. \en Deletes texture.
    void DeleteTexture();
    /// \ru Добавить объект, который использует этот материал. \en Adds object with given material.
    bool AddGeomObject(Geometry* pGeom);
    /// \ru Открепить геометрический объект, использующий этот материал, из массива. \en Detaches geometry object with given material from the array.
    bool DetachGeomObject(const NodeKey& key);
    /// \ru Добавить в массив идентификатор геометрии, использующий этот материал. \en Adds geometry identifier with given material to the array.
    bool AddObjectId(const NodeKey& key);
    /// \ru Открепить объект из массива идентификаторов, использующих этот материал. \en Detaches object from the array of identifiers that use this material.
    bool DetachObjectId(const NodeKey& key);
public:
    VSN_SIGNAL(Public, signalMaterialModified,           void signalMaterialModified(const Material& mt), mt)
    VSN_SIGNAL(Public, signalOpacityModified,            void signalOpacityModified(float opacity), opacity)
    VSN_SIGNAL(Public, signalIgnoreTransparencyModified, void signalIgnoreTransparencyModified(bool bIgnore), bIgnore)
    VSN_SIGNAL(Public, signalIgnoreDiffuseModified,      void signalIgnoreDiffuseModified(bool bIgnore), bIgnore)

    VSN_SLOT  (Public, slotSetOpacity,            void slotSetOpacity(float opacity))
    VSN_SLOT  (Public, slotCopyFrom,              void slotCopyFrom(const Material&))
    VSN_SLOT  (Public, slotSetIgnoreTransparency, void slotSetIgnoreTransparency(bool bIgnore))
    VSN_SLOT  (Public, slotSetIgnoreDiffuse,      void slotSetIgnoreDiffuse(bool bIgnore))
public:
    /// \ru Выполнить инициализацию материала для отрисовки. \en Initializes material for rendering.
    virtual void glPerform(FaceSide faceSide = FaceSide::FrontAndBack);
    /// \ru Выполнить инициализацию материала для отрисовки с прозрачностью. \en Initializes material for rendering with transparency.
    virtual void glPerform(float);
    /// \ru Освободить материал. \en Release the material.
    virtual void Release();
public:
    /// \ru Оператор присвоения. \en Assignment operator.
    inline Material& operator = (const Material& mat);
    /// \ru Вернуть true, если материал эквивалентен. \en True if material is equivalent.
    bool operator == (const Material&) const;
protected:
    /// \ru Конструктор для внутреннего использования. \en NO TRANSLATION.
    Material(MaterialPrivate& dd, Node* pParent);
    MaterialPrivate& m_materialPrivate;
    VSN_DECLARE_EX_PRIVATE(Material);
};

inline Material& Material::operator = (const Material& material)
{
    CopyFrom(material);
    return *this;
}

//------------------------------------------------------------------------------
/** \brief  \ru Кэш материалов для повторного использования.
            \en Material cache for reuse.
*/
//---
class VSN_CLASS MaterialCache
{
public:
    typedef typename std::map<const MbUuid, Material*>::iterator iteratorUuid;
    typedef typename std::map<const MbUuid, Material*>::const_iterator const_iteratorUuid;
    typedef typename std::map<const MbColor*, Material*>::iterator iteratorColor;
    typedef typename std::map<const MbColor*, Material*>::const_iterator const_iteratorColor;
    typedef typename std::map<const MbVisual*, Material*>::iterator iteratorVisual;
    typedef typename std::map<const MbVisual*, Material*>::const_iterator const_iteratorVisual;
public:
    MaterialCache() {}
    ~MaterialCache() {}
public:
    static Material* CreateMaterialFromAttribute(const MbAttributeContainer& attr, bool bFace, std::shared_ptr<MaterialCache> ptrHash = nullptr);
public:
    // ---
    iteratorUuid InsertUuid(const MbUuid& key, Material* value)
    { return m_dataId.insert(std::pair<const MbUuid, Material*>(key, value)).first; }

    iteratorUuid FindUuid(const MbUuid& key)
    { return m_dataId.find(key); }

    bool IsEmptyUuid() const
    { return m_dataId.empty(); }

    Material* GetValueUuid(const MbUuid& key) const
    {
        auto iter = m_dataId.find(key);
        if (iter == m_dataId.end())
            return nullptr;
        return iter->second;
    }

    // ---
    iteratorColor InsertColor(const MbColor* key, Material* value)
    { return m_dataAttrColor.insert(std::pair<const MbColor*, Material*>(key, value)).first; }

    iteratorColor FindColor(const MbColor* key)
    { return m_dataAttrColor.find(key); }

    bool IsEmptyColor() const
    { return m_dataAttrColor.empty(); }

    Material* GetValueColor(const MbColor* key) const
    {
        auto iter = m_dataAttrColor.find(key);
        if (iter == m_dataAttrColor.end())
            return nullptr;
        return iter->second;
    }
    // ---
    iteratorVisual InsertVisual(const MbVisual* key, Material* value)
    { return m_dataAttrVisual.insert(std::pair<const MbVisual*, Material*>(key, value)).first; }

    iteratorVisual FindVisual(const MbVisual* key)
    { return m_dataAttrVisual.find(key); }

    bool IsEmptyVisual() const
    { return m_dataAttrVisual.empty(); }

    Material* GetValueVisual(const MbVisual* key) const
    {
        auto iter = m_dataAttrVisual.find(key);
        if (iter == m_dataAttrVisual.end())
            return nullptr;
        return iter->second;
    }

    Material* GetValueIsSame(const MbVisual* key) const
    {
        for (auto it : m_dataAttrVisual)
        {
            if (it.first->IsSame(*key))
                return it.second;
        }
        return nullptr;
    }

private:
    std::map<const MbUuid, Material*> m_dataId;
    std::map<const MbColor*, Material*> m_dataAttrColor;
    std::map<const MbVisual*, Material*> m_dataAttrVisual;
};
typedef std::shared_ptr<MaterialCache> MaterialCachePtr;

} // namespace VSN

#endif /* __VSN_MATERIAL_H */
