#include "framework.h"



namespace message
{



   base::base(sp(::base::application) papp,class ::signal * psignal):
      element(papp),
      signal_details(psignal)
   {
      m_lresult = 0;
      m_plresult = &m_lresult;
   }

   base::base(sp(::base::application) papp,sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult):
      element(papp),
      signal_details(papp)
   {
      m_lresult = 0;
      set(pwnd,uiMessage,wparam,lparam,lresult);
   }

   void base::set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult)
   {
      m_pwnd            = pwnd;
      m_uiMessage       = uiMessage;
      m_wparam          = wparam;
      m_lparam          = lparam;
      m_plresult        = &lresult;
   }

   void base::set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam)
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

