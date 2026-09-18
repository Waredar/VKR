////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Параметры операций над каркасом.
         \en Parameters of operations on the wire frame. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __OP_WIREFRAME_PARAMETERS_H
#define __OP_WIREFRAME_PARAMETERS_H


#include <wire_frame.h>
#include <op_curve_parameter.h>
#include <wireframe_point.h>


class MbTrimmedWireFrameInfo;


//------------------------------------------------------------------------------
/** \brief \ru Параметры скругления каркаса.
           \en Parameters of wire frame fillets. \~
  \details \ru Параметры скругления каркаса: \n
               type - тип скругления( обычное или на поверхности ). \n
               radiuses - радиусы скругления, i-й радиус соответствует стыку i-го и i+1-го ребра. \n
           \en Parameters of wire frame fillets:  \n
               'type' is a fillet type( ordinary or on a surface ). \n
               'radiuses' are the fillet radii, the i-th radius corresponds to the joint of the i-th and the i+1-th edges. \n \~
  \warning \ru В разработке.
           \en Under development. \~
  \ingroup WireFrame_Parameters
*/ // ---
class MATH_CLASS MbWireFrameFilletsParams : public MbPrecision {
private:
  MbeConnectingType   _type;     ///< \ru Тип выполняемых скруглений. \en Fillet type( ordinary or on a surface ).
  c3d::DoubleVector   _radiuses; ///< \ru Множество радиусов скругления. \en An array of fillet radii.
  c3d::SNameMakerSPtr _snMaker;  ///< \ru Именователь с версией операции. \en Names maker with operation version.

public:
  /** \brief \ru Конструктор по параметрам.
             \en Constructor by parameters.\~
    \details \ru Конструктор по параметрам.
             \en Constructor by parameters.\~
    \param[in] type      - \ru Тип выполняемых скруглений. \en Fillet type.\~
    \param[in] radiuses  - \ru Множество радиусов скругления.  \en An array of fillet radii. \~
    \param[in] nameMaker - \ru Именователь с версией операции. \en Names maker with operation version.\~
  */
  MbWireFrameFilletsParams( MbeConnectingType type, const c3d::DoubleVector & radiuses, const MbSNameMaker & nameMaker );
  /// \ru Конструктор для чтения. \en Constructor for reading.
  MbWireFrameFilletsParams( TapeInit tapeInit );
  /// \ru Деструктор. \ en Destructor.
  ~MbWireFrameFilletsParams() {}

public:
  /// \ru Получить множество радиусов скругления. \en Get an array of fillet radii. 
  const c3d::DoubleVector & GetRadii()          const { return _radiuses; }
  /// \ru Получить тип выполняемых скруглений. \en Get the type of fillets. 
  MbeConnectingType         GetConnectingType() const { return _type; }
  /// \ru Получить именователь. \en Get names maker. 
  const MbSNameMaker &      GetNameMaker()      const { return *_snMaker; }

OBVIOUS_PRIVATE_COPY( MbWireFrameFilletsParams )
};


//-------------------------------------------------------------------------------
/** \brief \ru Информация для преобразования каркаса в Nurbs.
           \en Information for transformation of a wire frame to NURBS. \~
  \details \ru Информация для преобразования каркаса в Nurbs. \n
           \en Information for transformation of a wire frame to NURBS. \n \~
  \warning \ru В разработке.
           \en Under development. \~
  \ingroup WireFrame_Parameters
*/
// ---
class MATH_CLASS MbNurbsWireFrameInfo {
private:
  MbWireFramePoint _pbeg;         ///< \ru Начало участка каркаса. \en Wire frame piece start. 
  MbWireFramePoint _pend;         ///< \ru Конец участка каркаса. \en Wire frame piece end. 
  bool             _sense;        ///< \ru Направление сплайн-кривой. \en Direction of spline-curve. 
  bool             _matchParams;  ///< \ru Сохранять ли при преобразовании однозначное соответствие параметрических областей. \en Whether to save correspondence of parametric regions while transforming or not. 
  bool             _extendRange;  ///< \ru Строится ли преобразование на продолжении для незамкнутой подложки. \en Whether transformation is constructed on the extension for a non-closed substrate. 
  VERSION          _version;      ///< \ru Версия исполнения. \en The version of execution. 

private:
  MbNurbsWireFrameInfo();
public:

