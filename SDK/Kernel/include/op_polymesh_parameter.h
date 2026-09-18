////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Параметры операций над полигональными сетками с топологией.
         \en Parameters of operations on the polygonal meshes with topology. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __OP_POLYMESH_PARAMETERS_H
#define __OP_POLYMESH_PARAMETERS_H

#include <math_define.h>
#include <mb_placement3d.h>
#include <mb_data.h>
#include <templ_sptr.h>
#include <topology.h>
#include <curve3d.h>

class MbPolymesh;
class MbFaceShell;
class MbHalfedgeAttrSizetEdge;
class MbHalfedgeAttrDoubleEdge;
class MbHalfedgeAttrBoolVertex;
class MbPolyline3D;

//------------------------------------------------------------------------------
/** \brief \ru Параметры ремешинга.
           \en Remeshing parameters. \~
    \details \ru Параметры ремешинга.
             \en Remeshing parameters.
    \ingroup Polygonal_Objects
    \warning \ru В разработке.
           \en Under development. \~
*/
// ---
class MATH_CLASS MbRemeshParams
{
public:
  //------------------------------------------------------------------------------
  /** \brief \ru Перечисление методов ремешинга.
             \en Enumeration for remeshing methods. \~
  */
  // ---
  enum class MethodRemesh
  {
    incrementalUniform,   ///< \ru Однородный инкрементальный ремешинг. \en Uniform incremental remeshing.
    incrementalCurvature  ///< \ru Инкрементальный ремешинг по кривизне. \en Curvature incremental remeshing.
  };

private:
  MethodRemesh       _method;       ///< \ru Метод ремешинга. \en A remeshing method.
  double             _targetLength; ///< \ru Целевой размер ребра фасета для однородного метода. \en A target facet edge length for the uniform method.
  double             _tolCurvature; ///< \ru Относительная точность для метода по кривизне. \en A relative tolerance for the curvature method.
  double             _angleEdge;    ///< \ru Угол для автоматической разбивки ребер сегментации по сломам (градусы), если меньше нуля - не учитывается. \en A angle for automatic segmentation edges splitting (degrees). It is not used if negative. \~
  c3d::IndicesVector _fixedEdges;   ///< \ru Фиксированные ребра сетки. \en Mesh edges to be fixed.

public:
  mutable IProgressIndicator * _progress;  ///< \ru Индикатор прогресса выполнения операции. \en A progress indicator of the operation.

public:
  /// \ru Конструктор. \en Constructor.
  MbRemeshParams( IProgressIndicator * prog = nullptr );
  /// \ru Деструктор. \en Destructor.
  ~MbRemeshParams();

  /// \ru Инициализировать как однородный инкрементальный ремешинг. \en Initialize as a uniform incremental remeshing.
  void InitIncrementalUniform( double targetLength, const c3d::IndicesVector & fixedEdges, double angleEdge = -1. );
  /// \ru Инициализировать как инкрементальный ремешинг по кривизне. \en Initialize as an incremental remeshing by curvature.
  void InitIncrementalCurvature( double tolCurvature, const c3d::IndicesVector & fixedEdges, double angleEdge = -1. );
  ///< \ru Получить целевой размер ребра фасета. \en Get the target facet edge length.
  double GetTargetLength() const { return _targetLength; }
  ///< \ru Получить относительная точность. \en Get the relative tolerance.
  double GetCurvatureTolerance() const { return _tolCurvature; }
  ///< \ru Получить угол для разбивки ребер сегментации. \en Get the angle for segmentation edges splitting.
  double GetAngleEdge() const { return _angleEdge; }
  ///< \ru Получить способ вычисления. \en Get the calculation method.
  MethodRemesh GetMethod() const { return _method; }
  ///< \ru Получить фиксированные ребра. \en Get fixed edges.
  const c3d::IndicesVector & GetFixedEdges() const { return _fixedEdges; }
  ///< \ru Зафиксировать открытые границы. \en Fix open borders.
  void FixOpenBorders( MbPolymesh & mesh );

