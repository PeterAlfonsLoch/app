//
//  c_os_cross_win_gdi.mm
//  c
//
//  Created by Camilo Sasuke Tsumanuma on 12/22/11.
//  Copyright (c) 2011 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include <Cocoa/Cocoa.h>
#include "c_os_internal.h"


CGContextRef get_nswindow_cgcontext(HWND hwnd)
{

    return (CGContextRef) [[((NSWindow *) hwnd->m_pnswindow) graphicsContext] graphicsPort];

}

BOOL get_nswindow_rect(HWND hwnd, LPRECT lprect)
{
    
    NSRect rect = [((NSWindow *) hwnd->m_pnswindow) frame];
    
    lprect->left        = rect.origin.x;
    lprect->bottom      = rect.origin.y;
    lprect->right       = rect.origin.x + rect.size.width;
    lprect->top         = rect.origin.y - rect.size.height;
    
    
    return 1;
    
}

