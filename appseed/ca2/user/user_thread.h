#pragma once


namespace user
{


   class CLASS_DECL_ca2 thread :
      virtual public ::ca::thread
   {
   public:


      user::interaction_ptr_array *                  m_puiptra;
      ::user::interaction::timer_array *  m_ptimera;


      thread(::ca::applicationsp papp);
      virtual ~thread();


   };


} // namespace user



