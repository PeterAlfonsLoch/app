#pragma once


namespace userpresence
{


   class CLASS_DECL_ca userpresence :
      virtual public ::userpresence::presence_central_container
   {
   public:

   
      userpresence();
      virtual ~userpresence();

      
      virtual bool initialize();
      virtual bool finalize();


      virtual void defer_initialize_user_presence();
      virtual void defer_finalize_user_presence();


   };


} // namespace userpresence


