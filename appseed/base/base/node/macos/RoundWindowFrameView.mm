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
#import "macos_mm.h"



/**
 * Key Flags
 */

#define KBDEXT		(USHORT) 0x0100
#define KBDMULTIVK	(USHORT) 0x0200
#define KBDSPECIAL	(USHORT) 0x0400
#define KBDNUMPAD	(USHORT) 0x0800
#define KBDUNICODE	(USHORT) 0x1000
#define KBDINJECTEDVK	(USHORT) 0x2000
#define KBDMAPPEDVK	(USHORT) 0x4000
#define KBDBREAK	(USHORT) 0x8000

/**
 * X11 Keycodes
 */

/**
 * Mac OS X
 */

#define APPLE_VK_ANSI_A			0x00
#define APPLE_VK_ANSI_S			0x01
#define APPLE_VK_ANSI_D			0x02
#define APPLE_VK_ANSI_F			0x03
#define APPLE_VK_ANSI_H			0x04
#define APPLE_VK_ANSI_G			0x05
#define APPLE_VK_ANSI_Z			0x06
#define APPLE_VK_ANSI_X			0x07
#define APPLE_VK_ANSI_C			0x08
#define APPLE_VK_ANSI_V			0x09
#define APPLE_VK_ISO_Section		0x0A
#define APPLE_VK_ANSI_B			0x0B
#define APPLE_VK_ANSI_Q			0x0C
#define APPLE_VK_ANSI_W			0x0D
#define APPLE_VK_ANSI_E			0x0E
#define APPLE_VK_ANSI_R			0x0F
#define APPLE_VK_ANSI_Y			0x10
#define APPLE_VK_ANSI_T			0x11
#define APPLE_VK_ANSI_1			0x12
#define APPLE_VK_ANSI_2			0x13
#define APPLE_VK_ANSI_3			0x14
#define APPLE_VK_ANSI_4			0x15
#define APPLE_VK_ANSI_6			0x16
#define APPLE_VK_ANSI_5			0x17
#define APPLE_VK_ANSI_Equal		0x18
#define APPLE_VK_ANSI_9			0x19
#define APPLE_VK_ANSI_7			0x1A
#define APPLE_VK_ANSI_Minus		0x1B
#define APPLE_VK_ANSI_8			0x1C
#define APPLE_VK_ANSI_0			0x1D
#define APPLE_VK_ANSI_RightBracket	0x1E
#define APPLE_VK_ANSI_O			0x1F
#define APPLE_VK_ANSI_U			0x20
#define APPLE_VK_ANSI_LeftBracket	0x21
#define APPLE_VK_ANSI_I			0x22
#define APPLE_VK_ANSI_P			0x23
#define APPLE_VK_Return			0x24
#define APPLE_VK_ANSI_L			0x25
#define APPLE_VK_ANSI_J			0x26
#define APPLE_VK_ANSI_Quote		0x27
#define APPLE_VK_ANSI_K			0x28
#define APPLE_VK_ANSI_Semicolon		0x29
#define APPLE_VK_ANSI_Backslash		0x2A
#define APPLE_VK_ANSI_Comma		0x2B
#define APPLE_VK_ANSI_Slash		0x2C
#define APPLE_VK_ANSI_N			0x2D
#define APPLE_VK_ANSI_M			0x2E
#define APPLE_VK_ANSI_Period		0x2F
#define APPLE_VK_Tab			0x30
#define APPLE_VK_Space			0x31
#define APPLE_VK_ANSI_Grave		0x32
#define APPLE_VK_Delete			0x33
#define APPLE_VK_0x34			0x34
#define APPLE_VK_Escape			0x35
#define APPLE_VK_0x36			0x36
#define APPLE_VK_Command		0x37
#define APPLE_VK_Shift			0x38
#define APPLE_VK_CapsLock		0x39
#define APPLE_VK_Option			0x3A
#define APPLE_VK_Control		0x3B
#define APPLE_VK_RightShift		0x3C
#define APPLE_VK_RightOption		0x3D
#define APPLE_VK_RightControl		0x3E
#define APPLE_VK_Function		0x3F
#define APPLE_VK_F17			0x40
#define APPLE_VK_ANSI_KeypadDecimal	0x41
#define APPLE_VK_0x42			0x42
#define APPLE_VK_ANSI_KeypadMultiply	0x43
#define APPLE_VK_0x44			0x44
#define APPLE_VK_ANSI_KeypadPlus	0x45
#define APPLE_VK_0x46			0x46
#define APPLE_VK_ANSI_KeypadClear	0x47
#define APPLE_VK_VolumeUp		0x48
#define APPLE_VK_VolumeDown		0x49
#define APPLE_VK_Mute			0x4A
#define APPLE_VK_ANSI_KeypadDivide	0x4B
#define APPLE_VK_ANSI_KeypadEnter	0x4C
#define APPLE_VK_0x4D			0x4D
#define APPLE_VK_ANSI_KeypadMinus	0x4E
#define APPLE_VK_F18			0x4F
#define APPLE_VK_F19			0x50
#define APPLE_VK_ANSI_KeypadEquals	0x51
#define APPLE_VK_ANSI_Keypad0		0x52
#define APPLE_VK_ANSI_Keypad1		0x53
#define APPLE_VK_ANSI_Keypad2		0x54
#define APPLE_VK_ANSI_Keypad3		0x55
#define APPLE_VK_ANSI_Keypad4		0x56
#define APPLE_VK_ANSI_Keypad5		0x57
#define APPLE_VK_ANSI_Keypad6		0x58
#define APPLE_VK_ANSI_Keypad7		0x59
#define APPLE_VK_F20			0x5A
#define APPLE_VK_ANSI_Keypad8		0x5B
#define APPLE_VK_ANSI_Keypad9		0x5C
#define APPLE_VK_JIS_Yen		0x5D
#define APPLE_VK_JIS_Underscore		0x5E
#define APPLE_VK_JIS_KeypadComma	0x5F
#define APPLE_VK_F5			0x60
#define APPLE_VK_F6			0x61
#define APPLE_VK_F7			0x62
#define APPLE_VK_F3			0x63
#define APPLE_VK_F8			0x64
#define APPLE_VK_F9			0x65
#define APPLE_VK_JIS_Eisu		0x66
#define APPLE_VK_F11			0x67
#define APPLE_VK_JIS_Kana		0x68
#define APPLE_VK_F13			0x69
#define APPLE_VK_F16			0x6A
#define APPLE_VK_F14			0x6B
#define APPLE_VK_F10			0x6D
#define APPLE_VK_0x6C			0x6C
#define APPLE_VK_0x6E			0x6E
#define APPLE_VK_F12			0x6F
#define APPLE_VK_0x70			0x70
#define APPLE_VK_F15			0x71
#define APPLE_VK_Help			0x72
#define APPLE_VK_Home			0x73
#define APPLE_VK_PageUp			0x74
#define APPLE_VK_ForwardDelete		0x75
#define APPLE_VK_F4			0x76
#define APPLE_VK_End			0x77
#define APPLE_VK_F2			0x78
#define APPLE_VK_PageDown		0x79
#define APPLE_VK_F1			0x7A
#define APPLE_VK_LeftArrow		0x7B
#define APPLE_VK_RightArrow		0x7C
#define APPLE_VK_DownArrow		0x7D
#define APPLE_VK_UpArrow		0x7E
#define KEYCODE_TYPE_APPLE		0x00000001
#define KEYCODE_TYPE_EVDEV		0x00000002

