#if !defined(AFX_FileManagerFrame_H__34A118B5_AC52_4060_9C66_A9058218A705__INCLUDED_)
#define AFX_FileManagerFrame_H__34A118B5_AC52_4060_9C66_A9058218A705__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileManagerFrame.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// FileManagerFrame frame

class CLASS_DECL_ca FileManagerFrame :
   public simple_frame_window
{
public:
   FileManagerFrame(::ca::application * papp);

   simple_menu_bar           m_menubar;
     simple_toolbar           m_toolbar;
   bool CreateBars();
   virtual ~FileManagerFrame();

public:
   id m_idTab;

   bool DestroyBars();

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

   DECL_GEN_SIGNAL(_001OnSetText)

   // Generated message ::collection::map functions
   //{{AFX_MSG(FileManagerFrame)
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   //}}AFX_MSG
   ()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FileManagerFrame_H__34A118B5_AC52_4060_9C66_A9058218A705__INCLUDED_)
