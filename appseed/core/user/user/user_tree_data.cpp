//#include "framework.h"


namespace user
{


   tree_data::tree_data(::aura::application * papp):
      object(papp),
      ::data::data(papp),
      ::data::tree(papp)
   {



      }


   tree_data::~tree_data()
   {

   }


   ::count tree_data::get_data_bound_view_count() const
   {
      
      return m_treeptraBound.get_count();

   }


   ::user::impact * tree_data::get_data_bound_view(index iView)
   {

      return dynamic_cast <::user::impact * > (m_treeptraBound[iView]);

   }





   void tree_data::_001OnTreeDataChange()
   {
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


   image_list * tree_data::get_image_list() const
   {

      return m_pimagelist;

   }

   void tree_data::on_update(::user::impact * pSender,LPARAM lHint,::object* pHint)
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



