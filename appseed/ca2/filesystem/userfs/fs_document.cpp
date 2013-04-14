#include "framework.h"


namespace fs
{


   document::document(sp(::ca::application) papp) :
      ::ca::ca(papp),
      ::ca::data_container_base(papp),
      ::ca::data_container(papp),
      user::document(papp),
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

   bool document::file_manager_browse(const char * pszFolder)
   {
      m_strFolder = pszFolder;
      update_all_views(::null(), 123);
      return true;
   }



} // namespace filemanager



