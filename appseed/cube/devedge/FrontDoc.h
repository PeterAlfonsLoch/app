#pragma once

class CLASS_DECL_CA2_CUBE devedgeFrontDoc :
   public html_document
{
public:
   devedgeFrontDoc(::ca::application * papp);    

   virtual bool on_open_document(var varFile);
   virtual BOOL on_save_document(const char * lpszPathName);


   gen::memory_file         m_memfile;
   ex1::filesp           m_file;
   gen::memory_file       m_memfileBody;

   bool _001OnUpdateCmdUi(cmd_ui * pcmdui);
   bool _001OnCommand(id id);

   void get_output(const char * lpcsz, string &strHead, gen::memory_file & file);

   void OnUpdateStart(cmd_ui *pcmdui);
   void OnUpdateEditUndo(cmd_ui *pcmdui);
   void OnUpdateEditRedo(cmd_ui *pcmdui);
   void OnStart();
   void OnEditUndo();
   void OnEditRedo();

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(screencaptureDoc)
   public:
//   virtual void Serialize(CArchive& ar);   // overridden for document i/o
   protected:
   virtual BOOL on_new_document();
   //}}AFX_VIRTUAL

// Implementation
public:
   virtual ~devedgeFrontDoc();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};
