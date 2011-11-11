#include "StdAfx.h"

namespace html
{

   font::font()
   {
   }

   font::font(const class font & font)
   {
      m_strFamily             = font.m_strFamily;
      m_strSize               = font.m_strSize;
      m_strWeight             = font.m_strWeight;
      m_strTextDecoration     = font.m_strTextDecoration;
   }

   bool font::create(::ca::application * papp)
   {
      m_font.create(papp);
      LOGFONT lf;

      memset(&lf, 0, sizeof(lf));


      if(m_strWeight.CompareNoCase("bold") == 0)
      {
         lf.lfWeight = 800;
      }
      else
      {
         lf.lfWeight = 400;
      }
      lf.lfHeight = atoi(m_strSize);
      if(lf.lfHeight == 0)
         lf.lfHeight = 16;
      stringa stra;
      stra.add_tokens(m_strFamily,",", false);
      for(int i = 0; i < stra.get_size(); i++)
      {
         stra[i].trim();
         if(stra[i].CompareNoCase("fixed-width") == 0)
         {
            lf.lfPitchAndFamily = FF_DONTCARE | FIXED_PITCH;
            lf.lfQuality = PROOF_QUALITY;
            lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
            lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
            lf.lfCharSet =  DEFAULT_CHARSET;
         }
         else if(stra[i].CompareNoCase("sans-serif") == 0)
         {
            lf.lfPitchAndFamily = FF_SWISS | DEFAULT_PITCH;
         }
         else if(stra[i].CompareNoCase("serif") == 0)
         {
            lf.lfPitchAndFamily = FF_ROMAN | DEFAULT_PITCH;
         }
      }
      int iLen;
      if(stra.get_count() > 0)
      {
         iLen = min(sizeof(lf.lfFaceName) - 1, stra[0].get_length());
         strncpy(lf.lfFaceName, stra[0], iLen);
         lf.lfFaceName[iLen] = '\0';
         /*
         if(stra[0] == "Courier New")
         {
            string strHard = "Times New Roman";
            iLen = min(sizeof(lf.lfFaceName) - 1, strlen(strHard));
            strncpy(lf.lfFaceName, strHard, iLen);
         }
         */
      }
      lf.lfUnderline = gen::str::find_ci("underline", m_strTextDecoration) >= 0;

      m_font->CreateFontIndirectA(&lf);

      return true;
   }

   bool font::operator == (const font & font)
   {
      return !m_strFamily.CompareNoCase(font.m_strFamily)
          && !m_strSize.CompareNoCase(font.m_strSize)
          && !m_strWeight.CompareNoCase(font.m_strWeight)
          && !m_strTextDecoration.CompareNoCase(font.m_strTextDecoration);
   }

} // namespace html
