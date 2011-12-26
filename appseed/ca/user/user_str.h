#pragma once


#include "ca/primitive/id_space.h"


namespace user
{

   class str;

   class CLASS_DECL_ca str_context
   {
   public:
      raw_array < id > m_straParamLocale;
      raw_array < id > m_straParamStyle;

      str * m_pstr;

      str_context();

      inline raw_array < id > & param_locale_ex()
      {
         return m_straParamLocale;
      }

      inline raw_array < id > & param_style_ex()
      {
         return m_straParamStyle;
      }
      
      bool matches(id pszRoot, id pszExtra, const char * psz);
      bool begins(id pszRoot, id pszExtra, const char * psz);
      bool begins_eat(string & str, id pszRoot, id pszExtra);
      void get(stringa & stra, id pszRoot, id pszExtra);
      string get(id pszRoot, id pszExtra);
   };

   class CLASS_DECL_ca str_root
   {
   public:
      id          m_idLang;
      string      m_str;
   };

   class CLASS_DECL_ca str_style : 
      public ::collection::map < id, id, str_root, str_root >
   {
   public:
      id m_idStyle;
      id m_strLangDefault;
   };


   class CLASS_DECL_ca str_lang : 
      public ::collection::map < id, id, str_style, str_style >
   {
   public:
      id m_idLang;
      id m_strStyleDefault;
   };

   class CLASS_DECL_ca str_extra : 
      public ::collection::map < id, id, str_lang, str_lang >
   {
   public:
      id m_idExtra;
   };

   class CLASS_DECL_ca str : 
      public ::collection::map < id, id, str_extra, str_extra >
   {
   public:
      str(::ca::application * papp);

      bool initialize();


      void set(id pszRoot, id pszLang, id pszStyle, id pszExtra, const char * psz);
      string get(str_context * pcontext, id pszRoot, id pszLang, id pszStyle, id pszExtra);
      void get(stringa & stra, str_context * pcontext, id pszRoot, id pszLang, id pszStyle, id pszExtra);

      bool load(const char * pszBaseDir);
      bool load_uistr_file(id pszLang, id pszStyle, const char * pszFile);

      string body(const char * psz);

      bool matches(str_context * pcontext, id pszRoot, id pszExtra, const char * psz);
      bool begins(str_context * pcontext, const char * psz, id pszRoot, id pszExtra);
      bool begins_eat(str_context * pcontext, string & str, id pszRoot, id pszExtra);
      void get(stringa & stra, str_context * pcontext, id pszRoot, id pszExtra);
      string get(str_context * pcontext, id pszRoot, id pszExtra);
   };

} // namespace user