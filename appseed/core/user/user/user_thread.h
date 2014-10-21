#pragma once


namespace user
{


   class CLASS_DECL_CORE thread :
      virtual public thread
   {
   public:


      user::interaction_spa *                  m_puiptra;
      ::user::interaction::timer_array *  m_ptimera;


      thread(sp(::aura::application) papp);
      virtual ~thread();


   };


} // namespace user



