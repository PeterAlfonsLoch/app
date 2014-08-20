#include "framework.h"

namespace user
{

   network_configuration::network_configuration(sp(::axis::application) papp) :
      element(papp)
   {
//      m_pdoc   = NULL;
  //    m_pview  = NULL;
   }

   network_configuration::~network_configuration()
   {
   }

   bool network_configuration::initialize(sp(::user::interaction) puiParent)
   {
      /*m_pdoc = System.userex()->create_form(this, puiParent);
      if(m_pdoc != NULL)
      {
         m_pview = m_pdoc->get_typed_view < form_view > ();
         m_pview->m_pcallback = this;
         return true;
      }*/
      return false;
   }

   bool network_configuration::initialize_child(sp(::user::interaction) puiParent)
   {
      /*
      m_pdoc = Session.user()->create_child_form(this, puiParent);
      if(m_pdoc != NULL)
      {
         m_pview = m_pdoc->get_typed_view < form_view > ();
         m_pview->m_pcallback = this;
         return true;
      }*/
      return false;
   }

   void network_configuration::on_show()
   {
      /*
      if(!m_pdoc->on_open_document(Application.dir().matter("system/network/configuration/proxy.xhtml")))
      {
         return;
      }
      xml::node node(get_app());
      if(node.load(System.file_as_string(&System, System.dir().appdata("proxy.xml"))))
      {
         string strProxy = node.attr("server");
         int32_t iProxyPort = node.attr("port");
         sp(::user::interaction) pui = m_pview->get_child_by_name("server");
         sp(text_interface) ptext =  (pui);
         ptext->_001SetText(strProxy, false);
         pui = m_pview->get_child_by_name("port");
         ptext =  (pui);
         ptext->_001SetText(::str::from(iProxyPort), false);
      }*/
   }

//  bool network_configuration::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
  //{
     /*
      UNREFERENCED_PARAMETER(pview);
      if(pevent->m_eevent == ::user::event_button_clicked)
      {
         if(pevent->m_puie->m_id == "submit")
         {
            sp(::user::interaction) pui = m_pview->get_child_by_name("server");
            sp(text_interface) ptext =  (pui);
            //m_loginthread.m_puser = dynamic_cast < ::fontopus::user * > (System.allocate_user());
            string strServer;
            ptext->_001GetText(strServer);
            if(strServer.get_length() == 0)
            {
               ::DeleteFile(System.dir().appdata("proxy.xml"));
            }
            else
            {
               xml::node node(get_app());
               node.m_strName = "proxy";
               node.add_attr("server", strServer);
               pui = m_pview->get_child_by_name("port");
               ptext =  (pui);
               string strPort;
               ptext->_001GetText(strPort);
               node.add_attr("port", strPort);
               Application.file().put_contents(System.dir().appdata("proxy.xml"), node.get_xml());
            }
         }
      }*/
    //  return false;
   //}



} // namespace user
