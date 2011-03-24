#include "StdAfx.h"


namespace fs
{


   document::document(::ca::application * papp) :
      ::ca::data_container(papp),
      ::document(papp),
      userbase::document(papp)
   {
      m_pfsdata         = NULL;
   }

   document::~document()
   {
   }

   data * document::get_fs_data()
   {
      return m_pfsdata;
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