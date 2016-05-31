#pragma once


class CLASS_DECL_AURA last_error_exception :
   virtual public hresult_exception
{
public:

   
   last_error_exception(::aura::application * papp);
   ~last_error_exception();


};


