//
//  RoundWindow.m
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
#import "macos_mm.h"


@implementation RoundWindow


//
// initWithContentRect:styleMask:backing:defer:screen:
//
// Init method for the object.
//
- (id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)windowStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)deferCreation
{
   
   m_bNoActivate = false;
   
	self = [super initWithContentRect:contentRect styleMask:NSBorderlessWindowMask backing:bufferingType defer:deferCreation];

	if(self == NULL)
      return NULL;
   
	[self setOpaque:NO];
   
//	[self setOpaque:YES];

   [self setBackgroundColor:[NSColor clearColor]];
		
//	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(mainWindowChanged:) name:NSWindowDidBecomeMainNotification object:self];
		
//	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(mainWindowChanged:) name:NSWindowDidResignMainNotification object:self];
   
   [self setAcceptsMouseMovedEvents : YES];
   
   // Thank yous: http://ios.phonesdevelopers.com/195_17967545/
   // Thank you: Author: unitom Date: 2013-07-14
   // I have a fullscreen transparent window. When the user clicks on it I want the click to be sent to what's underneath the window. How would I do so?
   // Best   Answer
   
//   Setting IgnoresMouseEvents to YES should do the trick..
      
  //    (void)setIgnoresMouseEvents:(BOOL)ignoreMouseEvents

   [self setIgnoresMouseEvents : NO];
   
   
   [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowDidResize:) name:NSWindowDidResizeNotification object:self];
   
   [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowDidMove:) name:NSWindowDidResizeNotification object:self];
   
      
   m_controller = [[NSWindowController alloc] initWithWindow:self];
 
   [self create_view];
   
	return self;
   
}

//
// dealloc
//
// Releases instance memory.
//
- (void)dealloc
{
   
//   id observation = [[NSNotificationCenter defaultCenter] addObserverForName:NSWindowDidResizeNotification object:self usingBlock:^(NSNotification *){
//      NSLog(@"test");
//   }];
   m_pwindow = NULL;
	[[NSNotificationCenter defaultCenter] removeObserver:self];
   
//	[super dealloc];
   
}


//
// setContentSize:
//
// Convert from childContentView to frameView for size.
//
- (void)setContentSize:(NSSize)newSize
{
	
	[super setContentSize:newSize];
   
}

//
// mainWindowChanged:
//
// Redraw the close button when the main window status changes.
//
- (void)mainWindowChanged:(NSNotification *)aNotification
{
   
	[closeButton setNeedsDisplay];
   
}

//
// setContentView:
//
// Keep our frame view as the content view and make the specified "aView"
// the child of that.
//
- (void)create_view
{

	NSRect bounds = [self frame];
	
   bounds.origin = NSZeroPoint;

	RoundWindowFrameView * frameView = [[RoundWindowFrameView alloc] initWithFrame : bounds andRoundWindow: self] ;
   
	[super setContentView : frameView];

	[frameView setFrame : bounds];
   
	[frameView setAutoresizingMask: 0];
   
}

//
// contentView
//
// Returns the child of our frame view instead of our frame view.
//
- (NSView *)contentView
{
   
	return [super contentView];
   
}


//
// canBecomeKeyWindow
//
// Overrides the default to allow a borderless window to be the key window.
//
- (BOOL)canBecomeKeyWindow
{
   
   return YES;
   
}


//
// canBecomeMainWindow
//
// Overrides the default to allow a borderless window to be the main window.
//
- (BOOL)canBecomeMainWindow
{

   return YES;

}

//-

//- (BOOL) acceptsFirstResponder
//{
//   return YES;
//}
//
//- (BOOL) becomeFirstResponder
//{
//   return YES;
//}

/*
 
 let the view become first responder

- (BOOL) acceptsFirstResponder
{
   if(m_bNoActivate)
      return NO;
   else
      return YES;
}

- (BOOL) becomeFirstResponder
{
   if(m_bNoActivate)
      return NO;
   else
   {
      
//      m_pwindow->round_window_on_become_first_responder();
      
      return YES;
      
   }
}

- (BOOL) resignFirstResponder
{
   
   if(m_bNoActivate)
      return YES;
   else
      return NO;
   
}
 
 
 */

#define WINDOW_FRAME_PADDING 0


//
// contentRectForFrameRect:
//
// Returns the rect for the content rect, taking the frame.
//
- (NSRect)contentRectForFrameRect:(NSRect)windowFrame
{
  // bounds = windowFrame;
	windowFrame.origin = NSZeroPoint;
	return NSInsetRect(windowFrame, WINDOW_FRAME_PADDING, WINDOW_FRAME_PADDING);
}

//
// frameRectForContentRect:styleMask:
//
// Ensure that the window is make the appropriate amount bigger than the content.
//
+ (NSRect)frameRectForContentRect:(NSRect)windowContentRect styleMask:(NSUInteger)windowStyle
{
	return NSInsetRect(windowContentRect, -WINDOW_FRAME_PADDING, -WINDOW_FRAME_PADDING);
}


- (void)windowDidResize:(NSNotification *)notification
{

   //NSLog(@"test");
   
   m_pwindow->round_window_resized([self frame].size);
   
}


- (void)windowDidMove:(NSNotification *)notification
{

   //NSLog(@"test");
   
   try
   {
      
      NSRect rect = [self frame];
   
      CGPoint pt;

      pt.x        = rect.origin.x;
   
      pt.y        = [[NSScreen mainScreen] frame ].size.height - (rect.origin.y + rect.size.height);
   
      m_pwindow->round_window_moved(pt);
   
   }
   catch (...)
   {
      
      
      
   }

}

@end
