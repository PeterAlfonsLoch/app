#pragma once


/////////////////////////////////////////////////////////////////////////////
// front_child_frame frame

class _declspec(dllexport) front_child_frame :
   public simple_child_frame
{
public:
   front_child_frame(::ca::application * papp);

     simple_toolbar        m_toolbar;

   afx_msg void OnChangeEditSearch();

   FileManagerInterface * GetFileManager();

   bool CreateBars();
   bool DestroyBars();

   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 

   virtual ~front_child_frame();

   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

   DECL_GEN_SIGNAL(_001OnAppLanguage)

   BOOL PreCreateWindow(CREATESTRUCT& cs);
};
