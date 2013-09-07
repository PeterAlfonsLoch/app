#pragma once

namespace user
{

   class CLASS_DECL_ca2 plain_text_data :
      public ::data::tree_data
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

      class Command : public ::core::tree_item_data
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
         public spa(Command)
      {
      public:
         GroupCommand();
         sp(GroupCommand) m_pparent;
         virtual ECommand get_command(){ return CommandGroup;};
         virtual void Undo(plain_text_data * pedit);
         virtual void Redo(plain_text_data * pedit);

#undef new
         DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION
#define new DEBUG_NEW

      };


      sp(::data::tree_item)     m_ptreeitem;
      sp(GroupCommand)        m_pgroupcommand;
      index                   m_iBranch;
      ::file::buffer_sp            m_pfile;
      ::core::::file::edit_buffer         m_editfile;
      
      
      strsize                 m_iSelStart;
      strsize                 m_iSelEnd;


      plain_text_data(sp(base_application) papp);
      virtual ~plain_text_data();


      void SetFile(::file::buffer_sp pfile);


   private:

      plain_text_data(const plain_text_data & ) :
         m_editfile(NULL),
         ::data::tree_data(NULL)
      {
      }

   };


} // namespace user