  OBVIOUS_PRIVATE_COPY( MbRemeshParams );
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры линеаризации оболочки.
           \en Parameters for the shell linearization. \~
    \details \ru Параметры линеаризации оболочки.
                 Для каждой заданной группы граней будет создан один регион в полигональном объекте.
             \en Parameters for the shell linearization.
                 Creates one polymesh region for every given face group. \~
    \ingroup Polygonal_Objects
    \warning \ru В разработке.
           \en Under development. \~
*/
// ---
class MATH_CLASS MbShellLinearizationParams
{
private:
  bool                             _b2d;         ///< \ru Флаг создания атрибута параметров. \en A parametrers attribute creation flag. \~
  bool                             _bNormals;    ///< \ru Флаг создания атрибута нормалей. \en A normals attribute creation flag. \~
  bool                             _bCurvatures; ///< \ru Флаг создания атрибута кривизн. \en A curvatures attribute creation flag. \~
  MbStepData                       _stepData;    ///< \ru Данные для расчета шага. \en Data for the step calculation. \~
  std::vector<c3d::IndicesVector>  _faceGroups;  ///< \ru Группы граней. \en Face groups.
  c3d::IndicesVector               _fixedEdges;  ///< \ru Фиксированные ребра оболочки. \en Constrained shell edges.

public:
  /// \ru Конструктор. \en Constructor.
  MbShellLinearizationParams( const MbStepData & data, bool b2d, bool bNormals, bool bCurvatures, const std::vector<c3d::IndicesVector> & faceGroups, const c3d::IndicesVector & fixedEdges );
  /// \ru Конструктор. \en Constructor.
  MbShellLinearizationParams( const MbStepData & data, bool b2d, bool bNormals, bool bCurvatures, const std::vector<std::vector<MbItemIndex>> & faceGroups );
  /// \ru Конструктор. \en Constructor.
  MbShellLinearizationParams( const MbStepData & data, bool b2d, bool bNormals, bool bCurvatures, const MbFaceShell & shell, const std::vector<std::vector<const MbFace*>> & faceGroups );
  /// \ru Деструктор. \en Destructor.
  ~MbShellLinearizationParams() {}

  // \ru Получить данные для расчета шага. \en Get data for the step calculation. \~
  const MbStepData & GetStepData() const { return _stepData; }
  // \ru Получить группы граней. \en Get face groups. \~
  const std::vector<c3d::IndicesVector> & GetFaceGroups() const { return _faceGroups; }
  // \ru Получить фиксированные ребра. \en Get constrained edges. \~
  const c3d::IndicesVector & GetFixedEdges() const { return _fixedEdges; }
  // \ru Нужно ли создавать атрибут параметров. \en Check if parameters attribute should be created. \~
  bool IsUvNeeded() const { return _b2d; }
  // \ru Нужно ли создавать атрибут нормалей. \en Check if normals attribute should be created. \~
  bool IsNormalsNeeded() const { return _bNormals; }
  // \ru Нужно ли создавать атрибут кривизн. \en Check if curvatures attribute should be created. \~
  bool IsCurvaturesNeeded() const { return _bCurvatures; }

  OBVIOUS_PRIVATE_COPY( MbShellLinearizationParams );
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры операции расчета кривизн полигональной сетки.
           \en Parameters for mesh curvature calculation. \~
    \details \ru Параметры операции расчета кривизн полигональной сетки.
                 Возможны два метода - с помощью дискретного дифференциального оператора, и с помощью вписывания полиномиальной поверхности
                 в окрестность вершины. Количество соседей для второго метода должно быть в пределах от 1 до 10.
             \en Parameters for mesh curvature calculation. 
                 There are two methods are possible - by discrete differential operator and by polynomial surface fitting.
                 Number of neighbors for second method must be in the range from 1 to 10. \~
    \ingroup Polygonal_Objects
*/
// ---
class MATH_CLASS MbMeshCurvatureParams
{
public:
  //------------------------------------------------------------------------------
  /** \brief \ru Перечисление методов расчета кривизн полигональной сетки.
  */
  // ---
  enum class MethodCalcCurvatures
  {
    byDiscrDiffOperators, ///< \ru Дискретный дифференциальный оператор. \en Discrete differential operator.
    byApproxPolynom       ///< \ru Аппроксимация полиномиальной поверхностью. \en Polynomial surface fitting.
  };

private:
  MethodCalcCurvatures _method;        ///< \ru Метод расчета. \en Calculation method.
  size_t               _nNeighborRing; ///< \ru Количество соседей для аппроксимации поверхностью. \en Number of neighbors for surface fitting.

public:
  /// \ru Конструктор. \en Constructor.
  MbMeshCurvatureParams()
    : _method       ( MethodCalcCurvatures::byDiscrDiffOperators )
    , _nNeighborRing( 0                                          )
  {}
  /// \ru Деструктор. \en Destructor.
  ~MbMeshCurvatureParams() {}

