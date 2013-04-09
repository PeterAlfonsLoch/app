#include "framework.h"


namespace mail
{


   tree_interface::tree_interface(sp(::ca::application) papp) :
      ca(papp),
      ::user::scroll_view(papp),
      ::user::tree(papp),
      ::ca::tree_data(papp),
      ::mail::tree_data(papp)
   {

      m_dataid = "mail::tree_interface";

      ::ca::data_container::m_spdata = this;

   }


   void tree_interface::update_list()
   {
   }


   tree_interface::~tree_interface()
   {
   }


} // namespace mail


