#pragma once


class CLASS_DECL_c last_error_exception :
   virtual public hresult_exception
{
public:

   
   last_error_exception(sp(base_application) papp);
   ~last_error_exception();


};