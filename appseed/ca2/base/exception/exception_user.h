#pragma once


class CLASS_DECL_ca2 user_exception : 
   virtual public simple_exception   // general ::fontopus::user visible alert
{
public:


   user_exception(sp(::ca2::application) papp);
   virtual ~user_exception();


};


