#pragma once


namespace gen
{


   class CLASS_DECL_ca byte_stream_memory_file :
      virtual public gen::memory_file,
      virtual public ex1::byte_stream
   {
   public:
   

      byte_stream_memory_file(::ca::application * papp, ::primitive::memory_size iSize = 0);
      byte_stream_memory_file(::ca::application * papp, void * pMemory, ::primitive::memory_size dwSize);
      byte_stream_memory_file(::ca::application * papp, const memory_file & memoryfile);
      byte_stream_memory_file(::ca::application * papp, ::primitive::memory_base * pmemory);
      byte_stream_memory_file(const byte_stream_memory_file & file);
      virtual ~byte_stream_memory_file();


   };


} // namespace gen


