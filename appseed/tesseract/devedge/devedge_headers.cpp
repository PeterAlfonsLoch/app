#include "StdAfx.h"

namespace devedge
{

   headers::headers(::ca::application * papp) :
      ca(papp),
      array_app_alloc < file, file & > (papp),
      folder(papp)
   {
      m_bStdAfx = false;
   }

   void headers::load(project * pproject)
   {
      folder::load(pproject, "*.h");
      m_bStdAfx = has("StdAfx.h");
   }

} // namespace devedge