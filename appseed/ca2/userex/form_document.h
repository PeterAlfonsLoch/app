#pragma once

class CLASS_DECL_ca form_document :
   virtual public html_document
{
public:
   form_document(::ax::application * papp);

   virtual void OnBeforeNavigate2(html::data * pdata, var & varFile, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel);

};
