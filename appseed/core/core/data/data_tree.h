#pragma once


class image_list;


namespace data
{


   class CLASS_DECL_CORE tree :
      virtual public ::data::data_container
   {
   public:


      sp(tree_item)                       m_proot;
      sp(image_list)                      m_pimagelist;



      tree(sp(base_application) papp);
      virtual ~tree();


      sp(tree_item) allocate_branch_item();


      virtual void remove_all();



      virtual sp(tree_item) find(item * pitem, index i = 0);
      virtual bool contains(item * pitem);

      virtual bool contains(tree_item * pitem);

      virtual void _001OnTreeDataChange();

      virtual void _001OnItemExpand(::data::tree_item * pitem);
      virtual void _001OnItemCollapse(::data::tree_item * pitem);

      virtual ::count   remove(tree_item_ptr_array & itemptra);
      virtual ::count   remove(tree_item * pitem);
      virtual ::count   remove(item * pitem, index i = 0);


      void sort(index ( * lpfnCompare )(sp(tree_item) * pitem, sp(tree_item) * pitem2));

      virtual sp(tree_item) get_proper_item(index iIndex, index * piLevel);
      virtual index get_proper_item_index(tree_item * pitemParam, index * piLevel);
      virtual ::count get_proper_item_count();



      virtual sp(tree_item) get_base_item();

      virtual sp(tree_item) insert_item(item * pitemdataNew, ERelative erelativeNewItem, tree_item * pitemRelative);
      virtual bool insert_item(tree_item * pitemNew, ERelative erelativeNewItem, tree_item * pitemRelative);

      sp(image_list) get_image_list();

   };


} // namespace core
