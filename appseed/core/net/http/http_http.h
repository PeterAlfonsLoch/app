#pragma once


namespace fontopus
{
   class user;

} // namespace fontopus


namespace http
{

   enum e_status
   {
      status_unchanged,
      status_ok,
      status_connection_timed_out,
      status_failed,
   };

   class CLASS_DECL_ca2 signal :
      public signal_details
   {
   public:


      primitive::memory          m_memoryRet;
      e_status                   m_estatusRet;


      string                     m_strUrl;
      property_set          m_setPost;
      property_set          m_setHeaders;
      property_set          m_set;
      ::http::cookies *          m_pcookies;
      ::fontopus::user *         m_puser;
      string                     m_strVersion;


      signal();


   };

} // namespace http
