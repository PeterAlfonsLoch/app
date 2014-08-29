#pragma once


namespace database
{


   class server;
   class update_hint;


   class CLASS_DECL_AXIS change_event :
      public signal_details
   {
   public:


      server *          m_pserver;
      key               m_key;
      update_hint *     m_puh;
      bool              m_bOk;
      var *             m_pvar;

      change_event();
      change_event(var & var);


      bool data_get(::file::serializable & obj);


   };


} // namespace event