  /// \ru Инициализировать метод дискретного оператора. \en Initialize discrete operator method.
  void InitOperatorMethod()
  {
    _method = MethodCalcCurvatures::byDiscrDiffOperators;
    _nNeighborRing = 0;
  }
  /// \ru Инициализировать метод полиномиальной поверхности. \en Initialize polynomial surface method.
  void InitPolynomMethod( size_t nRing )
  {
    _method = MethodCalcCurvatures::byApproxPolynom;
    _nNeighborRing = nRing;
  }

  ///< \ru Получить способ вычисления. \en Get calculation method.
  MethodCalcCurvatures GetMethod() const { return _method; }
  ///< \ru Получить количество соседей. \en Get number of neighbors.
  size_t GetRingsNumber() const { return _nNeighborRing; }

  OBVIOUS_PRIVATE_COPY( MbMeshCurvatureParams )
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры драпировки оболочки тканью.
           \en Parameters for the shell draping. \~
  \details \ru Параметры драпировки оболочки тканью. \n
                 Параметры содержат информацию о положении развёртки и свойствах материала.
           \en Parameters for the shell draping. \n
               Parameters contain information about the scan position and material properties. \~
  \ingroup Shell_Building_Parameters
  \warning \ru В разработке.
           \en Under development. \~
*/
// ---
class MATH_CLASS MbDrapeShellParams
{
public:
  //------------------------------------------------------------------------------
  /** \brief \ru Перечисление для типа констрейна для кривой.
             \en Constraint curve type. \~
    \details \ru Перечисление для типа констрейна для кривой.
             \en Constraint curve type. \~
  */
  // ---
  enum class ConstraintCurveType
  {
    geodesic, ///< \ru Геодезическая. \en Geodesic.
    curve     ///< \ru Заданная кривая. \en Given curve.
  };

  //------------------------------------------------------------------------------
  /** \brief \ru Перечисление для угла между основой ткани и кривой-кострейна.
             \en Fiber angle from a constraint curve. \~
    \details \ru Перечисление для угла между основой ткани и кривой-кострейна.
             \en Fiber angle from a constraint curve. \~
  */
  // ---
  enum class AngleFromCurveType
  {
    degrees0,      ///< \ru Ноль градусов. \en Zero degrees.
    degreesPlus45, ///< \ru 45 градусов. \en 45 degrees.
    degreesMinus45 ///< \ru Минус 45 градусов. \en Minus 45 degrees.
  };

private:
  double                _epsSew;              ///< \ru Точность сшивки сетки. \en Sew tolerance. \~
  double                _cellSize;            ///< \ru Размер ячейки ткани. \en Fiber cell size. \~
  ConstraintCurveType   _constraintCurveType; ///< \ru Тип кривой-констрейна. \en Constraint curve type. \~
  AngleFromCurveType    _angleFromCurveType;  ///< \ru Угол между основой ткани и кривой. \en Fiber angle from a curve. \~
  MbPlacement3D         _place;               ///< \ru Локальная система координат развернутой поверхности. \en The local coordinate system for the result surface. \~
  MbStepData            _stepData;            ///< \ru Данные для расчета шага. \en Data for the step calculation. \~
  SPtr<MbPolymesh>      _mesh;                ///< \ru Линеаризация оболочки. \en Shell linearization. \~
  SPtr<const MbCurve3D> _firstStageRegion;    ///< \ru Кривая для приоритетной области. \en First stage region curve. \~
  SPtr<const MbCurve3D> _constrainCurve;      ///< \ru Кривая-констрейн. \en Constraint curve. \~

public:
  /// \ru Конструктор (только для внутреннего использования ). \en Constructor ( for internal usage only ).
  MbDrapeShellParams();

public:
  /// \ru Конструктор по параметрам. \en Constructor by parameters.
  MbDrapeShellParams( const MbFaceShell & shell, const MbStepData & stepData, double epsSew = METRIC_EPSILON );
  /// \ru Деструктор. \en Destructor.
  ~MbDrapeShellParams();

public:
  // \ru Валидны ли данные. \en Is data valid.
  bool IsValid() const;
  // \ru Инициализировать данные. \en Initialize data.
  void Init( const MbPlacement3D &     place, 
                   ConstraintCurveType constrCurveType, 
                   AngleFromCurveType  angFromCurveType, 
                   double              cellSize, 
             const MbCurve3D *         pConstraintCurve = nullptr,
             const MbCurve3D *         pFirstStageRegion = nullptr);

