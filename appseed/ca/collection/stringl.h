#pragma once

#include "primitive/var.h"

class CLASS_DECL_ca stringl :
   virtual public string_list,
   virtual public ex1::byte_serializable
{
public:

   stringl(INT_PTR nBlockSize = 10);
   virtual ~stringl();


   void explode(const char * lpcszSeparator, const char * psz);
   void implode(string & rwstr, const char * lpcszSeparator = NULL, index iStart = 0, count iCount = -1) const;
   string implode(const char * lpcszSeparator = NULL, index iStart = 0, count iCount = -1) const;
   void reverse_implode(string & rwstr, const char * lpcszSeparator = NULL, index iStart = 0, count iCount = -1) const;
   string reverse_implode(const char * lpcszSeparator = NULL, index iStart = 0, count iCount = -1) const;

   void add_tail_tokens(const char * lpcsz, const char * lpcszSeparator, BOOL bAddEmpty);


   void write(ex1::byte_output_stream & ostream);
   void read(ex1::byte_input_stream & istream);


};