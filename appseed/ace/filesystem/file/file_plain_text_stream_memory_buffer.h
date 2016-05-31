#pragma once


namespace file
{


   class CLASS_DECL_ACE plain_text_stream_memory_buffer :
      virtual public plain_text_stream
   {
   public:


      memory_buffer_sp        m_spmemorybuffer;


      plain_text_stream_memory_buffer(::ace::application * papp);
      plain_text_stream_memory_buffer(::primitive::memory_base * pbase);
      plain_text_stream_memory_buffer(::ace::application * papp, const void * data, memory_size_t c);
      virtual ~plain_text_stream_memory_buffer();


      virtual file_size_t get_length();
      virtual void * get_data();
      virtual string to_string();



   };


} // namespace file