  // \ru Получить линеаризацию оболочки. \en Get shell linearization. \~
  const SPtr<MbPolymesh> & GetMesh() const { return _mesh; }
  // \ru Получить приоритетную область. \en Get the first stage region. \~
  const SPtr<const MbCurve3D> & GetFirstStageRegion() const { return _firstStageRegion; }
  // \ru Получить для изменения приоритетную область. \en Get first stage region. \~
  SPtr<const MbCurve3D> & SetFirstStageRegion() { return _firstStageRegion; }
  // \ru Получить кривую-констрейн. \en Get constraint curve. \~
  const SPtr<const MbCurve3D> & GetConstraintCurve() const { return _constrainCurve; }
  // \ru Получить для изменения кривую-констрейн. \en Get constraint curve. \~
  SPtr<const MbCurve3D> & SetConstraintCurve() { return _constrainCurve; }
  // \ru Получить данные для расчета шага. \en Get data for step calculation. \~
  const MbStepData & GetStepData() const { return _stepData; }
 
  /// \ru Установить локальную систему координат развернутой поверхности сетки. \en Set the local coordinate system for a mesh unwrapping. \~
  void SetPlacement( const MbPlacement3D & pl ) { _place.Init( pl ); }
  // \ru Получить локальную систему координат развернутой поверхности сетки. \en Get the local coordinate system for a mesh unwrapping. \~
  const MbPlacement3D & GetPlacement() const { return _place; }
  /// \ru Установить размер ячейки. \en Set cell size. \~
  void SetCellSize( double cellSize ) { _cellSize = cellSize; }
  // \ru Получить размер ячейки. \en Get cell size. \~
  double GetCellSize() const { return _cellSize; }
  /// \ru Установить тип кривой-констрейна. \en Set constraint curve type. \~
  void SetConstraintCurveType( ConstraintCurveType type ) { _constraintCurveType = type; }
  // \ru Получить тип кривой-констрейна. \en Get constraint curve type. \~
  ConstraintCurveType GetConstraintCurveType() const { return _constraintCurveType; }
  /// \ru Установить угол между основой ткани и кривой. \en Set fiber angle from the curve. \~
  void SetAngleFromCurveType( AngleFromCurveType type ) { _angleFromCurveType = type; }
  // \ru Получить угол между основой ткани и кривой. \en Get fiber angle from the curve. \~
  AngleFromCurveType GetAngleFromCurveType() const { return _angleFromCurveType; }

  // \ru Функции только для внутреннего использования. \en Functions for the internal usage only. 

  // \ru Получить для изменения линеаризацию оболочки. \en Get the shell linearization. \~
  SPtr<MbPolymesh> & SetMesh() { return _mesh; }
  // \ru Получить для изменения данные для расчета шага. \en Get data for the step calculation. \~
  MbStepData & SetStepData() { return _stepData; }
  // \ru Инициализировать линеаризацию оболочки. \en Initialize the shell linearization. \~
  void InitMesh( const MbFaceShell & shell, const MbStepData & stepData, double epsSew );
  /// \ru Установить точность сшивки. \en Set sew tolerance. \~
  void SetSewTolerance( double epsSew ) { _epsSew = epsSew; }
  // \ru Получить точность сшивки. \en Get sew tolerance. \~
  double GetSewTolerance() const { return _epsSew; }
  
