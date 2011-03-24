#include "StdAfx.h"

namespace veriview
{

   document::document(::ca::application * papp) :
      ca(papp),
      ::ca::data_container(papp),
      ::document(papp),
      ::userbase::document(papp),
      html_document(papp)
   {
      get_html_data()->m_propset["bReplaceEx1"] = false;
   }
      
   document::~document()
   {
   }
      
} // namespace veriview