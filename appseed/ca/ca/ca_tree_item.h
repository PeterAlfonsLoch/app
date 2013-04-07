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

   class CLASS_DECL_ca tree_item
   {
   public:


      uint_ptr                   m_dwUser;
      uint_ptr                   m_dwMetaData;
      tree_item *                m_pparent;
      tree_item *                m_pchild;
      tree_item *                m_pnext;
      tree_item *                m_pprevious;
      uint32_t                   m_dwState;
      tree_item_data *           m_pitemdata;
      tree_data *                m_ptreedata;
      tree *                     m_ptree;


      tree_item();
      virtual ~tree_item();

      void delete_descendants();

      tree_item * get_child_by_user_data(uint_ptr iUserData);
      tree_item * find_next_by_user_data(uint_ptr iUserData);
      void get_children(::ca::tree_item_ptr_array &ptra);
      ::count get_children_count();
      ::count get_expandable_children_count();
      ::count get_proper_descendant_count();
      tree_item * get_expandable_child(index iIndex);
      tree_item * get_previous();
      tree_item * get_next(bool bChild = true, bool bParent = true, index * pindexLevel = ::null());


      void sort_children(int32_t ( * lpfnCompare )(tree_item *, tree_item *, ::ca::tree_data *), ::ca::tree_data * ptreedata);

      static void swap_sibling(tree_item * pitem1, tree_item * pitem2);

      tree_item * get_item(ETreeNavigation enavigation, index * piLevelOffset = ::null());
      tree_item * get_item(ERelative erelative);

      virtual tree_item * get_proper_item(index iIndex, index * piLevel);
      virtual index get_proper_item_index(tree_item * pitem, index * piLevel);
      virtual ::count get_proper_item_count();

      virtual tree * get_tree();
      
      virtual bool set_selection();
      virtual bool add_selection();
      virtual bool clear_selection();
      virtual bool remove_selection();
      virtual bool hover();
      virtual bool is_hover();
      virtual bool is_selected();
      virtual string get_text();
      virtual index get_image();
      virtual image_list * get_image_list();

/*#undef new
      void * operator new(size_t i, const char * lpszFileName, int32_t iLine);
      void * operator new(size_t i);
#define new DEBUG_NEW
      void operator delete(void *, const char * lpszFileName, int32_t iLine);
      void operator delete(void *);*/
   };


   class CLASS_DECL_ca tree_item_ptr_array :
      public comparable_array < tree_item * >
   {
   public:
   };


} // namespace ca


