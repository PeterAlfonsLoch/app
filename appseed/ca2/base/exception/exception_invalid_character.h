#pragma once




class CLASS_DECL_ca2 invalid_character : 
   virtual public simple_exception
{
public:
   

   invalid_character(sp(::ca::application) papp, const char * pszMessage);
   virtual ~invalid_character();


};
