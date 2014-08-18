#include "framework.h"


namespace simple_ui
{


   style::style(sp(::axis::application) papp) :
      element(papp)
   {

      m_eschema = schema_darker;

   }

   style::~style()
   {

   }


   string style::calc_locale()
   {

#if defined(WINDOWS)
      string strLocale;
      LANGID langid = ::GetUserDefaultLangID();
#define SPR_DEUTSCH LANG_GERMAN
      if (langid == LANG_SWEDISH)
      {
         strLocale = "se";
      }
      else if (langid == MAKELANGID(LANG_PORTUGUESE, SUBLANG_PORTUGUESE_BRAZILIAN))
      {
         strLocale = "pt-br";
      }
      else if (PRIMARYLANGID(langid) == SPR_DEUTSCH)
      {
         strLocale = "de";
      }
      else if (PRIMARYLANGID(langid) == LANG_ENGLISH)
      {
         strLocale = "en";
      }
      else if (PRIMARYLANGID(langid) == LANG_JAPANESE)
      {
         strLocale = "jp";
      }
      else if (PRIMARYLANGID(langid) == LANG_POLISH)
      {
         strLocale = "pl";
      }
      else
      {
         strLocale = "se";
      }
      return strLocale;
#else

      return "se";
#endif

   }

   string style::calc_schema()
   {

      return calc_locale();

   }


   string style::defer_get_plugin()
   {

      return "";

   }


   string style::defer_get(const char * pszUrl)
   {

      string str;

      int32_t iAttempt = 0;

   restart:

      defer_get_plugin();

      try
      {

         url_query_get_param_dup(m_strLocale, "locale", str);

      }
      catch (...)
      {
      }

      try
      {

         url_query_get_param_dup(m_strSchema, "schema", str);

      }
      catch (...)
      {
      }

      try
      {

         url_query_get_param_dup(m_strRuri, "ruri", str);

      }
      catch (...)
      {

      }

      if (m_strLocale.is_empty())
      {
         iAttempt++;

         if (iAttempt > 3)
            goto default_case;

         goto restart;

      }

   default_case:

      xxdebug_box("plugin::defer_get not logged", "defer get", 0);

      if (str_begins_ci_dup(m_strSchema, "darker;") || str_ends_ci_dup(m_strSchema, ";darker") || stristr_dup(m_strSchema, ";darker;")
         || str_begins_ci_dup(m_strSchema, "darker%3B") || str_ends_ci_dup(m_strSchema, "%3Bdarker") || stristr_dup(m_strSchema, "%3Bdarker%3B"))
      {

         m_eschema = schema_darker;

      }
      else
      {

         m_eschema = schema_normal;

      }

      if (m_strLocale.is_empty())
      {

         m_strLocale = calc_locale();

      }

      if (m_strSchema.is_empty())
      {

         m_strSchema = calc_schema();

      }

      return Application.http().get_locale_schema(pszUrl,m_strLocale,m_strSchema);

   }


} // namespace simple_ui


