#include "StdAfx.h"

namespace user
{

   str_context::str_context()
   {
      m_pstr = NULL;
   }

   bool str_context::matches(const id & idRoot, const id & idExtra, const char * psz)
   {
      if(m_pstr == NULL)
         return false;
      return m_pstr->matches(this, idRoot, idExtra, psz);
   }

   bool str_context::begins(const id & idRoot, const id & idExtra, const char * psz)
   {
      if(m_pstr == NULL)
         return false;
      return m_pstr->begins(this, idRoot, idExtra, psz);
   }

   bool str_context::begins_eat(string & strTopic, const id & idRoot, const id & idExtra)
   {
      if(m_pstr == NULL)
         return false;
      return m_pstr->begins_eat(this, strTopic, idRoot, idExtra);
   }

   void str_context::get(stringa & stra, const id & idRoot, const id & idExtra)
   {
      if(m_pstr == NULL)
         return;
      return m_pstr->get(stra, this, idRoot, idExtra);
   }

   string str_context::get(const id & idRoot, const id & idExtra)
   {
      if(m_pstr == NULL)
         return "";
      return m_pstr->get(this, idRoot, idExtra);
   }

   str::str(::ca::application * papp) :
   ca(papp)
   {
   }

   bool str::initialize()
   {
      string strMain = System.dir().path(System.dir().votagus(), "app\\appmatter\\main");
      if(!load(strMain))
         return false;
      return true;
   }

   bool str::load(const char * pszBaseDir)
   {
      string strMain = pszBaseDir;
      stringa straLangPath;
      stringa straLang;
      Application.dir().ls_dir(strMain, &straLangPath, &straLang);
      for(int iLang = 0; iLang < straLang.get_count(); iLang++)
      {
         string strLang = straLang[iLang];
         if(strLang.CompareNoCase(".svn") == 0)
            continue;
         stringa straStylePath;
         stringa straStyle;
         Application.dir().ls_dir(straLangPath[iLang], &straStylePath, &straStyle);
         for(int iStyle = 0; iStyle < straStyle.get_count(); iStyle++)
         {
            string idStyle = straStyle[iStyle];
            if(idStyle.CompareNoCase(".svn") == 0)
               continue;
            stringa straPath;
            Application.dir().rls(
               System.dir().path(straStylePath[iStyle], "uistr"),
               &straPath);
            for(int iPath = 0; iPath < straPath.get_count(); iPath++)
            {
               string strPath = straPath[iPath];
               if(gen::str::ends_ci(strPath, "\\.svn"))
                  continue;
               if(gen::str::find_ci("\\.svn\\", strPath) >= 0)
                  continue;
               if(Application.dir().is(strPath))
                  continue;
               load_uistr_file(strLang, idStyle, strPath);
            }
         }
      }

      return true;

/*      xml::node node(get_app());
      node.load(Application.file().as_string(pszFileName));
      for(int i = 0; i < node.get_children_count(); i++)
      {
         add(
            node.child_at(i)->get_attr("root"),
            node.child_at(i)->get_attr("lang"),
            node.child_at(i)->get_attr("style"),
            node.child_at(i)->get_attr("target"));
      }*/
   }

   void str::set(const id & idRoot, const id & pszLang, const id & pszStyle, const id & idExtra, const char * psz)
   {
      (*this)[idExtra][pszLang][pszStyle][idRoot].m_str = psz;
   }

   string str::get(str_context * pcontext, const id & idRoot, const id & pszLang, const id & pszStyle, const id & idExtra)
   {
      static id idEn("en");
      static id idStd("_std");
      string str;
      if(pszLang != NULL)
      {
         if(pszStyle != NULL)
         {
            str = (*this)[idExtra][pszLang][pszStyle][idRoot].m_str;
            if(str.has_char())
               return str;
         }
         str = (*this)[idExtra][pszLang][pszLang][idRoot].m_str;
         if(str.has_char())
            return str;
      }
      if(pcontext != NULL)
      {
         for(int i = 0; i < pcontext->param_locale_ex().get_count(); i++)
         {
            id & idStyle = pcontext->param_style_ex()[i];
            id & idLocale = pcontext->param_locale_ex()[i];
            str = (*this)[idExtra][idLocale][idStyle][idRoot].m_str;
            if(str.has_char())
               return str;
            str = (*this)[idExtra][idLocale][idLocale][idRoot].m_str;
            if(str.has_char())
               return str;
         }
      }
      if(pszStyle != NULL)
      {
         str = (*this)[idExtra][pszStyle][idEn][idRoot].m_str;
         if(str.has_char())
            return str;
      }
      str = (*this)[idExtra][idEn][idEn][idRoot].m_str;
      if(str.has_char())
         return str;
      if(pszStyle != NULL)
      {
         str = (*this)[idExtra][pszStyle][idStd][idRoot].m_str;
         if(str.has_char())
            return str;
      }
      str = (*this)[idExtra][idStd][idStd][idRoot].m_str;
      return str;
   }

