#pragma once


namespace userpresence
{


   class CLASS_DECL_ca2 userpresence :
      virtual public ::ca2::section,
      virtual public ::ca2::message_window_simple_callback
   {
   public:


      bool                    m_bUserPresenceFeatureRequired;


      userpresence(sp(::application) papp);
      virtual ~userpresence();


      virtual bool initialize();
      virtual bool finalize();


      virtual bool defer_initialize_user_presence();
      virtual bool defer_finalize_user_presence();


      virtual void message_window_message_handler(signal_details * pobj);

      virtual bool is_initialized();


   };


} // namespace userpresence





