#include "framework.h"


namespace file
{


   byte_stream_memory_buffer::byte_stream_memory_buffer(::axis::application * papp)
   {

      m_spmemorybuffer = canew(memory_buffer(papp));

      m_spbuffer = m_spmemorybuffer;

   }


   byte_stream_memory_buffer::byte_stream_memory_buffer(::primitive::memory_base * pbase)
   {

      m_spmemorybuffer = canew(memory_buffer(pbase->get_app(), pbase));

      m_spbuffer = m_spmemorybuffer;
      

   }


   byte_stream_memory_buffer::byte_stream_memory_buffer(::axis::application * papp, const void * data, ::primitive::memory_size c)
   {

      m_spmemorybuffer = canew(memory_buffer(papp, (void *) data, c));

      m_spbuffer = m_spmemorybuffer;

   }


   byte_stream_memory_buffer::~byte_stream_memory_buffer()
   {

   }


   file_size byte_stream_memory_buffer::get_length()
   {
      
      return m_spmemorybuffer->get_size();

   }


   void * byte_stream_memory_buffer::get_data()
   {
      
      return m_spmemorybuffer->get_data();

   }


} // namespace file




