#pragma once


namespace xml
{


   class CLASS_DECL_ca xml :
      public ::ca::section
   {
   public:

      entities       m_entities;
      disp_option *  m_poptionDefault;
      parse_info *   m_pparseinfoDefault;

      xml();
      virtual ~xml();

      virtual bool initialize1();

      virtual bool initialize();



      string special_chars(const char * psz);


   };


} // namespace ca2


