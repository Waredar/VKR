//////////////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief  \ru Типы данных модуля обнаружения столкновений.
          \en Data types of collision detection module. \~
*/
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __CDM_TYPES_H
#define __CDM_TYPES_H

#include <cdet_data.h>
#include <model_item.h>

class CdCollisionManager;

/**
  \addtogroup Collision_Detection
  \{
*/

/*
  Data structures of Collision Detection Basic API.
*/

typedef CdCollisionManager * cdet_scene;

//----------------------------------------------------------------------------------------
/** \brief \ru Результат смены настроек алгоритма поиска столкновений.
           \en The result of changing the collision search settings. \~
*/
enum cdet_setting_result
{
  /// \ru Параметр настройки изменен успешно.
  /// \en The setting parameter was applied successfully.
    CDM_PARAMETER_Applied = 1
  /// \ru Параметр не удается сменить, поскольку он определяется функцией обратного вызова.
  /// \en The parameter cannot be changed because it is defined by a callback function.  
  , CDM_PARAMETER_NotChanged
};

//---------------------------------------------------------------------------------------
// \ru Структура, определяющая экземпляр геометрического объекта (полигональное или граничное представление).
// \en The structure specifing the instance of geometric object (polygonal or boundary representation).
//---
struct CDM_instance
{
  SPtr<const MbItem> sample = nullptr;  // \ru Геометрический объект, являющийся образцом экземпляра. \en The geometric object that is a sample of the instance.
  MbPlacement3D      place = MbPlacement3D::global;   // \ru Локальная система координат, указанная в компоненте-владельце экземпляра. \en The local coordinate system specified in the owning component of the instance.
  cdet_app_item      appItem = CDET_APP_NULL;  // \ru Инстанс, представляющий экземпляр на стороне приложения. \en Application-side instance representative.
  CDM_instance() = default;
  CDM_instance(const CDM_instance & ) = default;
  CDM_instance & operator= (const CDM_instance&) = default;
  CDM_instance(const SPtr<MbItem> & mbItem, const MbPlacement3D & lcs, cdet_app_item aItem) : sample(mbItem), place(lcs), appItem(aItem) {};
};

//---------------------------------------------------------------------------------------
// \ru Компонентом является геометрическое объединение тел или полигональных объектов, 
//     наделенных собственной локальной системой координат.
// \en A component is a geometric union of bodies or polygonal objects which have their 
//     own local coordinate system.
struct CDM_component
{  
  MbPlacement3D place = MbPlacement3D::global; // \ru Локальная система координат, позиционирующая компонент. \en The local coordinate system positioning the component.
  cdet_app_item appItem = CDET_APP_NULL;       // \ru Инстанс, представляющий экземпляр на стороне приложения. \en Application-side instance representative.
  CDM_component() = default;
  CDM_component(const CDM_component & ) = default;
  CDM_component & operator= (const CDM_component & ) = default;
  CDM_component(const MbPlacement3D & lcs, cdet_app_item aItem) : place(lcs), appItem(aItem) {};
};

//---------------------------------------------------------------------------------------
// \ru Структура, определяющая луч в сцене детектора столкновений.
// \en The structure defining the ray in the collision detector scene.
struct CDM_ray
{
  MbCartPoint3D origin = MbCartPoint3D::origin; // \ru Вершина луча. \en Vertex of ray.
  MbVector3D    axisZ = MbVector3D::zAxis;      // \ru Направление луча. \en Direction of ray.
  MbPlacement3D place = MbPlacement3D::global;  // \ru Положение, которое занимает луч в глобальной СК. \en The placement that the ray takes in global space.
  cdet_app_item appItem = CDET_APP_NULL;        // \ru Геометрический объект пользователя. \en User geometric item.
  CDM_ray() = default;
  CDM_ray(const CDM_ray &) = default;
  CDM_ray(const MbCartPoint3D & vertex, const MbVector3D & direction, const MbPlacement3D & lcs, cdet_app_item aItem)
   : origin(vertex), axisZ(direction), place(lcs), appItem(aItem) {};
};

//---------------------------------------------------------------------------------------
// Callback enquiries
//---
typedef SPtr<MbItem> (*CDM_item_registered)( cdet_app_item appItem ); ///< Application item was registered in the scene.
typedef void (*CDM_item_unregistered)( cdet_app_item appItem );       ///< Application item was unregistered in the scene.
typedef bool (*CDM_abort)(); ///< Query to interrupt calculations

//----------------------------------------------------------------------------------------
/** \brief  \ru Структура, объединяющая обратные вызовы детектора столкновений.
            \en The structure uniting collision detection callbacks.
*/
//---
typedef struct
{
  /*
    General system callbacks;
  */
  CDM_item_registered   gRegister;
  CDM_item_unregistered gUnregister;
  CDM_abort             abortFunc;

  /*
    Geometry properties
  */
} CDM_callback_table;


/** \} */ // Collision_Detection

#endif // __CDM_DATA_H

// eof