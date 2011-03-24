#pragma once

class OptionsSongsGeneralDialog :
   public dialog
{
// Construction
public:
   OptionsSongsGeneralDialog(::ca::application * papp);

//   CSpinButtonCtrl   m_spinMRUCount;
   BOOL   m_bMRUEnable;
   int      m_iMRUCount;
   //}}AFX_DATA

      BOOL Update(BOOL bSaveAndValidate = TRUE);
   BOOL UpdateDatabase(BOOL bSaveAndValidate = TRUE);

//    int m_iMRUCount;
//    BOOL m_bMRUEnable;

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(OptionsSongsGeneralDialog)
//   protected:
//   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   virtual BOOL OnInitDialog();
};
