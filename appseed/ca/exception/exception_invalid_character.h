#pragma once




class CLASS_DECL_ca invalid_character : 
   virtual public simple_exception
{
public:
   

   invalid_character(::ca::application * papp, char * pszMessage);
   virtual ~invalid_character();


};
