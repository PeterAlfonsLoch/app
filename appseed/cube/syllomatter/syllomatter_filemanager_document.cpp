#include "StdAfx.h"


namespace syllomatter
{

   filemanager_document::filemanager_document(::ca::application * papp) :
      ca(papp),
      data_container(papp),
      ::document(papp),
      ::userbase::document(papp),
      ::fs::document (papp),
      ::filemanager::document (papp)
   {
   }

   filemanager_document::~filemanager_document()
   {
   }
   

}//  namespace syllomatter