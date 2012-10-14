#include "framework.h"
#undef new   
#include <gdiplus.h>


simple_path::simple_path()
{

   m_ppath = new Gdiplus::GraphicsPath();

}

simple_path::~simple_path()
{

   if(m_ppath != NULL)
   {
         
      delete m_ppath;
         
      m_ppath = NULL;

   }


}
