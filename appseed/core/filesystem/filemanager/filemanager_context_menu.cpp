#include "framework.h"



namespace filemanager
{


   context_menu::context_menu()
   {
#ifdef WINDOWSEX
      m_pcontextmenu = NULL;
#endif
   }

   context_menu::~context_menu()
   {

   }

   void context_menu::GetMessageString(UINT nID, string &rstrMessage)
   {
#ifdef WINDOWSEX
      if(m_pcontextmenu == NULL)
         return;
      string & str = rstrMessage;
      LPTSTR lpsz = str.GetBuffer(1024);
      m_pcontextmenu->GetCommandString(
         nID - 0x1000,
         GCS_HELPTEXTA,
         NULL,
         lpsz,
         1024);
      str.ReleaseBuffer();
#endif
   }

   void context_menu::GetVerb(UINT nID, string & rwstrMessage)
   {
#ifdef WINDOWSEX
      if(m_pcontextmenu == NULL)
         return;
      string & str = rwstrMessage;
      char * lpsz = str.GetBuffer(1024);
      m_pcontextmenu->GetCommandString(
         nID - 0x1000,
         GCS_VERBW,
         NULL,
         (LPTSTR) lpsz,
         1024);
      str.ReleaseBuffer();
#endif
   }


   void context_menu::OnCommand(UINT uiId)
   {
#ifdef WINDOWSEX
      if(m_pcontextmenu == NULL)
         return;

      CMINVOKECOMMANDINFO info;

      string wstrVerb;
      GetVerb(uiId, wstrVerb);

      info.cbSize = sizeof(info);
      info.fMask = CMIC_MASK_ASYNCOK;
      info.lpParameters = NULL;
      info.lpDirectory = NULL;
      info.hwnd = Session.get_active_ui()->get_handle();
      info.lpVerb = MAKEINTRESOURCE(uiId - 0x1000);
      info.nShow = SW_SHOWNORMAL;

      m_pcontextmenu->InvokeCommand((LPCMINVOKECOMMANDINFO) &info);

#endif
   }


} // namespace filemanager



