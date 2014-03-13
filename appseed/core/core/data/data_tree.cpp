#include "framework.h"


namespace data
{


   tree::tree(sp(base_application) papp) :
      element(papp),
      ::data::data(papp),
      m_mutex(papp)
   {

      m_bFill = false;
      
      m_proot = new tree_item;

      if(m_proot == NULL)
         throw memory_exception(get_app());

      m_proot->m_dwState |= ::data::tree_item_state_expandable;

      m_proot->m_dwState |= ::data::tree_item_state_expanded;

      m_proot->m_ptree = this;


   }


   tree::~tree()
   {

   }


   sp(tree_item) tree::find(item * pitemdata, index * piIndex)
   {
      
      index iIndex;

      if(pitemdata == NULL)
         return NULL;

      if (piIndex == NULL)
         iIndex = 0;
      else
         iIndex = *piIndex;


      sp(::data::tree_item) pitem = m_proot;
      for(; pitem != NULL; pitem = pitem->get_item(TreeNavigationExpandedForward))
      {
         if(pitem->m_pitem == pitemdata)
         {
            iIndex--;
            if(iIndex < 0)
               return pitem;
         }
      }

      if (piIndex != NULL)
         *piIndex = iIndex;

      return NULL;

   }

   bool tree::contains(item * pitemdata)
   {
      return find(pitemdata) != NULL;
   }

