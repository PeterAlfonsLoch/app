#pragma once


namespace user
{


   class CLASS_DECL_ca2 thread :
      virtual public ::radix::thread
   {
   public:


      user::LPWndArray *                  m_puiptra;
      ::user::interaction::timer_array *  m_ptimera;


      thread(::ca::application * papp);
      virtual ~thread();


   };


} // namespace user



