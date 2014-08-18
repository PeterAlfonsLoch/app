#pragma once




class CLASS_DECL_AXIS invalid_character : 
   virtual public simple_exception
{
public:
   

   invalid_character(sp(::base::application) papp, const char * pszMessage);
   virtual ~invalid_character();


};
