////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс ExplodeDispatcher используется для управления процессом разлета объектов 
               геометрической модели (сегментов сцены), обеспечивает поддержку работы с вкладками GUI и 
               предоставляет различные режимы просмотра.
           \en Class ExplodeDispatcher is used to manage the process of disassembling objects the
               geometric model (scene segments), it also provides support for working with GUI tabs and
               provides various viewing modes. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_EXPLODEDISPATCHER_H
#define __VSN_EXPLODEDISPATCHER_H

#include <map>

#include <vsn_global.h>
#include <vsn_vector3d.h>
#include <vsn_point3d.h>
#include <vsn_variant.h>

namespace VSN {

/** \brief   \ru Класс ExplodeParameterState используется для получения состояния элементов 
                 управления GUI по управляющему параметру. Для получения состояния используется метод
                 ExplodeDispatcher::GetParameterState(). Если для запрашиваемого параметра наличие состояния
                 не поддерживается, метод ExplodeDispatcher::GetParameterState()
                 вернет значение ResultState::rs_UnSupported.
             \en NOT TRANSLATED \~
    \ingroup
*/
class VSN_CLASS ExplodeParameterState
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    ExplodeParameterState() = default;
    /// \ru Деструктор. \en Destructor. \~
    ~ExplodeParameterState();
public:
    /// \ru Получить значение состояния Checked. \en Get Checked state. \~
    bool GetChecked() const;
    /// \ru Получить значение состояния Enabled. \en Get Enabled state. \~
    bool GetEnabled() const;
    /// \ru Установить значение состояния Checked и Enabled. \en Set Checked and Enabled states. \~
    void Set(const bool checked, const bool enabled);
    /// \ru Установить значение состояния Enabled. \en Set Enabled state. \~
    void SetEnabled(const bool enabled);
    /// \ru Валидация установки состояния Checked. \en Check Checked state availability. \~
    bool IsCheckedAvailable() const;
    /// \ru Валидация установки состояния Enabled. \en Check Enabled state availability.. \~
    bool IsEnabledAvailable() const;
private:
    Variant m_checked;
    Variant m_enabled;
};

/** \brief   \ru Класс ExplodeParameterValues используется для получения набора данных диапазонного типа, 
                 определяемых управляющим параметром. Для получения данных используется метод 
                 ExplodeDispatcher::GetParameterValues(). Если для запрашиваемого параметра такой диапазонный 
                 тип не поддерживается, метод  ExplodeDispatcher::GetParameterValues() 
                 вернет значение ResultState::rs_UnSupported.
             \en Class ExplodeParameterValues is used to get a set of a ranges,
                 determined by the control parameter. The method ExplodeDispatcher::GetParameterValues() is used to get data.
                 If for the requested parameter such a range
                 type is not supported, ExplodeDispatcher::GetParameterValues() method
                 will return ResultState::rs_UnSupported. \~
    \ingroup
*/
class VSN_CLASS ExplodeParameterValues
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    ExplodeParameterValues() = default;
    explicit ExplodeParameterValues(const int val, const int valMin, const int valMax, const float valFinal);
    /// \ru Деструктор. \en Destructor. \~
    ~ExplodeParameterValues();
public:
    /// \ru Получить текущее значение параметра. \en Get current parameter value. \~
    int GetCurrentValue() const;
    /// \ru Получить нижнюю границу диапазона значений параметра. \en Get lower bound of the range. \~
    int GetMinimumValue() const;
    /// \ru Получить верхнюю границу диапазона значений параметра. \en Get upper bound of the range. \~
    int GetMaximumValue() const;
    /// \ru Получить значение параметра. \en Get parameter value. \~
    float GetFinalValue() const;
private:
    int m_currentValue = 0;
    int m_minimumValue = 0;
    int m_maximumValue = 0;
    float m_finalValue = 0.0f;
};

