#include "framework.h"


namespace user
{


   tree_data::tree_data(sp(::axis::application) papp):
      element(papp),
      ::data::data(papp),
      ::data::tree(papp)
   {

         m_bFill = false;

         m_proot = new ::data::tree_item;

         if(m_proot == NULL)
            throw memory_exception(get_app());

         m_proot->m_dwState |= ::data::tree_item_state_expandable;

         m_proot->m_dwState |= ::data::tree_item_state_expanded;

         m_proot->m_ptree = this;


      }


   tree_data::~tree_data()
   {

   }


   sp(::data::tree_item) tree_data::find(::data::item * pitemdata,index * piIndex)
   {

      index iIndex;

      if(pitemdata == NULL)
         return NULL;

      if(piIndex == NULL)
         iIndex = 0;
      else
         iIndex = *piIndex;


      sp(::data::tree_item) pitem = m_proot;
      for(; pitem != NULL; pitem = pitem->get_item(::data::TreeNavigationExpandedForward))
      {
         if(pitem->m_pitem == pitemdata)
         {
            iIndex--;
            if(iIndex < 0)
               return pitem;
         }
      }

      if(piIndex != NULL)
         *piIndex = iIndex;

      return NULL;

   }

   bool tree_data::contains(::data::item * pitemdata)
   {
      return find(pitemdata) != NULL;
   }

   bool tree_data::contains(::data::tree_item * pitemParam)
   {
      sp(::data::tree_item) pitem = m_proot;
      for(; pitem != NULL; pitem = pitem->get_item(::data::TreeNavigationExpandedForward))
      {
         if(pitem == pitemParam)
            return true;
      }
      return false;
   }


   void tree_data::_001OnTreeDataChange()
   {
   }


   ::count tree_data::remove(::data::item * pitemdata,index i)
   {
      sp(::data::tree_item) pitem = find(pitemdata,&i);
      if(pitem == NULL)
         return false;
      return remove(pitem);
   }

   ::count tree_data::remove(::data::tree_item_ptr_array & itemptra)
   {

      ::count ca = 0;

      for(int32_t i = 0; i < itemptra.get_count(); i++)
      {

         ca += remove(itemptra(i));

      }

      return ca;

   }

   ::count tree_data::remove(::data::tree_item * pitem)
   {

      if(pitem->m_ptree == this)
         return pitem->remove_tree_item();

      return 0;

   }



   sp(::data::tree_item) tree_data::get_proper_item(index iIndex,index * piLevel,index * piCount)
   {

      index iCount = 0;

      if(*piLevel)
         *piLevel = 0;

      sp(::data::tree_item) pitem = get_base_item();

      while(pitem != NULL && iIndex >= 0)
      {
         pitem = pitem->get_item(::data::TreeNavigationProperForward,piLevel);
         iIndex--;
         iCount++;
      }

      if(iIndex < 0 && pitem.is_set())
         return pitem;

      if(piCount != NULL)
         *piCount = iCount;

      return NULL;

   }

   index tree_data::get_proper_item_index(::data::tree_item *pitemParam,index * piLevel,index * piCount)
   {

      //      index iFound = 0;

      int32_t iIndex = 0;

      count iCount = 0;

      if(piLevel != NULL)
         *piLevel = 0;

      sp(::data::tree_item) pitem = get_base_item();

      while(pitem != NULL)
      {
         pitem = pitem->get_item(::data::TreeNavigationProperForward,piLevel);
         if(pitem == pitemParam)
         {
            if(piCount != NULL)
               *piCount += iCount;
            return iIndex;
         }
         iIndex++;
         iCount++;
      }

      if(piCount != NULL)
         *piCount += iCount;

      return -1;

   }

   ::count tree_data::get_proper_item_count()
   {
      return get_base_item()->get_proper_item_count();
   }


   sp(::data::tree_item) tree_data::get_base_item()
   {
      return m_proot;
   }

   sp(::data::tree_item) tree_data::insert_item(::data::item * pitemdataNew,::data::ERelative erelativeNewItem,::data::tree_item *pitemRelative)
   {
      if(erelativeNewItem == ::data::RelativeReplace)
      {

         if(!contains(pitemRelative))
            return NULL;

         pitemRelative->m_pitem = pitemdataNew;

         return pitemRelative;

      }
      sp(::data::tree_item) pitemNew = new ::data::tree_item;
      if(pitemNew == NULL)
         return NULL;
      if(!insert_item(pitemNew,erelativeNewItem,pitemRelative))
      {
         return NULL;
      }
      pitemNew->m_pitem = pitemdataNew;
      return pitemNew;
   }


