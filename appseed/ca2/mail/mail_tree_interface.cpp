#include "StdAfx.h"


namespace mail
{


   tree_interface::tree_interface(::ca::application * papp) :
      ca(papp),
      ::user::scroll_view(papp),
      ::user::tree(papp),
      ex1::tree_data(papp),
      ::mail::tree_data(papp)
   {
      m_dataid = "mail::tree_interface";

      ::ca::data_container::m_spdata = this;

      if(!ex1::tree_data::initialize_data())
         throw simple_exception();
   
   }

   bool tree_interface::initialize()
   {
      if(!::ex1::tree::initialize())
         return false;
      ::ca::data_container::m_spdata = this;
      return true;
   }

   void tree_interface::update_list()
   {
   }


   tree_interface::~tree_interface()
   {
   }


} // namespace mail


