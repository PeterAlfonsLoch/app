#include "StdAfx.h"

namespace ca2
{
   
   bool note::has_tag_by_id(const char * pszTagId)
   {
      return m_taga.stra().contains(pszTagId);
   }


} // namespace ca2