#include "framework.h"


namespace filehandler
{


   tree_interface::tree_interface(sp(::ca::application) papp) :
      ca(papp),
      ::ca::tree(papp)
   {
         
         
   }

   bool tree_interface::initialize()
   {
      if(!::ca::tree::initialize())
         return false;
      ::ca::data_container::m_spdata = new tree_data(get_app());
      return true;
   }

   void tree_interface::update_list()
   {
   }


   tree_interface::~tree_interface()
   {
   }

   tree_data * tree_interface::get_filehandler_tree_data()
   {
      return dynamic_cast < tree_data * > (::ca::data_container::m_spdata.m_p);
   }
   
   
} // namespace filehandler




