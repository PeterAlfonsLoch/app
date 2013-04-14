#include "framework.h"


namespace user
{


   document::document(sp(::ca::application) papp) :
      ca(papp),
      ::ca::data_container_base(papp),
      ::ca::data_container(papp)

   {
   
      m_pdocumentemplate = ::null();
      m_bModified = FALSE;
      m_bAutoDelete = TRUE;       // default to auto delete document
      m_bEmbedded = FALSE;        // default to file-based document
      ASSERT(m_viewptra.is_empty());

      m_documentptra.add(this);

   }

   document::~document()
   {
   }



   bool document::set_data(::ca::data * pdata)
   {

      if(m_spdata.is_set())
      {

         remove_data(m_spdata);

      }

      ::ca::data_container::set_data(pdata);

      if(pdata != ::null())
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
      if (m_pdocumentemplate != ::null() &&
         m_pdocumentemplate->_001OnCmdMsg(pcmdmsg))
         return TRUE;

      return FALSE;
   }


#ifdef DEBUG
   void document::dump(dump_context & dumpcontext) const
   {
      ::ca::object::dump(dumpcontext);

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
      ::ca::object::assert_valid();

      ::count count = get_view_count();
      for(index index = 0; index < count; index++)
      {
         sp(::user::view) pview = get_view(index);
         ASSERT_VALID(pview);
      }
   }
#endif //DEBUG


   void document::on_alloc(sp(::ca::application) papp)
   {

      ::user::document::on_alloc(papp);
      ::database::client::initialize_data_client(App(papp).simpledb().get_data_server());

   }


} // namespace user


