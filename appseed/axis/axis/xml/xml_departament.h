#pragma once


namespace xml
{


   class CLASS_DECL_AXIS departament :
      public ::axis::departament
   {
   public:

      
      entities       m_entities;
      disp_option *  m_poptionDefault;
      parse_info *   m_pparseinfoDefault;


      departament(::axis::application * papp);
      virtual ~departament();

      virtual bool initialize1();

      virtual bool initialize();



      string special_chars(const char * psz);


   };


} // namespace bas


