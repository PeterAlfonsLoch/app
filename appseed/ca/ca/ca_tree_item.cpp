#include "framework.h"

namespace ca
{

/*   #define ROUND(x,y) (((x)+(y-1))&~(y-1))
   #define ROUND4(x) ROUND(x, 4)
   __STATIC fixed_alloc_no_sync _alloc001TreeDataItem(ROUND4(sizeof(tree_item)));

#undef new
   void * tree_item::operator new(size_t, const char *, int32_t)
   {
      return _alloc001TreeDataItem.Alloc();
   }

   void * tree_item::operator new(size_t)
   {
      return _alloc001TreeDataItem.Alloc();
   }
#define new DEBUG_NEW

   void tree_item::operator delete(void * p)
   {
      return _alloc001TreeDataItem.Free(p);
   }

   void tree_item::operator delete(void * p, const char *, int32_t)
   {
      return _alloc001TreeDataItem.Free(p);
   }*/

   tree_item::tree_item()
   {
      m_dwUser          = 0;
      m_pparent         = ::null();
      m_pchild          = ::null();
      m_pprevious       = ::null();
      m_pnext           = ::null();
      m_dwState         = 0;
      m_pitemdata       = ::null();
   }


   tree_item::~tree_item()
   {

   }

   sp(tree) tree_item::get_tree()
   {
      return m_ptree;
   }

   void tree_item::sort_children(int32_t ( * lpfnCompare )(sp(tree_item) &, sp(tree_item) &))
   {
      
      sp(tree_item) pitemParent = this;
      sp(tree_item) pitem1 = pitemParent->m_pchild;
      sp(tree_item) pitem2;
      for(; pitem1 != ::null(); pitem1 = pitem1->m_pnext)
      {
         pitem2 = pitem1->m_pnext;
         for(;pitem2 != ::null(); pitem2 = pitem2->m_pnext)
         {
            if(lpfnCompare(pitem1, pitem2) > 0)
            {
               swap_sibling(pitem1, pitem2);
            }
         }
      }

   }

   void tree_item::swap_sibling(sp(tree_item) pitem1, sp(tree_item) pitem2)
   {
      ASSERT(pitem1 != ::null());
      ASSERT(pitem2 != ::null());
      ASSERT(pitem1->m_pparent == pitem2->m_pparent);

      sp(tree_item) pprevious1 = pitem1->m_pprevious;
      sp(tree_item) pnext1 = pitem1->m_pnext;
      sp(tree_item) pprevious2 = pitem2->m_pprevious;
      sp(tree_item) pnext2 = pitem2->m_pnext;
      if(pitem1->m_pnext == pitem2)
      {
         pitem1->m_pnext      = pnext2;
         pitem2->m_pprevious  = pprevious1;
         pitem1->m_pprevious  = pitem2;
         pitem2->m_pnext      = pitem1;
         if(pprevious1 != ::null())
         {
            pprevious1->m_pnext = pitem2;
         }
         if(pnext2 != ::null())
         {
            pnext2->m_pprevious = pitem1;
         }
      }
      else if(pitem1->m_pprevious == pitem2)
      {
         pitem1->m_pprevious  = pprevious2;
         pitem2->m_pnext      = pnext1;
         pitem1->m_pnext      = pitem2;
         pitem2->m_pprevious  = pitem1;
         if(pnext1 != ::null())
         {
            pnext1->m_pprevious = pitem2;
         }
         if(pprevious2 != ::null())
         {
            pprevious2->m_pnext = pitem1;
         }
      }
      else
      {
         pitem1->m_pprevious  = pprevious2;
         pitem1->m_pnext      = pnext2;
         pitem2->m_pprevious  = pprevious1;
         pitem2->m_pnext      = pnext1;
         if(pprevious1 != ::null())
         {
            pprevious1->m_pnext = pitem2;
         }
         if(pnext1 != ::null())
         {
            pnext1->m_pprevious = pitem2;
         }
         if(pprevious2 != ::null())
         {
            pprevious2->m_pnext = pitem1;
         }
         if(pnext2 != ::null())
         {
            pnext2->m_pprevious = pitem1;
         }
      }

      if(pitem2->m_pparent->m_pchild == pitem2)
      {
         pitem2->m_pparent->m_pchild = pitem1;
      }
      else if(pitem1->m_pparent->m_pchild == pitem1)
      {
         pitem1->m_pparent->m_pchild = pitem2;
      }

   }