  /// \ru Конструктор. \en Constructor. 
  MbNurbsWireFrameInfo( const MbWireFramePoint & p1, const MbWireFramePoint & p2, bool sense, bool match, bool ext, VERSION version ) 
    : _pbeg       ( p1      )
    , _pend       ( p2      )
    , _sense      ( sense   )
    , _matchParams( match   )
    , _extendRange( ext     )
    , _version    ( version )
  {}
  /// \ru Конструктор. \en Constructor. 
  MbNurbsWireFrameInfo( const MbNurbsWireFrameInfo & other, const MbWireFramePoint & p1, const MbWireFramePoint & p2, bool sense ) 
    : _pbeg       ( p1    )
    , _pend       ( p2    )
    , _sense      ( sense )
    , _matchParams( other._matchParams )
    , _extendRange( other._extendRange )
    , _version    ( other._version     )
  {}
  /// \ru Конструктор копирования. \en Copy constructor. 
  MbNurbsWireFrameInfo( const MbNurbsWireFrameInfo & other ) 
    : _pbeg       ( other._pbeg  )
    , _pend       ( other._pend  )
    , _sense      ( other._sense )
    , _matchParams( other._matchParams )
    , _extendRange( other._extendRange )
    , _version    ( other._version     )
  {}
  /// \ru Конструктор для чтения. \en Constructor for reading. 
  MbNurbsWireFrameInfo( TapeInit tapeInit );


  /// \ru Функция инициализации. \en The initialization function. 
  void Init( const MbWireFramePoint & p1, const MbWireFramePoint & p2, bool sense )
  {
    _pbeg = p1;
    _pend = p2;
    _sense = sense;
  }
  /// \ru Функция инициализации. \en The initialization function. 
  void Init( const MbWireFramePoint & p1, const MbWireFramePoint & p2, bool sense, bool match, bool ext, VERSION version ) 
  {
    _matchParams = match;
    _extendRange = ext;
    _version = version;
    Init( p1, p2, sense );
  }

public:
  /// \ru Получить начало участка кривой. \en Get the start curve region.
  const MbWireFramePoint & GetPBeg()  const { return _pbeg;  }
  /// \ru Получить конец участка кривой. \en Get the end curve region.
  const MbWireFramePoint & GetPEnd()  const { return _pend;  }
  /// \ru Получить направление сплайн-кривой. \en Get the direction of spline-curve. 
  bool      GetSense() const { return _sense; }
  /// \ru Сохранять ли при преобразовании однозначное соответствие параметрических областей. \en Whether to save correspondence of parametric regions by transformation or not. 
  bool      MatchParams() const { return _matchParams; }
  /// \ru Строится ли преобразование на продолжении для незамкнутой подложки. \en Whether transformation is constructed on the extension for a non-closed substrate or not. 
  bool      ExtendRange() const { return _extendRange; }
  /// \ru Получить версию исполнения. \en Get the version of execution. 
  VERSION   GetMathVersion() const { return _version; }
  /// \ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool      IsSame( const MbNurbsWireFrameInfo & other, double accuracy ) const;