#ifdef __cplusplus
extern "C" {
#endif
   
   /**
    * Functions
    */
   
   char* GetVirtualKeyName(DWORD vkcode);
   DWORD GetVirtualKeyCodeFromName(const char* vkname);
   DWORD GetVirtualKeyCodeFromXkbKeyName(const char* xkbname);
   
   DWORD GetVirtualKeyCodeFromVirtualScanCode(DWORD scancode, DWORD dwKeyboardType);
   DWORD GetVirtualScanCodeFromVirtualKeyCode(DWORD vkcode, DWORD dwKeyboardType);
   
#define KEYCODE_TYPE_APPLE		0x00000001
#define KEYCODE_TYPE_EVDEV		0x00000002
   
   DWORD GetVirtualKeyCodeFromKeycode(DWORD keycode, DWORD dwFlags);
   DWORD GetKeycodeFromVirtualKeyCode(DWORD keycode, DWORD dwFlags);
   
#ifdef __cplusplus
}
#endif

DWORD fixKeyCode(DWORD keyCode, unichar keyChar, enum APPLE_KEYBOARD_TYPE type)
{
   /**
    * In 99% of cases, the given key code is truly keyboard independent.
    * This function handles the remaining 1% of edge cases.
    *
    * Hungarian Keyboard: This is 'QWERTZ' and not 'QWERTY'.
    * The '0' key is on the left of the '1' key, where '~' is on a US keyboard.
    * A special 'i' letter key with acute is found on the right of the left shift key.
    * On the hungarian keyboard, the 'i' key is at the left of the 'Y' key
    * Some international keyboards have a corresponding key which would be at
    * the left of the 'Z' key when using a QWERTY layout.
    *
    * The Apple Hungarian keyboard sends inverted key codes for the '0' and 'i' keys.
    * When using the US keyboard layout, key codes are left as-is (inverted).
    * When using the Hungarian keyboard layout, key codes are swapped (non-inverted).
    * This means that when using the Hungarian keyboard layout with a US keyboard,
    * the keys corresponding to '0' and 'i' will effectively be inverted.
    *
    * To fix the '0' and 'i' key inversion, we use the corresponding output character
    * provided by OS X and check for a character to key code mismatch: for instance,
    * when the output character is '0' for the key code corresponding to the 'i' key.
    */
   
#if 0
   switch (keyChar)
   {
      case '0':
      case 0x00A7: /* section sign */
         if (keyCode == APPLE_VK_ISO_Section)
            keyCode = APPLE_VK_ANSI_Grave;
         break;
         
      case 0x00ED: /* latin small letter i with acute */
      case 0x00CD: /* latin capital letter i with acute */
         if (keyCode == APPLE_VK_ANSI_Grave)
            keyCode = APPLE_VK_ISO_Section;
         break;
   }
#endif
   
   /* Perform keycode correction for all ISO keyboards */
   
   if (type == APPLE_KEYBOARD_TYPE_ISO)
   {
      if (keyCode == APPLE_VK_ANSI_Grave)
         keyCode = APPLE_VK_ISO_Section;
      else if (keyCode == APPLE_VK_ISO_Section)
         keyCode = APPLE_VK_ANSI_Grave;
   }
   
   return keyCode;
}


