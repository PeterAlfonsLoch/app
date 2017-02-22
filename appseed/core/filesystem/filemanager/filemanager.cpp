

namespace core
{


   // prompt for file name - used for open and save as
   bool application::do_prompt_file_name(var & varFile, UINT nIDSTitle, uint32_t lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument)
      // if ptemplate==NULL => all document templates
   {
      if (Session.m_pfilemanager != NULL)
      {
         return Session.m_pfilemanager->do_prompt_file_name(varFile, nIDSTitle, lFlags, bOpenFileDialog, ptemplate, pdocument);
      }
      ENSURE(m_pdocmanager != NULL);
      /*      return document_manager().do_prompt_file_name(fileName, nIDSTitle, lFlags,
      bOpenFileDialog, ptemplate);*/
      return FALSE;
   }

   bool session::on_initial_update()
   {

      if (m_pfilemanager == NULL)
      {

         m_pfilemanager = new ::filemanager::filemanager(this);

         m_pfilemanager->construct(this);

         if (!m_pfilemanager->initialize())
         {
            return false;

         }

         filemanager().std().m_strLevelUp = "levelup";

      }

      return true;

   }


   string session::filemanager_get_initial_browse_path()
   {
      return filemanager().get_initial_browse_path();
   }




} // namespace core


