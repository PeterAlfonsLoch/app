#import "macos/ca_os_graphics_mm.h"
#include <math.h>


#define MATH_PI 3.14159265359


os_simple_path::os_simple_path()
{

   m_path = NULL;
   
   m_bBegin = true;
   
   create();

}

os_simple_path::~os_simple_path()
{

   destroy();

}


bool os_simple_path::add_arc(const RECT & rect, int iStart, int iAngle)
{
   
   CGFloat d1 = rect.right - rect.left;
   
   if(d1 <= 0)
      return true;
   
   CGFloat d2 = rect.bottom - rect.top;
   
   if(d2 <= 0)
      return true;
   
   CGAffineTransform t = CGAffineTransformMakeScale(1.0, d2 / d1);
   CGFloat x = (rect.right + rect.left) / 2.0;
   CGFloat y = (rect.bottom + rect.top) / 2.0;
   CGFloat x1 = x + d1 * sin(iStart * MATH_PI / 180.0f);
   CGFloat y1 = y + d1 * cos(iStart * MATH_PI / 180.0f);
   CGFloat x2 = x + d1 * sin((iStart + iAngle) * MATH_PI / 180.0f);
   CGFloat y2 = y + d1 * cos((iStart + iAngle) * MATH_PI / 180.0f);
   
   if(CGPathIsEmpty(m_path))
   {
      
      add_move(x1, y1);
      
   }
   
   CGPathAddArcToPoint(m_path, &t, x1, y1, x2, y2, d1);
   
   return true;

}


bool os_simple_path::add_line(int x, int y)
{
   
   if(CGPathIsEmpty(m_path))
   {
      
      add_move(x, y);
      
   }
   else
   {
      
      CGPathAddLineToPoint(m_path, NULL, x, y);
      
   }
   
   return true;
   
}

bool os_simple_path::add_line(int x1, int y1, int x2, int y2)
{
   
   if(CGPathIsEmpty(m_path))
   {
      
      add_move(x1, y1);
      
   }
   else
   {
      
      CGPathAddLineToPoint(m_path, NULL, x1, y1);
      
   }
   
   CGPathAddLineToPoint(m_path, NULL, x2, y2);
   
   return true;

}



bool os_simple_path::add_rect(const RECT & rect)
{
   
   
   CGRect cgrect;
   
   cgrect.origin.x = rect.left;
   cgrect.origin.y = rect.top;
   cgrect.size.width = width(rect);
   cgrect.size.height = height(rect);
   
   
   CGPathAddRect(m_path, NULL, cgrect);
   
   return true;

}




   
   bool os_simple_path::begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode)
   {
      
      m_bBegin = true;
      
      return true;
      
   }
   
   
   bool os_simple_path::end_figure(bool bClose)
   {
      
      if(bClose)
      {
         
         CGPathCloseSubpath(m_path);
         
      }
      
      m_bBegin = true;
      
      return true;
      
   }
   
   
   
   
   bool os_simple_path::add_move(int x, int y)
   {
      
      CGPathMoveToPoint(m_path, NULL, x, y);
      
      m_bBegin = false;
      
      return true;
      
   }
   
   
   
   void * os_simple_path::detach()
   {
      
      void * ppath = get_os_data();
      
      m_path = NULL;
      
      return ppath;
      
   }
   
   
   void * os_simple_path::get_os_data() const
   {
      
      return m_path;
      
      
   }
   
   bool os_simple_path::destroy()
   {
      
      if(m_path != NULL)
      {
         
         CGPathRelease(m_path);
         
         m_path = NULL;
         
      }
      
      return true;
      
   }
   
   
   bool os_simple_path::create()
   {
      
      if(m_path != NULL)
      {
         
         destroy();
         
      }
      
      m_path = CGPathCreateMutable();
      
      return true;
      
   }
   

