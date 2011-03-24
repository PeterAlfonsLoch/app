#pragma once

class _declspec(dllexport) front_document :
   public html_document
{
public:
   front_document(::ca::application * papp);   

   virtual bool on_open_document(var varFile);
   virtual BOOL on_save_document(const char * lpszPathName);


   gen::memory_file         m_memfile;
   ex1::filesp           m_file;

   bool _001OnCommand(id id); 
   bool _001OnUpdateCmdUi(cmd_ui * pcmdui); 

   void OnUpdateStart(cmd_ui *pcmdui);
   void OnUpdateEditUndo(cmd_ui *pcmdui);
   void OnUpdateEditRedo(cmd_ui *pcmdui);
   void OnStart();
   void OnEditUndo();
   void OnEditRedo();

   virtual BOOL on_new_document();

   virtual ~front_document();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};

//{{AFX_INSERT_LOCATION}}
// Microsoft visual C++ will insert additional declarations immediately before the previous line.
