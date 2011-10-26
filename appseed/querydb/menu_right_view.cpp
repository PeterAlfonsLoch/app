#include "StdAfx.h"
#include <cpl.h>



typedef LONG (CALLBACK * pfnCPlApplet)(      
    HWND hwndCPl,
    UINT uMsg,
    LPARAM lParam1,
    LPARAM lParam2
);


namespace querydb
{

   menu_right_view::menu_right_view(::ca::application * papp) :
      ca(papp),
      ::user::scroll_view(papp),
      ::user::form(papp),
      ::user::list(papp),
      ::user::form_list(papp),
      ::userbase::form_list(papp),
      ::userbase::view(papp),
      simple_list_view(papp)
   {
   }

   void menu_right_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      simple_list_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &menu_right_view::_001OnCreate);
   }

   void menu_right_view::_001OnCreate(gen::signal_object * pobj)
   {
      ::user::list::m_etranslucency = ::user::list::TranslucencyPresent;
      _001SetView(ViewIcon);
      _001UpdateColumns();
      _001OnUpdateItemCount();
   }

   void menu_right_view::_001GetItemImage(::user::list_item * plistitem)
   {
      UNREFERENCED_PARAMETER(plistitem);
   }

   count menu_right_view::_001GetItemCount()
   {
      return 0;
   }

   void menu_right_view::_001GetItemText(::user::list_item * plistitem)
   {
      UNREFERENCED_PARAMETER(plistitem);
   }


   void menu_right_view::_001InsertColumns()
   {
      ::user::list_column column;
      column.m_sizeIcon.cx          = 48  ;
      column.m_sizeIcon.cy          = 48;
      //column.m_pilHover             = &m_il;
      //column.m_pil                  = &m_il;
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
         //if(iItem >= m_cpla.get_count())
           // continue;
         //::ShellExecute(NULL, NULL, "control.exe", m_cpla[iItem].m_strApplet, NULL, SW_SHOWNORMAL);
      }
   }
   _001ClearSelection();
   GetTopLevelParent()->PostMessage(WM_CLOSE);
}

} // namespace querydb