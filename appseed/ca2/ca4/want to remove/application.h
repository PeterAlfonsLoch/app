#pragma once

namespace ca8
{

   class CLASS_DECL_ca2api00200002 application :
      virtual public colorertake5::application,
      virtual public sockets::application_interface
   {
   protected:
      class ::ca4::compress   m_compress;
      class ::ca4::patch      m_patch;
      class ::ca5::crypt      m_crypt;
      class ::ca27::http      m_http;
      class ::ca27::email     m_email;
      class ::ca36::file      m_file;
      class ::copydesk *      m_pcopydesk;

   public:
      application();
      virtual ~application();

      virtual bool base_support();

      bool sync_load_url(string & str, const char * lpszUrl, ca2::user * puser = NULL, ::http::cookies * pcookies = NULL);

      virtual bool initialize();
      virtual int exit_instance();

      DECL_GEN_SIGNAL(on_application_signal);

      class ::ca4::compress   & compress();
      class ::ca4::patch      & patch();
      class ::ca5::crypt      & crypt();
      class ::ca27::http      & http();
      class ::ca27::email     & email();
      class ::ca36::file      & file36();
      class ::copydesk        & copydesk();

      virtual void http_config_proxy(http_tunnel * psocket);

   };

   inline CLASS_DECL_ca2api00200002 application & cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

} // namespace ca