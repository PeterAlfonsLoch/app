#pragma once


namespace database
{


   class CLASS_DECL_ca application :
      virtual public ca4::application,
      virtual public ::database::client
   {
   public:


      application();
      virtual ~application();

      
      virtual bool initialize();

      
      virtual ::database::server * get_data_server();


      virtual int32_t exit_instance();


   };


} // namespace database



