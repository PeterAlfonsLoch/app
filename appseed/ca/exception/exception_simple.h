#pragma once




class CLASS_DECL_ca simple_exception : 
   virtual public base_exception
{
public:
   
   
   vsstring       m_strMessage;


   simple_exception(::ca::applicationsp papp);
   simple_exception(::ca::applicationsp papp, const char * pszMessage);
   virtual ~simple_exception();


   virtual vsstring get_error_message();


};


