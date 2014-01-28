//
//  RoundWindow.h
//  RoundWindow
//
//  Created by Matt Gallagher on 12/12/08.
//  Copyright 2008 Matt Gallagher. All rights reserved.
//
//  Permission is given to use this source code file without charge in any
//  project, commercial or otherwise, entirely at your risk, with the condition
//  that any redistribution (in part or whole) of source code must retain
//  this copyright and permission notice. Attribution in compiled projects is
//  appreciated but not required.
//
#include "app/appseed/base/user/user/user_key_enum.h"


::user::e_key event_key(NSEvent * event);


class boot_window;
@class mm_window_frame_view;


@interface mm_window : NSWindow
{
@public
   
   
   boot_window             * m_pwindow;
   
   
	mm_window_frame_view    * childContentView;
	NSButton                * closeButton;
   NSWindowController      * m_controller;
   
}

- (void) unsafe_boot_window_has_focus : (bool *) pbool;
- (void) on_destroy;

@end
