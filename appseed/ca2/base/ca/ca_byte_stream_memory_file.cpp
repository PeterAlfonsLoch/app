#include "framework.h"


namespace ca2
{

   byte_stream_memory_file::byte_stream_memory_file(sp(::ca2::application) papp, ::primitive::memory_size iSize) :
      ca2(papp),
      memory_container(papp),
      ::primitive::memory_file(papp, iSize)
   {
   }

   byte_stream_memory_file::byte_stream_memory_file(sp(::ca2::application) papp, void * pMemory, primitive::memory_size dwSize) :
      ca2(papp),
      memory_container(papp, pMemory, dwSize),
      ::primitive::memory_file(papp, pMemory, dwSize)
   {
   }

   byte_stream_memory_file::byte_stream_memory_file(sp(::ca2::application) papp, const memory_file & memoryfile) :
      ca2(papp),
      memory_container(papp),
      ::primitive::memory_file(papp, memoryfile)
   {
   }

   byte_stream_memory_file::byte_stream_memory_file(sp(::ca2::application) papp, ::primitive::memory_base * pmemory) :
      ca2(papp),
      memory_container(papp, pmemory),
      ::primitive::memory_file(papp, pmemory)
   {
   }

   byte_stream_memory_file::byte_stream_memory_file(const byte_stream_memory_file & file) :
      ca2(file.get_app()),
      memory_container(file.get_app()),
      ::primitive::memory_file(file.get_app(), (const memory_file &) file)
   {
   }

   byte_stream_memory_file::~byte_stream_memory_file()
   {
   }


   file_position byte_stream_memory_file::seek(file_offset offset, ::ca2::e_seek seekOrigin)
   {
      return ::primitive::memory_file::seek(offset, seekOrigin);
   }

} // namespace ca2
