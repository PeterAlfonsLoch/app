#pragma once


namespace sockets
{


   namespace http
   {


      class CLASS_DECL_ca file : 
         virtual public ::ex2::transfer_file
      {
      public:

         
         file(::ca::application * papp, mutex * pmutex = NULL);
         file(::ca::application * papp, ::gen::memory_file * pmemoryfileIn);
         virtual ~file();


         virtual bool open(const char * lpszFileName, UINT nOpenFlags);

         
         DECL_GEN_SIGNAL(on_http_request_response);


      };


   } // namespace http


} // namespace sockets




