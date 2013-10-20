#pragma once


class image_list;


namespace data
{


   class tree_data;


   class CLASS_DECL_CORE tree :
      virtual public ::data::data_container
   {
   public:


      sp(tree_item)              m_pitem;
      tree_item_ptr_array        m_itemptraSelected;
      sp(tree_item)              m_pitemHover;


      tree(sp(base_application) papp);
      virtual ~tree();


      sp(tree_data) get_tree_data();


      sp(tree_item) allocate_branch_item(sp(::data::tree_data) pdata);
      sp(tree_item) allocate_item(sp(::data::tree_data) pdata);


      virtual void remove_all();



      virtual sp(tree_item) find(sp(tree_item_data) pitemdata, index i = 0);
      virtual bool contains(sp(tree_item_data) pitemdata);

      virtual bool contains(sp(tree_item) pitem);

      virtual void _001OnTreeDataChange();

      virtual bool      hover_tree_item(sp(tree_item) pitem);
      virtual bool      hover_tree_item_data(sp(tree_item_data) pitem, index i = 0);

      virtual ::count   add_tree_item_array_selection(tree_item_ptr_array & itemptra);
      virtual bool      add_tree_item_selection(sp(tree_item) pitem);
      virtual bool      add_tree_item_data_selection(sp(tree_item_data) pitem, index i = 0);

      virtual ::count   set_tree_item_array_selection(tree_item_ptr_array & itemptra);
      virtual bool      set_tree_item_selection(sp(tree_item) pitem);
      virtual bool      set_tree_item_data_selection(sp(tree_item_data) pitem, index i = 0);

      virtual ::count   remove_tree_item_array_selection(tree_item_ptr_array & itemptra);
      virtual bool      remove_tree_item_selection(sp(tree_item) pitem);
      virtual bool      remove_tree_item_data_selection(sp(tree_item_data) pitem, index i = 0);

      virtual ::count   remove_tree_item_array(tree_item_ptr_array & itemptra);
      virtual ::count   remove_tree_item(sp(tree_item) pitem);
      virtual ::count   remove_tree_item_data(sp(tree_item_data) pitem, index i = 0);


      virtual ::count   clear_selection();

      virtual bool   is_tree_item_selected(sp(tree_item) pitem);
      virtual bool   is_tree_item_data_selected(sp(tree_item_data) pitem);
      virtual bool   is_tree_item_hover(sp(tree_item) pitem);
      virtual bool   is_tree_item_data_hover(sp(tree_item_data) pitem);

      void sort(index ( * lpfnCompare )(sp(tree_item) &, sp(tree_item) &));

      virtual sp(tree_item) get_proper_item(index iIndex, index * piLevel);
      virtual index get_proper_item_index(sp(tree_item) pitemParam, index * piLevel);
      virtual ::count get_proper_item_count();



      virtual sp(image_list) get_image_list();

      virtual sp(tree_item) get_base_item();

      virtual sp(tree_item) insert_item_data(sp(::data::tree_data) ptreedata, sp(tree_item_data) pitemdataNew, ERelative erelativeNewItem, sp(tree_item) pitemRelative);
      virtual sp(tree_item) create_item(sp(::data::tree_data) ptreedata, sp(tree_item) pitemRelative, ERelative erelativeNewItem);
      virtual bool insert_item(sp(::data::tree_data) ptreedata, sp(tree_item) pitemNew, ERelative erelativeNewItem, sp(tree_item) pitemRelative);


   };


} // namespace core
