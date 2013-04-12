#pragma once


#include "ca/ca/ca_str_stream.h"


class CLASS_DECL_ca _template_std_istringstream :
   virtual public ::ca::plain_text_input_stream,
   virtual public ::ca::str_reader
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
   virtual public ::ca::plain_text_output_stream,
   virtual public ::ca::str_writer
{
public:
   
   string m_str;



   _template_std_ostringstream();

   string & str();

  // virtual void write(const void *,primitive::memory_size);

};



class CLASS_DECL_ca _template_std_stringstream :
   virtual public ::ca::plain_text_stream,
   virtual public ::ca::str_reader,
   virtual public ::ca::str_writer
{
public:
   
   string m_str;



   _template_std_stringstream();
   _template_std_stringstream(const char * psz);
   _template_std_stringstream(const string & str);

   string & str();

   //virtual void write(const void *,primitive::memory_size);

};

