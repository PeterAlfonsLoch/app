#pragma once

namespace user
{

   class CLASS_DECL_ca2 plain_text_data :
      virtual public ex1::tree_data
   {
   public:


      enum e_update_hint
      {
         update_hint_set_file,
      };

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
         virtual ECommand get_command();
         virtual void Undo(plain_text_data * pedit);
         virtual void Redo(plain_text_data * pedit);

#undef new
         DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION
#define new DEBUG_NEW

      };

      class SetSelCommand : public Command
      {
      public:
         int   m_iSelStart;
         int   m_iSelEnd;
         int   m_iPreviousSelStart;
         int   m_iPreviousSelEnd;
         virtual void Undo(plain_text_data * pedit);
         virtual void Redo(plain_text_data * pedit);
         virtual ECommand get_command(){ return CommandSetSel;};
      };

      class FileCommand : public Command
      {
      public:
         virtual void Undo(plain_text_data * pedit);
         virtual void Redo(plain_text_data * pedit);
         virtual ECommand get_command(){ return CommandFile;};
      };


      class GroupCommand : public Command,
         public base_array < Command *, Command * >
      {
      public:
         GroupCommand();
         GroupCommand * m_pparent;
         virtual ECommand get_command(){ return CommandGroup;};
         virtual void Undo(plain_text_data * pedit);
         virtual void Redo(plain_text_data * pedit);

#undef new
         DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION
#define new DEBUG_NEW

      };


      ::ex1::tree_item *      m_ptreeitem;
      GroupCommand *          m_pgroupcommand;
      int                     m_iBranch;
      ex1::file *             m_pfile;
      ex1::edit_file          m_editfile;


      plain_text_data(::ca::application * papp);
      virtual ~plain_text_data();


      void SetFile(ex1::file * pfile);




   };

} // namespace user

