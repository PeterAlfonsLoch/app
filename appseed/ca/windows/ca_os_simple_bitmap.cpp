#include "framework.h"
#undef new
#include <GdiPlus.h>


simple_bitmap::simple_bitmap()
{
   
   m_pbitmap = NULL;

}

simple_bitmap::~simple_bitmap()
{
   
   if(m_pbitmap != NULL)
   {

      destroy();

   }

}

bool simple_bitmap::create(int32_t cx, int32_t cy, simple_graphics & g, COLORREF ** ppdata)
{

   if(m_pbitmap != NULL)
   {
      
      destroy();

   }

   m_size.cx = abs(cx);
   m_size.cy = abs(cy);

   m_memory.allocate(4 * m_size.cx * m_size.cy);

   if(m_memory.get_data() == NULL)
   {
      m_size.cx = 0;
      m_size.cy = 0;
      return false;
   }

   m_pbitmap = new Gdiplus::Bitmap(m_size.cx, m_size.cy, m_size.cx * 4, PixelFormat32bppARGB, (BYTE *) m_memory.get_data());

   if(m_pbitmap == NULL)
   {
      m_memory.allocate(0);
      m_size.cx = 0;
      m_size.cy = 0;
      return FALSE;
   }

   if(ppdata != NULL)
   {
      *ppdata = (COLORREF *) m_memory.get_data(); 
   }

   return true;

}


bool simple_bitmap::create_from_data(int32_t cx, int32_t cy, COLORREF * pdata, simple_graphics & g)
{

   if(m_pbitmap != NULL)
   {
      
      destroy();

   }

   m_size.cx = abs(cx);
   m_size.cy = abs(cy);

   m_memory.attach(pdata, m_size.cx * m_size.cy * 4);

   if(m_memory.get_data() == NULL)
   {
      m_size.cx = 0;
      m_size.cy = 0;
      return false;
   }

   m_pbitmap = new Gdiplus::Bitmap(m_size.cx, m_size.cy, m_size.cx * 4, PixelFormat32bppARGB, (BYTE *) m_memory.get_data());

   if(m_pbitmap == NULL)
   {
      m_memory.allocate(0);
      m_size.cx = 0;
      m_size.cy = 0;
      return FALSE;
   }

   return true;

}



bool simple_bitmap::destroy()
{
   
   if(m_pbitmap == NULL)
      return true;

   bool bOk = true;

   try
   {
      
      delete m_pbitmap;

   }
   catch(...)
   {

      bOk = false;

   }

   m_pbitmap = NULL;

   if(!bOk)
      return false;

   return true;

}


