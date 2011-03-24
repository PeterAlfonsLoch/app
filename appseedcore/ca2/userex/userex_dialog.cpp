#include "StdAfx.h"

dialog::dialog(::ca::application * papp) :
   ca(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::userbase::scroll_view(papp),
   ::userbase::form_view(papp),
   form(papp),
   html_form(papp),
   html_form_view(papp),
   form_view(papp)
{
   m_pdocument    = NULL;
   m_pframe       = NULL;
   m_ulFlags      &= ~::ca::ca::flag_auto_delete;
}

dialog::~dialog()
{
}


bool dialog::show(const char * pszMatter, gen::property_set & propertyset)
{

   m_pdocument = System.create_form(this, this, System.m_puiInitialPlaceHolderContainer);
   if(m_pdocument == NULL)
   {
      string str;
      str.Format("Could not show dialog %s", pszMatter);
      TRACE(str);
      return false;
   }
   m_pdocument->get_html_data()->m_propertyset = propertyset;
   
   m_pdocument->on_open_document(System.dir().matter(pszMatter));
   
   m_pcallback = this;
   m_pframe = dynamic_cast < simple_frame_window * > (GetParentFrame());
   m_pframe->m_bCustomFrame      = true;
   m_pframe->m_bblur_Background  = true;

   on_position_parent_frame();

   on_show(pszMatter, m_pdocument->get_html_data()->m_propertyset);

   m_pframe->RunModalLoop();
   m_pframe->DestroyWindow();
   return true;
}

void dialog::on_show(const char * pszMatter, gen::property_set & propertyset)
{
   UNREFERENCED_PARAMETER(pszMatter);
   UNREFERENCED_PARAMETER(propertyset);
}

void dialog::EndModalLoop(int nResult)
{
   GetTopLevelFrame()->EndModalLoop(nResult);
   GetParentFrame()->ShowWindow(SW_HIDE);
}







void dialog::on_position_parent_frame()
{
   rect rectOpen;
   System.get_screen_rect(rectOpen);
   int iWidth = rectOpen.width();
   int iHeight = rectOpen.width();
   rectOpen.deflate(iWidth / 5, iHeight / 5);
   m_pframe->SetWindowPos(ZORDER_TOP, rectOpen.left,
      rectOpen.top,
      rectOpen.width(), rectOpen.height(), SWP_SHOWWINDOW);
   m_pframe->RedrawWindow();

}

void dialog::OnCancel()
{
}

void dialog::OnOK()
{
}

void dialog::form_from_user()
{
}

void dialog::form_to_user()
{
}