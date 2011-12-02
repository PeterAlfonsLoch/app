#include "StdAfx.h"

html_form_view::html_form_view(::ax::application * papp) :
   ax(papp),
   html_form(papp),
   ::user::interaction(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::userbase::scroll_view(papp),
   ::user::form(papp),
   ::userbase::form_view(papp)
{
}

html_form_view::~html_form_view()
{
}

void html_form_view::install_message_handling(::gen::message::dispatch * pinterface)
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

void html_form_view::OnDraw(::ax::graphics * pdcScreen)
{
   UNREFERENCED_PARAMETER(pdcScreen);
}

/////////////////////////////////////////////////////////////////////////////
// html_form_view diagnostics

#ifdef _DEBUG
void html_form_view::assert_valid() const
{
   html_form::assert_valid();
}

void html_form_view::dump(dump_context & dumpcontext) const
{
   html_form::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// html_form_view message handlers

// vmpLightView.cpp : implementation of the html_form_view class
//


BOOL html_form_view::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.lpszClass = System.RegisterWndClass(
      CS_DBLCLKS |
      CS_OWNDC,
      0, 0, 0);
   cs.style &= ~WS_EX_CLIENTEDGE;
   return html_form::PreCreateWindow(cs);
}
void html_form_view::_001OnInitialUpdate(gen::signal_object * pobj)
{
   html_form::_001OnInitialUpdate(pobj);

   if(get_html_data() != NULL)
   {
      GetClientRect(&get_html_data()->m_rect);
      if(get_html_data()->m_rect.width() > 0 &&
         get_html_data()->m_rect.height() > 0)
      {
         ::ax::graphics * pdc = GetDC();
         get_html_data()->layout(pdc);
         ReleaseDC(pdc);
         _001RedrawWindow();
      }
   }
}


void html_form_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint)
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
            bool bLayoutOk = false;
            ::ax::graphics * pdc = NULL;
            if(get_html_data() != NULL)
            {
               GetClientRect(&get_html_data()->m_rect);
               GetClientRect(&get_html_data()->m_rect);
               if(get_html_data()->m_rect.width() > 0 &&
                  get_html_data()->m_rect.height() > 0)
               {
                  bLayoutOk = true;
               }
               pdc = GetDC();
               get_html_data()->m_pguie = this;
               get_html_data()->implement(pdc);
               _001InitializeFormPreData();
               /*   ::view * pview = dynamic_cast <::view *>(get_guie());
                  if(pview != NULL)
                  {
                     if(pview->get_document() != NULL)
                     {
                        pview->get_document()->update_all_views(NULL);
                     }
                  }*/
               _001UpdateFunctionStatic();
               //   CVmsGuiApp * papp = (CVmsGuiApp *) &System;
               //   papp->TwfInitializeDescendants(pview->GetSafeHwnd(), true);
               for(int i = 0; i < m_controldescriptorset.get_size(); i++)
               {
                  user::control * pcontrol = m_controldescriptorset[i].m_pcontrol;
                  if(pcontrol != NULL)
                  {
                     _001Update(pcontrol);
                  }
               }
            }
            if(bLayoutOk)
            {
               get_html_data()->layout(pdc);
            }
            if(pdc != NULL)
            {
               ReleaseDC(pdc);
               pdc = NULL;
            }
            if(bLayoutOk)
            {
               _001RedrawWindow();
            }
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

bool html_form_view::Refresh2(int i)
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


void html_form_view::_001OnSetFocus(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   if(get_html_data()->m_focusptra.get_size() > 0)
   {
      Application.set_keyboard_focus(get_html_data()->m_focusptra[0]);
   }
}

void html_form_view::_001OnKillFocus(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
}

html::data * html_form_view::calc_data()
{
   if(m_spdata.m_p != NULL)
   {
      return dynamic_cast < html::data * > (m_spdata.m_p);
   }
   else if(get_document() != NULL)
   {
      html::data * pcontainer = dynamic_cast < html::data * > (get_document()->get_data());
      if(pcontainer != NULL)
         return pcontainer;
   }
   return html_form::calc_data();
}
