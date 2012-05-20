#pragma once

namespace simpledb
{

   class CLASS_DECL_ca manager :
      virtual public ::radix::thread,
      virtual public ::ca::message_window_simple_callback
   {
   public:



      DWORD                         m_dwBuildTimeWindow;
      DWORD                         m_dwBuildTimeRandomWindow;

      string_to_string_map          m_strmapFunUserKey;

      string                        m_strPersistentError;

      critical_section              m_csPersistentStr;
      critical_section              m_csUiRedir;
      mutex                         m_mutexTagId;
      string_to_string_map          m_tagid;
      string_to_string_map          m_usersecuretagid;
      mutex                         m_mutexTagName;
      string_to_string_map          m_tagname;

      int64_t                       m_iDatabaseWaitTimeOut;

      mutex                         m_mutexSession;
      ::collection::string_map < session * > m_mapSession;


      manager(::ca::application * papp);
      ~manager();

      bool initialize_instance();


      session * & get_session(const char * pszId);


      using ::radix::thread::handle;
      bool handle(socket * psocket);
      bool get_output_internal(const char * lpcszGet, primitive::memory & memeory);

      virtual void message_window_message_handler(gen::signal_object * pobj);

   };


} // namespace simpledb