  OBVIOUS_PRIVATE_COPY( MbDrapeShellParams );
}; // MbDrapeShellParams


//------------------------------------------------------------------------------
/** \brief \ru Результаты драпировки оболочки тканью.
           \en Shell draping results. \~
  \details \ru Результаты драпировки оболочки тканью. \n
               Содержат информацию о ячейках ткани в 3D и развертки в 2D.
           \en Shell draping results. \n
               Results contain information about 3D fiber cells and 2D unwrapping. \~
  \ingroup Shell_Building_Parameters
  \warning \ru В разработке.
           \en Under development. \~
*/
// ---
class MATH_CLASS MbDrapeShellResults
{
private:
  SPtr<MbPolymesh>                    _mesh;      ///< \ru Результат. \en The result. \~
  std::vector<c3d::SpacePointsVector> _sides;     ///< \ru Полилинии сторон ячеек. \en Cell sides polylines. \~
  std::vector<c3d::SpacePointsVector> _warp;      ///< \ru Полилинии для нулевой нити основы. \en Warp polylines. \~
  std::vector<c3d::SpacePointsVector> _weft;      ///< \ru Полилинии для нулевой нити утка. \en Weft polylines. \~
  MbHalfedgeAttrSizetEdge *           _pAttrId;   ///< \ru Атрибут индексов сторон ячеек. \en An attribute for cell sides indices. \~
  MbHalfedgeAttrDoubleEdge *          _pAttrAng;  ///< \ru Атрибут углов сторон ячеек. \en An attribute for cell sides angles. \~
  MbHalfedgeAttrBoolVertex *          _pAttrNode; ///< \ru Атрибут флагов узлов ткани. \en An attribute for fiber nodes flags. \~
  MbHalfedgeAttrSizetEdge *           _pAttrDir;  ///< \ru Атрибут направлений сторон ячеек ткани. \en An attribute for cell sides directions. \~

public:
  /// \ru Конструктор. \en Constructor.
  MbDrapeShellResults();
  /// \ru Деструктор. \en Destructor.
  ~MbDrapeShellResults();

  /// \ru Очистить данные. \en Clear data.
  void Clear();
  // \ru Получить результат. \en Get the result. \~
  const SPtr<MbPolymesh> & GetMesh() const { return _mesh; }
  // \ru Получить результат. \en Get the result. \~
  SPtr<MbPolymesh> & SetMesh() { return _mesh; }