@implementation RoundWindowFrameView


- (id)initWithFrame:(NSRect)frame andRoundWindow:(RoundWindow *)roundwindow
{

   self = [super initWithFrame:frame];
   
   appleKeyboardType = mac_detect_keyboard_type();
   
   m_roundwindow =  roundwindow;
   
   m_bLShift = false;
   m_bRShift = false;
   m_bLControl = false;
   m_bRControl = false;
   m_bLAlt = false;
   m_bRAlt = false;
   m_bLCommand = false;
   m_bRCommand = false;

   return self;
   
}


//
// resizeRect
//
// Returns the bounds of the resize box.
//
- (NSRect)resizeRect
{
   
	const CGFloat resizeBoxSize = 16.0;
   
	const CGFloat contentViewPadding = 5.5;
	
	NSRect contentViewRect = [[self window] contentRectForFrameRect:[[self window] frame]];
   
	NSRect resizeRect = NSMakeRect(
		NSMaxX(contentViewRect) + contentViewPadding,
		NSMinY(contentViewRect) - resizeBoxSize - contentViewPadding,
		resizeBoxSize,
		resizeBoxSize);
	
	return resizeRect;
   
}


- (void)mouseUp:(NSEvent *)event
{

   round_window * p = m_roundwindow->m_pwindow;
   
   if(p == NULL)
      return;
    
   NSRect e = [m_roundwindow frame];
   
   NSPoint point = [event locationInWindow];
   
   point.x = point.x + e.origin.x;

   point.y = point.y + e.origin.y;
   
   int H = (int) [[NSScreen mainScreen] frame].size.height;
   
   int x = point.x;
   
   int y = H - point.y;
   
   // Left Button
   
   int iButton = 0;
   
   p->round_window_mouse_up(iButton, x, y);
   
   return;
   
}


- (void)mouseMoved:(NSEvent *)event
{

   round_window * p = m_roundwindow->m_pwindow;
   
   if(p == NULL)
      return;
   
    NSRect e = [m_roundwindow frame];
    
    NSPoint point = [event locationInWindow];
    
   point.x = point.x + e.origin.x;
   
   point.y = point.y + e.origin.y;
   
   int H = (int) [[NSScreen mainScreen] frame].size.height;
   
   int x = point.x;
   
   int y = H - point.y;
   
   p->round_window_mouse_moved(x, y);
   
   return;
   
}


