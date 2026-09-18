////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Методы построения полигональных геометрических объектов с топологией.
         \en Functions for construction of the polygonal geometric object with topology. \~
  \details \ru Полигональные геометрические объекты могут быть построены по набору точек или на базе других объектов.
           \en Polygonal geometric objects can be constructed using a set of points or on the basis of other objects. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_POLYMESH_H
#define __ACTION_POLYMESH_H

#include <mb_cart_point.h>
#include <mb_cart_point3d.h>
#include <mb_operation_result.h>
#include <curve3d.h>

class MbPolymesh;
class MbFaceShell;
class MbPolymeshTopo;
class MbHalfedgeBoundaryCriterionBase;
class MbMeshCurvatureParams;
class MbDrapeShellParams;
class MbDrapeShellResults;
class MbRemeshParams;
class MbShellLinearizationParams;
class MbMergePolymeshParams;
class MbMeshSmoothingParams;
class MbPolyline3D;
class MbPolylinePolymeshProjectParams;
class MbPolylinePolymeshProjectResults;


//------------------------------------------------------------------------------
/** \brief \ru Создать полигональный объект по оболочке.
           \en Create the polymesh by the shell. \~
  \details \ru Создать полигональный объект по оболочке.
               В нем будет сохранен маппинг от регионов и ребер сегментации к граням и ребрам оболочки.
               Любые операции, изменяющие топологию сегментации, приведут к невалидности маппинга.
           \en Create the polymesh by the shell.
               Creates mapping from segmentation edges to shell edges and from segmentation regions to shell faces.
               Any operations that change segmentation topology will lead to invalid mapping.
  \param[in] params - \ru Параметры алгоритма.
                      \en The parameters. \~
  \param[in] shell - \ru Оболочка.
                      \en The shell. \~
  \param[in,out] mesh - \ru Полигональная сетка.
                        \en The polymesh.  \~
  \return \ru Код результата операции, rt_Success в случае успеха.
          \en Returns the operation result code, rt_Success if polymesh has been created. \n
  \ingroup Polygonal_Objects
  \warning \ru В разработке.
           \en Under development. \~
*/
// ---
MATH_FUNC( MbResultType ) CreatePolymeshByShell( const MbShellLinearizationParams & params, const MbFaceShell & shell, MbPolymesh & mesh );


//------------------------------------------------------------------------------
/** \brief \ru Выделить связные группы из набора фасетов.
           \en Get connected groups from facets. \~
  \param[in] mesh    - \ru Полигональный объект с топологией.
                       \en A polygonal object with topology. \~
  \param[in] facets  - \ru Набор фасетов.
                       \en Facet array. \~
  \param[out] groups - \ru Связные группы фасетов.
                       \en Groups of connected facets. \~
  \warning \ru В разработке.
           \en Under development. \~
*/ // ---
MATH_FUNC( void ) GetConnectedFacetGroups( const MbPolymesh &                      mesh, 
                                           const c3d::IndicesVector &              facets, 
                                                 std::vector<c3d::IndicesVector> & groups );


//------------------------------------------------------------------------------
/** \brief \ru Выделить связные группы из набора регионов.
           \en Get connected groups from regions. \~
  \param[in] mesh    - \ru Полигональный объект с топологией.
                       \en A polygonal object with topology. \~
  \param[in] regions - \ru Набор регионов.
                       \en Region array. \~
  \param[out] groups - \ru Связные группы регионов.
                       \en Groups of connected regions. \~
  \warning \ru В разработке.
           \en Under development. \~
*/ // ---
MATH_FUNC( void ) GetConnectedRegionGroups( const MbPolymesh &                      mesh,
                                            const c3d::IndicesVector &              regions,
                                                  std::vector<c3d::IndicesVector> & groups );


//------------------------------------------------------------------------------
/** \brief \ru Разбить сетку на регионы согласно критерию границы.
           \en Divide a polymesh into regions according to a given border criterion. \~
  \param[in] mesh    - \ru Полигональный объект с топологией.
                       \en A polygonal object with topology. \~
  \param[in] crit    - \ru Критерий границы.
                       \en Border criterion. \~
  \param[out] facets - \ru Группы фасетов, разделенные по регионам.
                       \en Groups of facets divided into regions. \~
  \warning \ru В разработке.
           \en Under development. \~
*/ // ---
MATH_FUNC( void ) GetPolymeshRegions( const MbPolymesh &                      mesh, 
                                      const MbHalfedgeBoundaryCriterionBase & crit,
                                            std::vector<c3d::IndicesVector> & facets );


