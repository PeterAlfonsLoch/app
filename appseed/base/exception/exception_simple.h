#pragma once




class CLASS_DECL_c simple_exception : 
   virtual public ::exception::base
{
public:
   
   
   string       m_strMessage;


   simple_exception(sp(base_application) papp);
   simple_exception(sp(base_application) papp, const char * pszMessage);
   virtual ~simple_exception();


   virtual string get_error_message();


};


