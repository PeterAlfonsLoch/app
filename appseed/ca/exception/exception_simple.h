#pragma once




class CLASS_DECL_ca simple_exception : 
   public base_exception
{
public:
   
   
   vsstring       m_strMessage;


   simple_exception();
   simple_exception(const char * pszMessage);
   virtual ~simple_exception();


   virtual vsstring get_error_message();


};


