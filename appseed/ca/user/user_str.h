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
      
      bool matches(const id & pszRoot, const id & pszExtra, const char * psz);
      bool begins(const id & pszRoot, const id & pszExtra, const char * psz);
      bool begins_eat(string & str, const id & pszRoot, const id & pszExtra);
      void get(stringa & stra, const id & pszRoot, const id & pszExtra);
      string get(const id & pszRoot, const id & pszExtra);


   };

   class CLASS_DECL_ca str_root
   {
   public:
      id          m_idLang;
      string      m_str;
   };

   class CLASS_DECL_ca str_style : 
      public ::collection::map < id, const id &, str_root, const str_root & >
   {
   public:
      id m_idStyle;
      id m_strLangDefault;
   };


   class CLASS_DECL_ca str_lang : 
      public ::collection::map < id, const id &, str_style, const str_style & >
   {
   public:
      id m_idLang;
      id m_strStyleDefault;
   };

   class CLASS_DECL_ca str_extra : 
      public ::collection::map < id, const id &, str_lang, const str_lang & >
   {
   public:
      id m_idExtra;
   };

   class CLASS_DECL_ca str : 
      public ::collection::map < id, const id &, str_extra, const str_extra & >
   {
   public:
      str(::ca::application * papp);

      bool initialize();


      void set(const id & pszRoot, const id & pszLang, const id & pszStyle, const id & pszExtra, const char * psz);
      string get(str_context * pcontext, const id & pszRoot, const id & pszLang, const id & pszStyle, const id & pszExtra);
      void get(stringa & stra, str_context * pcontext, const id & pszRoot, const id & pszLang, const id & pszStyle, const id & pszExtra);

      bool load(const char * pszBaseDir);
      bool load_uistr_file(const id & pszLang, const id & pszStyle, const char * pszFile);

      string body(const char * psz);

      bool matches(str_context * pcontext, const id & pszRoot, const id & pszExtra, const char * psz);
      bool begins(str_context * pcontext, const char * psz, const id & pszRoot, const id & pszExtra);
      bool begins_eat(str_context * pcontext, string & str, const id & pszRoot, const id & pszExtra);
      void get(stringa & stra, str_context * pcontext, const id & pszRoot, const id & pszExtra);
      string get(str_context * pcontext, const id & pszRoot, const id & pszExtra);
   
   
   };


} // namespace user


