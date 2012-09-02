#pragma once




class CLASS_DECL_ca invalid_character : 
   public simple_exception
{
public:
   
   invalid_character(const char * pszMessage);
   virtual ~invalid_character();

};
