#include "StdAfx.h"

namespace mediaplaylist
{

   tree_base::tree_base(::ca::application * papp) :
      ca(papp),
      data_container(papp),
      ::user::scroll_view(papp),
      ::user::tree(papp),
      ex1::tree_data(papp),
      ex1::tree(papp),
      ::ca::data(papp),
      ::mediaplaylist::tree_data(papp)
   {
      m_dataid = "mediaplaylist::tree_base";

      ::ca::data_container::m_spdata = this;

      if(!ex1::tree_data::initialize_data())
         throw simple_exception();
   
   }

   bool tree_base::initialize()
   {
      if(!::ex1::tree::initialize())
         return false;
      ::ca::data_container::m_spdata = this;
      return true;
   }

   void tree_base::update_list()
   {
   }


   tree_base::~tree_base()
   {
   }


   void tree_base::create_tree(xml::node * pnode, ex1::tree_item * pitemParent)
   {
      if(pitemParent == NULL)
         pitemParent = get_base_item();

      index iStart = 0;
      xml::node * pnodeChild;
      
      while((pnodeChild = pnode->get_child("playlist", iStart)) != NULL)
      {
         ::mediaplaylist::tree_item * pitem     = new ::mediaplaylist::tree_item;
         pnodeChild->get_attr("name", pitem->m_strName);
         ::ex1::tree_item * pitemNew = insert_item(pitem, ex1::RelativeLastChild, pitemParent);
         create_tree(pnodeChild, pitemNew);
         iStart++;
      }
   }

} // namespace mediaplaylist