////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс KeyboardDevice отвечает за диспетчеризацию событий от клавиатуры в объекты KeyboardEventHandler.
           \en NOT TRANSLATED. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_KEYBOARDDEVICE_H
#define __VSN_KEYBOARDDEVICE_H

#include <vsn_absinputdevice.h>
#include <vsn_global.h>

namespace VSN {

class KeyboardDevicePrivate;
class KeyboardHandler;

//------------------------------------------------------------------------------
/** \brief  \ru Класс KeyboardDevice отвечает за диспетчеризацию событий от клавиатуры в объекты KeyboardEventHandler.
            \en NOT TRANSLATED. \~
    \ingroup Vision_Input
*/
// ---
class VSN_CLASS KeyboardDevice : public AbsInputDevice
{
    VSN_OBJECT(KeyboardDevice)
    VSN_PROP_READ_NOTIFY(activeInput, GetActiveInput, OnActiveInputModified)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit KeyboardDevice(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    ~KeyboardDevice();
public:
    /// \ru Вернуть указатель на активное устройства клавиатуры. \en NOT TRANSLATED. \~
    KeyboardHandler* GetActiveInput() const;
    /// \ru Вернуть количество координат, которые есть у этого устройства. Всегда вернет 0; \en Returns coordinate quantity this device has. NOT TRANSLATED. \~
    virtual int GetCoordinateCount() const final;
    /// \ru Вернуть количество кнопок, которые есть у этого устройства. \en Returns button quantity this device has. \~
    virtual int GetButtonCount() const final;
    /// \ru Вернуть список имен координат устройства. Всегда вернет пустой вектор. \en Returns list of device coordinate names. NOT TRANSLATED. \~
    virtual std::vector<String> GetCoordinateNames() const final;
    /// \ru Вернуть список имен кнопок устройства. \en Returns list of device button names. \~
    virtual std::vector<String> GetButtonNames() const final;
    /// \ru Вернуть целочисленный идентификатор координаты или - 1, если он не существует на этом устройстве. \en Returns integer coordinate identifier or -1 if it doesn't exist on this device. \~
    virtual int GetCoordinateId(const String& name) const final;
    /// \ru Вернуть целочисленный идентификатор имени кнопки или -1, если он не существует на этом устройстве. \en Returns integer button name identifier or -1 if it doesn't exist on this device. \~
    virtual int GetButtonId(const String &name) const final;
private:
    /// \ru Установить активный ввод. \en NO TRANSLATION. \~
    void SetActiveInput(KeyboardHandler* pActiveInput);
protected:
    /// \ru Конструктор для внутреннего использования. \en Default constructor. NOT TRANSLATED. \~
    explicit KeyboardDevice(KeyboardDevicePrivate& dd, Node* pParent = nullptr);
    virtual void SceneModificationEvent(const std::shared_ptr<SceneModification>& modification) override;
public:
    /// \ru Сигнал будет сгенерирован при активности устройства. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, OnActiveInputModified, void OnActiveInputModified(KeyboardHandler* pActiveInput), pActiveInput)
private:
    VSN_DECLARE_EX_PRIVATE(KeyboardDevice)
};

} // namespace VSN

#endif // __VSN_KEYBOARDDEVICE_H