   ::count tree_item::remove_tree_item()
   {

      ::count c = 1; // this

      c += remove_tree_item_descendants();

      if(m_pnext != ::null())
      {

         m_pnext->m_pprevious = m_pprevious;

      }


      if(m_pprevious != ::null())
      {

         m_pprevious->m_pnext = m_pnext;

      }

      if(m_pparent != ::null())
      {
         
         if(m_pparent->m_pchild == this)
         {
            
            m_pparent->m_pchild = m_pnext;

         }

      }

      return c;

   }


   ::count tree_item::remove_tree_item_descendants()
   {
      
      ::count c = 0;

      while(m_pchild.is_set())
      {

         c += m_pchild->remove_tree_item();

      }

      return c;

   }


   sp(tree_item) tree_item::find_next_by_user_data(uint_ptr iUserData)
   {
      sp(tree_item) pitem = this;
      while(true)
      {
         pitem = pitem->get_item(TreeNavigationExpandedForward);
         if(pitem == ::null())
            return ::null();
         if(pitem->m_dwUser == (uint32_t) iUserData)
            return pitem;
      }
   }

   sp(tree_item) tree_item::get_child_by_user_data(uint_ptr iUserData)
   {
      sp(tree_item) pitem = m_pchild;
      while(pitem != ::null())
      {
         if(pitem->m_dwUser == iUserData)
            return pitem;
         pitem = pitem->m_pnext;
      }
      return ::null();
   }

   void tree_item::get_children(tree_item_ptr_array & ptra)
   {
      sp(tree_item) pitem = m_pchild;
      while(pitem != ::null())
      {
         ptra.add(pitem);
         pitem = pitem->m_pnext;
      }
   }


   ::count tree_item::get_children_count()
   {
      ::count iCount = 0;
      sp(tree_item) pitem = m_pchild;
      while(pitem != ::null())
      {
         iCount++;
         pitem = pitem->m_pnext;
      }
      return iCount;
   }

   ::count tree_item::get_expandable_children_count()
   {
      ::count iCount = 0;
      sp(tree_item) pitem = m_pchild;
      while(pitem != ::null())
      {
         if(pitem->get_children_count() > 0)
         {
            iCount++;
         }
         pitem = pitem->m_pnext;
      }
      return iCount;
   }

   sp(tree_item) tree_item::get_expandable_child(index iIndex)
   {
      ::count iCount = 0;
      sp(tree_item) pitem = m_pchild;
      while(pitem != ::null())
      {
         if(pitem->get_children_count() > 0)
         {
            if(iCount == iIndex)
               return pitem;
            iCount++;
         }
         pitem = pitem->m_pnext;
      }
      return ::null();
   }

   ::count tree_item::get_proper_descendant_count()
   {
      ::count iCount = 0;
      index iLevel = 0;
      sp(tree_item) pitem = this;
      for(;;)
      {
         pitem = pitem->get_item(TreeNavigationProperForward, &iLevel);
         if(pitem == ::null() || iLevel <= 0)
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
         return get_next((m_dwState & ::ca::tree_item_state_expanded) != 0, true, pindexLevel);
      default:
         // Not Expected
         ASSERT(FALSE);
         return ::null();
      }
   }

