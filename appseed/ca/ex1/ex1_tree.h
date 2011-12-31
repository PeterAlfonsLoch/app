#pragma once

class image_list;

namespace ex1
{

   class tree_data;

   class CLASS_DECL_ca tree :
      virtual public ::ca::data_container
   {
   protected:

      tree_item *             m_pitem;
      tree_item_ptr_array     m_itemptraSelected;
      tree_item *             m_pitemHover;


   public:

      tree(::ca::application * papp);
      virtual ~tree();


      virtual bool initialize();
      virtual bool finalize();


      tree_data * get_data();

      virtual tree_item * find(tree_item_data * pitemdata, index i = 0);
      virtual bool contains(tree_item_data * pitemdata);

      virtual bool contains(tree_item * pitem);

      virtual void _001OnTreeDataChange();

      virtual bool   hover(tree_item * pitem);
      virtual bool   hover(tree_item_data * pitem, index i = 0);

      virtual count  add_selection(tree_item_ptr_array & itemptra);
      virtual bool   add_selection(tree_item * pitem);
      virtual bool   add_selection(tree_item_data * pitem, index i = 0);

      virtual count  set_selection(tree_item_ptr_array & itemptra);
      virtual bool   set_selection(tree_item * pitem);
      virtual bool   set_selection(tree_item_data * pitem, index i = 0);

      virtual count  remove_selection(tree_item_ptr_array & itemptra);
      virtual bool   remove_selection(tree_item * pitem);
      virtual bool   remove_selection(tree_item_data * pitem, index i = 0);

      virtual count  clear_selection();

      virtual bool   is_selected(tree_item * pitem);
      virtual bool   is_selected(tree_item_data * pitem);
      virtual bool   is_hover(tree_item * pitem);
      virtual bool   is_hover(tree_item_data * pitem);

      void sort(int ( * lpfnCompare )(tree_item *, tree_item *, ::ex1::tree_data *));

      virtual tree_item * get_proper_item(index iIndex, index * piLevel);
      virtual index get_proper_item_index(tree_item * pitemParam, index * piLevel);
      virtual count get_proper_item_count();



      virtual image_list * get_image_list();

      virtual tree_item * get_base_item();

      virtual tree_item * insert_item(tree_item_data * pitemdataNew, ERelative erelativeNewItem, tree_item * pitemRelative);
      virtual tree_item * create_item(tree_item * pitemRelative, ERelative erelativeNewItem);
      virtual bool insert_item(tree_item * pitemNew, ERelative erelativeNewItem, tree_item * pitemRelative);

      tree_item * allocate_item();
      void delete_item(tree_item * pitem);

   };


} // namespace ex1
