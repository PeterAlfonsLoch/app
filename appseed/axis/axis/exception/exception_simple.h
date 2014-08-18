#pragma once




class CLASS_DECL_AXIS simple_exception : 
   virtual public ::exception::axis
{
public:
   
   
   simple_exception(sp(::axis::application) papp);
   simple_exception(sp(::axis::application) papp, const char * pszMessage);
   virtual ~simple_exception();


   virtual bool get_error_message(string & str, PUINT pnHelpContext = NULL);


};


