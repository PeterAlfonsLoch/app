#pragma once


namespace core
{


   class CLASS_DECL_CORE session :
      virtual public ::base::session,
      virtual public ::application
   {
   public:


      session();
      virtual ~session();


      virtual bool initialize1();


      virtual bool is_remote_session();
      virtual bool is_session();


   };


} // namespace core


