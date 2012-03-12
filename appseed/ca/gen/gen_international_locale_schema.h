#pragma once


namespace gen
{


   namespace international
   {


      class CLASS_DECL_ca locale_schema : 
         virtual public ::radix::object
      {
      public:

         // most simple use:
         // 1. allocate locale_schema.
         // 2. add locale variants in order of importance, most acceptable first
         // 3. finalize locale_schema
         // m_straLocale and m_straStyle will have the locale/styles

         bool                       m_bSchemaOnly;
         bool                       m_bAddAlternateStyle;

         id                         m_idLocale;
         id                         m_idSchema;

         comparable_array < id >    m_idaLocale;
         comparable_array < id >    m_idaSchema;


         locale_schema(::ca::application * papp);
         locale_schema(const locale_schema & ls);
         virtual ~locale_schema();


         virtual bool add_locale_variant(id idLocale, id Style);
         virtual bool finalize(bool bRtlLayout);
         virtual bool finalize();


         virtual bool defer_add_locale(id idLocale, id idStyle);
         virtual bool _add_locale_variant(id pszLocale, id idStyle);
         virtual bool process_final_locale_schema(bool bRTLLayout);
         virtual bool process_final_locale_schema();


         locale_schema & operator = (const locale_schema & ls);


      };


   }  // namespace international


} // namespace gen


