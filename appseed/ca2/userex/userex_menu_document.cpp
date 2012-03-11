#include "StdAfx.h"


menu_document::menu_document(::ca::application * papp) :
   ca(papp),
   form_document(papp)
{
}


void menu_document::OnBeforeNavigate2(html::data * pdata, var & varFile, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel)
{
   form_document::OnBeforeNavigate2(pdata, varFile, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
}


