#pragma once


namespace file
{


   class CLASS_DECL_ACE byte_stream_memory_buffer :
      virtual public byte_stream
   {
   public:


      memory_buffer_sp        m_spmemorybuffer;


      byte_stream_memory_buffer(::ace::application * papp);
      byte_stream_memory_buffer(::primitive::memory_base * pbase);
      byte_stream_memory_buffer(::ace::application * papp, const void * data, memory_size_t c);
      byte_stream_memory_buffer(byte_stream_memory_buffer && b);
      virtual ~byte_stream_memory_buffer();


      virtual file_size_t get_length();
      virtual void * get_data();
      operator void * () { return get_data(); }

   };


} // namespace file