  // \ru Является ли вершина узлом ткани. \en Is vertex a fiber node. \~
  bool IsNode( size_t iVx ) const;
  // \ru Получить угол деформации для ребра сетки. \en Get a deformation angle for the mesh edge. \~
  double GetEdgeAngle( size_t iEd ) const;
  // \ru Получить идентификатор полилинии для этого ребра сетки. \en Get a polyline index for the given mesh edge. \~
  size_t  GetSideId( size_t iEd ) const;
  /** \brief \ru Получить полилинии для главной нити основы.
            \en Get a polyline for the main warp thread. \~
   \details \ru Получить полилинии для главной нити основы.
                Эти полилинии идут от точки приложения в положительном и отрицательном направлении
                оси Х локальной системы координат.
            \en Get polyline for maGet a polyline for the main warp thread.
                Polylines go in a positive and negative direction along the X-axis of the local coordinate system.
 */
  const std::vector<c3d::SpacePointsVector> & GetWarp() const { return _warp; }
  /** \brief \ru Получить полилинии для главной нити утка.
             \en Get a polyline for the main weft thread. \~
    \details \ru Получить полилинии для главной нити утка.
                 Эти полилинии идут от точки приложения в положительном и отрицательном направлении
                 оси Y локальной системы координат.
             \en Get a polyline for the main weft thread.
                 Polylines go in a positive and negative direction along the Y-axis of the local coordinate system.
  */
  const std::vector<c3d::SpacePointsVector> & GetWeft() const { return _weft; }
  /** \brief \ru Получить полилинии для главной нити основы.
           \en Get a polyline for the main warp thread. \~
  \details \ru Получить полилинии для главной нити основы.
               Эти полилинии идут от точки приложения в положительном и отрицательном направлении
               оси Х локальной системы координат.
           \en Get a polyline for the main warp thread.
               Polylines go in a positive and negative direction along the X-axis of the local coordinate system.
*/
  std::vector<c3d::SpacePointsVector> & GetWarp() { return _warp; }
  /** \brief \ru Получить полилинии для главной нити утка.
             \en Get a polyline for the main weft thread. \~
    \details \ru Получить полилинии для главной нити утка.
                 Эти полилинии идут от точки приложения в положительном и отрицательном направлении
                 оси Y локальной системы координат.
             \en Get a polyline for the main weft thread. 
                 Polylines go in a positive and negative direction along the Y-axis of the local coordinate system.
  */
  std::vector<c3d::SpacePointsVector> & GetWeft() { return _weft; }
  /// \ru Получить полилинию для стороны ячейки. \en Get a cell side polyline.
  const std::vector<c3d::SpacePointsVector> & GetCellSides() const { return _sides; }
  /// \ru Получить полилинию для стороны ячейки. \en Get a cell side polyline.
  std::vector<c3d::SpacePointsVector> & GetCellSides() { return _sides; }
  /** \brief \ru Получить грань-развертку.
             \en Get an unwrapped face. \~
    \details \ru Получить грань-развертку.
                 Ее контур получается путем аппроксимации границы сеточной развертки.
             \en Get an unwrapped face.
                 This is a contour calculated by an approximation of the unwrapped mesh border.
    \param[in] tolApprox - \ru Точность аппроксимации.
                           \en An approximation tolerance. \~
    \param[out] unwrapped - \ru Грань-развертка.
                            \en An unwrapped face. \~
  */
  void GetUnwrapped( double tolApprox, c3d::FaceSPtr & unwrapped ) const;
  /** \brief \ru Получить полилинию разреза ткани на поверхности оболочки.
            \en Get a fiber cut polyline on the shell surface. \~
   \details \ru Получить полилинию разреза ткани на поверхности оболочки.
            \en Get a fiber cut polyline on the shell surface.
   \param[in] uv - \ru Начало прямой - линии разреза.
                   \en A cut line beginning. \~
   \param[in] dir - \ru Направление прямой - линии разреза.
                    \en A cut line direction. \~
   \param[out] polys - \ru Полилинии - отображение линии разреза на оболочку.
                       \en Polylines represented a line mapping to the shell. \~
 */
  void GetSplitPolylines( const MbCartPoint & uv, const MbVector & dir, std::vector<c3d::SpacePointsVector> & polys ) const;
  /** \brief \ru Получить атрибут направлений сторон ячеек.
             \en Get an attribute for cell sides directions. \~
   \details \ru Получить атрибут направлений сторон ячеек.
                Возможные значения:
                0 - вдоль основы, 1 - вдоль утка, 2 - против основы, 3 - против утка, SYS_MAX_T - не определено.
            \en Get an attribute for cell sides directions.
                Possible values are:
                0 - along warp, 1 - along weft, 2 - against warp, 3 - against weft, SYS_MAX_T - undefined.
 */
  const MbHalfedgeAttrSizetEdge * GetDirectionalAttribute() const { return _pAttrDir; }

  // \ru Инициализировать атрибуты сетки. \en Initialize the mesh attributes. \~
  void InitAttributes();

  OBVIOUS_PRIVATE_COPY( MbDrapeShellResults );
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры объединения полигональных объектов.
           \en Parameters for polymesh merging. \~
  \details \ru Параметры объединения полигональных объектов. \n
               Параметры содержат информацию о соответствующих рёбрах из объединяемых полигональных объектов, при объединении эти рёбра должны быть склеены.
               Первый компонент пары - индекс ребра топологии полигонального объекта, который копируется.
               Второй компонент пары - индекс ребра топологии полигонального объекта, который аккумулирует результат объединения.
           \en Parameters for polymesh merging. \n
               Parameters may contain information about corresponding edges from polymeshes being merged - these edges will be marked as twins.
               The first pair element is the edge index from the topology of a polymesh being copied.
               The second pair element is the edge index from the topology of a polymesh accumulating merged objects. \~
  \warning \ru В разработке.
           \en Under development. \~
*/
// ---
class MATH_CLASS MbMergePolymeshParams
{
private:
  c3d::IndicesPairsVector _edgePairs; ///< \ru Пары ребер, которые должны быть склеены. \en Pairs of edges being merged with each other. \~

public:
  /// \ru Конструктор. \en Constructor.
  MbMergePolymeshParams() : _edgePairs() {}
  /// \ru Конструктор по параметрам. \en Constructor by parameters.
  MbMergePolymeshParams( const c3d::IndicesPairsVector & edgePairs ) : _edgePairs( edgePairs ) {}
  /// \ru Деструктор. \en Destructor.
  ~MbMergePolymeshParams() {}

public:
  // \ru Получить пары соответствующих ребер. \en Get the pairs of corresponding edges. \~
  const c3d::IndicesPairsVector & GetEdgePairs() const { return _edgePairs; }
  // \ru Установить пары соответствующих ребер. \en Set the pairs of corresponding edges. \~
  void SetEdgePairs( const c3d::IndicesPairsVector & edgePairs ) { _edgePairs = edgePairs; }

