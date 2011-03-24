#pragma once

namespace netshareserver
{
   class socket_thread;

   class CLASS_DECL_NETSHARESERVER session :
      virtual public ::radix::object
   {
   public:

/*      class CLASS_DECL_NETSHARESERVER start_bergedge
      {
      public:
         ::bergedge::bergedge *  m_pbergedge;
         HANDLE                  m_hEventReady;
      };

      ::icube::application *  m_papp;*/
      int                        m_iEdge;
      ::ca::dib_sp               m_dibUser;
      ::ca::dib_sp               m_dibScreen;
      ::ca::dib_sp               m_dibDiff;
      ::ca::dib_sp               m_dibFrame;
      int                        m_iFrameCount;
      int                        m_iFrame;
      mutex                      m_mutexSnapshot;
      bergedge::frame *          m_pframe;
      bool                       m_bDrawCursor;
      bergedge::bergedge *       m_pbergedge;

      session(::ca::application * papp);

      virtual ::bergedge::bergedge * get_bergedge();

      void initialize();
      void take_screenshot();
      void PostMessage(UINT uiMessage, WPARAM wparam, LPARAM lparam);

      //static UINT AFX_CDECL ThreadProcStart(LPVOID lpv);
   };

} // namespace netshareserver