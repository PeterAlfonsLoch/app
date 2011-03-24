#include "StdAfx.h"

namespace ex1
{

   tree::tree(::ca::application * papp) :
      ca(papp),
      data_container(papp)
   {
      m_pitem = NULL;
   }

   tree::~tree()
   {
      finalize();
   }

   tree_data * tree::get_data()
   {
      return dynamic_cast < tree_data * > (::ca::data_container::get_data());
   }

   tree_item * tree::find(tree_item_data * pitemdata, index i)
   {
      if(i < 0)
         return NULL;
      if(pitemdata == NULL)
         return NULL;
      if(pitemdata->get_tree_data() != get_data())
         return NULL;
      ::ex1::tree_item * pitem = m_pitem;
      for(; pitem != NULL; pitem = pitem->get_item(TreeNavigationExpandedForward))
      {
         if(pitem->m_pitemdata == pitemdata)
         {
            i--;
            if(i < 0)
               return pitem;
         }
      }
      return NULL;
   }

   bool tree::contains(tree_item_data * pitemdata)
   {
      return find(pitemdata) != NULL;
   }

   bool tree::contains(tree_item * pitemParam)
   {
      ::ex1::tree_item * pitem = m_pitem;
      for(; pitem != NULL; pitem = pitem->get_item(TreeNavigationExpandedForward))
      {
         if(pitem == pitemParam)
            return true;
      }
      return false;
   }


   void tree::_001OnTreeDataChange()
   {
   }

   bool tree::add_selection(tree_item_data * pitemdata, index i)
   {
      tree_item * pitem = find(pitemdata, i);
      if(pitem == NULL)
         return false;
      return add_selection(pitem);
   }

   count tree::add_selection(tree_item_ptr_array & itemptra)
   {
      count count = 0;
      for(int i = 0; i < itemptra.get_count(); i++)
      {
         if(add_selection(itemptra[i]))
            count++;
      }
      return count;
   }

   bool tree::add_selection(tree_item * pitem)
   {
      if(!contains(pitem))
         return false;
      return m_itemptraSelected.add_unique(pitem);
   }

   bool tree::set_selection(tree_item_data * pitemdata, index i)
   {
      tree_item * pitem = find(pitemdata, i);
      if(pitem == NULL)
         return false;
      return set_selection(pitem);
   }

   count tree::set_selection(tree_item_ptr_array & itemptra)
   {
      count count = 0;
      for(int i = 0; i < itemptra.get_count(); i++)
      {
         if(contains(itemptra[i]) && m_itemptraSelected.add_unique(itemptra[i]))
            count++;
      }
      return count;
   }

   bool tree::set_selection(tree_item * pitem)
   {
      if(!contains(pitem))
         return false;
      bool bContains = m_itemptraSelected.contains(pitem);
      m_itemptraSelected.remove_all();
      m_itemptraSelected.add(pitem);
      return bContains;
   }

   bool tree::remove_selection(tree_item_data * pitemdata, index i)
   {
      tree_item * pitem = find(pitemdata, i);
      if(pitem == NULL)
         return false;
      return remove_selection(pitem);
   }

   count tree::remove_selection(tree_item_ptr_array & itemptra)
   {
      count count = 0;
      for(int i = 0; i < itemptra.get_count(); i++)
      {
         if(m_itemptraSelected.remove(itemptra[i]))
            count++;
      }
      return count;
   }

   bool tree::remove_selection(tree_item * pitem)
   {
      return m_itemptraSelected.remove(pitem) >= 0;
   }

   count tree::clear_selection()
   {
      return m_itemptraSelected.remove_all();
   }

   bool tree::hover(tree_item_data * pitemdata, index i)
   {
      tree_item * pitem = find(pitemdata, i);
      return hover(pitem);
   }

   bool tree::hover(tree_item * pitem)
   {
      if(pitem == NULL)
      {
         m_pitemHover = NULL;
         return true;
      }
      if(!contains(pitem))
         return false;
      return m_pitemHover == pitem;
   }

   bool tree::is_selected(tree_item * pitem)
   {
      return m_itemptraSelected.contains(pitem);
   }

   bool tree::is_selected(tree_item_data * pitemdata)
   {
      if(pitemdata == NULL)
         return NULL;
      if(pitemdata->get_tree_data() != get_data())
         return false;
      for(int i = 0; i < m_itemptraSelected.get_count(); i++)
      {
         if(m_itemptraSelected[i]->m_pitemdata == pitemdata)
            return true;
      }
      return false;
   }

