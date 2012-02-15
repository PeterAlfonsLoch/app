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

         locale_style::locale_style(const locale_style & ls) :
            ca(ls.get_app())
         {

            operator = (ls);
         
         }


         locale_style::~locale_style()
         {
         }


         bool locale_style::add_locale_variant(const char * pszLocale, const char * pszStyle)
         {

            if(m_idLocale.is_empty())
            {
               m_idLocale = pszLocale;
               if(m_idLocale.is_empty())
                  m_idLocale = "_std";
            }
            if(m_idStyle.is_empty())
            {
               m_idStyle = pszStyle;
               if(m_idStyle.is_empty())
                  m_idStyle = "_std";
            }

            string strLocale = pszLocale;
            string strStyle = pszStyle;

            if(strLocale.is_empty() && strStyle.is_empty())
               return false;

            if(strLocale.is_empty())
               strLocale = m_idLocale;
            
            if(strStyle.is_empty())
               strStyle = m_idStyle;

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

               if(strStyle == string(m_idStyle) && m_idStyle == m_idLocale) // if style is a locale and alternate style is locale too
               {
                  strStyle = pszLocale;
               }

               if(strStyle.get_length() == 0)
               {
                  strStyle = "_std";
               }

               for(int i = 0; i < m_idaLocale.get_count() && i < m_idaStyle.get_count(); i++)
               {
                  if(m_idaLocale[i] == pszLocale && m_idaStyle[i] == strStyle)
                     goto step2;
               }

               m_idaLocale.add(pszLocale);
               m_idaStyle.add(strStyle);

               bAdded = true;

            }

            step2:

            strStyle = m_idStyle;

            if(strStyle.get_length() == 0)
            {
               strStyle = "_std";
            }

            for(int i = 0; i < m_idaLocale.get_count() && i < m_idaStyle.get_count(); i++)
            {
               if(m_idaLocale[i] == pszLocale && m_idaStyle[i] == strStyle)
                  return bAdded;
            }

            m_idaLocale.add(pszLocale);
            m_idaStyle.add(strStyle);

            return true;

         }


         bool locale_style::process_final_locale_style(bool bRTLLayout)
         {
         restart:
            for(index i = 0; i < m_idaLocale.get_count(); i++)
            {
               string strLocale = m_idaLocale[i];
               if(i >= m_idaStyle.get_count())
                  m_idaStyle.add(m_idStyle);
               string strStyle = m_idaStyle[i];
               stringa stra;
               stra.explode("-", strLocale);
               if(stra.get_count() == 2)
               {
                  if(m_idaLocale.find_first(stra[0]) < 0)
                  {
                     m_idaLocale.insert_at(i + 1, stra[0]);
                     m_idaStyle.insert_at(i + 1, strStyle);
                     goto restart;
                  }
                  if(m_idaLocale.find_first(stra[1]) < 0)
                  {
                     m_idaLocale.insert_at(i + 1, stra[1]);
                     m_idaStyle.insert_at(i + 1, strStyle);
                     goto restart;
                  }
               }

            }


            comparable_array < id > idaLocaleAdd1;
            comparable_array < id > idaStyleAdd1;


            if(bRTLLayout)
            {
               for(index i = 0; i < m_idaLocale.get_count(); i++)
               {
                  string strLocale = m_idaLocale[i];
                  if(i >= m_idaStyle.get_count())
                     m_idaStyle.add(m_idStyle);
                  string strStyle = m_idaStyle[i];
                  if(strStyle.CompareNoCase("_std") != 0)
                  {
                     idaLocaleAdd1.add(strLocale);
                     idaStyleAdd1.add(strStyle + "_rl");
                  }
               }
            }
            if(bRTLLayout)
            {
               for(index i = 0; i < m_idaLocale.get_count(); i++)
               {
                  string strLocale = m_idaLocale[i];
                  if(i >= m_idaStyle.get_count())
                     m_idaStyle.add("_std");
                  string strStyle = m_idaStyle[i];
                  if(strStyle.CompareNoCase("_std") != 0)
                  {
                     idaLocaleAdd1.add(strLocale);
                     idaStyleAdd1.add("_std_rl");
                  }
               }
            }
            if(!m_bFixStyle)
            {
               for(index i = 0; i < m_idaLocale.get_count(); i++)
               {
                  string strLocale = m_idaLocale[i];
                  if(i >= m_idaStyle.get_count())
                     m_idaStyle.add("_std");
                  string strStyle = m_idaStyle[i];
                  if(strStyle.CompareNoCase("_std") != 0)
                  {
                     idaLocaleAdd1.add(strLocale);
                     idaStyleAdd1.add("_std");
                  }
               }
            }
            
            m_idaLocale.add(idaLocaleAdd1);
            m_idaStyle.add(idaStyleAdd1);


            return true;
         }

         bool locale_style::process_final_locale_style()
         {
            return process_final_locale_style(Application.directrix().m_varTopicQuery.has_property("right_to_left_layout") &&
               (bool) Application.directrix().m_varTopicQuery["right_to_left_layout"]);
         }

         locale_style & locale_style::operator = (const locale_style & ls)
         {

            if(&ls != this)
            {

               m_bFixStyle          = ls.m_bFixStyle;
               m_idLocale          = ls.m_idLocale;
               m_idStyle           = ls.m_idStyle;
               m_idaLocale         = ls.m_idaLocale;
               m_idaStyle          = ls.m_idaStyle;

            }

            return *this;
            
         }


   }  // namespace international


} // namespace gen


