#include "StdAfx.h"


namespace tesseract
{

   namespace simpledbcfg
   {


      simpledb::simpledb(application * papp) :
         ca(papp),
         ip_enum(papp)
      {
         m_papp = papp;
         m_ptemplatePane = new ::userbase::single_document_template(
            papp,
            "system/form",
            ::ca::get_type_info < form_document > (),
            ::ca::get_type_info < simple_frame_window > (),
            ::ca::get_type_info < userex::pane_tab_view > ());
      }

      simpledb::~simpledb()
      {
      }

      void simpledb::set_configuration()
      {
         ip_enum::enumerate();
         ::ca::create_context_sp cc(get_app());
         form_document * pdoc = dynamic_cast < form_document * > (m_ptemplatePane->open_document_file(cc));
         userex::pane_tab_view * pview = pdoc->get_typed_view < userex::pane_tab_view > ();
         pview->set_view_creator(this);
         HWND hwndDesktop = ::GetDesktopWindow();
         rect rectOpen;
         ::GetWindowRect(hwndDesktop, rectOpen);
         /*int iWidth = rectOpen.width();
         int iHeight = rectOpen.width();
         rectOpen.deflate(iWidth / 5, iHeight / 5);
         /*pview->GetParentFrame()->SetWindowPos(ZORDER_TOP, rectOpen.left,
            rectOpen.top,
            rectOpen.width(), rectOpen.height(), SWP_SHOWWINDOW);*/
         m_ptabview = pview;
         pview->add_tab("main", 1);
	     pview->add_tab("database", 2);
         pview->set_cur_tab_by_id(1);
         pview->GetTopLevelFrame()->RunModalLoop();
      }

      void simpledb::on_create_view(::user::view_creator_data * pcreatordata)
      {
	      pcreatordata->m_eflag.signalize(::user::view_creator_data::flag_hide_all_others_on_show);
         switch(pcreatordata->m_id)
         {
         case 1:
            {
			 
               m_mapdoc["server"] = System.create_form(this, m_ptabview);
               if(m_mapdoc["server"] != NULL)
               {
                  m_mapview["server"] = m_mapdoc["server"]->get_typed_view < form_view > ();
                  m_mapview["server"]->m_pcallback = this;

                  string strIpEnum = System.file().time_square();

                  string str;
                  string strHtml;
                  strHtml = "<html><head></head><body>";
                  strHtml += "<h1>simpledb main configuration</h1>";
                  strHtml += "<h2>fontopus server</h2>";
                  string strFontopusServer = System.db().data_load("fontopus_server", ::database::id(), ::database::id()); 
                  str.Format("<input type=\"text\" id=\"fontopus_server\" value=\"%s\"/>", strFontopusServer);
                  strHtml += str;
                  strHtml += "<br/>";
                  strHtml += "<br/>";
                  strHtml += "<h2>HTTP</h2>";
                  stringa stra;
                  string strCheck;
                  stra = System.db().data_load("simpledb", ::database::id(), ::database::id()); 
                  for(int i = 0; i < m_straIp.get_size(); i++)
                  {
                     if(stra.contains(m_straIp[i]))
                        strCheck = "checked";
                     else
                        strCheck = "unchecked";

                     str.Format("<input type=\"checkbox\" id=\"check%d\" value=\"%s\"/>%s<br /><br />", i, strCheck, m_straIp[i]);
                     strHtml += str;
                  }
                  strHtml += "<h2>HTTPS</h2>";
                  stra.remove_all();
                  stra = System.db().data_load("netnodes", ::database::id(), ::database::id()); 
                  for(int i = 0; i < m_straIp.get_size(); i++)
                  {
                     if(stra.contains(m_straIp[i]))
                        strCheck = "checked";
                     else
                        strCheck = "unchecked";


                     string strCert = System.db().data_load("netnodec", m_straIp[i], ::database::id()); 

                     str.Format("<input type=\"checkbox\" id=\"scheck%d\" value=\"%s\"/>%s<input type=\"text\" id=\"cert%d\" value=\"%s\"/><br /><br />", i, strCheck, m_straIp[i], i, strCert);
                     strHtml += str;
                  }
                  strHtml += "<input type=\"button\" id=\"submit\" value=\"Fechar\"/>";
                  strHtml += "</body></html>";

                  Application.file().put_contents(strIpEnum, strHtml);


                  m_mapview["server"]->get_html_data()->open_document(strIpEnum);
                  pcreatordata->m_pdoc = m_mapdoc["server"];
                  pcreatordata->m_pwnd = m_mapview["server"]->GetParentFrame();

               }
            }
            break;
         case 2:
            {
			 

			    m_mapdoc["database"] = System.create_form(this, m_ptabview);
               if(m_mapdoc["database"] != NULL)
               {
                  m_mapview["database"] = m_mapdoc["database"]->get_typed_view < form_view > ();
                  m_mapview["database"]->m_pcallback = this;

                  string strIpEnum = System.file().time_square();

                  string str;
                  string strHtml;
                  strHtml = "<html><head></head><body>";
                  strHtml += "<h1>simpledb database configuration</h1>";
                  strHtml += "<h2>database server</h2>";
                  string strDatabaseServer = System.db().data_load("database_server", ::database::id(), ::database::id()); 
                  str.Format("<input type=\"text\" id=\"database_server\" value=\"%s\"/>", strDatabaseServer);
                  strHtml += str;
                  strHtml += "<br/>";
                  strHtml += "<br/>";
                  strHtml += "<input type=\"button\" id=\"submit\" value=\"Fechar\"/>";
                  strHtml += "</body></html>";

                  Application.file().put_contents(strIpEnum, strHtml);


                  m_mapview["database"]->get_html_data()->open_document(strIpEnum);
                  pcreatordata->m_pdoc = m_mapdoc["database"];
                  pcreatordata->m_pwnd = m_mapview["database"]->GetParentFrame();

               }
            }
            break;
         }
      }



