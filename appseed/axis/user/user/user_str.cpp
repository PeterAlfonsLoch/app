#include "framework.h"


namespace user
{


   str_context::str_context(sp(::axis::application) papp) :
      element(papp)
   {


      m_plocaleschema = canew(::str::international::locale_schema(papp));


      m_pstr = NULL;


   }

   str_context::~str_context()
   {

   }


   void str_context::prepare()
   {

      static ::id idEn("en");
      static ::id idStd("_std");





      m_plocale               = NULL;

      m_pschema               = NULL;
      m_pschemaLocale         = NULL;
      m_pschemaSchemaEn       = NULL;
      m_pschemaSchemaStd      = NULL;


      m_schemaptra.remove_all();


      if(m_plocaleschema != NULL)
      {

         if(!m_plocaleschema->m_idLocale.is_empty())
         {

            m_plocale = m_pstr->get_locale(m_plocaleschema->m_idLocale);

            if(m_plocale != NULL)
            {

               if(!m_plocaleschema->m_idSchema.is_empty() && m_plocaleschema->m_idSchema != m_plocaleschema->m_idLocale)
               {
                  m_pschema = m_plocale->get_schema(m_plocaleschema->m_idSchema);
               }
               m_pschemaLocale = m_plocale->get_schema(m_plocaleschema->m_idSchema);
            }
         }

         if(!m_plocaleschema->m_idSchema.is_empty())
         {

            str_locale * plocale = m_pstr->get_locale(m_plocaleschema->m_idSchema);

            if(plocale != NULL)
            {

               m_pschemaSchemaEn = plocale->get_schema(idEn);

               m_pschemaSchemaStd = plocale->get_schema(idStd);

            }

         }

         strid_array stridaFailedLocale(false);

         for(int32_t i = 0; i < m_plocaleschema->m_idaLocale.get_count(); i++)
         {

            ::id & idLocale = m_plocaleschema->m_idaLocale[i];


            if(stridaFailedLocale.contains(idLocale))
               continue;

            str_locale * plocale = m_pstr->get_locale(idLocale);

            if(plocale == NULL)
            {
               stridaFailedLocale.add(idLocale);
               continue;
            }

            ::id & idSchema = m_plocaleschema->m_idaSchema[i];


            str_schema * pschema = plocale->get_schema(idSchema);

            if(pschema != NULL)
            {

               m_schemaptra.add(pschema);

            }

            if(idLocale != idSchema)
            {

               str_schema * pschema = plocale->get_schema(idLocale);

               if(pschema != NULL)
               {

                  m_schemaptra.add(pschema);

               }

            }

            if(__id(std) != idSchema)
            {

               str_schema * pschema = plocale->get_schema(__id(std));

               if(pschema != NULL)
               {

                  m_schemaptra.add(pschema);

               }

            }

         }

      }

   }

   str::str(sp(::axis::application) papp) :
      element(papp)
   {

      InitHashTable(64);

      operator[]("en")["en"]     =  *(m_pschemaEn    =  canew(str_schema));
      operator[]("_std")["_std"] =  *(m_pschemaStd   =  canew(str_schema));


   }

   bool str::initialize()
   {
#ifdef METROWIN
      return true;
#endif
      string strMain = ::dir_path(System.dir().element(), "app\\appmatter\\main");
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
      for(int32_t iLang = 0; iLang < straLang.get_count(); iLang++)
      {
         string strLang = straLang[iLang];
         if(strLang.CompareNoCase(".svn") == 0)
            continue;
         stringa straStylePath;
         stringa straStyle;
         Application.dir().ls_dir(straLangPath[iLang], &straStylePath, &straStyle);
         for(int32_t iStyle = 0; iStyle < straStyle.get_count(); iStyle++)
         {
            string idStyle = straStyle[iStyle];
            if(idStyle.CompareNoCase(".svn") == 0)
               continue;
            stringa straPath;
            Application.dir().rls(
               ::dir_path(straStylePath[iStyle], "uistr"),
               &straPath);
            for(int32_t iPath = 0; iPath < straPath.get_count(); iPath++)
            {
               string strPath = straPath[iPath];
               if(::str::ends_ci(strPath, "\\.svn"))
                  continue;
               if(::str::find_ci("\\.svn\\", strPath) >= 0)
                  continue;
               if(Application.dir().is(strPath))
                  continue;
               load_uistr_file(strLang, idStyle, strPath);
            }
         }
      }

      return true;

   }


   void str::set(const ::id & id, const ::id & idLocale, const ::id & idSchema, const char * psz)
   {


      (*this)[idLocale][idSchema][id] = psz;


   }



