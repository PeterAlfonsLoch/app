#include "StdAfx.h"

namespace sockets
{
   namespace http
   {

      file::file(::ca::application * papp) :
         ca(papp)
      {
         m_pmemory = new primitive::memory;
         m_pmemory->set_app(papp);
         m_pmemoryfileIn = new gen::memory_file(papp, *m_pmemory);
         m_pmemoryfileIn->m_bSynch = true;
         m_pmemoryfileOut = new gen::memory_file(papp, *m_pmemory);
         m_pmemoryfileOut->m_bSynch = true;
         m_ptimeoutfile = new ex1::timeout_file(papp, m_pmemoryfileOut);
         ::ex1::filesp::m_p = m_ptimeoutfile;
         m_ptimeoutfile->m_dwSleep = 284;
         m_ptimeoutfile->m_dwTimeOut = 184 * 1000;
      }

         // it is not currently designed to call open.
         //
      file::file(::ca::application * papp, ::gen::memory_file * pmemoryfileIn) :
         ca(papp)
      {
         m_pmemory = pmemoryfileIn->get_memory();
         m_pmemoryfileIn = pmemoryfileIn;
         m_pmemoryfileIn->m_bSynch = true;
         m_pmemoryfileOut = new gen::memory_file(papp, *m_pmemory);
         m_pmemoryfileOut->m_bSynch = true;
         m_ptimeoutfile = new ex1::timeout_file(papp, m_pmemoryfileOut);
         ::ex1::filesp::m_p = m_ptimeoutfile;
         m_ptimeoutfile->m_dwSleep = 284;
         m_ptimeoutfile->m_dwTimeOut = 184 * 1000;
      }

      
      BOOL file::open(const char * lpszFileName, UINT nOpenFlags, ex1::file_exception_sp * pError)
      {
         ca4::http::signal * psignal = new ca4::http::signal;

         m_pmemoryfileIn->m_ulFlags &= ~ca::flag_auto_clean;
         m_pmemoryfileOut->m_ulFlags &= ~ca::flag_auto_clean;
         m_ptimeoutfile->m_ulFlags &= ~ca::flag_auto_clean;

         (*psignal)()["file"] = (::ca::object *) m_pmemoryfileIn;
         (*psignal)()["file_out"] = (::ca::object *) m_ptimeoutfile;
         /*gen::property_set set(get_app());
         set.parse_url_query(System.url().get_query(lpszFileName));
         string strObject = System.url().url_encode(System.url().get_object(lpszFileName));
         strObject.replace("+", "%20");
         strObject = gen::str::replace_ci("%2F", "/", strObject);*/
         psignal->m_strUrl = lpszFileName; /*
            System.url().get_protocol(lpszFileName) +
            "://" + System.url().get_server(lpszFileName) +
            + strObject +
            gen::str::has_char(set.get_http_post(), "?");*/

         gen::emit(get_app(), this, &file::on_http_request_response, &Application.http(), &ca4::http::application::get, psignal);
         return TRUE;
      }

      void file::on_http_request_response(gen::signal_object * pobj)
      {
         //m_strTimePath
         /*SCAST_PTR(ca4::http::signal, psignal, pobj);

         string strResponse;

         psignal->m_memoryRet.to_string(strResponse);

         m_ptree->Parse((*psignal)()["request"], strResponse);
         m_plist->Parse(strResponse);*/
      }


   } // namespace http

} // namespace sockets