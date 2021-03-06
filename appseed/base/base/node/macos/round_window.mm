//
//  round_window.cpp
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/8/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#import "macos_mm.h"
#import "RoundWindow.h"


NSWindow * new_round_window(round_window * pwindow, CGRect rect)
{
   
   //rect.origin.x     = 0;
   rect.origin.y     = (int) [[NSScreen mainScreen]frame].size.height - (rect.origin.y + rect.size.height);
   //rect.size.width   = 0;
   //rect.size.height  = 0;
   
/* 
 
   rect.origin.x = 100;
   rect.origin.y = 100;
   rect.size.width   = 800;
   rect.size.height  = 500;
 
*/
   
   pwindow->m_proundwindow = (__bridge_retained void *)[RoundWindow alloc];
   
   ((__bridge RoundWindow *)pwindow->m_proundwindow)->m_pwindow = pwindow;
   
   return [[((__bridge RoundWindow *)pwindow->m_proundwindow) dd_invokeOnMainThreadAndWaitUntilDone:TRUE  ]initWithContentRect : rect styleMask : 0 backing : NSBackingStoreBuffered  defer : false ];
   
}


void ns_app_close()
{
   
   [NSApp terminate:nil];
   
}

void round_window::round_window_set_title(const char * pszTitle)
{
   
   NSString * str = [NSString stringWithUTF8String:pszTitle];
   
   [((__bridge RoundWindow *)m_proundwindow) setTitle:str];
   
}

void round_window::round_window_close()
{
   
   if(m_proundwindow == NULL)
      return;

   void * proundwindow = m_proundwindow;

//   ((RoundWindowFrameView *)((__bridge RoundWindow *)proundwindow)->childContentView)->m_roundwindow = NULL;

   m_proundwindow = NULL;

   ((__bridge RoundWindow *)proundwindow)->m_pwindow = NULL;
   
   [[((__bridge RoundWindow *)proundwindow) dd_invokeOnMainThreadAndWaitUntilDone:TRUE] close];
   
}


void round_window::round_window_show()
{
   
   [[((__bridge RoundWindow *)m_proundwindow)->m_controller dd_invokeOnMainThreadAndWaitUntilDone:TRUE] showWindow : ((__bridge RoundWindow *)m_proundwindow)];
   
   [((__bridge RoundWindow *)m_proundwindow) windowDidExpose];
   
}


void round_window::round_window_hide()
{
    
   [[((__bridge RoundWindow *)m_proundwindow) dd_invokeOnMainThreadAndWaitUntilDone:TRUE] orderOut : ((__bridge RoundWindow *)m_proundwindow)];
   
   [((__bridge RoundWindow *)m_proundwindow) windowWillClose];
    
}

void round_window::round_window_order_front()
{
   
   [[((__bridge RoundWindow *)m_proundwindow) dd_invokeOnMainThreadAndWaitUntilDone:TRUE] orderFront : ((__bridge RoundWindow *)m_proundwindow)];
   
}


void round_window::round_window_make_key_window()
{

   [[((__bridge RoundWindow *)m_proundwindow) dd_invokeOnMainThreadAndWaitUntilDone:TRUE] makeKeyWindow];
   
}


void round_window::round_window_make_key_window_and_order_front()
{
   
   [[((__bridge RoundWindow *)m_proundwindow) dd_invokeOnMainThreadAndWaitUntilDone:TRUE] makeKeyAndOrderFront: ((__bridge RoundWindow *)m_proundwindow)];
   
}


void round_window::round_window_make_main_window()
{
   
   [[((__bridge RoundWindow *)m_proundwindow) dd_invokeOnMainThreadAndWaitUntilDone:TRUE] makeMainWindow];
   
}


void round_window::round_window_redraw()
{

   [[((__bridge RoundWindow *)m_proundwindow) dd_invokeOnMainThreadAndWaitUntilDone:TRUE] display ];
   
}


void round_window::round_window_invalidate()
{
   
//   [[((__bridge RoundWindow *)m_proundwindow)->m_controller dd_invokeOnMainThread] setViewsNeedDisplay : TRUE];
   
}




bool nsapp_activation_policy_is_regular()
{
   
   if(NSApp.activationPolicy == NSApplicationActivationPolicyRegular)
   {
      return true;
   }
   
   return false;
   
}

bool nsapp_activation_policy_is_accessory()
{
   
   if(NSApp.activationPolicy == NSApplicationActivationPolicyAccessory)
   {
      
      return true;
      
   }
   
   return false;
   
}


void nsapp_activation_policy_regular()
{
   
   [[NSApp dd_invokeOnMainThreadAndWaitUntilDone:TRUE ]setActivationPolicy:NSApplicationActivationPolicyRegular];
   
}

void nsapp_activation_policy_accessory()
{
   
   [[NSApp dd_invokeOnMainThreadAndWaitUntilDone:TRUE ]setActivationPolicy:NSApplicationActivationPolicyAccessory];
   
}


void nsapp_activation_policy_prohibited()
{
   
   [[NSApp dd_invokeOnMainThreadAndWaitUntilDone:TRUE ]setActivationPolicy:NSApplicationActivationPolicyProhibited];
   
}


void nsapp_activate_ignoring_other_apps(int i)
{
   
   if(i)
   {
      
      [[NSApp dd_invokeOnMainThreadAndWaitUntilDone:TRUE ]activateIgnoringOtherApps:YES];
      
   }
   else
   {
      
      [[NSApp dd_invokeOnMainThreadAndWaitUntilDone:TRUE ]activateIgnoringOtherApps:NO];
      
   }
   
   
}



