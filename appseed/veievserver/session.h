#pragma once

namespace veievserver
{
   class socket_thread;

   class CLASS_DECL_VEIEVSERVER session :
      virtual public ::radix::object
   {
   public:

      class CLASS_DECL_VEIEVSERVER start_bergedge
      {
      public:
         bergedge::bergedge *          m_pbergedge;
         HANDLE                        m_hEventReady;
      };

      bergedge::bergedge *    m_pbergedge;
      ::ca::dib_sp            m_dibUser;
      ::ca::dib_sp            m_dibScreen;
      ::ca::dib_sp            m_dibDiff;
      ::ca::dib_sp            m_dibFrame;
      int                     m_iFrameCount;
      int                     m_iFrame;
      mutex                   m_mutexSnapshot;
      bergedge::frame *       m_pframe;
      bool                    m_bDrawCursor;

      session(::ca::application * papp);

      void initialize();
      void take_screenshot();
      void PostMessage(UINT uiMessage, WPARAM wparam, LPARAM lparam);

      static UINT AFX_CDECL ThreadProcStart(LPVOID lpv);
   };

} // namespace veievserver