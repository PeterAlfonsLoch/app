#include "StdAfx.h"

namespace devedge
{

   source::source(::ca::application * papp) :
      ca(papp),
      array_app_alloc < file, file & > (papp),
      folder(papp)
   {
      m_bStdAfx = false;
   }

   void source::load(project * pproject)
   {
      folder::load(pproject, "*.cpp");
      m_bStdAfx = has("StdAfx.cpp");
   }

} // namespace devedge