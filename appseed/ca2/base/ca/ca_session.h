#pragma once


namespace ca
{


   class CLASS_DECL_ca2 session :
      virtual public ::ca::application
   {
   public:


      session();
      virtual ~session();


      virtual bool is_remote_session();


   };


} // namespace ca