   string str::get(str_context * pcontext, const ::id & id)
   {

      static ::id idEn("en");
      static ::id idStd("_std");

      string str;
      if(pcontext != NULL)
      {

         pcontext->defer_ok(this);

         if(pcontext->m_pschema != NULL)
         {

            str = (*pcontext->m_pschema)[id];
            if(str.has_char())
               return str;

         }

         if(pcontext->m_pschemaLocale != NULL)
         {
            str = (*pcontext->m_pschemaLocale)[id];
            if(str.has_char())
               return str;
         }

         for(int32_t i = 0; i < pcontext->m_schemaptra.get_count(); i++)
         {

            str = (*pcontext->m_schemaptra[i])[id];
            if(str.has_char())
               return str;

         }

      }
      if(pcontext != NULL && pcontext->m_pschemaSchemaEn != NULL)
      {
         str = (*pcontext->m_pschemaSchemaEn)[id];// lang=pszStyle style=en
         if(str.has_char())
            return str;
      }
      str = (*m_pschemaEn)[id]; // lang=en style=en
      if(str.has_char())
         return str;
      if(pcontext != NULL && pcontext->m_pschemaSchemaStd != NULL)
      {
         str = (*pcontext->m_pschemaSchemaStd)[id];// lang=pszStyle style=en
         if(str.has_char())
            return str;
      }
      str = (*m_pschemaStd)[id]; // lang=_std style=_std
      return str;

   }

   string str::get(str_context * pcontext, const ::id & id, const ::id & idLocale, const ::id & idSchema)
   {

      if(!idLocale.is_empty())
      {
         string str;
         str_locale * plocale = get_locale(idLocale);
         if(plocale != NULL)
         {

            if(!idSchema.is_empty() && idSchema != idLocale)
            {
               str_schema * pschema = plocale->get_schema(idSchema);
               if(pschema != NULL)
               {
                  str = (*pschema)[id];
                  if(str.has_char())
                     return str;
               }
            }

            str_schema * pschema = plocale->get_schema(idLocale);
            if(pschema != NULL)
            {
               str = (*pschema)[id];
               if(str.has_char())
                  return str;
            }
         }
      }
      return get(pcontext, id);
   }

   void str::get(stringa & stra, str_context * pcontext, const ::id & id)
   {

      _get(stra, pcontext, id);

      ::id id2;

      index i = 0;

      stringa stra2;

      do
      {

         stra2.remove_all();

         id2 = *id.m_pstr + "[" + ::str::from(i) + "]";

         _get(stra2, pcontext, id2);

         stra.add(stra2);

         i++;

      } while (stra2.get_count() > 0);

      
   }


   void str::_get(stringa & stra, str_context * pcontext, const ::id & id)
   {

      static ::id idEn("en");
      static ::id idStd("_std");

      string str;
      if(pcontext != NULL)
      {

         pcontext->defer_ok(this);

         if(pcontext->m_pschema != NULL)
         {

            str = (*pcontext->m_pschema)[id];
            if(str.has_char())
               stra.add(str);

         }

         if(pcontext->m_pschemaLocale != NULL)
         {
            str = (*pcontext->m_pschemaLocale)[id];
            if(str.has_char())
               stra.add(str);
         }

         for(int32_t i = 0; i < pcontext->m_schemaptra.get_count(); i++)
         {

            str = (*pcontext->m_schemaptra[i])[id];
            if(str.has_char())
               stra.add(str);

         }

      }

      if(pcontext != NULL && pcontext->m_pschemaSchemaEn != NULL)
      {

         str = (*pcontext->m_pschemaSchemaEn)[id];// lang=pszStyle style=en
         if(str.has_char())
            stra.add(str);

      }

      str = (*m_pschemaEn)[id]; // lang=en style=en
      if(str.has_char())
         stra.add(str);

      if(pcontext != NULL && pcontext->m_pschemaSchemaStd != NULL)
      {

         str = (*pcontext->m_pschemaSchemaStd)[id];// lang=pszStyle style=en
         if(str.has_char())
            stra.add(str);

      }

      str = (*m_pschemaStd)[id]; // lang=_std style=_std
      if(str.has_char())
         stra.add(str);

   }

