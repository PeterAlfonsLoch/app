#pragma once


class CLASS_DECL_ca os_exception : public simple_exception
{
public:


   os_exception();
   os_exception(const char * pszMessage);
   virtual ~os_exception();


};

