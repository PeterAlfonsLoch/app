#pragma once




class CLASS_DECL_ACE invalid_character : 
   virtual public simple_exception
{
public:
   

   invalid_character(::ace::application * papp, const char * pszMessage);
   virtual ~invalid_character();


};
