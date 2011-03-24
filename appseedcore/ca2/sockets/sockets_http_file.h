#pragma once

namespace sockets
{

   namespace http
   {

      class CLASS_DECL_ca file : 
         virtual public ::ex1::filesp
      {
      public:

         ::ex1::timeout_file *   m_ptimeoutfile;
         ::primitive::memory *              m_pmemory;
         ::gen::memory_file *         m_pmemoryfileIn;
         ::gen::memory_file *         m_pmemoryfileOut;
         ::ex1::file *           m_pfileTime;
         string                  m_strTimePath;

         file(::ca::application * papp);
         file(::ca::application * papp, ::gen::memory_file * pmemoryfileIn);

         virtual BOOL open(const char * lpszFileName, UINT nOpenFlags, ::ex1::file_exception_sp * pError = NULL);

         DECL_GEN_SIGNAL(on_http_request_response);

      };

   } // namespace http

} // namespace sockets