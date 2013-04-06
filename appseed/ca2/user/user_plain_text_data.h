#pragma once

namespace user
{

   class CLASS_DECL_ca2 plain_text_data :
      public ::ca::tree_data
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

      class Command : public ::ca::tree_item_data
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
         strsize   m_iSelStart;
         strsize   m_iSelEnd;
         strsize   m_iPreviousSelStart;
         strsize   m_iPreviousSelEnd;
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
         public array < Command *, Command * >
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


      ::ca::tree_item *       m_ptreeitem;
      GroupCommand *          m_pgroupcommand;
      index                   m_iBranch;
      ::ca::file *            m_pfile;
      ::ca::edit_file         m_editfile;
      
      
      strsize                 m_iSelStart;
      strsize                 m_iSelEnd;


      plain_text_data(sp(::ca::application) papp);
      virtual ~plain_text_data();


      void SetFile(::ca::file * pfile);


   private:

      plain_text_data(const plain_text_data & ) :
         m_editfile(::null()),
         ::ca::tree_data(::null())
      {
      }

   };


} // namespace user



