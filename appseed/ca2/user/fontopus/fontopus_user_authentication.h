#pragma once


namespace fontopus
{

   
   class CLASS_DECL_ca2 user_authentication :
      public ::ca2::object
   {
   public:


      string_to_string_map                   m_mapFontopus;
      string_to_string_map                   m_mapServer;


   };


} // namespace fontopus

