#pragma once


class MixerMainView;
class CMenuV033;
class db_server;
class CWndFrameworkV033;
//class CAlbumOptionsDialog;




class CLASS_DECL_ca MixerFrameWnd :
   public simple_frame_window
{
public:


   ::view *                   m_pMainView;
   CMenuV033 *                m_pmenuv033;
   db_server *                m_pdbcentral;
   simple_toolbar               m_wndToolBar;
   simple_toolbar               m_wndToolBarExport;
   simple_toolbar             m_wndToolBarHtmlView;
   simple_status_bar          m_wndStatusBar;
   bool                        m_bSizeEnable;


   MixerFrameWnd(::ca::application * papp);
   virtual ~MixerFrameWnd();


   bool GetToolButtonText(string &str, UINT uiCmd);
   void UpdateToolBarText(simple_toolbar &toolbar);
   virtual void TwiOnDraw(::ca::graphics * pdc);
   MixerMainView * GetMainView();
   MixerMainView * GetAlbumView();
   
   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
   bool InitializeBars();
   afx_msg LRESULT OnAppLanguage(WPARAM wParam, LPARAM lParam);

   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 
   virtual void pre_translate_message(gen::signal_object * pobj);
   virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, create_context* pContext);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual void PostNcDestroy();

   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnDestroy)
   DECL_GEN_SIGNAL(_001OnMeasureItem)
   DECL_GEN_SIGNAL(_001OnClose)
   DECL_GEN_SIGNAL(_001OnNcDestroy)
   afx_msg bool OnMixerExit();
   afx_msg bool OnToolsOptions();

   DECL_GEN_SIGNAL(OnUserMessage)
   DECL_GEN_VSIGNAL(OnFrameworkV033Command)

};

