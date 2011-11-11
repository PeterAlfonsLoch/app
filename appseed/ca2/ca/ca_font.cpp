#include "StdAfx.h"

namespace ca
{

#ifdef _DEBUG
   void font::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      throw interface_only_exception();   
   }
#endif

   /////////////////////////////////////////////////////////////////////////////
   // out-of-line ::ca::brush, font, etc. helpers

   // nPointSize is actually scaled 10x
   BOOL font::CreatePointFont(int nPointSize, const char * lpszFaceName, ::ca::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(nPointSize);
      UNREFERENCED_PARAMETER(lpszFaceName);
      UNREFERENCED_PARAMETER(pgraphics);
      throw interface_only_exception();   
   }

   // pLogFont->nHeight is interpreted as PointSize * 10
   BOOL font::CreatePointFontIndirect(const LOGFONT* lpLogFont, ::ca::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(lpLogFont);
      UNREFERENCED_PARAMETER(pgraphics);
      throw interface_only_exception();   
   }

   BOOL font::CreateFontIndirect(const LOGFONT* lpLogFont)
   {
      UNREFERENCED_PARAMETER(lpLogFont);
      throw interface_only_exception();   
   }

   BOOL font::CreateFont(int nHeight, int nWidth, int nEscapement,
      int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline,
      BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision,
      BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily,
      const char * lpszFacename)
   {
      UNREFERENCED_PARAMETER(nHeight);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nEscapement);
      UNREFERENCED_PARAMETER(nOrientation);
      UNREFERENCED_PARAMETER(nWeight);
      UNREFERENCED_PARAMETER(bItalic);
      UNREFERENCED_PARAMETER(bUnderline);
      UNREFERENCED_PARAMETER(cStrikeOut);
      UNREFERENCED_PARAMETER(nCharSet);
      UNREFERENCED_PARAMETER(nOutPrecision);
      UNREFERENCED_PARAMETER(nClipPrecision);
      UNREFERENCED_PARAMETER(nQuality);
      UNREFERENCED_PARAMETER(nPitchAndFamily);
      UNREFERENCED_PARAMETER(lpszFacename);
      throw interface_only_exception();   
   }

   int font::GetLogFont(LOGFONT* pLogFont)
   {
      UNREFERENCED_PARAMETER(pLogFont);
      throw interface_only_exception();   
   }

   font & font::operator =(const font & fontSrc)
   {
      if(&fontSrc == this)
         return *this;
      LOGFONT lf;
      memset(&lf, 0, sizeof(lf));
      (const_cast < font & > (fontSrc)).GetLogFont(&lf);
      if(get_os_data() != NULL)
         delete_object();
      CreateFontIndirect(&lf);
      return *this;
   }

} // namespace ca