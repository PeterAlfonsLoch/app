//#include "framework.h"


namespace file
{


   plain_text_stream::plain_text_stream()
   {
   }

   plain_text_stream::plain_text_stream(file * pbuffer) :
      plain_text_ostream(pbuffer),
      plain_text_istream(pbuffer)
   {
   }

   plain_text_stream::plain_text_stream(const stream & stream) :
      plain_text_ostream(stream),
      plain_text_istream(stream)
   {
   }

   plain_text_stream::~plain_text_stream()
   {
   }

   stream & plain_text_stream::operator = (const stream & stream)
   {
      plain_text_istream::operator = (stream);
      plain_text_ostream::operator = (stream);
      return *this;
   }

   bool plain_text_stream::is_stream_null()
   {
      return is_writer_null() && is_reader_null();
   }

   bool plain_text_stream::is_stream_set()
   {
      return is_writer_set() || is_reader_set();
   }

   void plain_text_stream::close()
   {
      plain_text_istream::close();
      plain_text_ostream::close();
   }




   plain_text_stream_memory_file::plain_text_stream_memory_file(::aura::application * papp) :
      object(papp),
      memory_container(papp),
      memory_file(papp)
   {

      m_spfile = this;

   }


   plain_text_stream_memory_file::~plain_text_stream_memory_file()
   {


   }


   file_position_t plain_text_stream_memory_file::seek(file_offset_t offset, e_seek seekOrigin)
   {

      return memory_file::seek(offset, seekOrigin);

   }

   
   file_position_t plain_text_stream_memory_file::get_position() const
   {

      return memory_file::get_position();

   }

   
   void plain_text_stream_memory_file::flush()
   {

      memory_file::flush();

   }


   void * plain_text_stream_memory_file::get_internal_data()
   {

      return memory_file::get_internal_data();

   }
   
   
   const void * plain_text_stream_memory_file::get_internal_data() const
   {

      return memory_file::get_internal_data();

   }


   memory_size_t plain_text_stream_memory_file::get_internal_data_size() const
   {

      return memory_file::get_internal_data_size();

   }

   bool plain_text_stream_memory_file::set_internal_data_size(memory_size_t s)
   {

      return memory_file::set_internal_data_size(s);

   }
   
   void plain_text_stream_memory_file::write(const void * p, memory_size_t s)
   {

      memory_file::write(p, s);

   }
   
   
   memory_size_t plain_text_stream_memory_file::read(void * p, memory_size_t s)
   {

      return memory_file::read(p, s);

   }


   void plain_text_stream_memory_file::set_length(file_size_t dwNewLen)
   {

      memory_file::set_length(dwNewLen);

   }


   void plain_text_stream_memory_file::close()
   {

      plain_text_stream::close();

   }




   // string file


   plain_text_stream_string_file::plain_text_stream_string_file()
   {

      m_spfile = this;

   }


   plain_text_stream_string_file::~plain_text_stream_string_file()
   {

   }

   file_position_t plain_text_stream_string_file::seek(file_offset_t offset, e_seek seekOrigin)
   {

      return string_file::seek(offset, seekOrigin);

   }


   file_position_t plain_text_stream_string_file::get_position() const
   {

      return string_file::get_position();

   }


   void plain_text_stream_string_file::flush()
   {

      string_file::flush();

   }


   void plain_text_stream_string_file::write(const void * p, memory_size_t s)
   {

      string_file::write(p, s);

   }


   memory_size_t plain_text_stream_string_file::read(void * p, memory_size_t s)
   {

      return string_file::read(p, s);

   }

   void plain_text_stream_string_file::set_length(file_size_t dwNewLen)
   {

      plain_text_stream::set_length(dwNewLen);

   }


   void plain_text_stream_string_file::close()
   {

      plain_text_stream::close();

   }




   plain_text_stream_string::plain_text_stream_string()
   {

      m_pstr = &m_str;

   }


   plain_text_stream_string::~plain_text_stream_string()
   {

   }


} // namespace file


