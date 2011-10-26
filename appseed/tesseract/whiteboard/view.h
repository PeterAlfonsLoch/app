#pragma once

class html_view;
class options_view;
class document;

namespace whiteboard
{

   class main_frame;

   class CLASS_DECL_CA2_TESSERACT view : 
      virtual public ::userex::pane_tab_view
   {
      friend class html_view;
      friend class ::whiteboard::main_frame;

   public:
      
      enum ETimer
      {
         TimerNotify,
         TimerIconFlash,
         TimerHoverOut,
         TimerUserHour,
         TimerWTSRegisterSessionNotification,
      };

      enum EView
      {
         ViewHtml,
         ViewOptions,
         ViewWindow,
         ViewMrtsHtml,
         ViewMrtsQuerylistHtml,
         ViewUserHour
      };
      
      class ThreadProcInfo
      {
      public:
         view *     m_pview;
         user_hour::e_event     m_eevent;
      };

      html_view *            m_phtmlview;
      html_view *            m_phtmlviewMrts;
      html_view *            m_phtmlviewMrtsQuerylist;
      options_view *    m_poptionsview;
      ::userbase::view                   *  m_pview;
      EView                      m_eview;
      string                    m_strPreviousHome;
      ::collection::map < string, string, HICON, HICON > m_mapIcon;
      int                    m_iWTSRegisterSessionNotificationRetry;
      bool                    m_bWTSRegisterSessionNotification;
      
      NOTIFYICONDATA             m_nid;
      NOTIFYICONDATA             m_nidCalendar;
      NOTIFYICONDATA             m_nidMrts;
      NOTIFYICONDATA             m_nidMrtsQuerylist;


      bool     m_bHover;
      int      m_iIcon;
      int      m_iTimerIconFlash;
      int      m_iShowCalendarTrayIcon;
      bool     m_bSessionLocked;

      string                    m_strHtmlTitle;
      string                    m_strOptionsTitle;

      view(::ca::application * papp);
      virtual ~view();



      void on_create_view(::user::view_creator_data * pcreatordata);
      void on_show_view();

      void OnTimerUserHour();


      // HTML browsing
      void URLOpenNew(const char * lpcsz, bool bMakeVisible);
      void MrtsUrlOpenNew(const char * lpcsz, bool bMakeVisible);
      void MrtsQuerylistUrlOpenNew(const char * lpcsz, bool bMakeVisible);

      // Notification
      void UpdateCalendarTrayIcon();
      void UpdateMrtsTrayIcon();
      void UpdateMrtsQuerylistTrayIcon();
      bool IsNotified();
      void UpdateNotifyIcon(const char * pszMatter);
      void OnTimerNotify();
      void NotifyIconPopup();
      void MarkAsNotified();


      static UINT AFX_CDECL ThreadProc_UserHour_PulseEvent(LPVOID lpvoid);
      bool DeferWTSRegisterSessionNotification();


      void UpdateFrameTitle();
      void OnDirty();
      whiteboard::http_thread & GetConnectionThread(void);
      document* get_document();

      void OnWb();

      virtual void OnDraw(::ca::graphics * pgraphics);      // overridden to draw this ::view
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      void OnWtsSessionLock();
      void OnWtsSessionUnlock();
      void OnWtsSessionLogon();
      void OnWtsSessionLogoff();

      void ViewWhiteboard(bool bMAkeVisible);

      virtual void install_message_handling(::user::win::message::dispatch * pinterface);

      virtual void on_update(::view * /*pSender*/, LPARAM /*lHint*/, ::radix::object* /*pHint*/);
      void _UserHour_PulseEvent(user_hour::e_event eevent);
      bool _UserHour_PulseEvent(user_hour::e_event eevent, int iRetry);
      void _Backup(const char * lpcszPath);
      bool _Backup(const char * lpcszPath, int iRetry);
      void _BackupAndRestore(const char * lpcszPath);

      void LayoutChild(void);
      bool IsSessionLocked(void);
      
      void UserHour_PulseEvent(user_hour::e_event eevent);
      void ShowNotifyIcon(int iId, bool bShow);
      HICON GetIcon(const char * psz);
      bool IsInMrts(void);
      bool IsInMrtsQuerylist(void);

      void OnEndSessionLogoff();
      void OnEndSessionShutdown();


      void OnViewMrts();
      void OnUpdateViewMrts(cmd_ui *pcmdui);
      void OnUpdateViewMrtsQuerylist(cmd_ui *pcmdui);
      void OnViewMrtsQuerylist();
      virtual void OnInitialUpdate();
      void OnViewBrowser();
      LRESULT OnCalendarIcon(WPARAM wparam, LPARAM lparam);
      LRESULT OnMrtsIcon(WPARAM wparam, LPARAM lparam);

      DECL_GEN_SIGNAL(_001OnViewWhiteboard);
      DECL_GEN_SIGNAL(_001OnUpdateViewWhiteboard);
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnNotifyIcon)
      DECL_GEN_SIGNAL(_001OnDestroy)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnEraseBkgnd)
      DECL_GEN_SIGNAL(_001OnWtsSessionChange)


   };

} // namespace whiteboard
