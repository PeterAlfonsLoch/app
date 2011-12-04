#pragma once


namespace ca2
{


   namespace fontopus
   {


      class CLASS_DECL_ca2 application :
         virtual public ::cube2::application
      {
      public:


         application(void);
         virtual ~application(void);


         using ::ca::thread::construct;
         using ::ca::application::construct;
         virtual void construct();


         virtual ::fontopus::user * login();
         virtual bool get_auth(const char * psz, string & strUsername, string & strPassword);


         virtual bool initialize_instance();
         virtual int exit_instance();

         virtual bool bergedge_start();


      };


   } // namespace fontopus


} // namespace ca2