class SceneSegment;
class ExplodeDispatcher;
class ExplodeDispatcherPrivate;
/** \brief   \ru Класс ExplodeDispatcher используется для управления процессом разлета объектов 
                 геометрической модели (сегментов сцены), обеспечивает поддержку работы с вкладками GUI и 
                 предоставляет различные режимы просмотра.
             \en Class ExplodeDispatcher is used to manage the process of disassembling objects of the
                 geometric model (scene segments), it also provides support for working with GUI tabs and
                 provides various viewing modes. \~
    \details \ru Функционал “Взрыв” может быть использован в случаях, когда пользователю необходимо с помощью 
                 небольшого числа действий получить представление о составляющих модель объектах, их взаимосвязях 
                 и внутреннем строении модели. В частности, можно получить представление о телах внутри подсборок, 
                 загораживаемых другими телами, в таких случаях использование подходов, связанных со скрытием 
                 некоторых тел, изменением степени их прозрачности может оказаться существенно более трудоёмкой процедурой.
                 Процесс разлета объектов определяется набором управляющих параметров, определенных в типе
                 ExplodeDispatcher::ControlParameterType. За перемещение разлетающихся объектов отвечает параметр cpt_Explode, 
                 причем нулевому значению этого параметра соответствует исходное состояние модели до разлета, 
                 скорость перемещения объектов определяется параметром cpt_Speed. Функционал предоставляет довольно 
                 обширный набор опций по управлению режимами разлета: возможность задавать центр разлета относительно 
                 выбранного объекта (cpt_ExplodeFromItem), разлет относительно центра сцены (cpt_ExplodeFromCenter), 
                 поддерживается разлет в радиальном (cpt_RadialTrajectory), аксиальном (cpt_AxialTrajectory) направлениях 
                 и в направлении, ортогональном к аксиальному (cpt_OrthToAxialTrajectory). API функционала поддерживает 
                 режим многооконного GUI: есть возможность рассматривать выбранные сборки в отдельных вкладках и 
                 настраивать в каждой вкладке необходимый режим разлета независимо от других вкладок. Также поддерживаются: 
                 возможность синхронизации режимов разлета между всеми вкладками, синхронизация параметров, 
                 определяющих режим разлета (cpt_SynchronizeExplode), синхронизация параметров камеры (cpt_SynchronizeCamera) 
                 и селектированных объектов (cpt_SynchronizeSelection). Чтобы визуально уменьшить количество 
                 разлетающихся объектов, можно задать уровень в графе сегментов сцены (параметр cpt_TreeLevel), начиная 
                 с которого подсборки будут перемещаться в составе своих родительских сборок. Например, 
                 можно задать "разлет" корневых сборок так, чтобы подсборки на более высоких уровнях оставались 
                 неподвижными относительно корневых сборок. Функционал предоставляет дополнительные возможности 
                 для быстрого селектирования объектов. По селектированому объекту можно на любом из уровней получить 
                 подсборки (cpt_SelectAssembly), содержащие селектированный объект, в том числе корневую сборку
                 (cpt_SelectRootItem). Для выбора всех элементов в активной вкладке можно использовать параметр cpt_SelectAll.
                 Поддерживается возможность задания фильтров для визуального скрытия объектов, габариты которых 
                 меньше заданной величины (cpt_FilterHideSmallItems) или больше заданной величины (cpt_FilterHideBigItems), 
                 или скрытия объектов, расположенных от заданного центра на расстоянии, большем заданной величины 
                 (cpt_FilterHideByDistance). В активной вкладке можно перейти в режим просмотра (cpt_StartReviewMode) 
                 подсборки выбранной сборки, причем допускается повторный вызов этого режима для просмотра подсборок 
                 текущей подсборки и т.д.; параметр cpt_StopReviewMode используется для возврата из режима просмотра 
                 в исходный режим. Для создания новой вкладки используется метод CreateNewItem(), получающий в качестве параметров
                 имя вкладки и указатель на сегмент, определяющий подсборку в графе сцены. Возможность создания новой вкладки 
                 в текущем режиме можно определить по состоянию параметра (cpt_CreateNewExplodeView). Для текущей вкладки 
                 параметр cpt_ResetExplodeView позволяет сбросить настройки режима просмотра в исходное состояние, параметр
                 cpt_RebuildExplodeView используется для пересчета и перестроения конфигурации разлетающихся объектов 
                 модели относительно выбранного центра; если значение параметра cpt_CollapsOnRebuild установлено в true, 
                 то конфигурация объектов при таком перестроении "схлопнется" в исходное состояние, при этом селектированный 
                 объект не изменит своего положения. При установленном параметре cpt_AutoRebuild (значение true) после 
                 каждого селектирования будет автоматически производиться перестройка конфигурации разлетающихся объектов
                 с новым заданным центром разлета. При селектировании объекта в GUI необходимо передать соответствующий 
                 сегмент графа сцены в ExplodeDispatcher, используя метод SetSelectedSegment(). Метод GetSelectedSegment() 
                 возвращает селектированный объект. Предполагается использование методов SetSelectedSegment(), 
                 GetSelectedSegment() совместно с функционалом по селектированию, определяемым следующими параметрами:
                 cpt_SelectAssembly, cpt_SelectRootItem, cpt_SelectAll.
             \en The “Explosion” functionality can be used when the user needs to use
                 a small number of actions to get an idea of the objects that make up the model, their relationships
                 and internal structure of the model. In particular, you can get an idea of the bodies inside subassemblies,
                 blocked by other bodies. In such cases, the use of approaches like hiding
                 some bodies or changing the degree of their transparency can be much more time-consuming.
                 The decomposition of objects is determined by a set of control parameters defined in the type
                 ExplodeDispatcher::ControlParameterType. The cpt_Explode parameter is responsible for moving disassembled objects,
                 with the zero value of this parameter corresponding to the initial state of the model before the decomposition.
                 The speed at which objects move is determined by the cpt_Speed parameter. The functionality provides quite
                 an extensive set of options for controlling the decomposition modes: the ability to set the center of decomposition relative to
                 selected object (cpt_ExplodeFromItem), decomposition relative to the center of the scene (cpt_ExplodeFromCenter),
                 decomposition is supported in radial direction (cpt_RadialTrajectory), axial direction (cpt_AxialTrajectory)
                 and in the direction orthogonal to the axial (cpt_OrthToAxialTrajectory). The API supports
                 multi-window GUI: it is possible to view selected assemblies in separate tabs and
                 configure the desired decomposition mode in each tab, separately from other tabs. Other supported features:
                 the ability to synchronize the decomposition modes between all tabs, synchronization of parameters that
                 define the decomposition mode (cpt_SynchronizeExplode), synchronization of camera parameters (cpt_SynchronizeCamera)
                 and selected objects (cpt_SynchronizeSelection). To visually reduce the amount of
                 disassembled objects, you can set the level in the scene segment graph (parameter cpt_TreeLevel), starting
                 from which subassemblies will be moved as part of their parent assemblies. For example,
                 you can set the "ecomposition of root assemblies so that subassemblies at higher levels remain
                 fixed relative to the root assemblies. Functionality provides additional features
                 for quick selection of objects. From the selected object, you can get the
                 subassemblies (cpt_SelectAssembly) containing the selected object at any level, including the root assembly
                 (cpt_SelectRootItem). You can use the cpt_SelectAll option to select all items in the active tab.
                 It is possible to set filters to hide objects, whose dimensions are
                 less than the specified value (cpt_FilterHideSmallItems) or greater than the specified value (cpt_FilterHideBigItems),
                 or hide objects located farther from the specified center than the specified value
                 (cpt_FilterHideByDistance). In the active tab, you can switch to review mode (cpt_StartReviewMode) to view
                 subassemblies of the selected assembly. It is also possible to call this mode again to view subassemblies of the
                 current subassembly and so on. The cpt_StopReviewMode parameter is used to return from review mode
                 to original mode. To create a new tab, the CreateNewItem() method is used, which receives as parameters
                 the name of the tab and a pointer to a segment that defines a subassembly in the scene graph. The ability to create a new tab
                 in the current mode can be determined by the state of the parameter (cpt_CreateNewExplodeView). For the current tab
                 the cpt_ResetExplodeView parameter allows you to reset the view mode settings to their original state, the parameter
                 cpt_RebuildExplodeView is used to recalculate and rebuild the configuration of expanding objects
                 models relative to the selected center. If cpt_CollapsOnRebuild is set to true,
                 then the configuration of objects during a rebuild will "collapse" into the initial state, while the selected
                 the object will not change its position. With cpt_AutoRebuild set to true, after
                 each selection, the configuration of disassembled objects will be automatically restructured
                 with a new given center of decomposition. When selecting an object in the GUI, you must pass the appropriate
                 scene graph segment in ExplodeDispatcher using the SetSelectedSegment() method. Method GetSelectedSegment()
                 returns the selected object. The methods SetSelectedSegment() and
                 GetSelectedSegment() are supposed to be used along with the selection functionality defined by the following parameters:
                 cpt_SelectAssembly, cpt_SelectRootItem, cpt_SelectAll. \~
    \note    \ru Функционал “Взрыв” фактически является специальным “режим” отображения модели на уровне графа сцены. Не предполагается, что он
                 заменит специализированные системы по документированию сборок. \n
             \en The “Explosion” functionality is actually a special mode for displaying the model at the scene graph level. It is not supposed to
                 replace specialized systems for documenting assemblies. \n \~
    \ingroup 
*/
class VSN_CLASS ExplodeDispatcher
{
public:
    enum ResultState
    {
        rs_Undefined,
        rs_Success,
        rs_Error,
        rs_ErrorSegmentNotSelected,
        rs_ErrorUnsupported
    };
    enum ControlParameterType
    {
        cpt_Undefined,
        cpt_ExplodeToggled,           ///< \ru Переключение в режим разлета модели и возврат к исходному режиму (bool).
                                      ///  \en Switch to model decomposition mode and return to the original mode (bool). \~
        cpt_Explode,                  ///< \ru Параметр, определяющий коэффициент разлета объектов модели (int). \en A parameter that determines the coefficient of decomposition of model objects (int). \~
        cpt_Speed,                    ///< \ru Параметр, определяющий скорость разлета объектов модели (int). \en A parameter that determines the speed of decomposition of model objects (int). \~
        cpt_TreeLevel,                ///< \ru Параметр определяет уровень в графе сегментов сцены, начиная с которого подсборки модели будут разлетаться в составе своих родительских сборок (int).
                                      ///  \en The parameter defines the level in the graph of segments of the scene, starting from which the subassemblies of the model will fly apart as part of their parent assemblies (int). \~
        cpt_SelectAssembly,           ///< \ru Параметр используется для селектирования на заданном уровне вложенности графа сцены подсборки, содержащей выбранный сегмент (int).
                                      ///  \en The parameter is used to select the subassembly containing the selected segment (int) at the specified level of nesting of the scene graph. \~ 
        cpt_CreateNewExplodeView,     ///< \ru Состояние параметра позволяет определить, возможно ли создание новой вкладки в текущем режиме.
                                      ///  \en The state of the parameter allows you to determine whether it is possible to create a new tab in the current mode. \~
        cpt_StartReviewMode,          ///< \ru Перейти в режим просмотра подсборок. \en Enter subassembly viewing mode. \~
        cpt_StopReviewMode,           ///< \ru Выйти из режима просмотра подсборок. \en Exit subassembly viewing mode. \~
        cpt_RebuildExplodeView,       ///< \ru Перестроить модель разлета относительно выбранного центра. \en Rebuild the decomposition model relative to the selected center. \~
        cpt_ResetExplodeView,         ///< \ru Сбросить в исходное состояние опции разлета модели для данной вкладки. \en Reset model expansion options for this tab. \~
        cpt_SelectAll,                ///< \ru Выбрать все объекты в данной вкладке. \en Select all objects in this tab. \~
        cpt_SelectRootItem,           ///< \ru Выбрать, если возможно,на корневом уровне графа сцены модели подсборку , содержащую выбранный объект.
                                      ///  \en Select, if possible, the subassembly containing the selected object at the root level of the model's scene graph. \~
        cpt_ExplodeFromItem,          ///< \ru Задать режима разлета объектов относительно заданной сборки. \en Set the decomposition mode of objects relative to a given assembly. \~
        cpt_ExplodeFromCenter,        ///< \ru Задать режима разлета объектов относительно центра сцены. \en Set decomposition relative to the center of the scene. \~
        cpt_AutoRebuild,              ///< \ru Установить режим автоматического перестроения модели при селектировании сборки как нового центра разлета.
                                      ///  \en Set the mode of automatic rebuilding of the model when selecting an assembly as a new center of expansion. \~
        cpt_CollapsOnRebuild,         ///< \ru Параметр, который определяет, будет ли модель разлета "схлопываться" в исходное состояние при перестроении модели с новым центром разлета.
                                      ///  \en Parameter that determines whether the decomposition model will "collapse" to its original state when the model is rebuilt with a new decomposition center. \~
        cpt_RadialTrajectory,         ///< \ru Задать радиальный режим разлета (bool). \en Set radial decomposition model. \~
        cpt_AxialTrajectory,          ///< \ru Задать режим разлета вдоль оси симметрии (bool). \en Set expansion mode along symmetry axis (bool). \~
        cpt_OrthToAxialTrajectory,    ///< \ru Задать режим разлета объектов ортогонально оси симметрии (bool). \en Set expansion mode orthogonal to symmetry axis (bool). \~
        cpt_RefineAxisSymmetry,       ///< \ru Применить алгоритмы корректировки оси симметрии (bool). \en Apply symmetry axis correction algorithms (bool). \~
        cpt_FilterHideSmallItems,     ///< \ru Задать параметр фильтра скрытия со сцены объектов, габариты которых меньше заданного параметра (int).
                                      ///  \en Set filter to hide objects whose dimensions are less than the specified parameter. \~
        cpt_FilterHideBigItems,       ///< \ru Задать параметр фильтра скрытия со сцены объектов, габариты которых больше заданного параметра (int).
                                      ///  \en Set filter to hide objects whose dimensions are greater than the specified parameter. \~
        cpt_FilterHideByDistance,     ///< \ru Задать параметр фильтра скрытия со сцены объектов, расстояние от которых до центра больше заданного параметра (int).
                                      ///  \en Set filter to hide objects that are farther from the center than the specified parameter. \~
        cpt_SynchronizeExplode,       ///< \ru Синхронизировать параметры разлета модели во всех вкладках (bool). \en Synchronize model decomposition parameters in all tabs (bool). \~
        cpt_SynchronizeCamera,        ///< \ru Синхронизировать настройки камеры во всех вкладках (bool). \en Synchronize camera settings in all tabs (bool). \~
        cpt_SynchronizeSelection      ///< \ru Синхронизировать селектированные объекты во всех вкладках (bool). \en Synchronize selected objects in all tabs (bool). \~
    };
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit ExplodeDispatcher();
    /// \ru Деструктор. \en Destructor. \~
    ~ExplodeDispatcher();
public:
    /// \ru В качестве параметров инициализации передаются имя основной (главной) вкладки и указатель на корневой сегмент модели.
    /// \en The name of the main (main) tab and a pointer to the root segment of the model are passed as initialization parameters. \~
    void Init(const std::string& mainTabName, const std::string& tabNameSeparator, SceneSegment* pSegmModel);
    /// \ru Получить набор значений параметра. \en Get parameter values. \~
    ResultState GetParameterValues(const ControlParameterType paramType, ExplodeParameterValues& paramValues) const;
    /// \ru Получить состояние параметра. \en Get parameter state. \~
    ResultState GetParameterState(const ControlParameterType paramType, ExplodeParameterState& paramState); //
    /// \ru Установить новое значение управляющих параметров и, если recalculate == ture, пересчитать геометрию разлетающихся объектов (модели разлета).
    /// \en Set a new value for the control parameters and, if recalculate == ture, recalculate the geometry of decomposed objects (decomposition model). \~
    ExplodeDispatcher::ResultState SetParameter(const ControlParameterType paramType, const Variant& data, const bool recalculate = true);
    /// \ru Получить набор управляющих параметров. \en Get control parameters. \~
    std::vector<ControlParameterType> GetControlParameters() const;
    /// \ru Пересчитать модель разлета используя текущее значение параметров.
    /// \en Recalculate the decomposition model using the current parameter values. \~
    void Recalculate();
    /// \ru Метод возвращает значение true, если требуется пересчет геометрии разлетающихся объектов после изменений в параметрах.
    /// \en The method returns true if the geometry of decomposed objects needs to be recalculated after changes in the parameters. \~
    bool IsRecalculateRequired() const;
    /// \ru Получить параметры камеры для текущего вида (текущей вкладки). \en Get camera parameters for the current view (current tab). \~
    void GetCameraOptions(Point3DF& position, Point3DF& targetPosition, Vector3DF& upVector) const;
    /// \ru Установить параметры камеры для текущего вида (текущей вкладки). \en Set camera parameters for the current view (current tab). \~
    void SetCameraOptions(const Point3DF& position, const Point3DF& targetPosition, const Vector3DF& upVector);
    /// \ru Получить селектированный сегмент. \en Get selected segment. \~
    const SceneSegment* GetSelectedSegment() const;
    /// \ru Установить селектированный сегмент и обновить параметры, связанные с селектированием. \en Set selected segment and update selection related parameters. \~
    void SetSelectedSegment(const SceneSegment* pSegm);
    /// \ru Создать вкладку с новым видом. \en Create a tab with a new view. \~
    bool CreateNewItem(const std::string& tabName, const SceneSegment* pSegmSelected);
    /// \ru Сделать активной заданную вкладку. \en Make the specified tab active. \~
    bool SwitchActiveItem(const std::string& tabName);
    /// \ru Удалить указанную вкладку (режим просмотра). \en Delete the specified tab (view mode). \~
    bool RemoveItem(const std::string& tabName);
    /// \ru Получить максимальный номер среди существующих вкладок, может использоваться при генерации имени новой вкладки.
    /// \en Get the maximum number among existing tabs. Can be used when generating a new tab name. \~
    int GetMaximumTabNumber() const;
private:
    VSN_DISABLE_COPY(ExplodeDispatcher);
    VSN_DECLARE_PRIVATE(ExplodeDispatcher);
};

} // namespace VSN

#endif // __VSN_EXPLODEDISPATCHER_H