   void str::get(stringa & stra, str_context * pcontext, const id & idRoot, const id & pszLang, const id & pszStyle, const id & idExtra)
   {
      static id idEn("en");
      static id idStd("_std");
      string str;
      if(pszLang != NULL)
      {
         if(pszStyle != NULL)
         {
            str = (*this)[idExtra][pszLang][pszStyle][idRoot].m_str;
            if(str.has_char())
               stra.add_unique(str);
         }
         str = (*this)[idExtra][pszLang][pszLang][idRoot].m_str;
         if(str.has_char())
            stra.add_unique(str);
      }
      if(pcontext != NULL)
      {
         for(int i = 0; i < pcontext->param_locale_ex().get_count(); i++)
         {
            id & idStyle = pcontext->param_style_ex()[i];
            id & idLocale = pcontext->param_locale_ex()[i];
            str = (*this)[idExtra][idLocale][idStyle][idRoot].m_str;
            if(str.has_char())
               stra.add_unique(str);
            str = (*this)[idExtra][idLocale][idLocale][idRoot].m_str;
            if(str.has_char())
               stra.add_unique(str);
         }
      }
      if(pszStyle != NULL)
      {
         str = (*this)[idExtra][pszStyle][idEn][idRoot].m_str;
         if(str.has_char())
            stra.add_unique(str);
      }
      str = (*this)[idExtra][idEn][idEn][idRoot].m_str;
      if(str.has_char())
         stra.add_unique(str);
      if(pszStyle != NULL)
      {
         str = (*this)[idExtra][pszStyle][idStd][idRoot].m_str;
         if(str.has_char())
            stra.add_unique(str);
      }
      str = (*this)[idExtra][idStd][idStd][idRoot].m_str;
      if(str.has_char())
         stra.add_unique(str);
   }

/*   string persistent_ui_str::get(script_interface * pscript, const char * idRoot, const char * pszLang, const char * pszStyle)
   {
      string str;
      str = operator[](idRoot)[pszStyle][pszLang].m_str;
      if(str.has_char())
         return str;
      str = operator[](idRoot)[pszLang][pszLang].m_str;
      if(str.has_char())
         return str;
      str = operator[](idRoot)[pszStyle]["en"].m_str;
      if(str.has_char())
         return str;
      str = operator[](idRoot)["en"]["en"].m_str;
      return str;
   }
*/
   bool str::load_uistr_file(const id & pszLang, const id & pszStyle, const char * pszFile)
   {
      stringa straLines;
      stringa straSep;
      straSep.add("\r\n");
      straSep.add("\r");
      straSep.add("\n");
      straSep.add("\n\r");
      straLines.add_smallest_tokens(Application.file().as_string(pszFile), straSep, false);

      string str;
      string strLine;
      int i = 0;
      while(i < straLines.get_count())
      {
         for(; i < straLines.get_count(); i++)
         {
            strLine = straLines[i];
            if(strLine.Right(1) == "\\")
            {
               str += strLine.Left(strLine.get_length() - 1);
            }
            else
            {
               str += strLine;
               i++;
               break;
            }
         }
         str.trim();
         if(str.is_empty())
            continue;
         try
         {
            const char * psz = str;
            while(isspace(*psz))
               psz++;
            string strRoot = gen::str::consume_quoted_value(psz);
            while(isspace(*psz))
               psz++;
            if(*psz != '=')
               continue;
            psz++;
            while(isspace(*psz))
               psz++;
            string strBody = gen::str::consume_quoted_value(psz);
            set(
               strRoot,
               pszLang,
               pszStyle,
               NULL,
               body(strBody));
            str.Empty();
         }
         catch(...)
         {
         }
      }

      return true;
   }

   string str::body(const char * psz)
   {
      string str(psz);
      str.replace("\\r", "\r");
      str.replace("\\n", "\n");
      return str;
   }

   bool str::matches(str_context * pcontext, const id & idRoot, const id & idExtra, const char * psz)
   {
      string str;
      if(pcontext != NULL)
      {
         for(int i = 0; i < pcontext->param_locale_ex().get_count(); i++)
         {
            id & idStyle = pcontext->param_style_ex()[i];
            id idLocale = pcontext->param_locale_ex()[i];
            str = (*this)[idExtra][idLocale][idStyle][idRoot].m_str;
            if(!str.CompareNoCase(psz))
               return true;
            str = (*this)[idExtra][idLocale][idLocale][idRoot].m_str;
            if(!str.CompareNoCase(psz))
               return true;
         }
      }
      str = (*this)[idExtra]["en"]["en"][idRoot].m_str;
      if(!str.CompareNoCase(psz))
         return true;
      str = (*this)[idExtra]["_std"]["_std"][idRoot].m_str;
      if(!str.CompareNoCase(psz))
         return true;
      return false;
   }

