#pragma once


namespace data
{


   class CLASS_DECL_AXIS tree :
      virtual public ::data::data,
      virtual public ::signalizable
   {
   public:


      sp(tree_item)                       m_proot;
      mutex                               m_mutex;
      bool                                m_bFill;



      tree(sp(::axis::application) papp);
      virtual ~tree();


      sp(tree_item) allocate_branch_item();


      virtual void remove_all();



      virtual sp(tree_item) find(item * pitem, index * piIndex = NULL);
      virtual bool contains(item * pitem);

      virtual bool contains(tree_item * pitem);

      virtual void _001OnTreeDataChange();

      virtual void _001OnItemExpand(::data::tree_item * pitem, ::action::context actioncontext);
      virtual void _001OnItemCollapse(::data::tree_item * pitem, ::action::context actioncontext);
      virtual void _001OnOpenItem(::data::tree_item * pitem, ::action::context actioncontext);
      virtual void _001OnItemContextMenu(::data::tree_item * pitem, ::action::context actioncontext, ::user::tree * ptree, point pt);

      virtual ::count   remove(tree_item_ptr_array & itemptra);
      virtual ::count   remove(tree_item * pitem);
      virtual ::count   remove(item * pitem, index i = 0);


      void sort(index ( * lpfnCompare )(sp(tree_item) * pitem, sp(tree_item) * pitem2));

      virtual sp(tree_item) get_proper_item(index iIndex, index * piLevel, index * piCount = NULL);
      virtual index get_proper_item_index(tree_item * pitemParam, index * piLevel, index * piCount = NULL);
      virtual ::count get_proper_item_count();



      virtual sp(tree_item) get_base_item();

      virtual sp(tree_item) insert_item(item * pitemdataNew, ERelative erelativeNewItem, tree_item * pitemRelative);
      virtual bool insert_item(tree_item * pitemNew, ERelative erelativeNewItem, tree_item * pitemRelative);

      image_list * get_image_list() const;

      virtual void _001ExpandItem(tree_item * pitem, ::action::context actioncontext, bool bExpand = true, bool bRedraw = true, bool bLayout = true);
      virtual void _001EnsureVisible(::data::tree_item * pitem);
      virtual void _001SelectItem(::data::tree_item * pitem);

      virtual void get_selection(::data::tree_item_ptr_array & itemptraSelected) const;
      virtual bool is_selected(const ::data::tree_item * pitem) const;
      virtual bool is_selected(const ::data::item * pitem) const;

      virtual ::count   selection_set(::data::tree_item_ptr_array & itemptra);
      virtual bool      selection_set(::data::tree_item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      selection_set(::data::item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      selection_set(index iIndex, ::data::item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);

      virtual void on_update(sp(::user::impact) pSender, LPARAM lHint, ::object* pHint);


      virtual void on_fill_children();
      virtual void start_fill_children();

      static UINT c_cdecl thread_proc_fill_children(LPVOID lpParameter);

      virtual void tree_layout();

   };


} // namespace core
