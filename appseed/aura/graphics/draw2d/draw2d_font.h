#pragma once


namespace draw2d
{



   class CLASS_DECL_AURA text_metric
   {
   public:


      LONG        tmHeight;
      LONG        tmAscent;
      LONG        tmDescent;
      LONG        tmInternalLeading;
      LONG        tmExternalLeading;
      LONG        tmAveCharWidth;
      LONG        tmMaxCharWidth;
      LONG        tmWeight;
      LONG        tmOverhang;
      LONG        tmDigitizedAspectX;
      LONG        tmDigitizedAspectY;
      WCHAR       tmFirstChar;
      WCHAR       tmLastChar;
      WCHAR       tmDefaultChar;
      WCHAR       tmBreakChar;
      BYTE        tmItalic;
      BYTE        tmUnderlined;
      BYTE        tmStruckOut;
      BYTE        tmPitchAndFamily;
      BYTE        tmCharSet;

   };

   class CLASS_DECL_AURA font :
      virtual public ::draw2d::object
   {
   public:


      string      m_strFontFamilyName;
      double      m_dFontSize;
      double      m_dFontWidth;
      e_unit      m_eunitFontSize;
      int32_t         m_iFontWeight;
      bool        m_bItalic;
      bool        m_bUnderline;
      bool        m_bStrikeout;


      font();
      font(const font & font);
      virtual ~font();



      virtual bool create_pixel_font(
         const char * lpszFacename,
         double dSize,
         int32_t iWeight = 400,
         bool bItalic = false,
         bool bUnderline = false,
         bool bStrikeOut = false,
         double dWidth = 1.0);

      virtual bool create_point_font(
         const char * lpszFacename,
         double dSize,
         int32_t iWeight = 400,
         bool bItalic = false,
         bool bUnderline = false,
         bool bStrikeOut = false,
         double dWidth = 1.0);


      //    int32_t nEscapement
      //    int32_t nOrientation
      //    BYTE nCharSet
      //    BYTE nOutPrecision
      //    BYTE nClipPrecision
      //    BYTE nQuality
      //    BYTE nPitchAndFamily

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

   
} // namespace draw2d






