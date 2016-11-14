
//#include <openssl/err.h>

//#include "framework.h"
//#include "windows.h"
//#include <ddeml.h>  // for MSGF_DDEMGR


//__declspec(thread) HHOOK t_hHookOldMsgFilter = NULL;


//LRESULT CALLBACK __message_filter_hook(int32_t code,WPARAM wParam,LPARAM lParam);


void CLASS_DECL_AURA __init_thread()
{

   //if(t_hHookOldMsgFilter == NULL)
   //{

   //   t_hHookOldMsgFilter = ::SetWindowsHookEx(WH_MSGFILTER,__message_filter_hook,NULL,::GetCurrentThreadId());

   //}

}


void CLASS_DECL_AURA __term_thread()
{
  

}


//namespace windows
//{
//

   //thread::thread(::aura::application * papp):
   //   object(papp),
   //   ::thread_impl(papp)
   //{

   //      m_evFinish.SetEvent();
   //      m_pThreadParams = NULL;
   //      m_pfnThreadProc = NULL;

   //      CommonConstruct();

   //}

   //void thread::construct(__THREADPROC pfnThreadProc,LPVOID pParam)
   //{
   //   m_evFinish.SetEvent();
   //   m_pfnThreadProc = pfnThreadProc;
   //   m_pThreadParams = pParam;

   //   CommonConstruct();
   //}


__STATIC bool CLASS_DECL_AURA IsHelpKey(LPMSG lpMsg)
// return TRUE only for non-repeat F1 keydowns.
{
   return lpMsg->message == WM_KEYDOWN &&
      lpMsg->wParam == VK_F1 &&
      !(HIWORD(lpMsg->lParam) & KF_REPEAT) &&
      GetKeyState(VK_SHIFT) >= 0 &&
      GetKeyState(VK_CONTROL) >= 0 &&
      GetKeyState(VK_MENU) >= 0;
}

__STATIC inline bool IsEnterKey(LPMSG lpMsg)
{
   return lpMsg->message == WM_KEYDOWN && lpMsg->wParam == VK_RETURN;
}

__STATIC inline bool IsButtonUp(LPMSG lpMsg)
{
   return lpMsg->message == WM_LBUTTONUP;
}



void __term_threading()
{

   //if(t_hHookOldMsgFilter != NULL)
   //{
   //   ::UnhookWindowsHookEx(t_hHookOldMsgFilter);
   //   t_hHookOldMsgFilter = NULL;
   //}

}



bool __node_init_thread(::thread * pthread)
{

   try
   {

      pthread->::exception::translator::attach();

   }
   catch(...)
   {

      return false;

   }

   return true;

}




bool __node_term_thread(::thread * pthread)
{

   bool bOk1 = false;

   try
   {

      if(pthread != NULL)
      {

         pthread->::exception::translator::detach();

      }

      bOk1 = true;

   }
   catch(...)
   {

   }

   return bOk1;

}