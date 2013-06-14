#pragma once




class CLASS_DECL_ca2 simple_exception : 
   virtual public base_exception
{
public:
   
   
   vsstring       m_strMessage;


   simple_exception(sp(::ca2::application) papp);
   simple_exception(sp(::ca2::application) papp, const char * pszMessage);
   virtual ~simple_exception();


   virtual vsstring get_error_message();


};


