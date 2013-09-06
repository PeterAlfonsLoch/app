#include "framework.h"


namespace user
{


   plain_text_data::plain_text_data(sp(base_application) papp) :
      element(papp),
      ::data::tree_data(papp),
      m_editfile(papp)
   {
      m_pgroupcommand      = NULL;
      m_ptreeitem          = NULL;
      m_pfile              = NULL;
      m_iBranch            = 0;
   }

   plain_text_data::~plain_text_data()
   {
   }


   void plain_text_data::SetFile(::file::buffer_sp pfile)
   {
      m_editfile.SetFile(pfile);
      on_update_data(update_hint_set_file);
   }




   plain_text_data::ECommand plain_text_data::Command::get_command()
   {
      return CommandUndefined;
   }

   void plain_text_data::Command::Undo(plain_text_data * pedit)
   {
      UNREFERENCED_PARAMETER(pedit);
   }

   void plain_text_data::Command::Redo(plain_text_data * pedit)
   {
      UNREFERENCED_PARAMETER(pedit);
   }



   void plain_text_data::SetSelCommand::Undo(plain_text_data * pdoc)
   {
      UNREFERENCED_PARAMETER(pdoc);
      pdoc->m_iSelStart = m_iPreviousSelStart;
      pdoc->m_iSelEnd = m_iPreviousSelEnd;
   }
   void plain_text_data::SetSelCommand::Redo(plain_text_data * pdoc)
   {
      UNREFERENCED_PARAMETER(pdoc);
      pdoc->m_iSelStart = m_iSelStart;
      pdoc->m_iSelEnd = m_iSelEnd;
   }

   void plain_text_data::FileCommand::Undo(plain_text_data * pdoc)
   {
      pdoc->m_editfile.Undo();
   }

   void plain_text_data::FileCommand::Redo(plain_text_data * pdoc)
   {
      pdoc->m_editfile.Redo();
   }




   plain_text_data::GroupCommand::GroupCommand()
   {

      m_pparent = NULL;

   }

   void plain_text_data::GroupCommand::Undo(plain_text_data * pdoc)
   {

      for(index i = get_upper_bound(); i >= 0; i--)
      {
         this->element_at(i)->Undo(pdoc);
      }

   }

   void plain_text_data::GroupCommand::Redo(plain_text_data * pdoc)
   {

      for(index i = 0; i < this->get_size(); i++)
      {
         this->element_at(i)->Redo(pdoc);
      }

   }


} // namespace user



