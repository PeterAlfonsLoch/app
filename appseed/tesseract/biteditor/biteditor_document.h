#pragma once

class _declspec(dllexport) biteditor_document :
   virtual public ::userbase::document,
   virtual public ex1::tree_data,
   virtual public ex1::tree
{
public:

   enum ECommand
   {
      CommandUndefined,
      CommandSetSel,
      CommandFile,
      CommandGroup,
   };

   class Command : public ex1::tree_item_data
   {
   public:
      virtual ECommand get_command() { return CommandUndefined; }
      virtual void Undo(biteditor_document * pdoc) {UNREFERENCED_PARAMETER(pdoc);}
      virtual void Redo(biteditor_document * pdoc) {UNREFERENCED_PARAMETER(pdoc);}

#undef new
         DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION
#define new DEBUG_NEW

   };

   class SetSelCommand : public Command
   {
   public:
      file_position   m_iSelStart;
      file_position   m_iSelEnd;
      file_position   m_iPreviousSelStart;
      file_position   m_iPreviousSelEnd;
      virtual void Undo(biteditor_document * pdoc);
      virtual void Redo(biteditor_document * pdoc);
      virtual ECommand get_command(){ return CommandSetSel;};
   };

   class FileCommand : public Command
   {
   public:
      virtual void Undo(biteditor_document * pdoc);
      virtual void Redo(biteditor_document * pdoc);
      virtual ECommand get_command(){ return CommandFile;};
   };


   class GroupCommand : public Command,
      public base_array < Command *, Command * >
   {
   public:
      GroupCommand * m_pparent;
      virtual ECommand get_command(){ return CommandGroup;};
      virtual void Undo(biteditor_document * pdoc);
      virtual void Redo(biteditor_document * pdoc);

#undef new
         DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION
#define new DEBUG_NEW

   };

   ::ex1::tree_item *      m_ptreeitem;

   gen::memory_file        m_memfile;
   ex1::filesp             m_pfile;
   ex1::edit_file *        m_peditfile;
   file_position           m_iSelStart;
   file_position           m_iSelEnd;
   int                     m_iBranch;

   GroupCommand *          m_pgroupcommand;
   bool                    m_bReadOnly;


   biteditor_document(::ca::application * papp);
   virtual ~biteditor_document();


   virtual bool on_open_document(var varFile);
   virtual BOOL on_save_document(const char * lpszPathName);

   bool CanUndo();
   int GetRedoBranchCount();
   bool Undo();
   bool Redo();

   void reload();


   void MacroBegin();
   void MacroRecord(Command * pcommand);
   void MacroEnd();
   DECL_GEN_VSIGNAL(data_on_after_change);

   bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

   DECL_GEN_SIGNAL(_001OnUpdateFileSave)
   DECL_GEN_SIGNAL(_001OnUpdateFilePut)
   DECL_GEN_SIGNAL(_001OnUpdateEditUndo)
   DECL_GEN_SIGNAL(_001OnUpdateEditRedo)
   DECL_GEN_SIGNAL(_001OnUpdateEditCut)
   DECL_GEN_SIGNAL(_001OnUpdateEditCopy)
   DECL_GEN_SIGNAL(_001OnUpdateEditPaste)
   DECL_GEN_SIGNAL(_001OnFileSave)
   DECL_GEN_SIGNAL(_001OnFilePut)
   DECL_GEN_SIGNAL(_001OnEditUndo)
   DECL_GEN_SIGNAL(_001OnEditRedo)
   DECL_GEN_SIGNAL(_001OnEditCut)
   DECL_GEN_SIGNAL(_001OnEditCopy)
   DECL_GEN_SIGNAL(_001OnEditPaste)

   void Put();
   void FtpPut(const char * lpcszLocal, const char * lpcszRemote);

   virtual BOOL on_new_document();
   
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   virtual ex1::tree_item_data * on_allocate_item();
   virtual void on_delete_item(ex1::tree_item_data * pitem);

};