  /// \ru Оператор присваивания. \en An assignment operator. 
  const MbNurbsWireFrameInfo & operator = ( const MbNurbsWireFrameInfo & other ) {
    _pbeg        = other._pbeg;
    _pend        = other._pend;
    _sense       = other._sense;
    _matchParams = other._matchParams;
    _extendRange = other._extendRange;
    _version     = other._version;
    return *this;
  }

KNOWN_OBJECTS_RW_REF_OPERATORS( MbNurbsWireFrameInfo ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class. \~
};


//-------------------------------------------------------------------------------
/** \brief \ru Параметры преобразования каркаса в Nurbs.
           \en Parameters for transformation of a wire frame to NURBS. \~
  \details \ru Параметры преобразования каркаса в Nurbs. \n
           \en Parameters for transformation of a wire frame to NURBS. \n \~
  \ingroup WireFrame_Parameters
*/
// ---
class MATH_CLASS MbNurbsWireFrameParams : public MbPrecision {
private:
  MbNurbsWireFrameInfo _frameIntoNurbsInfo;   ///< \ru Информация для преобразования каркаса в Nurbs. \en Information for transformation of a wire frame to NURBS. \~
  c3d::SNameMakerSPtr  _snMaker;              ///< \ru Именователь с версией операции. \en Names maker with operation version.

private:
  MbNurbsWireFrameParams();

public:
  /// \ru Конструктор. \en Constructor. 
  MbNurbsWireFrameParams( const MbNurbsWireFrameInfo & info, 
                          const MbSNameMaker &         nameMaker )
    : _frameIntoNurbsInfo( info )
    , _snMaker( &nameMaker.Duplicate() )
  {}

  /// \ru Конструктор. \en Constructor. 
  explicit MbNurbsWireFrameParams( const MbWireFramePoint & p1, 
                                   const MbWireFramePoint & p2, 
                                         bool               sense,
                                         bool               match, 
                                         bool               ext, 
                                   const MbSNameMaker &     nameMaker,
                                         VERSION            ver );

  /// \ru Конструктор. \en Constructor. 
  explicit MbNurbsWireFrameParams( const MbNurbsWireFrameParams & other, 
                                   const MbWireFramePoint &       p1, 
                                   const MbWireFramePoint &       p2, 
                                         bool                     sense,
                                   const MbSNameMaker &           nameMaker );

  /// \ru Конструктор копирования. \en Copy constructor. 
  MbNurbsWireFrameParams( const MbNurbsWireFrameParams & other );

  /// \ru Конструктор для чтения. \en Constructor for reading. 
  MbNurbsWireFrameParams( TapeInit tapeInit );

  /// \ru Функция инициализации. \en The initialization function. 
  void Init( const MbWireFramePoint & p1, const MbWireFramePoint & p2, bool sense )
  {
    _frameIntoNurbsInfo.Init( p1, p2, sense );
  }
  /// \ru Функция инициализации. \en The initialization function. 
  void Init( const MbWireFramePoint & p1, const MbWireFramePoint & p2, bool sense, bool match, bool ext ) {
    _frameIntoNurbsInfo.Init( p1, p2, sense, match, ext, Math::DefaultMathVersion() );
  }

public:
  /// \ru Получить параметр начала участка кривой. \en Get the parameter of the start curve region. 
  const MbWireFramePoint & GetPBeg()  const { return _frameIntoNurbsInfo.GetPBeg();  }
  /// \ru Получить параметр конца участка кривой. \en Get the parameter of the end curve region. 
  const MbWireFramePoint & GetPEnd()  const { return _frameIntoNurbsInfo.GetPEnd();  }
  /// \ru Получить направление сплайн-кривой. \en Get the direction of spline-curve. 
  bool      GetSense() const { return _frameIntoNurbsInfo.GetSense(); }
  /// \ru Сохранять ли при преобразовании однозначное соответствие параметрических областей. \en Whether to save correspondence of parametric regions by transformation or not. 
  bool      MatchParams() const { return _frameIntoNurbsInfo.MatchParams(); }
  /// \ru Строится ли преобразование на продолжении для незамкнутой подложки. \en Whether transformation is constructed on the extension for a non-closed substrate or not. 
  bool      ExtendRange() const { return _frameIntoNurbsInfo.ExtendRange(); }
  /// \ru Получить версию исполнения. \en Get the version of execution. 
  VERSION   GetMathVersion() const { return _frameIntoNurbsInfo.GetMathVersion(); }

