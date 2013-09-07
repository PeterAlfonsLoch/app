#include "framework.h"


namespace file
{


   byte_stream_memory_buffer::byte_stream_memory_buffer(::primitive::memory_base * pbase) :
      m_memorybuffer(pbase->get_app(), pbase)
   {

      

   }


   byte_stream_memory_buffer::~byte_stream_memory_buffer()
   {
   }


} // namespace file


