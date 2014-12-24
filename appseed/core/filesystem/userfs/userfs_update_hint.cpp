//#include "framework.h"


namespace userfs
{



   update_hint::update_hint()
   {

   }


   update_hint::~update_hint()
   {

   }


   bool update_hint::is_type_of(e_type e_type)
   {

      return m_etype == e_type;

   }


   void update_hint::set_type(e_type e_type)
   {

      m_etype = e_type;

   }


} // namespace userfs




