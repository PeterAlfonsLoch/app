#pragma once

class CTimerWnd;
class CVMSApp;

class CLASS_DECL_CA2_CUBE CVmpHighThread :
   public ::radix::thread
{
public:
   CVmpHighThread(::ca::application * papp);        // protected constructor used by dynamic creation
   
   critical_section   m_csBitmap;
   DWORD               m_dwImageLoaderEventAdvise;
   critical_section  m_csTimersWindows;
   base_array <CTimerWnd *, CTimerWnd *>   m_timersWindows;
   CVMSApp *         m_pMainApp;
   bool              m_bEnableTimers;
   
   void TranslateApp3388Message(gen::signal_object * pobj);
   bool CreateTimer(gen::TimerCallback * ptc, UINT uiElapse, UINT uiIDEvent);
   int DeleteTimerWnd(CTimerWnd * pTimerWnd);
   ::ca::bitmap * LoadImageSync(const char * lpcsz);
   virtual void ProcessMessageFilter(int code, gen::signal_object * pobj);
   void EnableTimers(bool bEnable = true);
   void DeleteTimersWindows();
   void TranslateUserMessage(gen::signal_object * pobj);

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(XfplayerThreadV1)
   public:
   virtual bool initialize_instance();
   virtual int exit_instance();
   virtual void pre_translate_message(gen::signal_object * pobj);
   virtual BOOL on_idle(LONG lCount);
   virtual int run();
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual ~CVmpHighThread();

   // Generated message ::collection::map functions
   //{{AFX_MSG(XfplayerThreadV1)
      // NOTE - the ClassWizard will add and remove member functions here.
   //}}AFX_MSG

   ()

   afx_msg LRESULT OnVmsmV001(WPARAM wparam, LPARAM lparam);
    
};

