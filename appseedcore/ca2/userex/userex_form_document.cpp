#include "StdAfx.h"

form_document::form_document(::ca::application * papp) :
   ca(papp),
   data_container(papp),
   ::document(papp),
   ::userbase::document(papp),
   html_document(papp)
{
}

void form_document::OnBeforeNavigate2(html::data * pdata, const char * lpszUrl, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel)
{
   string strUrl(lpszUrl);
   if(gen::str::begins_eat(strUrl, "ext://"))
   {
      ::ShellExecute(NULL, "open", strUrl, "", "", SW_SHOWNORMAL);
      *pbCancel = true;
      return;
   }
   if(gen::str::begins_eat(strUrl, "hist://"))
   {
      System.hist().hist(strUrl);
      *pbCancel = true;
      return;
   }
   if(get_html_data()->m_pform != NULL
      && get_html_data()->m_pform->m_pcallback != NULL
      && get_html_data()->m_pform->m_pcallback != dynamic_cast < ::user::form_callback * > (this))
   {
      get_html_data()->m_pform->m_pcallback->OnBeforeNavigate2(get_html_data(), lpszUrl, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
   }
}

