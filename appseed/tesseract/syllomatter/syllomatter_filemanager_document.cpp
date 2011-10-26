#include "StdAfx.h"


namespace syllomatter
{


   filemanager_document::filemanager_document(::ca::application * papp) :
      ca(papp),
      data_container(papp),
      ::document(papp),
      ::userbase::document(papp),
      ::fs::document (papp),
      ::filemanager::document (papp),
      ::ca::data(papp),
      ::fs::data(papp),
      ::fs::set(papp)
   {
   }


   filemanager_document::~filemanager_document()
   {
   }
   

}//  namespace syllomatter