//------------------------------------------------------------------------------
/** \brief \ru Получить регион сетки согласно критерию границы по указанному фасету-затравке.
           \en Get the region containing a given facet according to a given border criterion. \~
  \param[in] mesh    - \ru Полигональный объект с топологией.
                       \en A polygonal object with topology. \~
  \param[in] crit    - \ru Критерий границы.
                       \en Border criterion. \~
  \param[in] seed    - \ru Фасет-затравка.
                       \en A seed facet. \~
  \param[out] facets - \ru Все фасеты региона.
                       \en All the facets of a region. \~
  \warning \ru В разработке.
           \en Under development. \~
*/ // ---
MATH_FUNC( void ) GetPolymeshRegion( const MbPolymesh &                      mesh, 
                                     const MbHalfedgeBoundaryCriterionBase & crit,
                                           size_t                            seed, 
                                           c3d::IndicesVector &              facets );


//------------------------------------------------------------------------------
/** \brief \ru Получить границы региона фасетов.
           \en Get the border edges of a given region. \~
  \param[in] mesh     - \ru Полигональный объект с топологией.
                        \en A polygonal object with topology. \~
  \param[in] region   - \ru Набор фасетов, составляющих регион.
                        \en Facet array which forms a region. \~
  \param[out] borders - \ru Границы региона (набор граничных ребер).
                        \en Border edges of a region. \~
  \warning \ru В разработке.
           \en Under development. \~
*/ // ---
MATH_FUNC( void ) GetPolymeshRegionBorders( const MbPolymesh &                      mesh, 
                                            const c3d::IndicesVector &              region, 
                                                  std::vector<c3d::IndicesVector> & borders );


//------------------------------------------------------------------------------
/** \brief \ru Получить открытые границы сетки.
           \en Get the open border edges of a polymesh. \~
  \param[in] mesh     - \ru Полигональный объект с топологией.
                        \en A polygonal object with topology. \~
  \param[out] borders - \ru Открытые границы (наборы граничных ребер).
                        \en Arrays of open border edges. \~
  \warning \ru В разработке.
           \en Under development. \~
*/ // ---
MATH_FUNC( void ) GetPolymeshOpenBorders( const MbPolymesh & mesh, std::vector<c3d::IndicesVector> & borders );


//------------------------------------------------------------------------------
/** \brief \ru Получить открытые границы сегментации.
           \en Get open segmentation borders. \~
  \param[in] mesh     - \ru Полигональный объект с топологией.
                        \en A polygonal object with topology. \~
  \param[out] borders - \ru Открытые границы (наборы граничных ребер сегментации).
                        \en Arrays of open border edges of a segmentation. \~
  \warning \ru В разработке.
           \en Under development. \~
*/ // ---
MATH_FUNC( void ) GetSegmOpenBorders( const MbPolymesh & mesh, std::vector<c3d::IndicesVector> & borders );


/// \ru Получить полилинию для ребра сегментации.
MATH_FUNC( bool ) GetPolymeshEdgePolyline( const MbPolymesh & mesh, size_t iEdSegm, c3d::SpacePointsVector & polyline );


/// \ru Получить полилинию для цикла сегментации.
MATH_FUNC( void ) GetPolymeshLoopPolyline( const MbPolymesh & mesh, size_t iLoop, c3d::SpacePointsVector & polyline );


//------------------------------------------------------------------------------
/** \brief \ru Построить контур сечения полигонального объекта плоскостью.
           \en Create a section contour for a polygonal object. \~
  \param[in] mesh       - \ru Полигональный объект с топологией.
                          \en A polygonal object with topology. \~
  \param[in] place      - \ru Секущая плоскость.
                          \en A cutting plane. \~
  \param[out] polylines - \ru Построенные ломаные контура сечения объекта.
                          \en The resultant contours. \~
  \warning \ru В разработке.
           \en Under development. \~
*/ // ---
MATH_FUNC( MbResultType ) PolymeshSection( const MbPolymesh &                 mesh,
                                           const MbPlacement3D &              place,
                                                 c3d::SpaceCurvesSPtrVector & polylines );


