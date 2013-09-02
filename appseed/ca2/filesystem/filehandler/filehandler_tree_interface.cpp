#include "framework.h"


namespace filehandler
{


   tree_interface::tree_interface(sp(::application) papp) :
      element(papp),
      ::ca2::tree(papp)
   {

      ::data_container::m_spdata = new tree_data(get_app());
         
   }


   void tree_interface::update_list()
   {

   }


   tree_interface::~tree_interface()
   {

   }

   sp(tree_data) tree_interface::get_filehandler_tree_data()
   {
      return  (::data_container::m_spdata.m_p);
   }
   
   
} // namespace filehandler




