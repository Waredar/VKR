#ifndef MODEL_TREE_LINEARIZED_H
#define MODEL_TREE_LINEARIZED_H

#include <conv_model_document.h>
#include <mb_matrix.h>
#include <solid.h>
#include <vector>


//------------------------------------------------------------------------------
// Данные терминатора
// ---
struct TerminatorData
{
  int type;
  double parameter;
  double sizeX;
  double sizeY;
  bool sameDirection;
};


//------------------------------------------------------------------------------
// Данные кривой с терминаторами
// ---
struct DecoratedCurveData
{
  int curveType;
  std::vector<TerminatorData> terminators;
};


//------------------------------------------------------------------------------
// Данные размера
// ---
struct DimensionData
{
  double value;
  double valuePlus;
  double valueMinus;
  bool isRangeSet;
  bool isValueDefined;
  std::vector<DecoratedCurveData> decoratedCurves;
};


//------------------------------------------------------------------------------
// Контейнер элементов с вхождениями
// ---
template <typename ReferencedItemType>
class LinearizedContainer {
  
  ReferencedItemType item;
  mutable std::vector<MbMatrix3D> references;
public:
  // Конструктор по умолчанию
  LinearizedContainer() = default;

  // Конструктор копирования по умолчанию
  LinearizedContainer(const LinearizedContainer& i) = default;

  // Конструктор
  LinearizedContainer(const ReferencedItemType& it)
    : item( it )
    , references() {
  }

  // Оператор сравнения
  bool operator ==(const LinearizedContainer& to) const {
    return item == to.item;
  }

  // Получить элемент-ключ
  ReferencedItemType Item() const {
    return item;
  }

  // Получить число вхождений
  size_t ReferencesCount() const {
    return references.size();
  }

  // Получить матрицу вхождения по индексу
  MbMatrix3D Reference( size_t index ) const {
    MbMatrix3D result;
    if ( index < ReferencesCount() )
      result = references[index];
    return result;
  }

  // Добавить матрицу вхождения
  void AddReference( const MbMatrix3D& matr ) {
    references.push_back( matr );
  }
};

typedef std::vector<LinearizedContainer<ModelPartPtr>> PartsLinearized;
typedef std::vector<LinearizedContainer<ModelAssemblyPtr>> AssembliesLinearized;
typedef std::vector<LinearizedContainer<c3d::SolidSPtr>> SolidsLinearized;

//------------------------------------------------------------------------------
// Документ
// ---
class CONV_CLASS LinearizedTreeDocument : public C3dModelDocument
{
  PartsLinearized parts;
  AssembliesLinearized assemblies;
  SolidsLinearized solids;
  std::vector<SPtr<MbCurve3D>> spaceCurves;
  std::vector<SPtr<MbMesh>> meshes;
  vector_of_annotation annotations;
  vector_of_annotation techReq;

  bool calculateMIP;
  bool sliceSolids;

public:
  // Конструктор
  LinearizedTreeDocument();  
  // Деструктор
  ~LinearizedTreeDocument();

  PartsLinearized GetPartsList() const;

  AssembliesLinearized GetAssembliesList() const;

  // Заполнить данные
  void FillLinearizedData();

  private:
  // Заполнены ли данные
  bool IsFilled();

  bool GetSolid( const size_t ind, c3d::SolidSPtr& sld ) const;
  
  void SetSliceSolids( const bool val ) { sliceSolids = val; }

  // Заполнить списки компонент
  void FillComponents();
  // Заполнить списки объектов
  void FillObjectsFromComponents();
  // Обработать сборку со вставками
  void ProcessAssembly( ModelAssemblyPtr assm, const MbMatrix3D & matr );
  // Добавить деталь
  void AddPart( ModelPartPtr prt, const MbMatrix3D & matr );
  // Добавить сборку
  void AddAssembly( ModelAssemblyPtr assm, const MbMatrix3D & matr );
  // Добавить тело
  void AddSolid( c3d::SolidSPtr sld, const MbMatrix3D & matr );
  // Выдать данные размера
  void GetPmiDimensionData( MaDimension & dimension, DimensionData & dimData );
  // Сбросить данные размера
  void UnsetPmiDimensionData( DimensionData & dimData );
  // Выдать данные кривой с терминаторами
  void GetPmiDecoratedCurveData( MaDecoratedCurve & decoratedCurve, DecoratedCurveData & decCurveData );
  // Выдать данные терминатора
  void GetPmiTerminatorData( MaTerminatorSymbol & terminator, TerminatorData & termData );
  // Выдать идентификатор
  bool GetCadItemIdentifier( const MbAttributeContainer& item, ptrdiff_t & id );
  // Резка тела координатными плоскостями
  void SolidPlaneCutting( const MbSolid & solid, std::vector<MbResultType> & cutRes );
  // Резка тела
  MbResultType SolidCut( const MbSolid & solid, const MbSurface & surf, bool forward );
};

#endif //MODEL_TREE_LINEARIZED_H