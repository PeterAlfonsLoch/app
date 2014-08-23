#include "framework.h"


menu_document::menu_document(sp(::aura::application) papp) :
   element(papp),
   ::data::data_container_base(papp),
   ::user::document(papp),
   html_document(papp),
   form_document(papp)
{
}


void menu_document::OnBeforeNavigate2(::html::data * pdata, var & varFile, uint32_t nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, bool* pbCancel)
{
   form_document::OnBeforeNavigate2(pdata, varFile, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
}


