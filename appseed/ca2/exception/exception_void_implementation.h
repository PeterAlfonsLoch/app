#pragma once


class CLASS_DECL_ca void_implementation_exception : public not_implemented_exception
{
public:

   void_implementation_exception(const char * pszTip = NULL);
   void_implementation_exception(const void_implementation_exception & e);
   virtual ~void_implementation_exception();
};