  /// \ru Получить информацию для преобразования каркаса в Nurbs. \en Get information for transformation of a wire frame to NURBS.
  const MbNurbsWireFrameInfo & GetNurbsWireFrameInfo() const { return _frameIntoNurbsInfo; }

  /// \ru Получить именователь. \en Get names maker. 
  const MbSNameMaker & GetNameMaker() const { return *_snMaker; }

  /// \ru Оператор присваивания. \en An assignment operator. 
  const MbNurbsWireFrameParams & operator = ( const MbNurbsWireFrameParams & other ) {
    MbPrecision::operator=( other );
   _frameIntoNurbsInfo = other._frameIntoNurbsInfo;
    return *this;
  }

};


//-------------------------------------------------------------------------------
/** \brief \ru Параметры проецирования точки на проволочный каркас.
           \en Parameters for projecting points onto a wire frame. \~
  \details \ru Параметры проецирования точки на проволочный каркас. \n
           \en Parameters for projecting points onto a wire frame. \n \~
  \ingroup WireFrame_Parameters
*/
// ---
class MATH_CLASS MbWireFrameProjParams : public MbPrecision {
private:
  MbCartPoint3D            _point;    ///< \ru Точка для проецирования. \en Projection point.
  c3d::WireFramePointsPair _range;    ///< \ru Диапазон поиска проекции. Может быть не задан. \en Projection search range. May not be specified.
  bool                     _ext;      ///< \ru Признак выхода за пределы диапазона поиска или за пределы областей связных контуров каркаса. \en Sign of going beyond the search range or beyond the areas of connected frame contours.

public:
  /// \ru Конструктор по умолчанию. \en Default constructor.
  MbWireFrameProjParams()
    : MbPrecision()
    , _point()
    , _range( MbWireFramePoint(), MbWireFramePoint() )
    , _ext( false )
  {}

  /** \brief \ru Конструктор по параметрам.
             \en Constructor by parameters. \~
    \details \ru Конструктор по точке и признаку выхода за пределы диапазона.
             \en Constructor by point and a sign of out of range. \~
    \param[in] point - \ru Проецируемая точка.
                       \en Projected point. \~
    \param[in] ext - \ru Признак выхода за пределы областей связных контуров каркаса.
                     \en Sign of going beyond the beyond the areas of connected wire frame contours. \~
  */
  MbWireFrameProjParams( const MbCartPoint3D & point, bool ext )
    : MbPrecision()
    , _point( point )
    , _range( MbWireFramePoint(), MbWireFramePoint() )
    , _ext( ext )
  {}

  /** \brief \ru Конструктор по параметрам.
             \en Constructor by parameters. \~
    \details \ru Конструктор с указанием диапазона поиска.
             \en Constructor specifying the search range. \~
    \param[in] point - \ru Проецируемая точка.
                       \en Projected point. \~
    \param[in] range - \ru Диапазон поиска проекции.
                       \en Projection search range. \~
    \param[in] ext - \ru Признак выхода за пределы диапазона поиска или за пределы областей связных контуров каркаса.
                     \en Sign of going beyond the search range or beyond the areas of connected frame contours. \~
  */
  MbWireFrameProjParams( const MbCartPoint3D & point, const c3d::WireFramePointsPair & range, bool ext )
    : MbPrecision()
    , _point( point )
    , _range( range )
    , _ext( ext )
  {}

