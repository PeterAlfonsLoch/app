#pragma once


// Ubuntu apt-get install libx11-dev
#include <X11/Xlib.h>
#include <X11/Xutil.h>
// Ubuntu apt-get install libcairo2-dev

#include "linux_cross_win_gdi.h"

//#include "graphics/draw2d_xlib/draw2d_xlib.h"


void set(XColor & color, COLORREF cr);





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
        //exit ( 1 );
    }

/**code for argb visual*/
  /*  bool  argbVisual=false;
    int32_t screen = DefaultScreen ( dpy );
    Colormap colormap = 0;
    Visual *visual = 0;
    int32_t eventAxis, errorAxis;

    if ( XRenderQueryExtension ( dpy, &eventAxis, &errorAxis ) ) {
        qWarning ("You have ARGB support");
        int32_t nvi;
        XVisualInfo templ;
        templ.screen  = screen;
        templ.depth   = 32;
        templ.c_class = TrueColor;
        XVisualInfo *xvi = XGetVisualInfo ( dpy, VisualScreenMask |
                                            VisualDepthMask |
                                            VisualClassMask, &templ, &nvi );

        for ( int32_t i = 0; i < nvi; ++i ) {
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




