#pragma once

class CLASS_DECL_CA2_TESSERACT devedgeHtmlChildFrame :
   public simple_child_frame
{
public:
   devedgeHtmlChildFrame(::ca::application * papp);
     simple_toolbar        m_toolbar;

   void OnChangeEditSearch();

   FileManagerInterface * GetFileManager();

   bool CreateBars();
   bool DestroyBars();

   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 

   virtual ~devedgeHtmlChildFrame();

   int OnCreate(LPCREATESTRUCT lpCreateStruct);

   DECL_GEN_SIGNAL(_001OnAppLanguage)

   BOOL devedgeHtmlChildFrame::PreCreateWindow(CREATESTRUCT& cs);
};

