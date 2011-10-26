#include "StdAfx.h"


namespace syllomatter
{

   main_document::main_document(::ca::application * papp) :
      ca(papp),
      data_container(papp),
      ::document(papp),
      ::userbase::document(papp)
   {
   }
   
   main_document::~main_document()
   {
   }

} // namespace syllomatter