#pragma once


namespace fontopus
{


   class CLASS_DECL_ca application :
      virtual public ::fs::application
   {
   public:


      bool           m_bIsCreatingUser;
      user *         m_puser;

      
      application();
      virtual ~application();

      using ::ca::thread::construct;
      using ::ca::application::construct;

      virtual void construct();

      virtual user * create_user(::fontopus::user * puser);
      virtual user * allocate_user();
      virtual user * create_current_user();
      virtual user * login(gen::property_set & set);

      virtual void logout();

      virtual user * get_user();
      virtual void set_user(const char * psz);
      virtual void set_user(::fontopus::user * psz);


      virtual bool get_auth(const char * psz, string & strUsername, string & strPassword);

      virtual bool initialize_instance();
      virtual int exit_instance();

      virtual bool bergedge_start();


      virtual bool check_license(const char * pszId, bool bInteractive);

      virtual void on_user_login(::fontopus::user * puser);

   };


} // namespace fontopus


