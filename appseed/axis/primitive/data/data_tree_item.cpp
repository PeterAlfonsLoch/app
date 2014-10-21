#include "framework.h"


namespace data
{



   tree_item::tree_item()
   {
      m_dwUser          = 0;
      m_dwState         = 0;
   }


   tree_item::~tree_item()
   {

   }

   sp(tree) tree_item::get_tree()
   {
      return m_ptree;
   }

   void tree_item::sort_children(index ( * lpfnCompare )(sp(tree_item) * pitem, sp(tree_item) * pitem2))
   {

      m_children.quick_sort(lpfnCompare);

   }


   void tree_item::SetParent(sp(tree_item) pparent)
   {

      if(pparent == this || is_descendant(pparent) || is_ascendant(pparent))
         return;

      m_pparent->m_children.remove(this);

      m_pparent = pparent;

      m_pparent->m_children.add(this);

   }

   ::count tree_item::remove_tree_item()
   {

      ::count ca = 1; // this

      ca += remove_tree_item_descendants();

      if(m_pparent != NULL)
      {

         if(m_pparent->m_children.contains(this))
         {

            m_pparent->m_children.remove(this);

            m_pparent.release();

         }

      }

      return ca;

   }


   ::count tree_item::remove_tree_item_descendants()
   {


      ::count ca = 0;

      while(m_children.has_elements())
      {

         ca += m_children.last_element()->remove_tree_item();

      }

      return ca;

   }


   sp(tree_item) tree_item::find_next_by_user_data(uint_ptr iUserData)
   {
      sp(tree_item) pitem = this;
      while(true)
      {
         pitem = pitem->get_item(TreeNavigationExpandedForward);
         if(pitem == NULL)
            return NULL;
         if(pitem->m_dwUser == (uint32_t) iUserData)
            return pitem;
      }
   }

   sp(tree_item) tree_item::get_child_by_user_data(uint_ptr iUserData)
   {
      for (index i = 0; i < m_children.get_count(); i++)
      {
         if(m_children[i]->m_dwUser == iUserData)
            return m_children[i];
      }
      return NULL;
   }

   void tree_item::get_children(tree_item_ptr_array & ptra)
   {
      ptra.copy(m_children);
   }


   ::count tree_item::get_children_count()
   {

      return m_children.get_count();

   }

   ::count tree_item::get_expandable_children_count()
   {
      ::count iCount = 0;
      for (index i = 0; i < m_children.get_count(); i++)
      {
         if (m_children[i]->get_children_count() > 0)
         {
            iCount++;
         }
      }
      return iCount;
   }

   sp(tree_item) tree_item::get_expandable_child(index iIndex)
   {
      ::count iCount = 0;
      for (index i = 0; i < m_children.get_count(); i++)
      {
         if (m_children[i]->get_children_count() > 0)
         {
            if (iCount == iIndex)
               return m_children[i];
            iCount++;
         }
      }
      return NULL;
   }

   ::count tree_item::get_proper_descendant_count()
   {
      ::count iCount = 0;
      index iLevel = 0;
      sp(tree_item) pitem = this;
      for(;;)
      {
         pitem = pitem->get_item(TreeNavigationProperForward, &iLevel);
         if(pitem == NULL || iLevel <= 0)
            break;
         iCount++;
      }
      return iCount;
   }


   sp(tree_item) tree_item::get_item(ETreeNavigation enavigation, index * pindexLevel)
   {
      switch(enavigation)
      {
      case TreeNavigationExpandedForward:
         return get_next(true, true, pindexLevel);
      case TreeNavigationProperForward:
         return get_next((m_dwState & ::data::tree_item_state_expanded) != 0, true, pindexLevel);
      default:
         // Not Expected
         ASSERT(FALSE);
         return NULL;
      }
   }

   sp(tree_item) tree_item::get_item(ERelative erelative)
   {
      sp(tree_item) pitem;
      switch(erelative)
      {
      case RelativeFirstChild:
         {
            return m_children.has_elements() ? m_children.first_element() : NULL;
         }
         break;
      case RelativeLastChild:
         {
            return m_children.has_elements() ? m_children.last_element() : NULL;
         }
      case RelativeParent:
         {
            return m_pparent;
         }
         break;
      case RelativeFirstSibling:
         {
            ASSERT(m_pparent != NULL);
            return m_pparent->get_item(RelativeFirstChild);
         }
         break;
      case RelativePreviousSibling:
         {
            ASSERT(m_pparent != NULL);
            index iFind = m_pparent->m_children.find_first(this);
            if (iFind <= 0)
               return NULL;
            return m_pparent->m_children[iFind - 1];
         }
         break;
      case RelativeNextSibling:
         {
            ASSERT(m_pparent != NULL);
            index iFind = m_pparent->m_children.find_first(this);
            if (iFind < 0 || iFind >= m_pparent->m_children.get_upper_bound())
               return NULL;
            return m_pparent->m_children[iFind + 1];
         }
         break;
      case RelativeLastSibling:
         {
            ASSERT(m_pparent != NULL);
            return m_pparent->get_item(RelativeLastChild);
         }
         break;
      default:
         // Not Expected
         ASSERT(FALSE);
         return NULL;
      }
   }

