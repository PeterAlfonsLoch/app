#pragma once


class CLASS_DECL_ca user_exception : public simple_exception   // general ::fontopus::user visible alert
{
   
public:
   user_exception();

// Implementation
public:
   explicit user_exception(bool bAutoDelete);
   user_exception(bool bAutoDelete, UINT nResourceID);
   virtual ~user_exception();
};


