#pragma once

namespace verisimplevideo
{

   class CLASS_DECL_CA2_TESSERACT frame : public simple_child_frame
   {
   public:
      frame(::ca::application * papp);

      string                     m_strAnimatedStatusBarText;
      int                        m_iAnimateStep;
      image_list *                m_pimagelist;
      bool m_bTimerOn;



      virtual void install_message_handling(::user::win::message::dispatch * pinterface);

      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      //virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 
      void ShowControlBars(bool bShow);
      void AnimateStatusBar();
      void SetAnimatedStatusBarText(const char * lpcsz);
      virtual ~frame();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      bool m_bHoverMouse;
      DWORD m_dwLastHover;

      void OnHoverAction();


   //   simple_menu_bar     m_menubar;
   //   SimpleDialogBar   m_dialogbar;
   //xxx   SimpleReBar       m_wndReBar;
   //   simple_status_bar   m_statusbar;
   //   simple_toolbar     m_toolbar;
   //   simple_toolbar     m_toolbarView;


      DECL_GEN_SIGNAL(_001OnCreate)
      void OnTimer(UINT nIDEvent);
   };


} // namespace verisimplevideo
