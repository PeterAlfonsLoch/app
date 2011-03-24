#pragma once

class CLASS_DECL_CA2_CUBE devedgeHtmlEditDoc :
   public html_document
{
public:
   devedgeHtmlEditDoc(::ca::application * papp);


   virtual bool on_open_document(var varFile);
   virtual BOOL on_save_document(const char * lpszPathName);


   gen::memory_file         m_memfile;
   ex1::filesp           m_file;

   bool _001OnCommand(id id);
   bool _001OnUpdateCmdUi(cmd_ui * pcmdui);

   void OnUpdateFileSave(cmd_ui *pcmdui);
   void OnUpdateEditUndo(cmd_ui *pcmdui);
   void OnUpdateEditRedo(cmd_ui *pcmdui);
   void on_file_save();
   void OnEditUndo();
   void OnEditRedo();
   virtual BOOL on_new_document();
public:
   virtual ~devedgeHtmlEditDoc();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};
