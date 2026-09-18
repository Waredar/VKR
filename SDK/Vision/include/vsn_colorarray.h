////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс Image обеспечивает аппаратно-независимое изображение.
           \en Image class provides a device-independent image. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_COLORARRAY_H
#define __VSN_COLORARRAY_H

#include <vsn_color.h>
#include <vsn_namespace.h>
#include <vsn_global.h>

namespace VSN {

class ColorsArrayPrivate;
/* ColorsArray */
class VSN_CLASS ColorsArray
{
public:
    ColorsArray();
    ColorsArray(std::initializer_list<Color> list);
    ColorsArray(const ColorsArray& other);
    ~ColorsArray();
public:
    // вставить в конец масиива
    void PushBack(const Color& color);
    // вставить перед элементом под индексом
    void Insert(const Color& color, size_t index);

    Color Get(size_t index) const;
    void Set(size_t index, const Color& color);

    void Remove(size_t index);
    size_t Count()const;
public:
    ColorsArray & operator = (const ColorsArray&);
    bool operator == (const ColorsArray&) const;
private:
    VSN_DECLARE_PRIVATE(ColorsArray);
};

} // namespace VSN

#endif // __VSN_COLORARRAY_H
