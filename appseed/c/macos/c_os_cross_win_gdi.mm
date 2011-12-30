//
//  c_os_cross_win_gdi.mm
//  c
//
//  Created by Camilo Sasuke Tsumanuma on 12/22/11.
//  Copyright (c) 2011 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include <Cocoa/Cocoa.h>
#include "c_os_cross_win_gdi_internal.h"


CGContextRef get_nswindow_cgcontext(void * pwindow)
{

    NSWindow * pnswindow = (NSWindow * ) pwindow;
    
    return (CGContextRef) [[pnswindow graphicsContext] graphicsPort];

}

bool get_nswindow_rect(LPRECT lprect, void * pwindow)
{
    
    NSWindow * pnswindow = (NSWindow * ) pwindow;
    
    NSRect rect = [pnswindow frame];
    
    lprect->left        = rect.origin.x;
    lprect->top         = rect.origin.y;
    lprect->right       = rect.origin.x + rect.size.width;
    lprect->bottom      = rect.origin.y + rect.size.height;
    
    
    return true;
    
}