   bool tree::contains(tree_item * pitemParam)
   {
      sp(::data::tree_item) pitem = m_proot;
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


   ::count tree::remove(item * pitemdata, index i)
   {
      sp(tree_item) pitem = find(pitemdata, &i);
      if(pitem == NULL)
         return false;
      return remove(pitem);
   }

   ::count tree::remove(tree_item_ptr_array & itemptra)
   {

      ::count ca = 0;

      for(int32_t i = 0; i < itemptra.get_count(); i++)
      {

         ca += remove(itemptra(i));

      }

      return ca;

   }

   ::count tree::remove(tree_item * pitem)
   {

      if(pitem->m_ptree == this)
         return pitem->remove_tree_item();

      return 0;

   }



   sp(::data::tree_item) tree::get_proper_item(index iIndex, index * piLevel, index * piCount)
   {

      index iCount = 0;

      if(*piLevel) 
         *piLevel = 0;

      sp(::data::tree_item) pitem = get_base_item();
      
      while(pitem != NULL && iIndex >= 0)
      {
         pitem = pitem->get_item(TreeNavigationProperForward, piLevel);
         iIndex--;
         iCount++;
      }
      
      if (iIndex < 0 && pitem.is_set())
         return pitem;

      if (piCount != NULL)
         *piCount = iCount;

      return NULL;

   }

   index tree::get_proper_item_index(::data::tree_item *pitemParam, index * piLevel, index * piCount)
   {
      
//      index iFound = 0;

      int32_t iIndex = 0;

      count iCount = 0;

      if(piLevel != NULL)
         *piLevel = 0;

      sp(::data::tree_item) pitem = get_base_item();

      while (pitem != NULL)
      {
         pitem = pitem->get_item(TreeNavigationProperForward, piLevel);
         if (pitem == pitemParam)
         {
            if (piCount != NULL)
               *piCount += iCount;
            return iIndex;
         }
         iIndex++;
         iCount++;
      }

      if (piCount != NULL)
         *piCount += iCount;
         
      return -1;

   }

   ::count tree::get_proper_item_count()
   {
      return get_base_item()->get_proper_item_count();
   }


   sp(::data::tree_item) tree::get_base_item()
   {
      return m_proot;
   }

   sp(::data::tree_item) tree::insert_item(::data::item * pitemdataNew, ERelative erelativeNewItem, ::data::tree_item *pitemRelative)
   {
      if(erelativeNewItem == RelativeReplace)
      {

         if(!contains(pitemRelative))
            return NULL;

         pitemRelative->m_pitem = pitemdataNew;

         return pitemRelative;

      }
      sp(::data::tree_item) pitemNew = new tree_item;
      if(pitemNew == NULL)
         return NULL;
      if(!insert_item(pitemNew, erelativeNewItem, pitemRelative))
      {
         return NULL;
      }
      pitemNew->m_pitem = pitemdataNew;
      return pitemNew;
   }


   bool tree::insert_item(::data::tree_item *pitemNew, ERelative erelativeNewItem, ::data::tree_item *pitemRelative)
   {
      if(pitemNew == NULL)
         return false;
      if(!contains(pitemRelative))
         return false;
      if(erelativeNewItem == RelativeParent)
         return false;

      if(erelativeNewItem == RelativeLastSibling)
      {
         if(pitemRelative == m_proot)
         {
            erelativeNewItem = RelativeFirstChild;
         }
      }

      switch(erelativeNewItem)
      {
      case RelativeFirstChild:
         {
            pitemRelative->m_children.insert_at(0, pitemNew);
            pitemNew->m_pparent = pitemRelative;
         }
         break;
      case RelativeLastChild:
         {
            pitemRelative->m_children.add(pitemNew);
            pitemNew->m_pparent = pitemRelative;
         }
         break;
      case RelativePreviousSibling:
         {
            // all tree items that have siblings have a parent (at least the base item)
            ASSERT(pitemRelative->m_pparent != NULL);
            // Is pitemRelative a first child ?
            index iFind = pitemRelative->m_pparent->m_children.find_first(pitemRelative);
            if(iFind > 0)
               iFind--;
            pitemRelative->m_pparent->m_children.insert_at(0, pitemNew);
            pitemNew->m_pparent = pitemRelative->m_pparent;
         }
         break;
      case RelativeNextSibling:
         {
            // all tree items that have siblings have a parent (at least the base item)
            ASSERT(pitemRelative->m_pparent != NULL);
            // Is pitemRelative a first child ?
            index iFind = pitemRelative->m_pparent->m_children.find_first(pitemRelative);
            if (iFind < 0)
               iFind = 0;
            else
               iFind++;
            pitemRelative->m_pparent->m_children.insert_at(0, pitemNew);
            pitemNew->m_pparent = pitemRelative->m_pparent;
         }
         break;
      case RelativeLastSibling:
         {
            // all tree items that have siblings have a parent (at least the base item)
            ASSERT(pitemRelative->m_pparent != NULL);
            pitemRelative->m_pparent->m_children.add(pitemNew);
            pitemNew->m_pparent = pitemRelative->m_pparent;
         }
         break;
      case RelativeReplace:
         {
            pitemNew->m_dwUser      = pitemRelative->m_dwUser;
            pitemNew->m_dwMetaData  = pitemRelative->m_dwMetaData;
            pitemNew->m_pparent     = pitemRelative->m_pparent;
            pitemNew->m_children    = pitemRelative->m_children;
            pitemNew->m_dwState     = pitemRelative->m_dwState;
            pitemNew->m_pitem       = pitemRelative->m_pitem;
            index iFind = pitemRelative->m_pparent->m_children.find_first(pitemRelative);
            if (iFind >= 0)
            {
               pitemRelative->m_pparent->m_children.element_at(iFind) = pitemNew;
            }
        }
         break;
      case RelativeMacroRecord:
      {
         if (pitemRelative->get_next(false, false) != NULL)
         {
            insert_item(pitemNew, ::data::RelativeFirstChild, pitemRelative);
         }
         else
         {
            insert_item(pitemNew, ::data::RelativeLastSibling, pitemRelative);
         }

      }
         break;
         default:
            throw not_supported_exception(get_app());
      }
      pitemNew->m_ptree = this;
      _001OnTreeDataChange();
      return true;
   }

   void tree::remove_all()
   {

      get_base_item()->m_children.remove_all();

   }

   void tree::sort(index ( * lpfnCompare )(sp(tree_item) *, sp(tree_item) *))
   {
      sp(tree_item) pitem = get_base_item();
      while(pitem != NULL)
      {
         pitem->sort_children(lpfnCompare);
         pitem = (sp(tree_item)) pitem->get_next();
      }
   }


   void tree::_001ExpandItem(::data::tree_item * pitem, ::action::context actioncontext, bool bExpand, bool bRedraw, bool bLayout)
   {

      for (index i = 0; i < m_treeptra.get_count(); i++)
      {

         m_treeptra[i]._001ExpandItem(pitem, actioncontext, bExpand, bRedraw, bLayout);

      }

   }

   void tree::_001EnsureVisible(::data::tree_item * pitem)
   {

      for (index i = 0; i < m_treeptra.get_count(); i++)
      {

         m_treeptra[i]._001EnsureVisible(pitem);

      }

   }


   void tree::_001SelectItem(::data::tree_item * pitem)
   {

      for (index i = 0; i < m_treeptra.get_count(); i++)
      {

         m_treeptra[i]._001SelectItem(pitem);

      }

   }

   void tree::get_selection(::data::tree_item_ptr_array & itemptraSelected) const
   {

      for (index i = 0; i < m_treeptra.get_count(); i++)
      {

         itemptraSelected.add_unique(m_treeptra[i].m_itemptraSelected);

      }

   }


   bool tree::is_selected(const ::data::tree_item * pitem) const
   {

      for (index i = 0; i < m_treeptra.get_count(); i++)
      {

         if (m_treeptra[i].is_selected(pitem))
            return true;

      }

      return false;

   }


   bool tree::is_selected(const ::data::item * pitem) const
   {

      for (index i = 0; i < m_treeptra.get_count(); i++)
      {

         if (m_treeptra[i].is_selected(pitem))
            return true;

      }

      return false;

   }


   void tree::_001OnItemExpand(::data::tree_item * pitem, ::action::context actioncontext)
   {

      if (pitem->is_expanded())
         return;

      pitem->on_fill_children();

      if (pitem->get_children_count() > 0)
      {
         pitem->m_dwState |= ::data::tree_item_state_expanded;
         pitem->m_dwState |= ::data::tree_item_state_expandable;
      }

/*      for (index i = 0; i < m_treeptra.get_count(); i++)
      {

         m_treeptra[i]._001OnItemExpand(pitem, actioncontext);

      }*/


      

   }


   void tree::_001OnItemCollapse(::data::tree_item * pitem, ::action::context actioncontext)
   {

      if (!pitem->is_expanded())
         return;
      if (pitem->get_children_count() > 0)
      {
         pitem->m_dwState |= ::data::tree_item_state_expandable;
      }
      pitem->m_dwState &= ~::data::tree_item_state_expanded;
      /*for (index i = 0; i < m_treeptra.get_count(); i++)
      {

         m_treeptra[i]._001OnItemCollapse(pitem);

      }*/

   }


   void tree::_001OnOpenItem(::data::tree_item * pitem, ::action::context actioncontext)
   {

      for (index i = 0; i < m_treeptra.get_count(); i++)
      {

         m_treeptra[i]._001OnOpenItem(pitem, actioncontext);

      }

   }



   ::count   tree::selection_set(::data::tree_item_ptr_array & itemptra)
   {

      ::count c = 0;

      for (index iTree = 0; iTree < m_treeptra.get_count(); iTree++)
      {

         c += m_treeptra[iTree].selection_set(itemptra);

      }

      return c;

   }


   bool      tree::selection_set(::data::tree_item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      bool bAllOk = true;

      for (index iTree = 0; iTree < m_treeptra.get_count(); iTree++)
      {

         if (!m_treeptra[iTree].selection_set(pitem))
            bAllOk = false;

      }


      return bAllOk;

   }


   bool      tree::selection_set(::data::item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      bool bAllOk = true;

      for (index iTree = 0; iTree < m_treeptra.get_count(); iTree++)
      {

         if(!m_treeptra[iTree].selection_set(pitem, bIfNotInSelection, bIfParentInSelection))
            bAllOk = false;

      }

      return bAllOk;

   }


   bool      tree::selection_set(index iIndex, ::data::item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      bool bAllOk = true;

      for (index iTree = 0; iTree < m_treeptra.get_count(); iTree++)
      {

         if (!m_treeptra[iTree].selection_set(iIndex, pitem, bIfNotInSelection, bIfParentInSelection))
            bAllOk = false;

      }

      return bAllOk;

   }


   sp(image_list) tree::get_image_list() const
   {
      
      return m_pimagelist;

   }

   void tree::on_update(sp(::user::impact) pSender, LPARAM lHint, ::object* pHint)
   {

   }



   void tree::on_fill_children()
   {

   }


   void tree::start_fill_children()
   {

      single_lock sl(&m_mutex, true);

      m_bFill = true;

      __begin_thread(get_app(), thread_proc_fill_children, this);

   }

   UINT c_cdecl tree::thread_proc_fill_children(LPVOID lpParameter)
   {

      tree * ptree = (tree *) lpParameter;

      Sleep(284);

      try
      {
         
         ptree->on_fill_children();

      }
      catch (...)
      {

      }

      ptree->m_bFill = false;

      return 0;


   }


} // namespace data



