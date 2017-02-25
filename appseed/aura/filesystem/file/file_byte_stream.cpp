//#include "framework.h"


namespace file
{


   byte_stream::byte_stream()
   {

   }


   byte_stream::byte_stream(file * pbuffer) :
      stream_base(pbuffer),
      stream(pbuffer)
   {

   }


   byte_stream::byte_stream(const stream & strm) :
      stream_base(strm),
      stream(strm)
   {

   }


   byte_stream::~byte_stream()
   {

   }


   stream & byte_stream::operator = (const stream & stream)
   {

      stream::operator = (stream);

      return *this;

   }


   bool byte_stream::is_stream_null()
   {

      return is_writer_null() && is_reader_null();

   }


   bool byte_stream::is_stream_set()
   {

      return is_writer_set() || is_reader_set();

   }


   void byte_stream::close()
   {

      istream::close();

      ostream::close();

   }


   file_position_t byte_stream::get_position() const
   {

      return m_spfile->get_position();

   }


   byte_stream_memory_file::byte_stream_memory_file(::aura::application * papp) :
      object(papp),
      memory_container(papp),
      memory_file(papp)
   {

      m_spfile = this;

   }


   byte_stream_memory_file::~byte_stream_memory_file()
   {


   }


   file_position_t byte_stream_memory_file::seek(file_offset_t offset, e_seek seekOrigin)
   {

      return memory_file::seek(offset, seekOrigin);

   }


   file_position_t byte_stream_memory_file::get_position() const
   {

      return memory_file::get_position();

   }


   void byte_stream_memory_file::flush()
   {

      memory_file::flush();

   }


   void * byte_stream_memory_file::get_internal_data()
   {

      return memory_file::get_internal_data();

   }


   const void * byte_stream_memory_file::get_internal_data() const
   {

      return memory_file::get_internal_data();

   }


   memory_size_t byte_stream_memory_file::get_internal_data_size() const
   {

      return memory_file::get_internal_data_size();

   }

   bool byte_stream_memory_file::set_internal_data_size(memory_size_t s)
   {

      return memory_file::set_internal_data_size(s);

   }

   void byte_stream_memory_file::write(const void * p, memory_size_t s)
   {

      memory_file::write(p, s);

   }


   memory_size_t byte_stream_memory_file::read(void * p, memory_size_t s)
   {

      return memory_file::read(p, s);

   }


   void byte_stream_memory_file::set_length(file_size_t dwNewLen)
   {

      byte_stream::set_length(dwNewLen);

   }


   void byte_stream_memory_file::close()
   {

      byte_stream::close();

   }


} // namespace file




