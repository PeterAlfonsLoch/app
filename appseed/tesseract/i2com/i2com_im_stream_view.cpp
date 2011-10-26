#include "StdAfx.h"

namespace i2com
{

   im_stream_view::im_stream_view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp), 
      ::userbase::view(papp),
      ::user::scroll_view(papp),
      ::userbase::scroll_view(papp),
      ::userbase::form_view(papp),
      user::form(papp),
      html_form(papp)
   {
      connect_update_cmd_ui("edit_undo", &im_stream_view::_001OnUpdateEditUndo);
      connect_command("edit_undo", &im_stream_view::_001OnEditUndo);
      connect_update_cmd_ui("edit_redo", &im_stream_view::_001OnUpdateEditRedo);
      connect_command("edit_redo", &im_stream_view::_001OnEditRedo);

      LOGFONT lf;

      memset(&lf, 0, sizeof(lf));
      lf.lfHeight = 16;
      strcpy(lf.lfFaceName, "Courier New");
      
   }

   im_stream_view::~im_stream_view()
   {
   }



   #ifdef _DEBUG
   void im_stream_view::assert_valid() const
   {
      ::html_form::assert_valid();
   }

   void im_stream_view::dump(dump_context & dumpcontext) const
   {
      ::html_form::dump(dumpcontext);
   }
   #endif //_DEBUG

   void im_stream_view::on_update(::view * pSender, LPARAM lHint, ::radix::object * phint) 
   {
      ::html_form::on_update(pSender, lHint, phint);
      if(lHint == 1001)
      {
         _001RedrawWindow();
      }
      /*xxx if(phint != NULL)
      {
         if(base < PaneViewUpdateHint >::bases(phint))
         {
            PaneViewUpdateHint * puh = (PaneViewUpdateHint * ) phint;
            if(puh->is_type_of(PaneViewUpdateHint::TypeOnBeforeShowView))
            {
               get_document()->on_save_document(get_document()->get_path_name());
            }
            else if(puh->is_type_of(PaneViewUpdateHint::TypeOnShowView))
            {
               get_document()->reload();
            }
         }
      }*/
      
   }

   void im_stream_view::_001OnContextMenu(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
    //  SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
//      int iItem;
  //    HRESULT hr;
      //point point = pmouse->m_pt;
      point point;
      System.get_cursor_pos(&point);
      class point ptClient = point;
      ClientToScreen(&point);
      //ScreenToClient(&ptClient);
      ::userbase::menu menu(get_app());
      ex1::text_file_sp spfile(get_app());

      string strModuleFolder;
      strModuleFolder = System.get_module_folder();

      if(!spfile->open(System.dir().path(strModuleFolder, "devedge_contextmenu.xml"), ::ex1::file::type_text | ::ex1::file::mode_read))
         return;

      string str;
      spfile->read_full_string(str);

      xml::node node(get_app());

      node.load(str);

      if (menu.LoadMenu(&node))
      {
         //::userbase::menu* pPopup = (::userbase::menu_item *) menu.GetSubMenu(0);
         //ASSERT(pPopup != NULL);
         userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > ( dynamic_cast < ::ca::window * > (GetParentFrame()));
         //pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
           // point.x, point.y,
            //(::ca::window *) pframe);
         menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
            point.x, point.y,
            pframe);
      }
   }

   document * im_stream_view::get_document() const
   {
      return dynamic_cast < document * > (::html_form::get_document());
   }

   void im_stream_view::_001OnUpdateEditUndo(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      //pcmdui->m_pcmdui->Enable(m_pdata->m_editfile.CanUndo());
   }

   void im_stream_view::_001OnUpdateEditRedo(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      //pcmdui->m_pcmdui->Enable(m_pdata->m_editfile.GetRedoBranchCount() > 0);
   }

   void im_stream_view::_001OnEditUndo(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
    //  Undo();
   }

   void im_stream_view::_001OnEditRedo(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
    //  Redo();
   }

   void im_stream_view::_001OnAfterChangeText()
   {
//      ::userbase::edit_plain_text_view::_001OnAfterChangeText();
      get_document()->set_modified_flag(TRUE);
   }

   void im_stream_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::html_form::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &im_stream_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &im_stream_view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &im_stream_view::_001OnTimer);
   }

   void im_stream_view::_001OnCreate(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::user::win::message::create, pcreate, pobj);
      SetTimer(23, 1000, NULL);
   }

   void im_stream_view::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj);
      if(ptimer->m_nIDEvent == 23)
      {
         get();
         update();
      }
   }

   void im_stream_view::update()
   {
      if(m_recStart.is_empty())
      {
         m_recStart = Application.db().im_post().last(ApplicationUser.m_strFunUserId, m_pimview->m_strRecipient);
      }
      var varList = Application.db().im_post().get_since(m_recStart);
      string strHtml;
      for(int i = 0; i < varList.vara().get_count(); i++)
      {
         var & varItem = varList.vara()[i];
         strHtml += "<span style=\"color: #888888;\">";
         strHtml += varItem["sender"];
         strHtml += "&nbsp;:&nbsp;</span>";
         string strMessage = varItem["message"];
         strHtml += strMessage;
         strHtml += "<br />";
      }
      _001SetText(strHtml);
   }

   void im_stream_view::get()
   {
      string strPath;
      var rec = Application.db().im_post().last(ApplicationUser.m_strFunUserId, m_pimview->m_strRecipient);
      rec.propset(get_app())["user"] = m_pimview->m_strRecipient;
      strPath = "http://i2com.api.veriterse.net/get?"
         + string("sessid=")
         + ApplicationUser.get_sessid("i2com.api.veriterse.net") + "&" + rec.propset().get_http_post();
      string str = Application.http().get(strPath);
      str.trim();
      if(str.has_char())
      {
         xml::document doc(get_app());
         doc.load(str);
         xml::node & node = *doc.get_root();
         string strThread;
         if(node.m_strName == "messages")
         {
            for(int i = 0; i < node.get_children_count(); i++)
            {
               xml::node * pnodeMessage = node.child_at(i);
               string strSender;
               string strBody;
               xml::node * pnodeSender = pnodeMessage->get_child("sender");
               if(pnodeSender != NULL)
                  strSender = pnodeSender->m_strValue;
//               int iLength = strSender.get_length();
               xml::node * pnodeBody = pnodeMessage->get_child("body");
               if(pnodeBody != NULL)
               {
                  strBody = pnodeBody->m_strValue;
                  if(pnodeMessage->m_strName == "message")
                  {
                     strBody = pnodeBody->m_strValue;
                     pnodeBody->attrs()["message"] = strBody;
                     pnodeBody->attrs()["name"] = "message";
                     Application.db().im_post().write(pnodeBody->attrs());
                     strThread += strSender + " : " + strBody + "\r\n";
                  }
                  else if(pnodeMessage->m_strName == "invite")
                  {
                     if(pnodeBody->attrs()["sender"] == m_pimview->m_pcommview->m_strRecipient)
                     {
                        pnodeBody->attrs()["message"] = "<a href=\"i2com://" + pnodeBody->attrs()["senderaddress"] + "/10.10.101.101:3000/\">" + pnodeBody->attrs()["senderaddress"] + " is inviting for a phone session.</a>";
                        pnodeBody->attrs()["name"] = "invite";
                     }
                     else
                     {
                        pnodeBody->attrs()["message"] = "Invitation sent";
                        pnodeBody->attrs()["name"] = "invitation_sent";
                     }
                     Application.db().im_post().write(pnodeBody->attrs());

   /*                  string strPath;
                     strPath = "http://i2com.api.veriterse.net/post";
                     System.url().set(strPath, "topic", "invite");
               //    System.url().set(strPath, "message", System.url().url_encode(strInviteNode));
                     System.url().set(strPath, "recipient", m_pcommview->m_strRecipient);
                     string str = Application.http().get(strPath);*/


                     /*xml::node nodeInvite(get_app());
                     node.load(strBody);
                     string strSenderAddress = node.attrs()["senderaddress"];
                     strThread += "invite from "+ strSender;
                     update();
                     //post(strThread);
                     //post("trying to accept...");
                     int iPort = Application.open_rtprx(strSenderAddress, 3000);
//                     post("trying to accept...");
/*                     int iPort = Application.open_rtprx(NULL, -1);
                     if(iPort < 0)
                     {
                        //post("failed to open receive channel");
                        return;
                     }
                     strPath = "http://i2com.api.veriterse.net/accept_invitation?"
                       + string("sessid=")
                       + "&rtprx_port=" + gen::str::itoa(iPort);
                       + "&user=" + strSender;
                     string str = Application.http().get(strPath);
                     //post("failed to open receive channel");*/
                  }
                  else if(pnodeMessage->m_strName == "invitation_accepted")
                  {
                     if(pnodeBody->attrs()["sender"] == m_pimview->m_pcommview->m_strRecipient)
                     {
                        if(m_pimview->m_pcommview->m_bSentInvitation)
                        {
                           pnodeBody->attrs()["message"] = "Invitation accepted by recipient";
                           pnodeBody->attrs()["name"] = "invitation_accepted_by_recipient";
                           Application.start_rtptx(pnodeBody->get_child("invitation_accepted")->attrs()["senderaddress"], 3000, 1);
                        }
                        else
                        {
                           pnodeBody->attrs()["message"] = "";
                           pnodeBody->attrs()["name"] = "no_paired_invitation_accepted_by_recipient";
                        }
                     }
                     else
                     {
                        pnodeBody->attrs()["message"] = "Invitation accepted by me";
                        pnodeBody->attrs()["name"] = "invitation_accepted_by_me";
                     }
                     Application.db().im_post().write(pnodeBody->attrs());
                  }
               }
            }
            if(strThread.get_length() > 0)
            {
//               post(strThread);
            }
         }
      }
   }


   void im_stream_view::OnBeforeNavigate2(var & varFile, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel)
   {
      string strPath(varFile);
      if(gen::str::begins_eat(strPath, "i2com://"))
      {
         string strDst = strPath.Left(strPath.find("/"));
         string strSrc = strPath.Mid(strPath.find("/") + 1);
         string strDstHost = strDst.Left(strDst.find(":"));
         string strSrcHost = strSrc.Left(strSrc.find(":"));

         string strPath;
         strPath = "http://i2com.api.veriterse.net/post";
         System.url().set(strPath, "topic", "invitation_accepted");
         System.url().set(strPath, "recipient", m_pimview->m_pcommview->m_strRecipient);
         string str = Application.http().get(strPath);

         Application.open_rtprx("0.0.0.0", 3000);

         *pbCancel = TRUE;
      }

   }

} // namespace i2com