////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс SizeI описывает размер и использует целочисленную точность.
         \en SizeI class describes a size and uses an integer precision. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_SIZE_H
#define __VSN_SIZE_H

#include <vsn_global.h>

namespace VSN {

//----------------------------------------------------------------------------
//
/** \brief \ru Класс SizeI описывает размер и использует целочисленную точность.
           \en SizeI class describes a size and uses an integer precision. \~
    \details \ru SizeI определяет ширину и высоту. Он может быть инициализирован в конструкторе 
                 или изменен с помощью функций SetWidth(), SetHeight(), а также использует 
                 арифметические операторы. SizeI можно управлять, непосредственно изменив 
                 его значения путем получения ссылок на ширину и высоту. Ширину 
                 и высоту можно инициализировать функциями или через конструктор. Метод IsValid() определяет 
                 правильный размер: у правильного размер ширина и высота должны быть больше нуля.
                 Функция IsEmpty() возвращает true, если ширина и высота меньше или равны нулю, 
                 а функция IsNull() возвращает true, если ширина и высота равны нулю.\n
             \en SizeI class defines a width and height. It can be initialized in constructor
                 or changed with SetWidth(), SetHeight() functions, and also uses the arithmetic operators.
                 SizeI can be managed directly changing its values by receiving the references to width and
                 heights. The width and height can be initialized with functions or with constructor.
                 IsValid() method defines the correct size: the correct size must have a width and height
                 greater than 0. IsEmpty() function returns true if the width and height are less than or
                 equal to 0, and IsNull() function returns true if the width and height are 0. \n \~
    \ingroup Vision_Mathematic
*/
// ---
class VSN_CLASS SizeI
{
public:
    /// \ru Конструктор по умолчанию. Создает недопустимый размер, т. е. IsValid() возвращает false. \en Default constructor that creates invalid size, i.e. IsValid() returns false. \~
    SizeI();
    /// \ru Конструктор с заданием ширины и высоты. \en Constructor with setting width and height. \~
    SizeI(int w, int h);
public:
    /// \ru Возвращает true, если ширина и высота равны 0, в противном случае возвращает false. \en Returns true if width and height are 0 otherwise returns false. \~
    bool IsNull() const; 
    /// \ru Возвращает true, если ширина и высота меньше или равны 0, в противном случае возвращает false.\en Returns true if width and height are less than or equal to 0 otherwise returns false. \~
    bool IsEmpty() const;
    /// \ru Возвращает true, если ширина и высота равны или больше 0, в противном случае возвращает false. \en Returns true if width and height are greater than or equal to 0 otherwise returns false. \~
    bool IsValid() const;

    /// \ru Возвращает ширину. \en Returns width. \~
    int GetWidth() const;
    /// \ru Возвращает высоту. \en Returns height. \~
    int GetHeight() const;
  
    /// \ru Установить ширину. \en Sets width. \~
    void SetWidth(int w);
    /// \ru Установить высоту. \en Sets height. \~
    void SetHeight(int h);

    /// \ru Возвращает ссылку на ширину. \en Returns reference to width. \~
    int& InitWidth();
    /// \ru Возвращает ссылку на высоту. \en Returns reference to height. \~
    int& InitHeight();

    /// \ru Добавляет указанный размер к этому размеру и возвращает ссылку на этот размер. \en Adds the specified size to this size and returns reference to this size. \~
    SizeI& operator += (const SizeI&);
    /// \ru Вычитает заданный размер из этого размера и возвращает ссылку на этот размер. \en Subtracts the given size from this size and returns reference to this size. \~
    SizeI& operator -= (const SizeI&);
    /// \ru Умножает размер на указанное число. \en Multiplies size by the specified number. \~
    const SizeI operator *= (float);

    /// \ru Возвращает true, если указанный размер и этот равны, в противном случае возвращает false. \en Returns true if the specified size and this one are equal otherwise returns false. \~
    bool operator == (const SizeI&);
    /// \ru Возвращает true, если указанный размер и этот отличны, в противном случае возвращает false. \en Returns true if the specified size and this one are different otherwise returns false. \~
    bool operator != (const SizeI&);

