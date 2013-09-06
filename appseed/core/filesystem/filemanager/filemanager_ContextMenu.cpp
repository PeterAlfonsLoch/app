#include "framework.h"
#include "ContextMenu.h"


namespace filemanager
{


   ContextMenu::ContextMenu()
   {
#ifdef WINDOWSEX
      m_pcontextmenu = NULL;
#endif
   }

   ContextMenu::~ContextMenu()
   {

   }

   void ContextMenu::GetMessageString(UINT nID, string &rstrMessage)
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

   void ContextMenu::GetVerb(UINT nID, string & rwstrMessage)
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


   void ContextMenu::OnCommand(UINT uiId)
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
      info.hwnd = System.GetMainWnd()->get_handle();
      info.lpVerb = MAKEINTRESOURCE(uiId - 0x1000);
      info.nShow = SW_SHOWNORMAL;

      m_pcontextmenu->InvokeCommand((LPCMINVOKECOMMANDINFO) &info);

#endif
   }


} // namespace filemanager



