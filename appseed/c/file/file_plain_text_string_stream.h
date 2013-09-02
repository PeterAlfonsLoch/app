#pragma once



class CLASS_DECL_c _template_std_istringstream :
   virtual public ::file::plain_text_input_stream,
   virtual public ::file::string_reader
{
public:
   
   string m_str;



   _template_std_istringstream();
   _template_std_istringstream(const char * psz);
   _template_std_istringstream(const string & str);

   string & str();

   //virtual void write(const void *,primitive::memory_size);

};


class CLASS_DECL_c _template_std_ostringstream :
   virtual public ::file::plain_text_output_stream,
   virtual public ::file::string_writer
{
public:
   
   string m_str;



   _template_std_ostringstream();

   string & str();

  // virtual void write(const void *,primitive::memory_size);

};



class CLASS_DECL_c _template_std_stringstream :
   virtual public ::file::plain_text_stream,
   virtual public ::file::string_reader,
   virtual public ::file::string_writer
{
public:
   
   string m_str;



   _template_std_stringstream();
   _template_std_stringstream(const char * psz);
   _template_std_stringstream(const string & str);

   string & str();

   //virtual void write(const void *,primitive::memory_size);

};