//------------------------------------------------------------------------------
/** \brief \ru Отрезать часть полигонального объекта плоскостью.
           \en Cut the part of a polygonal object by a plane. \~
  \param[in] place    - \ru Секущая плоскость.
                        \en A cutting plane. \~
  \param[in] bTriangulate    - \ru Триангулировать ли разрезанные фасеты.
                               \en Should cut facets be triangulated. \~
  \param[in,out] mesh - \ru Полигональный объект с топологией.
                        \en A polygonal object with topology. \~
  \warning \ru В разработке.
           \en Under development. \~
*/ // ---
MATH_FUNC( bool ) CutPolymeshByPlane( const MbPlacement3D & place,
                                            bool            bTriangulate,
                                            MbPolymesh    & mesh );


//------------------------------------------------------------------------------
/** \brief \ru Скопировать часть полигонального объекта в другой полигональный объект.
           \en Copy the part of a polygonal object into another polygonal object. \~
  \param[in] mesh        - \ru Оригинальный полигональный объект.
                           \en An original polygonal object. \~
  \param[in] facets      - \ru Набор копируемых фасетов.
                           \en A polygonal object with topology. \~
  \param[in,out] meshSub - \ru Полигональный объект, в который производится копирование.
                           \en A polygonal object in which data should be copied to. \~
  \warning \ru В разработке.
           \en Under development.\~
*/ // ---
MATH_FUNC( void ) CopyPolymeshPart( const MbPolymesh & mesh, const c3d::IndicesVector & facets, MbPolymesh & meshSub );


//------------------------------------------------------------------------------
/** \brief \ru Проверить, является ли полигональный объект триангуляцией.
           \en Verify if polymesh is triangulation. \~
  \param[in] mesh        - \ru Полигональный объект.
                           \en Polygonal object. \~
  \return \ru True если полигональный объект является триангуляцией, иначе false.
          \en True if polymesh is triangulation, otherwise false. \~
*/ // ---
MATH_FUNC( bool ) IsPolymeshTriangulation( const MbPolymesh & mesh );


//------------------------------------------------------------------------------
/** \brief \ru Ремешировать полигональный объект.
           \en Remesh a polygonal object. \~
  \details \ru Ремешировать полигональный объект.
               Он должен быть триангуляцией. Если метод ремешинга по кривизне, в сетке должен
               присутствовать атрибут кривизн.
               Атрибуты нормалей и кривизн будут удалены.
               Если в сетке есть оболочка как параметрическая подложка, она будет использована для проецирования
               вершин триангуляции.
           \en Remesh a polygonal object.
               The polymesh must contains only triangle facets.
               For remeshing by curvature method a curvature attribute must be defined.
               Deletes curvature and normal attributes.
               If the polymesh has a shell as a parametric substrate, it will be used for a polymesh vertices projection. \~
  \param[in] params - \ru Параметры алгоритма.
                      \en The parameters. \~
  \param[in,out] mesh - \ru Полигональная сетка.
                        \en The polymesh.  \~
  \return \ru Код результата операции, rt_Success в случае успеха.
          \en Returns the operation result code, rt_Success if remeshing is successful. \n
  \ingroup Polygonal_Objects
  \warning \ru В разработке.
           \en Under development. \~
*/
// ---
MATH_FUNC( MbResultType ) Remesh( const MbRemeshParams & params, MbPolymesh & mesh );


//------------------------------------------------------------------------------
/** \brief \ru Рассчитать кривизны полигональной сетки.
           \en Calculates mesh curvatures. \~
  \details \ru Рассчитать кривизны полигональной сетки.
               Результатом операции является появление у полигональной сетки атрибута кривизн.
               Если атрибут уже был, он будет удален и создан заново.
           \en Calculates mesh curvatures.
               Operation result is a curvature half edge attribute inserted into the original polymesh.
               If mesh has one it will be removed before caclulation. \~
  \param[in] params - \ru Параметры алгоритма.
                      \en The parameters. \~
  \param[in,out] mesh - \ru Полигональная сетка.
                        \en Polymesh.  \~
  \return \ru Код результата операции, rt_Success если кривизны были рассчитаны.
          \en Returns the operation result code, rt_Success if curvatures were calculated. \n
  \ingroup Polygonal_Objects
  \warning \ru В разработке.
           \en Under development. \~
*/
// ---
MATH_FUNC( MbResultType ) CalculatePolymeshCurvatures( const MbMeshCurvatureParams & params, MbPolymesh & mesh );


