#include "StdAfx.h"

namespace user
{

   str_context::str_context()
   {
      m_pstr = NULL;
   }

   bool str_context::matches(const char * pszRoot, const char * psz)
   {
      if(m_pstr == NULL)
         return false;
      return m_pstr->matches(this, pszRoot, psz);
   }

   bool str_context::begins_eat(string & strTopic, const char * pszRoot)
   {
      if(m_pstr == NULL)
         return false;
      return m_pstr->begins_eat(this, strTopic, pszRoot);
   }

   void str_context::get(stringa & stra, const char * pszRoot)
   {
      if(m_pstr == NULL)
         return;
      return m_pstr->get(stra, this, pszRoot);
   }

   string str_context::get(const char * pszRoot)
   {
      if(m_pstr == NULL)
         return "";
      return m_pstr->get(this, pszRoot);
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
      System.dir().ls_dir(strMain, &straLangPath, &straLang);
      for(int iLang = 0; iLang < straLang.get_count(); iLang++)
      {
         string strLang = straLang[iLang];
         if(strLang.CompareNoCase(".svn") == 0)
            continue;
         stringa straStylePath;
         stringa straStyle;
         System.dir().ls_dir(straLangPath[iLang], &straStylePath, &straStyle);
         for(int iStyle = 0; iStyle < straStyle.get_count(); iStyle++)
         {
            string strStyle = straStyle[iStyle];
            if(strStyle.CompareNoCase(".svn") == 0)
               continue;
            stringa straPath;
            System.dir().rls(
               System.dir().path(straStylePath[iStyle], "uistr"),
               &straPath);
            for(int iPath = 0; iPath < straPath.get_count(); iPath++)
            {
               string strPath = straPath[iPath];
               if(gen::str::ends_ci(strPath, "\\.svn"))
                  continue;
               if(gen::str::find_ci("\\.svn\\", strPath) >= 0)
                  continue;
               if(System.dir().is(strPath))
                  continue;
               load_uistr_file(strLang, strStyle, strPath);
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

   void str::set(const char * pszRoot, const char * pszLang, const char * pszStyle, const char * psz)
   {
      (*this)[pszLang][pszStyle][pszRoot].m_str = psz;
   }

   string str::get(str_context * pcontext, const char * pszRoot, const char * pszLang, const char * pszStyle)
   {
      string str;
      if(pszLang != NULL)
      {
         if(pszStyle != NULL)
         {
            str = (*this)[pszLang][pszStyle][pszRoot].m_str;
            if(str.has_char())
               return str;
         }
         str = (*this)[pszLang][pszLang][pszRoot].m_str;
         if(str.has_char())
            return str;
      }
      if(pcontext != NULL)
      {
         for(int i = 0; i < pcontext->param_locale_ex().get_count(); i++)
         {
            string strStyle = pcontext->param_style_ex()[i];
            string strLocale = pcontext->param_locale_ex()[i];
            str = (*this)[strLocale][strStyle][pszRoot].m_str;
            if(str.has_char())
               return str;
            str = (*this)[strLocale][strLocale][pszRoot].m_str;
            if(str.has_char())
               return str;
         }
      }
      if(pszStyle != NULL)
      {
         str = (*this)[pszStyle]["en"][pszRoot].m_str;
         if(str.has_char())
            return str;
      }
      str = (*this)["en"]["en"][pszRoot].m_str;
      if(str.has_char())
         return str;
      if(pszStyle != NULL)
      {
         str = (*this)[pszStyle]["_std"][pszRoot].m_str;
         if(str.has_char())
            return str;
      }
      str = (*this)["_std"]["_std"][pszRoot].m_str;
      return str;
   }

   void str::get(stringa & stra, str_context * pcontext, const char * pszRoot, const char * pszLang, const char * pszStyle)
   {
      string str;
      if(pszLang != NULL)
      {
         if(pszStyle != NULL)
         {
            str = (*this)[pszLang][pszStyle][pszRoot].m_str;
            if(str.has_char())
               stra.add_unique(str);
         }
         str = (*this)[pszLang][pszLang][pszRoot].m_str;
         if(str.has_char())
            stra.add_unique(str);
      }
      if(pcontext != NULL)
      {
         for(int i = 0; i < pcontext->param_locale_ex().get_count(); i++)
         {
            string strStyle = pcontext->param_style_ex()[i];
            string strLocale = pcontext->param_locale_ex()[i];
            str = (*this)[strLocale][strStyle][pszRoot].m_str;
            if(str.has_char())
               stra.add_unique(str);
            str = (*this)[strLocale][strLocale][pszRoot].m_str;
            if(str.has_char())
               stra.add_unique(str);
         }
      }
      if(pszStyle != NULL)
      {
         str = (*this)[pszStyle]["en"][pszRoot].m_str;
         if(str.has_char())
            stra.add_unique(str);
      }
      str = (*this)["en"]["en"][pszRoot].m_str;
      if(str.has_char())
         stra.add_unique(str);
      if(pszStyle != NULL)
      {
         str = (*this)[pszStyle]["_std"][pszRoot].m_str;
         if(str.has_char())
            stra.add_unique(str);
      }
      str = (*this)["_std"]["_std"][pszRoot].m_str;
      if(str.has_char())
         stra.add_unique(str);
   }

/*   string persistent_ui_str::get(netnodeScriptInterface * pscript, const char * pszRoot, const char * pszLang, const char * pszStyle)
   {
      string str;
      str = operator[](pszRoot)[pszStyle][pszLang].m_str;
      if(str.has_char())
         return str;
      str = operator[](pszRoot)[pszLang][pszLang].m_str;
      if(str.has_char())
         return str;
      str = operator[](pszRoot)[pszStyle]["en"].m_str;
      if(str.has_char())
         return str;
      str = operator[](pszRoot)["en"]["en"].m_str;
      return str;
   }
*/
   bool str::load_uistr_file(const char * pszLang, const char * pszStyle, const char * pszFile)
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

   bool str::matches(str_context * pcontext, const char * pszRoot, const char * psz)
   {
      string str;
      if(pcontext != NULL)
      {
         for(int i = 0; i < pcontext->param_locale_ex().get_count(); i++)
         {
            string strStyle = pcontext->param_style_ex()[i];
            string strLocale = pcontext->param_locale_ex()[i];
            str = (*this)[strLocale][strStyle][pszRoot].m_str;
            if(!str.CompareNoCase(psz))
               return true;
            str = (*this)[strLocale][strLocale][pszRoot].m_str;
            if(!str.CompareNoCase(psz))
               return true;
         }
      }
      str = (*this)["en"]["en"][pszRoot].m_str;
      if(!str.CompareNoCase(psz))
         return true;
      str = (*this)["_std"]["_std"][pszRoot].m_str;
      if(!str.CompareNoCase(psz))
         return true;
      return false;
   }

   bool str::begins_eat(str_context * pcontext, string & strTopic, const char * pszRoot)
   {
      string str;
      if(pcontext != NULL)
      {
         for(int i = 0; i < pcontext->param_locale_ex().get_count(); i++)
         {
            string strStyle = pcontext->param_style_ex()[i];
            string strLocale = pcontext->param_locale_ex()[i];
            str = (*this)[strLocale][strStyle][pszRoot].m_str;
            if(str.has_char() && gen::str::begins_eat_ci(strTopic, str))
               return true;
            str = (*this)[strLocale][strLocale][pszRoot].m_str;
            if(str.has_char() && gen::str::begins_eat_ci(strTopic, str))
               return true;
         }
      }
      str = (*this)["en"]["en"][pszRoot].m_str;
      if(str.has_char() && gen::str::begins_eat_ci(strTopic, str))
         return true;
      str = (*this)["_std"]["_std"][pszRoot].m_str;
      if(str.has_char() && gen::str::begins_eat_ci(strTopic, str))
         return true;
      return false;
   }

   void str::get(stringa & stra, str_context * pcontext, const char * pszRoot)
   {
      string str;
      if(pcontext != NULL)
      {
         for(int i = 0; i < pcontext->param_locale_ex().get_count(); i++)
         {
            string strStyle = pcontext->param_style_ex()[i];
            string strLocale = pcontext->param_locale_ex()[i];
            str = (*this)[strLocale][strStyle][pszRoot].m_str;
            if(str.has_char())
               stra.add_unique(str);
            str = (*this)[strLocale][strLocale][pszRoot].m_str;
            if(str.has_char())
               stra.add_unique(str);
         }
      }
      str = (*this)["en"]["en"][pszRoot].m_str;
      if(str.has_char())
         stra.add_unique(str);
      str = (*this)["_std"]["_std"][pszRoot].m_str;
      if(str.has_char())
         stra.add_unique(str);
   }

   string str::get(str_context * pcontext, const char * pszRoot)
   {
      string str;
      if(pcontext != NULL)
      {
         for(int i = 0; i < pcontext->param_locale_ex().get_count(); i++)
         {
            string strStyle = pcontext->param_style_ex()[i];
            string strLocale = pcontext->param_locale_ex()[i];
            str = (*this)[strLocale][strStyle][pszRoot].m_str;
            if(str.has_char())
               return str;
            str = (*this)[strLocale][strLocale][pszRoot].m_str;
            if(str.has_char())
               return str;
         }
      }
      str = (*this)["en"]["en"][pszRoot].m_str;
      if(str.has_char())
         return str;
      str = (*this)["_std"]["_std"][pszRoot].m_str;
      if(str.has_char())
         return str;
      return "";
   }

} // namespace user