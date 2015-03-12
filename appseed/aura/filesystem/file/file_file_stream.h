#pragma once


namespace file
{


   class CLASS_DECL_AURA file_stream:
      virtual public stream,
      virtual public file_ostream,
      virtual public file_istream
   {
   public:


      file_stream();
      file_stream(const char * lpszFileName,uint32_t nOpenFlags,::aura::application * papp = ::get_thread_app());
      file_stream(stream_buffer * preader);
      file_stream(const file_stream & preader);
      virtual ~file_stream();

   };


} // namespace file


