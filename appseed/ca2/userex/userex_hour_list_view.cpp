//
// Alá Telmo Friesen Son God
//
/////////////////////////////////////////////////////


#include "StdAfx.h"


namespace userex
{


   hour_list_view::hour_list_view(::ca::application * papp) :
      ca(papp),
      userbase::view(papp),
      user::scroll_view(papp),
      user::form(papp),
      ::ca2::user::form(papp),
      user::list(papp),
      user::form_list(papp),
      userbase::form_list(papp),
      simple_list_view(papp)
   {
      m_eview = ViewList;
      m_scrollinfo.m_rectMargin.null();

      m_etranslucency = TranslucencyPresent;

   }
   
   hour_list_view::~hour_list_view()
   {
   }




#ifdef _DEBUG
   void hour_list_view::assert_valid() const
   {
      simple_list_view::assert_valid();
   }

   void hour_list_view::dump(dump_context & dumpcontext) const
   {
      simple_list_view::dump(dumpcontext);
   }
#endif //_DEBUG




   void hour_list_view::install_message_handling(::gen::message::dispatch * pinterface)
   {
      simple_list_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &hour_list_view::_001OnCreate);
   }

   void hour_list_view::_001GetItemText(::user::list_item * pitem)
   {
      pitem->m_strText.Format("%d", pitem->m_iItem);
      pitem->m_bOk = true;
   }
   count hour_list_view::_001GetItemCount()
   {
      return 24;
   }

   void hour_list_view::_001InsertColumns()
   {

      ::user::list_column column;

      column.m_iWidth               = 33;
      column.m_iSubItem             = 0;
      _001AddColumn(column);

   }

   void hour_list_view::_001OnCreate(gen::signal_object * pobj)
   {
      pobj->previous();
      if(pobj->m_bRet)
         return;
      _001UpdateColumns();
      _001OnUpdateItemCount();
   }

   void hour_list_view::_001OnSelectionChange()
   {

      ::user::control_event ev;
      ev.m_puie         = this;
      ev.m_eevent       = ::user::event_after_change_text;
      ev.m_bUser        = true;
      GetParent()->BaseOnControlEvent(&ev);
      BaseOnControlEvent(&ev);

   }

   int hour_list_view::set_hour(int iHour)
   {
      return set_cur_sel(iHour);
   }

   int hour_list_view::get_hour()
   {
      return get_cur_sel();
   }

} // namespace userex


