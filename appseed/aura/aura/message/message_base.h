#pragma once


#undef new



namespace message
{


   class CLASS_DECL_AURA base :
      public signal_details
   {
   public:


      sp(::user::primitive)      m_pwnd;
      bool                       m_bConditional;
      bool                       m_bReflect;
      bool                       m_bDestroyed;
      bool                       m_bDoSystemDefault;
      LRESULT *                  m_plresult;
      LRESULT                    m_lresult;


      base(::aura::application * papp,class ::signal * psignal = NULL);
      base(::aura::application * papp,::user::primitive * pwnd,UINT uiMessage,WPARAM wparam,::lparam lparam,LRESULT & lresult);
      base(const base & base);
      virtual ~base();



      virtual void set_lresult(LRESULT lresult);
      virtual LRESULT & get_lresult();
      virtual void set(::user::primitive * pwnd,UINT uiMessage,WPARAM wparam,::lparam lparam,LRESULT & lresult);
      virtual void set(::user::primitive * pwnd,UINT uiMessage,WPARAM wparam,::lparam lparam);

      base & operator = (const base & base);

      void copy_this(const base & base);

   };


   class CLASS_DECL_AURA timer: public base
   {
   public:


      timer(::aura::application * papp): ::message::base(papp) {}
      using ::message::base::set;
      virtual void set(::user::primitive * pwnd,UINT uiMessage,WPARAM wparam,::lparam lparam,LRESULT & lresult);
      UINT m_nIDEvent;
   };



} // namespace message


#define new AURA_NEW
