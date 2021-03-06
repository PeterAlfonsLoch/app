//
//  RoundWindowFrameView.m
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


@implementation mm_window_frame_view

//
// resizeRect
//
// Returns the bounds of the resize box.
//
/*- (CGRect)resizeRect
{
   
	const CGFloat resizeBoxSize = 16.0;
   
	const CGFloat contentViewPadding = 5.5;
	
	CGRect contentViewRect = [[self window] contentRectForFrameRect:[[self window] frame]];
   
	CGRect resizeRect = NSMakeRect(
		NSMaxX(contentViewRect) + contentViewPadding,
		NSMinY(contentViewRect) - resizeBoxSize - contentViewPadding,
		resizeBoxSize,
		resizeBoxSize);
	
	return resizeRect;
   
}*/

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    
    BOOL allTouchesEnded = ([touches count] == [[event touchesForView:self] count]);
   
   boot_window * p = m_roundwindow->m_pwindow;
    
    if ([touches count] == 1 && allTouchesEnded) {
        
        UITouch *touch = [touches anyObject];
        
        if ([touch tapCount] == 1) {
            
            // if touch is a single tap, store its location so we can average it with the second touch location
            
            CGPoint point = [touch locationInView:self];
            
            CGRect e = [[UIScreen mainScreen] applicationFrame];
            
            int H = (int) e.size.height;
            
            int x = point.x;
            
            int y = H - point.y;
            
            p->boot_window_mouse_up(x, y);
            
        } else {
            
//            twoFingerTapIsPossible = NO;
            
        }
        
    }
   
//   CGPoint point = [[self window] convertBaseToScreen:[event locationInWindow]];
   
   return;
   
}


- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
   
   boot_window * p = m_roundwindow->m_pwindow;
   
    if ([touches count] == 1) {
        
        UITouch *touch = [touches anyObject];
        
        if ([touch tapCount] == 1) {
            
            // if touch is a single tap, store its location so we can average it with the second touch location
            
            CGPoint point = [touch locationInView:self];
            
            CGRect e = [[UIScreen mainScreen] applicationFrame];
            
            int H = (int) e.size.height;
            
            int x = point.x;
            
            int y = H - point.y;
            
            p->boot_window_mouse_moved(x, y);
            
        } else {
            
            //            twoFingerTapIsPossible = NO;
            
        }
        
    }
   
   return;
   
}


/*- (void)mouseDragged:(NSEvent *)event
{
   
   boot_window * p = m_roundwindow->m_pwindow;
   
   CGPoint point = [[self window] convertBaseToScreen:[event locationInWindow]];
   
   CGRect e = [[NSScreen mainScreen] frame];
   
   int H = (int) e.size.height;
   
   int x = point.x;
   
   int y = H - point.y;
   
   p->boot_window_mouse_dragged(x, y);
   
   return;
   
   
}
 */


//
// mouseDown:
//
// Handles mouse clicks in our frame. Two actions:
//	- click in the resize box should resize the window
//	- click anywhere else will drag the window.
//
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
   
    
    
    boot_window * p = m_roundwindow->m_pwindow;
 
//    BOOL allTouchesEnded = ([touches count] == [[event touchesForView:self] count]);

//    if ([touches count] == 1 && allTouchesEnded) {
    if ([touches count] == 1) {
        
        UITouch *touch = [touches anyObject];
        
        if ([touch tapCount] == 1) {
            
            // if touch is a single tap, store its location so we can average it with the second touch location
            
            CGPoint point = [touch locationInView:self];
            
            CGRect e = [[UIScreen mainScreen] applicationFrame];
            
            int H = (int) e.size.height;
            
            int x = point.x;
            
            int y = H - point.y;
            
            p->boot_window_mouse_down(x, y);
            
        } else {
            
            //            twoFingerTapIsPossible = NO;
            
        }
        
    }
   
   return;
   
