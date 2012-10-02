#pragma once


class CLASS_DECL_ca user_exception : 
   virtual public simple_exception   // general ::fontopus::user visible alert
{
public:


   user_exception(::ca::application * papp);
   virtual ~user_exception();


};


