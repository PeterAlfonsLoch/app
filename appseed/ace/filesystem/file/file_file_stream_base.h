#pragma once


namespace file
{

   class CLASS_DECL_ACE file_stream_base:
      virtual public stream_base
   {
   public:


      memory_size_t      m_gcount;


      file_stream_base();
      virtual ~file_stream_base();


      virtual void open(const ::file::path & lpszFileName,uint32_t nOpenFlags,::ace::application * papp = ::get_thread_app());

   };


} // namespace file