   bool tree::is_hover(tree_item * pitem)
   {
      return pitem != NULL && m_pitemHover == pitem;
   }

   bool tree::is_hover(tree_item_data * pitemdata)
   {
      if(pitemdata == NULL)
         return NULL;
      if(pitemdata->get_tree_data() != get_data())
         return false;
      if(m_pitemHover == NULL)
         return false;
      if(m_pitemHover->m_pitemdata != pitemdata)
         return false;
      return true;
   }

   ::ex1::tree_item * tree::get_proper_item(index iIndex, index * piLevel)
   {
      if(*piLevel) *piLevel = 0;
      ::ex1::tree_item * pitem = get_base_item();
      while(pitem != NULL && iIndex >= 0)
      {
         pitem = pitem->get_item(TreeNavigationProperForward, piLevel);
         iIndex--;
      }
      return pitem;

   }

   index tree::get_proper_item_index(::ex1::tree_item * pitemParam, index * piLevel)
   {
      int iIndex = 0;
      if(piLevel != NULL) *piLevel = 0;
      ::ex1::tree_item * pitem = get_base_item();
      while(pitem != NULL)
      {
         pitem = pitem->get_item(TreeNavigationProperForward, piLevel);
         if(pitem == pitemParam)
            return iIndex;
         iIndex++;
      }
      return -1;
   }

   count tree::get_proper_item_count()
   {
      return get_base_item()->get_proper_item_count();
   }



   bool tree::initialize()
   {
      if(m_pitem != NULL)
         return true;
      m_pitem = allocate_item();
      if(m_pitem == NULL)
         return false;
      m_pitem->m_dwState |= ::ex1::tree_item_state_expandable;
      m_pitem->m_dwState |= ::ex1::tree_item_state_expanded;
      ex1::simple_tree_item_data * pitemdata = new ex1::simple_tree_item_data();
      m_pitem->m_pitemdata = pitemdata;
      pitemdata->m_str = "tree";
      return true;
   }

   bool tree::finalize()
   {
      if(m_pitem != NULL)
      {
         delete_item(m_pitem);
         m_pitem = NULL;
      }
      return true;
   }


   ::ex1::tree_item * tree::get_base_item()
   {
      return m_pitem;
   }

   ::ex1::tree_item * tree::insert_item(::ex1::tree_item_data * pitemdataNew, ERelative erelativeNewItem, ::ex1::tree_item * pitemRelative)
   {
      if(erelativeNewItem == RelativeReplace)
         return NULL;
      ::ex1::tree_item * pitemNew = allocate_item();
      if(pitemNew == NULL)
         return NULL;
      if(!insert_item(pitemNew, erelativeNewItem, pitemRelative))
      {
         delete_item(pitemNew);
         return NULL;
      }
      pitemNew->m_pitemdata = pitemdataNew;
      return pitemNew;
   }

   ::ex1::tree_item * tree::create_item(::ex1::tree_item * pitemRelative, ERelative erelativeNewItem)
   {
      if(erelativeNewItem == RelativeReplace)
         return NULL;
      ::ex1::tree_item * pitemNew = allocate_item();
      if(pitemNew == NULL)
         return NULL;
      if(!insert_item(pitemNew, erelativeNewItem, pitemRelative))
      {
         delete_item(pitemNew);
         return NULL;
      }
      if(get_data() != NULL)
      {
         pitemNew->m_pitemdata = get_data()->_allocate_item();
      }
      return pitemNew;
   }


