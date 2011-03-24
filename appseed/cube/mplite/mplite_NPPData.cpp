#include "StdAfx.h"


CNPPData::CNPPData(::ca::application * papp) :
   ca(papp)
{
   m_hwndParent = NULL;
   m_pdoctemplate = NULL;   
   m_pdoc = NULL;
}

CNPPData::~CNPPData()
{

}

bool CNPPData::open_document_file(HWND hwnd, const char * lpcsz)
{
   if(m_pdoctemplate == NULL)
      if(!CreateDocTemplate())
         return false;
   if(m_pdoc == NULL)
   {
      m_pdoc = dynamic_cast < document * > (m_pdoctemplate->open_document_file(lpcsz, false));
      if(m_pdoc == NULL)
         return false;
   }
   frame_window * pframe = GetFrame();
   if(pframe == NULL)
      return false;
   pframe->SetParent(System.window_from_os_data(hwnd));
   pframe->ModifyStyle(
      WS_CAPTION
      | WS_OVERLAPPED
      | WS_THICKFRAME,
      WS_CHILD,
      SWP_SHOWWINDOW);
   pframe->ModifyStyleEx(
      WS_EX_CLIENTEDGE,
      WS_EX_TOOLWINDOW,
      SWP_SHOWWINDOW);
   ::view * pview = GetView();
   if(pview == NULL)
      return false;
   pview->ModifyStyleEx(
      WS_EX_CLIENTEDGE,
      0,
      SWP_SHOWWINDOW);
   return true;
}

bool CNPPData::CreateDocTemplate()
{
   m_pdoctemplate = new musctrl::single_document_template(
      get_app(),
      "mplite/mainframe",
      &typeid(mplite::document),
      &typeid(InlineFrame),
      &typeid(mplite::pane_view));
   musctrl::MusicalPlayerCentralContainer::AppGetMusicalPlayerCentral(get_app()).m_pdoctemplate = m_pdoctemplate;
   if(m_pdoctemplate == NULL)
      return false;
   else
      return true;
}

frame_window * CNPPData::GetFrame()
{
   if(m_pdoc == NULL)
      return NULL;
   ::view * pview = m_pdoc->get_view();
   if(pview == NULL)
      return NULL;
   frame_window * pframe = pview->GetParentFrame();
   if(pframe == NULL)
      return NULL;
   return pframe;
}

::view * CNPPData::GetView()
{
   if(m_pdoc == NULL)
      return NULL;
   ::view * pview = m_pdoc->get_view();
   if(pview == NULL)
      return NULL;
   return dynamic_cast < ::view * > (pview);
}

bool CNPPData::OpenPlayerFile(const char * lpcszFilePath)
{
   if(lpcszFilePath != NULL)
   {
      gen::international::AcpToUtf8(m_strFilePath, lpcszFilePath);
   }
   if(m_hwndParent == NULL)
      return false;
   ::view * pview = (::view *) GetView();
   if(pview == NULL)
   {
      open_document_file(m_hwndParent, NULL);
      UpdateWindowPos();
      pview = (::view *) GetView();
   }
   if(!m_strFilePath.is_empty())
   {
      //const char * lpcsz = m_strFilePath;
      return m_pdoctemplate->open_document_file(m_strFilePath) != NULL;
   }
   return false;
}

void CNPPData::UpdateWindowPos()
{
   frame_window * pframe = GetFrame();
   if(pframe != NULL)
   {
      pframe->SetWindowPos(
         ZORDER_TOP,
         0, 0,
         m_rectLast.width(),
         m_rectLast.height(),
         SWP_SHOWWINDOW);
   }

}
