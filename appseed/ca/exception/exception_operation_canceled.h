#pragma once


class CLASS_DECL_ca operation_canceled_exception : public simple_exception
{
public:


   operation_canceled_exception();
   operation_canceled_exception(const char * pszMessage);
   operation_canceled_exception(bool bAutoDelete);
   operation_canceled_exception(bool bAutoDelete, UINT nResourceID);
   virtual ~operation_canceled_exception();


};

