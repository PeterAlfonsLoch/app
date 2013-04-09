#pragma once


namespace userpresence
{


   class CLASS_DECL_ca userpresence :
      virtual public ::ca::section,
      virtual public ::ca::message_window_simple_callback
   {
   public:


      bool                    m_bUserPresenceFeatureRequired;


      userpresence(sp(::ca::application) papp);
      virtual ~userpresence();


      virtual bool initialize();
      virtual bool finalize();


      virtual bool defer_initialize_user_presence();
      virtual bool defer_finalize_user_presence();


      virtual void message_window_message_handler(::ca::signal_object * pobj);

      virtual bool is_initialized();


   };


} // namespace userpresence





