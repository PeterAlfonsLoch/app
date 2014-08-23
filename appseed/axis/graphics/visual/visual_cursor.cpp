#include "framework.h"




namespace visual
{

   cursor::cursor(sp(::aura::application) papp) :
      element(papp),
      m_dib(allocer())
      //,m_dibWork(allocer())
   {

#ifdef WINDOWSEX

      m_hcursor = NULL;

#endif

   }


   bool cursor::to(::draw2d::graphics * pgraphics, point pt)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      return pgraphics->BitBlt(pt - m_szHotspotOffset, m_dib->m_size, m_dib->get_graphics());

   }


#ifdef WINDOWSEX

   HCURSOR cursor::get_HCURSOR()
   {

      if(m_hcursor == NULL)
      {

         m_hcursor = ::CreateAlphaCursor(m_dib,m_szHotspotOffset.cx,m_szHotspotOffset.cy);

      }

      return m_hcursor;

   }

#endif

} // namespace visual







#ifdef WINDOWSEX

// Derived from Microsoft KB318876!!
// on 2014-06-29!! During World Cup Games 2014!! Oitavas de Final, third game between Nederland and Mexico!!
// Thank you God!!
// Thank you Microsoft!!
// Thank you Pappi!! Pelo passeio no Mercado Municipal de Curitiba com a Mummi e pelo almoço com o-bento de sushi e onigiri delicioso!!
// Obrigado Mummi por tudo!! E por hoje também e por propiciar isso tudo!! Por falar tão profundamente do Chico Xavier mesmo com muitas dúvidas minhas!!
// Obrigado Carlos!! Você poderia colaborar, não é!!
// Meu Deus me ajude!!

HBITMAP CreateAlphaBitmapV5(::draw2d::dib * pdib)
{
   HDC hMemDC;
   DWORD dwWidth,dwHeight;
   BITMAPV5HEADER bi;
   HBITMAP hBitmap,hOldBitmap;
   void *lpBits;
   HCURSOR hAlphaCursor = NULL;

   dwWidth  = pdib->m_size.cx;  // width of the Bitmap V5 Dib bitmap
   dwHeight = pdib->m_size.cy;  // height of the Bitmap V5 Dib bitmap

   ZeroMemory(&bi,sizeof(BITMAPV5HEADER));
   bi.bV5Size           = sizeof(BITMAPV5HEADER);
   bi.bV5Width           = dwWidth;
   bi.bV5Height          = - (LONG) dwHeight;
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

   // Set the alpha values for each pixel in the cursor so that
   // the complete cursor is semi-transparent.
   memcpy(lpBits,pdib->m_pcolorref,(size_t) (sizeof(COLORREF)* pdib->area()));

   return hBitmap;
}

HCURSOR CreateAlphaIcon(::draw2d::dib * pdib,bool bIcon,int xHotSpot,int yHotSpot)
{

   HBITMAP hBitmap = ::CreateAlphaBitmapV5(pdib);

   // Create an empty mask bitmap.
   HBITMAP hMonoBitmap = CreateBitmap(pdib->m_size.cx,pdib->m_size.cy,1,1,NULL);

   if(bIcon)
   {
      xHotSpot = 0;
      yHotSpot = 0;
   }

   ICONINFO ii;
   ii.fIcon = bIcon ? TRUE : FALSE;  // Change fIcon to TRUE to create an alpha icon
   ii.xHotspot = xHotSpot;
   ii.yHotspot = yHotSpot;
   ii.hbmMask = hMonoBitmap;
   ii.hbmColor = hBitmap;

   // Create the alpha cursor with the alpha DIB section.
   HICON hicon = CreateIconIndirect(&ii);

   DeleteObject(hBitmap);
   DeleteObject(hMonoBitmap);

   return hicon;
}


HCURSOR CreateAlphaCursor(::draw2d::dib * pdib,int xHotSpot,int yHotSpot)
{

   return (HCURSOR) ::CreateAlphaIcon(pdib,false,xHotSpot,yHotSpot);

}

#endif