#include "StdAfx.h"


namespace mixeruserbase
{


   document::document(::ca::application * papp) :
      ca(papp),
      data_container(papp),
      ::document(papp),
      userbase::document(papp)
   {
   }

   document::~document()
   {
   }

   BOOL document::on_new_document()
   {

      if(!::userbase::document::on_new_document())
         return FALSE;

      return TRUE;
   }



   #ifdef _DEBUG
   void document::assert_valid() const
   {
      ::userbase::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::userbase::document::dump(dumpcontext);
   }
   #endif //_DEBUG


} // namespace mixeruserbase

