#pragma once


namespace sockets
{


   class CLASS_DECL_AURA http_buffer :
      virtual public ::file::transfer_file
   {
   public:


      http_buffer(::aura::application * papp, mutex * pmutex = NULL);
      http_buffer(::aura::application * papp, ::memory_file * pmemoryfileIn);
      virtual ~http_buffer();


      virtual cres open(const ::file::path & lpszFileName, UINT nOpenFlags);


      DECL_GEN_SIGNAL(on_http_request_response);


   };


} // namespace sockets




