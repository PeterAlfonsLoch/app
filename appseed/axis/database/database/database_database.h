#pragma once


namespace database
{


   class CLASS_DECL_AXIS database :
      virtual public ::database::client
   {
   public:


      database();
      virtual ~database();

      
      virtual bool initialize();

      
      virtual ::database::server * get_data_server();


      virtual int32_t exit_instance();


   };


} // namespace database



