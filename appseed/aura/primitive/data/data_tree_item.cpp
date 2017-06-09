#include "framework.h"
#include "aura/primitive/collection/collection_sort.h"


namespace data
{



   tree_item::tree_item()
   {
      m_iIndexHint = -1;
      m_dwUser          = 0;
      m_dwState         = 0;
      m_ptree           = NULL;
      m_pparent         = NULL;
      m_iLevel          = -1;

   }


   tree_item::~tree_item()
   {

   }

   tree * tree_item::get_tree()
   {
      
      return m_ptree;

   }



   void tree_item::SetParent(tree_item * pparent)
   {

      if(m_pparent == pparent || pparent == this || is_descendant(pparent) || is_ascendant(pparent))
         return;

      pparent->m_children.add(this);

      m_pparent->m_children.remove(this);

      m_pparent = pparent;

      for (auto c : m_pparent->m_children)
      {

//         c->update_pointers();

      }

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

         }

      }

      for (auto c : m_pparent->m_children)
      {

//         c->update_pointers();

      }


      return ca;

   }


   ::count tree_item::remove_tree_item_descendants()
   {


      ::count ca = 0;

      while(m_children.has_elements())
      {

         ca += m_children.last_sp()->remove_tree_item();

      }



      return ca;

   }


   tree_item * tree_item::find_next_by_user_data(uint_ptr iUserData)
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

   bool tree_item::remove_item_from_parent()
   {

      tree_item * pitem = this;

      if (pitem->m_pparent == NULL)
      {

         return true;

      }

      index iFind = pitem->m_pparent->m_children.find_first(pitem);

      if (iFind < 0)
      {

         // self healing?
         pitem->m_pparent = NULL;

         return false;

      }

      pitem->m_pparent->m_children.remove_at(iFind);

      pitem->m_pparent = NULL;

      return true;

   }


   bool tree_item::insert(ERelative erelative, tree_item * pitemNew)
   {

      if (erelative == RelativeFirstChild)
      {

         //if (contains(pitemNew))
         //{

         //   return true;

         //}

         pitemNew->remove_item_from_parent();

         m_children.insert_at(0, pitemNew);

         pitemNew->m_iLevel = m_iLevel + 1;

         pitemNew->m_pparent = this;

         return true;

      }
      else if (erelative == RelativeLastChild)
      {

         pitemNew->remove_item_from_parent();

         m_children.add(pitemNew);

         pitemNew->m_iLevel = m_iLevel + 1;

         pitemNew->m_pparent = this;

         return true;

      }
      else if (erelative == RelativePreviousSibling)
      {

         ASSERT(m_pparent != NULL);

         if (m_pparent == NULL)
         {

            return false;

         }

         index iFind = m_pparent->m_children.find_first(this);

         if (iFind < 0)
         {

            // self-healinng
            m_pparent = NULL;

            return false;

         }

         if (iFind > 0)
         {

            iFind--;

         }

         m_pparent->m_children.insert_at(iFind, pitemNew);

         pitemNew->m_iLevel = m_iLevel;

         pitemNew->m_pparent = m_pparent;


      }
      else if(erelative == RelativeNextSibling)
      {

         if (m_pparent == NULL)
         {

            return false;

         }

         index iFind = m_pparent->m_children.find_first(this);

         if (iFind < 0)
         {

            // self-healing
            m_pparent = NULL;

            return false;

         }
         else
         {

            iFind++;

         }

         m_pparent->m_children.insert_at(iFind, pitemNew);

         pitemNew->m_iLevel = m_iLevel;

         pitemNew->m_pparent = m_pparent;

      }
      else if(erelative == RelativeLastSibling)
      {

         m_pparent->m_children.add(pitemNew);

         pitemNew->m_iLevel = m_iLevel;

         pitemNew->m_pparent = m_pparent;

      }
      else if(erelative == RelativeReplace)
      {

         index iFind = m_pparent->m_children.find_first(this);

         if(iFind < 0)
         {

            m_pparent = NULL;

            return false;

         }

         m_pparent->m_children.element_at(iFind) = pitemNew;

         m_pparent = NULL;

         remove_tree_item();

      }


   

      return false;


   }

   tree_item * tree_item::get_child_by_user_data(uint_ptr iUserData)
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

   tree_item * tree_item::get_parent()
   {

      return m_pparent;

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

   tree_item * tree_item::get_expandable_child(index iIndex)
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

   //tree_item * tree_item::get_previous_or_parent(index * iLevelOffset)
   //{

   //   if (!(m_uiTreeItemFlag & flag_previous_or_parent))
   //   {

   //      m_iLevelPreviousOrParentOffset = 0;

   //      m_pitemPreviousOrParent = calc_previous_or_parent(&m_iLevelPreviousOrParentOffset);

   //      //m_uiTreeItemFlag |= flag_previous_or_parent;

   //   }

   //   if (iLevelOffset != NULL)
   //   {

   //      *iLevelOffset += m_iLevelPreviousOrParentOffset;

   //   }

   //   return m_pitemPreviousOrParent;

   //}


   //tree_item * tree_item::get_previous()
   //{

   //   if (!(m_uiTreeItemFlag & flag_previous))
   //   {

   //      m_pitemPrevious = calc_previous(false);

   //      //m_uiTreeItemFlag |= flag_previous;

   //   }

   //   return m_pitemPrevious;

   //}


   //tree_item * tree_item::get_next()
   //{

   //   if (!(m_uiTreeItemFlag & flag_next))
   //   {

   //      m_pitemNext = calc_next();

   //      //m_uiTreeItemFlag |= flag_next;

   //   }

   //   return m_pitemNext;

   //}


   //tree_item * tree_item::get_next_or_parent(index * iLevelOffset)
   //{

   //   if (!(m_uiTreeItemFlag & flag_next_or_parent))
   //   {

   //      m_iLevelNextOrParentOffset = 0;

   //      m_pitemNextOrParent = calc_next_or_parent(&m_iLevelNextOrParentOffset);

   //      //m_uiTreeItemFlag |= flag_next_or_parent;

   //   }

   //   if (iLevelOffset != NULL)
   //   {

   //      *iLevelOffset += m_iLevelNextOrParentOffset;

   //   }

   //   return m_pitemNextOrParent;

   //}


   //tree_item * tree_item::get_child_or_next(index * iLevelOffset)
   //{
   //   
   //   if (!(m_uiTreeItemFlag & flag_child_or_next))
   //   {

   //      m_iLevelChildOrNextOffset = 0;

   //      m_pitemChildOrNext = calc_child_or_next(&m_iLevelChildOrNextOffset);

   //      //m_uiTreeItemFlag |= flag_child_or_next;

   //   }

   //   if (iLevelOffset != NULL)
   //   {

   //      *iLevelOffset += m_iLevelChildOrNextOffset;

   //   }

   //   return m_pitemChildOrNext;
   //}


   //tree_item * tree_item::get_child_next_or_parent(index * iLevelOffset)
   //{

   //   if (!(m_uiTreeItemFlag & flag_child_next_or_parent))
   //   {

   //      m_iLevelChildNextOrParentOffset = 0;

   //      m_pitemChildNextOrParent = calc_child_next_or_parent(&m_iLevelChildNextOrParentOffset);

   //      //m_uiTreeItemFlag |= flag_child_next_or_parent;

   //   }

   //   if (iLevelOffset != NULL)
   //   {

   //      *iLevelOffset += m_iLevelChildNextOrParentOffset;

   //   }

   //   return m_pitemChildNextOrParent;
   //}



   //tree_item * tree_item::calc_previous_or_parent(index * iLevelOffset)
   tree_item * tree_item::get_previous_or_parent(index * iLevelOffset)
   {

      if (m_pparent == NULL)
      {

         return NULL;

      }

      int iFastLevel = -1;

      {

         tree_item * p = this;

         while (p != NULL)
         {

            iFastLevel++;

            p = p->m_pparent;

         }

      }

      index iFind = get_index();

      if (iFind <= 0)
      {

         if (iLevelOffset != NULL)
         {

            (*iLevelOffset)--;

         }

         return m_pparent;

      }

      return m_pparent->m_children[iFind - 1];

   }

   //tree_item * tree_item::calc_previous()
   tree_item * tree_item::get_previous()
   {
      
      if (m_pparent == NULL)
      {

         return NULL;

      }

      index iFind = get_index();

      if (iFind <= 0)
      {

         return NULL;

      }

      return m_pparent->m_children[iFind - 1];

   }

   //tree_item * tree_item::calc_next()
   tree_item * tree_item::get_next()
   {
      
      if (m_pparent == NULL)
      {

         return NULL;

      }

      index iFind = get_index();

      if (iFind < 0 || iFind >= m_pparent->m_children.get_upper_bound())
      {

         return NULL;

      }

      return m_pparent->m_children[iFind + 1];

   }


   index tree_item::calc_level()
   {

      if (m_iLevel < 0)
      {


         m_iLevel = -1;

         tree_item * p = this;

         while (p != NULL)
         {

            m_iLevel++;

            p = p->m_pparent;

         }

      }

      return m_iLevel;

   }

   



   index tree_item::get_index()
   {

      if (m_pparent == NULL)
      {

         return 0;

      }


      index iHint = -1;

      if (m_iIndexHint >= 0 && m_iIndexHint < m_pparent->m_children.get_size())
      {

         if (m_pparent->m_children.ptr_at(m_iIndexHint) == this)
         {

            return m_iIndexHint;

         }

         iHint = MAX(0, m_iIndexHint - 10);

      }

      index iLevel = get_level();

      if (iHint < 0)
      {

         iHint = m_ptree->m_iaLevelNext.element_at_grow(iLevel);

      }

      //index iLevel = get_level();

      //index iHint = m_ptree->m_iaLevelNext.get_at_grow(iLevel);

      index iFind = m_pparent->m_children.find_first(this, iHint);

      if (iFind < 0 && iHint > 0)
      {

         iFind = m_pparent->m_children.find_first(this, 0, iHint);

      }

      m_iIndexHint = iFind;
      // safe hint for many cases, 
      // specially for ca2, hint is any hint,
      // or maybe not
      m_ptree->m_iaLevelNext[iLevel] = MAX(0, iFind - 6);

      return iFind;

   }

   //tree_item * tree_item::calc_next_or_parent(index * iLevelOffset)
   tree_item * tree_item::get_next_or_parent(index * iLevelOffset)
   {
      
      if (m_pparent == NULL)
      {

         return NULL;

      }

      index iFind = get_index();

      if (iFind < 0 || iFind >= m_pparent->m_children.get_upper_bound())
      {

         if (iLevelOffset != NULL)
         {

            (*iLevelOffset)--;

         }

         return m_pparent->get_next_or_parent(iLevelOffset);

      }

      return m_pparent->m_children[iFind + 1];

   }


   //tree_item * tree_item::calc_child_or_next(index * iLevelOffset)
   tree_item * tree_item::get_child_or_next(index * iLevelOffset)
   {
      
      tree_item * pitem = first_child();

      if (pitem != NULL)
      {

         if (iLevelOffset != NULL)
         {

            (*iLevelOffset)++;

         }

         return pitem;

      }

      if (m_pparent == NULL)
      {

         return NULL;

      }

      pitem = get_next();

      if (pitem != NULL)
      {


         return pitem;

      }

      return NULL;

   }

   //tree_item * tree_item::calc_child_next_or_parent(index * iLevelOffset)
   tree_item * tree_item::get_child_next_or_parent(index * iLevelOffset)
   {

      tree_item * pitem = first_child();

      if (pitem != NULL)
      {

         if (iLevelOffset != NULL)
         {

            (*iLevelOffset)++;

         }

         return pitem;

      }

      if (m_pparent == NULL)
      {

         return NULL;

      }

      pitem = get_next();

      if (pitem != NULL)
      {


         return pitem;

      }

      if (iLevelOffset != NULL)
      {

         (*iLevelOffset)--;

      }

      return m_pparent->get_next_or_parent(iLevelOffset);


   }


   tree_item * tree_item::get_item(ETreeNavigation enavigation, index * pindexLevel)
   {
      tree_item * pitem;
      switch(enavigation)
      {
      case TreeNavigationExpandedForward:
         
         return get_child_next_or_parent(pindexLevel);

      case TreeNavigationProperForward:
         
         if ((m_dwState & ::data::tree_item_state_expanded) != 0)
         {
            
            return get_child_next_or_parent(pindexLevel);

         }
         else
         {

            return get_next_or_parent(pindexLevel);

         }

      default:
         // Not Expected
         ASSERT(FALSE);
         return NULL;
      }
   }

   tree_item * tree_item::get_item(ERelative erelative)
   {
      sp(tree_item) pitem;
      switch(erelative)
      {
      case RelativeFirstChild:
         {
            return m_children.has_elements() ? m_children.first_sp() : NULL;
         }
         break;
      case RelativeLastChild:
         {
            return m_children.has_elements() ? m_children.last_sp() : NULL;
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
            index iFind = get_index();
            if (iFind <= 0)
               return NULL;
            return m_pparent->m_children[iFind - 1];
         }
         break;
      case RelativeNextSibling:
         {
            ASSERT(m_pparent != NULL);
            index iFind = get_index();
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

   tree_item * tree_item::calc_previous(bool bParent)
   {
      
      if (m_pparent == NULL)
         return NULL;
      
      index iFind = get_index();
      
      if (iFind <= 0)
      {
         
         if (bParent)
            return m_pparent;
         else
            return NULL;

      }

      return m_pparent->m_children[iFind - 1];

   }


   tree_item * tree_item::first_child()
   {
      
      if (m_children.is_empty())
         return NULL;

      return m_children.first_sp();

   }




   tree_item * tree_item::calc_next(bool bChild, bool bParent, index * pindexLevel)
   {

      index iFind;
      
      if(bChild && m_children.has_elements())
      {
         
         if(pindexLevel != NULL)
            (*pindexLevel)++;

         return m_children[0];

      }
      else if (m_pparent != NULL && (iFind = get_index()) >= 0 && iFind < m_pparent->m_children.get_upper_bound())
         return m_pparent->m_children[iFind + 1];
      else if(bParent && m_pparent != NULL)
      {
         if(pindexLevel != NULL) (*pindexLevel)--;
         return m_pparent->calc_next(false, true, pindexLevel);
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


   tree_item * tree_item::get_proper_item(index iIndex, index * piLevel)
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

   index tree_item::get_proper_item_index(tree_item * pitemParam, index * piLevel)
   {
      int32_t iIndex = 0;
      if(piLevel != NULL) *piLevel = 0;
      tree_item * pitem = this;
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
      tree_item * pitem = this;
      index iLevel = 0;
      ::count iCount = -1;
      while(pitem != NULL)
      {
         pitem = pitem->get_item(TreeNavigationProperForward, &iLevel);
         iCount++;
         if (iCount >= 65536)
         {
            break;

         }
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


   bool tree_item::is_descendant(tree_item * pitem)
   {

      if (pitem == NULL)
      {
       
         return false;

      }
      
      return pitem->is_ascendant(this);

   }


   bool tree_item::is_ascendant(tree_item * pitem)
   {

      if (pitem == NULL)
      {

         return false;

      }

      tree_item * pparent = m_pparent;

      if(pparent == NULL)
         return false;

      while(pparent != NULL)
      {

         if(pparent == pitem)
            return true;

         pparent = pparent->m_pparent;

      }
      
      return false;

   }

   //void tree_item::update_pointers()
   //{

   //   if (m_pparent == NULL)
   //   {

   //      m_iLevel = 0;

   //   }
   //   else
   //   {

   //      m_iLevel = m_pparent->m_iLevel + 1;

   //   }

   //   update_previous_pointers(true);

   //   if (m_children.has_elements())
   //   {
   //      
   //      m_children[0]->update_previous_pointers(true);

   //   }

   //   if (m_children.get_count() > 1)
   //   {

   //      m_children.last_sp()->update_next_pointers(true);

   //   }

   //   update_next_pointers(true);

   //}

   //void tree_item::update_previous_pointers(bool bUpdateNext)
   //{

   //   m_pprevious = calc_previous(false);

   //   if (bUpdateNext && m_pprevious != NULL)
   //   {

   //      m_pprevious->update_next_pointers(false);

   //   }

   //   m_ppreviousParent = calc_previous(true);

   //   if (bUpdateNext && m_ppreviousParent != NULL && m_ppreviousParent != m_pprevious)
   //   {

   //      m_ppreviousParent->update_next_pointers(false);

   //   }

   //}


   //void tree_item::update_next_pointers(bool bUpdatePrevious)
   //{
   //   
   //   m_iLevelNext = m_iLevel;

   //   m_pnext = calc_next(false, false, &m_iLevelNext);

   //   if (bUpdatePrevious && m_pnext != NULL)
   //   {

   //      m_pnext->update_previous_pointers(false);

   //   }

   //   m_iLevelNextChild = m_iLevel;

   //   m_pnextChild = calc_next(true, false, &m_iLevelNextChild);

   //   if (bUpdatePrevious && m_pnextChild != NULL && m_pnextChild != m_pnext)
   //   {

   //      m_pnextChild->update_next_pointers(false);

   //   }

   //   m_iLevelNextParent = m_iLevel;

   //   m_pnextParent = calc_next(false, true, &m_iLevelNextParent);

   //   if (bUpdatePrevious && m_pnextParent != NULL && m_pnextParent != m_pnext  && m_pnextParent != m_pnextChild)
   //   {

   //      m_pnextParent->update_next_pointers(false);

   //   }

   //   m_iLevelNextParentChild = m_iLevel;

   //   m_pnextParentChild = calc_next(true, true, &m_iLevelNextParentChild);

   //   if (bUpdatePrevious && m_pnextParentChild != NULL && m_pnextParentChild != m_pnext && m_pnextParentChild != m_pnextChild  && m_pnextParentChild != m_pnextParent)
   //   {

   //      m_pnextParentChild->update_next_pointers(false);

   //   }

   //}


   void tree_item::on_fill_children()
   {

      if (m_pitem != NULL)
      {

         m_pitem->data_item_on_fill_children(this);

      }

      for (index i = 0; i < m_children.get_count(); i++)
      {

         if (m_children[i]->is_expanded())
         {

            m_children[i]->on_fill_children();

         }

      }

   }


} // namespace data



