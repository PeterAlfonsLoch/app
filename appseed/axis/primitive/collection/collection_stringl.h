#pragma once


class CLASS_DECL_BASE stringl :
   virtual public string_list,
   virtual public ::file::serializable
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


   void write(::file::output_stream & ostream);
   void read(::file::input_stream & istream);


};


