#pragma once


namespace ex1
{


   class CLASS_DECL_ca simple_tree_data :
      virtual public tree_data
   {
   public:


      simple_tree_data(::ca::application * papp);


      virtual bool initialize_data();
      virtual bool finalize_data();

      virtual tree_item_data * on_allocate_item();
      virtual void on_delete_item(tree_item_data * pitem);

   };



} // namespace ex1



