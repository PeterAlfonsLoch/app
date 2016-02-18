#pragma once


namespace user
{


   class CLASS_DECL_CORE tree_data:
      virtual public ::data::tree
   {
   public:


      ptr_array < ::user::tree >          m_treeptra; 
      ptr_array < ::user::tree >          m_treeptraBound; 
      sp(image_list)                      m_pimagelist;



      tree_data(::aura::application * papp);
      virtual ~tree_data();



      virtual ::count           get_data_bound_view_count() const;
      virtual ::user::impact *  get_data_bound_view(index iView);



      virtual void _001OnTreeDataChange();

      virtual void _001OnItemExpand(::data::tree_item * pitem,::action::context actioncontext);
      virtual void _001OnItemCollapse(::data::tree_item * pitem,::action::context actioncontext);
      virtual void _001OnOpenItem(::data::tree_item * pitem,::action::context actioncontext);
      virtual void _001OnItemContextMenu(::data::tree_item * pitem,::action::context actioncontext,::user::tree * ptree,point pt);

      image_list * get_image_list() const;

      virtual void _001ExpandItem(::data::tree_item * pitem,::action::context actioncontext,bool bExpand = true,bool bRedraw = true,bool bLayout = true);
      virtual void _001EnsureVisible(::data::tree_item * pitem);
      virtual void _001SelectItem(::data::tree_item * pitem);

      virtual void get_selection(::data::tree_item_ptr_array & itemptraSelected) const;
      virtual bool is_selected(const ::data::tree_item * pitem) const;
      virtual bool is_selected(const ::data::item * pitem) const;

      virtual ::count   selection_set(::data::tree_item_ptr_array & itemptra);
      virtual bool      selection_set(::data::tree_item * pitem,bool bIfNotInSelection = false,bool bIfParentInSelection = false);
      virtual bool      selection_set(::data::item * pitem,bool bIfNotInSelection = false,bool bIfParentInSelection = false);
      virtual bool      selection_set(index iIndex,::data::item * pitem,bool bIfNotInSelection = false,bool bIfParentInSelection = false);

      virtual void on_update(::user::impact * pSender,LPARAM lHint,::object* pHint);

      virtual void on_fill_children();

      virtual void tree_layout();

      virtual void on_merge_user_tree(::user::tree * pusertree);
      virtual void on_bind_user_tree(::user::tree * pusertree);


   };


} // namespace core
