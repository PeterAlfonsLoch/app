#pragma once

namespace simpledb
{

   class CLASS_DECL_CORE manager :
      virtual public thread,
      virtual public message_queue
   {
   public:



      uint32_t                         m_dwBuildTimeWindow;
      uint32_t                         m_dwBuildTimeRandomWindow;

      string_to_string          m_strmapFunUserKey;

      string                        m_strPersistentError;

      critical_section              m_csPersistentStr;
      critical_section              m_csUiRedir;
      mutex                         m_mutexTagId;
      string_to_string          m_tagid;
      string_to_string          m_usersecuretagid;
      mutex                         m_mutexTagName;
      string_to_string          m_tagname;

      int64_t                       m_iDatabaseWaitTimeOut;

      mutex                         m_mutexSession;
      string_map < session * >      m_mapSession;


      manager(sp(::base::application) papp);
      ~manager();

      bool initialize_instance();


      session * & get_session(const char * pszId);


      using thread::handle;
      bool handle(socket * psocket);
      bool get_output_internal(const char * lpcszGet, primitive::memory & memeory);

      virtual void message_queue_message_handler(signal_details * pobj);

   };


} // namespace simpledb
