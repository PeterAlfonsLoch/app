#include "StdAfx.h"


namespace gen
{


   namespace international
   {


         locale_style::locale_style(::ca::application * papp) :
            ca(papp)
         {

            m_bFixStyle             = false;

            m_bAddAlternateStyle    = false;

         }


         locale_style::~locale_style()
         {
         }


         bool locale_style::add_locale_variant(const char * pszLocale, const char * pszStyle)
         {

            if(m_strLocale.is_empty())
            {
               m_strLocale = pszLocale;
               if(m_strLocale.is_empty())
                  m_strLocale = "_std";
            }
            if(m_strStyle.is_empty())
            {
               m_strStyle = pszStyle;
               if(m_strStyle.is_empty())
                  m_strStyle = "_std";
            }

            string strLocale = pszLocale;
            string strStyle = pszStyle;

            if(strLocale.is_empty() && strStyle.is_empty())
               return false;

            if(strLocale.is_empty())
               strLocale = m_strLocale;
            
            if(strStyle.is_empty())
               strStyle = m_strStyle;

            if(defer_add_locale(strLocale, strStyle))
            {
               _add_locale_variant(strLocale, strStyle);
            }

            stringa stra;
            stra.add_tokens(strLocale, "-", FALSE);
            if(stra.get_count() > 1)
            {
               for(int i = stra.get_upper_bound(); i >= 0; i--)
               {
                  if(defer_add_locale(stra[i], pszStyle))
                  {
                     _add_locale_variant(stra[i], pszStyle);
                  }
               }
            }
            
            return true;

         }

         bool locale_style::finalize(bool bRtlLayout)
         {
            return process_final_locale_style(bRtlLayout);
         }

         bool locale_style::finalize()
         {
            return process_final_locale_style();
         }


         bool locale_style::_add_locale_variant(const char * pszLocale, const char  * pszStyle)
         {
            string strLocale(pszLocale);

            if(strLocale == "at")
            {
               defer_add_locale("de-at", pszStyle);
               defer_add_locale("de", pszStyle);
               defer_add_locale("de-de", pszStyle);
            }
            else if(strLocale == "br")
            {
               defer_add_locale("pt-br", pszStyle);
               defer_add_locale("pt", pszStyle);
               defer_add_locale("es", pszStyle);
            }
            else if(strLocale == "cn")
            {
               defer_add_locale("zh-cn", pszStyle);
               defer_add_locale("zh-tw", pszStyle);
            }
            else if(strLocale == "hk")
            {
               defer_add_locale("zh-cn", pszStyle);
               defer_add_locale("zh-tw", pszStyle);
               defer_add_locale("cn", pszStyle);
            }
            else if(strLocale == "ja")
            {
               defer_add_locale("jp", pszStyle);
            }
            else if(strLocale == "jp")
            {
               defer_add_locale("ja", pszStyle);
            }
            else if(strLocale == "pt")
            {
               defer_add_locale("br", pszStyle);
               defer_add_locale("pt-br", pszStyle);
               defer_add_locale("es", pszStyle);
            }
            else if(strLocale == "es")
            {
               defer_add_locale("br", pszStyle);
               defer_add_locale("pt-br", pszStyle);
               defer_add_locale("pt", pszStyle);
            }
            else if(strLocale == "pe")
            {
               defer_add_locale("es", pszStyle);
               defer_add_locale("br", pszStyle);
               defer_add_locale("pt-br", pszStyle);
               defer_add_locale("pt", pszStyle);
            }
            else if(strLocale == "en")
            {
               defer_add_locale("_std", pszStyle);
            }
            else if(strLocale == "mx")
            {
               defer_add_locale("es", pszStyle);
               defer_add_locale("br", pszStyle);
               defer_add_locale("pt-br", pszStyle);
               defer_add_locale("pt", pszStyle);
            }
            else if(strLocale == "ec")
            {
               defer_add_locale("es", pszStyle);
               defer_add_locale("br", pszStyle);
               defer_add_locale("pt-br", pszStyle);
               defer_add_locale("pt", pszStyle);
            }
            else if(strLocale == "tw")
            {
               defer_add_locale("zh-cn", pszStyle);
               defer_add_locale("zh-tw", pszStyle);
               defer_add_locale("cn", pszStyle);
            }
            return true;

         }


