#include "framework.h"


namespace filehandler
{


   tree_interface::tree_interface(sp(::ca::application) papp) :
      ca(papp),
      ::ca::tree(papp)
   {

      ::ca::data_container::m_spdata = new tree_data(get_app());
         
   }


   void tree_interface::update_list()
   {

   }


   tree_interface::~tree_interface()
   {

   }

   sp(tree_data) tree_interface::get_filehandler_tree_data()
   {
      return  (::ca::data_container::m_spdata.m_p);
   }
   
   
} // namespace filehandler




