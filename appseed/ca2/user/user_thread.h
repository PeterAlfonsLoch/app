#pragma once


namespace user
{


   class CLASS_DECL_ca2 thread :
      virtual public ::ca2::thread
   {
   public:


      user::interaction_ptr_array *                  m_puiptra;
      ::user::interaction::timer_array *  m_ptimera;


      thread(sp(::ca2::application) papp);
      virtual ~thread();


   };


} // namespace user



