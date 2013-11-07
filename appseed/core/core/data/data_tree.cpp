#include "framework.h"


namespace data
{


   tree::tree(sp(base_application) papp) :
      element(papp)
   {

/*    
      
      m_proot = new tree_item;

      if(m_proot == NULL)
         throw memory_exception(get_app());

      m_proot->m_dwState |= ::data::tree_item_state_expandable;

      m_proot->m_dwState |= ::data::tree_item_state_expanded;

      ::data::simple_item * pitemdata = new ::data::simple_item();

      m_proot->m_proot = pitemdata;

      pitemdata->m_str = "tree";

*/

   }


   tree::~tree()
   {

   }


   sp(tree_item) tree::find(item * pitemdata, index i)
   {
      if(i < 0)
         return NULL;
      if(pitemdata == NULL)
         return NULL;
      sp(::data::tree_item) pitem = m_proot;
      for(; pitem != NULL; pitem = pitem->get_item(TreeNavigationExpandedForward))
      {
         if(pitem->m_pitem == pitemdata)
         {
            i--;
            if(i < 0)
               return pitem;
         }
      }
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
      sp(tree_item) pitem = find(pitemdata, i);
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



   sp(::data::tree_item) tree::get_proper_item(index iIndex, index * piLevel)
   {
      if(*piLevel) *piLevel = 0;
      sp(::data::tree_item) pitem = get_base_item();
      while(pitem != NULL && iIndex >= 0)
      {
         pitem = pitem->get_item(TreeNavigationProperForward, piLevel);
         iIndex--;
      }
      return pitem;

   }

   index tree::get_proper_item_index(::data::tree_item *pitemParam, index * piLevel)
   {
      int32_t iIndex = 0;
      if(piLevel != NULL) *piLevel = 0;
      sp(::data::tree_item) pitem = get_base_item();
      while(pitem != NULL)
      {
         pitem = pitem->get_item(TreeNavigationProperForward, piLevel);
         if(pitem == pitemParam)
            return iIndex;
         iIndex++;
      }
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
         }
         break;
      case RelativeLastChild:
         {
            pitemRelative->m_children.add(pitemNew);
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
         }
         break;
      case RelativeLastSibling:
         {
            // all tree items that have siblings have a parent (at least the base item)
            ASSERT(pitemRelative->m_pparent != NULL);
            pitemRelative->m_pparent->m_children.add(pitemNew);
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





} // namespace data



