#include "framework.h"


// Derived from Microsoft KB318876!!
// on 2014-06-29!! During World Cup Games 2014!! Oitavas de Final, third game between Nederland and Mexico!!
// Thank you God!!
// Thank you Microsoft!!
// Thank you Pappi!! Pelo passeio no Mercado Municipal de Curitiba com a Mummi e pelo almoço com o-bento de sushi e onigiri delicioso!!
// Obrigado Mummi por tudo!! E por hoje também e por propiciar isso tudo!! Por falar tão profundamente do Chico Xavier mesmo com muitas dúvidas minhas!!
// Obrigado Carlos!! Você poderia colaborar, não é!!
// Meu Deus me ajude!!

HCURSOR CreateAlphaBV5(::draw2d::dib * pdib)
{
   HDC hMemDC;
   DWORD dwWidth,dwHeight;
   BITMAPV5HEADER bi;
   HBITMAP hBitmap,hOldBitmap;
   void *lpBits;
   DWORD x,y;
   HCURSOR hAlphaCursor = NULL;

   dwWidth  = 32;  // width of cursor
   dwHeight = 32;  // height of cursor

   ZeroMemory(&bi,sizeof(BITMAPV5HEADER));
   bi.bV5Size           = sizeof(BITMAPV5HEADER);
   bi.bV5Width           = dwWidth;
   bi.bV5Height          = dwHeight;
   bi.bV5Planes = 1;
   bi.bV5BitCount = 32;
   bi.bV5Compression = BI_BITFIELDS;
   // The following mask specification specifies a supported 32 BPP
   // alpha format for Windows XP.
   bi.bV5RedMask   =  0x00FF0000;
   bi.bV5GreenMask =  0x0000FF00;
   bi.bV5BlueMask  =  0x000000FF;
   bi.bV5AlphaMask =  0xFF000000;

   HDC hdc;
   hdc = GetDC(NULL);

   // Create the DIB section with an alpha channel.
   hBitmap = CreateDIBSection(hdc,(BITMAPINFO *)&bi,DIB_RGB_COLORS,
      (void **)&lpBits,NULL,(DWORD)0);

   hMemDC = CreateCompatibleDC(hdc);
   ReleaseDC(NULL,hdc);

   // Draw something on the DIB section.
   hOldBitmap = (HBITMAP)SelectObject(hMemDC,hBitmap);
   PatBlt(hMemDC,0,0,dwWidth,dwHeight,WHITENESS);
   SetTextColor(hMemDC,RGB(0,0,0));
   SetBkMode(hMemDC,TRANSPARENT);
   TextOut(hMemDC,0,9,"rgba",4);
   SelectObject(hMemDC,hOldBitmap);
   DeleteDC(hMemDC);

   // Create an empty mask bitmap.
   HBITMAP hMonoBitmap = CreateBitmap(dwWidth,dwHeight,1,1,NULL);

   // Set the alpha values for each pixel in the cursor so that
   // the complete cursor is semi-transparent.
   DWORD *lpdwPixel;
   memcpy(lpBits, pdib->m_pcolorref, sizeof(COLORREF) * pdib->area());

   return hBitmap;
}


HCURSOR CreateAlphaCursor(::draw2d::dib * pdib, int xHotSpot, int yHotSpot)
{
   HDC hMemDC;
   DWORD dwWidth,dwHeight;
   BITMAPV5HEADER bi;
   HBITMAP hBitmap,hOldBitmap;
   void *lpBits;
   DWORD x,y;
   HCURSOR hAlphaCursor = NULL;

   dwWidth  = 32;  // width of cursor
   dwHeight = 32;  // height of cursor

   ZeroMemory(&bi,sizeof(BITMAPV5HEADER));
   bi.bV5Size           = sizeof(BITMAPV5HEADER);
   bi.bV5Width           = dwWidth;
   bi.bV5Height          = dwHeight;
   bi.bV5Planes = 1;
   bi.bV5BitCount = 32;
   bi.bV5Compression = BI_BITFIELDS;
   // The following mask specification specifies a supported 32 BPP
   // alpha format for Windows XP.
   bi.bV5RedMask   =  0x00FF0000;
   bi.bV5GreenMask =  0x0000FF00;
   bi.bV5BlueMask  =  0x000000FF;
   bi.bV5AlphaMask =  0xFF000000;

   HDC hdc;
   hdc = GetDC(NULL);

   // Create the DIB section with an alpha channel.
   hBitmap = CreateDIBSection(hdc,(BITMAPINFO *)&bi,DIB_RGB_COLORS,
      (void **)&lpBits,NULL,(DWORD)0);

   hMemDC = CreateCompatibleDC(hdc);
   ReleaseDC(NULL,hdc);

   // Draw something on the DIB section.
   hOldBitmap = (HBITMAP)SelectObject(hMemDC,hBitmap);
   PatBlt(hMemDC,0,0,dwWidth,dwHeight,WHITENESS);
   SetTextColor(hMemDC,RGB(0,0,0));
   SetBkMode(hMemDC,TRANSPARENT);
   TextOut(hMemDC,0,9,"rgba",4);
   SelectObject(hMemDC,hOldBitmap);
   DeleteDC(hMemDC);

   // Create an empty mask bitmap.
   HBITMAP hMonoBitmap = CreateBitmap(dwWidth,dwHeight,1,1,NULL);

   // Set the alpha values for each pixel in the cursor so that
   // the complete cursor is semi-transparent.
   DWORD *lpdwPixel;
   lpdwPixel = (DWORD *)lpBits;
   for(x=0;x<dwWidth;x++)
   for(y=0;y<dwHeight;y++)
   {
      // Clear the alpha bits
      *lpdwPixel &= 0x00FFFFFF;
      // Set the alpha bits to 0x9F (semi-transparent)
      *lpdwPixel |= 0x9F000000;
      lpdwPixel++;
   }

   ICONINFO ii;
   ii.fIcon = FALSE;  // Change fIcon to TRUE to create an alpha icon
   ii.xHotspot = xHotSpot;
   ii.yHotspot = yHotSpot;
   ii.hbmMask = hMonoBitmap;
   ii.hbmColor = hBitmap;

   // Create the alpha cursor with the alpha DIB section.
   hAlphaCursor = CreateIconIndirect(&ii);

   DeleteObject(hBitmap);
   DeleteObject(hMonoBitmap);

   return hAlphaCursor;
}


namespace visual
{

   cursor::cursor(sp(::base::application) papp) :
      element(papp),
      m_dib(allocer())
      //,m_dibWork(allocer())
   {
   }


   bool cursor::to(::draw2d::graphics * pgraphics, point pt)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      return pgraphics->BitBlt(pt - m_szHotspotOffset, m_dib->m_size, m_dib->get_graphics());

   }


} // namespace visual