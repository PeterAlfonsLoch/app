#pragma once

namespace mediaplay
{

   class CLASS_DECL_ca record_notify_view :
      public virtual_user_interface
   {
   public:
      
      
      DWORD       m_dwOnTime;
      DWORD       m_dwOffTime;

      
      record_notify_view(::ca::application * papp);
      virtual ~record_notify_view();
   
#if !core_level_1
   using ::virtual_user_interface::create;
#endif

      
      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      
      virtual void GetParentClientRect(LPRECT lprect);
   
      virtual void _001OnDraw(::ca::graphics *pdc);
      DECL_GEN_SIGNAL(_001OnTimer)

      bool create(::user::interaction * pinterface, id id);

      static void CALLBACK TimerProc(HWND, UINT, UINT_PTR, DWORD);

   };


} // namespace mediaplay