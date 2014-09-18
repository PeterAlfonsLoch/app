#pragma once


namespace file
{

   class CLASS_DECL_AURA file_stream_base:
      virtual public stream_base
   {
   public:


      ::primitive::memory_size      m_gcount;


      file_stream_base();
      virtual ~file_stream_base();


      virtual void open(const char * lpszFileName,uint32_t nOpenFlags,sp(::aura::application) papp = ::get_thread_app());

   };


} // namespace file





