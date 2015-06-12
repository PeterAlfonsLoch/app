#pragma once


#undef new



namespace message
{


   class CLASS_DECL_AURA base :
      public signal_details
   {
   public:


      ::user::primitive *      m_pwnd;
      bool                       m_bConditional;
      bool                       m_bReflect;
      bool                       m_bDestroyed;
      bool                       m_bDoSystemDefault;

      base(::aura::application * papp,class ::signal * psignal = NULL);
      base(::aura::application * papp,::user::primitive * pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
      base(const base & base);
      virtual ~base();



      virtual void set_lresult(LRESULT lresult);
      virtual LRESULT & get_lresult();
      virtual void set(::user::primitive * pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
      virtual void set(::user::primitive * pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam);
   protected:
      LRESULT * m_plresult;
      LRESULT  m_lresult;
   };


} // namespace message


#define new AURA_NEW