  /// \ru Конструктор копирования. \en Copy constructor.
  MbWireFrameProjParams( const MbWireFrameProjParams & other )
    : MbPrecision( other )
    , _point( other._point )
    , _range( other._range )
    , _ext( other._ext )
  {}

public:
  /// \ru Задан ли диапазон. \en Is the range set?
        bool                      IsRangeSet()  const { return _range.first.IsValid() && _range.second.IsValid(); }
  /// \ru Выдать диапазон поиска. \en Give search range.
  const c3d::WireFramePointsPair & GetRange()   const { return _range; }
  /// \ru Выдать признак выхода за пределы диапазона поиска. \en Get sign of going beyond the search range.
        bool                      GetExt()      const { return _ext; }
  /// \ru Выдать точку для проецирования. \en Get projection point.
  const MbCartPoint3D &           GetPoint()    const { return _point; }

  /// \ru Оператор присваивания. \en An assignment operator. 
  const MbWireFrameProjParams & operator = ( const MbWireFrameProjParams & other ) {
    MbPrecision::operator=( other );
   _point = other._point;
   _range = other._range;
   _ext = other._ext;
   return *this;
  }
};


//-------------------------------------------------------------------------------
/** \brief \ru Результаты проецирования точки на проволочный каркас.
           \en Results for projecting points onto a wire frame. \~
  \details \ru Результаты проецирования точки на проволочный каркас. \n
           \en Results for projecting points onto a wire frame. \n \~
  \ingroup WireFrame_Parameters
*/
// ---
class MATH_CLASS MbWireFrameProjResult {
private:
  MbWireFramePoint _projection;  ///< \ru Точка на проволочном каркасе. \en Point on the wire frame.
  bool             _result;      ///< \ru true, если найденный параметр находится в допустимом диапазоне, или false - в противном случае. \en true if the found parameter is in a valid range or false - otherwise.

public:
  /// \ru Конструктор по умолчанию. \en Default constructor.
  MbWireFrameProjResult()
    : _projection()
    , _result( false )
  {}
  /// \ru Конструктор по параметрам. \en Constructor by parameters.
  MbWireFrameProjResult( const MbWireFramePoint & point, bool result )
    : _projection( point )
    , _result( result )
  {}
  /// \ru Конструктор копирования. \en Copy constructor.
  MbWireFrameProjResult( const MbWireFrameProjResult & other )
    : _projection( other._projection )
    , _result( other._result )
  {}

  /// \ru Инициализация по параметрам. \en Initialization by parameters.
  void Init( const MbWireFramePoint & point, bool result ) {
    _projection = point;
    _result = result;
  }

  /// \ru Выдать точку на проволочном каркасе. \en Get point on the wire frame.
  const MbWireFramePoint & GetWireFramePoint() const { return _projection; }

  /// \ru
  bool GetResult() const { return _result; }

