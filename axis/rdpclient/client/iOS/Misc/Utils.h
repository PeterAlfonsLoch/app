/*
 Utility functions

 Copyright 2013 Thincast Technologies GmbH, Authors: Martin Fleisz, Dorian Johnson

 This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import "TSXTypes.h"

// helper macro to encode a table path into a tag value (used to identify controls in their delegate handlers)
#define GET_TAG(section, row) ((((int)section) << 16) | ((int)(row)))
#define GET_TAG_FROM_PATH(path) ((((int)path.section) << 16) | ((int)(path.row)))


WINBOOL ScanHostNameAndPort(NSString* address, NSString** host, unsigned short* port);

#pragma mark -
#pragma mark Screen Resolutions

NSString* ScreenResolutionDescription(TSXScreenOptions type, int width, int height);
WINBOOL ScanScreenResolution(NSString* description, int* width, int* height, TSXScreenOptions* type);

NSDictionary* SelectionForColorSetting(void);
NSArray* ResolutionModes(void);

#pragma mark Security Protocol

NSString* ProtocolSecurityDescription(TSXProtocolSecurityOptions type);
WINBOOL ScanProtocolSecurity(NSString* description, TSXProtocolSecurityOptions* type);
NSDictionary* SelectionForSecuritySetting(void);

#pragma mark Bookmarks
@class BookmarkBase;
NSMutableArray* FilterBookmarks(NSArray* bookmarks, NSArray* filter_words);
NSMutableArray* FilterHistory(NSArray* history, NSString* filterStr);

#pragma mark iPad/iPhone detection

WINBOOL IsPad(void);
WINBOOL IsPhone(void);

#pragma mark Version Info
NSString* TSXAppFullVersion(void);

#pragma mark Touch/Mouse handling

// set mouse buttons swapped flag
void SetSwapMouseButtonsFlag(WINBOOL swapped);

// set invert scrolling flag
void SetInvertScrollingFlag(WINBOOL invert);

// return event value for left mouse button
int GetLeftMouseButtonClickEvent(WINBOOL down);

// return event value for right mouse button
int GetRightMouseButtonClickEvent(WINBOOL down);

// return event value for mouse move event
int GetMouseMoveEvent(void);

// return mouse wheel event
int GetMouseWheelEvent(WINBOOL down);

// scrolling gesture detection delta
CGFloat GetScrollGestureDelta(void);

#pragma mark Connectivity tools
// activates the iphone's WWAN interface in case it is offline
void WakeUpWWAN(void);

#pragma mark System Info functions
NSString* TSXGetPlatform(void);
WINBOOL TSXDeviceHasJailBreak(void);
NSString* TSXGetPrimaryMACAddress(NSString *sep);

