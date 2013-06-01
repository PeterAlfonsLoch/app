#pragma once


namespace sockets
{


   namespace http
   {


      class CLASS_DECL_ca2 file : 
         virtual public ::ca::transfer_file
      {
      public:

         
         file(sp(::ca::application) papp, mutex * pmutex = NULL);
         file(sp(::ca::application) papp, ::primitive::memory_file * pmemoryfileIn);
         virtual ~file();


         virtual bool open(const char * lpszFileName, UINT nOpenFlags);

         
         DECL_GEN_SIGNAL(on_http_request_response);


      };


   } // namespace http


} // namespace sockets




