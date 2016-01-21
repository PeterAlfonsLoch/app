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
   
   //rect.origin.x     = 0;
   //rect.origin.y     = (int) [[NSScreen mainScreen]frame].size.height - rect.origin.y;
   //rect.size.width   = 0;
   //rect.size.height  = 0;
   
/* 
 
   rect.origin.x = 100;
   rect.origin.y = 100;
   rect.size.width   = 800;
   rect.size.height  = 500;
 
*/
   
   pwindow->m_proundwindow = [RoundWindow alloc];
   
   pwindow->m_proundwindow->m_pwindow = pwindow;
   
   return [[pwindow->m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE  ]initWithContentRect : rect styleMask : 0 backing : NSBackingStoreBuffered  defer : false ];
   
}

void ns_shared_application(int argc, char *argv[])
{
  
   NSApplication * application = [NSApplication sharedApplication];
   
   RoundWindowApp * appDelegate = [[RoundWindowApp alloc] init];
   
   [application setDelegate:appDelegate];
   [NSApplication sharedApplication];
   [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
   id menubar = [NSMenu alloc];
   id appMenuItem = [NSMenuItem alloc];
   [menubar addItem:appMenuItem];
   [NSApp setMainMenu:menubar];
   id appMenu = [NSMenu alloc];
   id appName = [[NSProcessInfo processInfo] processName];
   id quitTitle = [@"Quit " stringByAppendingString:appName];
   id quitMenuItem = [[NSMenuItem alloc] initWithTitle:quitTitle
                                                 action:@selector(terminate:) keyEquivalent:@"q"];
   [appMenu addItem:quitMenuItem];
   [appMenuItem setSubmenu:appMenu];
/*   id window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 200, 200)
                                            styleMask:NSTitledWindowMask backing:NSBackingStoreBuffered defer:NO]
                ;
   [window cascadeTopLeftFromPoint:NSMakePoint(20,20)];
   [window setTitle:appName];
   [window makeKeyAndOrderFront:nil];*/
   [NSApp activateIgnoringOtherApps:YES];
   [NSApp run];
//   return 0;
//   NSApplicationMain(argc, (const char **) argv);

//   [RoundWindowApp sharedApplication];
   
}


void ns_app_run()
{

   [NSApp run];
   
}

void ns_app_close()
{
   
   [NSApp terminate:nil];
   
}


void round_window::round_window_close()
{
   
   if(m_proundwindow == NULL)
      return;
   
   m_proundwindow->m_pwindow = NULL;
   
   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] close];
   
   m_proundwindow = NULL;
   
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

