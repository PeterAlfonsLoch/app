#pragma once


class CLASS_DECL_ca os_exception : public simple_exception
{
public:


   os_exception();
   os_exception(const char * pszMessage);
   os_exception(bool bAutoDelete);
   os_exception(bool bAutoDelete, UINT nResourceID);
   virtual ~os_exception();


};

