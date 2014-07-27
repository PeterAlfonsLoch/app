#include "framework.h"


namespace userex
{


   hour_list_view::hour_list_view(sp(::base::application) papp) :
      element(papp),
      user::scroll_view(papp),
      user::form(papp),
      user::list(papp),
      user::form_list(papp),
      simple_list_view(papp)
   {

      m_eview = ViewList;
      
      m_scrollinfo.m_rectMargin.null();

   }
   
   hour_list_view::~hour_list_view()
   {

   }




   void hour_list_view::assert_valid() const
   {
      simple_list_view::assert_valid();
   }

   void hour_list_view::dump(dump_context & dumpcontext) const
   {
      simple_list_view::dump(dumpcontext);
   }




   void hour_list_view::install_message_handling(::message::dispatch * pinterface)
   {
      simple_list_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &hour_list_view::_001OnCreate);
   }

   void hour_list_view::_001GetItemText(::user::list_item * pitem)
   {
      pitem->m_strText.Format("%d", pitem->m_iItem);
      pitem->m_bOk = true;
   }
   ::count hour_list_view::_001GetItemCount()
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

   void hour_list_view::_001OnCreate(signal_details * pobj)
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
      ev.m_actioncontext   = ::action::source_user;
      GetParent()->BaseOnControlEvent(&ev);
      BaseOnControlEvent(&ev);

   }

   int32_t hour_list_view::set_hour(int32_t iHour)
   {
      return (int32_t) set_cur_sel(iHour);
   }

   int32_t hour_list_view::get_hour()
   {
      return (int32_t) get_cur_sel();
   }

} // namespace userex


