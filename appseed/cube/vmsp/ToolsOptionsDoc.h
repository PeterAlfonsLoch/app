#pragma once


class CLASS_DECL_CA2_CUBE CToolsOptionsDoc :
   public ::userbase::document
{
public:


   stringa        m_wstraSongDirectories;
   bool           m_bSongDirectoriedModified;


   CToolsOptionsDoc(::ca::application * papp);  
   virtual ~CToolsOptionsDoc();



   virtual BOOL on_save_document(const char * lpszPathName);
   virtual BOOL on_new_document();

   bool do_save(const char * lpszPathName, bool bReplace);
   BOOL is_modified();
   void SetSongDirectoriesModified(bool bModified);
   bool IsSongDirectoriesModified();
   bool UpdateSongDirectories(bool bSave);
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   afx_msg void OnUpdateFileSave(cmd_ui * pcmdui);
   afx_msg void OnFileSaveAndClose();
   afx_msg void OnUpdateFileSaveAndClose(cmd_ui * pcmdui);

};

