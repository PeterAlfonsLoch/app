//
//  user_notify_icon_mm_bridge.m
//  core
//
//  Created by Carlos Gustavo Cecyn Lundgren on 3/17/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "user_notify_icon_mm_bridge.h"


void user_notify_icon_mm_bridge::notify_icon_init(const char * strIconFile)
{
   NSString * str = [[NSString alloc] initWithCString:strIconFile encoding:NSUTF8StringEncoding];
   m_pnotifyicon = [[user_notify_icon alloc] init: str bridge:this];
   
}

bool nsapp_activation_policy_is_regular()
{
   
   if(NSApp.activationPolicy == NSApplicationActivationPolicyRegular)
   {
      return true;
   }
   
   return false;
   
}

bool nsapp_activation_policy_is_accessory()
{
   
   if(NSApp.activationPolicy == NSApplicationActivationPolicyAccessory)
   {
      
      return true;
      
   }
   
   return false;
   
}


void nsapp_activation_policy_regular()
{
   
   [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
   
}

void nsapp_activation_policy_accessory()
{
   
   [NSApp setActivationPolicy:NSApplicationActivationPolicyAccessory];
   
}


void nsapp_activation_policy_prohibited()
{

   [NSApp setActivationPolicy:NSApplicationActivationPolicyProhibited];
   
}


void nsapp_activate_ignoring_other_apps(int i)
{
   
   if(i)
   {

      [NSApp activateIgnoringOtherApps:YES];
      
   }
   else
   {

      [NSApp activateIgnoringOtherApps:NO];
      
   }


}