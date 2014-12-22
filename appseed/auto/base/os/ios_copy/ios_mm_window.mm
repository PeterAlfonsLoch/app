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
#import "ios_mm.h"


@implementation mm_window


//
// initWithContentRect:styleMask:backing:defer:screen:
//
// Init method for the object.
//
- (id)initWithFrame:(CGRect)contentRect
{
   
	self = [super initWithFrame:contentRect ];

	if(self == NULL)
      return NULL;
   
   [self setWindowLevel:UIWindowLevelAlert];
   
	[self setOpaque:NO];

   [self setBackgroundColor:[UIColor clearColor]];
		
//	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(mainWindowChanged:) name:NSWindowDidBecomeMainNotification object:self];
		
//	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(mainWindowChanged:) name:NSWindowDidResignMainNotification object:self];
   
//   [self setAcceptsMouseMovedEvents : YES];
      
   m_controller = [[UIViewController alloc] init];
 

   [self create_view];
   
   [self setRootViewController : m_controller];
   
   
	return self;
   
}

- (void) unsafe_boot_window_has_focus : (bool *) pbool
{

  /* NSWindow * pkeywindow = [NSApp keyWindow];
   
   NSWindow * pwindow = self;
   
   if(pkeywindow != NULL)
   {

      *pbool = pkeywindow == pwindow;
      
   
   }
   else
   {
      *pbool = false;
   }*/
    
    
}


//
// dealloc
//
// Releases instance memory.
//
- (void)dealloc
{
   
//	[[NSNotificationCenter defaultCenter] removeObserver:self];
   
	[super dealloc];
   
}

-(void) display
{
   [childContentView setNeedsDisplay];
}

//
// setContentSize:
//
// Convert from childContentView to frameView for size.
//
- (void)setContentSize:(CGSize)newSize
{
	
//	[super setContentSize:newSize];
   
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

	CGRect bounds = [self frame];
	
//   bounds.origin = CGZeroPoint;
    

	mm_window_frame_view * frameView = [[mm_window_frame_view alloc] initWithFrame : bounds] ;
   
   frameView->m_roundwindow =  self;
   
   frameView->m_bShift = false;
   frameView->m_bControl = false;
   frameView->m_bAlt = false;
   
   childContentView = frameView;
   
		
//	[super setContentView : frameView];

	[frameView setFrame : bounds];
   
	[frameView setAutoresizingMask: 0];
   
   [ m_controller.view addSubview : frameView];
   
}

//
// contentView
//
// Returns the child of our frame view instead of our frame view.
//
- (UIView *)contentView
{
//return [super contentView];
    return NULL;
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

//
// contentRectForFrameRect:
//
// Returns the rect for the content rect, taking the frame.
//
/*- (CGRect)contentRectForFrameRect:(CGRect)windowFrame
{
  // bounds = windowFrame;
//	windowFrame.origin = NSZeroPoint;
//	return NSInsetRect(windowFrame, NS_ROUND_WINDOW_FRAME_PADDING, NS_ROUND_WINDOW_FRAME_PADDING);
}

//
// frameRectForContentRect:styleMask:
//
// Ensure that the window is make the appropriate amount bigger than the content.
//
+ (NSRect)frameRectForContentRect:(NSRect)windowContentRect styleMask:(NSUInteger)windowStyle
{
	return NSInsetRect(windowContentRect, -NS_ROUND_WINDOW_FRAME_PADDING, -NS_ROUND_WINDOW_FRAME_PADDING);
}
*/

- (void) on_destroy;
{
   
   m_pwindow = NULL;
   
   childContentView->m_roundwindow = nil;
   
   childContentView = nil;
   
   closeButton = nil;
   
   [m_controller release];
   
}





@end
