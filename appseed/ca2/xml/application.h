#pragma once


namespace xml
{


   class CLASS_DECL_ca application :
      virtual public ex2::application
   {
   public:

      entities       m_entities;
      disp_option *  m_poptionDefault;
      parse_info *   m_pparseinfoDefault;

      application();
      virtual ~application();

      virtual bool initialize1();

      virtual bool initialize();
      
   };

   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

   inline disp_option::disp_option(::ca::application * papp)
   {
      newline = true; 
      reference_value = true; 
      m_pentities = &::xml::app_cast(papp).m_entities; 
      tab_base = 0; 
      value_quotation_mark = '"'; 
   }

} // namespace xml