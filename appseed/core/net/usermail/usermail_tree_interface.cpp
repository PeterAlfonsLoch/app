#include "framework.h"


namespace usermail
{


   tree_interface::tree_interface(sp(base_application) papp) :
      element(papp),
      
      ::user::scroll_view(papp),
      ::user::tree(papp),
      ::data::tree_data(papp),
      ::usermail::tree_data(papp)
   {

      m_dataid = "mail::tree_interface";

      ::data_container::m_spdata = this;

   }


   void tree_interface::update_list()
   {
   }


   tree_interface::~tree_interface()
   {
   }


} // namespace mail


