#pragma once


#include "base/ca2/ca2_str_stream.h"


class CLASS_DECL_ca2 _template_std_istringstream :
   virtual public ::ca2::plain_text_input_stream,
   virtual public ::ca2::str_reader
{
public:
   
   string m_str;



   _template_std_istringstream();
   _template_std_istringstream(const char * psz);
   _template_std_istringstream(const string & str);

   string & str();

   //virtual void write(const void *,primitive::memory_size);

};


class CLASS_DECL_ca2 _template_std_ostringstream :
   virtual public ::ca2::plain_text_output_stream,
   virtual public ::ca2::str_writer
{
public:
   
   string m_str;



   _template_std_ostringstream();

   string & str();

  // virtual void write(const void *,primitive::memory_size);

};



class CLASS_DECL_ca2 _template_std_stringstream :
   virtual public ::ca2::plain_text_stream,
   virtual public ::ca2::str_reader,
   virtual public ::ca2::str_writer
{
public:
   
   string m_str;



   _template_std_stringstream();
   _template_std_stringstream(const char * psz);
   _template_std_stringstream(const string & str);

   string & str();

   //virtual void write(const void *,primitive::memory_size);

};

