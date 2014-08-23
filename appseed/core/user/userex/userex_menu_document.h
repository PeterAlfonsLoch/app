#pragma once

class CLASS_DECL_CORE menu_document :
   virtual public form_document
{
public:
   menu_document(sp(::aura::application) papp);

   virtual void OnBeforeNavigate2(::html::data * pdata, var & varFile, uint32_t nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, bool* pbCancel);

};