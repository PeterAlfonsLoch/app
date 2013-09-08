#pragma once




class CLASS_DECL_c simple_exception : 
   virtual public ::exception::base
{
public:
   
   
   simple_exception(sp(base_application) papp);
   simple_exception(sp(base_application) papp, const char * pszMessage);
   virtual ~simple_exception();


   virtual const char * get_error_message () const throw ();


};


