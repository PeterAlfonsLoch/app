#pragma once


class CLASS_DECL_CA2_CUBE checkimage : 
   virtual public ptr
{
public:

   void generate_new_image();
   void output_image(const char * pszCode);
   string generate_code();
   string register_code(const char * pszCode);
   bool verify_code(const char * pszCode);
   bool is_valid_code(const char * pszCode);

};