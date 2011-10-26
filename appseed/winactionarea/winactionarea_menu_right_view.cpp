#include "StdAfx.h"
#include <cpl.h>



typedef LONG (CALLBACK * pfnCPlApplet)(      
    HWND hwndCPl,
    UINT uMsg,
    LPARAM lParam1,
    LPARAM lParam2
);


namespace winactionarea
{

   menu_right_view::menu_right_view(::ca::application * papp) :
      ca(papp),
      ::user::scroll_view(papp),
      ::user::form(papp),
      ::user::list(papp),
      ::user::form_list(papp),
      ::userbase::form_list(papp),
      ::userbase::view(papp),
      simple_list_view(papp),
      m_il(papp)
   {
      m_il.create(48, 48, 0, 0, 0);
   }

   void menu_right_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      simple_list_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &menu_right_view::_001OnCreate);
   }

   void menu_right_view::_001OnCreate(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      wchar_t wbuf[4096];
      HWND hwnd = _get_handle();
      char buf[4096];
      memset(buf, 0, sizeof(buf));
      SHGetSpecialFolderPath(
         NULL,
         buf,
         CSIDL_SYSTEM,
         FALSE);
      stringa straPath;
      stringa straTitle;
      System.dir().ls_pattern(buf, "*.cpl", &straPath, &straTitle);

      for(int i = 0; i < straPath.get_count(); i++)
      {
         HMODULE hmodule = ::LoadLibrary(straPath[i]);
         if(hmodule == NULL)
            continue;
         pfnCPlApplet fnCPlApplet = (pfnCPlApplet) ::GetProcAddress(hmodule, "CPlApplet");
         if(fnCPlApplet != NULL)
         {
            fnCPlApplet(hwnd, CPL_INIT, 0, 0);
            int iCount = fnCPlApplet(hwnd, CPL_GETCOUNT, 0, 0);
            for(int j = 0; j < iCount; j++)
            {
               CPLINFO info;
               memset(&info, 0, sizeof(info));
               fnCPlApplet(hwnd, CPL_INQUIRE, j, (LPARAM) &info);
               cpl_program cpl;
               cpl.m_iImage = m_il.add_icon_os_data((HICON) ::LoadImage((HINSTANCE) hmodule, MAKEINTRESOURCE(info.idIcon), IMAGE_ICON, 48, 48, 0));
               cpl.m_iIndex =  j;
               cpl.m_strApplet = straTitle[i];
               ::LoadStringW((HINSTANCE) hmodule, info.idName, wbuf, sizeof(wbuf) / sizeof(wchar_t));
               cpl.m_strName = gen::international::unicode_to_utf8(wbuf);
               ::LoadStringW((HINSTANCE) hmodule, info.idInfo, wbuf, sizeof(wbuf) / sizeof(wchar_t));
               cpl.m_strDescription = gen::international::unicode_to_utf8(wbuf);
               m_cpla.add(cpl);
               fnCPlApplet(hwnd, CPL_STOP, j, (LPARAM) &info);
            }
            fnCPlApplet(hwnd, CPL_EXIT, 0, 0);
         }
         ::FreeLibrary(hmodule);
      }
      ::user::list::m_etranslucency = ::user::list::TranslucencyPresent;
      _001SetView(ViewIcon);
      _001UpdateColumns();
      _001OnUpdateItemCount();
   }

   void menu_right_view::_001GetItemImage(::user::list_item * pitem)
   {
      pitem->m_iImage = m_cpla[pitem->m_iItem].m_iImage;
      if(pitem->m_iImage >= 0)
      {
         return_ (pitem->m_bOk, true);
      }
      else
      {
         return_ (pitem->m_bOk, false);
      }
   }

   count menu_right_view::_001GetItemCount()
   {
      return m_cpla.get_count();
   }

   void menu_right_view::_001GetItemText(::user::list_item * pitem)
   {
      if(pitem->m_iItem >= 0 && pitem->m_iItem < m_cpla.get_count())
      {
         pitem->m_strText = m_cpla[pitem->m_iItem].m_strName;
         return_ (pitem->m_bOk, true);
      }
      return_ (pitem->m_bOk, false);
   }


   void menu_right_view::_001InsertColumns()
   {
      ::user::list_column column;
      column.m_sizeIcon.cx          = 48  ;
      column.m_sizeIcon.cy          = 48;
      column.m_pilHover             = &m_il;
      column.m_pil                  = &m_il;
      column.m_iWidth               = 100;
	   _001AddColumn(column);
   }


void menu_right_view::_001OnClick(UINT nFlags, point point) 
{
   UNREFERENCED_PARAMETER(nFlags);
   UNREFERENCED_PARAMETER(point);
   int iItemRange, iItem;
   Range range;
   _001GetSelection(range);
   for(iItemRange = 0;
       iItemRange < range.get_item_count(); 
       iItemRange++)
   {
      ItemRange itemrange = range.ItemAt(iItemRange);
      for(iItem = itemrange.GetLBound(); 
          iItem <= itemrange.GetUBound();
          iItem++)
      {
         if(iItem < 0)
            continue;
         if(iItem >= m_cpla.get_count())
            continue;
         ::ShellExecute(NULL, NULL, "control.exe", m_cpla[iItem].m_strApplet, NULL, SW_SHOWNORMAL);
      }
   }
   _001ClearSelection();
   GetTopLevelParent()->PostMessage(WM_CLOSE);
}

} // namespace winactionarea