//
//  c_os_cross_win_user.cpp
//  c
//
//  Created by Snow Leopard User on 06/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "StdAfx.h"
#include "c_os_cross_win_user_internal.h"

BOOL IsWindowVisible(HWND hwnd)
{
}


BOOL IsIconic(HWND hwnd)
{
    if(!IsWindowCollapsable(hwnd))
    return FALSE;
    
    CollapseWindow(hwnd);
    return TRUE;
   
    
}