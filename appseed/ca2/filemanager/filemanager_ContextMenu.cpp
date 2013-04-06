#include "framework.h"
#include "ContextMenu.h"


namespace filemanager
{


   ContextMenu::ContextMenu()
   {
#ifdef WINDOWSEX
      m_pcontextmenu = ::null();
#endif
   }

   ContextMenu::~ContextMenu()
   {

   }

   void ContextMenu::GetMessageString(UINT nID, string &rstrMessage)
   {
#ifdef WINDOWSEX
      if(m_pcontextmenu == ::null())
         return;
      string & str = rstrMessage;
      LPTSTR lpsz = str.GetBuffer(1024);
      m_pcontextmenu->GetCommandString(
         nID - 0x1000,
         GCS_HELPTEXTA,
         ::null(),
         lpsz,
         1024);
      str.ReleaseBuffer();
#endif
   }

   void ContextMenu::GetVerb(UINT nID, string & rwstrMessage)
   {
#ifdef WINDOWSEX
      if(m_pcontextmenu == ::null())
         return;
      string & str = rwstrMessage;
      char * lpsz = str.GetBuffer(1024);
      m_pcontextmenu->GetCommandString(
         nID - 0x1000,
         GCS_VERBW,
         ::null(),
         (LPTSTR) lpsz,
         1024);
      str.ReleaseBuffer();
#endif
   }


   void ContextMenu::OnCommand(UINT uiId)
   {
#ifdef WINDOWSEX
      if(m_pcontextmenu == ::null())
         return;

      CMINVOKECOMMANDINFO info;

      string wstrVerb;
      GetVerb(uiId, wstrVerb);

      info.cbSize = sizeof(info);
      info.fMask = CMIC_MASK_ASYNCOK;
      info.lpParameters = ::null();
      info.lpDirectory = ::null();
      info.hwnd = System.GetMainWnd()->get_handle();
      info.lpVerb = MAKEINTRESOURCE(uiId - 0x1000);
      info.nShow = SW_SHOWNORMAL;

      m_pcontextmenu->InvokeCommand((LPCMINVOKECOMMANDINFO) &info);

#endif
   }


} // namespace filemanager



