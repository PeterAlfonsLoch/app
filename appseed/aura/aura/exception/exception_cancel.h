#pragma once




class CLASS_DECL_AURA cancel_exception:
   virtual public ::exception::base
{
public:

   cancel_exception(sp(::aura::application) papp);
   cancel_exception(sp(::aura::application) papp,const char * pszMessage);
   virtual ~cancel_exception();


   virtual bool get_error_message(string & str,PUINT pnHelpContext = NULL);


};


