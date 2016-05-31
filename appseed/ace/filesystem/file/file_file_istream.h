#pragma once


namespace file
{


   class CLASS_DECL_AURA file_istream :
      virtual public file_stream_base,
      virtual public istream
   {
   public:


      file_istream();
      file_istream(const char * lpszFileName,uint32_t nOpenFlags,::aura::application * papp = ::get_thread_app());
      file_istream(stream_buffer * preader);
      file_istream(const file_istream & preader);
      virtual ~file_istream();

   };


} // namespace file





