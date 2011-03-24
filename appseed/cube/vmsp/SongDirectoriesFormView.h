#pragma once

class CToolsOptionsDoc;

class CLASS_DECL_CA2_CUBE CSongDirectoriesFormView : public form_view
{
protected:
   CSongDirectoriesFormView(::ca::application * papp); 

// Form Data
public:
   //{{AFX_DATA(CSongDirectoriesFormView)
   //enum { IDD = IDD_OPTIONS_SONGS_DIRECTORIES };
      // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA

// Attributes
public:
   CToolsOptionsDoc * get_document();

// Operations
public:
   bool UpdateForm(bool bSave);

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CSongDirectoriesFormView)
   public:
   virtual void OnInitialUpdate();
   protected:
//   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual ~CSongDirectoriesFormView();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   // Generated message ::collection::map functions
   //{{AFX_MSG(CSongDirectoriesFormView)
   afx_msg void OnAdd();
   afx_msg void OnRemove();
   afx_msg void OnAddSongDirectory();
   afx_msg void OnUpdateAddSongDirectory(cmd_ui * pcmdui);
   afx_msg void OnRemoveSongDirectory();
   afx_msg void OnUpdateRemoveSongDirectory(cmd_ui * pcmdui);
   //afx_msg void on_file_save();
   //afx_msg void OnUpdateFileSave(cmd_ui * pcmdui);
   //}}AFX_MSG
   ()
};


#ifndef _DEBUG  // debug version in xfplayer4View.cpp
inline CToolsOptionsDoc* CSongDirectoriesFormView::get_document()
   { return (CToolsOptionsDoc*)::view::get_document(); }
#endif


