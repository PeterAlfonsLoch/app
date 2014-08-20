/*
Copyright(C) Nishant Sivakumar.
URLs - http://blog.voidnish.com and http://www.voidnish.com
Contact : nish@voidnish.com
*/

// ShellTrayInfoView.cpp : implementation of the notification_area class
//

#include "framework.h"

namespace user
{

   // notification_area

   notification_area::notification_area() :
      m_hfontHidden(NULL),
      m_hfontRegular(NULL)
   {
      // TODO: add construction code here
      m_pil16 = NULL;
   }

   notification_area::~notification_area()
   {
#ifdef WINDOWSEX
      ::DeleteObject(m_hfontHidden);
      ::DeleteObject(m_hfontRegular);
#else
      throw todo(get_app());
#endif
   }

   void notification_area::Initialize(sp(::axis::application) papp)
   {

#ifdef WINDOWSEX

      LOGFONTW lf = {0};
      wcscpy(lf.lfFaceName, L"Arial");

      lf.lfHeight = 16;
      m_hfontRegular = CreateFontIndirectW(&lf);

      lf.lfItalic = TRUE;
      m_hfontHidden = CreateFontIndirectW(&lf);

      m_oswindowTray = FindTrayToolbarWindow();

      m_pil16 = new image_list(papp);
      m_pil16->create(16,16,ILC_COLOR24,16,16);

#else
      throw todo(get_app());
#endif

      ListTrayIcons();
   }

   void notification_area::ListTrayIcons(int32_t defindex /*= 0*/)
   {
#ifdef WINDOWSEX
      UNREFERENCED_PARAMETER(defindex);
      m_infoa.remove_all();

      m_pil16->remove_all();

      if(m_oswindowTray == NULL)
      {
         m_oswindowTray = FindTrayToolbarWindow();
         if(m_oswindowTray == NULL)
         {
            return;
         }
      }

      DWORD dwTrayPid = 0;
      if(!GetWindowThreadProcessId(m_oswindowTray, &dwTrayPid))
         return;

      if(dwTrayPid == 0)
         return;

      int32_t count = (int32_t)::SendMessage(m_oswindowTray, TB_BUTTONCOUNT, 0, 0);

      process_data<TBBUTTON> data(dwTrayPid);
      TBBUTTON tb = {0};
      TRAYDATA tray = {0};
      TrayItemInfo info;

      for(int32_t i=0; i<count; i++)
      {
         ::SendMessage(m_oswindowTray, TB_GETBUTTON, i, (LPARAM)data.get_data());
         data.ReadData(&tb);
         data.ReadData<TRAYDATA>(&tray,(LPCVOID)tb.dwData);

         DWORD dwProcessId = 0;
         GetWindowThreadProcessId(tray.m_oswindow,&dwProcessId);

         info.sProcessPath = GetFilenameFromPid(dwProcessId);

         wchar_t TipChar;
         wchar_t sTip[1024] = {0};
         wchar_t* pTip = (wchar_t*)tb.iString;

         if(!(tb.fsState&TBSTATE_HIDDEN))
         {
            int32_t x = 0;
            do
            {
               if(x == 1023)
               {
                  wcscpy(sTip,L"[ToolTip was either too long or not set]");
                  break;
               }
               data.ReadData<wchar_t>(&TipChar, (LPCVOID)pTip++);
            }while(sTip[x++] = TipChar);
         }
         else
            wcscpy(sTip,L"[Hidden icon]");

         info.sTip = ::str::international::unicode_to_utf8(sTip);

         info.m_oswindow = tray.m_oswindow;
         info.uCallbackMessage = tray.uCallbackMessage;
         info.uID = tray.uID;

         info.bVisible = !(tb.fsState & TBSTATE_HIDDEN);

         int32_t iconindex = 0;
         ICONINFO  iinfo;
         if(GetIconInfo(tray.hIcon,&iinfo) != 0)
         {
            iconindex = m_pil16->add_icon_os_data(tray.hIcon);
         }
         ::DestroyIcon(tray.hIcon);
         ::DeleteObject(iinfo.hbmColor);
         ::DeleteObject(iinfo.hbmMask);

         //LVITEM lv = {0};
         //lv.iItem = GetListCtrl().get_item_count();
         //lv.iSubItem = 0;
         //lv.mask = LVIF_IMAGE;
         //lv.iImage = iconindex;

         m_infoa.add(new TrayItemInfo(info));
         //int32_t index = GetListCtrl().InsertItem(&lv);
         //GetListCtrl().set_item_text(index,1,info.sTip);
         //GetListCtrl().set_item_text(index,2,info.sProcessPath);
      }

      //if( (count>0) && (defindex>=0) && (defindex<count) )
      //   GetListCtrl().SetItemState(defindex,
      //      LVIS_FOCUSED|LVIS_SELECTED,
      //      LVIS_FOCUSED|LVIS_SELECTED);
#else
      throw todo(get_app());
#endif
   }

