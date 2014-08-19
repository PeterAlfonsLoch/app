#pragma once


class CLASS_DECL_BASE last_error_exception :
   virtual public hresult_exception
{
public:

   
   last_error_exception(sp(::axis::application) papp);
   ~last_error_exception();


};


