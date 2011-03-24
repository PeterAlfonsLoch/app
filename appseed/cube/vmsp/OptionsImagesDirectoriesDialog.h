#pragma once

class OptionsSongsImagesDirectoriesDialog :
   public dialog
{
// Construction
public:
   bool is_modified();
   OptionsSongsImagesDirectoriesDialog(::ca::application * papp);

   stringa   m_ImagesDirs;
   bool         m_bModified;

   void set_modified_flag(bool bModified = true);
   BOOL Update(BOOL bSaveAndValidate = TRUE);
   BOOL UpdateDatabase(BOOL bSaveAndValidate = TRUE);

   virtual BOOL DestroyWindow();
   protected:
//   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   virtual BOOL OnInitDialog();
   afx_msg void OnAdd();
   afx_msg void OnRemove();
};

