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
      public ::collection::string_map < ui_redir_lang, ui_redir_lang >
   {
   public:
      string m_strSchema;
      string m_strLangDefault;
   };


   class CLASS_DECL_ca ui_redir_root : 
      public ::collection::string_map < ui_redir_style, ui_redir_style >
   {
   public:
      string m_strRoot;
      string m_strLangDefault;
   };

   class CLASS_DECL_ca ui_redir : 
      public ::collection::string_map < ui_redir_root, ui_redir_root >
   {
   public:
      ui_redir(::ca::application * papp);
      void load_xml(const string & pszFileName);
      void add(const string & pszRoot, const string & pszLang, const string & pszStyle, const string & pszTarget);
      string solve(const string & pszRoot, const string & pszLang, const string & pszStyle, const string & pszExUri);
   };


} // namespace webserver


