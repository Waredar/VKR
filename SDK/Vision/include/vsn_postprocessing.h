////////////////////////////////////////////////////////////////////////////////
/**
    \file
    \brief \ru Класс UniteVerticesProcess, BuildVertexNormalsProcess является шагом постобработки для 
               определенных действий на полигональном представлении.
           \en NO TRANSLATION. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_UNITEVERTICESPROCESS_H
#define __VSN_UNITEVERTICESPROCESS_H

#include <vsn_string.h>
#include <vsn_global.h>

class MbMesh;

namespace VSN {

class UniteVerticesProcessPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс UniteVerticesProcess является шагом постобработки по определению одинаковых вершин и их удалению.
           \en NO TRANSLATION. \~
    \details \ru UniteVerticesProcess объединяет идентичные вершины во всех сетках. UniteVerticesProcess находит эти 
                 идентичные вершины и удаляет их копии, кроме одной. Обычно это уменьшает количество вершин в сетке 
                 на серьезную величину и увеличивает производительность рендеринга сетки. \n.
             \en NO TRANSLATION. \n \~
    \ingroup Vision_PostProcess
*/
// ---
class VSN_CLASS UniteVerticesProcess
{
public:
    struct InfoProcess
    {
        WString name;
        uint meshIndex;
        uint countVertices;
        uint countUniqueVertices;
        float percent;
    };
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit UniteVerticesProcess();
    /// \ru Деструктор. \en Destructor. \~
    ~UniteVerticesProcess();
public:
    /// \ru Объединяет одинаковые вершины в заданной сетке. \en Combines identical vertices in the given mesh. \~
    void StartProcess(MbMesh* pMesh);
    /// \ru Вернуть информацию о результате процесса. \en Return information about the result of the process.\~
    const ObjectVector<UniteVerticesProcess::InfoProcess>& GetInfoProcess() const;
    /// \ru Очистить массив информации. \en clear the array of information.\~
    void ClearInfoProcess();
protected:
    VSN_DISABLE_COPY(UniteVerticesProcess);
    VSN_DECLARE_PRIVATE(UniteVerticesProcess);
};

class BuildVertexNormalsProcessPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс BuildVertexNormalsProcess является шагом постобработки по 
               вычислению нормалей в каждой вершине.
           \en NO TRANSLATION. \~
    \ingroup Vision_PostProcess
*/
// ---
class VSN_CLASS BuildVertexNormalsProcess
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit BuildVertexNormalsProcess();
    /// \ru Деструктор. \en Destructor. \~
    ~BuildVertexNormalsProcess();
public:
    /// \ru Вычислить нормали в каждой грани. \en Calculate normals in each face. \~
    void StartProcess(MbMesh* pMesh);
protected:
    VSN_DISABLE_COPY(BuildVertexNormalsProcess);
    VSN_DECLARE_PRIVATE(BuildVertexNormalsProcess);
};

class BuildUVMappingProcessPrivate;
// НЕ ГОТОВО...
//------------------------------------------------------------------------------
/** \brief \ru Класс BuildUVMappingProcess является шагом постобработки по вычислению UV - не готово.
           \en NO TRANSLATION - не готово. \~
    \ingroup Vision_PostProcess
*/
// ---

/* BuildVertexNormalsProcess */
class VSN_CLASS BuildUVMappingProcess
{
public:
    enum BuildUVType
    {
        None,
        Sphere,
        Cylinder,
        Plane,
    };
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit BuildUVMappingProcess();
    /// \ru Деструктор. \en Destructor. \~
    ~BuildUVMappingProcess();
public:
    /// \ru Вычислить UV в каждой грани. \en Calculate UV in each face. \~
    void StartProcess(MbMesh* pMesh, BuildUVType type);
protected:
    VSN_DISABLE_COPY(BuildUVMappingProcess);
    VSN_DECLARE_PRIVATE(BuildUVMappingProcess);
};

} // namespace VSN

#endif /* __VSN_UNITEVERTICESPROCESS_H */
