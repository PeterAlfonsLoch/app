#pragma once


#include "ca/ex1/ex1_str_stream.h"


class CLASS_DECL_ca _template_std_istringstream :
   virtual public ex1::plain_text_input_stream,
   virtual public ex1::str_reader
{
public:
   
   string m_str;



   _template_std_istringstream();
   _template_std_istringstream(const char * psz);
   _template_std_istringstream(const string & str);

   string & str();

   //virtual void write(const void *,primitive::memory_size);

};


class CLASS_DECL_ca _template_std_ostringstream :
   virtual public ex1::plain_text_output_stream,
   virtual public ex1::str_writer
{
public:
   
   string m_str;



   _template_std_ostringstream();

   string & str();

  // virtual void write(const void *,primitive::memory_size);

};



class CLASS_DECL_ca _template_std_stringstream :
   virtual public ex1::plain_text_stream,
   virtual public ex1::str_reader,
   virtual public ex1::str_writer
{
public:
   
   string m_str;



   _template_std_stringstream();
   _template_std_stringstream(const char * psz);
   _template_std_stringstream(const string & str);

   string & str();

   //virtual void write(const void *,primitive::memory_size);

};

