#pragma once

namespace user
{

   class str;

   class CLASS_DECL_ca str_context
   {
   public:
      stringa *   m_pstraParamLocale;
      stringa *   m_pstraParamStyle;

      str * m_pstr;

      str_context();

      inline stringa & param_locale_ex()
      {
         return *m_pstraParamLocale;
      }

      inline stringa & param_style_ex()
      {
         return *m_pstraParamStyle;
      }
      
      bool matches(const char * pszRoot, const char * psz);
      bool begins_eat(string & str, const char * pszRoot);
      void get(stringa & stra, const char * pszRoot);
      string get(const char * pszRoot);
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
      string m_strLangDefault;
   };


   class CLASS_DECL_ca str_lang : 
      public ::collection::map < id, id, str_style, str_style >
   {
   public:
      id m_idLang;
      string m_strStyleDefault;
   };

   class CLASS_DECL_ca str : 
      public ::collection::map < id, id, str_lang, str_lang >
   {
   public:
      str(::ca::application * papp);

      bool initialize();


      void set(const char * pszRoot, const char * pszLang, const char * pszStyle, const char * psz);
      string get(str_context * pcontext, const char * pszRoot, const char * pszLang, const char * pszStyle);
      void get(stringa & stra, str_context * pcontext, const char * pszRoot, const char * pszLang, const char * pszStyle);

      bool load(const char * pszBaseDir);
      bool load_uistr_file(const char * pszLang, const char * pszStyle, const char * pszFile);

      string body(const char * psz);

      bool matches(str_context * pcontext, const char * pszRoot, const char * psz);
      bool begins_eat(str_context * pcontext, string & str, const char * pszRoot);
      void get(stringa & stra, str_context * pcontext, const char * pszRoot);
      string get(str_context * pcontext, const char * pszRoot);
   };

} // namespace user