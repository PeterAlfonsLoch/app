//
//  round_window.cpp
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/8/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#import "macos_mm.h"


NSWindow * new_round_window(round_window * pwindow, CGRect rect)
{
   
   rect.origin.x     = 0;
   rect.origin.x     = 0;
   rect.size.width   = 0;
   rect.size.height  = 0;
   
   pwindow->m_proundwindow = [RoundWindow alloc];
   
   pwindow->m_proundwindow->m_pwindow = pwindow;
   
   return [pwindow->m_proundwindow initWithContentRect : rect styleMask : 0 backing : NSBackingStoreBuffered  defer : false ];
   
}


void ns_shared_application()
{

   [RoundWindowApp sharedApplication];
   
}


void ns_app_run()
{

   [NSApp run];
   
}


void round_window::round_window_close()
{
   
   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] close];
   
}


void round_window::round_window_show()
{
   
   [[m_proundwindow->m_controller dd_invokeOnMainThreadAndWaitUntilDone:TRUE] showWindow : m_proundwindow];
   
}


void round_window::round_window_hide()
{
    
   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] orderOut : m_proundwindow];
    
}

void round_window::round_window_order_front()
{
   
   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] orderFront : m_proundwindow];
   
}


void round_window::round_window_make_key_window()
{

   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] makeKeyWindow];
   
}


void round_window::round_window_make_key_window_and_order_front()
{
   
   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] makeKeyAndOrderFront: m_proundwindow];
   
}


void round_window::round_window_make_main_window()
{
   
   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] makeMainWindow];
   
}


void round_window::round_window_redraw()
{

   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] display ];
   
}


void round_window::round_window_invalidate()
{
   
//   [[m_proundwindow->m_controller dd_invokeOnMainThread] setViewsNeedDisplay : TRUE];
   
}

