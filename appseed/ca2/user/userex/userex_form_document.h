#pragma once


class CLASS_DECL_ca2 form_document :
   public html_document
{
public:
   form_document(sp(::ca2::application) papp);

   virtual void OnBeforeNavigate2(html::data * pdata, var & varFile, uint32_t nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, bool* pbCancel);

};



