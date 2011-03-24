#pragma once


namespace fontopus
{
   class user;

} // namespace fontopus


namespace ca4
{

   namespace http
   {

      enum e_status
      {
         status_unchanged,
         status_ok,
         status_connection_timed_out,
         status_failed,
      };

      class CLASS_DECL_ca signal :
         public gen::signal_object
      {
      public:


         primitive::memory          m_memoryRet;
         e_status                   m_estatusRet;


         string                     m_strUrl;
         gen::property_set          m_setPost;
         gen::property_set          m_setHeaders;
         ::http::cookies *          m_pcookies;
         ::fontopus::user *         m_puser;
         string                     m_strVersion;


         signal();

         
      };
   
   } // namespace http

} // namespace ca4

