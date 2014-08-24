#pragma once


namespace userpresence
{


   class CLASS_DECL_BASE userpresence :
      virtual public ::aura::departament,
      virtual public ::aura::message_queue_listener
   {
   public:


      bool                       m_bUserPresenceFeatureRequired;
      ::aura::message_queue_sp  m_spqueue;


      userpresence(sp(::aura::application) papp);
      virtual ~userpresence();


      virtual bool initialize();
      virtual bool finalize();


      virtual bool defer_initialize_user_presence();
      virtual bool defer_finalize_user_presence();


      virtual void message_queue_message_handler(signal_details * pobj);

      virtual bool is_initialized();


   };


} // namespace userpresence