   bool tree::insert_item(::ex1::tree_item * pitemNew, ERelative erelativeNewItem, ::ex1::tree_item * pitemRelative)
   {
      if(pitemNew == NULL)
         return false;
      if(!contains(pitemRelative))
         return false;
      if(erelativeNewItem == RelativeParent)
         return false;

      if(erelativeNewItem == RelativeLastSibling)
      {
         if(pitemRelative == m_pitem)
         {
            erelativeNewItem = RelativeFirstChild;
         }
      }

      switch(erelativeNewItem)
      {
      case RelativeFirstChild:
         {
            if(pitemRelative->m_pchild == NULL)
            {
               pitemRelative->m_pchild      = pitemNew;
      
               pitemNew->m_pparent  = pitemRelative;
            }
            else
            {
               ::ex1::tree_item * pitemOldFirstChild = pitemRelative->m_pchild;

               pitemRelative->m_pchild                  = pitemNew;

               pitemNew->m_pparent              = pitemRelative;
               pitemNew->m_pnext                = pitemOldFirstChild;
               
               pitemOldFirstChild->m_pprevious  = pitemNew;
            }
         }
         break;
      case RelativeLastChild:
         {
            if(pitemRelative->m_pchild == NULL)
            {
               pitemRelative->m_pchild         = pitemNew;
      
               pitemNew->m_pparent     = pitemRelative;
            }
            else
            {
               ::ex1::tree_item * pitemOldLastChild = pitemRelative->get_item(RelativeLastChild);

               pitemNew->m_pparent     = pitemRelative;
               pitemNew->m_pprevious   = pitemOldLastChild;
               
               pitemOldLastChild->m_pnext = pitemNew;
            }
         }
         break;
      case RelativePreviousSibling:
         {
            // all tree items that have siblings have a parent (at least the base item)
            ASSERT(pitemRelative->m_pparent != NULL);
            // Is pitemRelative a first child ?
            if(pitemRelative->get_item(RelativeFirstSibling) == pitemRelative)
            {
               return insert_item(pitemNew, RelativeFirstChild, pitemRelative->m_pparent);
            }
            else
            {
               pitemNew->m_pprevious   = pitemRelative->m_pprevious;
               pitemNew->m_pnext       = pitemRelative;

               pitemRelative->m_pprevious   = pitemNew;
            }
         }
         break;
      case RelativeNextSibling:
         {
            // all tree items that have siblings have a parent (at least the base item)
            ASSERT(pitemRelative->m_pparent != NULL);
            // Is pitemRelative a last child ?
            if(pitemRelative->get_item(RelativeLastSibling) == pitemRelative)
            {
               return insert_item(pitemNew, RelativeLastChild, pitemRelative->m_pparent);
            }
            else
            {
               pitemNew->m_pprevious   = pitemRelative;
               pitemNew->m_pnext       = pitemRelative->m_pnext;

               pitemRelative->m_pnext   = pitemNew;
            }
         }
         break;
      case RelativeLastSibling:
         {
            while(pitemRelative->m_pnext != NULL)
               pitemRelative = pitemRelative->m_pnext;
            if(pitemRelative->m_pnext == NULL)
            {
               pitemRelative->m_pnext          = pitemNew;
         
               pitemNew->m_pparent     = pitemRelative->m_pparent;
               pitemNew->m_pprevious   = pitemRelative;
               pitemNew->m_pnext       = NULL;
            }
         }
         break;
      case RelativeReplace:
         {
            pitemNew->m_dwUser      = pitemRelative->m_dwUser;
            pitemNew->m_dwMetaData  = pitemRelative->m_dwMetaData;
            pitemNew->m_pparent     = pitemRelative->m_pparent;
            pitemNew->m_pchild      = pitemRelative->m_pchild;
            pitemNew->m_pnext       = pitemRelative->m_pnext;
            pitemNew->m_pprevious   = pitemRelative->m_pprevious;
            pitemNew->m_dwState     = pitemRelative->m_dwState;
            pitemNew->m_pitemdata   = pitemRelative->m_pitemdata;
            if(pitemRelative->m_pparent->m_pchild == pitemRelative)
            {
               pitemNew->m_pparent->m_pchild = pitemNew;
            }
            delete_item(pitemRelative);
         }
         break;
      }

      _001OnTreeDataChange();
      return true;
   }

   ex1::tree_item * tree::allocate_item()
   {
      ex1::tree_item * pitemNew = new tree_item;
      pitemNew->m_ptree = this;
      return pitemNew;
   }

   void tree::delete_item(ex1::tree_item * pitem)
   {
      delete pitem;
   }

   void tree::sort(int ( * lpfnCompare )(tree_item *, tree_item *, void *), void * pvoidParam)
   {
      tree_item * pitem = get_base_item();
      while(pitem != NULL)
      {
         pitem->sort_children(lpfnCompare, pvoidParam);
         pitem = (tree_item *) pitem->get_next();
      }
   }



   image_list * tree::get_image_list()
   {
      return NULL;
   }

} // namespace ex1