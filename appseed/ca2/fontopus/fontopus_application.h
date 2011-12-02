#pragma once


namespace ca2
{

namespace fontopus
{


   class CLASS_DECL_ca application :
      virtual public ::cube2::application
   {
   public:


      
      application(void);
      virtual ~application(void);

      using ::ax::thread::construct;
      using ::ax::application::construct;

      virtual void construct();

      virtual user * create_user(::fontopus::user * puser);
      virtual user * allocate_user();
      virtual user * create_current_user();
      virtual user * login();

      virtual void logout();

      virtual user * get_user();
      virtual void set_user(const char * psz);
      virtual void set_user(::fontopus::user * psz);


      virtual bool get_auth(const char * psz, string & strUsername, string & strPassword);

      virtual bool initialize_instance();
      virtual int exit_instance();

      virtual bool bergedge_start();




   };


} // namespace fontopus


} // namespace ca2