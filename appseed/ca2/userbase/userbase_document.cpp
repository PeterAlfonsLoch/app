#include "framework.h"


namespace userbase
{


   document::document(::ca::application * papp) :
      ca(papp),
      ::document(papp)
   {
      m_pdocumentemplate = NULL;
      m_bModified = FALSE;
      m_bAutoDelete = TRUE;       // default to auto delete document
      m_bEmbedded = FALSE;        // default to file-based document
      ASSERT(m_viewptra.is_empty());
   }

   document::~document()
   {
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


   #ifdef _DEBUG
   void document::dump(dump_context & dumpcontext) const
   {
      ::radix::object::dump(dumpcontext);

      dumpcontext << "m_wstrTitle = " << m_strTitle;
      dumpcontext << "\nm_wstrPathName = " << m_strPathName;
      dumpcontext << "\nm_bModified = " << m_bModified;
      dumpcontext << "\nm_pDocTemplate = " << (void *)m_pdocumentemplate;

      if (dumpcontext.GetDepth() > 0)
      {
         count count = get_view_count();
         for(index index = 0; index < count; index++)
         {
            ::view * pview = get_view(index);
            dumpcontext << "\nwith ::view " << (void *)pview;
         }
      }

      dumpcontext << "\n";
   }

   void document::assert_valid() const
   {
      ::radix::object::assert_valid();

      count count = get_view_count();
      for(index index = 0; index < count; index++)
      {
         ::view * pview = get_view(index);
         ASSERT_VALID(pview);
      }
   }
   #endif //_DEBUG


   void document::on_alloc(::ca::application * papp)
   {

      ::document::on_alloc(papp);
      ::database::client::initialize(papp);

   }


} // namespace userbase


