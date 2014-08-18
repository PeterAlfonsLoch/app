#pragma once


class CLASS_DECL_BASE user_exception : 
   virtual public simple_exception   // general ::fontopus::user visible alert
{
public:


   user_exception(sp(::base::application) papp);
   virtual ~user_exception();


};


