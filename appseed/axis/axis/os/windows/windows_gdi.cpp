#include "framework.h"


HBITMAP CreateHBITMAP(COLORREF * pdata,int stride,int cx,int cy)
{

   HBITMAP hbmp = NULL;

   BITMAPINFO bminfo;

   ZeroMemory(&bminfo,sizeof(bminfo));
   bminfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   bminfo.bmiHeader.biWidth = width;
   bminfo.bmiHeader.biHeight = -((LONG)height);
   bminfo.bmiHeader.biPlanes = 1;
   bminfo.bmiHeader.biBitCount = 32;
   bminfo.bmiHeader.biCompression = BI_RGB;

   COLORREF * pvImageBits = NULL;
   HDC hdcScreen = GetDC(NULL);
   hbmp = CreateDIBSection(hdcScreen,&bminfo,DIB_RGB_COLORS,&pvImageBits,NULL,0);
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




