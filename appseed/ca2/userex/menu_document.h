#pragma once

class CLASS_DECL_ca menu_document :
   virtual public form_document
{
public:
   menu_document(::ax::application * papp);

   virtual void OnBeforeNavigate2(html::data * pdata, var & varFile, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel);

};