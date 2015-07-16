#pragma once


namespace userpresence
{


   class CLASS_DECL_AXIS userpresence :
      virtual public ::aura::departament,
      virtual public ::aura::timer_array
   {
   public:


      bool                       m_bUserPresenceFeatureRequired;
      bool                       m_bInit;


      userpresence(::aura::application * papp);
      virtual ~userpresence();


      virtual bool initialize();
      virtual bool finalize();


      virtual bool defer_initialize_user_presence();
      virtual bool defer_finalize_user_presence();


      virtual void message_queue_message_handler(signal_details * pobj);

      virtual bool is_initialized();

      virtual void _001OnTimer(::timer * ptimer);


   };


} // namespace userpresence





