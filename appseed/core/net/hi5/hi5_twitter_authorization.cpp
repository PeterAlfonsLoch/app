#include "framework.h"
//#include <openssl/rsa.h>
//#include <openssl/engine.h>
//#include <openssl/err.h>


//typedef string ( *SALT)(sp(::aura::application), const char * , stringa &);

namespace hi5
{

   namespace twitter
   {

      authorization::authorization(sp(::aura::application) papp, const char * pszAuthorizationUrl, const char * pszForm, bool bAuth, bool bInteractive) :
         element(papp)
      {
         m_strAuthorizationUrl=pszAuthorizationUrl;
         m_bInteractive    = bInteractive;
         m_bAuth    = bAuth;
         m_strForm         = pszForm;
         m_ptemplatePane   = new ::user::single_document_template(
            papp,
            "system/auth",
            System.type_info < form_document > (),
            System.type_info < simple_frame_window > (),
            System.type_info < userex::pane_tab_view > ());
         m_pviewAuth       = NULL;
         m_pdocAuth        = NULL;
         m_pdoc            = NULL;
         m_ptabview        = NULL;
      }

      authorization::~authorization()
      {
      }

      string authorization::get_pin()
      {
         ensure_main_document();
         page1();

         if(m_pviewAuth == NULL)
            return "";

         m_pviewAuth->SetTimer(8888, 484, NULL);
         m_ptabview->GetWindow()->RunModalLoop(MLF_NOIDLEMSG | MLF_NOKICKIDLE);
         m_ptemplatePane->close_all_documents(FALSE);
         return m_strPin;
      }

      void authorization::ensure_main_document()
      {
         if(m_pdoc != NULL)
            return;
         sp(create_context) createcontext(allocer());
         createcontext->m_bMakeVisible = false;
         createcontext->m_puiParent = Sys(get_app()).oprop("top_parent").cast < ::user::interaction > ();
         createcontext->m_bOuterPopupAlertLike = true;

         m_pdoc = (m_ptemplatePane->open_document_file(createcontext));

         if(m_pdoc == NULL)
            return;

         sp(userex::pane_tab_view) pview = m_pdoc->get_typed_view < userex::pane_tab_view >();
         pview->set_view_creator(this);
         m_ptabview = pview;
         pview->add_tab("ca2open", 1);
         pview->set_cur_tab_by_id(1);
      }


      void authorization::page1()
      {

         if(m_pdocAuth == NULL)
            return;

         string strUrl;
         strUrl = "http://spaignition.api.server.ca2.cc/query?node=install_application&id=";
         string strAppName;
         if(System.m_strAppName == "winactionarea")
         {
            strAppName = "_set_windesk";
         }
         else
         {

            strAppName = System.m_strAppName;
         
         }

         strUrl += strAppName;

         strUrl += "&key=name";

         property_set set(get_app());

         m_pdocAuth->get_html_data()->m_propertyset["application_name"] = System.http().get(strUrl, set);

         m_pdocAuth->get_html_data()->m_propertyset["authorization_link"] = m_strAuthorizationUrl;

         if(m_strLicense.is_empty())
         {

            m_pdocAuth->get_html_data()->m_propertyset["reason"] = "Authenticating";

         }
         else
         {

            m_pdocAuth->get_html_data()->m_propertyset["reason"] = "Licensing";

         }
         
         if(!m_pdocAuth->on_open_document(Application.dir().matter(m_strForm)))
         {

            return;

         }

         ::html::elemental * pelemental = m_pdocAuth->get_html_data()->get_element_by_id("authorization_link");

         ::html::impl::text * ptext = dynamic_cast < ::html::impl::text * > (pelemental->m_pimpl);

         ptext->m_strLink = "ext://" + m_strAuthorizationUrl;

         ptext->m_bLink = true;

         display_main_frame();

      }


      void authorization::display_main_frame()
      {
         
         rect rectOpen;

         m_ptabview->GetParentFrame()->best_top_level_parent(rectOpen);

         int32_t iWidth = rectOpen.width();

         int32_t iHeight = rectOpen.height();

         rectOpen.deflate(iWidth / 5, iHeight / 50);

         rectOpen.top = iHeight * 2 / 3;

         sp(simple_frame_window) pframe = m_pviewAuth->GetParentFrame();

         if(pframe != NULL)
         {

            pframe->m_puserschema = this;
            
            m_etranslucency = ::user::TranslucencyPresent;

            pframe->m_bblur_Background = true;

         }

         if(&Bergedge != NULL && Platform.get_document() != NULL && Platform.get_document()->get_bergedge_view() != NULL)
         {

            Platform.get_document()->get_bergedge_view()->ShowWindow(SW_SHOW);

         }
         else
         {

            m_ptabview->GetTopLevelFrame()->ShowWindow(SW_SHOW);

         }

         m_ptabview->GetParentFrame()->SetWindowPos(
            ZORDER_TOP,
            rectOpen.left, rectOpen.top,
            rectOpen.width(), rectOpen.height(),
            SWP_SHOWWINDOW);

         m_pviewAuth->GetParentFrame()->SetForegroundWindow();

         m_pviewAuth->GetParentFrame()->BringWindowToTop();

      }

      void authorization::pageMessage(const char * pszMatter, property_set & set)
      {
         ensure_main_document();
         m_pdocAuth->get_html_data()->m_propertyset = set;
         m_pdocAuth->on_open_document(Application.dir().matter(pszMatter));
         display_main_frame();
         m_ptabview->GetWindow()->RunModalLoop(MLF_NOIDLEMSG | MLF_NOKICKIDLE);
         m_ptabview->GetWindow()->EndAllModalLoops(IDOK);
      }

      void authorization::on_create_view(::user::view_creator_data * pcreatordata)
      {
         switch(pcreatordata->m_id)
         {
         case 1:
            {
               m_pdocAuth = Platform.userex()->create_child_form(this, pcreatordata->m_pholder);
               if(m_pdocAuth != NULL)
               {
                  m_pviewAuth = m_pdocAuth->get_typed_view < form_view > ();
                  m_pviewAuth->m_pcallback = this;
                  pcreatordata->m_pdoc = m_pdocAuth;
                  pcreatordata->m_pwnd = m_pviewAuth->GetParentFrame();
               }
            }
            break;

            break;
         }
         if(pcreatordata->m_pwnd != NULL)
         {
            pcreatordata->m_eflag.signalize(::user::view_creator_data::flag_hide_all_others_on_show);
         }

      }
      void authorization::on_show_view()
      {
         switch(get_view_id())
         {
         case 1:
            {
            }
            break;

         }
      }








      bool authorization::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
      {
         UNREFERENCED_PARAMETER(pview);
         if(pevent->m_eevent == ::user::event_button_clicked
            || pevent->m_eevent == ::user::event_enter_key)
         {
            if(pevent->m_puie->m_id == "submit" ||
               pevent->m_eevent == ::user::event_enter_key)
            {
               sp(::user::interaction) pui = m_pviewAuth->get_child_by_name("pin");
               sp(text_interface) ptext =  (pui.m_p);
               ptext->_001GetText(m_strPin);
               m_ptabview->GetWindow()->EndModalLoop(IDOK);
               m_ptabview->GetParentFrame()->ShowWindow(SW_HIDE);
            }
         }
         return false;
      }


   } // namespace twitter


} // namespace hi5




