#include "framework.h"


namespace usermail
{


   tree::tree(sp(base_application) papp) :
      element(papp),
      ::data::tree(papp),
   {

      m_dataid = "usermail::tree";

      ::data::data_container::m_spdata = this;

   }



   tree::~tree()
   {
   }

   void tree::update_list()
   {
   }


} // namespace mail


