#pragma once

namespace rtp
{
   class CLASS_DECL_ca file :
      public ex1::file
   {
   public:
      gen::property_set    m_set;
      profile *            m_pprofile;
      session *            m_psession;
      int                  m_iError;
      uint32_t             m_uiTimeStamp;
      DWORD                m_dwSynchSource;
      DWORD                m_dwTimeOut;
      string               m_strListenAddress;
      string               m_strRemoteAddress;
      int                  m_iListenPort;
      int                  m_iRemotePort;

      int                  have_more;
      int                  format;
      int                  jittcomp;
      bool_t               adapt;
      int                  clockslide;
      int                  jitter;

      file(::ca::application * papp);
      virtual ~file();

      bool rx_open(const char * pszAddress, int iPort);
      bool tx_open(const char * pszAddress, int iPort);

      virtual bool IsValid() const;

#if core_level2
      using ex1::file::read;
#endif
      virtual DWORD_PTR read(void *lpBuf, DWORD_PTR nCount);

#if core_level2
      using ex1::file::write;
#endif
      virtual void write(const void * lpBuf, DWORD_PTR nCount);

      virtual void close();


   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif


      void set_payload(const char * pszProfile, PayloadType * ptype, int iIndex = 0);
   };

} // namespace rtp