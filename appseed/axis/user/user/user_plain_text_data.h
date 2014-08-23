#pragma once

namespace user
{


   class plain_text_group_command;

   enum e_plain_text_command
   {
      plain_text_command_none,
      plain_text_command_set_sel,
      plain_text_command_file,
      plain_text_command_group,
   };


   class CLASS_DECL_AXIS plain_text_tree :
      public ::data::tree
   {
   public:


      enum e_update_hint
      {
         update_hint_set_file,
      };





      sp(plain_text_group_command)     m_pgroupcommand;
      index                            m_iBranch;
      ::file::buffer_sp                m_pfile;
      ::file::edit_buffer              m_editfile;
      
      
      strsize                          m_iSelStart;
      strsize                          m_iSelEnd;


      plain_text_tree(sp(::aura::application) papp);
      virtual ~plain_text_tree();


      void SetFile(::file::buffer_sp  pfile);


   };

   class plain_text_command : public ::data::item
   {
   public:
      virtual e_plain_text_command get_command();
      virtual void Undo(plain_text_tree * pedit);
      virtual void Redo(plain_text_tree * pedit);

#undef new
      DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION
#define new AXIS_NEW

   };


   class plain_text_set_sel_command : public plain_text_command
   {
   public:
      strsize   m_iSelStart;
      strsize   m_iSelEnd;
      strsize   m_iPreviousSelStart;
      strsize   m_iPreviousSelEnd;
      virtual void Undo(plain_text_tree * pedit);
      virtual void Redo(plain_text_tree * pedit);
      virtual e_plain_text_command get_command(){ return plain_text_command_set_sel; };
   };

   class plain_text_file_command : public plain_text_command
   {
   public:
      virtual void Undo(plain_text_tree * pedit);
      virtual void Redo(plain_text_tree * pedit);
      virtual e_plain_text_command get_command(){ return plain_text_command_file; };
   };


   class plain_text_group_command : public plain_text_command,
      public spa(plain_text_command)
   {
   public:
      
      sp(plain_text_command) m_pparent;

      plain_text_group_command();
      virtual e_plain_text_command get_command(){ return plain_text_command_group; };
      virtual void Undo(plain_text_tree * pedit);
      virtual void Redo(plain_text_tree * pedit);

#undef new
      DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION
#define new AXIS_NEW

      };

} // namespace user



