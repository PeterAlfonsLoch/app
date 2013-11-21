#include "framework.h"


namespace userfs
{


   document::document(sp(base_application) papp) :
      element(papp),
      ::user::object(papp),
      m_fsset(papp)
   {
   }

   document::~document()
   {
   }

   void document::assert_valid() const
   {
      ::user::object::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::user::object::dump(dumpcontext);
   }

   bool document::file_manager_browse(const char * pszFolder)
   {
      m_strFolder = pszFolder;
      update_all_views(NULL, 123);
      return true;
   }



} // namespace userfs



