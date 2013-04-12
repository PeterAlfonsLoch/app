#pragma once


namespace fontopus
{


   class CLASS_DECL_ca fontopus :
      virtual public ::ca::section
   {
   public:


      ::ca::thread * m_pthreadCreatingUser;
      user *         m_puser;

      
      fontopus();
      virtual ~fontopus();


      virtual user * create_user(::fontopus::user * puser);
      virtual user * create_system_user(const string & strSystemUserName);
      virtual user * allocate_user();
      virtual user * create_current_user();
      virtual user * login(::ca::property_set & set);

      virtual void logout();

      virtual user * get_user();
      virtual void set_user(const char * psz);
      virtual void set_user(::fontopus::user * psz);


      virtual bool get_auth(const char * psz, string & strUsername, string & strPassword);

      virtual bool initialize_instance();
      virtual int32_t exit_instance();

      virtual bool check_license(const char * pszId, bool bInteractive);

      virtual void on_user_login(::fontopus::user * puser);

   };


} // namespace fontopus