- (void)mouseDragged:(NSEvent *)event
{

   round_window * p = m_roundwindow->m_pwindow;
   
   if(p == NULL)
      return;
   
   NSRect e = [m_roundwindow frame];
    
   NSPoint point = [event locationInWindow];
    
   point.x = point.x + e.origin.x;
   
   point.y = point.y + e.origin.y;
   
   int H = (int) [[NSScreen mainScreen] frame].size.height;
   
   int x = point.x;
   
   int y = H - point.y;
   
   p->round_window_mouse_dragged(x, y);
   
}


//
// mouseDown:
//
// Handles mouse clicks in our frame. Two actions:
//	- click in the resize box should resize the window
//	- click anywhere else will drag the window.
//

///////////////////////////////
//
//   Left click only
//
- (void)mouseDown:(NSEvent *)event
{
   
   round_window * p = m_roundwindow->m_pwindow;
   
   if(p == NULL)
      return;
   
   NSRect e = [m_roundwindow frame];
    
   NSPoint point = [event locationInWindow];
    
   point.x = point.x + e.origin.x;
   
   point.y = point.y + e.origin.y;
   
   int H = (int) [[NSScreen mainScreen] frame].size.height;
   
   int x = point.x;
   
   int y = H - point.y;
   
   // Left Button
   
   int iButton = 0;
   
   p->round_window_mouse_down(iButton, x, y);
   
   return;
   
}


- (void)rightMouseUp:(NSEvent *)event
{
   
   round_window * p = m_roundwindow->m_pwindow;
   
   if(p == NULL)
      return;
   
   NSRect e = [m_roundwindow frame];
   
   NSPoint point = [event locationInWindow];
   
   point.x = point.x + e.origin.x;
   
   point.y = point.y + e.origin.y;
   
   int H = (int) [[NSScreen mainScreen] frame].size.height;
   
   int x = point.x;
   
   int y = H - point.y;
   
   // Right Button
   
   int iButton = 1;
   
   p->round_window_mouse_up(iButton, x, y);
   
   return;
   
}


- (void)rightMouseDown:(NSEvent *)event
{
   
   round_window * p = m_roundwindow->m_pwindow;
   
   if(p == NULL)
      return;
   
   NSRect e = [m_roundwindow frame];
   
   NSPoint point = [event locationInWindow];
   
   point.x = point.x + e.origin.x;
   
   point.y = point.y + e.origin.y;
   
   int H = (int) [[NSScreen mainScreen] frame].size.height;
   
   int x = point.x;
   
   int y = H - point.y;
  
   // Right Button
   
   int iButton = 1;
   
   p->round_window_mouse_down(iButton, x, y);
   
   return;

}


- (BOOL) isFlipped
{
   
   return YES;
   
}


#define WINDOW_FRAME_PADDING 32

- (void)drawDebugRect:(NSRect)rect
{
   
   /*
    
    //   [super drawRect:rect];
    
    
    // return;
    
    BOOL bWindowVisible = [m_roundwindow isVisible];
    
    BOOL bViewHidden = [self isHidden];
    
    NSRect e = [m_roundwindow frame];
    
    NSRect e2 = [[NSScreen mainScreen] frame];
    
    double a = [m_roundwindow alphaValue];
    
    
    
    
    
    CGContextRef cgc1 = (CGContextRef) [[NSGraphicsContext currentContext] graphicsPort];
    
    
    COLORREF cr = ARGB(255, 0, 0, 0);
    
    
    CGContextSetBlendMode(cgc1, kCGBlendModeCopy);
    
    
    CGContextSetRGBFillColor(cgc1, argb_get_r_value(cr) / 255.0f, argb_get_g_value(cr) / 255.0f, argb_get_b_value(cr) / 255.0f, argb_get_a_value(cr) / 255.0f);
    
    
    CGContextFillRect(cgc1, rect);
    
    
    
    
    
    //   [[NSColor greenColor] set];
    
    //   NSRectFill(rect);
    
    return;
    
    */
   
   /* 	[[NSColor clearColor] set];
    NSRectFill(rect);
    
    NSBezierPath * rectPath = [NSBezierPath bezierPathWithRect : [self bounds]];
    
    NSGradient * gradient = [[NSGradient alloc] initWithColorsAndLocations : [NSColor whiteColor], (CGFloat) 0.0, [NSColor lightGrayColor], (CGFloat)1.0, nil];
    
    [gradient drawInBezierPath : rectPath angle:90];
    
    [[NSColor whiteColor] set];
    [rectPath stroke];
    
    NSRect resizeRect = [self resizeRect];
    NSBezierPath *resizePath = [NSBezierPath bezierPathWithRect:resizeRect];
    
    [[NSColor lightGrayColor] set];
    [resizePath fill];
    
    [[NSColor darkGrayColor] set];
    [resizePath stroke];
    
    
    [[NSColor blackColor] set];
    NSString *windowTitle = [[self window] title];
    NSRect titleRect = [self bounds];
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
    
    
    return; */

}


