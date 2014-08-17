#pragma once


#undef new



namespace message
{


   class CLASS_DECL_BASE base:
      public signal_details
   {
   public:


      ::user::interaction *      m_pwnd;
      UINT                       m_uiMessage;
      WPARAM                     m_wparam;
      lparam                     m_lparam;
      bool                       m_bConditional;
      bool                       m_bReflect;

      base(sp(::base::application) papp,class ::signal * psignal = NULL);
      base(sp(::base::application) papp,sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);



      virtual void set_lresult(LRESULT lresult);
      virtual LRESULT & get_lresult();
      virtual void set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
      virtual void set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam);
   protected:
      LRESULT * m_plresult;
      LRESULT  m_lresult;
   };


} // namespace message


#define new BASE_NEW