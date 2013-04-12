#include "framework.h"

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

   bool font::create(sp(::ca::application) papp)
   {
      m_font.create(papp);


      int32_t iWeight;
      if(m_strWeight.CompareNoCase("bold") == 0)
      {
         iWeight = 800;
      }
      else
      {
         iWeight = 400;
      }
      
      double dSize;
      
      m_strSize.trim();

      if(m_strSize.is_empty())
      {
         dSize = 11;
      }
      else
      {
         dSize = strtod(m_strSize, ::null());
      }



      stringa stra;
      stra.add_tokens(m_strFamily,",", false);
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         stra[i].trim();
         if(stra[i].CompareNoCase("fixed-width") == 0)
         {
         }
         else if(stra[i].CompareNoCase("sans-serif") == 0)
         {
         }
         else if(stra[i].CompareNoCase("serif") == 0)
         {
         }
      }
//      strsize iLen;
      string strName;
      if(stra.get_count() > 0)
      {
         strName = stra[0];
//         iLen = min(sizeof(lf.lfFaceName) - 1, stra[0].get_length());
  //       strncpy(lf.lfFaceName, stra[0], iLen);
    //     lf.lfFaceName[iLen] = '\0';
         strName.trim();
      }
      else
      {
         strName = "Arial";
      }
      
      
      bool bUnderline = ::ca::str::find_ci("underline", m_strTextDecoration) >= 0;

      m_font->create_point_font(strName, dSize, iWeight, false, bUnderline);

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