  /// \ru Оператор присваивания. \en An assignment operator. 
  const MbWireFrameProjResult & operator = ( const MbWireFrameProjResult & other ) {
    _projection = other._projection;
    return *this;
  }
};


//-------------------------------------------------------------------------------
/** \brief \ru Параметры для усечения каркаса.
           \en Parameters for trimmed of a wire frame. \~
  \details \ru Параметры для усечения каркаса. \n
           \en Parameters for trimmed of a wire frame. \n \~
  \ingroup WireFrame_Parameters
*/
// ---
class MATH_CLASS MbTrimmedWireFrameParams : public MbPrecision {
private:
  DPtr<MbTrimmedWireFrameInfo> _trimmedWireFrameInfo; ///< \ru Информация для усечения каркаса. \en Information for trimmed wire frame. \~
  c3d::SNameMakerSPtr          _snMaker;              ///< \ru Именователь с версией операции. \en Names maker with operation version.
private:
  MbTrimmedWireFrameParams();
public:
  /// \ru Конструктор. \en Constructor. 
  explicit MbTrimmedWireFrameParams( const MbWireFramePoint & p1,
                                     const MbWireFramePoint & p2, 
                                           bool               sense,
                                           bool               saveParLenAndLaw,
                                     const MbSNameMaker &     nameMaker );
  /// \ru Конструктор копирования. \en Copy constructor. 
           MbTrimmedWireFrameParams( const MbTrimmedWireFrameParams & other );
  /// \ru Деструктор \en Destructor
  virtual  ~MbTrimmedWireFrameParams();
  /// \ru Функция инициализации. \en The initialization function. 
  void     Init( const MbWireFramePoint & p1, 
                 const MbWireFramePoint & p2, 
                       bool               sense,
                       bool               saveParLenAndLaw );
  /// \ru Получить параметр начала участка кривой. \en Get the parameter of the start curve region. 
  const MbWireFramePoint &         GetPBeg()  const;
  /// \ru Получить параметр конца участка кривой. \en Get the parameter of the end curve region. 
  const MbWireFramePoint &         GetPEnd()  const;
  /// \ru Получить направление усеченной кривой относительно исходной. \en Get the direction of a trimmed curve in relation to an initial curve.  
  bool                             GetSense() const;
  /// \ru Получить информацию о сохранении параметрической длины и закона. \en Get information about saving parametric length and law. 
  bool                             GetSaveLengthAndLow() const;
  /// \ru Получить именователь. \en Get names maker. 
  const MbSNameMaker &             GetNameMaker() const { return *_snMaker; }
  /// \ru Оператор присваивания. \en An assignment operator. 
  const MbTrimmedWireFrameParams & operator = ( const MbTrimmedWireFrameParams & other );
};


//-------------------------------------------------------------------------------
/** \brief \ru Параметры эквидистантного каркаса.
           \en Parameters of an offset wire frame. \~
  \details \ru Параметры эквидистантного каркаса.
           \en Parameters of an offset wire frame. \~
  \ingroup WireFrame_Parameters
*/
// ---
class MATH_CLASS MbOffsetWireFrameParams : public MbPrecision {
private:
  std::unique_ptr<MbSpatialOffsetCurveParams> _spatialParameters; ///< \ru Параметры для смещения пространственной кривой. \en Parameters for offsetting a spatial curve. \~
  std::unique_ptr<MbSurfaceOffsetCurveParams> _surfaceParameters; ///< \ru Параметры для смещения кривой вдоль поверхности. \en Parameters for offsetting a curve along a surface. \~
  MbVector3D                                  _offset;            ///< \ru Вспомогательный вектор смещения. \en The auxiliary offset vector.

public:
  /** \brief \ru Конструктор по параметрам.
             \en Constructor by parameters. \~
    \details \ru Конструктор для смещения пространственной кривой.
             \en Constructor for offsetting a spatial curve. \~
    \param[in] offsetVect - \ru Вектор, задающий смещение в точке кривой.
                            \en The displacement vector at a point of the curve. \~
    \param[in] useFillet - \ru Если true, то разрывы заполнять скруглением, иначе продолженными кривыми.
                           \en If 'true', the gaps are to be filled with fillet, otherwise with the extended curves. \~
    \param[in] keepRadius - \ru Если true, то в существующих скруглениях сохранять радиусы.
                            \en If 'true', the existent fillet radii are to be kept. \~
    \param[in] bluntAngle - \ru Если true, то в притуплять острые углы.
                            \en If 'true', sharp corners are to be blunt. \~
    \param[in] fromBeg - \ru Вектор смещения привязан к началу (если true).
                         \en The translation vector is associated with the beginning (if true). \~
    \param[in] nameMaker - \ru Именователь кривых каркаса.
                           \en An object defining the frame curves names. \~
    \param[in] useSurfaceNormal - \ru Эквидистанта согласована с нормалью к поверхности.
                                  \en Offset point is moved according to surface normal. \~
    \param[in] surface - \ru Поверхность кривой или подобная ей.
                         \en Curve's surface or similar to such surface. \~
  */
  explicit MbOffsetWireFrameParams( const MbVector3D &          offsetVect,
                                          bool                  useFillet,
                                          bool                  keepRadius,
                                          bool                  bluntAngle,
                                          bool                  fromBeg,
                                    const MbSNameMaker &        nameMaker,
                                          bool                  useSurfaceNormal,
                                          c3d::ConstSurfaceSPtr surface = nullptr );

