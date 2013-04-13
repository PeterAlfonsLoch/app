#pragma once


class CLASS_DECL_ca2 last_error_exception :
   virtual public hresult_exception
{
public:

   
   last_error_exception(sp(::ca::application) papp);
   ~last_error_exception();


};