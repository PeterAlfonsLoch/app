#pragma once


namespace mediaplaylist
{


   class CLASS_DECL_ca tree_base :
      virtual public ::user::tree,
      virtual public ::mediaplaylist::tree_data
   {
   public:
      

      tree_base(::ca::application * papp);
      virtual ~tree_base();


      virtual bool initialize();

      void update_list();

      void create_tree(xml::node * pnode, ex1::tree_item * pitemParent = NULL);

   };


} // namespace mediaplaylist


