#include "framework.h"


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

bool simple_bitmap::create(int cx, int cy, simple_graphics & g, COLORREF ** ppdata)
{

   if(m_pbitmap != NULL)
   {

      destroy();

   }

   D2D1_SIZE_U size;

   size.width = cx;
   size.height = cy;

   D2D1_BITMAP_PROPERTIES props;

   props.pixelFormat.alphaMode = D2D1_ALPHA_MODE_STRAIGHT;
   props.pixelFormat.format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
   props.dpiX = 72.0;
   props.dpiY = 72.0;

   g.m_pdc->CreateBitmap(size, props, &m_pbitmap);

   m_pbitmap->Map(D2D1_MAP_OPTIONS_READ | D2D1_MAP_OPTIONS_WRITE, &m_map);

   if(ppdata != NULL)
      *ppdata = (COLORREF) m_map.bits;


   return true;

}


bool simple_bitmap::create_from_data(int cx, int cy, COLORREF * pdata, simple_graphics & g)
{

   UNREFERENCED_PARAMETER(g);

   if(m_pcr != NULL)
   {
      destroy();
   }


   m_pcr = pdata;

   //m_hbitmap = ::CreateBitmap(cx, cy, 1, 32, pdata);

   if(m_pcr == NULL)
      return false;

   return true;

}



bool simple_bitmap::destroy()
{
   
   if(m_pcr == NULL)
      return true;

   bool bOk = true;

   try
   {

      ca2_free(m_pcr);

   }
   catch(...)
   {
      bOk = false;
   }

   m_pcr = NULL;

   if(!bOk)
      return false;

   return true;

}
