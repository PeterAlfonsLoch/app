#pragma once


namespace xml
{


   class CLASS_DECL_ca2 xml :
      public ::ca2::section
   {
   public:

      
      entities       m_entities;
      disp_option *  m_poptionDefault;
      parse_info *   m_pparseinfoDefault;


      xml(::ca2::application * papp);
      virtual ~xml();

      virtual bool initialize1();

      virtual bool initialize();



      string special_chars(const char * psz);


   };


} // namespace ca2


