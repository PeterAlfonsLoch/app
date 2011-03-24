#pragma once



class CLASS_DECL_CA2_CUBE devedgeHtmlEditChildFrame :
   public simple_child_frame
{
public:
   devedgeHtmlEditChildFrame(::ca::application * papp);

     simple_toolbar        m_toolbar;

   afx_msg void OnChangeEditSearch();

   FileManagerInterface * GetFileManager();
   bool CreateBars();
   bool DestroyBars();
   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 
   virtual ~devedgeHtmlEditChildFrame();

   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   DECL_GEN_SIGNAL(_001OnAppLanguage)

   BOOL PreCreateWindow(CREATESTRUCT& cs);
};
