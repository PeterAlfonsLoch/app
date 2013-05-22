#include "framework.h"


namespace xml
{


   xml::xml(::ca::application * papp) :
      ca(papp),
      ::ca::section(papp)
   {
      
      m_poptionDefault     = ::null();
      m_pparseinfoDefault  = ::null();


   }


   xml::~xml()
   {

   }


   bool xml::initialize1()
   {

      if(Application.is_system())
      {
         System.factory().cloneable_large < ::xml::edit_item > ();
      }

      if(!::ca::section::initialize1())
         return false;

      m_poptionDefault     = new disp_option(get_app());
      m_pparseinfoDefault  = new parse_info(get_app());

      m_entities.add_entity('&'    , "&amp;" );
      m_entities.add_entity('\"'   , "&quot;");
      m_entities.add_entity('\''   , "&apos;");
      m_entities.add_entity('<'    , "&lt;");
      m_entities.add_entity('>'    , "&gt;");

      return true;

   }


   bool xml::initialize()
   {

      if(!::ca::section::initialize())
         return false;

      return true;

   }


   string xml::special_chars(const char * psz)
   {
      
      string str(psz);

      str.replace("&"      , "&amp;");
      str.replace("\""     , "&quot;"); // quando ENT_NOQUOTES n縊 est・definida.
      str.replace("'"      , "&#039;"); // apenas quando ENT_QUOTES est・definida.
      str.replace("<"      , "&lt;");
      str.replace(">"      , "&gt;");

      return str;

   }


} //namespace xml



