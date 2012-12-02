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

   D2D1_BITMAP_PROPERTIES1 props;

   props.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
   props.pixelFormat.format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
   props.dpiX = ::Windows::Graphics::Display::DisplayProperties::LogicalDpi;
   props.dpiY = ::Windows::Graphics::Display::DisplayProperties::LogicalDpi;
   props.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CPU_READ;

   if(ppdata != NULL)
   {
      g.m_pdc->CreateBitmap(size, *ppdata, cx * sizeof(COLORREF), props, &m_pbitmap);
   }
   else
   {
      g.m_pdc->CreateBitmap(size, NULL, cx * sizeof(COLORREF), props, &m_pbitmap);
   }

   m_pbitmap->Map(D2D1_MAP_OPTIONS_READ | D2D1_MAP_OPTIONS_WRITE, &m_map);

   if(ppdata != NULL)
      *ppdata = (COLORREF *) m_map.bits;


   return true;

}


bool simple_bitmap::create_from_data(int cx, int cy, COLORREF * pdata, simple_graphics & g)
{

   if(m_pbitmap != NULL)
   {

      destroy();

   }

   D2D1_SIZE_U size;

   size.width = cx;
   size.height = cy;

   D2D1_BITMAP_PROPERTIES1 props;

   props.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
   props.pixelFormat.format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
   props.dpiX = ::Windows::Graphics::Display::DisplayProperties::LogicalDpi;
   props.dpiY = ::Windows::Graphics::Display::DisplayProperties::LogicalDpi;
   props.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CPU_READ;

   g.m_pdc->CreateBitmap(size, pdata, cx * sizeof(COLORREF), props, &m_pbitmap);

   m_pbitmap->Map(D2D1_MAP_OPTIONS_READ | D2D1_MAP_OPTIONS_WRITE, &m_map);

   return true;


}



bool simple_bitmap::destroy()
{
   
   m_pbitmap->Unmap();

   m_pbitmap->Release();

   return true;

}
