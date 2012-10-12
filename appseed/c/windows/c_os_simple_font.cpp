#include "framework.h"


simple_font::simple_font()
{
   
   m_hfont = NULL;

}

simple_font::~simple_font()
{
   
   if(m_hfont != NULL)
   {

      destroy();

   }

}

bool simple_font::create_indirect(LPLOGFONT  lplf)
{

   m_hfont = ::CreateFontIndirect(lplf);

   if(m_hfont == NULL)
      return false;


   return true;

}

bool simple_font::destroy()
{
   
   if(m_hfont == NULL)
      return true;


   bool bOk = ::DeleteObject(m_hfont) != FALSE;

   m_hfont = NULL;

   if(!bOk)
      return false;

   return true;

}


bool simple_font::create_point(int nPointSize, const char * lpszFaceName, simple_graphics & g)
{

   return create_point_bold(nPointSize, lpszFaceName, FALSE, g);

}

bool simple_font::create_point_bold(int nPointSize, const char * lpszFaceName, int iBold, simple_graphics & g)
{

   LOGFONT logFont;

   memset_dup(&logFont, 0, sizeof(LOGFONT));

   logFont.lfCharSet = DEFAULT_CHARSET;

   if(g.m_hdc == NULL)
   {

      g.create();

   }

   // convert nPointSize to logical units based on pgraphics
   POINT pt;
   // 72 points/inch, 10 decipoints/point
   pt.y = ::MulDiv(::GetDeviceCaps(g.m_hdc, LOGPIXELSY), logFont.lfHeight, 720);
   pt.x = 0;
   ::DPtoLP(g.m_hdc, &pt, 1);
   POINT ptOrg = { 0, 0 };
   ::DPtoLP(g.m_hdc, &ptOrg, 1);
   logFont.lfHeight = -abs(pt.y - ptOrg.y);

   logFont.lfWeight = iBold ? FW_BOLD : FW_NORMAL;

   strncpy_dup(logFont.lfFaceName, lpszFaceName, sizeof(logFont.lfFaceName));

   return create_indirect(&logFont);

}
