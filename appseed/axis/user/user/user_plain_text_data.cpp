#include "framework.h"


namespace user
{


   plain_text_tree::plain_text_tree(sp(::aura::application) papp) :
      element(papp),
      ::data::data(papp),
      ::data::tree(papp),
      m_editfile(papp)
   {
      m_pgroupcommand      = NULL;
      m_pfile              = NULL;
      m_iBranch            = 0;
   }

   plain_text_tree::~plain_text_tree()
   {
   }


   void plain_text_tree::SetFile(::file::buffer_sp  pfile)
   {
      m_editfile.SetFile(pfile);
   }




   e_plain_text_command plain_text_command::get_command()
   {
      return plain_text_command_none;
   }

   void plain_text_command::Undo(plain_text_tree * pedit)
   {
      UNREFERENCED_PARAMETER(pedit);
   }

   void plain_text_command::Redo(plain_text_tree * pedit)
   {
      UNREFERENCED_PARAMETER(pedit);
   }



   void plain_text_set_sel_command::Undo(plain_text_tree * pdoc)
   {
      UNREFERENCED_PARAMETER(pdoc);
      pdoc->m_iSelStart = m_iPreviousSelStart;
      pdoc->m_iSelEnd = m_iPreviousSelEnd;
   }
   void plain_text_set_sel_command::Redo(plain_text_tree * pdoc)
   {
      UNREFERENCED_PARAMETER(pdoc);
      pdoc->m_iSelStart = m_iSelStart;
      pdoc->m_iSelEnd = m_iSelEnd;
   }

   void plain_text_file_command::Undo(plain_text_tree * pdoc)
   {
      pdoc->m_editfile.Undo();
   }

   void plain_text_file_command::Redo(plain_text_tree * pdoc)
   {
      pdoc->m_editfile.Redo();
   }




   plain_text_group_command::plain_text_group_command()
   {

      m_pparent = NULL;

   }

   void plain_text_group_command::Undo(plain_text_tree * pdoc)
   {

      for(index i = get_upper_bound(); i >= 0; i--)
      {
         this->element_at(i)->Undo(pdoc);
      }

   }

   void plain_text_group_command::Redo(plain_text_tree * pdoc)
   {

      for(index i = 0; i < this->get_size(); i++)
      {
         this->element_at(i)->Redo(pdoc);
      }

   }


} // namespace user



