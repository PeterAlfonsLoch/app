#include "framework.h"


namespace usermail
{


   tree::tree(sp(base_application) papp) :
      element(papp),
      ::data::data(papp),
      ::data::tree(papp)
   {

   }



   tree::~tree()
   {
   }

   void tree::update_list()
   {
   }


} // namespace mail


