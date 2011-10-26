#include "StdAfx.h"

namespace userex
{

   namespace autocomplete
   {

      interaction::interaction(::ca::application * papp) :
         ca(papp)
      {
         m_phandler = NULL;
      }

      void interaction::install_message_handling(::user::win::message::dispatch * pinterface)
      {
         IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &interaction::_001OnCreate);
      }

      void interaction::autocomplete_set_text(const char * pszText)
      {
         UNREFERENCED_PARAMETER(pszText);
      }

      void interaction::_001OnCreate(gen::signal_object * pobj)
      {
         UNREFERENCED_PARAMETER(pobj);
         m_phandler = new handler(this);
      }



      handler::handler(interaction * pinteraction) :
         ::ca::ca(pinteraction->get_app()),
         m_pinteraction(pinteraction)
      {
         m_pdocument       = NULL;
         m_pformview       = NULL;
         m_bUpdatingForm   = false;
      }

      handler::~handler()
      {
      }


      void handler::ensure_main_document()
      {
         if(m_pdocument != NULL)
            return;
         /*m_pdocument = System.create_form(this, NULL);
         if(m_pdocument != NULL)
         {
            m_pformview = m_pdocument->get_typed_view < form_view > ();
            m_pformview->m_pcallback = this;
         }*/
      }



      bool handler::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
      {
         UNREFERENCED_PARAMETER(pview);
         UNREFERENCED_PARAMETER(pevent);
         return false;
      }



      void handler::set_text(const char * pszText)
      {
         UNREFERENCED_PARAMETER(pszText);
         ensure_main_document();
         if(m_pformview == NULL)
            return;

         string strIpEnum = System.file().time_square();

         string str;
         string strHtml;
         strHtml = "<html><head></head><body>";
         strHtml += "<a href=\"http://x-square.xpressions.net/test/html/table/index.html\" style=\"font-size: 30;\">Table Test HTML</a>";
         strHtml += "</body></html>";

         Application.file().put_contents(strIpEnum, strHtml);

         keeper < bool > keepUpdatingForm(&m_bUpdatingForm, true, false, true);
         m_pdocument->open_document(strIpEnum);
         keepUpdatingForm.KeepAway();

         class rect rectWindow;
         m_pinteraction->GetWindowRect(rectWindow);
         if(rectWindow.is_null())
            m_pformview->GetParentFrame()->ShowWindow(SW_HIDE);
         else
         {
            m_pformview->GetParentFrame()->SetWindowPos(
               ZORDER_TOPMOST,
               System.m_monitorinfoa[0].rcMonitor.left,
               rectWindow.bottom,
               System.m_monitorinfoa[0].rcMonitor.right - System.m_monitorinfoa[0].rcMonitor.left,
               484,
               SWP_SHOWWINDOW);
            m_pformview->layout();
            m_pformview->GetParentFrame()->layout();
         }

      }

      void handler::OnBeforeNavigate2(html::data * pdata, var & varFile, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel)
      {
         UNREFERENCED_PARAMETER(pdata);
         UNREFERENCED_PARAMETER(nFlags);
         UNREFERENCED_PARAMETER(lpszTargetFrameName);
         UNREFERENCED_PARAMETER(baPostedData);
         UNREFERENCED_PARAMETER(lpszHeaders);
         if(m_bUpdatingForm)
            return;
         *pbCancel = true;
         m_pformview->GetParentFrame()->ShowWindow(SW_HIDE);
         m_pinteraction->autocomplete_set_text(varFile);
      }

   } // namespace autocomplete

} // namespace userex

