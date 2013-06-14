#pragma once


namespace ca2
{


   class CLASS_DECL_ca2 byte_stream_memory_file :
      virtual public ::primitive::memory_file,
      virtual public ::ca2::byte_stream
   {
   public:
   

      byte_stream_memory_file(sp(::ca2::application) papp, ::primitive::memory_size iSize = 0);
      byte_stream_memory_file(sp(::ca2::application) papp, void * pMemory, ::primitive::memory_size dwSize);
      byte_stream_memory_file(sp(::ca2::application) papp, const memory_file & memoryfile);
      byte_stream_memory_file(sp(::ca2::application) papp, ::primitive::memory_base * pmemory);
      byte_stream_memory_file(const byte_stream_memory_file & file);
      virtual ~byte_stream_memory_file();

      file_position seek(file_offset offset, ::ca2::e_seek seekOrigin);

   };


} // namespace ca2


