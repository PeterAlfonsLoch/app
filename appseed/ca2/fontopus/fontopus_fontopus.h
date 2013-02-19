#pragma once


namespace ca2
{


   namespace fontopus
   {


      class CLASS_DECL_ca2 application :
         virtual public ::fontopus::fontopus
      {
      public:


         application();
         virtual ~application();


         using ::cube2::application::construct;
         virtual void construct();


         virtual ::fontopus::user * login(gen::property_set & set);
         virtual bool get_auth(const char * psz, string & strUsername, string & strPassword);


         virtual bool initialize_instance();
         virtual int32_t exit_instance();

         virtual bool bergedge_start();


         virtual bool check_license(const char * pszId, bool bInteractive);

         virtual void on_request(::ca::create_context * pcreatecontext);


      };


   } // namespace fontopus


} // namespace ca2



