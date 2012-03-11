#include "StdAfx.h"


namespace fs
{


   document::document(::ca::application * papp) :
      ::ca::ca(papp),
      userbase::document(papp),
      ::ca::data(papp),
      ::fs::data(papp),
      ::fs::set(papp)
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



