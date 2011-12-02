#pragma once


namespace user
{


   class CLASS_DECL_ca thread :
      virtual public ::radix::thread
   {
   public:


      user::LPWndArray *                  m_puiptra;
      ::user::interaction::timer_array *  m_ptimera;


      thread(::ax::application * papp);
      virtual ~thread();


   };


} // namespace user



