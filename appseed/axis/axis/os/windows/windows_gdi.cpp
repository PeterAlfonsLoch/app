#include "framework.h"


// CreateHITMAP (adapted)
// Adapted from 
// Marius Bancila's Blog
// C++,.NET,Windows programming & others
// (CAmiloST's opinion [Sato's opinion] why 's and .NET?, isn't ++ enough or needed more .Net or exquisite type of coffe?!?!?! or snake or something else?!?!
// Marius Bancila
// Software Developer
// Microsoft MVP VisualC++
// Cofounder of Codexpert
// www.mariusbancila.ro
// http://mariusbancila.ro/blog/tag/wic/
// Display images as you type in C++
// Marius Bancila C++ 2011 - 08 - 04 1 comment

HBITMAP CreateHBITMAP(COLORREF * pdata,int stride,int cx,int cy)
{

   HBITMAP hbmp = NULL;

   BITMAPINFO bminfo;

   ZeroMemory(&bminfo,sizeof(bminfo));
   bminfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   bminfo.bmiHeader.biWidth = cx;
   bminfo.bmiHeader.biHeight = -((LONG)cy);
   bminfo.bmiHeader.biPlanes = 1;
   bminfo.bmiHeader.biBitCount = 32;
   bminfo.bmiHeader.biCompression = BI_RGB;

   COLORREF * pvImageBits = NULL;

   HDC hdcScreen = GetDC(NULL);

   hbmp = CreateDIBSection(hdcScreen,&bminfo,DIB_RGB_COLORS, (void **) &pvImageBits,NULL,0);

   ReleaseDC(NULL,hdcScreen);

   if(hbmp == NULL)
      goto Return;

   int bmStride = cx * sizeof(COLORREF);

   if(stride == bmStride)
   {

      memcpy(pvImageBits,pdata,cy * stride);

   }
   else
   {

      byte * psrc = (byte *)pdata;

      byte * pdst = (byte *)pvImageBits;

      for(index i = 0; i < cy; i++)
      {

         memcpy(pvImageBits,pdata,bmStride);

      }

   }

Return:

   return hbmp;

}





// default implementation for these methods (present only in Windows for Desktop Applications)


namespace draw2d
{

   HBITMAP bitmap::GetHBITMAP()
   {

      if(m_hbitmapGet != NULL)
         return m_hbitmapGet;

      m_hbitmapGet = _GetHBITMAP();

      return m_hbitmapGet;

   }

   void bitmap::ReleaseHBITMAP(HBITMAP hbitmap)
   {

      if(hbitmap == NULL)
         return;

      if(m_hbitmapGet == NULL)
         return;

      _ReleaseHBITMAP(hbitmap);

      m_hbitmapGet = NULL;

   }

   HBITMAP bitmap::_GetHBITMAP()
   {

      if(get_os_data() == NULL)
         return NULL;

      ::draw2d::dib_sp dib(allocer());

      dib->create(GetBitmapDimension());

      if(dib->area() <= 0)
         return NULL;

      ::draw2d::graphics_sp g(allocer());

      g->CreateCompatibleDC(NULL);

      g->SelectObject(this);

      dib->get_graphics()->BitBlt(null_point(),dib->m_size,g,null_point(),SRCCOPY);

      return CreateHBITMAP(dib->m_pcolorref,dib->m_iScan,dib->m_size.cx,dib->m_size.cy);

   }


   void bitmap::_ReleaseHBITMAP(HBITMAP hbitmap)
   {

      ::DeleteObject(hbitmap);

   }

} // namespace draw2d