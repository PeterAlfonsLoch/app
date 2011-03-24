#pragma once

class view;


namespace whiteboard
{

   class http_window;
   class view;

   class CLASS_DECL_CA2_CUBE http_thread : 
      public ::radix::thread
   {
   public:
      friend class http_window;
      
      
      enum e_message
      {
         MessageCommand = WM_APP + 493,
         MessageTimer,
         MessageHttpRequest,
         MessageTicketHdl,
      };

      enum ECommand
      {
         CommandViewWhiteboard,
      };

      enum ETimer
      {
         TimerDeferNotify,
         TimerUserHour,
      };


      bool     m_bDeferNotify;
      int      m_iTimerNotify; // in millis
      int      m_iTimerUserHour; // in millis

      bool     m_bLogin;


      http_window * m_pwnd;

      view * m_pview;


      http_thread(::ca::application * papp);
      virtual ~http_thread();

      void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);







      bool Login();
      bool UserHourPulseEvent();
      void GetBaseUrl(string & str);
      bool GetQueryResult(string & str, const char * lpcszQryTyp, const char * lpcszKey);

      bool GetLastChangeTime(class time & time);
      void ViewWhiteboard();
      void PostCommandMessage(ECommand ecommand);

      void OnDirty();

      bool db_getGroupDateTime(string &str,  const char * lpcszOp);
      bool db_getUserDateTime(string &str, const char * lpcszOp);
      bool db_getDateTime(string &str, const char * lpcszKey);
      bool db_getDate(string &str, const char * lpcszKey);
      bool db_getTime(string &str, const char * lpcszKey);

      void OnTime(class time & time, e_time etime);
      void OnViewWhiteboard();
      void DeferNotify();

      virtual bool initialize_instance();
      virtual int exit_instance();


      virtual void pre_translate_message(gen::signal_object * pobj);
      virtual void ProcessMessageFilter(int code, gen::signal_object * pobj);


      DECL_GEN_SIGNAL(OnIWinThread_message_ticket_receiver)
      DECL_GEN_SIGNAL(OnCommandMessage)
      DECL_GEN_SIGNAL(OnTimerMessage)
      DECL_GEN_SIGNAL(OnHttpGet)

   };

} // namespace whiteboard