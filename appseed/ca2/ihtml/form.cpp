#include "StdAfx.h"


namespace ihtml
{

form::form()
{
}

form::~form()
{
}

void form::_001OnDraw(CDC * pdc)
{
   rect rectClient;
   _001GetWnd()->GetClientRect(rectClient);
   pdc->FillSolidRect(rectClient, RGB(240, 240, 255));
   //m_document._001OnDraw(pdc);
}


void form::_001InstallMessageHandling(igui::win::message::Dispatch * pinterface)
{
   IGUI_WIN_MSG_LINK(WM_SIZE, this, this, &form::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_CREATE, this, this, &form::_001OnCreate);

   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN    , this, this, &Ex1VirtualGuieInterface::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP    , this, this, &Ex1VirtualGuieInterface::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN    , this, this, &Ex1VirtualGuieInterface::_001OnKeyDown);
   IGUI_WIN_MSG_LINK(WM_KEYUP    , this, this, &Ex1VirtualGuieInterface::_001OnKeyUp);
   IGUI_WIN_MSG_LINK(WM_TIMER    , this, this, &Ex1VirtualGuieInterface::_001OnTimer);

   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN    , this, this, &form::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE      , this, this, &form::_001OnMouseMove);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP      , this, this, &form::_001OnLButtonUp);

}


bool form::OpenDocument(const char * lpszPathName)
{
   string strPathName(lpszPathName);
   if(strPathName.Mid(3) == "wb:")
      return FALSE;
   string str = ca2::app(get_app()).file().as_string(lpszPathName);
   if(str.is_empty())
   {
      ca36::app(get_app()).sync_load_url(str, lpszPathName, ca2::app(get_app()).user().get_user(), m_pcookies);
   }
   m_strPathName = lpszPathName;
   //m_document.m_strPathName = m_strPathName;
   //m_document.load(str);
   //m_document.m_papp = get_app();
   Layout();
   return TRUE;

}


void form::Layout()
{
   //_001GetWnd()->GetClientRect(&m_document.m_rect);
   /*bool bLayoutOk = false;
   if(m_document.m_rect.Width() > 0 &&
      m_document.m_rect.Height() > 0)
   {
      bLayoutOk = true;
   }
   CDC * pdc = _001GetWnd()->GetDC();
   m_document.m_pguie = this;
   m_document.m_pwnd = _001GetWnd();
   m_document.implement(pdc);
   if(bLayoutOk)
   {
      m_document.layout(pdc);
   }
   ReleaseDC(pdc);
   if(bLayoutOk)
   {
      _001RedrawWindow();
   }*/

}


void form::_001OnSize(gen::signal_object * pobj)
{
   Layout();
}

  void form::_001OnCreate(gen::signal_object * pobj)
  {
     SCAST_PTR(igui::win::message::create, pcreate, pobj)
      if(!m_strOpenOnCreate.is_empty() && !OpenDocument(m_strOpenOnCreate))
      {
         pcreate->set_lresult(-1);
         pcreate->m_bRet = true;
         return;
      }
      return;
  }



  void form::_001OnLButtonDown(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj);
   /*m_pelementalLButtonDown = m_document.m_elemental.hit_test(pmouse->m_pt);
   if(m_pelementalLButtonDown != NULL)
   {
      html::signal signal(pobj->m_psignal);
      signal.m_pdoccontainer = this;
      signal.m_psignal = pmouse;
      m_pelementalLButtonDown->OnLButtonDown(&signal);
   }*/
}

void form::_001OnMouseMove(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj);
   /*html::elemental *pelemental = m_document.m_elemental.hit_test(pmouse->m_pt);
   if(pelemental != NULL)
   {
      html::signal signal(pobj->m_psignal);
      signal.m_pdoccontainer = this;
      signal.m_psignal = pmouse;
      pelemental->OnMouseMove(&signal);
   }*/
}

void form::_001OnLButtonUp(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj);
   /*html::elemetal * pelemental = m_document.m_elemental.hit_test(pmouse->m_pt);
   if(m_pelementalLButtonDown != NULL
      && pelemental == m_pelementalLButtonDown)
   {
      html::signal signal(pobj->m_psignal);
      signal.m_pdoccontainer = this;
      signal.m_psignal = pmouse;
      m_pelementalLButtonDown->OnLButtonUp(&signal);
   }*/
}



bool form::open_document(const char * pszPath)
{
   return OpenDocument(pszPath);
}

} // namespac eihtml