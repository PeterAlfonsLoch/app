#include "framework.h"


namespace user
{


   document::document(sp(base_application) papp) :
      element(papp),
      ::ca2::data_container_base(papp)
   {
   
      m_pdocumentemplate = NULL;
      m_bModified = FALSE;
      m_bAutoDelete = TRUE;       // default to auto delete document
      m_bEmbedded = FALSE;        // default to file-based document
      ASSERT(m_viewptra.is_empty());

      m_documentptra.add(this);

   }

   document::~document()
   {
   }



   bool document::set_data(::data * pdata)
   {

      if(m_spdata.is_set())
      {

         remove_data(m_spdata);

      }

      ::data_container::set_data(pdata);

      if(pdata != NULL)
      {

         add_data(pdata);

      }

      return true;

   }





   bool document::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)

   {
      if (command_target::_001OnCmdMsg(pcmdmsg))
         return TRUE;

      // otherwise check template
      if (m_pdocumentemplate != NULL &&
         m_pdocumentemplate->_001OnCmdMsg(pcmdmsg))
         return TRUE;

      return FALSE;
   }


   void document::dump(dump_context & dumpcontext) const
   {
      object::dump(dumpcontext);

      dumpcontext << "m_wstrTitle = " << m_strTitle;
      dumpcontext << "\nm_wstrPathName = " << m_strPathName;
      dumpcontext << "\nm_bModified = " << m_bModified;
      dumpcontext << "\nm_pDocTemplate = " << (void *)m_pdocumentemplate;

      if (dumpcontext.GetDepth() > 0)
      {
         ::count count = get_view_count();
         for(index index = 0; index < count; index++)
         {
            sp(::user::view) pview = get_view(index);
            dumpcontext << "\nwith ::user::view " << (void *)pview;
         }
      }

      dumpcontext << "\n";
   }

   void document::assert_valid() const
   {
      object::assert_valid();

      ::count count = get_view_count();
      for(index index = 0; index < count; index++)
      {
         sp(::user::view) pview = get_view(index);
         ASSERT_VALID(pview);
      }
   }


   void document::on_alloc(sp(base_application) papp)
   {

      //::user::document::on_alloc(papp);
      ::database::client::initialize_data_client(App(papp).simpledb().get_data_server());

   }


} // namespace user


