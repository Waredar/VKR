////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Перечисление с результатом конвертирования.
         \en Enumeration with the result of conversion. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CONV_RES_TYPE_H
#define __CONV_RES_TYPE_H

//------------------------------------------------------------------------------
/** \brief  \ru Результат конвертирования.
\en Result of converting operation.
\ingroup Data_Interface
*/
// ---
enum MbeConvResType {
  cnv_Success = 0,           ///< \ru Успешное завершение.                      \en Success.
  cnv_PartialSuccess,        ///< \ru Успешно обработана только часть объектов. При экспорте некоторые из переданных объектов не соответствуют требованиям формата. \en Only some objects were successfully processed. While export it turned out that some objects don't meet the requirements of the exchange format.
  cnv_Error,                 ///< \ru Ошибка в процессе конвертирования.        \en Error.
  cnv_UserCanceled,          ///< \ru Процесс прерван пользователем.            \en Process interrupted by user.
  cnv_NoBody,                ///< \ru Не найдено тел.                           \en No solids found.
  cnv_NoObjects,             ///< \ru Не найдено объектов.                      \en No objects found.
  cnv_FileOpenError,         ///< \ru Ошибка открытия файла.                    \en File open error.
  cnv_FileWriteError,        ///< \ru Ошибка записи файла.                      \en File write error.
  cnv_FileDeleteError,       ///< \ru Ошибка удаления файла.                    \en Could not delete file.
  cnv_ImpossibleReadAssembly,///< \ru Не поддерживает работу со сборками.       \en Assemblies are not supported.
  cnv_LicenseNotFound,       ///< \ru Ошибка получения лицензии.                \en License check failure.
  cnv_NotEnoughMemory,       ///< \ru Недостаточно памяти.                      \en Not enough memory.
  cnv_UnknownExtension,      ///< \ru Неизвестное расширение файла.             \en Unknown file extenstion.
  cnv_UnsupportedVersion     ///< \ru Неподдерживаемая версия формата.          \en Unsupported format version.
};

//------------------------------------------------------------------------------
/** \brief  \ru Получить строковое описание результата конвертирования.
\en Get string description of the result of converting operation.
\ingroup Data_Interface
*/
// ---
CONV_FUNC (std::string) MbeConvResTypeToString(MbeConvResType result);

#endif