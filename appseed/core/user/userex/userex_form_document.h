#pragma once


class CLASS_DECL_CORE form_document :
   virtual public html_document
{
public:
   form_document(sp(::axis::application) papp);

   virtual void OnBeforeNavigate2(::html::data * pdata, var & varFile, uint32_t nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, bool* pbCancel);

};



