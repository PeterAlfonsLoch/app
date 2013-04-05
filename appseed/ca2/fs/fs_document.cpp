#include "framework.h"


namespace fs
{


   document::document(::ca::applicationsp papp) :
      ::ca::ca(papp),
      ::ca::data_container_base(papp),
      userbase::document(papp),
      m_fsset(papp)
   {
   }

   document::~document()
   {
   }

   void document::assert_valid() const
   {
      ::userbase::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::userbase::document::dump(dumpcontext);
   }

   bool document::file_manager_browse(const char * pszFolder)
   {
      m_strFolder = pszFolder;
      update_all_views(NULL, 123);
      return true;
   }



} // namespace filemanager



