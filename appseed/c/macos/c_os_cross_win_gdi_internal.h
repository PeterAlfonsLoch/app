#pragma once


inline int wxRound(double x)
{
#if defined(HAVE_ROUND)
    return int(round(x));
#else
    return (int)(x < 0 ? x - 0.5 : x + 0.5);
#endif
}

//#include <X11/Xlib.h>
//#include <X11/Xutil.h>

/*  ---------------------------------------------------------------------------- */
/*  standard wxWidgets types */
/*  ---------------------------------------------------------------------------- */

/*  the type for screen and DC coordinates */
typedef int wxCoord;


enum { wxDefaultCoord = -1 };


class CLASS_DECL_____ wxSize
{
public:
    // members are public for compatibility, don't use them directly.
    int x, y;
    
    // constructors
    wxSize() : x(0), y(0) { }
    wxSize(int xx, int yy) : x(xx), y(yy) { }
    
    // no copy ctor or assignment operator - the defaults are ok
    
    bool operator==(const wxSize& sz) const { return x == sz.x && y == sz.y; }
    bool operator!=(const wxSize& sz) const { return x != sz.x || y != sz.y; }
    
    wxSize operator+(const wxSize& sz) const { return wxSize(x + sz.x, y + sz.y); }
    wxSize operator-(const wxSize& sz) const { return wxSize(x - sz.x, y - sz.y); }
    wxSize operator/(int i) const { return wxSize(x / i, y / i); }
    wxSize operator*(int i) const { return wxSize(x * i, y * i); }
    
    wxSize& operator+=(const wxSize& sz) { x += sz.x; y += sz.y; return *this; }
    wxSize& operator-=(const wxSize& sz) { x -= sz.x; y -= sz.y; return *this; }
    wxSize& operator/=(const int i) { x /= i; y /= i; return *this; }
    wxSize& operator*=(const int i) { x *= i; y *= i; return *this; }
    
    void IncTo(const wxSize& sz)
    { if ( sz.x > x ) x = sz.x; if ( sz.y > y ) y = sz.y; }
    void DecTo(const wxSize& sz)
    { if ( sz.x < x ) x = sz.x; if ( sz.y < y ) y = sz.y; }
    
    void IncBy(int dx, int dy) { x += dx; y += dy; }
    void IncBy(const wxSize& sz) { IncBy(sz.x, sz.y); }
    void IncBy(int d) { IncBy(d, d); }
    
    void DecBy(int dx, int dy) { IncBy(-dx, -dy); }
    void DecBy(const wxSize& sz) { DecBy(sz.x, sz.y); }
    void DecBy(int d) { DecBy(d, d); }
    
    
    wxSize& Scale(float xscale, float yscale)
    { x = (int)(x*xscale); y = (int)(y*yscale); return *this; }
    
    // accessors
    void Set(int xx, int yy) { x = xx; y = yy; }
    void SetWidth(int w) { x = w; }
    void SetHeight(int h) { y = h; }
    
    int GetWidth() const { return x; }
    int GetHeight() const { return y; }
    
    bool IsFullySpecified() const { return x != wxDefaultCoord && y != wxDefaultCoord; }
    
    // combine this size with the other one replacing the default (i.e. equal
    // to wxDefaultCoord) components of this object with those of the other
    void SetDefaults(const wxSize& size)
    {
        if ( x == wxDefaultCoord )
            x = size.x;
        if ( y == wxDefaultCoord )
            y = size.y;
    }
    
    // compatibility
    int GetX() const { return x; }
    int GetY() const { return y; }
};


class CLASS_DECL_____ wxPoint
{
public:
    int x, y;
    
    wxPoint() : x(0), y(0) { }
    wxPoint(int xx, int yy) : x(xx), y(yy) { }
    
    // no copy ctor or assignment operator - the defaults are ok
    
    // comparison
    bool operator==(const wxPoint& p) const { return x == p.x && y == p.y; }
    bool operator!=(const wxPoint& p) const { return !(*this == p); }
    
    // arithmetic operations (component wise)
    wxPoint operator+(const wxPoint& p) const { return wxPoint(x + p.x, y + p.y); }
    wxPoint operator-(const wxPoint& p) const { return wxPoint(x - p.x, y - p.y); }
    
    wxPoint& operator+=(const wxPoint& p) { x += p.x; y += p.y; return *this; }
    wxPoint& operator-=(const wxPoint& p) { x -= p.x; y -= p.y; return *this; }
    
    wxPoint& operator+=(const wxSize& s) { x += s.GetWidth(); y += s.GetHeight(); return *this; }
    wxPoint& operator-=(const wxSize& s) { x -= s.GetWidth(); y -= s.GetHeight(); return *this; }
    
