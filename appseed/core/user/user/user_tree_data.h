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



      tree_data(sp(::aura::application) papp);
      virtual ~tree_data();


      sp(::data::tree_item) allocate_branch_item();


      virtual void remove_all();



      virtual sp(::data::tree_item) find(::data::item * pitem,index * piIndex = NULL);
      virtual bool contains(::data::item * pitem);

      virtual bool contains(::data::tree_item * pitem);

      virtual void _001OnTreeDataChange();

      virtual void _001OnItemExpand(::data::tree_item * pitem,::action::context actioncontext);
      virtual void _001OnItemCollapse(::data::tree_item * pitem,::action::context actioncontext);
      virtual void _001OnOpenItem(::data::tree_item * pitem,::action::context actioncontext);
      virtual void _001OnItemContextMenu(::data::tree_item * pitem,::action::context actioncontext,::user::tree * ptree,point pt);

      virtual ::count   remove(::data::tree_item_ptr_array & itemptra);
      virtual ::count   remove(::data::tree_item * pitem);
      virtual ::count   remove(::data::item * pitem,index i = 0);


      void sort(index(* lpfnCompare)(sp(::data::tree_item) * pitem,sp(::data::tree_item) * pitem2));

      virtual sp(::data::tree_item) get_proper_item(index iIndex,index * piLevel,index * piCount = NULL);
      virtual index get_proper_item_index(::data::tree_item * pitemParam,index * piLevel,index * piCount = NULL);
      virtual ::count get_proper_item_count();



      virtual sp(::data::tree_item) get_base_item();

      virtual sp(::data::tree_item) insert_item(::data::item * pitemdataNew,::data::ERelative erelativeNewItem,::data::tree_item * pitemRelative);
      virtual bool insert_item(::data::tree_item * pitemNew,::data::ERelative erelativeNewItem,::data::tree_item * pitemRelative);

      sp(image_list) get_image_list() const;

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
      //virtual void start_fill_children();

      //static UINT c_cdecl thread_proc_fill_children(LPVOID lpParameter);


      virtual void tree_layout();

      virtual void on_merge_user_tree(::user::tree * pusertree);
      virtual void on_bind_user_tree(::user::tree * pusertree);


   };


} // namespace core
