#pragma once


namespace file
{


   class CLASS_DECL_c byte_stream_memory_buffer :
      virtual public byte_stream
   {
   public:


      memory_buffer        m_memorybuffer;


      byte_stream_memory_buffer(::primitive::memory_base * pbase);
      virtual ~byte_stream_memory_buffer();

   };


} // namespace file


