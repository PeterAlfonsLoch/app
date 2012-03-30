#include "StdAfx.h"

dialog::dialog(::ca::application * papp) :
   ca(papp)
{
   m_pdocument    = NULL;
   m_pframe       = NULL;
   m_ulFlags      &= ~::ca::ca::flag_auto_delete;
}

dialog::~dialog()
{
   if(m_pdocument != NULL)
   {
      m_pdocument->on_close_document();
      m_pdocument = NULL;
   }
   if(m_pframe != NULL)
   {
//      m_pframe->DestroyWindow();
     // m_pframe = NULL;
   }
}


bool dialog::show(const char * pszMatter, gen::property_set & propertyset)
{

   gen::property_set set(get_app());

   set["hold"] = false;

   m_pdocument = Application.create_form(this, Bergedge.get_view(), set);
   if(m_pdocument == NULL)
   {
      string str;
      str.Format("Could not show dialog %s", pszMatter);
      TRACE(str);
      return false;
   }
   m_pdocument->get_html_data()->m_propertyset = propertyset;
   
   m_pdocument->on_open_document(Application.dir().matter(pszMatter));
   
   m_pframe = dynamic_cast < simple_frame_window * > (m_pdocument->get_view()->GetParentFrame());
   m_pframe->m_bWindowFrame         = true;
   m_pframe->m_bblur_Background     = true;
   m_pframe->m_etranslucency        = ::user::interaction::TranslucencyPresent;

   on_position_parent_frame();

   on_show(pszMatter, m_pdocument->get_html_data()->m_propertyset);

   m_pframe->RunModalLoop();

   return true;

}

void dialog::on_show(const char * pszMatter, gen::property_set & propertyset)
{
   UNREFERENCED_PARAMETER(pszMatter);
   UNREFERENCED_PARAMETER(propertyset);
}

void dialog::EndModalLoop(id nResult)
{
   m_pframe->EndModalLoop(nResult);
   m_pframe->ShowWindow(SW_HIDE);
}







void dialog::on_position_parent_frame()
{
   rect rectOpen;
   Bergedge.get_screen_rect(rectOpen);
   int iWidth = rectOpen.width();
   int iHeight = rectOpen.height();
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