#pragma once

class CLASS_DECL_CA2_CUBE devedgeHtmlDoc :
   public html_document
{
public:
   devedgeHtmlDoc(::ca::application * papp);           // protected constructor used by dynamic creation
   // // DECLARE_DYNCREATE(devedgeHtmlDoc)

// Attributes
public:
   virtual bool on_open_document(var varFile);
   virtual BOOL on_save_document(const char * lpszPathName);

   enum ECommand
   {
      CommandSetSel,
      CommandFile,
      CommandGroup,
   };


   gen::memory_file         m_memfile;
   ex1::filesp           m_file;
   int m_iBranch;



// Operations
public:
   bool _001OnCommand(id id);
   bool _001OnUpdateCmdUi(cmd_ui * pcmdui);

   void OnUpdateFileSave(cmd_ui *pcmdui);
   void OnUpdateEditUndo(cmd_ui *pcmdui);
   void OnUpdateEditRedo(cmd_ui *pcmdui);
   void on_file_save();
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
   virtual ~devedgeHtmlDoc();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};

