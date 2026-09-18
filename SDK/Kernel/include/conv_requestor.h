////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Интерфейс запроса масштаба. Интерфейс запроса сшивки.
         \en Interface of scale request. Interface of stitching request. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CONV_REQUESTOR_H
#define __CONV_REQUESTOR_H


#include <reference_item.h>
#include <math_define.h>
#include <tool_cstring.h>


//------------------------------------------------------------------------------
/** 
\brief \ru Интерфейс выбора конфигурации. 
       \en Interface of configuration selection. \~
\details  \ru Вызывается при импорте однократно, если импортируемоя модель содержит более одной конфигурации.
          \en Called on import once if the model contains contains more than one configurations. \~
*/
// ---
class CONV_CLASS IConfigurationSelector : public MbRefItem
{
public:
  // \ru Конструктор по умолчанию. \en Default constructor.
  IConfigurationSelector() = default;

  // \ru Деструктор. \en Destructor.
  virtual ~IConfigurationSelector() = default;

  // \ru Добавить конфигурацию для выбора пользователем. \en Add configuration for selection by user.
  virtual void    AddConfiguration        ( const c3d::string_t& configurationName )  = 0;

  // \ru Добавить конфигурацию для выбора пользователем, не содержащую модель. \en Add configuration without model for selection by user.
  virtual void    AddEmptyConfiguration( const c3d::string_t & configurationName ) { AddConfiguration( configurationName ); };

  // \ru Указать индекс активной конфигурации. \en Specify the index of active configuration.
  virtual void    SetActiveConfiguration  ( const size_t index )                      = 0;

  // \ru Получить индекс конфигурации выбранной пользователем. \en Get index of configuration chosen by user.
  virtual size_t  GetConfiguration        () const                                    = 0;

  // \ru Индекс конфигурации для прекращения чтения по запросу пользователя. \en Index which should be returned if user canceled import.
  static const size_t configurationIdToCancel = SYS_MAX_T;
};


//------------------------------------------------------------------------------
/**
\brief \ru Интерфейс для сохранения списка имен атрибутов модели.
       \en Interface for collecting model attribute names. \~
\details  \ru Вызывается во время импорта предварительных данных модели
        для задания списка имен атрибутов модели.
          \en Called during import of preliminary model data to specify
        a list of model attribute names .  \~
 \note \ru ЭКСПЕРИМЕНТАЛЬНАЯ.
       \en EXPEREIMENTAL. \~
*/
// ---
class CONV_CLASS IAttributeNamesCollector : public MbRefItem
{
public:
  virtual void AddAttributeName( const c3d::string_t& configurationName ) = 0;
};



//------------------------------------------------------------------------------
///  
/** 
\brief \ru Интерфейс запроса масштаба.
       \en Interface of scale request. \~
\details  \ru Рекомендуется использовать методы интерфейса IConvertorProperty3D.
          \en Using methods of the IConvertorProperty3D interface recommended. \~
 \note \ru Рекомендуется использовать методы интерфейса IConvertorProperty3D.
       \en Using methods of the IConvertorProperty3D interface recommended. \~
*/
// ---
class CONV_CLASS IScaleRequestor : public MbRefItem
{
public:
  virtual double ScaleRequest() = 0;
};


//------------------------------------------------------------------------------
/** 
\brief \ru Интерфейс запроса сшивки. 
      \en Interface of stitching request \~
\details  \ru Рекомендуется использовать методы интерфейса IConvertorProperty3D.
          \en Using methods of the IConvertorProperty3D interface recommended. \~
 \note \ru Рекомендуется использовать методы интерфейса IConvertorProperty3D.
       \en Using methods of the IConvertorProperty3D interface recommended. \~
*/
// ---
class CONV_CLASS IStitchRequestor : public MbRefItem
{
public:
  virtual bool StitchRequest() = 0;
};


//------------------------------------------------------------------------------
/**
\brief \ru Интерфейс запроса отладочного вывода.
      \en Debug output request interface \~
*/
// ---
class IConverterEventLogger : public MbRefItem
{
public:
  virtual bool WriteToLog( const char * ) = 0;
};


//------------------------------------------------------------------------------
/**
\brief \ru Интерфейс передачи метаданных.
      \en Metadata transfer. \~
*/
// ---
class CONV_CLASS IConverterMetadataReceiver : public MbRefItem 
{
public:
  virtual bool InitMetadataForItem(const c3d::string_t& category, const c3d::string_t& nameInCategory, const c3d::string_t& contentType) = 0;
  virtual void CloseMetadataForItem(const c3d::string_t& category, const c3d::string_t& nameInCategory) = 0;
  virtual void TransferMetadataForItem(const c3d::string_t& category, const c3d::string_t& nameInCategory, const char* metadataBuffer, unsigned long int bufferCapacity) = 0;
};


#endif // __CONV_REQUESTOR_H
