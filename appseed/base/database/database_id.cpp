#include "framework.h"

namespace database
{

   bool id::is_null()
   {
      return m_id.is_empty();
   }

   ::id id::get_id()
   {
      return m_id;
   }

   void id::set_id(::id id)
   {
      m_id = id;
   }

} // namespace database