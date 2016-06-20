//
//  user_notify_icon_mm_bridge.h
//  core
//
//  Created by Carlos Gustavo Cecyn Lundgren on 3/17/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#ifndef user_notify_icon_mm_bridge_h
#define user_notify_icon_mm_bridge_h


#ifdef __OBJC__
#include "user_notify_icon_mm.h"
#endif

class user_notify_icon_mm_bridge
{
public:
   
   
   void * m_pnotifyicon;
   
   
   
   
   virtual void notify_icon_init(const char * strIconFile);
   virtual void notify_icon_play(const char * action) = 0;
   virtual bool notify_icon_frame_is_opened() = 0;
   
};





#endif /* user_notify_icon_mm_bridge_h */
