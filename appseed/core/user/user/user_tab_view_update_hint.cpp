//#include "framework.h"

namespace user
{

   tab_view_update_hint::tab_view_update_hint()
   {

   }

   tab_view_update_hint::~tab_view_update_hint()
   {

   }

   bool tab_view_update_hint::is_type_of(e_type e_type)
   {
      return m_etype == e_type;
   }

   void tab_view_update_hint::set_type(e_type e_type)
   {
      m_etype = e_type;
   }

} // namespace user