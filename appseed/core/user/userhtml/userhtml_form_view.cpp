#include "framework.h"


html_form_view::html_form_view(sp(::base::application) papp) :
   element(papp),
   html_form(papp),
   ::user::interaction(papp),
   ::user::scroll_view(papp),
   ::user::form_interface(papp),
   ::user::form(papp)
{

}


html_form_view::~html_form_view()
{

}


void html_form_view::install_message_handling(::message::dispatch * pinterface)
{

   html_form::install_message_handling(pinterface);

   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &html_form_view::_001OnDestroy);
//   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &html_form_view::_001OnSize);

//   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &html_form_view::_001OnTabClick);
   //connect_command(ID_FILE_PRINT, html_form::OnFilePrint)
   //connect_command(ID_FILE_PRINT_DIRECT, html_form::OnFilePrint)
   //connect_command(ID_FILE_PRINT_PREVIEW, html_form::OnFilePrintPreview)
//   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
//   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
   IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);

//   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &html_form_view::_001OnLButtonDown);
  // IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &html_form_view::_001OnMouseMove);
   //IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &html_form_view::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &html_form_view::_001OnKeyDown);
   IGUI_WIN_MSG_LINK(WM_SETFOCUS, pinterface, this, &html_form_view::_001OnSetFocus);
   IGUI_WIN_MSG_LINK(WM_KILLFOCUS, pinterface, this, &html_form_view::_001OnKillFocus);
//   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &html_form_view::_001OnCreate);

}
/////////////////////////////////////////////////////////////////////////////
// html_form_view drawing

void html_form_view::OnDraw(::draw2d::graphics * pdcScreen)
{
   UNREFERENCED_PARAMETER(pdcScreen);
}

/////////////////////////////////////////////////////////////////////////////
// html_form_view diagnostics

void html_form_view::assert_valid() const
{
   html_form::assert_valid();
}

void html_form_view::dump(dump_context & dumpcontext) const
{
   html_form::dump(dumpcontext);
}

/////////////////////////////////////////////////////////////////////////////
// html_form_view message handlers

// vmpLightView.cpp : implementation of the html_form_view class
//


bool html_form_view::pre_create_window(CREATESTRUCT& cs)
{
   cs.style &= ~WS_EX_CLIENTEDGE;
   return html_form::pre_create_window(cs);
}
void html_form_view::_001OnInitialUpdate(signal_details * pobj)
{

   html_form::_001OnInitialUpdate(pobj);

}


void html_form_view::on_update(sp(::user::impact) pSender, LPARAM lHint, object* phint)
{
   UNREFERENCED_PARAMETER(pSender);
   UNREFERENCED_PARAMETER(lHint);
   if(phint != NULL)
   {
      html_view_update_hint * puh = dynamic_cast < html_view_update_hint * >
         (phint);
      if(puh != NULL)
      {
         if(puh->m_etype == html_view_update_hint::type_document_complete)
         {
            ASSERT(get_html_data() != NULL);

            defer_implement();

            _001InitializeFormPreData();

            _001UpdateFunctionStatic();

            for(int32_t i = 0; i < m_controldescriptorset.get_size(); i++)
            {
               sp(::user::control) pcontrol = m_controldescriptorset[i].m_pcontrol;
               if(pcontrol != NULL)
               {
                  _001Update(pcontrol);
               }
            }

            defer_layout();

            on_document_complete(puh->m_strUrl);

            GetParentFrame()->SetActiveView(this);

            SetFocus();

         }
      }
   }


}


string html_form_view::GetLocationURL()
{
   return m_strPath;
}

bool html_form_view::Refresh2(int32_t i)
{
   UNREFERENCED_PARAMETER(i);
   get_document()->on_open_document(GetLocationURL());
   return true;
}

bool html_form_view::Navigate(const char * pszUrl)
{
   ASSERT(FALSE);
/*   if(!open_document(pszUrl))
      return false;*/
   m_strPath = pszUrl;
   return true;
}

void html_form_view::on_document_complete(const char * pszUrl)
{
   UNREFERENCED_PARAMETER(pszUrl);
}


void html_form_view::_001OnSetFocus(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   if(get_html_data()->m_focusptra.get_size() > 0)
   {
      session().user()->set_keyboard_focus(get_html_data()->m_focusptra[0]);
   }
}

void html_form_view::_001OnKillFocus(signal_details * pobj)
{

   UNREFERENCED_PARAMETER(pobj);

}

