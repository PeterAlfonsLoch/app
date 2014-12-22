#pragma once


namespace aura
{


   class CLASS_DECL_AURA interaction :
      virtual public command_target,
      virtual public ::aura::draw_interface
   {
   public:

      
      void *         m_pvoidUserInteraction; // ::user::interaction * 


      interaction();
      virtual ~interaction();


   };


} // namespace aura