/*	CGPoint pointInView = [self convertPoint:[event locationInWindow] fromView:nil];
	
	BOOL resize = NO;
	if (CGPointInRect(pointInView, [self resizeRect]))
	{
		resize = YES;
	}
	
	NSWindow *window = [self window];
	CGPoint originalMouseLocation = [window convertBaseToScreen:[event locationInWindow]];
	CGRect originalFrame = [window frame];
	
    while (YES)
	{
		//
		// Lock focus and take all the dragged and mouse up events until we
		// receive a mouse up.
		//
        NSEvent *newEvent = [window
			nextEventMatchingMask:(NSLeftMouseDraggedMask | NSLeftMouseUpMask)];
		
        if ([newEvent type] == NSLeftMouseUp)
		{
			break;
		}
		
		//
		// Work out how much the mouse has moved
		//
		CGPoint newMouseLocation = [window convertBaseToScreen:[newEvent locationInWindow]];
		CGPoint delta = NSMakePoint(
			newMouseLocation.x - originalMouseLocation.x,
			newMouseLocation.y - originalMouseLocation.y);
		
		CGRect newFrame = originalFrame;
		
		if (!resize)
		{
			//
			// Alter the frame for a drag
			//
			newFrame.origin.x += delta.x;
			newFrame.origin.y += delta.y;
		}
		else
		{
			//
			// Alter the frame for a resize
			//
			newFrame.size.width += delta.x;
			newFrame.size.height -= delta.y;
			newFrame.origin.y += delta.y;
			
			//
			// Constrain to the window's min and max size
			//
			CGRect newContentRect = [window contentRectForFrameRect:newFrame];
			NSSize maxSize = [window maxSize];
			NSSize minSize = [window minSize];
			if (newContentRect.size.width > maxSize.width)
			{
				newFrame.size.width -= newContentRect.size.width - maxSize.width;
			}
			else if (newContentRect.size.width < minSize.width)
			{
				newFrame.size.width += minSize.width - newContentRect.size.width;
			}
			if (newContentRect.size.height > maxSize.height)
			{
				newFrame.size.height -= newContentRect.size.height - maxSize.height;
				newFrame.origin.y += newContentRect.size.height - maxSize.height;
			}
			else if (newContentRect.size.height < minSize.height)
			{
				newFrame.size.height += minSize.height - newContentRect.size.height;
				newFrame.origin.y -= minSize.height - newContentRect.size.height;
			}
		}
		
		[window setFrame:newFrame display:YES animate:NO];
	}*/
}

- (BOOL) isFlipped
{
   return YES;
}

//
// drawRect:
//
// Draws the frame of the window.
//
- (void)drawRect:(CGRect)rect
{
   
   //	[[NSColor clearColor] set];
	//CGRectFill(rect);

/*
	NSBezierPath * rectPath = [NSBezierPath bezierPathWithRect : [self bounds]];
	
	NSGradient * gradient = [[NSGradient alloc] initWithColorsAndLocations : [NSColor whiteColor], (CGFloat) 0.0, [NSColor lightGrayColor], (CGFloat)1.0, nil];

   [gradient drawInBezierPath : rectPath angle:90];

	[[NSColor whiteColor] set];
	[rectPath stroke];
	
   CGRect resizeRect = [self resizeRect];
	NSBezierPath *resizePath = [NSBezierPath bezierPathWithRect:resizeRect];

	[[NSColor lightGrayColor] set];
	[resizePath fill];

	[[NSColor darkGrayColor] set];
	[resizePath stroke];
	

   [[NSColor blackColor] set];
	NSString *windowTitle = [[self window] title];
	CGRect titleRect = [self bounds];
	titleRect.origin.y = titleRect.size.height - (WINDOW_FRAME_PADDING - 7);
	titleRect.size.height = (WINDOW_FRAME_PADDING - 7);
	NSMutableParagraphStyle *paragraphStyle =
		[[NSMutableParagraphStyle alloc] init];
	[paragraphStyle setAlignment:NSCenterTextAlignment];
	[windowTitle
		drawWithRect:titleRect
		options:0
		attributes:[NSDictionary
			dictionaryWithObjectsAndKeys:
				paragraphStyle, NSParagraphStyleAttributeName,
				[NSFont systemFontOfSize:14], NSFontAttributeName,
			nil]];
 */
   
   if(m_roundwindow == nil)
      return;
  
   boot_window * p = m_roundwindow->m_pwindow;
   
   //   [m_roundwindow disableScreenUpdatesUntilFlush];
   
//   [m_roundwindow disableFlushWindow];
   
   CGContextRef context = UIGraphicsGetCurrentContext();
   
   {
      
      CGRect rectangle = CGRectMake(0, 100, 100, 100);
      CGContextSetRGBFillColor(context, 1.0, 0.0, 0.0, 0.5);
      CGContextSetRGBStrokeColor(context, 0.0, 0.0, 0.0, 0.5);
      CGContextFillRect(context, rectangle);
      CGContextSetLineWidth(context, 5.0f);
      CGContextStrokeRect(context, rectangle);
      
   }
   
   return;

   p->boot_window_draw(context);
   
   {
   CGRect rectangle = CGRectMake(100, 200, 100, 100);
   CGContextSetRGBFillColor(context, 0.0, 0.0, 1.0, 0.5);
   CGContextSetRGBStrokeColor(context, 0.0, 0.0, 0.0, 0.5);
   CGContextFillRect(context, rectangle);
   }

   
   
   
  // [m_roundwindow enableFlushWindow];
   
//   [m_roundwindow flushWindow];
   
}


