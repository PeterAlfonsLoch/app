#include "framework.h"

namespace database
{

   selection::selection()
   {

   }

   selection::~selection()
   {

   }

   void selection::add_item(class id id, class id idIndex)
   {
      selection_item item(id);
      m_itema.add(item);
   }

} // namespace database