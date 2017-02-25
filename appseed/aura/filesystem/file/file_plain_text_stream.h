#pragma once


#include "file_memory_file.h"
#include "file_string_file.h"


namespace file
{


   class CLASS_DECL_AURA plain_text_stream :
      virtual public plain_text_ostream,
      virtual public plain_text_istream,
      virtual public stream
   {
   public:

      
      plain_text_stream();
      plain_text_stream(file * pbuffer);
      plain_text_stream(const stream & stream);
      virtual ~plain_text_stream();

      
      stream & operator = (const stream & stream);

      virtual bool is_stream_null();
      virtual bool is_stream_set();

      virtual void close();



   };


   class CLASS_DECL_AURA plain_text_stream_memory_file :
      virtual public plain_text_stream,
      virtual public memory_file
   {
   public:


      plain_text_stream_memory_file(::aura::application * papp);
      virtual ~plain_text_stream_memory_file();
      
      virtual file_position_t seek(file_offset_t offset, e_seek seekOrigin);
      virtual file_position_t get_position() const;
      virtual void flush();
      virtual void * get_internal_data();
      virtual const void * get_internal_data() const;
      virtual memory_size_t get_internal_data_size() const;
      virtual bool set_internal_data_size(memory_size_t s);
      virtual void write(const void * p, memory_size_t s);
      virtual memory_size_t read(void * p, memory_size_t s);
      virtual void set_length(file_size_t dwNewLen);
      virtual void close();

   };


   class CLASS_DECL_AURA plain_text_stream_string_file :
      virtual public plain_text_stream,
      virtual public string_file
   {
   public:


      plain_text_stream_string_file();
      virtual ~plain_text_stream_string_file();

      virtual file_position_t seek(file_offset_t offset, e_seek seekOrigin);
      virtual file_position_t get_position() const;
      virtual void flush();
      virtual void write(const void * p, memory_size_t s);
      virtual memory_size_t read(void * p, memory_size_t s);
      virtual void set_length(file_size_t dwNewLen);
      virtual void close();

   };


   class CLASS_DECL_AURA plain_text_stream_string :
      virtual public plain_text_stream_string_file
   {
   public:

      string m_str;


      plain_text_stream_string();
      virtual ~plain_text_stream_string();


   };

} // namespace file


using std_string_stream = ::file::plain_text_stream;