- (BOOL)acceptsFirstResponder
{
   return TRUE;
}

//- (BOOL) acceptsFirstMouse:(NSEvent *)theEvent//
//{
  // [self mouseDown: theEvent];
   //return YES;
//}





/*
- (void)keyDown:(UIEvent *)event {
   

   ::user::e_key ekey = event_key(event);
   
   boot_window * p = m_roundwindow->m_pwindow;
   
   if(p->boot_window_key_down(ekey, event.characters.UTF8String))
      return;
   
   [super keyDown:event];
   
}

- (void)keyUp:(NSEvent *)event {
   
   
   ::user::e_key ekey = event_key(event);
   
   boot_window * p = m_roundwindow->m_pwindow;
   
   if(p->boot_window_key_up(ekey, event.characters.UTF8String))
      return;
   
   [super keyUp:event];
   
}

- (void)flagsChanged:(NSEvent *)event
{

   boot_window * p = m_roundwindow->m_pwindow;
   
   if([event modifierFlags] & NSShiftKeyMask)
   {
      if(!m_bShift)
      {
         m_bShift = true;
         if(p->boot_window_key_down(::user::key_shift, ""))
            return;
      }
   }
   else
   {
      if(m_bShift)
      {
         m_bShift = false;
         if(p->boot_window_key_up(::user::key_shift, ""))
            return;
      }
   }

   if([event modifierFlags] & NSControlKeyMask)
   {
      if(!m_bControl)
      {
         m_bControl = true;
         if(p->boot_window_key_down(::user::key_control, ""))
            return;
      }
   }
   else
   {
      if(m_bControl)
      {
         m_bControl = false;
         if(p->boot_window_key_up(::user::key_control, ""))
            return;
      }
   }
 
   if([event modifierFlags] & NSAlternateKeyMask)
   {
      if(!m_bAlt)
      {
         m_bAlt = true;
         if(p->boot_window_key_down(::user::key_alt, ""))
            return;
      }
   }
   else
   {
      if(m_bAlt)
      {
         m_bAlt = false;
         if(p->boot_window_key_up(::user::key_alt, ""))
            return;
      }
   }

   [super flagsChanged:event];
}
*/


-(void) redraw_view
{
   
   [self setNeedsDisplay];
   
   
   [[NSRunLoop currentRunLoop] runMode: NSDefaultRunLoopMode beforeDate: [NSDate date]];
}



@end