    wxPoint operator+(const wxSize& s) const { return wxPoint(x + s.GetWidth(), y + s.GetHeight()); }
    wxPoint operator-(const wxSize& s) const { return wxPoint(x - s.GetWidth(), y - s.GetHeight()); }
    
    wxPoint operator-() const { return wxPoint(-x, -y); }
};

typedef Window HWND;

class CLASS_DECL_____ device_context
{
public:
    
    // wxBase Begin
    
    // coordinate system variables
    
    // TODO short descriptions of what exactly they are would be nice...
    
    wxCoord m_logicalOriginX, m_logicalOriginY;
    wxCoord m_deviceOriginX, m_deviceOriginY;
    
    double m_logicalScaleX, m_logicalScaleY;
    double m_userScaleX, m_userScaleY;
    double m_scaleX, m_scaleY;   
    
    // Used by SetAxisOrientation() to invert the axes
    int m_signX, m_signY;
    
    // bounding and clipping boxes
    wxCoord m_minX, m_minY, m_maxX, m_maxY;
    wxCoord m_clipX1, m_clipY1, m_clipX2, m_clipY2;    
    
    // wxBase End
    
    
    
    // in order to preserve the const inheritance of the virtual functions,
    // we have to use mutable variables starting from CWPro 5
    wxPoint                         m_macLocalOrigin;
    mutable void *                  m_macATSUIStyle;    
    
    
    
    CGContextRef    m_gcontext;
    
    
    
    
    device_context() :
    /*  m_colour(wxColourDisplay())
    , m_ok(true)
    , m_clipping(false)
    , m_isInteractive(0)
    , m_isBBoxValid(false)
    , */ m_logicalOriginX(0), m_logicalOriginY(0)
    , m_deviceOriginX(0), m_deviceOriginY(0)
    , m_logicalScaleX(1.0), m_logicalScaleY(1.0)
    , m_userScaleX(1.0), m_userScaleY(1.0)
    , m_scaleX(1.0), m_scaleY(1.0)
    , m_signX(1), m_signY(1)
    , m_minX(0), m_minY(0), m_maxX(0), m_maxY(0)
    , m_clipX1(0), m_clipY1(0), m_clipX2(0), m_clipY2(0)
  /*  , m_logicalFunction(wxCOPY)
    , m_backgroundMode(wxTRANSPARENT)
    , m_mappingMode(wxMM_TEXT)
    , m_pen() */
   /* , m_brush()
    , m_backgroundBrush(*wxTRANSPARENT_BRUSH)
    , m_textForegroundColour(*wxBLACK)
    , m_textBackgroundColour(*wxWHITE)
    , m_font()
#if wxUSE_PALETTE
    , m_palette()
    , m_hasCustomPalette(false)
#endif // wxUSE_PALETTE */   
    {
        m_gcontext = NULL;
    }
    
    wxCoord XDEV2LOG(wxCoord x) const
    {
        return wxRound((double)(x - m_deviceOriginX) / m_scaleX) * m_signX + m_logicalOriginX;
    }
    wxCoord XDEV2LOGREL(wxCoord x) const
    {
        return wxRound((double)(x) / m_scaleX);
    }
    wxCoord YDEV2LOG(wxCoord y) const
    {
        return wxRound((double)(y - m_deviceOriginY) / m_scaleY) * m_signY + m_logicalOriginY;
    }
    wxCoord YDEV2LOGREL(wxCoord y) const
    {
        return wxRound((double)(y) / m_scaleY);
    }
    wxCoord XLOG2DEV(wxCoord x) const
    {
        return wxRound((double)(x - m_logicalOriginX) * m_scaleX) * m_signX + m_deviceOriginX;
    }
    wxCoord XLOG2DEVREL(wxCoord x) const
    {
        return wxRound((double)(x) * m_scaleX);
    }
    wxCoord YLOG2DEV(wxCoord y) const
    {
        return wxRound((double)(y - m_logicalOriginY) * m_scaleY) * m_signY + m_deviceOriginY;
    }
    wxCoord YLOG2DEVREL(wxCoord y) const
    {
        return wxRound((double)(y) * m_scaleY);
    }
    
    wxCoord XLOG2DEVMAC(wxCoord x) const
    {
        return wxRound((double)(x - m_logicalOriginX) * m_scaleX) * m_signX + m_deviceOriginX + m_macLocalOrigin.x;
    }
    
    wxCoord YLOG2DEVMAC(wxCoord y) const
    {
        return wxRound((double)(y - m_logicalOriginY) * m_scaleY) * m_signY + m_deviceOriginY + m_macLocalOrigin.y;
    }    
    
    
    
};