//
// drawRect:
//
// Draws the frame of the window.
//
- (void)drawRect:(NSRect)rect
{

   // [[self drawDebugRect] rect];
  
   round_window * p = m_roundwindow->m_pwindow;
   
   if(p == NULL)
      return;
   
   CGContextRef cgc = (CGContextRef) [[NSGraphicsContext currentContext] graphicsPort];
   
   p->round_window_draw(cgc);
   
}


- (BOOL)acceptsFirstResponder
{

   return TRUE;

}


- (BOOL) acceptsFirstMouse:(NSEvent *)theEvent
{

//printf("\nacceptsFirstMouse\n");
   
   if(![NSApp isActive])
   {
      
      [NSApp activate];
      
   }
   
   if(![m_roundwindow isKeyWindow])
   {
      
      [m_roundwindow makeKeyWindow];
      
   }
   
//   if(![m_roundwindow isMainWindow])
//   {
//
//      [m_roundwindow makeMainWindow];
//
//   }
//   
//   if([[NSApp orderedWindows] firstObject] != m_roundwindow)
//   {
//   
//      [m_roundwindow orderFront:self];
//      
//   }

   return YES;
   
}


- (BOOL) mouseDownCanMoveWindow
{

   return NO;

}

//
//// from RoundWindow.mm
//
///*- (BOOL) acceptsFirstResponder
//{
//   if(m_bNoActivate)
//      return NO;
//   else
//      return YES;
//}*/
//
//- (BOOL) becomeFirstResponder
//{
//   return YES;
//}
////   if(m_bNoActivate)
//  //    return NO;
//  // else
//  // {
//      
//      //      m_pwindow->round_window_on_become_first_responder();
//      
//    //  return YES;
//      
//  // }
////}
//
////- (BOOL) resignFirstResponder
////{
////   return YES;
////   //if(m_bNoActivate)
////     // return YES;
////   //else
////  //    return YES;
////   
////}
//

#define DO_FLAG(m_f, p, now, key) \
if(m_f) \
{ \
if(!now) \
{ \
p->round_window_key_up(key); \
m_f = false; \
} \
} \
else \
{ \
if(now) \
{ \
p->round_window_key_down(key); \
m_f = true; \
} \
}


- (void)keyDown:(NSEvent *)event
{

   unsigned int uiKeyCode = event_key_code(event);
//   
//   
//   round_window * p = m_roundwindow->m_pwindow;
//   
//   if(p == NULL)
//      return;
//   
//   bool bLCommand = [event modifierFlags] & (1 << 4);
//   bool bRCommand = [event modifierFlags] & (1 << 5);
//   
//   DO_FLAG(m_bLCommand, p, bLCommand, 2031)
//   DO_FLAG(m_bRCommand, p, bRCommand, 2033)
//   
//   if(p->round_window_key_down(uiKeyCode))
//      return;
   
   round_window * p = m_roundwindow->m_pwindow;
     
   if(p == NULL)
      return;
   
   DWORD keyCode;
   DWORD keyFlags;
   DWORD vkcode;
   DWORD scancode;
   unichar keyChar;
   NSString* characters;
   
//   if (!is_connected)
  //    return;
   
//   keyFlags = KBD_FLAGS_DOWN;
   
   bool bLCommand = [event modifierFlags] & (1 << 4);
   bool bRCommand = [event modifierFlags] & (1 << 5);
      
//   DO_FLAG(m_bLCommand, p, bLCommand, 2031)
//   DO_FLAG(m_bRCommand, p, bRCommand, 2033)
   
   keyCode = [event keyCode];
   
   characters = [event charactersIgnoringModifiers];
   
   if ([characters length] > 0)
   {
      keyChar = [characters characterAtIndex:0];
      keyCode = fixKeyCode(keyCode, keyChar, appleKeyboardType);
   }
   
//   if(uiKeyCode != 0)
//   {
//   
//      vkcode = uiKeyCode;
//      
//   }
//   else
//   {
   
      vkcode = GetVirtualKeyCodeFromKeycode(keyCode + 8, KEYCODE_TYPE_APPLE);
      
//   }
   scancode = GetVirtualScanCodeFromVirtualKeyCode(vkcode, 4);
   keyFlags |= (scancode & KBDEXT) ? KBDEXT : 0;
   scancode &= 0xFF;
   vkcode &= 0xFF;
   
#if 0
   WLog_ERR(TAG,  "keyDown: keyCode: 0x%04X scancode: 0x%04X vkcode: 0x%04X keyFlags: %d name: %s",
            keyCode, scancode, vkcode, keyFlags, GetVirtualKeyName(vkcode));
#endif
   
   
   if(p->round_window_key_down(vkcode, scancode))
      return;

//   freerdp_input_send_keyboard_event(instance->input, keyFlags, scancode);
   
   [super keyDown:event];
   
}


