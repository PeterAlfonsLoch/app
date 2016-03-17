//
//  user_notify_icon_mm.h
//  core
//
//  Created by Carlos Gustavo Cecyn Lundgren on 3/17/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#ifndef user_notify_icon_mm_h
#define user_notify_icon_mm_h

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <ApplicationServices/ApplicationServices.h>

class user_notify_icon_mm_bridge;


@interface user_notify_icon :  NSObject {
@public
   
   
   user_notify_icon_mm_bridge * m_pbridge;
   
   // http://stackoverflow.com/questions/3409985/how-to-create-a-menubar-application-for-mac
   // Flycut/AppController.h
   NSMenu *jcMenu;
   NSStatusItem *statusItem;
   NSMenuItem *closeItem;
   NSMenuItem *quitItem;
}
- (id)init:(NSString *)strIconFile bridge: (user_notify_icon_mm_bridge *) pbridge
;
- (void)play:(NSString *)strIconFile;

@end

#endif /* user_notify_icon_mm_h */