   bool str::load_uistr_file(const ::id & pszLang, const ::id & pszStyle, const char * pszFile)
   {
      stringa straLines;
      stringa straSep;
      straSep.add("\r\n");
      straSep.add("\r");
      straSep.add("\n");
      straSep.add("\n\r");
      straLines.add_smallest_tokens(Application.file_as_string(pszFile), straSep, false);

      string str;
      string strLine;
      int32_t i = 0;
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
            string strRoot = ::str::consume_quoted_value(psz);
            while(isspace(*psz))
               psz++;
            if(*psz != '=')
               continue;
            psz++;
            while(isspace(*psz))
               psz++;
            string strBody = ::str::consume_quoted_value(psz);
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

   bool str::matches(str_context * pcontext, const ::id & id, const char * psz)
   {

      static ::id idEn("en");
      static ::id idStd("_std");

      string str;
      if(pcontext != NULL)
      {

         pcontext->defer_ok(this);

         if(pcontext->m_pschema != NULL)
         {

            str = (*pcontext->m_pschema)[id];
            if(!str.CompareNoCase(psz))
               return true;

         }

         if(pcontext->m_pschemaLocale != NULL)
         {
            str = (*pcontext->m_pschemaLocale)[id];
            if(!str.CompareNoCase(psz))
               return true;
         }

         for(int32_t i = 0; i < pcontext->m_schemaptra.get_count(); i++)
         {

            str = (*pcontext->m_schemaptra[i])[id];
            if(!str.CompareNoCase(psz))
               return true;

         }

      }

      if(pcontext != NULL && pcontext->m_pschemaSchemaEn != NULL)
      {

         str = (*pcontext->m_pschemaSchemaEn)[id];// lang=pszStyle style=en
         if(!str.CompareNoCase(psz))
            return true;

      }

      str = (*m_pschemaEn)[id]; // lang=en style=en
      if(!str.CompareNoCase(psz))
         return true;

      if(pcontext != NULL && pcontext->m_pschemaSchemaStd != NULL)
      {

         str = (*pcontext->m_pschemaSchemaStd)[id];// lang=pszStyle style=en
         if(!str.CompareNoCase(psz))
            return true;

      }



      return false;


   }

   bool str::begins(str_context * pcontext, const char * pszTopic, const ::id & id)
   {

      static ::id idEn("en");
      static ::id idStd("_std");

      string str;
      if(pcontext != NULL)
      {

         pcontext->defer_ok(this);

         if(pcontext->m_pschema != NULL)
         {

            str = (*pcontext->m_pschema)[id];
            if(str.has_char() && ::str::begins_ci(pszTopic, str))
               return true;

         }

         if(pcontext->m_pschemaLocale != NULL)
         {
            str = (*pcontext->m_pschemaLocale)[id];
            if(str.has_char() && ::str::begins_ci(pszTopic, str))
               return true;
         }

         for(int32_t i = 0; i < pcontext->m_schemaptra.get_count(); i++)
         {

            str = (*pcontext->m_schemaptra[i])[id];
            if(str.has_char() && ::str::begins_ci(pszTopic, str))
               return true;

         }

      }

      if(pcontext != NULL && pcontext->m_pschemaSchemaEn != NULL)
      {

         str = (*pcontext->m_pschemaSchemaEn)[id];// lang=pszStyle style=en
         if(str.has_char() && ::str::begins_ci(pszTopic, str))
            return true;

      }

      str = (*m_pschemaEn)[id]; // lang=en style=en
      if(str.has_char() && ::str::begins_ci(pszTopic, str))
         return true;

      if(pcontext != NULL && pcontext->m_pschemaSchemaStd != NULL)
      {

         str = (*pcontext->m_pschemaSchemaStd)[id];// lang=pszStyle style=en
         if(str.has_char() && ::str::begins_ci(pszTopic, str))
            return true;

      }



      return false;


   }

   bool str::begins_eat(str_context * pcontext, string & strTopic, const ::id & id)
   {

      static ::id idEn("en");
      static ::id idStd("_std");

      string str;
      if(pcontext != NULL)
      {

         pcontext->defer_ok(this);

         if(pcontext->m_pschema != NULL)
         {

            str = (*pcontext->m_pschema)[id];
            if(str.has_char() && ::str::begins_eat_ci(strTopic, str))
               return true;

         }

         if(pcontext->m_pschemaLocale != NULL)
         {
            str = (*pcontext->m_pschemaLocale)[id];
            if(str.has_char() && ::str::begins_eat_ci(strTopic, str))
               return true;
         }

         for(int32_t i = 0; i < pcontext->m_schemaptra.get_count(); i++)
         {

            str = (*pcontext->m_schemaptra[i])[id];
            if(str.has_char() && ::str::begins_eat_ci(strTopic, str))
               return true;

         }

      }

      if(pcontext != NULL && pcontext->m_pschemaSchemaEn != NULL)
      {

         str = (*pcontext->m_pschemaSchemaEn)[id];// lang=pszStyle style=en
            if(str.has_char() && ::str::begins_eat_ci(strTopic, str))
               return true;

      }

      str = (*m_pschemaEn)[id]; // lang=en style=en
      if(str.has_char() && ::str::begins_eat_ci(strTopic, str))
         return true;

      if(pcontext != NULL && pcontext->m_pschemaSchemaStd != NULL)
      {

         str = (*pcontext->m_pschemaSchemaStd)[id];// lang=pszStyle style=en
         if(str.has_char() && ::str::begins_eat_ci(strTopic, str))
            return true;

      }


      return false;


   }




} // namespace user


