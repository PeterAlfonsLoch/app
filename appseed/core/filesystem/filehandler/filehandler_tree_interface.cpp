#include "framework.h"


namespace filehandler
{


   tree_interface::tree_interface(sp(::axis::application) papp) :
      element(papp),
      ::data::data(papp),
      ::data::tree(papp)
   {

   }


   void tree_interface::update_list()
   {

   }


   tree_interface::~tree_interface()
   {

   }

   
   
} // namespace filehandler




