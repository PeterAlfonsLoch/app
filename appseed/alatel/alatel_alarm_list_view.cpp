//
// Alá Telmo Friesen Son God
//
/////////////////////////////////////////////////////


#include "stdafx.h"


namespace alatel
{


   alarm_list_view::alarm_list_view(::ca::application * papp) :
      ca(papp),
      userbase::view(papp),
      user::scroll_view(papp),
      user::form(papp),
      user::list(papp),
      user::form_list(papp),
      userbase::form_list(papp),
      simple_list_view(papp)
   {
      m_scrollinfo.m_rectMargin.null();
   }
   
   alarm_list_view::~alarm_list_view()
   {
   }


#ifdef _DEBUG
   void alarm_list_view::assert_valid() const
   {
      ::simple_list_view::assert_valid();
   }

   void alarm_list_view::dump(dump_context & dumpcontext) const
   {
      ::simple_list_view::dump(dumpcontext);
   }
#endif //_DEBUG

   document * alarm_list_view::get_document()
   {
      return dynamic_cast < alatel::document * >(::view::get_document());
   }


   void alarm_list_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      simple_list_view::install_message_handling(pinterface);
      USER_MESSAGE_LINK(message_create, pinterface, this, &alarm_list_view::_001OnCreate);

      connect_command("delete_alarm" , &alarm_list_view::_001OnDeleteAlarm);
      connect_update_cmd_ui("delete_alarm" , &alarm_list_view::_001OnUpdateDeleteAlarm);

   }

   void alarm_list_view::_001GetItemText(::user::list_item * pitem)
   {
      pitem->m_strText = get_document()->get_alarm_name(m_strProfile, pitem->m_iItem);
      return_(pitem->m_bOk, true);
   }
   count alarm_list_view::_001GetItemCount()
   {
      return get_document()->get_alarm_count(m_strProfile);
   }

   void alarm_list_view::_001InsertColumns()
   {

      ::user::list_column column;

      column.m_iWidth               = 100;
      column.m_iSubItem             = 0;
      _001AddColumn(column);

   }

   void alarm_list_view::_001OnCreate(gen::signal_object * pobj)
   {
      pobj->previous();
      if(pobj->m_bRet)
         return;
      _001UpdateColumns();
      _001OnUpdateItemCount();
   }

   void alarm_list_view::_001OnDeleteAlarm(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      _001RemoveSelection();
   }

   void alarm_list_view::_001OnUpdateDeleteAlarm(gen::signal_object * pobj) 
   {
      SCAST_PTR(base_cmd_ui, pupdatecmdui, pobj)

      Range range;

      _001GetSelection(range);

      pupdatecmdui->m_pcmdui->Enable(range.get_item_count() > 0);
      pupdatecmdui->m_bRet = true;
   }


   bool alarm_list_view::_001OnRemoveItem(index iItem)
   {
      ::alatel::document * pdoc = dynamic_cast < ::alatel::document * > (get_document());
      return pdoc->remove_alarm(m_strProfile, iItem);
   }

   void alarm_list_view::_001OnSelectionChange()
   {
      get_document()->update_all_views(NULL, 2);
   }

   int alarm_list_view::set_cur_alarm(int iAlarm)
   {
      return set_cur_sel(iAlarm);
   }

   int alarm_list_view::get_cur_alarm()
   {
      return get_cur_sel();
   }

   void alarm_list_view::_001OnInitialUpdate(gen::signal_object * pobj)
   {
      layout();
   }

   void alarm_list_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
   {
      ::simple_list_view::on_update(pSender, lHint, phint);

      if(pSender == NULL && lHint == 0 && phint == NULL)
      {
         _001OnUpdateItemCount();
         layout();
      }
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(phint);
      if(lHint == 2)
      {
      }
   
   }


} // namespace alatel


