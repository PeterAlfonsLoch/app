#pragma once




class CLASS_DECL_AURA invalid_character : 
   virtual public simple_exception
{
public:
   

   invalid_character(sp(::aura::application) papp, const char * pszMessage);
   virtual ~invalid_character();


};
