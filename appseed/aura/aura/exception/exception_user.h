#pragma once


class CLASS_DECL_AURA user_exception : 
   virtual public simple_exception   // general ::fontopus::user visible alert
{
public:


   user_exception(sp(::aura::application) papp);
   virtual ~user_exception();


};


