#include "StdAfx.h"
#include <Psapi.h>

namespace winutil
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::userbase::view(papp),
      m_taska(papp, this),
      m_dibV(papp),
      m_brushBkActive(papp),
      m_brushBkInactive(papp),
      m_font(papp)
   {
      m_brushBkActive->CreateSolidBrush(RGB(150, 255, 130));
      m_brushBkInactive->CreateSolidBrush(RGB(128, 208, 120));
      LOGFONT lf;
      memset(&lf, 0, sizeof(lf));

      strcpy(lf.lfFaceName, "Verdana");
      lf.lfHeight = 13;
      m_font->CreateFontIndirect(&lf);

      m_iItemHeight = 26;
      m_iTaskOffset = 1000;
      m_iClockOffset = 10000;
   //   m_iNotificationAreaButtonOffset = 10100;
      m_iNotificationAreaOffset = 10200;
      m_iClockH = 30;
      m_iDragTask = -1;
      m_bDragTask = false;
      m_iNotificationAreaH = 30;
      m_bNotificationArea = true;
      m_iNotificationAreaColumnCount = 15;
      m_iV = 123;
      m_iVH = 49;
      m_iVW = 123;
      m_iShutDown = 60000;
      m_iShutDownW = 49;
      m_iShutDownH = 49;
      m_bShutDown = false;
   }

   view::~view()
   {
   }

   void view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::view::_001InstallMessageHandling(pinterface);

	   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
	   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &view::_001OnSize);
	   //IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &view::_001OnPaint);
	   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
	   IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
	   IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);

   //   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
     // IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);

      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &view::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &view::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_RBUTTONUP, pinterface, this, &view::_001OnRButtonUp);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &view::_001OnTimer);

      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &view::_001OnShowWindow);
      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);

   }
   /////////////////////////////////////////////////////////////////////////////
   // ::view drawing

   void view::OnDraw(::ca::graphics * pdcScreen)
   {
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::view diagnostics

   #ifdef _DEBUG
   void view::assert_valid() const
   {
	   ::userbase::view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
	   ::userbase::view::dump(dumpcontext);
   }
   #endif //_DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // ::view message handlers

   // vmpLightView.cpp : implementation of the ::view class
   //


   /////////////////////////////////////////////////////////////////////////////
   // ::view


   BOOL view::PreCreateWindow(CREATESTRUCT& cs)
   {
      cs.lpszClass = Application.RegisterWndClass(
		   CS_DBLCLKS |
		   CS_OWNDC,
		   0, 0, 0);
      cs.style &= ~WS_EX_CLIENTEDGE;
	   return ::userbase::view::PreCreateWindow(cs);
   }
   void view::_001OnInitialUpdate(gen::signal_object * pobj) 
   {
      ::userbase::view::_001OnInitialUpdate(pobj);
   //   UpdateList();
   }

   void view::on_update(::view  * pSender, LPARAM lHint, ::radix::object* phint) 
   {
      if(lHint == 5432108)
      {
         SetTimer(5432108, 100, NULL);
      }
      else if(lHint == 543218)
      {
   //	   m_ca2spa.load(get_app());
      }
   	
   }

   void view::_001OnDestroy(gen::signal_object * pobj) 
   {
   /*   for(int i = 0; i < m_areaa.get_size(); i++)
      {
         for(int j = 0; j < m_areaa[i].m_hwnda.get_size(); j++)
         {
            HWND hwnd = m_areaa[i].m_hwnda[j];
            ::ShowWindow(hwnd, SW_MINIMIZE);
         }
      }*/
	   ::userbase::view::_001OnDestroy(pobj);
   }



   void view::_001OnSize(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::size, psize, pobj)

      rect rectDesktop;
      Application.get_screen_rect(rectDesktop);

      m_iWScreen = rectDesktop.width();
      m_iHScreen = rectDesktop.height();
      rect rectClient;
      GetClientRect(rectClient);
      rectClient.deflate(2, 2);
      int iW = rectClient.width() / 2;
      int iH = rectClient.height() / 2;
      iH = min(iH, 120);
      double r = (double) iW / (double) iH;
      double rScreen = (double) rectDesktop.width() / (double) rectDesktop.height();
      if(r < rScreen)
      {
         iH = iW / rScreen;
      }
      else if(r > rScreen)
      {
         iW = iH * rScreen;
      }
   //   m_iW = iW;
     // m_iH = iH;
   /*   m_areaa[0].m_spdib.create(iW - 4, iH - 4);
      m_areaa[1].m_spdib.create(iW - 4, iH - 4);
      m_areaa[2].m_spdib.create(iW - 4, iH - 4);
      m_areaa[3].m_spdib.create(iW - 4, iH - 4);*/
   //   Snapshot();
   }

   void view::_001OnPaint(gen::signal_object * pobj) 
   {
   //	CPaintDC spgraphics(this); // device context for winutiling
   //   spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
   }


   void view:: _001OnDraw(::ca::graphics * pdc)
   {
      rect rectClient;
      GetClientRect(rectClient);

      //pdc->FillSolidRect(rectClient, RGB(255, 255, 255));

      class imaging & imaging = Application.imaging();

      imaging.color_blend(pdc, rectClient, RGB(255, 255, 255), 128);

      rect rectArea;

      GetAreaThumbRect(rectArea, m_iV);
      m_dibV->to(pdc, rectArea);

      for(int i = 0; i < m_taska.base_array < task >::get_size(); i++)
      {
         GetAreaThumbRect(rectArea, m_iTaskOffset + i);

         pdc->FillSolidRect(rectArea, RGB(240, 250, 210));
         pdc->Draw3dRect(rectArea, RGB(120, 180, 100), RGB(200, 220, 180));
         rectArea.deflate(1, 1, 1, 1);
         pdc->Draw3dRect(rectArea, RGB(200, 220, 180), RGB(120, 180, 100));
         rectArea.deflate(1, 1, 1, 1);
         pdc->SetBkMode(TRANSPARENT);
         if(m_taska.base_array < task >::element_at(i).m_bNameReady)
         {
            pdc->DrawText(m_taska.base_array < task >::element_at(i).m_strName, rectArea, DT_BOTTOM | DT_LEFT);
         }

      }

   }

   void view::_001OnCreate(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;
      SetTimer(3003, 300, NULL);
      SetTimer(543218, 1000, NULL);

      SetTimer(5432182, 1000, NULL);
      SetTimer(5432185, 1000 * 15, NULL);

      m_dibV.load_from_matter("votagus_mountains_and_valleys-123.png");

      m_taska.start_load();

      frame * pframe = dynamic_cast < frame * > (GetTopLevelFrame());
      pframe->m_pwinutilview = this;

      
      //m_notificationareainfo.Initialize(get_app());
      //m_taska.internet_load(get_app());
   /*   winaction_frame * pframe = dynamic_cast < winaction_frame * > (GetParentFrame());
      if(pframe != NULL)
      {
         pframe->m_pwinutilview = this;
      }*/
   }


   void view::_001OnContextMenu(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
      point point = pcontextmenu->GetPoint();
   }


   void view::_001OnTabClick(int iTab)
   {
      if(iTab == 1)
      {
         Application.simple_message_box(NULL, "Playlist");
      }
   }

   void view::_001OnSetCursor(gen::signal_object * pobj) 
   {
      ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
   	
	   pobj->previous();
   }

   document * view::get_document()
   {
      return dynamic_cast < document * > (::userbase::view::get_document());
   }

   /*void view::SwitchArea(int iArea)
   {
      if(iArea != m_iArea)
      {
         //m_bNotificationArea = false;
         UpdateCurrentArea();
         Snapshot(m_iArea);
         for(int i = 0; i < m_areaa[m_iArea].m_hwnda.get_size(); i++)
         {
            ::ShowWindow(m_areaa[m_iArea].m_hwnda[i], SW_HIDE);
         }
         m_iArea = iArea;
         for(int i = 0; i < m_areaa[m_iArea].m_hwnda.get_size(); i++)
         {
            ::ShowWindow(m_areaa[m_iArea].m_hwnda[i], SW_SHOW);
         }
         Sleep(23);
         Snapshot(m_iArea);
         GetParentFrame()->::ca::window::RedrawWindow(NULL, NULL, RDW_FRAME | RDW_UPDATENOW | RDW_INVALIDATE);
      }
   }*/
   /*
   void view::Snapshot()
   {
      int iArea = m_iArea;
      SwitchArea(0);
      SwitchArea(1);
      SwitchArea(2);
      SwitchArea(3);
      SwitchArea(iArea);
   }
   */
   /*void view::Snapshot(int iArea)
   {
      ::ca::graphics * pdc = ::ca::window::GetWindowDC();

      ::ca::graphics_sp spgraphics(get_app());
      spgraphics->CreateCompatibleDC(pdc);
      HGDIOBJ hobj = spgraphics->SelectObject(m_areaa[m_iArea].m_spdib.m_hbitmap);
      m_areaa[m_iArea].m_bBlend = false;

      HDC hdc = ::GetDC(NULL); //get full screen

      ::ca::graphics_sp dcScreen;
      spgraphicsScreen->Attach(hdc);

      spgraphics->SetStretchBltMode(HALFTONE);
      spgraphics->StretchBlt(0, 0, m_iW - 4, m_iH - 4, &dcScreen, 0, 0, m_iWScreen, m_iHScreen, SRCCOPY);

      spgraphicsScreen->Detach();

      VERIFY(::ReleaseDC(NULL, hdc));
      spgraphics->SelectObject(hobj);
      
      ::ca::window::ReleaseDC(pdc);
   }*/

   void view::GetAreaThumbRect(LPRECT lprect, int iArea)
   {
      rect rectClient;
      GetClientRect(rectClient);
      if(iArea == m_iV)
      {
         lprect->bottom = rectClient.bottom;
         lprect->top = lprect->bottom - m_iVH;
         lprect->left = 1;
         lprect->right = lprect->left + m_iVW;
      }
      else if(iArea == m_iShutDown)
      {
         lprect->bottom = rectClient.bottom;
         lprect->top = lprect->bottom - m_iShutDownH;
         lprect->right = rectClient.right - 1;
         lprect->left = lprect->right - m_iShutDownW;
         
      }
      else if(iArea >= m_iNotificationAreaOffset)
      {
         int iColCount = m_iNotificationAreaColumnCount;
         int iCol = (iArea - m_iNotificationAreaOffset) % iColCount;
         int iLin = (iArea - m_iNotificationAreaOffset) / iColCount;
         int cx = 20;
         lprect->left = 1 + iCol * cx;
         lprect->top = rectClient.bottom - m_iVH - m_iItemHeight * 3 + m_iItemHeight * (((iArea - m_iNotificationAreaOffset) / iColCount));
         lprect->right = lprect->left + cx;
         lprect->bottom = lprect->top + m_iItemHeight;
      }
   /*   else if(iArea >= m_iNotificationAreaButtonOffset)
      {
         lprect->left = 1;
         lprect->top = 1 + m_iClockH + m_iH * 2 + 5;
         lprect->right = 350;
         lprect->bottom = lprect->top + m_iNotificationAreaH;
      }*/
      else if(iArea >= m_iClockOffset)
      {
         lprect->left = 1;
         lprect->top = 1;
         lprect->right = 350;
         lprect->bottom = lprect->top + m_iClockH;
         return;
      }
      else if(iArea >= m_iTaskOffset)
      {
         lprect->left = 1;
         //lprect->top = m_iClockH + m_iNotificationAreaH + m_iH * 2 + 5 + m_iItemHeight * ((iArea - m_iTaskOffset));
         lprect->top = m_iClockH + m_iItemHeight * ((iArea - m_iTaskOffset));
         lprect->right = 350;
         lprect->bottom = lprect->top + m_iItemHeight;
      }
   }

   int view::hit_test(point pt)
   {
      rect rectArea;
      GetAreaThumbRect(rectArea, m_iV);
      if(rectArea.contains(pt))
      {
         return m_iV;
      }
      GetAreaThumbRect(rectArea, m_iShutDown);
      if(rectArea.contains(pt))
      {
         return m_iShutDown;
      }
      GetAreaThumbRect(rectArea, m_iClockOffset);
      if(rectArea.contains(pt))
      {
         return m_iClockOffset;
      }
   /*   GetAreaThumbRect(rectArea, m_iNotificationAreaButtonOffset);
      if(rectArea.contains(pt))
      {
         return m_iNotificationAreaButtonOffset;
      }*/
   /*   for(int i = 0; i < m_notificationareainfo.m_infoa.get_size(); i++)
      {
         GetAreaThumbRect(rectArea, m_iNotificationAreaOffset + i);
         if(rectArea.contains(pt))
         {
            return m_iNotificationAreaOffset + i;
         }
      }*/
   /*   for(int i = 0; i < 4; i++)
      {
         GetAreaThumbRect(rectArea, i);
         if(rectArea.contains(pt))
         {
            return i;
         }
      }*/
      for(int i = 0; i < m_taska.base_array < task >::get_size(); i++)
      {
         GetAreaThumbRect(rectArea, m_iTaskOffset + i);
         if(rectArea.contains(pt))
         {
            return m_iTaskOffset + i;
         }
      }
      return -1;
   }

   void view::_001OnLButtonDown(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      int iHitArea = hit_test(pt);
      if(iHitArea >= 0 && !m_bShutDown)
      {
         if(iHitArea >= m_iTaskOffset && iHitArea < (m_iTaskOffset + m_taska.base_array < task >::get_size()))
         {
            m_iDragTask = iHitArea;
            SetTimer(5432180, 400, NULL); // DragTask
         }
      }

   }

   void view::_001OnLButtonUp(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      KillTimer(5432180);
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      int iHitArea = hit_test(pt);
      if(m_bDragTask && !m_bShutDown)
      {
         m_bDragTask = false;
         if(m_iDragTask >= m_iTaskOffset
         && m_iDragTask < m_iTaskOffset + m_taska.base_array < task >::get_size())
         {
   /*         HWND hwnd = m_areaa[m_iArea].m_hwndaPreserve[m_iDragTask - m_iTaskOffset];
            ::ShowWindow(hwnd, SW_HIDE);
            SwitchArea(iHitArea);
            m_dw3003Time = ::GetTickCount();
            SetTimer(3003, 300, NULL);
            ::ShowWindow(hwnd, SW_RESTORE);*/
            return;
         }
      }
      if(iHitArea == m_iV)
      {

      }
      else if(iHitArea == m_iShutDown)
      {
         m_bShutDown = !m_bShutDown;
         _001RedrawWindow();
      }
      else if(iHitArea >= 0)
      {
         {
      /*      else if(iHitArea == m_iNotificationAreaButtonOffset)
            {
               m_notificationareainfo.Refresh();
               m_bNotificationArea = true;
            }*/
            if(iHitArea >= m_iNotificationAreaOffset && iHitArea < (m_iNotificationAreaOffset + m_notificationareainfo.m_infoa.get_size()))
            {
               m_notificationareainfo.LeftClick(iHitArea - m_iNotificationAreaOffset);
               ::Sleep(100);
               GetParentFrame()->ShowWindow(SW_HIDE);
            }
   /*         else if(iHitArea < m_areaa.get_size())
            {
              m_dwCurrentAreaTime = ::GetTickCount();
              GetTopLevelFrame()->ShowWindow(SW_HIDE);
            }*/
            else if(iHitArea >= m_iTaskOffset && iHitArea < (m_iTaskOffset + m_taska.base_array < task >::get_size()))
            {
   //            m_iCurrentArea = iHitArea;
               m_dwCurrentAreaTime = ::GetTickCount();
               _001RedrawWindow();
               string strPath;
               strPath = System.dir().stageapp(m_taska.base_array < task >::element_at(iHitArea - m_iTaskOffset).m_strPath);
               //strPath = "D:\\Arquivos de Programas\\ca2\\stage\\ca2\\fontopus\\cast\\main\\front\\Release\\" + m_taska[iHitArea - m_iTaskOffset].m_id + "Application.exe";
               ::ShellExecute(GetTopLevelParent()->_get_handle(), NULL, strPath, NULL, System.dir().name(strPath), SW_SHOW);

   /*            HWND hwnd = m_areaa[m_iArea].m_hwndaPreserve[iHitArea - m_iTaskOffset];
               if(::IsIconic(hwnd))
               {
                  AfxBeginThread(ThreadProcShowWindow, new show_window(hwnd, SW_RESTORE, this));
               }
               else
               {
                  if(hwnd != m_areaa[m_iArea].m_hwnda[0])
                  {
                     AfxBeginThread(ThreadProcShowWindow, new show_window(hwnd, -1, this));
                     
                  }
                  else
                  {
                     AfxBeginThread(ThreadProcShowWindow, new show_window(hwnd, SW_MINIMIZE, this));
                  }
               }
               UpdateCurrentArea();
               Snapshot(m_iArea);
               _001RedrawWindow();
               ::Sleep(100);*/
   /*            for(int i = 0; i < m_areaa[m_iArea].m_hwndaPreserve.get_size(); i++)
               {
                  hwnd = m_areaa[m_iArea].m_hwndaPreserve[i];
                  if(!::IsIconic(hwnd))
                  {
                     GetParentFrame()->ShowWindow(SW_HIDE);
                     break;
                  }
               }*/
               //Snapshot(m_iArea);
            }
         }
      }

   }

   void view::_001OnRButtonUp(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)

      int iHitArea = hit_test(pmouse->m_pt);
      if(iHitArea >= m_iNotificationAreaOffset)
      {
         m_notificationareainfo.RightClick(iHitArea - m_iNotificationAreaOffset);
      }
      else if(iHitArea >= m_iClockOffset)
      {
      }
      else if(iHitArea >= m_iTaskOffset 
         && iHitArea < m_iTaskOffset + m_taska.base_array < task >::get_size())
      {
   /*      ::userbase::menu menu;
         menu.LoadMenu(::GetSystemMenu(GetParentFrame()->GetSafeHwnd(), FALSE));
         menu.set_app(get_app());
         menu.TrackPopupMenu(0, pmouse->m_pt.x, pmouse->m_pt.y, 
            m_areaa[m_iArea].m_hwndaPreserve[iHitArea - m_iTaskOffset]);*/
      }
      else if(iHitArea < 0)
      {
         ::userbase::menu menu(get_app());
         menu.LoadXmlMenu( "winutil\\popup_winutil.xml");
         ::userbase::menu menuPopup(get_app(), menu.GetSubMenu(0));
         menuPopup.set_app(get_app());
         menuPopup.TrackPopupMenu(0, pmouse->m_pt.x, pmouse->m_pt.y, GetParentFrame());
      }
      
   }

   void view::_001OnOp(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj)
   /*   if(pbase->m_wparam == OpUpdateCurrentArea)
      {
      }*/
   }


   /*void view::area::UpdatePreserve()
   {
      bool bAutoDelete;
      for(int i = 0; i < m_hwndaPreserve.get_size(); i++)
      {
         HWND hwnd = m_hwndaPreserve[i];
         HICON hicon16 = NULL;
         HICON hicon48 = NULL;
         HICON hicon16_1 = NULL;
         HICON hicon48_1 = NULL;
         HICON hicon_2 = NULL;
         if(!::SendMessageTimeout(hwnd, WM_GETICON, ICON_BIG, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &hicon_2))
         {
            hicon48_1 = NULL;
         }
         if(!::SendMessageTimeout(hwnd, WM_GETICON, ICON_SMALL, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &hicon_2))
         {
            hicon_2 = NULL;
         }
         bAutoDelete = false;
         if(hicon_2 == NULL)
         {
            hicon_2 = hicon48_1;
         }
         if(hicon_2 == NULL)
         {
            hicon_2 = (HICON)GetClassLong(hwnd, GCL_HICONSM);
         }
         if(hicon_2 == NULL)
         {
            hicon_2 = (HICON)GetClassLong(hwnd, GCL_HICON);
         }
         if(hicon_2 == NULL)
         {
            bAutoDelete = true;
            DWORD dwProcessId;
            char szFilename[1024];
            DWORD dwThreadId = ::GetWindowThreadProcessId(hwnd, &dwProcessId);
            HANDLE hprocess = (HANDLE) OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ , FALSE, dwProcessId);
            memset(szFilename, 0, sizeof(szFilename));
            ::GetModuleFileNameEx((HMODULE) hprocess, NULL, szFilename, sizeof(szFilename));
            string strFilename = szFilename;
            bool bPathCaption = strFilename.Right(13) == "\\explorer.exe";
            filemanager::_shell::ImageSet::GetIcon(m_pview->GetSafeHwnd(), szFilename, L"", filemanager::_shell::IconNormal, &hicon16, &hicon48);
            hicon_2 = hicon16;
            ::CloseHandle(hprocess);
         }
         
         visual::icon & icon = m_hicona[i];
         if(icon.m_bAutoDelete)
         {
            ::DestroyIcon(icon.m_hicon);
         }
         icon.m_hicon = hicon_2;
         icon.m_bAutoDelete = bAutoDelete;
         if(hicon48 != NULL)
         {
            ::DestroyIcon(hicon48);
         }
      }
   restart:
      for(int i = 0; i < m_hwndaPreserve.get_size(); i++)
      {
         if(m_hwnda.FindFirst(m_hwndaPreserve[i]) < 0)
         {
            op op;
            op.m_eop = op_delete;
            op.m_hwnd = m_hwndaPreserve[i];
            op.m_dwTime = ::GetTickCount() + 2000;
            m_opa.add(op);
         }
      }
      for(int i = 0; i < m_hwnda.get_size(); i++)
      {
         if(m_hwndaPreserve.FindFirst(m_hwnda[i]) < 0)
         {
            op op;
            op.m_eop = op_add;
            op.m_hwnd = m_hwnda[i];
            op.m_dwTime = ::GetTickCount() + 2000;
            m_opa.add(op);
         }
      }
   restart_cancel:
      for(int i = 0; i < m_opa.get_size(); i++)
      {
         if(cancel_op(i, m_opa[i].m_eop, m_opa[i].m_hwnd))
         {
            goto restart_cancel;
         }
      }
   restart_do:
      for(int i = 0; i < m_opa.get_size(); i++)
      {
         if(defer_do_op(i))
            goto restart_do;
      }
   }

   bool view::area::cancel_op(int iParam, e_op eop, HWND hwnd)
   {
      bool bCancel = false;
      for(int i = 0; i < m_opa.get_size(); i++)
      {
         if(i != iParam)
         {
            if(m_opa[i].m_hwnd == hwnd)
            {
               if(eop == op_delete && m_opa[i].m_eop == op_add
               || eop == op_add && m_opa[i].m_eop == op_delete)
               {
                  bCancel = true;
               }
            }
         }
      }
      if(bCancel)
      {
         for(int i = 0; i < m_opa.get_size();)
         {
            if(m_opa[i].m_hwnd == hwnd)
            {
               m_opa.remove_at(i);
            }
            else
            {
               i++;
            }
         }
      }
      return bCancel;
   }

   bool view::area::defer_do_op(int i)
   {
      if(m_opa[i].m_dwTime > ::GetTickCount())
      {
         if(m_opa[i].m_eop == op_delete)
         {
            int iRemove = m_hwndaPreserve.FindFirst(m_opa[i].m_hwnd);
            m_hwndaPreserve.remove_at(iRemove);
            m_hicona.remove_at(iRemove);
            m_opa.remove_at(i);
            m_baPathCaption.remove_at(i);
         }
         else if(m_opa[i].m_eop == op_add)
         {
            HWND hwnd = m_opa[i].m_hwnd;
            if(m_hwndaPreserve.FindFirst(hwnd) < 0)
            {
               visual::icon icon;
               icon.m_hicon = NULL;
               icon.m_bAutoDelete = false;
               m_hicona.add(icon);
               m_hicona[m_hicona.get_upper_bound()].m_bAutoDelete = false;
               m_hwndaPreserve.add(m_opa[i].m_hwnd);
               bool bPathCaption;
               {
                  DWORD dwProcessId;
                  char szFilename[1024];
                  DWORD dwThreadId = ::GetWindowThreadProcessId(hwnd, &dwProcessId);
                  HANDLE hprocess = (HANDLE) OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ , FALSE, dwProcessId);
                  memset(szFilename, 0, sizeof(szFilename));
                  ::GetModuleFileNameEx((HMODULE) hprocess, NULL, szFilename, sizeof(szFilename));
                  string strFilename = szFilename;
                  bPathCaption = strFilename.Right(13) == "\\explorer.exe";
                  ::CloseHandle(hprocess);
               }
               m_baPathCaption.add(bPathCaption);
            }
            m_opa.remove_at(i);
         }
         return true;
      }
      return false;
   }
   */
   void view::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj)
      if(ptimer->m_nIDEvent == 5432185)
      {
         m_taska.start_load();
         //UpdateList();
      }
      else if(ptimer->m_nIDEvent == 5432182)
      {
         //UpdateList();
         //KillTimer(5432182);
         //SetTimer(5432180, 1000 * 60, NULL);
      }
      else if(ptimer->m_nIDEvent == 543218)
      {
         if(IsWindowVisible())
         {
   /*         UpdateCurrentArea();
            Snapshot(m_iArea);
            m_notificationareainfo.Refresh();*/
         }
      }
      else if(ptimer->m_nIDEvent == 5432108)
      {
         KillTimer(ptimer->m_nIDEvent);
   /*      UpdateCurrentArea();
         Snapshot(m_iArea);*/
      }
      else if(ptimer->m_nIDEvent == 5432180)
      {
         KillTimer(ptimer->m_nIDEvent);
         m_bDragTask = true;
      }
      else if(ptimer->m_nIDEvent == 3003)
      {
         point pt;
         Application.get_cursor_pos(&pt);
         HWND hwnd = ::WindowFromPoint(pt);
         if(GetTopLevelParent()->_get_handle() != hwnd
            && !user::WndUtil::IsAscendant(GetTopLevelParent()->_get_handle(), hwnd))
         {
            GetParentFrame()->ShowWindow(SW_HIDE);
         }
      }
   }
   /*
   */

   BOOL CALLBACK view::UpdateCurrentAreaEnumWindowsProc(      
       HWND hwnd,
       LPARAM lParam)
   {
      ::view * pview = (::view *) lParam;
      DWORD dwThreadId;
      DWORD dwProcessId;
      HICON hicon16;
      HICON hicon48;
      ::ca::window * pwnd = pview->m_papp->m_psystem->window_from_os_data(hwnd);
      if(pwnd == NULL)
         return TRUE;
      //HICON hicon = pwnd->GetIcon(FALSE);
      //if(hicon == NULL)
      //{
         //hicon = pwnd->GetIcon(TRUE);
      //}
      int iStyle = pwnd->GetStyle();
      int iStyleEx = pwnd->GetExStyle();
      if(hwnd != pview->GetTopLevelParent()->_get_handle()
        && (iStyle & WS_VISIBLE)
        && !(iStyleEx & WS_EX_TOOLWINDOW)
        &&((iStyleEx & WS_EX_APPWINDOW)
        || (!(iStyle & WS_CHILD)
        && pwnd->GetOwner() == NULL)))
      {
   /*      if(!pview->m_areaa.Contains(pwnd->GetSafeHwnd(), pview->m_iArea))
            pview->m_areaa[pview->m_iArea].m_hwnda.add(pwnd->GetSafeHwnd());*/
      }
      return TRUE;
   }

   UINT AFX_CDECL view::ThreadProcShowWindow(LPVOID lpparam)
   {
      show_window * pshow = (show_window *) lpparam;
      if(pshow->m_iShow == -1)
      {
         ::SetForegroundWindow(pshow->m_hwnd);
         ::SetWindowPos(pshow->m_hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
      }
      else
      {
         if(pshow->m_iShow == SW_RESTORE)
         {
            ::SetForegroundWindow(pshow->m_hwnd);
         }
         ::ShowWindow(pshow->m_hwnd, pshow->m_iShow);
      }
   //   pshow->m_pview->PostMessageA(MessageOp, OpUpdateCurrentArea);
      delete pshow;
      return 0;
   }

   view::show_window::show_window(HWND hwnd, int iShow, ::view * pview)
   {
      m_hwnd   = hwnd;
      m_iShow  = iShow;
      m_pview  = pview;
   }



   void view::_001OnShowWindow(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::show_window, pshowwindow, pobj)
   }

   /*bool view::area_array::Contains(HWND hwnd, int iExcludeArea)
   {
      for(int iArea = 0; iArea < get_size(); iArea++)
      {
         if(iArea != iExcludeArea)
         {
            if(element_at(iArea).m_hwnda.FindFirst(hwnd) >= 0)
               return true;
         }
      }
      return false;
   }
   */


   void view::ensure_apps()
   {
      if(::IsWindow(m_hwndWinactionarea) &&
         ::IsWindow(m_hwndCommand) &&
         ::IsWindow(m_hwndWinutil))
         return;
      EnumWindows(GetAppsEnumWindowsProc, (LPARAM) this);
      if(!::IsWindow(m_hwndWinactionarea))
      {
         /*::ShellExecuteW(
               NULL, 
               NULL, 
               gen::international::utf8_to_unicode(m_strWinactionarea),
               NULL,
               gen::international::utf8_to_unicode(System.dir().name(m_strWinactionarea)),
               SW_SHOW);*/
      }
      if(!::IsWindow(m_hwndCommand))
      {
         /*::ShellExecuteW(
               NULL, 
               NULL, 
               gen::international::utf8_to_unicode(m_id),
               NULL,
               gen::international::utf8_to_unicode(System.dir().name(m_id)),
               SW_SHOW);*/
      }
   }


   BOOL CALLBACK view::GetAppsEnumWindowsProc(      
       HWND hwnd,
       LPARAM lParam)
   {
      view * pview = (view *) lParam;
      DWORD dwThreadId;
      DWORD dwProcessId;
      HICON hicon16;
      HICON hicon48;
      DWORD dwptr;
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 1, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 2)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 2, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 4)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 4, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 5)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 5, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 8)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 8, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 11)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 11, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 23)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 23, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 33)
      {
         return TRUE;
      }
      if(::SendMessageTimeout(hwnd, WM_APP + 2000, 33, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr))
      {
         if(dwptr == 1)
         {
            pview->m_hwndCommand = hwnd;
         }
         else if(dwptr == 67)
         {
            pview->m_hwndWinactionarea = hwnd;
         }
         else if(dwptr == 68)
         {
            pview->m_hwndWinutil = hwnd;
         }

      }
      return TRUE;
   }

   view::task_array::task_array(::ca::application * papp, ::view * pview) :
      ca(papp),
      thread(papp),
      simple_thread(papp),
      m_pview(pview)
   {
   }

   void view::task_array::start_load()
   {
      CSingleLock sl(&m_mutex, FALSE);
      if(!sl.Lock(0))
         return;
      task task;
      base_array < class task >::remove_all();
      xml::node node(get_app());
      node.load(Application.file().as_string(System.dir().appdata("spa_install.xml")));
      xml::node * lpnodeInstalled = node.get_child("installed");
      if(lpnodeInstalled != NULL)
      {
         for(int i = 0; i < lpnodeInstalled->children().get_size(); i++)
         {
            task.m_id = lpnodeInstalled->child_at(i)->attr("id");
            if(task.m_id != "_set_windesk")
            {
               task.m_bPathReady = false;
               task.m_bNameReady = false;
               task.m_strName = task.m_id;
               task.m_strPath = "";
               base_array < class task >::add(task);
            }
         }
      }
      sl.Unlock();
      Begin();
   }

   int view::task_array::run()
   {
      CSingleLock sl(&m_mutex, TRUE);
      string strUrl;
      gen::property_set headers;
      for(int i = 0; i < base_array < task >::get_size(); i++)
      {
         task * ptask = &base_array < task >::element_at(i);
         strUrl = "http://spaignition.api.veriterse.net/query?node=install_application&id=";
         strUrl += ptask->m_id;
         strUrl += "&key=launch_name";
         ptask->m_strName= System.http().get(strUrl);
         ptask->m_bNameReady = !ptask->m_strName.is_empty();
         headers.m_propertya.remove_all();
         strUrl = "http://spaignition.api.veriterse.net/query?node=install_application&id=";
         strUrl += ptask->m_id;
         strUrl += "&key=launch_application";
         ptask->m_strPath = System.http().get(strUrl);
         ptask->m_bPathReady = !ptask->m_strPath.is_empty();
         headers.m_propertya.remove_all();
         m_pview->_001RedrawWindow();
      }  
      return 0;
   }

   void view::task_array::assert_valid() const
   {
      base_array < task >::assert_valid();
      simple_thread::assert_valid();
   }

   void view::task_array::dump(dump_context & context) const
   {
      base_array < task >::dump(context);
      simple_thread::dump(context);
   }

} // namespace winutil