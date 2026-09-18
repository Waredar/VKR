#ifndef __VSN_MARKUP_H
#define __VSN_MARKUP_H

#include <vsn_node.h>
#include <vsn_string.h>
#include <vsn_pen.h>

namespace VSN {

class MarkupGeom;
class GraphicsScene;
class PrMainMarkupPrivate;
class MarkupItemPrivate;

//class Markup;
class VSN_CLASS MarkupItem final : public Node
{
    VSN_OBJECT(MarkupItem);
public:
    MarkupItem(int& viewWidth, int& viewHeight,Node* pParent = nullptr);
    virtual ~MarkupItem();
public:
    void AddGeom(std::shared_ptr<MarkupGeom> item);
    void DeleteGeom(std::shared_ptr<MarkupGeom> item);
public:
    bool IsVisible() const;
    void SetVisible(bool bVisible);
public:
    bool WriteToSVG(const String& strPath);
    bool ReadFromSVG(const String& strPath, GraphicsScene* pScene);
public:
    bool WriteInto(std::string& output);
public:
    void SetPen(const Pen& pen);
    Pen GetPen() const;
public:
    String GetDataTime() const;
public:
    void SetParametrCamera(const Point3DF& pos, const Point3DF& posTarget, const Vector3DF& upVector);
    void GetParametrCamera(Point3DF& pos, Point3DF& posTarget, Vector3DF& upVector);
private:
    VSN_DECLARE_EX_PRIVATE(MarkupItem);
};

//class MainEditerMarkup
class VSN_CLASS PrMainMarkup final : public Object
{
    VSN_OBJECT(PrMainMarkup);
public:
    enum class TypeEditerMarkup
    {
        mrk_LineSegment,
        mrk_Rect,
        mrk_Circle,
        mrk_Ellipse,
        mrk_Path,
    };
public:
    explicit PrMainMarkup(GraphicsScene* pScene,  Object* pParent = nullptr);
    virtual ~PrMainMarkup();
public:
    int CreateMarkup(const Point3DF& pos, const Point3DF& posTarget, const Vector3DF& upVector);
    void DeleteMarkup(int nIndex);
    MarkupItem* GetMarkup(int nIndex);
public:
    size_t SizeMarkups();
public:
    void ResetGeoms();
public:
    void SetPen(const Pen& pen);
public:
    bool CreatePrMarkupGeom(TypeEditerMarkup eType);
public:
    VSN_SIGNAL(Public, OnStopCreateGeom, void OnStopCreateGeom())
private:
    void OnStopProcess(MarkupGeom* item);
private:
    VSN_DECLARE_EX_PRIVATE(PrMainMarkup);
};

} // namespace VSN

#endif // __VSN_MARKUP_H
