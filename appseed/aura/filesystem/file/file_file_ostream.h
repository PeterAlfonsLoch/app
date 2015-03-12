#pragma once


namespace file
{


   class ostream;

   typedef smart_pointer < ostream > ostream_sp;


   class CLASS_DECL_AURA file_ostream:
      virtual public file_stream_base,
      virtual public ostream
   {
   public:


      file_ostream();
      file_ostream(const char * lpszFileName,uint32_t nOpenFlags,::aura::application * papp = ::get_thread_app());
      file_ostream(stream_buffer * pwriter);
      file_ostream(const file_ostream & pwriter);
      virtual ~file_ostream();


   };


} // namespace file



