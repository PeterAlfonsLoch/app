#pragma once


namespace file
{


   class CLASS_DECL_AURA file_stream:
      virtual public file_output_stream,
      virtual public file_input_stream
   {
   public:


      file_stream();
      file_stream(const char * lpszFileName,uint32_t nOpenFlags,sp(::aura::application) papp = ::get_thread_app());
      file_stream(stream_buffer * preader);
      file_stream(const file_stream & preader);
      virtual ~file_stream();

   };


} // namespace file