         bool locale_style::defer_add_locale(const char * pszLocale, const char * pszStyle)
         {

            bool bAdded = false;

            string strStyle;

            if(m_bAddAlternateStyle)
            {

               strStyle = pszStyle;

               if(strStyle.get_length() == 0)
               {
                  strStyle = "_std";
               }

               for(int i = 0; i < m_straLocale.get_count() && i < m_straStyle.get_count(); i++)
               {
                  if(m_straLocale[i] == pszLocale && m_straStyle[i] == strStyle)
                     goto step2;
               }

               m_straLocale.add(pszLocale);
               m_straStyle.add(strStyle);

               bAdded = true;

            }

            step2:

            strStyle = m_strStyle;

            if(strStyle.get_length() == 0)
            {
               strStyle = "_std";
            }

            for(int i = 0; i < m_straLocale.get_count() && i < m_straStyle.get_count(); i++)
            {
               if(m_straLocale[i] == pszLocale && m_straStyle[i] == strStyle)
                  return bAdded;
            }

            m_straLocale.add(pszLocale);
            m_straStyle.add(strStyle);

            return true;

         }


         bool locale_style::process_final_locale_style(bool bRTLLayout)
         {
         restart:
            for(index i = 0; i < m_straLocale.get_count(); i++)
            {
               string strLocale = m_straLocale[i];
               if(i >= m_straStyle.get_count())
                  m_straStyle.add(m_strStyle);
               string strStyle = m_straStyle[i];
               stringa stra;
               stra.explode("-", strLocale);
               if(stra.get_count() == 2)
               {
                  if(m_straLocale.find_first(stra[0]) < 0)
                  {
                     m_straLocale.insert_at(i + 1, stra[0]);
                     m_straStyle.insert_at(i + 1, strStyle);
                     goto restart;
                  }
                  if(m_straLocale.find_first(stra[1]) < 0)
                  {
                     m_straLocale.insert_at(i + 1, stra[1]);
                     m_straStyle.insert_at(i + 1, strStyle);
                     goto restart;
                  }
               }

            }
            stringa m_straLocaleAdd1;
            stringa m_straStyleAdd1;
            if(bRTLLayout)
            {
               for(index i = 0; i < m_straLocale.get_count(); i++)
               {
                  string strLocale = m_straLocale[i];
                  if(i >= m_straStyle.get_count())
                     m_straStyle.add(m_strStyle);
                  string strStyle = m_straStyle[i];
                  if(strStyle.CompareNoCase("_std") != 0)
                  {
                     m_straLocaleAdd1.add(strLocale);
                     m_straStyleAdd1.add(strStyle + "_rl");
                  }
               }
            }
            if(bRTLLayout)
            {
               for(index i = 0; i < m_straLocale.get_count(); i++)
               {
                  string strLocale = m_straLocale[i];
                  if(i >= m_straStyle.get_count())
                     m_straStyle.add("_std");
                  string strStyle = m_straStyle[i];
                  if(strStyle.CompareNoCase("_std") != 0)
                  {
                     m_straLocaleAdd1.add(strLocale);
                     m_straStyleAdd1.add("_std_rl");
                  }
               }
            }
            if(!m_bFixStyle)
            {
               for(index i = 0; i < m_straLocale.get_count(); i++)
               {
                  string strLocale = m_straLocale[i];
                  if(i >= m_straStyle.get_count())
                     m_straStyle.add("_std");
                  string strStyle = m_straStyle[i];
                  if(strStyle.CompareNoCase("_std") != 0)
                  {
                     m_straLocaleAdd1.add(strLocale);
                     m_straStyleAdd1.add("_std");
                  }
               }
            }
            
            m_straLocale.add(m_straLocaleAdd1);
            m_straStyle.add(m_straStyleAdd1);


            return true;
         }

         bool locale_style::process_final_locale_style()
         {
            return process_final_locale_style(Application.directrix().m_varTopicQuery.has_property("right_to_left_layout") &&
               (bool) Application.directrix().m_varTopicQuery["right_to_left_layout"]);
         }



   }  // namespace international


} // namespace gen


