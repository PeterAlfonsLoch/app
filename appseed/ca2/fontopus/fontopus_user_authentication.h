#pragma once


namespace fontopus
{

   
   class CLASS_DECL_ca user_authentication :
      public ::radix::object
   {
   public:


      string_to_string_map                   m_mapFontopus;
      string_to_string_map                   m_mapServer;


   };


} // namespace fontopus

