#pragma once




class CLASS_DECL_AURA simple_exception : 
   virtual public ::exception::base
{
public:
   
   simple_exception(::ace::application * papp);
   simple_exception(::ace::application * papp, const char * pszMessage);
   virtual ~simple_exception();


   virtual bool get_error_message(string & str, PUINT pnHelpContext = NULL);


};


