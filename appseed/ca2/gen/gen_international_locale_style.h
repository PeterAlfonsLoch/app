#pragma once


namespace gen
{


   namespace international
   {


      class CLASS_DECL_ca locale_style : 
         virtual public ::radix::object
      {
      public:

         // most simple use:
         // 1. allocate locale_style.
         // 2. initialize locale_style
         // 2. add locale variants in order of importance, most acceptable first
         // 3. finalize locale_style
         // m_straLocale and m_straStyle will have the locale/styles



         string   m_strLocale;
         string   m_strStyle;

         stringa  m_straLocale;
         stringa  m_straStyle;

         locale_style(::ca::application * papp);
         virtual ~locale_style();


         virtual bool initialize(const char * pszLocale, const char * pszStyle);
         virtual bool add_locale_variant(const char * pszLocale, const char * pszStyle);
         virtual bool finalize(bool bRtlLayout);
         virtual bool finalize();


         virtual bool defer_add_locale(const char * pszLocale, const char * pszStyle);
         virtual bool _add_locale_variant(const char * pszLocale, const char * pszStyle);
         virtual bool process_final_locale_style(bool bRTLLayout);
         virtual bool process_final_locale_style();


      };


   }  // namespace international


} // namespace gen