// end from RoundWindow.mm
- (void)keyUp:(NSEvent *)event
{
   
   unsigned int uiKeyCode = event_key_code(event);
//   
//   round_window * p = m_roundwindow->m_pwindow;
//   
//   if(p == NULL)
//      return;
//   
//   bool bLCommand = [event modifierFlags] & (1 << 4);
//   bool bRCommand = [event modifierFlags] & (1 << 5);
//   
//   DO_FLAG(m_bLCommand, p, bLCommand, 2031)
//   DO_FLAG(m_bRCommand, p, bRCommand, 2033)
//   
//   if(p->round_window_key_up(uiKeyCode))
//      return;
//   
   DWORD keyCode;
   DWORD keyFlags;
   DWORD vkcode;
   DWORD scancode;
   unichar keyChar;
   NSString* characters;
   
   //   if (!is_connected)
   //    return;
   
   //   keyFlags = KBD_FLAGS_DOWN;

   round_window * p = m_roundwindow->m_pwindow;
   
   if(p == NULL)
      return;
   
   bool bLCommand = [event modifierFlags] & (1 << 4);
   bool bRCommand = [event modifierFlags] & (1 << 5);
      
//   DO_FLAG(m_bLCommand, p, bLCommand, 2031)
//   DO_FLAG(m_bRCommand, p, bRCommand, 2033)
   
   
   keyCode = [event keyCode];
   
   characters = [event charactersIgnoringModifiers];
   
   if ([characters length] > 0)
   {
      keyChar = [characters characterAtIndex:0];
      keyCode = fixKeyCode(keyCode, keyChar, appleKeyboardType);
   }
   
//   if(uiKeyCode != 0)
//   {
//      
//      vkcode = uiKeyCode;
//      
//   }
//   else
//   {
   
      vkcode = GetVirtualKeyCodeFromKeycode(keyCode + 8, KEYCODE_TYPE_APPLE);
      
//   }
   scancode = GetVirtualScanCodeFromVirtualKeyCode(vkcode, 4);
   keyFlags |= (scancode & KBDEXT) ? KBDEXT : 0;
   scancode &= 0xFF;
   vkcode &= 0xFF;
   
#if 0
   WLog_ERR(TAG,  "keyDown: keyCode: 0x%04X scancode: 0x%04X vkcode: 0x%04X keyFlags: %d name: %s",
            keyCode, scancode, vkcode, keyFlags, GetVirtualKeyName(vkcode));
#endif
   
   
   if(p->round_window_key_up(vkcode, scancode))
      return;
   
   //   freerdp_input_send_keyboard_event(instance->input, keyFlags, scancode);
   
   [super keyUp:event];
   
}




