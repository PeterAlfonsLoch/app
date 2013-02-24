#include "framework.h"


namespace gen
{

   byte_stream_memory_file::byte_stream_memory_file(::ca::application * papp, ::primitive::memory_size iSize) :
      ca(papp),
      memory_container(papp),
      ::primitive::memory_file(papp, iSize)
   {
   }

   byte_stream_memory_file::byte_stream_memory_file(::ca::application * papp, void * pMemory, primitive::memory_size dwSize) :
      ca(papp),
      memory_container(papp, pMemory, dwSize),
      ::primitive::memory_file(papp, pMemory, dwSize)
   {
   }

   byte_stream_memory_file::byte_stream_memory_file(::ca::application * papp, const memory_file & memoryfile) :
      ca(papp),
      memory_container(papp),
      ::primitive::memory_file(papp, memoryfile)
   {
   }

   byte_stream_memory_file::byte_stream_memory_file(::ca::application * papp, ::primitive::memory_base * pmemory) :
      ca(papp),
      memory_container(papp, pmemory),
      ::primitive::memory_file(papp, pmemory)
   {
   }

   byte_stream_memory_file::byte_stream_memory_file(const byte_stream_memory_file & file) :
      ca(file.get_app()),
      memory_container(file.get_app()),
      ::primitive::memory_file(file.get_app(), (const memory_file &) file)
   {
   }

   byte_stream_memory_file::~byte_stream_memory_file()
   {
   }


   file_position byte_stream_memory_file::seek(file_offset offset, ::gen::e_seek seekOrigin)
   {
      return ::primitive::memory_file::seek(offset, seekOrigin);
   }

} // namespace gen