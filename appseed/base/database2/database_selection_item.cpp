#include "framework.h"

namespace database
{

   selection_item::selection_item()
   {

   }

   selection_item::selection_item(class id & id, class id & idIndex)
   {
      m_id       = id;
      m_idIndex       = idIndex;
   }

   selection_item::~selection_item()
   {

   }

} // namespace database