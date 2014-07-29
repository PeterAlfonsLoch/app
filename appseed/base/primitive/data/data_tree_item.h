#pragma once


class image_list;


namespace data
{


   class tree_item_ptr_array;
   class tree;


   enum ERelative
   {
      RelativeParent,
      RelativeFirstChild,
      RelativeLastChild,
      RelativeFirstSibling,
      RelativePreviousSibling,
      RelativeNextSibling,
      RelativeLastSibling,
      RelativeReplace,
      RelativeMacroRecord
   };


   enum ETreeNavigation
   {
      TreeNavigationExpandedForward,
      TreeNavigationProperForward,
   };


   enum e_tree_item_state
   {
      tree_item_state_expandable = 1,
      tree_item_state_expanded   = 2,
      tree_item_state_selected   = 4,
   };

   class CLASS_DECL_BASE tree_item :
      public root
   {
   public:


      sp(tree)                      m_ptree;
      sp(tree_item)                 m_pparent;
      spa(tree_item)                m_children;
      sp(::data::item)              m_pitem;
      uint_ptr                      m_dwUser;
      uint32_t                      m_dwState;
      uint_ptr                      m_dwMetaData;


      tree_item();
      virtual ~tree_item();

      sp(tree_item) get_child_by_user_data(uint_ptr iUserData);
      sp(tree_item) find_next_by_user_data(uint_ptr iUserData);
      void get_children(::data::tree_item_ptr_array &ptra);
      ::count get_children_count();
      ::count get_expandable_children_count();
      ::count get_proper_descendant_count();
      sp(tree_item) get_expandable_child(index iIndex);
      sp(tree_item) get_previous(bool bParent = true);
      sp(tree_item) get_next(bool bChild = true, bool bParent = true, index * pindexLevel = NULL);
      

      sp(tree_item) previous();
      sp(tree_item) first_child();
      sp(tree_item) next();


      void sort_children(index ( * lpfnCompare )(sp(tree_item) *, sp(tree_item) *));

      sp(tree_item) get_item(ETreeNavigation enavigation, index * piLevelOffset = NULL);
      sp(tree_item) get_item(ERelative erelative);

      virtual sp(tree_item) get_proper_item(index iIndex, index * piLevel);
      virtual index get_proper_item_index(sp(tree_item) pitem, index * piLevel);
      virtual ::count get_proper_item_count();

      virtual sp(tree) get_tree();

      virtual string get_text() const;
      virtual index get_image() const;
      virtual sp(image_list) get_image_list() const;


      void SetParent(sp(tree_item) pparent);

      ::count remove_tree_item();
      ::count remove_tree_item_descendants();


      virtual bool is_expanded() const;
      virtual bool is_expandable() const;

      virtual void on_fill_children();

      virtual bool is_descendant(sp(tree_item) pitem);
      virtual bool is_ascendant(sp(tree_item) pitem);

   };


   class CLASS_DECL_BASE tree_item_ptr_array :
      public spa(tree_item)
   {
   public:
   };


} // namespace core


