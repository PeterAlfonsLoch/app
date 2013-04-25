#pragma once


class image_list;


namespace ca
{


   class tree_item_ptr_array;
   class tree_data;
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
      RelativeReplace
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

   class CLASS_DECL_ca2 tree_item :
      public ::c::c
   {
   public:


      uint_ptr                      m_dwUser;
      uint_ptr                      m_dwMetaData;
      sp(tree_item)                 m_pparent;
      sp(tree_item)                 m_pchild;
      sp(tree_item)                 m_pnext;
      sp(tree_item)                 m_pprevious;
      uint32_t                      m_dwState;
      sp(tree_item_data)            m_pitemdata;
      sp(tree_data)                 m_ptreedata;
      sp(tree)                      m_ptree;


      tree_item();
      virtual ~tree_item();

      sp(tree_item) get_child_by_user_data(uint_ptr iUserData);
      sp(tree_item) find_next_by_user_data(uint_ptr iUserData);
      void get_children(::ca::tree_item_ptr_array &ptra);
      ::count get_children_count();
      ::count get_expandable_children_count();
      ::count get_proper_descendant_count();
      sp(tree_item) get_expandable_child(index iIndex);
      sp(tree_item) get_previous();
      sp(tree_item) get_next(bool bChild = true, bool bParent = true, index * pindexLevel = ::null());


      void sort_children(index ( * lpfnCompare )(sp(tree_item) &, sp(tree_item) &));

      static void swap_sibling(sp(tree_item) pitem1, sp(tree_item) pitem2);

      sp(tree_item) get_item(ETreeNavigation enavigation, index * piLevelOffset = ::null());
      sp(tree_item) get_item(ERelative erelative);

      virtual sp(tree_item) get_proper_item(index iIndex, index * piLevel);
      virtual index get_proper_item_index(sp(tree_item) pitem, index * piLevel);
      virtual ::count get_proper_item_count();

      virtual sp(tree) get_tree();
      
      virtual bool set_selection();
      virtual bool add_selection();
      virtual bool clear_selection();
      virtual bool remove_selection();
      virtual bool hover();
      virtual bool is_hover();
      virtual bool is_selected();
      virtual string get_text();
      virtual index get_image();
      virtual sp(image_list) get_image_list();


      ::count remove_tree_item();
      ::count remove_tree_item_descendants();


/*#undef new
      void * operator new(size_t i, const char * lpszFileName, int32_t iLine);
      void * operator new(size_t i);
#define new DEBUG_NEW
      void operator delete(void *, const char * lpszFileName, int32_t iLine);
      void operator delete(void *);*/
   };


   class CLASS_DECL_ca2 tree_item_ptr_array :
      public spa(tree_item)
   {
   public:
   };


} // namespace ca


