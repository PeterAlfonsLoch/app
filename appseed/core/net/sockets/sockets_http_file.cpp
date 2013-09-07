#include "framework.h"


namespace sockets
{


   namespace http
   {


      file::file(sp(base_application) papp, mutex * pmutex) :
         element(papp),
         transfer_file(papp, pmutex)
      {
      }

      // it is not currently designed to call open.
      //
      file::file(sp(base_application) papp, ::file::memory_buffer * pmemoryfileIn) :
         element(papp),
         transfer_file(papp, pmemoryfileIn)
      {
      }

      file::~file()
      {

      }
      
      bool file::open(const char * lpszFileName, UINT nOpenFlags)
      {

//         if(!Application.file().exists(lpszFileName))
  //          return false;

         ::http::signal * psignal = new ::http::signal;

         psignal->m_set["file"]       = (sp(element)) m_pmemoryfileIn;
         psignal->m_set["file_out"]   = (sp(element)) m_ptimeoutfile;

         psignal->m_strUrl = lpszFileName; 
         //psignal->m_set["optional_ca2_login"] = true;
         psignal->m_set["noclose"] = false;

         if((nOpenFlags & ::file::binary_buffer::hint_unknown_length_supported) != 0)
         {
            m_ptimeoutfile->m_uiExpectedSize = (uint64_t) -2;
         }
         else
         {
            m_ptimeoutfile->m_uiExpectedSize = (uint64_t) -1;
         }

         ::core::emit(get_app(), this, &file::on_http_request_response, &Application.http(), &::http::application::get, psignal);
         return TRUE;
      }

      void file::on_http_request_response(signal_details * pobj)
      {
         UNREFERENCED_PARAMETER(pobj);
      }


   } // namespace http


} // namespace sockets