- (void)flagsChanged:(NSEvent *)event
{

   round_window * p = m_roundwindow->m_pwindow;
   
   if(p == NULL)
      return;
   int key;
   DWORD keyFlags;
   DWORD vkcode;
   DWORD scancode;
   DWORD modFlags;
   
   //if (!is_connected)
     // return;
   
   keyFlags = 0;
   key = [event keyCode] + 8;
   modFlags = [event modifierFlags] & NSDeviceIndependentModifierFlagsMask;
   
   vkcode = GetVirtualKeyCodeFromKeycode(key, KEYCODE_TYPE_APPLE);
   scancode = GetVirtualScanCodeFromVirtualKeyCode(vkcode, 4);
   keyFlags |= (scancode & KBDEXT) ? KBDEXT : 0;
   scancode &= 0xFF;
   vkcode &= 0xFF;
   
#if 0
   WLog_DBG(TAG,  "flagsChanged: key: 0x%04X scancode: 0x%04X vkcode: 0x%04X extended: %d name: %s modFlags: 0x%04X",
            key - 8, scancode, vkcode, keyFlags, GetVirtualKeyName(vkcode), modFlags);
   
   if (modFlags & NSAlphaShiftKeyMask)
      WLog_DBG(TAG,  "NSAlphaShiftKeyMask");
   
   if (modFlags & NSShiftKeyMask)
      WLog_DBG(TAG,  "NSShiftKeyMask");
   
   if (modFlags & NSControlKeyMask)
      WLog_DBG(TAG,  "NSControlKeyMask");
   
   if (modFlags & NSAlternateKeyMask)
      WLog_DBG(TAG,  "NSAlternateKeyMask");
   
   if (modFlags & NSCommandKeyMask)
      WLog_DBG(TAG,  "NSCommandKeyMask");
   
   if (modFlags & NSNumericPadKeyMask)
      WLog_DBG(TAG,  "NSNumericPadKeyMask");
   
   if (modFlags & NSHelpKeyMask)
      WLog_DBG(TAG,  "NSHelpKeyMask");
#endif

   
   if ((modFlags & NSAlphaShiftKeyMask) && !(kbdModFlags & NSAlphaShiftKeyMask))
      p->round_window_key_down(vkcode, scancode);
   else if (!(modFlags & NSAlphaShiftKeyMask) && (kbdModFlags & NSAlphaShiftKeyMask))
      p->round_window_key_up(vkcode, scancode);
   
   if ((modFlags & NSShiftKeyMask) && !(kbdModFlags & NSShiftKeyMask))
      p->round_window_key_down(vkcode, scancode);
   else if (!(modFlags & NSShiftKeyMask) && (kbdModFlags & NSShiftKeyMask))
      p->round_window_key_up(vkcode, scancode);
   
   if ((modFlags & NSControlKeyMask) && !(kbdModFlags & NSControlKeyMask))
      p->round_window_key_down(vkcode, scancode);
   else if (!(modFlags & NSControlKeyMask) && (kbdModFlags & NSControlKeyMask))
      p->round_window_key_up(vkcode, scancode);
   
   if ((modFlags & NSAlternateKeyMask) && !(kbdModFlags & NSAlternateKeyMask))
      p->round_window_key_down(vkcode, scancode);
   else if (!(modFlags & NSAlternateKeyMask) && (kbdModFlags & NSAlternateKeyMask))
      p->round_window_key_up(vkcode, scancode);
   
   if ((modFlags & NSCommandKeyMask) && !(kbdModFlags & NSCommandKeyMask))
      p->round_window_key_down(vkcode, scancode);
   else if (!(modFlags & NSCommandKeyMask) && (kbdModFlags & NSCommandKeyMask))
      p->round_window_key_up(vkcode, scancode);
   
   if ((modFlags & NSNumericPadKeyMask) && !(kbdModFlags & NSNumericPadKeyMask))
      p->round_window_key_down(vkcode, scancode);
   else if (!(modFlags & NSNumericPadKeyMask) && (kbdModFlags & NSNumericPadKeyMask))
      p->round_window_key_up(vkcode, scancode);
   
   if ((modFlags & NSHelpKeyMask) && !(kbdModFlags & NSHelpKeyMask))
      p->round_window_key_down(vkcode, scancode);
   else if (!(modFlags & NSHelpKeyMask) && (kbdModFlags & NSHelpKeyMask))
      p->round_window_key_up(vkcode, scancode);
   
//   if ((modFlags & NSAlphaShiftKeyMask) && !(kbdModFlags & NSAlphaShiftKeyMask))
//      freerdp_input_send_keyboard_event(instance->input, keyFlags | KBD_FLAGS_DOWN, scancode);
//   else if (!(modFlags & NSAlphaShiftKeyMask) && (kbdModFlags & NSAlphaShiftKeyMask))
//      freerdp_input_send_keyboard_event(instance->input, keyFlags | KBD_FLAGS_RELEASE, scancode);
//   
//   if ((modFlags & NSShiftKeyMask) && !(kbdModFlags & NSShiftKeyMask))
//      freerdp_input_send_keyboard_event(instance->input, keyFlags | KBD_FLAGS_DOWN, scancode);
//   else if (!(modFlags & NSShiftKeyMask) && (kbdModFlags & NSShiftKeyMask))
//      freerdp_input_send_keyboard_event(instance->input, keyFlags | KBD_FLAGS_RELEASE, scancode);
//   
//   if ((modFlags & NSControlKeyMask) && !(kbdModFlags & NSControlKeyMask))
//      freerdp_input_send_keyboard_event(instance->input, keyFlags | KBD_FLAGS_DOWN, scancode);
//   else if (!(modFlags & NSControlKeyMask) && (kbdModFlags & NSControlKeyMask))
//      freerdp_input_send_keyboard_event(instance->input, keyFlags | KBD_FLAGS_RELEASE, scancode);
//   
//   if ((modFlags & NSAlternateKeyMask) && !(kbdModFlags & NSAlternateKeyMask))
//      freerdp_input_send_keyboard_event(instance->input, keyFlags | KBD_FLAGS_DOWN, scancode);
//   else if (!(modFlags & NSAlternateKeyMask) && (kbdModFlags & NSAlternateKeyMask))
//      freerdp_input_send_keyboard_event(instance->input, keyFlags | KBD_FLAGS_RELEASE, scancode);
//   
//   if ((modFlags & NSCommandKeyMask) && !(kbdModFlags & NSCommandKeyMask))
//      freerdp_input_send_keyboard_event(instance->input, keyFlags | KBD_FLAGS_DOWN, scancode);
//   else if (!(modFlags & NSCommandKeyMask) && (kbdModFlags & NSCommandKeyMask))
//      freerdp_input_send_keyboard_event(instance->input, keyFlags | KBD_FLAGS_RELEASE, scancode);
//   
//   if ((modFlags & NSNumericPadKeyMask) && !(kbdModFlags & NSNumericPadKeyMask))
//      freerdp_input_send_keyboard_event(instance->input, keyFlags | KBD_FLAGS_DOWN, scancode);
//   else if (!(modFlags & NSNumericPadKeyMask) && (kbdModFlags & NSNumericPadKeyMask))
//      freerdp_input_send_keyboard_event(instance->input, keyFlags | KBD_FLAGS_RELEASE, scancode);
//   
//   if ((modFlags & NSHelpKeyMask) && !(kbdModFlags & NSHelpKeyMask))
//      freerdp_input_send_keyboard_event(instance->input, keyFlags | KBD_FLAGS_DOWN, scancode);
//   else if (!(modFlags & NSHelpKeyMask) && (kbdModFlags & NSHelpKeyMask))
//      freerdp_input_send_keyboard_event(instance->input, keyFlags | KBD_FLAGS_RELEASE, scancode);
   
   kbdModFlags = modFlags;
   
//   
//   unsigned int ui = [event modifierFlags];
//   bool sl = (ui & 2) != 0;;
//   bool sr = (ui & 4) != 0;
//   bool cl = (ui & 1) != 0;;
//   bool cr = (ui & (1 << 13)) != 0;
//   bool al = (ui & (1 << 5)) != 0;;
//   bool ar = (ui & (1 << 6)) != 0;
//   
//   
//   DO_FLAG(m_bLShift, p, sl, 2001)
//   DO_FLAG(m_bRShift, p, sr, 2003)
//   DO_FLAG(m_bLControl, p, cl, 2011)
//   DO_FLAG(m_bRControl, p, cr, 2013)
//   DO_FLAG(m_bLAlt, p, al, 2021)
//   DO_FLAG(m_bRAlt, p, ar, 2023)

   [super flagsChanged:event];
   
}

@end


unsigned int event_num_pad_key_code(NSEvent * event)
{

   NSString * arrow = [event charactersIgnoringModifiers];
   
   if([arrow length] == 1)
   {
      
      unichar key = [arrow characterAtIndex:0];
      
      if(key == NSLeftArrowFunctionKey)
      {
         
         return VK_LEFT; //::user::key_left;
         
      }
      else if(key == NSRightArrowFunctionKey)
      {
         
         return VK_RIGHT; //::user::key_right;
         
      }
      else if(key == NSUpArrowFunctionKey)
      {
         
         return VK_UP; // ::user::key_up;
         
      }
      else if(key == NSDownArrowFunctionKey)
      {
         
         return VK_DOWN; // ::user::key_down;
         
      }
      else if(key >= L'0' && key <= L'9')
      {
         
         //return 3000 + key - L'0';
         
         return 0;
         
      }
      
   }
   
   return 0;

}


unsigned int event_key_code(NSEvent * event)
{

   unsigned int uiModifierFlags = [event modifierFlags];

   if(uiModifierFlags & NSNumericPadKeyMask)
   {

      return event_num_pad_key_code(event);
   
   }
   
   unsigned int uiKeyCode = [event keyCode];
 
   return uiKeyCode;
   
}





