//
// Alá Telmo Friesen Son God
//
/////////////////////////////////////////////////////


#include "StdAfx.h"


namespace alatel
{


   week_view::week_view(::ca::application * papp) :
      ca(papp),
      ::userbase::split_layout(papp),
      ::userbase::view(papp),
      ::userbase::split_view(papp),
      place_holder_container(papp)
   {
   }

   week_view::~week_view()
   {
   }

   #ifdef _DEBUG
   void week_view::assert_valid() const
   {
      ::userbase::split_view::assert_valid();
   }

   void week_view::dump(dump_context & dumpcontext) const
   {
      ::userbase::split_view::dump(dumpcontext);
   }

   #endif //_DEBUG


   document * week_view::get_document()
   {
      return dynamic_cast < alatel::document * >(::view::get_document());
   }

   void week_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      split_view::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &week_view::_001OnCreate);
      connect_command("add_alarm", &week_view::_001OnAddAlarm);
      connect_update_cmd_ui("add_alarm", &week_view::_001OnUpdateAddAlarm);
   }


   void week_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
   {
      if(lHint == 2)
      {
         document * pdoc = get_document();
         int iAlarm = get_current_alarm();
         if(iAlarm >= 0)
         {
            ::text_interface * ptext = dynamic_cast < ::text_interface * > (m_pviewWeekday->GetChildById("alarm_name"));
            ptext->_001SetText(pdoc->get_alarm_name("by_weekday", iAlarm));
            m_phourlistview->set_hour(pdoc->get_alarm_hour("by_weekday", iAlarm));
            m_pminutelistview->set_minute(pdoc->get_alarm_minute("by_weekday", iAlarm));
            m_psecondlistview->set_second(pdoc->get_alarm_second("by_weekday", iAlarm));
         }
      }
   
   }


   void week_view::_001OnCreate(gen::signal_object * pobj)
   {
      pobj->previous();
      if(pobj->m_bRet)
         return;
   }

   bool week_view::create_views()
   {

      simple_frame_window * pframe = GetTypedParent < simple_frame_window > ();
      
      pframe->LoadToolBar("by_weekday", "alatel/week.xml");

      SetPaneCount(5);

      SetSplitOrientation(orientation_vertical);
  
      set_position(0, 120);

      create_context cc;
      cc.m_pCurrentDoc = get_document();
      cc.m_typeinfoNewView =  &typeid(alarm_list_view);
      cc.m_pCurrentFrame = this;

      m_palarmlistview = dynamic_cast < alarm_list_view * > (create_view(&cc, this, 100));
      if(m_palarmlistview == NULL)
      {
         Application.simple_message_box(NULL, "Could not create folder tree ::view");
      }
      m_palarmlistview->m_strProfile = "by_weekday";
      SetPane(0, m_palarmlistview, false);


      set_position(1, 550);

      m_pdocWeekday = Application.create_form(this, this);
      if(m_pdocWeekday == NULL)
      {
         Application.simple_message_box(NULL, "Could not create file list ::view");
      }
      m_pviewWeekday = dynamic_cast < form_view *> (m_pdocWeekday->get_view());
      if(m_pviewWeekday == NULL)
      {
         Application.simple_message_box(NULL, "Could not create file list ::view");
      }
      if(m_pviewWeekday->GetParentFrame() == NULL)
      {
         Application.simple_message_box(NULL, "Could not create file list ::view");
      }
      SetPane(1, m_pviewWeekday->GetParentFrame(), false);

      cc.m_typeinfoNewView =  &typeid(::userex::hour_list_view);
      m_phourlistview = dynamic_cast < ::userex::hour_list_view * > (create_view(&cc, this, 100));
      m_phourlistview->m_id = "hour_list";
      set_position(2, 590);
      SetPane(2, m_phourlistview, false);

      cc.m_typeinfoNewView =  &typeid(::userex::minute_list_view);
      m_pminutelistview = dynamic_cast < ::userex::minute_list_view * > (create_view(&cc, this, 100));
      m_pminutelistview->m_id = "minute_list";
      set_position(3, 670);
      SetPane(3, m_pminutelistview, false);

      cc.m_typeinfoNewView =  &typeid(::userex::second_list_view);
      m_psecondlistview = dynamic_cast < ::userex::second_list_view * > (create_view(&cc, this, 100));
      m_psecondlistview->m_id = "second_list";
      SetPane(4, m_psecondlistview, false);


      m_pdocWeekday->open_document(System.dir().matter("alatel/week.html"));

      return true;
   }


   bool week_view::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
   {
      if(pview == m_pviewWeekday)
      {
         return BaseOnControlEvent(pevent);
      }
      return false;
   }
   
   bool week_view::BaseOnControlEvent(::user::control_event * pevent)
   {
      
      if(pevent->m_eevent == ::user::event_after_change_text && pevent->m_bUser)
      {
         document * pdoc = get_document();
         int iAlarm = get_current_alarm();
         if(iAlarm >= 0)
         {
            if(pevent->m_puie->m_id == "alarm_name")
            {
               string str;
               ::text_interface * ptext = dynamic_cast < ::text_interface * > (pevent->m_puie);
               ptext->_001GetText(str);
               pdoc->set_alarm_name("by_weekday", iAlarm, str);
               return true;
            }
            else if(pevent->m_puie->m_id == "hour_list")
            {
               int iHour = m_phourlistview->get_hour();
               pdoc->set_alarm_hour("by_weekday", iAlarm, iHour);
               return true;
            }
            else if(pevent->m_puie->m_id == "minute_list")
            {
               int iMinute = m_pminutelistview->get_minute();
               pdoc->set_alarm_minute("by_weekday", iAlarm, iMinute);
               return true;
            }
            else if(pevent->m_puie->m_id == "second_list")
            {
               int iSecond = m_psecondlistview->get_second();
               pdoc->set_alarm_second("by_weekday", iAlarm, iSecond);
               return true;
            }
         }
      }


      /*
      if(pevent->m_eevent == ::user::event_button_clicked
         || pevent->m_eevent == ::user::event_enter_key)
      {
         if(pevent->m_puie->m_id == "submit" ||
            pevent->m_eevent == ::user::event_enter_key)
         {
            if(m_loginthread.get_os_data() != NULL)
               return true;
            m_pviewAuth->KillTimer(1984);
            if(m_bVotagusAuth)
            {
               m_ptabview->GetParentFrame()->ShowWindow(SW_HIDE);
               ::user::interaction * pguie = m_pviewAuth->GetChildByName("user");
               text_interface * ptext = dynamic_cast < text_interface * > (pguie);
               //m_loginthread.m_puser = dynamic_cast < ::fontopus::user * > (Application.allocate_user());
               ptext->_001GetText(m_loginthread.m_strUsername);
               pguie = m_pviewAuth->GetChildByName("password");
               ptext = dynamic_cast < text_interface * > (pguie);
               ptext->_001GetText(m_loginthread.m_strPassword);
               m_loginthread.m_pcallback = this;
               m_loginthread.Begin();
            }
            else
            {
               m_pauth = new auth;
               ::user::interaction * pguie = m_pviewAuth->GetChildByName("user");
               text_interface * ptext = dynamic_cast < text_interface * > (pguie);
               ptext->_001GetText(m_pauth->m_strUsername);
               pguie = m_pviewAuth->GetChildByName("password");
               ptext = dynamic_cast < text_interface * > (pguie);
               ptext->_001GetText(m_pauth->m_strPassword);
               m_ptabview->m_pwnd->EndModalLoop(IDOK);
               m_ptabview->GetParentFrame()->ShowWindow(SW_HIDE);
            }
            return true;
         }
      }
      else if(pevent->m_eevent == ::user::event_timer
         && pevent->m_uiEvent == 1984)
      {
         string strDir;
         string strUsername;
         string strPasshash;
         Application.crypt().file_get(System.dir().usersystemappdata(System.dir().default_os_user_path_prefix(), "license_auth", "00001.data"), strUsername, "");
         m_loginthread.m_strUsername = strUsername;
         Application.crypt().file_get(System.dir().default_userappdata(System.dir().default_os_user_path_prefix(), strUsername, "license_auth/00002.data"), strPasshash, calc_key_hash());
         if(strUsername.has_char() && strPasshash.has_char())
         {
            m_pviewAuth->KillTimer(1984);
            m_loginthread.m_strPassword.Empty();
            m_loginthread.m_strPasshash = strPasshash;
            m_loginthread.m_pcallback = this;
            m_loginthread.Begin();
         }
         return true;
      }
      return false;

      */

      return false;
   }

   int week_view::get_current_alarm()
   {
      return m_palarmlistview->get_cur_alarm();
   }

   void week_view::_001OnAddAlarm(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      document * pdoc = get_document();      
      pdoc->create_alarm("by_weekday");
   }

   void week_view::_001OnUpdateAddAlarm(gen::signal_object * pobj) 
   {
      SCAST_PTR(base_cmd_ui, pupdatecmdui, pobj)

      pupdatecmdui->m_pcmdui->Enable();
      pupdatecmdui->m_bRet = true;
   }


} // namespace alatel

