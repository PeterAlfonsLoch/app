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

      enum e_cs
      {
         cs_none,
         cs_ansi,
         cs_default,
         cs_symbol,
         cs_shiftjis,
         cs_hangeul,
         cs_hangul,
         cs_gb2312,
         cs_chinesebig5,
         cs_johab,
         cs_hebrew,
         cs_arabic,
         cs_greek, 
         cs_turkish, 
         cs_vietnamese, 
         cs_thai, 
         cs_easteurope, 
         cs_russian,
         cs_mac,
         cs_baltic,
         cs_count
      };

      class CLASS_DECL_AURA enum_item
      {
      public:

         string      m_strFile;
         string      m_strName;
         e_cs        m_ecs;


         enum_item() : m_ecs(cs_none) {}
         enum_item(string strName, e_cs ecs) : m_strName(strName), m_ecs(ecs) {}
         enum_item(string strFile, string strName, e_cs ecs) : m_strFile(strFile), m_strName(strName), m_ecs(ecs) {}

         bool operator < (const enum_item & item) const
         {

            int iCompare = m_strName.compare(item.m_strName);

            if (iCompare < 0)
               return true;

            if (iCompare > 0)
               return false;

            iCompare = ((int) m_ecs) - ((int) item.m_ecs);

            if (iCompare < 0)
               return true;

            if (iCompare > 0)
               return false;

            return m_strFile.compare(item.m_strFile);

         }

         bool operator == (const enum_item & item) const
         {

            return m_strFile == item.m_strFile
               && m_strName == item.m_strName
               && m_ecs == item.m_ecs;

         }

         bool operator != (const enum_item & item) const { return !this->operator==(item);  }

      };


      using enum_item_array = comparable_array < enum_item >;


      string      m_strFontFamilyName;
      double      m_dFontSize;
      double      m_dFontWidth;
      e_unit      m_eunitFontSize;
      int32_t     m_iFontWeight;
      bool        m_bItalic;
      bool        m_bUnderline;
      bool        m_bStrikeout;
      e_cs        m_ecs;
      e_text_rendering m_etextrendering;

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
      
      virtual e_cs calc_cs(::draw2d::graphics * pgraphics);
      virtual e_cs get_cs(::draw2d::graphics * pgraphics);
      virtual string get_sample_text(::draw2d::graphics * pgraphics);

      static string get_sample_text(e_cs ecs);

      

   };
   
   
   typedef smart_pointer < font > font_sp;

#ifdef WINDOWS

   CLASS_DECL_AURA void wingdi_enum_fonts(::draw2d::font::enum_item_array & itema, bool bRaster, bool bTrueType, bool bOther);
   CLASS_DECL_AURA font::e_cs wingdi_get_cs(int iCs);

#endif

   
} // namespace draw2d






