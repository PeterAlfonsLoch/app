#include "framework.h"



dialog::dialog(const char * pszMatter, sp(::user::interaction) puiParent) :
   element(puiParent->get_app()),
   user::scroll_view(puiParent->get_app()),
   ::user::form_interface(puiParent->get_app()),
   user::form(puiParent->get_app()),
   html_form(puiParent->get_app()),
   html_form_view(puiParent->get_app()),
   form_view(puiParent->get_app())
{
   m_strMatter = pszMatter;
   m_pdocument    = NULL;
   m_pframe       = NULL;
   m_ulFlags      &= ~element::flag_auto_delete;
}


dialog::dialog(sp(::axis::application) papp) :
   element(papp),
   user::scroll_view(papp),
   ::user::form_interface(papp),
   user::form(papp),
   html_form(papp),
   html_form_view(papp),
   form_view(papp)
{
   m_pdocument    = NULL;
   m_pframe       = NULL;
   m_ulFlags      &= ~element::flag_auto_delete;
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


bool dialog::show(const char * pszMatter, property_set  * ppropertyset)
{

   if(pszMatter != NULL && *pszMatter != '\0')
   {
      m_strMatter = pszMatter;
   }

   property_set set(get_app());

   set["hold"] = false;

  m_pdocument = Application.userex()->create_form(this, NULL, platform().get_view(), set);
   if(m_pdocument == NULL)
   {
      string str;
      str.Format("Could not show dialog %s", pszMatter);
      TRACE(str);
      return false;
   }

   if(ppropertyset != NULL)
   {

      m_pdocument->get_html_data()->m_propertyset = *ppropertyset;

   }

   m_pdocument->on_open_document(Application.dir().matter(m_strMatter));

   m_pframe =  (m_pdocument->get_view()->GetParentFrame());
   m_pframe->m_bWindowFrame         = true;
   m_pframe->m_bblur_Background     = true;

   on_position_parent_frame();

   on_show(m_strMatter, &m_pdocument->get_html_data()->m_propertyset);

   m_pframe->RunModalLoop();

   return true;

}

void dialog::on_show(const char * pszMatter, property_set  * ppropertyset)
{

   UNREFERENCED_PARAMETER(pszMatter);

   UNREFERENCED_PARAMETER(ppropertyset);

}

void dialog::EndModalLoop(id nResult)
{

   m_pframe->EndModalLoop(nResult);

   m_pframe->ShowWindow(SW_HIDE);

}







void dialog::on_position_parent_frame()
{
   
   rect rectOpen;
   
   best_monitor(rectOpen);

   int32_t iWidth = rectOpen.width();

   int32_t iHeight = rectOpen.height();

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


void dialog::do_data_exchange(::user::data_exchange * pdx)
{
}


int_bool dialog::on_init_dialog()
{

   return TRUE;

}



CLASS_DECL_CORE void DDX_Control(::user::data_exchange * pdx, id idControl, ::user::interaction & control)
{
}

CLASS_DECL_CORE void DDX_Text(::user::data_exchange * pdx, id idControl, string & str)
{
}

CLASS_DECL_CORE void DDV_MaxChars(::user::data_exchange * pdx, string & str, int32_t iMax)
{
}

CLASS_DECL_CORE void DDX_Check(::user::data_exchange * pdx, id idControl, int32_t & iBool)
{
}

CLASS_DECL_CORE void DDX_Check(::user::data_exchange * pdx, id idControl, bool & b)
{
}


