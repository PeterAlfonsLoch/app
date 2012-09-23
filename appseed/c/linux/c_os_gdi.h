#pragma once


// Ubuntu apt-get install libx11-dev
#include <X11/Xlib.h>
#include <X11/Xutil.h>


/*
Hi,
if you want to make a ARGB window using xlib/Qt here is the code i use
/**files to include from xlib*/
/*#include <X11/extensions/Xrender.h>
#include <X11/Xlib.h>

/**getting display*/
/*Display *dpy = XOpenDisplay ( 0 ); // open default display
    if ( !dpy ) {
        qWarning ( "Cannot connect to the X server" );
        exit ( 1 );
    }

/**code for argb visual*/
  /*  bool  argbVisual=false;
    int screen = DefaultScreen ( dpy );
    Colormap colormap = 0;
    Visual *visual = 0;
    int eventBase, errorBase;

    if ( XRenderQueryExtension ( dpy, &eventBase, &errorBase ) ) {
        qWarning ("You have ARGB support");
        int nvi;
        XVisualInfo templ;
        templ.screen  = screen;
        templ.depth   = 32;
        templ.c_class = TrueColor;
        XVisualInfo *xvi = XGetVisualInfo ( dpy, VisualScreenMask |
                                            VisualDepthMask |
                                            VisualClassMask, &templ, &nvi );

        for ( int i = 0; i < nvi; ++i ) {
            XRenderPictFormat *format = XRenderFindVisualFormat ( dpy,
                                        xvi[i].visual );
            if ( format->type == PictTypeDirect && format->direct.alphaMask
) {
                visual = xvi[i].visual;
                colormap = XCreateColormap ( dpy, RootWindow ( dpy, screen
),
                                             visual, AllocNone );
                argbVisual=true;
                break;
            }
        }
    }
    /**end of code for argb visual*/




class CLASS_DECL_c simple_brush
{
public:


   int                  m_iStyle;
   COLORREF             m_cr;
   int                  m_iStock;


   simple_brush();
   ~simple_brush();


   // aim to be all-platoform - but if there is no equivalent because no op : create empty method
   bool create_solid(COLORREF cr);
   bool destroy();


   // platform-specific
   bool from_stock(int iId);


};



class CLASS_DECL_c simple_bitmap
{
public:


   Display *               m_pdisplay;
   Pixmap                  m_pixmap;
   simple_memory           m_mem;


   simple_bitmap();
   ~simple_bitmap();


   bool create(int cx, int cy, simple_graphics & g, COLORREF ** ppdata = NULL);
   bool create_from_data(int cx, int cy, COLORREF * pdata, simple_graphics & g);
   bool destroy();


};

class CLASS_DECL_c simple_font
{
public:


   vsstring                m_strFamily;
   int                     m_iWeight;
   int                     m_iSize;
   XFontSet                m_fontset;
   bool                    m_bUpdated;
   Display *               m_pdisplay;
   int                     m_iAscent;
   int                     m_iDescent;


   simple_font();
   ~simple_font();

   bool create_point(int nPointSize, const char * lpszFaceName, simple_graphics & g);
   bool create_point_bold(int nPointSize, const char * lpszFaceName, int BOLD, simple_graphics & g);

   // aim to be all-platoform
   bool destroy();


   // platform-specific
//   bool create_indirect(LPLOGFONT lplf);
   vsstring get_name(int i);
   vsstring get_weight(int iWeight);
   bool update(Display * pdisplay);

};



class CLASS_DECL_c simple_pen
{
public:


   int                  m_iStock;
   int                  m_iStyle;
   int                  m_iWidth;
   COLORREF             m_cr;


   simple_pen();
   ~simple_pen();

   bool create_solid(int iWidth, COLORREF cr);
   bool from_stock(int iId);

   bool destroy();

   simple_pen & operator = (const simple_pen & pen);

};




class CLASS_DECL_c simple_graphics
{
public:


   Display *               m_pdisplay;
   int                     m_iScreen;
   Drawable                m_d;
   GC                      m_gc;
   Colormap                m_colormap;
   simple_pen              m_pen;
   simple_brush            m_brush;
   simple_font             m_font;
   simple_bitmap           m_bitmap;
/*   HWND                    m_hwnd;
   HBITMAP                 m_hbitmapOld;
   HPEN                    m_hpenOld;
   HFONT                   m_hfontOld;
   HBRUSH                  m_hbrushOld;
   int                     m_iType;
   PAINTSTRUCT             m_ps;*/
   int                     m_iType;
   bool                    m_bForeColor;
   bool                    m_bBackColor;
   long unsigned int       m_uiForeColor;
   long unsigned int       m_uiBackColor;
   COLORREF                m_crTextColor;


   simple_graphics();
   ~simple_graphics();


   // aim to be all-platoform - but if there is no equivalent because no op : create empty method
   bool create();
   bool destroy();
   bool bit_blt(int x, int y, int cx, int cy, simple_graphics & gSrc, int x1, int y1, DWORD rop);
   bool alpha_blend(int x, int y, int cx, int cy, simple_graphics & gSrc, int x1, int y1, int cx1, int cy1, BLENDFUNCTION bf);
   bool create_from_bitmap(simple_bitmap & b);
   bool detach_bitmap();
   void fill_solid_rect(LPCRECT lpRect, COLORREF clr);
   bool select(simple_font & font);
   bool select(simple_brush & brush);
   bool select(simple_pen & brush);
   bool text_out(int x, int y, const char * pszUtf8, int iLen = -1);
   bool fill_rect(LPCRECT lpcrect, simple_brush & brush);
   bool blend_bitmap_data(int x, int y, int cx, int cy, COLORREF * pdata);
   bool rectangle(LPCRECT lpcrect);
   SIZE get_text_extent(const char * psz, int iLen = -1);
   bool set_text_color(COLORREF cr);

   // may be multi-platform
   bool create(simple_graphics & g);
   bool create_from_screen();
   bool set_offset(int x, int y);
   bool offset(int x, int y);


   // platform-specific
   bool create(HDC hdc);
   bool from_entire_window(HWND hwnd);
   bool from_window(HWND hwnd);
   bool from_window_paint(HWND hwnd, LPRECT lprectPaint = NULL);
   bool reference_os_data(HDC hdc);
   XFontStruct * get_font(simple_font & font);
   XFontStruct * get_font();
   void select_brush();
   void select_brush(simple_brush & brush);
   void select_pen();
   void select_pen(simple_pen & pen);
   long unsigned int alloc_color(COLORREF cr);
   bool free_color(long unsigned int pixel);
   void set_foreground(COLORREF cr);
   void set_background(COLORREF cr);







};
