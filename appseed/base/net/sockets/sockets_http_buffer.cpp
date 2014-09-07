#include "framework.h" // from "base/net/net_sockets.h"


namespace sockets
{


   http_buffer::http_buffer(sp(::aura::application) papp, mutex * pmutex) :
      element(papp),
      transfer_buffer(papp, pmutex)
   {

   }


   // it is not currently designed to call open.
   //
   http_buffer::http_buffer(sp(::aura::application) papp, ::file::memory_buffer * pmemoryfileIn) :
      element(papp),
      transfer_buffer(papp, pmemoryfileIn)
   {

   }


   http_buffer::~http_buffer()
   {

   }

      
   bool http_buffer::open(const char * lpszFileName, UINT nOpenFlags)
   {

//         if(!Application.http_buffer().exists(lpszFileName))
//          return false;

      ::http::signal * psignal = new ::http::signal;

      psignal->m_set["file"]       = (sp(element)) m_pmemoryfileIn;
      psignal->m_set["file_out"]   = (sp(element)) m_ptimeoutfile;

      psignal->m_strUrl = lpszFileName; 
      //psignal->m_set["optional_ca2_login"] = true;
      psignal->m_set["noclose"] = false;

      if((nOpenFlags & ::file::hint_unknown_length_supported) != 0)
      {
         m_ptimeoutfile->m_uiExpectedSize = (uint64_t) -2;
      }
      else
      {
         m_ptimeoutfile->m_uiExpectedSize = (uint64_t) -1;
      }

      ::emit(get_app(), this, &http_buffer::on_http_request_response, &Application.http(), &::http::application::get, psignal);

      return TRUE;

   }


   void http_buffer::on_http_request_response(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


} // namespace sockets





