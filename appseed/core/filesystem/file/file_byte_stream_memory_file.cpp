#include "framework.h"


namespace core
{

   byte_stream_memory_file::byte_stream_memory_file(sp(base_application) papp, ::primitive::memory_size iSize) :
      element(papp),
      memory_container(papp),
      ::::file::memory_buffer(papp, iSize)
   {
   }

   byte_stream_memory_file::byte_stream_memory_file(sp(base_application) papp, void * pMemory, primitive::memory_size dwSize) :
      element(papp),
      memory_container(papp, pMemory, dwSize),
      ::::file::memory_buffer(papp, pMemory, dwSize)
   {
   }

   byte_stream_memory_file::byte_stream_memory_file(sp(base_application) papp, const memory_buffer & memoryfile) :
      element(papp),
      memory_container(papp),
      ::::file::memory_buffer(papp, memoryfile)
   {
   }

   byte_stream_memory_file::byte_stream_memory_file(sp(base_application) papp, ::primitive::memory_base * pmemory) :
      element(papp),
      memory_container(papp, pmemory),
      ::::file::memory_buffer(papp, pmemory)
   {
   }

   byte_stream_memory_file::byte_stream_memory_file(const byte_stream_memory_file & file) :
      element(file.get_app()),
      memory_container(file.get_app()),
      ::::file::memory_buffer(file.get_app(), (const memory_buffer &) file)
   {
   }

   byte_stream_memory_file::~byte_stream_memory_file()
   {
   }


   file_position byte_stream_memory_file::seek(file_offset offset, ::file::e_seek seekOrigin)
   {
      return ::::file::memory_buffer::seek(offset, seekOrigin);
   }

} // namespace core
