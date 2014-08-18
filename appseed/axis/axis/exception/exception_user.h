#pragma once


class CLASS_DECL_AXIS user_exception : 
   virtual public simple_exception   // general ::fontopus::user visible alert
{
public:


   user_exception(sp(::base::application) papp);
   virtual ~user_exception();


};