    /// \ru Возвращает сумму указанного размера и этого, каждый компонент добавляется отдельно. \en Returns sum of the specified size and this one. Each component is added separately. \~
    const SizeI operator + (const SizeI&);
    /// \ru Возвращает разность из этого размера и указанного, каждый компонент вырезается отдельно. \en Returns difference between this size and the specified one. Each component is subtracted separately. \~
    const SizeI operator - (const SizeI&);
    /// \ru Возвращает произведение двух размеров с указанным числом. \en Returns composition of two sizes with the specified number. \~
    //  const SizeI operator * (float);
    friend VSN_FUNC_EX const SizeI operator * (const SizeI &s, float c);
private:
    int m_width;  ///< \ru Ширина размера. \en SizeI width.
    int m_height; ///< \ru Высота размера. \en SizeI height.
};


//----------------------------------------------------------------------------
//
/** \brief \ru Класс SizeI описывает размер и использует точность с плавающей точкой.
           \en SizeI class describes a size and uses an floating precision. \~
    \details \ru SizeI определяет ширину и высоту. Он может быть инициализирован в конструкторе 
                 или изменен с помощью функций SetWidth(), SetHeight(), а также использует
                 арифметические операторы. SizeI также можно управлять, непосредственно изменив 
                 его значения путем получения ссылок на ширину и высоту. Ширину 
                 и высоту можно инициализировать функциями или через конструктор. Метод IsValid() определяет 
                 правильный размер (у правильного размер ширина и высота должны быть больше нуля). 
                 Функция IsEmpty() возвращает true, если ширина и высота меньше или равны нулю, 
                 а функция IsNull() возвращает true, если ширина и высота равны нулю.\n
             \en SizeI class defines a width and height. It can be initialized in constructor
                 or changed with SetWidth(), SetHeight() functions, and also uses the arithmetic operators.
                 SizeI can be managed directly changing its values by receiving the references to width and
                 heights. The width and height can be initialized with functions or with constructor.
                 IsValid() method defines the correct size: the correct size must have a width and height
                 greater than 0. IsEmpty() function returns true if the width and height are less than or
                 equal to 0, and IsNull() function returns true if the width and height are 0. \n \~
    \ingroup Vision_Mathematic
*/
// ---
class VSN_CLASS SizeF
{
public:
    /// \ru Конструктор по умолчанию. Создает недопустимый размер, т. е. IsValid() возвращает false. \en Default constructor that creates invalid size, i.e. IsValid() returns false. \~
    SizeF();
    /// \ru Конструктор с заданием размера ширины и высоты с целочисленной точностью. \en Constructor with setting size width and height with integer precision. \~
    SizeF(const SizeI& sz);
    /// \ru Конструктор с заданием ширины и высоты с плавающей точностью. \en Constructor with setting size width and height with floating precision. \~
    SizeF(float w, float h);
public:
    /// \ru Возвращает значение true, если ширина и высота равны 0.0, в противном случае возвращает false. \en Returns true if width and height are 0.0 otherwise returns false. \~
    bool IsNull() const;
    /// \ru Возвращает true, если ширина и высота меньше или равны 0, в противном случае возвращает false. \en Returns true if width and height are less than or equal to 0 otherwise returns false. \~
    bool IsEmpty() const;
    /// \ru Возвращает true, если ширина и высота равны или больше 0, в противном случае возвращает false. \en Returns true if width and height are greater than or equal to 0 otherwise returns false. \~
    bool IsValid() const;

    /// \ru Возвращает ширину. \en Returns width. \~
    float GetWidth() const;
    /// \ru Возвращает высоту. \en Returns height . \~
    float GetHeight() const;

    /// \ru Установить ширину. \en Sets width. \~
    void SetWidth(float w); 
    /// \ru Установить высоту. \en Sets height. \~
    void SetHeight(float h);

    /// \ru Возвращает ссылку на ширину. \en Returns reference to width. \~
    float& InitWidth();
    /// \ru Возвращает ссылку на высоту. \en Returns reference to height. \~
    float& InitHeight();

    /// \ru Добавляет указанный размер к этому размеру и возвращает ссылку на этот размер. \en Adds the specified size to this size and returns reference to this size. \~
    SizeF& operator+=(const SizeF&);
    /// \ru Ввычитает заданный размер из этого размера и возвращает ссылку на этот размер. \en Subtracts the given size from this size and returns reference to this size. \~
    SizeF& operator-=(const SizeF&);
    /// \ru Умножает ширину и высоту на заданную величину и возвращает ссылку на размер. \en Multiplies width and height by the given value, and returns reference to size. \~
    SizeF& operator*=(float c);
    /// \ru Делит ширину и высоту на заданный делитель и возвращает ссылку на размер. \en Divides width and height by the given divider and returns reference to size. \~
    SizeF& operator/=(float c);

    /// \ru Возвращает true, если указанный размер и этот равны, в противном случае возвращает false. \en Returns true if the specified size and this one are equal otherwise returns false. \~
    friend bool operator==(const SizeF&, const SizeF&);
    /// \ru Возвращает true, если указанный размер и этот отличны, в противном случае возвращает false. \en Returns true if the specified size and this one are different otherwise returns false. \~
    friend bool operator!=(const SizeF&, const SizeF&);
    /// \ru Возвращает сумму указанного размера и этого, каждый компонент добавляется отдельно. \en Returns sum of the specified size and this one. Each component is added separately. \~
    friend const SizeF operator+(const SizeF&, const SizeF&);
    /// \ru Возвращает разность из этого размера и указанного, каждый компонент вырезается отдельно. \en Returns difference between this size and the specified one. Each component is subtracted separately. \~
    friend const SizeF operator-(const SizeF&, const SizeF&);
    /// \ru Умножает данный размер на заданное значение и возвращает результат. \en Multiplies the given size by the given value and returns result. \~
    friend const SizeF operator*(const SizeF&, float);
    /// \ru Умножает данный размер на заданное значение и возвращает результат. \en Multiplies the given size by the given value and returns result. \~
    friend const SizeF operator*(float, const SizeF&);
    /// \ru Делит данный размер на данный делитель и возвращает результат. \en Divides the given size by the given divider and returns result. \~
    friend const SizeF operator/(const SizeF&, float);
private:
  float m_dbWidth;   ///< \ru Ширина размера. \en SizeI width. \~
  float m_dbHeight;  ///< \ru Высота размера. \en SizeI height. \~
};

} // namespace VSN

#endif // __VSN_SIZE_H