  OBVIOUS_PRIVATE_COPY( MbMergePolymeshParams );
}; // MbMergePolymeshParams


//------------------------------------------------------------------------------
/** \brief \ru Параметры сглаживания полигональных объектов.
           \en Parameters for the polymesh smoothing. \~
  \details \ru Параметры сглаживания полигональных объектов. \n
               Параметры содержат информацию о коэффициентах сглаживания, методе сглаживания, максимальном числе итераций,
               наборе индексов фасетов для сглаживания.
           \en Parameters for the polymesh smoothing. \n
               The parameters contain information about the smoothing coefficients, the smoothing method, the maximum number of iterations 
               and the set of facet indices for smoothing. \~
  \ingroup Polygonal_Objects
  \warning \ru В разработке.
           \en Under development. \~
*/
// ---
class MATH_CLASS MbMeshSmoothingParams
{
public:
  //------------------------------------------------------------------------------
  /** \brief \ru Перечисление методов сглаживания.
             \en Enumeration for smoothing methods. \~
  */
  // ---
  enum class MethodSmoothMesh
  {
    smoothTaubin, ///< \ru Метод Таубина. \en Taubin's method.
    smoothLaplas  ///< \ru Метод Лапласа. \en Laplace method.
  };

private:
  MethodSmoothMesh   _method;      ///< \ru Метод сглаживания сетки. \en Mesh smoothing method.
  double             _lambda;      ///< \ru Коэффициент сжатия, используемый на нечетных шагах в "taubin smoothing". \en The compression factor used in odd steps in "taubin smoothing".
  double             _mu;          ///< \ru Коэффициент расширения, используемый на четных шагах в "taubin smoothing". \en The expansion factor used in even steps in "taubin smoothing".
  size_t             _maxIter;     ///< \ru Максимальное число итераций. \en Maximum iteration number.
  bool               _bFixBorders; ///< \ru Сохранять границы. \en Save borders.
  c3d::IndicesVector _facets;      ///< \ru Индексы фасетов. Если набор фасетов пустой, то сглаживается вся сетка. \en Facet indices to smooth. If the facet set is empty, the entire mesh is smoothed.
  c3d::IndicesVector _fixVertices; ///< \ru Индексы фиксированных вершин. \en Fixed vertex indices.

public:
  /// \ru Конструктор. \en Constructor.
  MbMeshSmoothingParams()
    : _method      ( MethodSmoothMesh::smoothTaubin )
    , _lambda      ( 0.33                           )
    , _mu          ( -0.34                          )
    , _maxIter     ( 100                            )
    , _bFixBorders ( true                           )
    , _facets      (                                )
    , _fixVertices (                                )
  {}
  /// \ru Конструктор по параметрам. \en Constructor by parameters.
  MbMeshSmoothingParams( MethodSmoothMesh           method, 
                         double                     lambda, 
                         double                     mu, 
                         size_t                     maxIter, 
                         bool                       bFixBorders, 
                         const c3d::IndicesVector & facets, 
                         const c3d::IndicesVector & fixVertices )
    : _method      ( method       )
    , _lambda      ( lambda       )
    , _mu          ( mu           )
    , _maxIter     ( maxIter      )
    , _bFixBorders ( bFixBorders  )
    , _facets      ( facets       )
    , _fixVertices ( fixVertices  )
  {}
  /// \ru Деструктор. \en Destructor.
  ~MbMeshSmoothingParams() {}

public:
  // \ru Установить метод сглаживания. \en Set the smoothing method. \~
  void SetMethod( MethodSmoothMesh method ) { _method = method; }
  // \ru Установить коэффициент сжатия. \en Set the compression factor. \~
  void SetLambda( double lambda ) { _lambda = lambda; }
  // \ru Установить коэффициент расширения. \en Set the expansion factor. \~
  void SetMu( double mu ) { _mu = mu; }
  // \ru Установить максимальное число итераций. \en Set the maximum iteration number. \~
  void SetMaxIter( size_t maxIter ) { _maxIter = maxIter; }
  // \ru Установить флаг сохранения границ. \en Set the save borders flag. \~
  void SetFixBorders( bool bFixBorders ) { _bFixBorders = bFixBorders; }
  // \ru Установить набор индексов фасетов для сглаживания. \en Set facet indices to smooth. \~
  void SetFacets( const c3d::IndicesVector & facets ) { _facets = facets; }
  // \ru Установить набор фиксированных вершин. \en Set the fixed vertex indices. \~
  void SetFixVertices( const c3d::IndicesVector & fixVertices ) { _fixVertices = fixVertices; }
  // \ru Получить метод сглаживания. \en Get the the smoothing method. \~
  MethodSmoothMesh GetMethod() const { return _method; }
  // \ru Получить коэффициент сжатия. \en Get the the compression factor. \~
  double GetLambda() const { return _lambda; }
  // \ru Получить коэффициент расширения. \en Get the expansion factor. \~
  double GetMu() const { return _mu; }
  // \ru Получить максимальное число итераций. \en Get the maximum iteration number. \~
  size_t GetMaxIter() const { return _maxIter; }
  // \ru Получить флаг сохранения границ. \en Get the save borders flags. \~
  bool GetFixBorders() const { return _bFixBorders; }
  // \ru Получить набор индексов фасетов для сглаживания. \en Get facet indices to smooth. \~
  const c3d::IndicesVector & GetFacets() const { return _facets; }
  // \ru Получить набор фиксированных вершин. \en Get the fixed vertex indices. \~
  const c3d::IndicesVector & GetFixVertices() const { return _fixVertices; }

