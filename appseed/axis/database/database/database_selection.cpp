//#include "framework.h"


namespace database
{


   selection::selection()
   {

   }


   selection::~selection()
   {

   }


   void selection::add_item(class id id)
   {

      selection_item item(id);

      m_itema.add(item);

   }


} // namespace database