::user::e_key event_key(UIEvent * event)
{
   /*
   if([event modifierFlags] & NSNumericPadKeyMask) // arrow keys have this mask
   {
      
      NSString * arrow = [event charactersIgnoringModifiers];
      
      unichar key = 0;
      
      if([arrow length] == 0)
         return ::user::key_none;            // reject dead keys
      
      if([arrow length] == 1)
      {
         
         key = [arrow characterAtIndex:0];
         
         if(key == NSLeftArrowFunctionKey)
         {
            
            return ::user::key_left;
            
         }
         
         if(key == NSRightArrowFunctionKey)
         {
            
            return ::user::key_right;
            
         }
         
         if(key == NSUpArrowFunctionKey)
         {
            
            return ::user::key_up;
            
         }
         
         if(key == NSDownArrowFunctionKey)
         {
            
            return ::user::key_down;
            
         }
         
      }
      
   }
   else
   {
      
      unsigned short ush = [event keyCode];
      
      if(ush == 12)
      {
         return ::user::key_q;
      }
      else if(ush == 13)
      {
         return ::user::key_w;
      }
      else if(ush == 14)
      {
         return ::user::key_e;
      }
      else if(ush == 15)
      {
         return ::user::key_r;
      }
      else if(ush == 17)
      {
         return ::user::key_t;
      }
      else if(ush == 16)
      {
         return ::user::key_y;
      }
      else if(ush == 32)
      {
         return ::user::key_u;
      }
      else if(ush == 34)
      {
         return ::user::key_i;
      }
      else if(ush == 31)
      {
         return ::user::key_o;
      }
      else if(ush == 35)
      {
         return ::user::key_p;
      }
      else if(ush == 0)
      {
         return ::user::key_a;
      }
      else if(ush == 1)
      {
         return ::user::key_2;
      }
      else if(ush == 2)
      {
         return ::user::key_d;
      }
      else if(ush == 3)
      {
         return ::user::key_f;
      }
      else if(ush == 5)
      {
         return ::user::key_g;
      }
      else if(ush == 4)
      {
         return ::user::key_h;
      }
      else if(ush == 38)
      {
         return ::user::key_j;
      }
      else if(ush == 40)
      {
         return ::user::key_k;
      }
      else if(ush == 37)
      {
         return ::user::key_l;
      }
      else if(ush == 41)
      {
         return ::user::key_semicolon;
      }
      else if(ush == 6)
      {
         return ::user::key_z;
      }
      else if(ush == 7)
      {
         return ::user::key_x;
      }
      else if(ush == 8)
      {
         return ::user::key_c;
      }
      else if(ush == 9)
      {
         return ::user::key_v;
      }
      else if(ush == 11)
      {
         return ::user::key_b;
      }
      else if(ush == 45)
      {
         return ::user::key_n;
      }
      else if(ush == 46)
      {
         return ::user::key_m;
      }
      else if(ush == 43)
      {
         return ::user::key_comma;
      }
      else if(ush == 47)
      {
         return ::user::key_dot;
      }
      else if(ush == 44)
      {
         //         return ::user::key_;
      }
      else if(ush == 18)
      {
         return ::user::key_1;
      }
      else if(ush == 19)
      {
         return ::user::key_2;
      }
      else if(ush == 20)
      {
         return ::user::key_3;
      }
      else if(ush == 21)
      {
         return ::user::key_4;
      }
      else if(ush == 23)
      {
         return ::user::key_5;
      }
      else if(ush == 22)
      {
         return ::user::key_6;
      }
      else if(ush == 26)
      {
         return ::user::key_7;
      }
      else if(ush == 28)
      {
         return ::user::key_8;
      }
      else if(ush == 25)
      {
         return ::user::key_9;
      }
      else if(ush == 29)
      {
         return ::user::key_0;
      }
      else if(ush == 36)
      {
         return ::user::key_return;
      }
      else if(ush == 48)
      {
         return ::user::key_tab;
      }
      else if(ush == 51)
      {
         return ::user::key_back;
      }
      else if(ush == 117)
      {
         return ::user::key_delete;
      }
      
   }*/
   
   return ::user::key_none;;
   
   
}