  /** \brief \ru Конструктор по параметрам.
             \en Constructor by parameters. \~
    \details \ru Конструктор для смещения пространственной кривой.
             \en Constructor for offsetting a spatial curve. \~
    \param[in] offsetVect - \ru Вектор, задающий смещение в точке кривой.
                            \en The displacement vector at a point of the curve. \~
    \param[in] nameMaker - \ru Именователь кривых каркаса.
                           \en An object defining the frame curves names. \~
  */
  explicit MbOffsetWireFrameParams( const MbVector3D &   offsetVect,
                                    const MbSNameMaker & nameMaker );

  /** \brief \ru Конструктор по параметрам.
             \en Constructor by parameters. \~
    \details \ru Конструктор для смещения кривой вдоль поверхности.
             \en Constructor for offsetting a curve along a surface. \~
    \param[in] face - \ru Грань, на которой строится эквидистанта.
                      \en The face on which to build the offset curve. \~
    \param[in] axis - \ru Направление смещения с точкой приложения.
                      \en The offset direction with a reference point. \~
    \param[in] dist - \ru Величина смещения.
                      \en The offset distance. \~
    \param[in] nameMaker - \ru Именователь кривых каркаса.
                           \en An object defining the frame curves names. \~
  */
  explicit MbOffsetWireFrameParams( const MbFace & face, const MbAxis3D & axis, double dist, const MbSNameMaker & nameMaker );
  /// \ru Конструктор копирования. \en Copy constructor.
  MbOffsetWireFrameParams( const MbOffsetWireFrameParams & other );
  /// \ru Конструктор для чтения. \en Constructor for reading.
  MbOffsetWireFrameParams( TapeInit ti );
  /// \ru Деструктор. \en Destructor.
  virtual ~MbOffsetWireFrameParams() {}

public:
  /// \ru Получить параметры. \en Get parameters.
  const MbSpatialOffsetCurveParams * GetSpatialParams() const { return _spatialParameters.get(); }
  /// \ru Получить параметры. \en Get parameters.
  const MbSurfaceOffsetCurveParams * GetSurfaceParams() const { return _surfaceParameters.get(); }
  /// \ru Выдать вектор смещения. \en Get offset vector.
  const MbVector3D & GetOffsetVector() const;
  /// \ru Установить вектор смещения. \en Set offset vector.
  MbVector3D & SetOffsetVector();
  /// \ru Установить параметры по вектору смещения. \en Set parameters by offset vector.
  void SetOffsetParams( const MbVector3D & offset );
  /// \ru Являются ли параметры параметрами для смещением кривой вдоль вектора. \en Are the parameters for a shift of the curve along the vector.
  bool IsParamsForSpatialCurve() const;
  /// \ru Преобразовать элемент согласно матрице. \en Transform element by matrix.
  void Transform( const MbMatrix3D & matrix );
  /// \ru поворот точек вокруг произвольной оси \en rotate points around an arbitrary axis.
  void Rotate( const MbAxis3D & axis, double angle );
  /// \ru Сдвиг точек на произвольный вектор \en Move points  on arbitrary vector.
  void Move( const MbVector3D & to );
  /// \ru Проверка на равенство. \en Check if *this == other.
  bool IsEqual( const MbOffsetWireFrameParams & other, double accuracy ) const;
  /// \ru Получить именователь операции. \en Get names maker.
  const MbSNameMaker & GetNameMaker() const;

  /// \ru Оператор присваивания. \en An assignment operator.
  const MbOffsetWireFrameParams & operator=( const MbOffsetWireFrameParams & other );

  KNOWN_OBJECTS_RW_REF_OPERATORS( MbOffsetWireFrameParams ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class. \~

};


#endif // __OP_WIREFRAME_PARAMETERS_H
