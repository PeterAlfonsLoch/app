#pragma once


namespace ca
{


   class CLASS_DECL_ca byte_stream_memory_file :
      virtual public ::primitive::memory_file,
      virtual public ::ca::byte_stream
   {
   public:
   

      byte_stream_memory_file(sp(::ca::application) papp, ::primitive::memory_size iSize = 0);
      byte_stream_memory_file(sp(::ca::application) papp, void * pMemory, ::primitive::memory_size dwSize);
      byte_stream_memory_file(sp(::ca::application) papp, const memory_file & memoryfile);
      byte_stream_memory_file(sp(::ca::application) papp, ::primitive::memory_base * pmemory);
      byte_stream_memory_file(const byte_stream_memory_file & file);
      virtual ~byte_stream_memory_file();

      file_position seek(file_offset offset, ::ca::e_seek seekOrigin);

   };


} // namespace ca


