#import "macos/c_os_graphics_mm.h"
#include <math.h>


os_simple_path::os_simple_path()
{

   m_bFill  = false;

   m_nspath  = [NSBezierPath bezierPath];

}

os_simple_path::~os_simple_path()
{

   if(m_nspath != NULL)
   {
         
      [m_nspath release];


   }


}


bool os_simple_path::add_arc(const RECT & rect, int iStart, int iAngle)
{
   
   NSAffineTransform * transform = [NSAffineTransform transform];
   
   double xCenter = (rect.left + rect.right) / 2.0;
   
   double yCenter = (rect.top + rect.bottom) / 2.0;
   
   double xRadius = abs(rect.left - rect.right) / 2.0;
   
   double yRadius = abs(rect.top - rect.bottom) / 2.0;
   
   [transform translateXBy: xCenter yBy: yCenter];

   [transform scaleXBy: xRadius yBy: yRadius];
   
   [m_nspath transformUsingAffineTransform: transform];
   
   [m_nspath appendBezierPathWithArcWithCenter: NSMakePoint(0.0, 0.0) radius: 1.0 startAngle: (CGFloat) iStart endAngle: (CGFloat) (iStart + iAngle)];
   
   [transform invert];

   [m_nspath transformUsingAffineTransform: transform];
   
   [transform release];

   return true;

}

bool os_simple_path::add_line(int x1, int y1, int x2, int y2)
{
   
   if([m_nspath isEmpty])
   {
   
      [m_nspath moveToPoint: NSMakePoint(x1, y1)];
   
   }
   else
   {

      [m_nspath lineToPoint: NSMakePoint(x1, y1)];
   
   }

   [m_nspath lineToPoint: NSMakePoint(x2, y2)];

   return true;

}

bool os_simple_path::begin_figure(bool bFill, ::ca::e_fill_mode efillmode)
{
   
   m_bFill = bFill;
   
   if(m_efillmode == ::ca::fill_mode_alternate)
   {
      [m_nspath setWindingRule:NSEvenOddWindingRule];
   }
   else
   {
        [m_nspath setWindingRule:NSNonZeroWindingRule];
   }
   
   return true;
   
}


bool os_simple_path::end_figure(bool bClose)
{

   if(bClose)
   {

      [m_nspath closePath];

   }

   return true;

}


bool os_simple_path::add_rect(const RECT & rect)
{
   
   
   [m_nspath appendBezierPathWithRect: NSMakeRect(rect.left, rect.top, width(rect), height(rect))];
   
   return true;

}