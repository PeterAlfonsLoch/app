#pragma once


/////////////////////////////////////////////////////////////////////////////
// mirroring support

//WINBUG: some mirroring stuff will be in wingdi.h someday
#ifndef LAYOUT_RTL
#define LAYOUT_RTL                         0x00000001
#define NOMIRRORBITMAP                     0x80000000
#endif

#ifndef LAYOUT_LTR
#define LAYOUT_LTR                               0x00000000
#endif

#ifndef NOMIRRORBITMAP
#define NOMIRRORBITMAP                     0x80000000
#endif

//WINBUG: some mirroring stuff will be in winuser.h someday
#ifndef WS_EX_LAYOUTRTL
#define WS_EX_LAYOUTRTL                    0x00400000L
#endif


#include "draw2d/draw2d.h"


#include "visual/visual.h"





