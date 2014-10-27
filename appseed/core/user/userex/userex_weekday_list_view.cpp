#include "framework.h"


namespace userex
{


   weekday_list_view::weekday_list_view(sp(::aura::application) papp):
      element(papp),
      ::user::scroll_view(papp),
      ::user::form_interface(papp),
      user::form(papp),
      user::list(papp),
      user::form_list(papp),
      simple_list_view(papp)
   {

      m_eview = ViewList;

      m_scrollinfo.m_rectMargin.null();

   }

   weekday_list_view::~weekday_list_view()
   {

   }




   void weekday_list_view::assert_valid() const
   {
      simple_list_view::assert_valid();
   }

   void weekday_list_view::dump(dump_context & dumpcontext) const
   {
      simple_list_view::dump(dumpcontext);
   }




   void weekday_list_view::install_message_handling(::message::dispatch * pinterface)
   {
      simple_list_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE,pinterface,this,&weekday_list_view::_001OnCreate);
   }

   
   void weekday_list_view::_001GetItemText(::user::list_item * pitem)
   {
      
      pitem->m_strText = System.datetime().get_week_day_str(Session.str_context(),pitem->m_iItem + 1);
      
      pitem->m_bOk = true;

   }


   ::count weekday_list_view::_001GetItemCount()
   {
      
      return 7;

   }


   void weekday_list_view::_001InsertColumns()
   {

      ::user::list_column column;

      column.m_iWidth               = 120;
      column.m_iSubItem             = 0;
      _001AddColumn(column);

   }

   void weekday_list_view::_001OnCreate(signal_details * pobj)
   {
      pobj->previous();
      if(pobj->m_bRet)
         return;
      _001UpdateColumns();
      _001OnUpdateItemCount();
   }

   void weekday_list_view::_001OnSelectionChange()
   {

      ::user::control_event ev;
      ev.m_puie         = this;
      ev.m_eevent       = ::user::event_after_change_text;
      ev.m_actioncontext   = ::action::source_user;
      GetParent()->BaseOnControlEvent(&ev);
      BaseOnControlEvent(&ev);

   }

   
   void weekday_list_view::set_weekday(const int_array & iaWeekday)
   {

      index_array ia = iaWeekday;

      set_cur_sel(ia);

   }


   int_array weekday_list_view::get_weekday()
   {

      index_array ia;
      
      get_cur_sel(ia);


      return ia;

   }


} // namespace userex




































