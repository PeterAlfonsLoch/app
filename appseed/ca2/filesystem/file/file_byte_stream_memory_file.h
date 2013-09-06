#pragma once


namespace file
{


   class CLASS_DECL_ca2 byte_stream_memory_file :
      virtual public ::::file::memory_buffer,
      virtual public ::ca2::byte_stream
   {
   public:
   

      byte_stream_memory_file(sp(base_application) papp, ::primitive::memory_size iSize = 0);
      byte_stream_memory_file(sp(base_application) papp, void * pMemory, ::primitive::memory_size dwSize);
      byte_stream_memory_file(sp(base_application) papp, const memory_buffer & memoryfile);
      byte_stream_memory_file(sp(base_application) papp, ::primitive::memory_base * pmemory);
      byte_stream_memory_file(const byte_stream_memory_file & file);
      virtual ~byte_stream_memory_file();

      file_position seek(file_offset offset, ::file::e_seek seekOrigin);

   };


} // namespace file