  OBVIOUS_PRIVATE_COPY( MbMeshSmoothingParams );
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры проецирования полилинии на полигональный объект.
           \en Parameters for projecting a polyline on a polymesh. \~
  \details \ru Параметры проецирования полилинии на полигональный объект. \n
               Параметры содержат проецируемую полилинию.
           \en Parameters for projecting a polyline on a polymesh. \n
               Parameters contain a polyline to be projected. \~
  \warning \ru В разработке.
           \en Under development. \~
*/
// ---
class MATH_CLASS MbPolylinePolymeshProjectParams : public MbPrecision
{
private:
  const MbPolyline3D & _polyline;  ///< \ru Полилиния. \en Polyline. \~

public:
  /// \ru Конструктор по параметрам. \en Constructor by parameters.
  MbPolylinePolymeshProjectParams( const MbPolyline3D & polyline )
    : MbPrecision(          )
    , _polyline  ( polyline )
  {}
  /// \ru Деструктор. \en Destructor.
  ~MbPolylinePolymeshProjectParams() {}

public:
  // \ru Получить полилинию. \en Get the polyline. \~
  const MbPolyline3D & GetPolyline() const { return _polyline; }

  OBVIOUS_PRIVATE_COPY( MbPolylinePolymeshProjectParams );
};


//------------------------------------------------------------------------------
/** \brief \ru Результаты проецирования полилинии на полигональный объект.
           \en Results of projecting a polyline on a polymesh. \~
  \details \ru Результаты проецирования полилинии на полигональный объект. \n
               Результаты содержат массив цепочек пар рёбер вдоль проекции.
           \en Results of projecting a polyline on a polymesh. \n
               Results contain paths of edge pairs along the projection. \~
  \warning \ru В разработке.
           \en Under development. \~
*/
// ---
class MATH_CLASS MbPolylinePolymeshProjectResults
{
private:
  std::vector<c3d::IndicesPairsVector> _paths; ///< \ru Цепочки пар рёбер. \en Paths of edge pairs. \~

public:
  /// \ru Конструктор. \en Constructor.
  MbPolylinePolymeshProjectResults() : _paths() {}
  /// \ru Деструктор. \en Destructor.
  ~MbPolylinePolymeshProjectResults() {}

public:
  // \ru Получить полилинию. \en Get the polyline. \~
  const std::vector<c3d::IndicesPairsVector> & GetEdgePairPaths() const { return _paths; }
  // \ru Получить полилинию. \en Get the polyline. \~
  std::vector<c3d::IndicesPairsVector> & GetEdgePairPaths() { return _paths; }

  OBVIOUS_PRIVATE_COPY( MbPolylinePolymeshProjectResults );
};

#endif // __OP_POLYMESH_PARAMETERS_H
