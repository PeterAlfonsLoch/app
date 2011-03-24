#include "StdAfx.h"


namespace alarm
{

   document::document(::ca::application * papp) :
      ca(papp),
      ::ca::data_container(papp),
      ::document(papp),
      ::userbase::document(papp)
   {
   }

   BOOL document::on_new_document()
   {
	   if (!::userbase::document::on_new_document())
		   return FALSE;

	   return TRUE;
   }

   document::~document()
   {
   }


   #ifdef _DEBUG
   void document::assert_valid() const
   {
      ::userbase::document::assert_valid();
   }

   void document::dump(dump_context& dc) const
   {
	   ::userbase::document::dump(dc);
   }
   #endif //_DEBUG



   BOOL document::on_open_document(const char * lpszPathName)
   {
      string str = Application.file().as_string(lpszPathName);
      if(str.is_empty())
      {
         System.sync_load_url(str, lpszPathName);
      }
      update_all_views(NULL, 123);
      return TRUE;
   }

} // namespace alarm