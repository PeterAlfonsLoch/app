#pragma once

class CLASS_DECL_ca2 menu_document :
   virtual public form_document
{
public:
   menu_document(::ca::application * papp);

   virtual void OnBeforeNavigate2(html::data * pdata, var & varFile, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, bool* pbCancel);

};