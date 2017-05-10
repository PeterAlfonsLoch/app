#include "framework.h" // from "base/user/user.h"


namespace data
{


   tree::tree(::aura::application * papp) :
      object(papp),
      ::data::data(papp),
      m_mutex(papp)
   {

      defer_create_mutex();

      m_bFill = false;
      
      m_proot = canew(tree_item);

      if(m_proot == NULL)
         throw memory_exception(get_app());

      m_proot->m_dwState |= ::data::tree_item_state_expandable;

      m_proot->m_dwState |= ::data::tree_item_state_expanded;

      m_proot->m_ptree = this;


   }


   tree::~tree()
   {

   }


   tree_item * tree::find(item * pitemdata, index * piIndex)
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
      ::data::tree_item * pitem = m_proot;
      for(; pitem != NULL; pitem = pitem->get_item(TreeNavigationExpandedForward))
      {
         if(pitem == pitemParam)
            return true;
      }
      return false;
   }


   void tree::_001OnTreeDataChange()
   {
      
      update_levels();

   }


   ::count tree::remove(item * pitemdata, index i)
   {
      tree_item * pitem = find(pitemdata, &i);
      if(pitem == NULL)
         return false;
      return remove(pitem);
   }



   ::count tree::remove(tree_item_ptr_array & itemptra)
   {

      ::count ca = 0;

      for(int32_t i = 0; i < itemptra.get_count(); i++)
      {

         ca += remove(itemptra[i]);

      }

      return ca;

   }

   ::count tree::remove(tree_item * pitem)
   {

      if(pitem->m_ptree == this)
         return pitem->remove_tree_item();

      return 0;

   }



   ::data::tree_item * tree::get_proper_item(index iIndex, index * piLevel, index * piCount)
   {

      index iCount = 0;

      if(piLevel) 
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
      
      synch_lock sl(m_pmutex);

      return get_base_item()->get_proper_item_count();

   }


   ::data::tree_item * tree::get_base_item()
   {
      return m_proot;
   }

   
   ::data::tree_item * tree::insert_item(::data::item * pitemdataNew, ERelative erelativeNewItem, ::data::tree_item *pitemRelative, bool bVoidTreeDataChangeEvent)
   {

      if(erelativeNewItem == RelativeReplace)
      {

         if(!contains(pitemRelative))
            return NULL;

         pitemRelative->m_pitem = pitemdataNew;

         return pitemRelative;

      }
      
      sp(::data::tree_item) pitemNew = canew(tree_item);

      if(pitemNew == NULL)
         return NULL;

      if(!insert_item(pitemNew, erelativeNewItem, pitemRelative, bVoidTreeDataChangeEvent))
      {

         return NULL;

      }
      
      pitemNew->m_pitem = pitemdataNew;
      
      return pitemNew;

   }


   bool tree::insert_item(::data::tree_item *pitemNew, ERelative erelativeNewItem, ::data::tree_item *pitemRelative, bool bVoidTreeDataChangeEvent)
   {

      synch_lock sl(m_pmutex);

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

      bool bOk = false;

      switch(erelativeNewItem)
      {
      case RelativeFirstChild:
         {

            bOk=pitemRelative->insert(erelativeNewItem, pitemNew);

         }
         break;
      case RelativeLastChild:
         {

            bOk = pitemRelative->insert(erelativeNewItem, pitemNew);

         }
         break;
      case RelativePreviousSibling:
         {

            bOk = pitemRelative->insert(erelativeNewItem, pitemNew);

         }
         break;
      case RelativeNextSibling:
         {

            bOk = pitemRelative->insert(erelativeNewItem, pitemNew);

         }
         break;
      case RelativeLastSibling:
         {

            bOk = pitemRelative->insert(erelativeNewItem, pitemNew);

         }
         break;
      case RelativeReplace:
         {

            pitemNew->m_dwUser      = pitemRelative->m_dwUser;
            pitemNew->m_dwMetaData  = pitemRelative->m_dwMetaData;
            pitemNew->m_dwState     = pitemRelative->m_dwState;
            pitemNew->m_pitem       = pitemRelative->m_pitem;

            pitemNew->m_iLevel = pitemRelative->m_iLevel;

            bOk = pitemRelative->insert(erelativeNewItem, pitemNew);

         }
         break;

      case RelativeMacroRecord:
      {

         if (pitemRelative->get_next() != NULL)
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

      if (!bVoidTreeDataChangeEvent)
      {

         _001OnTreeDataChange();

      }

      return true;

   }


   void tree::remove_all()
   {

      get_base_item()->remove_tree_item_descendants();

   }



   void tree::sort(index ( * lpfnCompare )(const sp(tree_item) &, const sp(tree_item) &))
   {
      
      sp(tree_item) pitem = get_base_item();

      while(pitem != NULL)
      {

         pitem->sort_children(lpfnCompare);

         pitem = pitem->get_child_next_or_parent();

      }

   }

   void tree::update_levels()
   {

      index iLevel = -1;

      sp(tree_item) pitem = get_base_item();

      while (pitem != NULL)
      {

         pitem->m_iLevel = iLevel;

         pitem = pitem->get_child_next_or_parent(&iLevel);

      }

   }


   void tree::_001ExpandItem(::data::tree_item * pitem, ::action::context actioncontext, bool bExpand, bool bRedraw, bool bLayout)
   {


   }

   void tree::_001EnsureVisible(::data::tree_item * pitem)
   {


   }


   void tree::_001SelectItem(::data::tree_item * pitem)
   {


   }

   void tree::get_selection(::data::tree_item_ptr_array & itemptraSelected) const
   {


   }


   bool tree::is_selected(const ::data::tree_item * pitem) const
   {


      return false;

   }


   bool tree::is_selected(const ::data::item * pitem) const
   {


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


   }


   void tree::_001OnItemContextMenu(::data::tree_item * pitem, ::action::context actioncontext, ::user::primitive * ptree, point pt)
   {


   }


   ::count   tree::selection_set(::data::tree_item_ptr_array & itemptra)
   {

      return 0;

   }


   bool      tree::selection_set(::data::tree_item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }


   bool      tree::selection_set(::data::item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }


   bool      tree::selection_set(index iIndex, ::data::item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }


   image_list * tree::get_image_list() const
   {
      
      return NULL;

   }

   void tree::on_update(::user::impact * pSender, LPARAM lHint, ::object* pHint)
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


      try
      {


         ptree->tree_layout();

      }
      catch (...)
      {

      }

      ptree->m_bFill = false;

      return 0;


   }

   void tree::tree_layout()
   {

   }


} // namespace data



