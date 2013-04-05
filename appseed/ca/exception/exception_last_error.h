#pragma once


class CLASS_DECL_ca last_error_exception :
   virtual public hresult_exception
{
public:

   
   last_error_exception(::ca::applicationsp papp);
   ~last_error_exception();


};