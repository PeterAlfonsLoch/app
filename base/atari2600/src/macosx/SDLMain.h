/** SDLMain.m - main entry point for our Cocoa-ized SDL app
    Initial Version: Darrell Walisser <dwaliss1@purdue.edu>
    Non-NIB-Code & other changes: Max Horn <max@quendi.de>
  */
// $Id: SDLMain.h 3217 2015-09-25 22:45:44Z stephena $

#import <Cocoa/Cocoa.h>

@interface SDLMain : NSObject
{
}
+ (SDLMain*) sharedInstance;

@end
