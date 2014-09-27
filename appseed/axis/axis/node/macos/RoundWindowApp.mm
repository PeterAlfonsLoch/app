//
//  RoundWindowApp.m
//  axis
//
//  Created by Carlos Gustavo Cecyn Lundgren on 27/09/14.
//
//

#import "macos_mm.h"



@implementation RoundWindowApp


- (void)sendEvent:(NSEvent *)theEvent
{

   /*
   
   char szEvent[128];
   
   ZERO(szEvent);
   
   if([theEvent type] == NSLeftMouseDown)
   {
   
      strcpy(szEvent, "NSLeftMouseDown");
      
   }
   else if([theEvent type] == NSLeftMouseUp)
   {
     
      strcpy(szEvent, "NSLeftMouseUp");
      
   }
   
   if(strlen(szEvent) > 0)
   {
   
      char szEventCopy[128];
   
      strcpy(szEventCopy, szEvent);
      
      printf("\n%s", szEventCopy);
      
   }
   
   */
   
   [super sendEvent:theEvent];
   
}



@end