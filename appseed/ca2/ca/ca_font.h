#pragma once

namespace ca
{

   class CLASS_DECL_ca font : 
      virtual public graphics_object
   {
   public:

      virtual BOOL CreateFontIndirect(const LOGFONT* lpLogFont);
      virtual BOOL CreateFont(int nHeight, int nWidth, int nEscapement,
            int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline,
            BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision,
            BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily,
            const char * lpszFacename);
      virtual BOOL CreatePointFont(int nPointSize, const char * lpszFaceName, ::ca::graphics * pgraphics = NULL);
      virtual BOOL CreatePointFontIndirect(const LOGFONT* lpLogFont, ::ca::graphics * pgraphics = NULL);

   // Attributes
      virtual int GetLogFont(LOGFONT* pLogFont);


      font & operator =(const font & fontSrc);

      // Implementation
      public:
      #ifdef _DEBUG
         virtual void dump(dump_context & dumpcontext) const;
      #endif
   };

   typedef smart_pointer < font > font_sp;

} // namespace ca