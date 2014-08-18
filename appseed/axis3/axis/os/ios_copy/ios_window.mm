//
//  boot_window.cpp
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/8/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#import "ios_mm.h"



UIWindow * new_boot_window(boot_window * pwindow, CGRect rect)
{
   
//   rect.origin.x     = 0;
//   rect.origin.x     = 0;
//   rect.size.width   = 0;
//   rect.size.height  = 0;
   
   pwindow->m_proundwindow = [mm_window alloc];
   
   pwindow->m_proundwindow->m_pwindow = pwindow;
   
   return [pwindow->m_proundwindow initWithFrame : rect ];
    
}




void ui_shared_application()
{

   [UIApplication sharedApplication];
   
}


void ui_app_run()
{

//   [NSApp run];
   
}



void boot_window::boot_window_show()
{
   
//   [[m_proundwindow->m_controller dd_invokeOnMainThread] showWindow : m_proundwindow];
   
}

void boot_window::boot_window_redraw()
{

//   [[m_proundwindow dd_invokeOnMainThread] display ];
   
   boot_window_invalidate();
   
}


void boot_window::boot_window_invalidate()
{
   
   [[m_proundwindow->childContentView dd_invokeOnMainThread] redraw_view];
   
}


bool boot_window::boot_window_has_focus()
{

   bool b = false;

   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] unsafe_boot_window_has_focus : &b ];

   return b;
   
}


void boot_window::boot_window_destroy()
{

   [m_proundwindow on_destroy];

}