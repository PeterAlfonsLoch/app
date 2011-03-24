#pragma once

class CLASS_DECL_CA2_CUBE CDBrowseView :
   public ::userbase::split_view
{
public:
   CDBrowseView(::ca::application * papp);
   virtual ~CDBrowseView();

   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
   ()
};