   sp(tree_item) tree_item::get_item(ERelative erelative)
   {
      sp(tree_item) pitem;
      switch(erelative)
      {
      case RelativeFirstChild:
         {
            return m_pchild;
         }
         break;
      case RelativeLastChild:
         {
            if(m_pchild == ::null())
               return ::null();
            pitem = m_pchild;
            while(pitem->m_pnext != ::null())
            {
               pitem = pitem->m_pnext;
            }
            return pitem;
         }
      case RelativeParent:
         {
            return m_pparent;
         }
         break;
      case RelativeFirstSibling:
         {
            ASSERT(m_pparent != ::null());
            return m_pparent->get_item(RelativeFirstChild);
         }
         break;
      case RelativePreviousSibling:
         {
            return m_pprevious;
         }
         break;
      case RelativeNextSibling:
         {
            return m_pnext;
         }
         break;
      case RelativeLastSibling:
         {
            ASSERT(m_pparent != ::null());
            return m_pparent->get_item(RelativeLastChild);
         }
         break;
      default:
         // Not Expected
         ASSERT(FALSE);
         return ::null();
      }
   }

   sp(tree_item) tree_item::get_previous()
   {
      if(m_pprevious != ::null())
         return m_pprevious;
      else
         return m_pparent;
   }


   sp(tree_item) tree_item::get_next(bool bChild, bool bParent, index * pindexLevel)
   {
      if(bChild && m_pchild != ::null())
      {
         if(pindexLevel != ::null()) (*pindexLevel)++;
         return m_pchild;
      }
      else if(m_pnext != ::null())
         return m_pnext;
      else if(bParent && m_pparent != ::null())
      {
         if(pindexLevel != ::null()) (*pindexLevel)--;
         return m_pparent->get_next(false, true, pindexLevel);
      }
      else
         return ::null();
   }


   bool tree_item::add_selection()
   {
      return m_ptree->add_tree_item_selection(this);
   }

   bool tree_item::set_selection()
   {
      return m_ptree->set_tree_item_selection(this);
   }

   bool tree_item::clear_selection()
   {
      return m_ptree->remove_tree_item_selection(this);
   }

   bool tree_item::remove_selection()
   {
      return m_ptree->remove_tree_item_selection(this);
   }

   bool tree_item::hover()
   {
      return m_ptree->hover_tree_item(this);
   }

   bool tree_item::is_hover()
   {
      return m_ptree->is_tree_item_hover(this);
   }

   bool tree_item::is_selected()
   {
      return m_ptree->is_tree_item_selected(this);
   }


   string tree_item::get_text()
   {
      if(m_pitemdata == ::null())
         return "";
      return m_pitemdata->get_text(m_ptree);
   }

   index tree_item::get_image()
   {
      if(m_pitemdata == ::null())
         return -1;
      return m_pitemdata->get_image(m_ptree);
   }

   sp(image_list) tree_item::get_image_list()
   {
      
      if(m_ptreedata != ::null())
         return m_ptreedata->m_pimagelist;

      if(m_ptree != ::null())
         return m_ptree->get_image_list();

      return ::null();

   }


   sp(tree_item) tree_item::get_proper_item(index iIndex, index * piLevel)
   {
      if(*piLevel) *piLevel = 0;
      sp(tree_item) pitem = this;
      while(pitem != ::null() && iIndex >= 0)
      {
         pitem = pitem->get_item(TreeNavigationProperForward, piLevel);
         iIndex--;
      }
      return pitem;
   }

   index tree_item::get_proper_item_index(sp(tree_item) pitemParam, index * piLevel)
   {
      int32_t iIndex = 0;
      if(piLevel != ::null()) *piLevel = 0;
      sp(tree_item) pitem = this;
      while(pitem != ::null())
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
      while(pitem != ::null())
      {
         pitem = pitem->get_item(TreeNavigationProperForward, &iLevel);
         iCount++;
         if(iLevel <= 0)
            break;
      }
      return iCount;
   }

} // namespace ca
