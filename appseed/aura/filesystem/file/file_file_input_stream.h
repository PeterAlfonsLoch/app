#pragma once


namespace file
{


   class CLASS_DECL_AURA file_input_stream :
      virtual public file_stream_base,
      virtual public input_stream
   {
   public:


      file_input_stream();
      file_input_stream(const char * lpszFileName,uint32_t nOpenFlags,sp(::aura::application) papp = ::get_thread_app());
      file_input_stream(stream_buffer * preader);
      file_input_stream(const file_input_stream & preader);
      virtual ~file_input_stream();

   };


} // namespace file





