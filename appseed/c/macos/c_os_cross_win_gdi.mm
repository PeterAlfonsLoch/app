//
//  c_os_cross_win_gdi.mm
//  c
//
//  Created by Camilo Sasuke Tsumanuma on 12/22/11.
//  Copyright (c) 2011 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "StdAfx.h"
#include "c_os_cross_win_gdi_internal.h"
#include <Cocoa/Cocoa.h>



HDC GetDC(HWND hwnd)
{
    
    HDC hdc = new device_context;
    
    
    hdc->m_window = hwnd;
    hdc->m_windowPort = GetWindowPort(hwnd);
    GetPortBounds(hdc->m_windowPort, &hdc->m_portBounds);
    
    hdc->m_wasSwapped = QDSwapPort(hwnd->m_windowPort, &hwnd->m_savedPort);
    
    
    /* ... QuickDraw Drawing Commands ... */
    // at windowPort
    
    
    QDBeginCGContext(hdc->m_windowPort, &hdc->m_cgcontext);
    SyncCGContextOriginWithPort(hdc->m_cgcontext, hdc->m_windowPort);
    //ClipCGContextToRegion(cgContext, &portBounds, clippingRegion);
    //DisposeRgn(clippingRegion);
    //clippingRegion = NULL;
    
    /* ... Quartz Drawing Commands ... */
    
    
    hdc->m_cgcolorrefText = mac_create_color(0);
    hdc->m_cgcolorrefBk = mac_create_color(RGB(255, 255, 255));
    
    return hdc;
    
}
