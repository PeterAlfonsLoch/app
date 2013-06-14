#include "framework.h"


namespace usermail
{


   tree_interface::tree_interface(sp(::ca2::application) papp) :
      ca2(papp),
      
      ::user::scroll_view(papp),
      ::user::tree(papp),
      ::ca2::tree_data(papp),
      ::usermail::tree_data(papp)
   {

      m_dataid = "mail::tree_interface";

      ::ca2::data_container::m_spdata = this;

   }


   void tree_interface::update_list()
   {
   }


   tree_interface::~tree_interface()
   {
   }


} // namespace mail


