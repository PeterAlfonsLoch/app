#pragma once


namespace webserver
{


   class CLASS_DECL_ca ui_redir_lang
   {
   public:
      string m_strLang;
      string m_strTarget;
   };

   class CLASS_DECL_ca ui_redir_style : 
      public ::collection::map < string, const char *, ui_redir_lang, ui_redir_lang >
   {
   public:
      string m_strStyle;
      string m_strLangDefault;
   };


   class CLASS_DECL_ca ui_redir_root : 
      public ::collection::map < string, const char *, ui_redir_style, ui_redir_style >
   {
   public:
      string m_strRoot;
      string m_strLangDefault;
   };

   class CLASS_DECL_ca ui_redir : 
      public ::collection::map < string, const char *, ui_redir_root, ui_redir_root >
   {
   public:
      ui_redir(::ca::application * papp);
      void load_xml(const char * pszFileName);
      void add(const char * pszRoot, const char * pszLang, const char * pszStyle, const char * pszTarget);
      string solve(const char * pszRoot, const char * pszLang, const char * pszStyle, const char * pszExUri);
   };


} // namespace webserver


