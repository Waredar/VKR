#ifndef __VSN_DISPLAY_H
#define __VSN_DISPLAY_H

#include <string>
#include <vsn_objectlist.h>
#include <vsn_object.h>
#include <vsn_rect.h>
#include <vsn_size.h>
#include <vsn_global.h>

namespace VSN {

class RectI;
class PlatformDisplay;
class DisplayPrivate;
/* Display */
class VSN_CLASS Display : public Object
{
    VSN_OBJECT(Display)
public:
    enum DisplayOrientation
    {
        PrimaryOrientation = 0x00000000,
        PortraitOrientation = 0x00000001,
        LandscapeOrientation = 0x00000002,
        InvertedPortraitOrientation = 0x00000004,
        InvertedLandscapeOrientation = 0x00000008
    };
public:
    ~Display();
public:
    PlatformDisplay* GetPlatformOpenGLContext() const;

    PlatformDisplay* GetHandle() const;
    std::string GetName() const;

    int GetDepth() const;
    SizeI GetSize() const;
    RectI GetGeometry() const;

    SizeF GetPhysicalSize() const;

    double GetPhysicalDotsPerInchX() const;
    double GetPhysicalDotsPerInchY() const;
    double GetPhysicalDotsPerInch() const;

    double GetLogicalDotsPerInchX() const;
    double GetLogicalDotsPerInchY() const;
    double GetLogicalDotsPerInch() const;

    double GetDevicePixelRatio() const;

    SizeI GetAvailableSize() const;
    RectI GetAvailableGeometry() const;

    ObjectList<Display*> virtualSiblings() const;

    SizeI GetVirtualSize() const;
    RectI GetVirtualGeometry() const;

    SizeI GetAvailableVirtualSize() const;
    RectI GetAvailableVirtualGeometry() const;

    DisplayOrientation GetPrimaryOrientation() const;
    DisplayOrientation GetOrientation() const;
    DisplayOrientation GetNativeOrientation() const;

    uint8 GetOrientationUpdateMask() const;
    void SetOrientationUpdateMask(uint8 mask);

    int GetAngleBetween(DisplayOrientation a, DisplayOrientation b) const;
    RectI GetMapBetween(DisplayOrientation a, DisplayOrientation b, const RectI& rect) const;

    bool IsPortrait(DisplayOrientation orientation) const;
    bool IsLandscape(DisplayOrientation orientation) const;
    double RefreshRate() const;
private:
    explicit Display(PlatformDisplay* pDisplay);
private:
    VSN_DISABLE_COPY(Display)
    friend class PlatformDisplay;
    friend class PlatformIntegration;
protected:
    VSN_DECLARE_EX_PRIVATE(Display)
};

} // namespace VSN

#endif // __VSN_DISPLAY_H

