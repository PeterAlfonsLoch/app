#include "StdAfx.h"

namespace mplite
{

   command_document::command_document(::ca::application * papp) :
      ca(papp),
      data_container(papp),
      ::document(papp),
      ::userbase::document(papp),
      html_document(papp),
      form_document(papp)
   {
   }

   command_document::~command_document()
   {
   }

      
#ifdef _DEBUG
   void command_document::assert_valid() const
   {
      ::userbase::document::assert_valid();
   }

   void command_document::dump(dump_context & dumpcontext) const
   {
      ::userbase::document::dump(dumpcontext);
   }
#endif

}