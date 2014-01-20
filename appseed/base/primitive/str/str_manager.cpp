#include "framework.h"


#define ROUND(x,y) (((x)+(y-1))&~(y-1))
#define ROUND4(x) ROUND(x, 4)

string_manager::string_manager()
{
/*   m_palloca = new fixed_alloc_array();
   //bool bEnable = __enable_memory_tracking(FALSE);
   try
   {
      m_palloca->add(new fixed_alloc(ROUND4(32), 1024));
   }
   catch(...)
   {
   }
   try
   {
      m_palloca->add(new fixed_alloc(ROUND4(64), 1024));
   }
   catch(...)
   {
   }
   try
   {
      m_palloca->add(new fixed_alloc(ROUND4(128), 1024));
   }
   catch(...)
   {
   }
   try
   {
      m_palloca->add(new fixed_alloc(ROUND4(256), 1024));
   }
   catch(...)
   {
   }
   try
   {
      m_palloca->add(new fixed_alloc(ROUND4(512), 1024));
   }
   catch(...)
   {
   }
   try
   {
      m_palloca->add(new fixed_alloc(ROUND4(768), 1024));
   }
   catch(...)
   {
   }
   try
   {
      m_palloca->add(new fixed_alloc(ROUND4(1024), 1024));
   }
   catch(...)
   {
   }*/
   //__enable_memory_tracking(bEnable);

   
   
   m_nil.SetManager(this);
}







