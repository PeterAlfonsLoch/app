#include "framework.h"


namespace ca8
{


   network_configuration::network_configuration(::ca::application * papp) :
      ca(papp)
   {
      m_pdoc   = NULL;
      m_pview  = NULL;
   }

   network_configuration::~network_configuration()
   {
   }

   bool network_configuration::initialize(::user::interaction * puiParent)
   {
      m_pdoc = Cube.create_form(this, puiParent);
      if(m_pdoc != NULL)
      {
         m_pview = m_pdoc->get_typed_view < form_view > ();
         m_pview->m_pcallback = this;
         return true;
      }
      return false;
   }

   bool network_configuration::initialize_child(::user::interaction * puiParent)
   {
      m_pdoc = Cube.create_child_form(this, puiParent);
      if(m_pdoc != NULL)
      {
         m_pview = m_pdoc->get_typed_view < form_view > ();
         m_pview->m_pcallback = this;
         return true;
      }
      return false;
   }

   void network_configuration::on_show()
   {
      if(!m_pdoc->on_open_document(Application.dir().matter("system/network/configuration/proxy.xhtml")))
      {
         return;
      }

      xml::document doc(get_app());

      if(doc.load(System.file_as_string(&System, System.dir().appdata("proxy.xml"))))
      {
         string strProxy = doc.get_root()->attr("server");
         int iProxyPort = doc.get_root()->attr("port");
         ::user::interaction * pguie = m_pview->GetChildByName("server");
         text_interface * ptext = dynamic_cast < text_interface * > (pguie);
         ptext->_001SetText(strProxy);
         pguie = m_pview->GetChildByName("port");
         ptext = dynamic_cast < text_interface * > (pguie);
         ptext->_001SetText(gen::str::itoa(iProxyPort));
      }

   }

  bool network_configuration::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
  {
      UNREFERENCED_PARAMETER(pview);
      if(pevent->m_eevent == ::user::event_button_clicked)
      {
         if(pevent->m_puie->m_id == "submit")
         {
            ::user::interaction * pguie = m_pview->GetChildByName("server");
            text_interface * ptext = dynamic_cast < text_interface * > (pguie);
            //m_loginthread.m_puser = dynamic_cast < ::fontopus::user * > (System.allocate_user());
            string strServer;
            ptext->_001GetText(strServer);
            if(strServer.get_length() == 0)
            {
               ::DeleteFile(System.dir().appdata("proxy.xml"));
            }
            else
            {
               xml::document doc(get_app());
               doc.get_root()->set_name("proxy");
               doc.get_root()->add_attr("server", strServer);
               pguie = m_pview->GetChildByName("port");
               ptext = dynamic_cast < text_interface * > (pguie);
               string strPort;
               ptext->_001GetText(strPort);
               doc.get_root()->add_attr("port", strPort);
               Application.file().put_contents(System.dir().appdata("proxy.xml"), doc.get_xml());
            }
         }
      }

      return false;

   }


} // namespace ca8


