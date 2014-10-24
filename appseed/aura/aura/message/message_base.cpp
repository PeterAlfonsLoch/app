#include "framework.h"



namespace message
{



   base::base(sp(::aura::application) papp,class ::signal * psignal):
      element(papp),
      signal_details(psignal)
   {

      m_lresult            = 0;
      m_bDestroyed         = false;
      m_pwnd               = NULL;
      m_plresult           = &m_lresult;

   }


   base::base(sp(::aura::application) papp,::user::interaction * pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult):
      element(papp),
      signal_details(papp)
   {

      m_lresult            = 0;
      m_bDestroyed         = false;
      set(pwnd,uiMessage,wparam,lparam,lresult);

      Application.tellme_destroyed(pwnd, &m_bDestroyed);

   }


   base::base(const base & base)
   {

      m_pwnd               = base.m_pwnd;
      m_uiMessage          = base.m_uiMessage;
      m_wparam             = base.m_wparam;
      m_lparam             = base.m_lparam;
      m_bConditional       = base.m_bConditional;
      m_bReflect           = base.m_bReflect;
      m_bDestroyed         = false;

      Application.tellme_destroyed(m_pwnd, &m_bDestroyed);

   }

   base::~base()
   {

      if(m_pwnd != NULL)
      {

         synch_lock sl(get_ui_destroyed_mutex());

         if(m_bDestroyed)
         {

            printf("Window Already Destroyed");

         }
         else
         {

            Application.tellme_destroyed(m_pwnd, &m_bDestroyed, false);

         }

      }

   }


   void base::set(::user::interaction * pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult)
   {

      m_pwnd            = pwnd;
      m_uiMessage       = uiMessage;
      m_wparam          = wparam;
      m_lparam          = lparam;
      m_plresult        = &lresult;

   }


   void base::set(::user::interaction * pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam)
   {

      set(pwnd,uiMessage,wparam,lparam,m_lresult);

   }


   void base::set_lresult(LRESULT lresult)
   {

      *m_plresult = lresult;

   }


   LRESULT & base::get_lresult()
   {

      return *m_plresult;

   }


} // namespace user








#define ROUND(x,y) (((x)+(y-1))&~(y-1))
#define ROUND4(x) ROUND(x, 4)

#define IMPLEMENT_SIGNAL_OBJECT_FIXED_ALLOC(class_name) IMPLEMENT_FIXED_ALLOC(class_name, ROUND4(sizeof(class_name) * 32))

