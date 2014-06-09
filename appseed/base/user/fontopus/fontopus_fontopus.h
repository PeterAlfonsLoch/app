#pragma once


namespace fontopus
{


   class CLASS_DECL_BASE fontopus :
      virtual public ::base::departament
   {
   public:


      class create_user_thread *                   m_pthreadCreatingUser;
      user *                                       m_puser;
      string_to_string                             m_mapFontopusServer;
      string                                       m_strFirstFontopusServer;
      authentication_map                           m_authmap;
      string_map < sp(::sockets::http_session) >   m_mapFontopusSession;



      fontopus(::base::application * papp);
      virtual ~fontopus();


      virtual user * create_user(::fontopus::user * puser);
      virtual user * create_system_user(const string & strSystemUserName);
      virtual user * allocate_user();
      virtual user * create_current_user();
      virtual user * login(property_set & set);

      virtual void logout();

      virtual user * get_user();
      virtual void set_user(const char * psz);
      virtual void set_user(::fontopus::user * psz);


      virtual bool get_auth(const char * psz, string & strUsername, string & strPassword);

      virtual bool initialize_instance();
      virtual int32_t exit_instance();

      virtual bool check_license(const char * pszId, bool bInteractive);

      virtual void on_user_login(::fontopus::user * puser);

      virtual void on_request(sp(::create_context) pcreatecontext);


      virtual string get_server(const char * pszSourceUrl, int32_t iRetry = 8);

      virtual string get_fontopus_server(const char * pszRequestingServerOrUrl,int iRetry = 8);

   };



   class CLASS_DECL_BASE create_user_thread:
      virtual public thread
   {
   public:


      manual_reset_event m_evReady;

      create_user_thread(sp(::base::application) papp);
      virtual ~create_user_thread();

      int32_t run();

   };


} // namespace fontopus





