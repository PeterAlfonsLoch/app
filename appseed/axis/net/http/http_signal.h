#pragma once


namespace http
{


   class CLASS_DECL_BASE signal :
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
