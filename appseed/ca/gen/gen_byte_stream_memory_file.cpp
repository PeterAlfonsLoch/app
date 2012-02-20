#include "StdAfx.h"


namespace gen
{

   byte_stream_memory_file::byte_stream_memory_file(::ca::application * papp, ::primitive::memory_size iSize) :
      ca(papp),
      memory_container(papp),
      gen::memory_file(papp, iSize)
   {
   }

   byte_stream_memory_file::byte_stream_memory_file(::ca::application * papp, void * pMemory, primitive::memory_size dwSize) :
      ca(papp),
      memory_container(papp, pMemory, dwSize),
      gen::memory_file(papp, pMemory, dwSize)
   {
   }

   byte_stream_memory_file::byte_stream_memory_file(::ca::application * papp, const memory_file & memoryfile) :
      ca(papp),
      memory_container(papp),
      gen::memory_file(papp, memoryfile)
   {
   }

   byte_stream_memory_file::byte_stream_memory_file(::ca::application * papp, ::primitive::base_memory * pmemory) :
      ca(papp),
      memory_container(papp, pmemory),
      gen::memory_file(papp, pmemory)
   {
   }

   byte_stream_memory_file::byte_stream_memory_file(const byte_stream_memory_file & file) :
      ca(file.get_app()),
      memory_container(file.get_app()),
      gen::memory_file(file.get_app(), (const memory_file &) file)
   {
   }

   byte_stream_memory_file::~byte_stream_memory_file()
   {
   }




} // namespace gen