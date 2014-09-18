#pragma once


namespace file
{


   class output_stream;

   typedef smart_pointer < output_stream > output_stream_sp;


   class CLASS_DECL_AURA file_output_stream:
      virtual public file_stream_base,
      virtual public output_stream
   {
   public:


      file_output_stream();
      file_output_stream(const char * lpszFileName,uint32_t nOpenFlags,sp(::aura::application) papp = ::get_thread_app());
      file_output_stream(stream_buffer * pwriter);
      file_output_stream(const file_output_stream & pwriter);
      virtual ~file_output_stream();


   };


} // namespace file