   bool str::begins(str_context * pcontext, const char * pszTopic, const id & idRoot, const id & idExtra)
   {
      string str;
      if(pcontext != NULL)
      {
         for(int i = 0; i < pcontext->param_locale_ex().get_count(); i++)
         {
            const id & idStyle = pcontext->param_style_ex()[i];
            const id & idLocale = pcontext->param_locale_ex()[i];
            str = (*this)[idExtra][idLocale][idStyle][idRoot].m_str;
            if(str.has_char() && gen::str::begins_ci(pszTopic, str))
               return true;
            str = (*this)[idExtra][idLocale][idLocale][idRoot].m_str;
            if(str.has_char() && gen::str::begins_ci(pszTopic, str))
               return true;
         }
      }
      str = (*this)[idExtra]["en"]["en"][idRoot].m_str;
      if(str.has_char() && gen::str::begins_ci(pszTopic, str))
         return true;
      str = (*this)[idExtra]["_std"]["_std"][idRoot].m_str;
      if(str.has_char() && gen::str::begins_ci(pszTopic, str))
         return true;
      return false;
   }

   bool str::begins_eat(str_context * pcontext, string & strTopic, const id & idRoot, const id & idExtra)
   {
      string str;
      if(pcontext != NULL)
      {
         for(int i = 0; i < pcontext->param_locale_ex().get_count(); i++)
         {
            id & idStyle = pcontext->param_style_ex()[i];
            id & idLocale = pcontext->param_locale_ex()[i];
            str = (*this)[idExtra][idLocale][idStyle][idRoot].m_str;
            if(str.has_char() && gen::str::begins_eat_ci(strTopic, str))
               return true;
            str = (*this)[idExtra][idLocale][idLocale][idRoot].m_str;
            if(str.has_char() && gen::str::begins_eat_ci(strTopic, str))
               return true;
         }
      }
      str = (*this)[idExtra]["en"]["en"][idRoot].m_str;
      if(str.has_char() && gen::str::begins_eat_ci(strTopic, str))
         return true;
      str = (*this)[idExtra]["_std"]["_std"][idRoot].m_str;
      if(str.has_char() && gen::str::begins_eat_ci(strTopic, str))
         return true;
      return false;
   }

   void str::get(stringa & stra, str_context * pcontext, const id & idRoot, const id & idExtra)
   {
      string str;
      string strRoot;
      if(pcontext != NULL)
      {
         for(int i = 0; i < pcontext->param_locale_ex().get_count(); i++)
         {
            id & idStyle = pcontext->param_style_ex()[i];
            id & idLocale = pcontext->param_locale_ex()[i];
            str = (*this)[idExtra][idLocale][idStyle][idRoot].m_str;
            if(str.has_char())
               stra.add_unique(str);
            str = (*this)[idExtra][idLocale][idLocale][idRoot].m_str;
            if(str.has_char())
               stra.add_unique(str);
         }
         bool bOk = true;
         int i = 0;
         while(i < 32 && bOk)
         {
            bOk = false;
            for(int j = 0; j < pcontext->param_locale_ex().get_count(); j++)
            {
               id & idStyle = pcontext->param_style_ex()[i];
               id & idLocale = pcontext->param_locale_ex()[i];
               strRoot.Format("%s[%d]", idRoot.str(), i);
               str = (*this)[idExtra][idLocale][idStyle][strRoot].m_str;
               if(str.has_char())
               {
                  bOk = true;
                  stra.add_unique(str);
               }
               str = (*this)[idExtra][idLocale][idLocale][strRoot].m_str;
               if(str.has_char())
               {
                  bOk = true;
                  stra.add_unique(str);
               }
            }
            i++;
         }
      }
      str = (*this)[idExtra]["en"]["en"][idRoot].m_str;
      if(str.has_char())
         stra.add_unique(str);
      str = (*this)[idExtra]["_std"]["_std"][idRoot].m_str;
      if(str.has_char())
         stra.add_unique(str);
   }

   string str::get(str_context * pcontext, const id & idRoot, const id & idExtra)
   {
      string str;
      if(pcontext != NULL)
      {
         for(int i = 0; i < pcontext->param_locale_ex().get_count(); i++)
         {
            id & idStyle = pcontext->param_style_ex()[i];
            id & idLocale = pcontext->param_locale_ex()[i];
            str = (*this)[idExtra][idLocale][idStyle][idRoot].m_str;
            if(str.has_char())
               return str;
            str = (*this)[idExtra][idLocale][idLocale][idRoot].m_str;
            if(str.has_char())
               return str;
         }
      }
      str = (*this)[idExtra]["en"]["en"][idRoot].m_str;
      if(str.has_char())
         return str;
      str = (*this)[idExtra]["_std"]["_std"][idRoot].m_str;
      if(str.has_char())
         return str;
      return "";
   }

} // namespace user
