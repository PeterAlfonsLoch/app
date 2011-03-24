#pragma once


class CToolV023Dialog : public dialog
{
public:
   virtual void OnOK( );
   virtual void OnCancel();
   CToolV023Dialog(::ca::application * papp);

   ::ca::window    * m_pwndCloseWindow;
   ::radix::object * m_pobjSource;
//   simple_edit   m_edit;

   virtual BOOL DestroyWindow();
//   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual void PostNcDestroy();

   afx_msg void OnClose();
   afx_msg void OnDestroy();
   afx_msg LRESULT OnVMSNotify(WPARAM wParam, LPARAM lParam);
};

