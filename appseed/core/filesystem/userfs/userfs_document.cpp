#include "framework.h"


namespace userfs
{


   document::document(sp(::base::application) papp) :
      element(papp),
      ::data::data_container_base(papp),
      ::user::document(papp),
      m_fsset(papp)
   {
   }

   document::~document()
   {
   }

   void document::assert_valid() const
   {
      ::user::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::user::document::dump(dumpcontext);
   }

   bool document::file_manager_browse(const char * pszFolder, ::action::context actioncontext)
   {
      
      m_strFolder = pszFolder;

      update_hint uh;

      uh.set_type(update_hint::type_synchronize_path);
      uh.m_strPath = pszFolder;
      uh.m_actioncontext = ::action::source::sync(actioncontext);

      update_all_views(NULL, 0, &uh);

      return true;

   }



} // namespace userfs