      bool simpledb::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
      {
         UNREFERENCED_PARAMETER(pview);
         if(pevent->m_eevent == ::user::event_button_clicked)
         {
		   if(pevent->m_puie->m_id == "submit")
		   {
		     if(pview == m_mapview["server"])
		     {
				   string str;
				   stringa straSubmit;
				   for(int i = 0; i < m_straIp.get_size(); i++)
				   {
				      str.Format("check%d", i);
				      ::user::interaction * pguie = m_mapview["server"]->GetChildById(str);
				      ::user::check_interface * pcheck = dynamic_cast < ::user::check_interface * > (pguie);
				      if(pcheck->_001GetCheck() == check::checked)
				      {
					     straSubmit.add(m_straIp[i]);
				      }
				   }
				   System.db().data_save("simpledb", ::database::id(), ::database::id(), straSubmit);
				   straSubmit.remove_all();
				   for(int i = 0; i < m_straIp.get_size(); i++)
				   {
				      str.Format("scheck%d", i);
				      ::user::interaction * pguie = m_mapview["server"]->GetChildById(str);
				      ::user::check_interface * pcheck = dynamic_cast < ::user::check_interface * > (pguie);
				      if(pcheck->_001GetCheck() == check::checked)
				      {
					     straSubmit.add(m_straIp[i]);
				      }
				      string strCert;
				      str.Format("cert%d", i);
				      pguie = m_mapview["server"]->GetChildById(str);
				      ::text_interface * ptext = dynamic_cast < ::text_interface * > (pguie);
				      ptext->_001GetText(strCert);
				      System.db().data_save("netnodec", m_straIp[i], ::database::id(), strCert);
				   }
				   System.db().data_save("netnodes", ::database::id(), ::database::id(), straSubmit);
				   ::user::interaction * pguie = m_mapview["server"]->GetChildById("fontopus_server");
				   ::text_interface * ptext = dynamic_cast < ::text_interface * > (pguie);
				   string strFontopusServer;
				   ptext->_001GetText(strFontopusServer);
				   System.db().data_save("fontopus_server", ::database::id(), ::database::id(), strFontopusServer);
				   m_mapview["server"]->GetTopLevelParent()->EndModalLoop(IDOK);
				   m_mapview["server"]->GetTopLevelParent()->ShowWindow(SW_HIDE);
			    }
			     else if(pview == m_mapview["database"])
			     {
					   ::user::interaction * pguie = m_mapview["database"]->GetChildById("database_server");
					   ::text_interface * ptext = dynamic_cast < ::text_interface * > (pguie);
					   string strFontopusServer;
					   ptext->_001GetText(strFontopusServer);
					   System.db().data_save("database_server", ::database::id(), ::database::id(), strFontopusServer);
					   m_mapview["database"]->GetTopLevelParent()->EndModalLoop(IDOK);
					   m_mapview["database"]->GetTopLevelParent()->ShowWindow(SW_HIDE);
			     }
		   }
         }
         return false;
      }


      void simpledb::OnBeforeNavigate2(html::data * pdata, var & varFile, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel)
      {
         UNREFERENCED_PARAMETER(pdata);
         UNREFERENCED_PARAMETER(nFlags);
         UNREFERENCED_PARAMETER(lpszTargetFrameName);
         UNREFERENCED_PARAMETER(baPostedData);
         UNREFERENCED_PARAMETER(lpszHeaders);
         string str(varFile);
         if(gen::str::begins_eat(str, "simpledbcfg://"))
         {
            m_mapview["server"]->GetTopLevelParent()->EndModalLoop(IDOK);
            m_mapview["server"]->GetTopLevelParent()->ShowWindow(SW_HIDE);
            *pbCancel = TRUE;
         }
      }

      BOOL simpledb::EnumCallbackFunction(int nAdapter, const in_addr& address)
      {
         UNREFERENCED_PARAMETER(nAdapter);
         string strIpAddress = inet_ntoa(address);
         m_straIp.add(strIpAddress);
         return TRUE;
      }


   } // namespace simpledbcfg


} // namespace tesseract


