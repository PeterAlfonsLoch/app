#include "framework.h"


form_document::form_document(sp(::aura::application) papp) :
   element(papp),
   ::data::data_container_base(papp),
   ::user::document(papp),
   html_document(papp)
{
}

void form_document::OnBeforeNavigate2(::html::data * pdata, var & varFile, uint32_t nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, bool* pbCancel)
{

   UNREFERENCED_PARAMETER(pdata);
   string strUrl(varFile);
   if(::str::begins_eat(strUrl, "ext://"))
   {
      Application.open_link(strUrl, lpszTargetFrameName);
/*         simple_shell_launcher launcher(NULL, "open", strUrl, "", "", SW_SHOWNORMAL);
         launcher.execute();*/

      *pbCancel = true;
      return;
   }
   if(::str::begins_eat(strUrl, "hist://"))
   {
      System.hist().hist(strUrl);
      *pbCancel = true;
      return;
   }
   if(get_html_data()->m_pform != NULL
      && get_html_data()->m_pform->m_pcallback != NULL
      && get_html_data()->m_pform->m_pcallback != dynamic_cast < ::user::form_callback * > (this))
   {
      get_html_data()->m_pform->m_pcallback->OnBeforeNavigate2(get_html_data(), varFile, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
   }

}


