#include "StdAfx.h"


namespace sockets
{


   namespace http
   {


      file::file(::ca::application * papp, mutex * pmutex) :
         ca(papp),
         transfer_file(papp, pmutex)
      {
      }

      // it is not currently designed to call open.
      //
      file::file(::ca::application * papp, ::gen::memory_file * pmemoryfileIn) :
         ca(papp),
         transfer_file(papp, pmemoryfileIn)
      {
      }

      file::~file()
      {

      }
      
      BOOL file::open(const char * lpszFileName, UINT nOpenFlags, ex1::file_exception_sp * pError)
      {
         UNREFERENCED_PARAMETER(pError);
         ca4::http::signal * psignal = new ca4::http::signal;

         (*psignal)()["file"] = (::ca::ca *) m_pmemoryfileIn;
         (*psignal)()["file_out"] = (::ca::ca *) m_ptimeoutfile;
         psignal->m_strUrl = lpszFileName; 
         psignal->m_set["optional_ca2_login"] = true;

         if((nOpenFlags & ::ex1::file::hint_unknown_length_supported) != 0)
         {
            m_ptimeoutfile->m_uiExpectedSize = (uint64_t) -2;
         }
         else
         {
            m_ptimeoutfile->m_uiExpectedSize = (uint64_t) -1;
         }

         gen::emit(get_app(), this, &file::on_http_request_response, &Application.http(), &ca4::http::application::get, psignal);
         return TRUE;
      }

      void file::on_http_request_response(gen::signal_object * pobj)
      {
         UNREFERENCED_PARAMETER(pobj);
      }


   } // namespace http


} // namespace sockets

