#pragma once


namespace core
{


   class CLASS_DECL_CORE session :
      virtual public ::application,
      virtual public ::base::session_interface
   {
   public:


      session(sp(::base::application) papp);
      virtual ~session();


      virtual bool initialize1();

      virtual bool initialize();

      virtual int32_t exit_instance();


      virtual bool is_remote_session();
      virtual bool is_session();


   };


} // namespace core