   sp(tree_item) tree_item::get_previous(bool bParent)
   {
      
      if (m_pparent == NULL)
         return NULL;
      
      index iFind = m_pparent->m_children.find_first(this);
      
      if (iFind <= 0)
      {
         
         if (bParent)
            return m_pparent;
         else
            return NULL;

      }

      return m_pparent->m_children[iFind - 1];

   }


   sp(tree_item) tree_item::first_child()
   {
      
      if (m_children.is_empty())
         return NULL;

      return m_children.first_element();

   }


   sp(tree_item) tree_item::previous()
   {

      return get_previous(false);

   }


   sp(tree_item) tree_item::next()
   {

      return get_next(false, false);

   }


   sp(tree_item) tree_item::get_next(bool bChild, bool bParent, index * pindexLevel)
   {

      index iFind;
      
      if(bChild && m_children.has_elements())
      {
         
         if(pindexLevel != NULL)
            (*pindexLevel)++;

         return m_children(0);

      }
      else if (m_pparent != NULL && (iFind = m_pparent->m_children.find_first(this)) >= 0 && iFind < m_pparent->m_children.get_upper_bound())
         return m_pparent->m_children(iFind + 1);
      else if(bParent && m_pparent != NULL)
      {
         if(pindexLevel != NULL) (*pindexLevel)--;
         return m_pparent->get_next(false, true, pindexLevel);
      }
      else
         return NULL;
   }



   string tree_item::get_text() const
   {
      if(m_pitem == NULL)
         return "";
      return m_pitem->data_item_get_text(m_ptree);
   }

   index tree_item::get_image() const
   {

      if(m_pitem == NULL)
         return -1;

      return m_pitem->data_item_get_image(m_ptree);

   }

   image_list * tree_item::get_image_list() const
   {

      if(m_pitem != NULL)
         return m_pitem->data_item_get_image_list(m_ptree);

      return NULL;

   }


   sp(tree_item) tree_item::get_proper_item(index iIndex, index * piLevel)
   {
      if(*piLevel) *piLevel = 0;
      sp(tree_item) pitem = this;
      while(pitem != NULL && iIndex >= 0)
      {
         pitem = pitem->get_item(TreeNavigationProperForward, piLevel);
         iIndex--;
      }
      return pitem;
   }

   index tree_item::get_proper_item_index(sp(tree_item) pitemParam, index * piLevel)
   {
      int32_t iIndex = 0;
      if(piLevel != NULL) *piLevel = 0;
      sp(tree_item) pitem = this;
      while(pitem != NULL)
      {
         pitem = pitem->get_item(TreeNavigationProperForward, piLevel);
         if(pitem == pitemParam)
            return iIndex;
         iIndex++;
      }
      return -1;
   }

   ::count tree_item::get_proper_item_count()
   {
      sp(tree_item) pitem = this;
      index iLevel = 0;
      ::count iCount = -1;
      while(pitem != NULL)
      {
         pitem = pitem->get_item(TreeNavigationProperForward, &iLevel);
         iCount++;
         if(iLevel <= 0)
            break;
      }
      return iCount;
   }


   bool tree_item::is_expanded() const
   {

      return (m_dwState & ::data::tree_item_state_expanded) != 0;

   }

   bool tree_item::is_expandable() const
   {

      return (m_dwState & ::data::tree_item_state_expandable) != 0;

   }


   bool tree_item::is_descendant(sp(tree_item) pitem)
   {

      if(pitem.is_null())
         return false;
      
      return pitem->is_ascendant(this);

   }


   bool tree_item::is_ascendant(sp(tree_item) pitem)
   {

      if(pitem.is_null())
         return false;

      sp(tree_item) pparent = m_pparent;

      if(pparent.is_null())
         return false;

      while(pparent.is_set())
      {

         if(pparent == pitem)
            return true;

         pparent = pparent->m_pparent;

      }
      
      return false;

   }


   void tree_item::on_fill_children()
   {

      if (m_pitem != NULL)
      {

         m_pitem->data_item_on_fill_children(this);

      }

      for (index i = 0; i < m_children.get_count(); i++)
      {

         if (m_children(i)->is_expanded())
         {

            m_children(i)->on_fill_children();

         }

      }

   }


} // namespace data



