////////////////////////////////////////////////////////////////////////////////
/**
    \file
    \brief \ru Общий узел 3D геометрического преобразования.
           \en NO TRANSLATION. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_TRANSFORM_H
#define __VSN_TRANSFORM_H

#include <vsn_feature.h>
#include <vsn_matrix3d.h>

namespace VSN {

namespace Features
{

class TransformPrivate;
//------------------------------------------------------------------------------
/** \brief  \ru Общий узел 3D геометрического преобразования.
            \en NO TRANSLATION. \~
    \details  \ru  Этот узел определяет геометрическое трехмерное преобразование
                   в основе которого лежит математическая матрица преобразование. \n.
              \en  NO TRANSLATION. \n \~
    \ingroup Vision_Transforms
*/
// ---
class VSN_CLASS Transform : public Feature
{
    VSN_OBJECT(Transform);
    VSN_PROP_READ_WRITE_NOTIFY(matrix, GetMatrix, SetMatrix, MatrixModified)
public:
    /// \ru Конструктор по умолчанию. \en Constructor. \~
    explicit Transform(Node* pParent = nullptr);
    /// \ru Конструктор с параметрами перемещения. \en NO TRANSLATION. \~
    Transform(const Point3DF& origin, Node* pParent = nullptr);
    /// \ru Конструктор с параметрами преобразования. \en NO TRANSLATION. \~
    Transform(const Point3DF& origin, float angleX, float angleY, float angleZ, Node* pParent = nullptr);
    /// \ru Конструктор с параметрами преобразования. \en NO TRANSLATION. \~
    Transform(float angleX, float angleY, float angleZ, Node* pParent = nullptr);
    /// \ru Конструктор с параметрами преобразования. \en NO TRANSLATION. \~
    Transform(const Matrix3DF& m, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor.
    virtual ~Transform();
public:
    /// \ru Вернуть математическую матрицу. \en NO TRANSLATION. \~
    Matrix3DF GetMatrix() const;
public:
    VSN_SLOT(Public, SetMatrix, void SetMatrix(const Matrix3DF& matrix))
    VSN_SLOT(Public, Move,      void Move(const Vector3DF& v))
    VSN_SLOT(Public, Scale,     void Scale(float x, float y, float z))
    VSN_SLOT(Public, Rotate,    void Rotate(float x, float y, float z))
public:
    VSN_SIGNAL(Public, MatrixModified, void MatrixModified())
protected:
    /// \ru Приватный конструктор для наследников. \en Private constructor for inheritors. \~
    explicit Transform(TransformPrivate& dd, Node* pParent = nullptr);
private:
    virtual NCreatedModificationBasicPtr CreateNodeModification() const override;
private:
    VSN_DECLARE_EX_PRIVATE(Transform);
};

} // namespace Features

} // namespace VSN

#endif // __VSN_TRANSFORM_H
