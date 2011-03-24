#pragma once

class COptionsSongsDirectoriesDialog;

class AlbumOptionsDialog : 
   public dialog
{
public:


   AlbumOptionsDialog ** m_pp;
   COptionsSongsDirectoriesDialog *   m_pSongsDirsDlg;

   
   AlbumOptionsDialog(::ca::application * papp);
   virtual ~AlbumOptionsDialog();

   
   BOOL create(AlbumOptionsDialog ** pp);
   bool Apply();
   virtual void pre_translate_message(gen::signal_object * pobj);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual void PostNcDestroy();

   afx_msg void OnSelchangingTab(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
   virtual bool _001Initialize();
   virtual void OnOK();
   afx_msg void OnApply();
   afx_msg void OnDestroy();
   afx_msg void OnClose();
};
