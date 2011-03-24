#include "StdAfx.h"

namespace mplite
{

   view_update_hint::view_update_hint()
   {
      m_etype = type_none;
      m_pmidiplayer = NULL;
      m_pplaylistdoc = NULL;
   }

   view_update_hint::~view_update_hint()
   {

   }

   void view_update_hint::set_type(e_type e_type)
   {
      m_etype = e_type;
   }

   bool view_update_hint::is_type_of(e_type e_type)
   {
      return m_etype == e_type;
   }

} // namespace mplite