#include "StdAfx.h"


namespace alatel
{


   main_document::main_document(::ca::application * papp) :
      ca(papp),
      ::ca::data_container(papp),
      ::document(papp),
      ::userbase::document(papp)
   {
   }

   BOOL main_document::on_new_document()
   {
	   if (!::userbase::document::on_new_document())
		   return FALSE;

	   return TRUE;
   }

   main_document::~main_document()
   {
   }


   #ifdef _DEBUG
   void main_document::assert_valid() const
   {
      ::userbase::document::assert_valid();
   }

   void main_document::dump(dump_context& dc) const
   {
	   ::userbase::document::dump(dc);
   }
   #endif //_DEBUG



   bool main_document::on_open_document(var varFile)
   {
      string str = Application.file().as_string(varFile);
      update_all_views(NULL, 123);
      return TRUE;
   }


} // namespace alatel


