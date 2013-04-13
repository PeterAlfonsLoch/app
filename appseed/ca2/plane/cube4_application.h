#pragma once


namespace planebase
{


   class CLASS_DECL_ca application :
      virtual public ::fontopus::application
   {
   public:


      service_base * m_pservice;


      application();
      virtual ~application();


      virtual bool on_install();
      virtual bool on_uninstall();


      virtual bool is_serviceable();


      virtual int32_t run();


      service_base * get_service();
      virtual service_base * allocate_new_service();
      virtual bool create_new_service();


      virtual bool create_service();
      virtual bool remove_service();

      virtual bool start_service();
      virtual bool stop_service();


      virtual void on_service_request(::ca::create_context * pcreatecontext);


   };


   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }


} // namespace cube4


