#pragma once


#include "database/database_key.h"


namespace database
{


   class server;
   class update_hint;


   class CLASS_DECL_ca2 change_event :
      public ::ca2::signal_object
   {
   public:


      server *          m_pserver;
      key               m_key;
      update_hint *     m_puh;
      bool              m_bOk;
      var *             m_pvar;

      change_event();
      change_event(var & var);


      bool data_get(::ca2::byte_serializable & obj);


   };


} // namespace event