   void notification_area::EditCopy(int32_t iItem)
   {
      UNREFERENCED_PARAMETER(iItem);
   /*   POSITION pos = GetListCtrl().GetFirstSelectedItemPosition();
      if(pos)
      {
         int32_t index = GetListCtrl().GetNextSelectedItem(pos);
         OpenClipboard();
         EmptyClipboard();
         HGLOBAL hText = GlobalAlloc(GMEM_MOVEABLE, sizeof char * 512);
         LPTSTR pStr = (LPTSTR)GlobalLock(hText);
         _stprintf(pStr, "Tray Tip : %s\r\nOwner : %s",
            m_infoa[index].sTip, m_infoa[index].sProcessPath);
         GlobalUnlock(hText);
         SetClipboardData(CF_TEXT, hText);
         CloseClipboard();
      }*/
   }

   void notification_area::DoubleClick(int32_t iItem)
   {
      PostMessageToTrayIcon(iItem, WM_LBUTTONDBLCLK);
   }

   void notification_area::LeftClick(int32_t iItem)
   {
      PostMessageToTrayIcon(iItem, WM_LBUTTONDOWN);
      PostMessageToTrayIcon(iItem, WM_LBUTTONUP);
   }

   void notification_area::RightClick(int32_t iItem)
   {
      PostMessageToTrayIcon(iItem, WM_RBUTTONDOWN);
      PostMessageToTrayIcon(iItem, WM_RBUTTONUP);
   }

   void notification_area::PostMessageToTrayIcon(int32_t iItem, LPARAM lParam)
   {
#ifdef WINDOWSEX
      ::PostMessage(m_infoa[iItem].m_oswindow, m_infoa[iItem].uCallbackMessage, m_infoa[iItem].uID, lParam);
#endif
   }

   void notification_area::MoveLeft(int32_t iItem)
   {
#ifdef WINDOWSEX
      if(iItem > 0)
      {
         ::SendMessage(m_oswindowTray, TB_MOVEBUTTON, iItem, iItem-1);
         ListTrayIcons(iItem - 1);
      }
#else
      throw todo(get_app());
#endif
   }

   void notification_area::MoveRight(int32_t iItem)
   {
#ifdef WINDOWSEX
      if(iItem < (m_infoa.get_size() - 1))
      {
         ::SendMessage(m_oswindowTray, TB_MOVEBUTTON, iItem, iItem+1);
         ListTrayIcons(iItem + 1);
      }
#else
      throw todo(get_app());
#endif
   }


   void notification_area::Refresh()
   {
      ListTrayIcons();
   }

   /*
      Copyright(C) Nishant Sivakumar.
      URLs - http://blog.voidnish.com and http://www.voidnish.com
      Contact : nish@voidnish.com
   */


   char GetDriveLetter(const char * lpDevicePath)
   {
#ifdef WINDOWSEX
      char d = 'A';
      while(d <= 'Z')
      {
         char szDeviceName[3] = {d,':','\0'};
         char szTarget[512] = {0};
         if(QueryDosDevice(szDeviceName, szTarget, 511) != 0)
            if(_tcscmp(lpDevicePath, szTarget) == 0)
               return d;
         d++;
      }
#else
      throw todo(get_thread_app());
#endif

      return '\0';

   }

   oswindow FindTrayToolbarWindow()
   {
      oswindow oswindow = NULL;
#ifdef WINDOWSEX
      oswindow = ::FindWindow("Shell_TrayWnd", NULL);
      if(oswindow != NULL)
      {
         oswindow = ::FindWindowEx(oswindow,NULL,"TrayNotifyWnd", NULL);
         if(oswindow != NULL)
         {
            oswindow = ::FindWindowEx(oswindow,NULL,"SysPager", NULL);
            if(oswindow != NULL)
            {
               oswindow = ::FindWindowEx(oswindow, NULL,"ToolbarWindow32", NULL);
            }
         }
      }
#endif
      return oswindow;
   }

#ifdef WINDOWSEX
   string GetFilenameFromPid(uint32_t pid)
   {
      string strRet = "[Unknown Process]";
      char ImageFileName[1024] = {0};
      HANDLE ph = OpenProcess(PROCESS_QUERY_INFORMATION,FALSE,pid);
      if(ph)
      {
         CloseHandle(ph);

         string sTmp = ImageFileName;
         string strSearch = "\\Device\\HarddiskVolume";
         strsize ind = sTmp.find(strSearch);
         if(ind != -1)
         {
            ind = sTmp.find('\\', ind + strSearch.get_length());
            if(ind != -1)
            {
               string sReplace = "#:";
               sReplace.set_at(0,GetDriveLetter(sTmp.Left(ind)));

               strRet = sReplace + sTmp.Mid(ind);
            }
         }
      }
      return strRet;
   }
#endif

} // namespace user
