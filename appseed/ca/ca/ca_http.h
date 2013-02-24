#pragma once


namespace fontopus
{
   class user;

} // namespace fontopus


namespace ca
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
         public ca::signal_object
      {
      public:


         primitive::memory          m_memoryRet;
         e_status                   m_estatusRet;


         string                     m_strUrl;
         ca::property_set          m_setPost;
         ca::property_set          m_setHeaders;
         ca::property_set          m_set;
         ::http::cookies *          m_pcookies;
         ::fontopus::user *         m_puser;
         string                     m_strVersion;


         signal();

         
      };
   
   } // namespace http

} // namespace ca

