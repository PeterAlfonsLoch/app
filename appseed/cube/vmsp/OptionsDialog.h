#pragma once

class OptionsSongsDirectoriesDialog;
class OptionsSongsGeneralDialog;
class OptionsSongsImagesDirectoriesDialog;
class OptionsSongsImagesDialog;
class OptionsSongsAudioDevicesDialog;

class OptionsDialog :
   public dialog
{
public:
   bool Apply();
   OptionsDialog(::ca::application * papp);
   ~OptionsDialog();   
   OptionsSongsGeneralDialog *               m_pdlgGeneral;
   OptionsSongsImagesDirectoriesDialog *   m_pImagesDirsDlg;
   OptionsSongsImagesDialog   *         m_pImagesDlg;
   OptionsSongsAudioDevicesDialog *      m_pAudioDevsDlg;
   

//   enum { IDD = IDD_OPTIONS };
   //simple_tab_control   m_Tab;

   virtual void pre_translate_message(gen::signal_object * pobj);
//   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   afx_msg void OnSelchangingTab(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
   virtual BOOL OnInitDialog();
   virtual void OnOK();
   afx_msg void OnApply();
   afx_msg void OnDestroy();
};

