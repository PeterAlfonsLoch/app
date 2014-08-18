#pragma once


namespace user
{


   class CLASS_DECL_AXIS message :
      virtual public ::object
   {
   public:


      sp(::user::interaction)    m_pui;
      UINT                       m_uiMessage;
      WPARAM                     m_wparam;
      LPARAM                     m_lparam;


      LRESULT send();
      static UINT ThreadProcSendMessage(LPVOID lp);
      static void post(sp(::user::interaction) puie, UINT uiMessage, WPARAM wparam, LPARAM lparam, int32_t epriority = ::get_scheduling_priority_normal());

   };


} // namespace user
