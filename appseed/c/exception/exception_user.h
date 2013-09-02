#pragma once


class CLASS_DECL_c user_exception : 
   virtual public simple_exception   // general ::fontopus::user visible alert
{
public:


   user_exception(sp(::application) papp);
   virtual ~user_exception();


};


