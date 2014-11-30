#pragma once


class CLASS_DECL_CORE form_document :
   virtual public ::user::document,
   virtual public ::database::client,
   virtual public ::user::form_callback
{
public:
   form_document(::aura::application * papp);

   virtual void OnBeforeNavigate2(::html::data * pdata, var & varFile, uint32_t nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, bool* pbCancel);

};



