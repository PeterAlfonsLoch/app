#pragma once


class CLASS_DECL_ca2 stringl :
   virtual public string_list,
   virtual public ::ca::byte_serializable
{
public:

   stringl(int_ptr nBlockSize = 10);
   virtual ~stringl();


   void explode(const char * lpcszSeparator, const char * psz);
   void implode(string & rwstr, const char * lpcszSeparator = NULL, index iStart = 0, ::count iCount = -1) const;
   string implode(const char * lpcszSeparator = NULL, index iStart = 0, ::count iCount = -1) const;
   void reverse_implode(string & rwstr, const char * lpcszSeparator = NULL, index iStart = 0, ::count iCount = -1) const;
   string reverse_implode(const char * lpcszSeparator = NULL, index iStart = 0, ::count iCount = -1) const;

   void add_tail_tokens(const char * lpcsz, const char * lpcszSeparator, bool bAddEmpty);


   void write(::ca::byte_output_stream & ostream);
   void read(::ca::byte_input_stream & istream);


};