   bool tree_data::insert_item(::data::tree_item *pitemNew,::data::ERelative erelativeNewItem,::data::tree_item *pitemRelative)
   {
      if(pitemNew == NULL)
         return false;
      if(!contains(pitemRelative))
         return false;
      if(erelativeNewItem == ::data::RelativeParent)
         return false;

      if(erelativeNewItem == ::data::RelativeLastSibling)
      {
         if(pitemRelative == m_proot)
         {
            erelativeNewItem = ::data::RelativeFirstChild;
         }
      }

      switch(erelativeNewItem)
      {
      case ::data::RelativeFirstChild:
      {
                                        pitemRelative->m_children.insert_at(0,pitemNew);
                                        pitemNew->m_pparent = pitemRelative;
      }
         break;
      case ::data::RelativeLastChild:
      {
                                       pitemRelative->m_children.add(pitemNew);
                                       pitemNew->m_pparent = pitemRelative;
      }
         break;
      case ::data::RelativePreviousSibling:
      {
                                             // all tree_data items that have siblings have a parent (at least the base ::data::item)
                                             ASSERT(pitemRelative->m_pparent != NULL);
                                             // Is pitemRelative a first child ?
                                             index iFind = pitemRelative->m_pparent->m_children.find_first(pitemRelative);
                                             if(iFind > 0)
                                                iFind--;
                                             pitemRelative->m_pparent->m_children.insert_at(0,pitemNew);
                                             pitemNew->m_pparent = pitemRelative->m_pparent;
      }
         break;
      case ::data::RelativeNextSibling:
      {
                                         // all tree_data items that have siblings have a parent (at least the base ::data::item)
                                         ASSERT(pitemRelative->m_pparent != NULL);
                                         // Is pitemRelative a first child ?
                                         index iFind = pitemRelative->m_pparent->m_children.find_first(pitemRelative);
                                         if(iFind < 0)
                                            iFind = 0;
                                         else
                                            iFind++;
                                         pitemRelative->m_pparent->m_children.insert_at(0,pitemNew);
                                         pitemNew->m_pparent = pitemRelative->m_pparent;
      }
         break;
      case ::data::RelativeLastSibling:
      {
                                         // all tree_data items that have siblings have a parent (at least the base ::data::item)
                                         ASSERT(pitemRelative->m_pparent != NULL);
                                         pitemRelative->m_pparent->m_children.add(pitemNew);
                                         pitemNew->m_pparent = pitemRelative->m_pparent;
      }
         break;
      case ::data::RelativeReplace:
      {
                                     pitemNew->m_dwUser      = pitemRelative->m_dwUser;
                                     pitemNew->m_dwMetaData  = pitemRelative->m_dwMetaData;
                                     pitemNew->m_pparent     = pitemRelative->m_pparent;
                                     pitemNew->m_children    = pitemRelative->m_children;
                                     pitemNew->m_dwState     = pitemRelative->m_dwState;
                                     pitemNew->m_pitem       = pitemRelative->m_pitem;
                                     index iFind = pitemRelative->m_pparent->m_children.find_first(pitemRelative);
                                     if(iFind >= 0)
                                     {
                                        pitemRelative->m_pparent->m_children.element_at(iFind) = pitemNew;
                                     }
      }
         break;
      case ::data::RelativeMacroRecord:
      {
                                         if(pitemRelative->get_next(false,false) != NULL)
                                         {
                                            insert_item(pitemNew,::data::RelativeFirstChild,pitemRelative);
                                         }
                                         else
                                         {
                                            insert_item(pitemNew,::data::RelativeLastSibling,pitemRelative);
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

   void tree_data::remove_all()
   {

      get_base_item()->m_children.remove_all();

   }

   void tree_data::sort(index(* lpfnCompare)(sp(::data::tree_item) *,sp(::data::tree_item) *))
   {
      sp(::data::tree_item) pitem = get_base_item();
      while(pitem != NULL)
      {
         pitem->sort_children(lpfnCompare);
         pitem = (sp(::data::tree_item)) pitem->get_next();
      }
   }


   void tree_data::_001ExpandItem(::data::tree_item * pitem,::action::context actioncontext,bool bExpand,bool bRedraw,bool bLayout)
   {

      for(index i = 0; i < m_treeptra.get_count(); i++)
      {

         m_treeptra[i]->_001ExpandItem(pitem,actioncontext,bExpand,bRedraw,bLayout);

      }

   }

   void tree_data::_001EnsureVisible(::data::tree_item * pitem)
   {

      for(index i = 0; i < m_treeptra.get_count(); i++)
      {

         m_treeptra[i]->_001EnsureVisible(pitem);

      }

   }


   void tree_data::_001SelectItem(::data::tree_item * pitem)
   {

      for(index i = 0; i < m_treeptra.get_count(); i++)
      {

         m_treeptra[i]->_001SelectItem(pitem);

      }

   }

   void tree_data::get_selection(::data::tree_item_ptr_array & itemptraSelected) const
   {

      for(index i = 0; i < m_treeptra.get_count(); i++)
      {

         itemptraSelected.add_unique(m_treeptra[i]->m_itemptraSelected);

      }

   }


   bool tree_data::is_selected(const ::data::tree_item * pitem) const
   {

      for(index i = 0; i < m_treeptra.get_count(); i++)
      {

         if(m_treeptra[i]->is_selected(pitem))
            return true;

      }

      return false;

   }


   bool tree_data::is_selected(const ::data::item * pitem) const
   {

      for(index i = 0; i < m_treeptra.get_count(); i++)
      {

         if(m_treeptra[i]->is_selected(pitem))
            return true;

      }

      return false;

   }


   void tree_data::_001OnItemExpand(::data::tree_item * pitem,::action::context actioncontext)
   {

      if(pitem->is_expanded())
         return;

      pitem->on_fill_children();

      if(pitem->get_children_count() > 0)
      {
         pitem->m_dwState |= ::data::tree_item_state_expanded;
         pitem->m_dwState |= ::data::tree_item_state_expandable;
      }

      /*      for (index i = 0; i < m_treeptra.get_count(); i++)
      {

      m_treeptra[i]->_001OnItemExpand(pitem, actioncontext);

      }*/




   }


   void tree_data::_001OnItemCollapse(::data::tree_item * pitem,::action::context actioncontext)
   {

      if(!pitem->is_expanded())
         return;
      if(pitem->get_children_count() > 0)
      {
         pitem->m_dwState |= ::data::tree_item_state_expandable;
      }
      pitem->m_dwState &= ~::data::tree_item_state_expanded;
      /*for (index i = 0; i < m_treeptra.get_count(); i++)
      {

      m_treeptra[i]->_001OnItemCollapse(pitem);

      }*/

   }


   void tree_data::_001OnOpenItem(::data::tree_item * pitem,::action::context actioncontext)
   {

      for(index i = 0; i < m_treeptra.get_count(); i++)
      {

         m_treeptra[i]->_001OnOpenItem(pitem,actioncontext);

      }

   }


   void tree_data::_001OnItemContextMenu(::data::tree_item * pitem,::action::context actioncontext,::user::tree * ptree,point pt)
   {

      for(index i = 0; i < m_treeptra.get_count(); i++)
      {

         m_treeptra[i]->_001OnItemContextMenu(pitem,actioncontext,ptree,pt);

      }

   }


   ::count   tree_data::selection_set(::data::tree_item_ptr_array & itemptra)
   {

      ::count c = 0;

      for(index iTree = 0; iTree < m_treeptra.get_count(); iTree++)
      {

         c += m_treeptra[iTree]->selection_set(itemptra);

      }

      return c;

   }


   bool      tree_data::selection_set(::data::tree_item * pitem,bool bIfNotInSelection,bool bIfParentInSelection)
   {

      bool bAllOk = true;

      for(index iTree = 0; iTree < m_treeptra.get_count(); iTree++)
      {

         if(!m_treeptra[iTree]->selection_set(pitem))
            bAllOk = false;

      }


      return bAllOk;

   }


   bool      tree_data::selection_set(::data::item * pitem,bool bIfNotInSelection,bool bIfParentInSelection)
   {

      bool bAllOk = true;

      for(index iTree = 0; iTree < m_treeptra.get_count(); iTree++)
      {

         if(!m_treeptra[iTree]->selection_set(pitem,bIfNotInSelection,bIfParentInSelection))
            bAllOk = false;

      }

      return bAllOk;

   }


   bool      tree_data::selection_set(index iIndex,::data::item * pitem,bool bIfNotInSelection,bool bIfParentInSelection)
   {

      bool bAllOk = true;

      for(index iTree = 0; iTree < m_treeptra.get_count(); iTree++)
      {

         if(!m_treeptra[iTree]->selection_set(iIndex,pitem,bIfNotInSelection,bIfParentInSelection))
            bAllOk = false;

      }

      return bAllOk;

   }


   sp(image_list) tree_data::get_image_list() const
   {

      return m_pimagelist;

   }

   void tree_data::on_update(sp(::user::impact) pSender,LPARAM lHint,::object* pHint)
   {

   }



   void tree_data::on_fill_children()
   {

   }




   void tree_data::tree_layout()
   {

      for(index i = 0; i < m_treeptra.get_count(); i++)
      {
         try
         {

            m_treeptra[i]->layout();

         }
         catch(...)
         {
         }

      }

   }


   void tree_data::on_merge_user_tree(::user::tree * pusertree)
   {

      UNREFERENCED_PARAMETER(pusertree);

   }


   void tree_data::on_bind_user_tree(::user::tree * pusertree)
   {

      UNREFERENCED_PARAMETER(pusertree);

   }



} // namespace data



