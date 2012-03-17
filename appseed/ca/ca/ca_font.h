#pragma once


namespace ca
{

   enum e_unit
   {
      unit_pixel,
      unit_point,
   };

   class CLASS_DECL_ca font : 
      virtual public graphics_object
   {
   public:


      string      m_strFontFamilyName;
      double      m_dFontSize;
      double      m_dFontWidth;
      e_unit      m_eunitFontSize;
      bool        m_bBold;
      bool        m_bItalic;
      bool        m_bUnderline;
      bool        m_bStrikeout;


      font();


      virtual BOOL CreateFontIndirect(const LOGFONT* lpLogFont);
      virtual BOOL CreateFont(int nHeight, int nWidth, int nEscapement,
            int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline,
            BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision,
            BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily,
            const char * lpszFacename);
      virtual BOOL CreatePointFont(int nPointSize, const char * lpszFaceName, ::ca::graphics * pgraphics = NULL);
      virtual BOOL CreatePointFontIndirect(const LOGFONT* lpLogFont, ::ca::graphics * pgraphics = NULL);

      font & operator = (const font & font);

      virtual void dump(dump_context & dumpcontext) const;

      virtual void set_family_name(const char * pszFamilyName);
      virtual void set_size(double dSize, e_unit = unit_point);
      virtual void set_bold(bool bBold = true);
      virtual void set_italic(bool bItalic = true);
      virtual void set_underline(bool bUnderline = true);
      virtual void set_strikeout(bool bStrikeout = true);


   };

   typedef smart_pointer < font > font_sp;

} // namespace ca