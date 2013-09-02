#pragma once


namespace xml
{


   class CLASS_DECL_c departament :
      public ::departament
   {
   public:

      
      entities       m_entities;
      disp_option *  m_poptionDefault;
      parse_info *   m_pparseinfoDefault;


      departament(::application * papp);
      virtual ~departament();

      virtual bool initialize1();

      virtual bool initialize();



      string special_chars(const char * psz);


   };


} // namespace ca2


