#pragma once


class CLASS_DECL_ACE last_error_exception :
   virtual public hresult_exception
{
public:

   
   last_error_exception(::ace::application * papp);
   ~last_error_exception();


};


