#include "framework.h"


namespace userfs
{


   document::document(sp(::ca2::application) papp) :
      ::ca2::ca2(papp),
      ::ca2::data_container_base(papp),
      
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
      update_all_views(NULL, 123);
      return true;
   }



} // namespace userfs