//------------------------------------------------------------------------------
/** \brief \ru Драпировка оболочки тканью.
           \en Drap a shell with fabric. \~
  \details \ru Драпировка оболочки тканью.
           \en Drap a shell with fabric.
  \param[in] params - \ru Параметры алгоритма.
                      \en The parameters. \~
  \param[out] results - \ru Результаты алгоритма.
                        \en Results.  \~
  \return \ru Код результата операции, rt_Success если драпировка получилась.
          \en Returns the operation result code, rt_Success if drape is successful. \n
  \ingroup Shell_Modeling
  \warning \ru В разработке.
           \en Under development. \~
*/
// ---
MATH_FUNC( MbResultType ) DrapeShell( const MbDrapeShellParams & params, MbDrapeShellResults & results );


//------------------------------------------------------------------------------
/** \brief \ru Объединить полигональный объект с другим полигональным объектом.
           \en Merge a polygonal object with another polygonal object. \~
  \param[in] meshFrom   - \ru Полигональный объект, который копируется в meshTo.
                          \en A polygonal object, being copied into meshTo. \~
  \param[in] params     - \ru Параметры объединения.
                          \en Merging parameters. \~
  \param[in-out] meshTo - \ru Полигональный объект, который аккумулирует результат объединения.
                          \en A polygonal object, accumulating merged objects. \~
  \return \ru Код результата операции, rt_Success, если объекты успешно объединены.
          \en Returns the operation result code, rt_Success if the objects are successfully merged. \n
  \warning \ru В разработке.
           \en Under development.\~
*/ // ---
MATH_FUNC( MbResultType ) MergePolymeshes( const MbPolymesh & meshFrom, const MbMergePolymeshParams & params, MbPolymesh & meshTo );


//------------------------------------------------------------------------------
/** \brief \ru Сгладить полигональный объект по набору входных параметров сглаживания.
           \en Smooth a polygonal object using a set of input smoothing parameters. \~
  \param[in] params   - \ru Параметры сглаживания.
                        \en Smoothing parameters. \~
  \param[in-out] mesh - \ru Полигональный объект.
                         \en A polygonal object. \~
  \return \ru Код результата операции, rt_Success если объект успешно сглажен.
          \en Returns the operation result code, rt_Success if the object is successfully smoothed. \n
  \warning \ru В разработке.
           \en Under development.\~
*/ // ---
MATH_FUNC( MbResultType ) SmoothPolymesh( const MbMeshSmoothingParams & params, MbPolymesh & mesh );



//------------------------------------------------------------------------------
/** \brief \ru Спроецировать полилинию на полигональный объект.
           \en Project a polyline on a polygonal object. \~
  \details \ru Спроецировать полилинию на полигональный объект.
               Если на некотором участке полилиния проецируется внутрь фасета, он разделяется на несколько фасетов.
               При этом создаются новые рёбра полигонального объекта.
           \en Project a polyline on a polygonal object.
               In case of projecting a polyline's fragment inside a facet, it splits into new ones, so new edges are created. \~
  \param[in-out] mesh - \ru Полигональный объект.
                        \en A polygonal object being projected on. \~
  \param[in] params   - \ru Параметры проецирования полилинии на полигональный объект.
                        \en Parameters for projecting a polyline on a polymesh. \~
  \param[out] results - \ru Результат проецирования полилинии на полигональный объект.
                        \en Result of projecting a polyline on a polymesh. \~
  \return \ru Код результата операции, rt_Success, если проекция успешно построена.
          \en Returns the operation result code, rt_Success if a polyline is successfully projected. \n
  \warning \ru В разработке.
           \en Under development.\~
*/ // ---
MATH_FUNC( MbResultType ) ProjectPolylineOnPolymesh( MbPolymesh & mesh, const MbPolylinePolymeshProjectParams & params, MbPolylinePolymeshProjectResults & results );


#endif // __ACTION_POLYMESH_H
