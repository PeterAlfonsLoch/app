#pragma once


#ifdef WINDOWSEX


namespace base
{

   // top level window for receiving system messages broadcasted to top level windows in Windows

   class CLASS_DECL_BASE system_interaction_impl:
      virtual public ::user::interaction
   {
   public:

      system_interaction_impl(::aura::application * papp);
      virtual ~system_interaction_impl();

      void install_message_handling(::message::dispatch * pdispath);

      DECL_GEN_SIGNAL(_001MessageHub);


   };


} // namespace base


#endif


