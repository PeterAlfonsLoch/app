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

   class CLASS_DECL_AURA tree_item :
      virtual public object
   {
   public:

      enum e_flag
      {

         flag_previous_or_parent = 1,
         flag_previous = 2,
         flag_next = 4,
         flag_next_or_parent = 8,
         flag_child_or_next = 16,
         flag_child_next_or_parent = 32,
         flag_previoub = flag_previous_or_parent | flag_previous,
         flag_nexts = flag_next | flag_next_or_parent | flag_child_or_next| flag_child_next_or_parent,
      };

      spa(tree_item)                m_children;
      tree_item *                   m_pparent;
      index                         m_iIndexHint;
      tree *                        m_ptree;
      index                         m_iLevel;
      sp(::data::item)              m_pitem;
      uint_ptr                      m_dwUser;
      uint32_t                      m_dwState;
      uint_ptr                      m_dwMetaData;


      tree_item();
      virtual ~tree_item();


      virtual int64_t add_ref()
      {
         return ::object::add_ref();
      }
      virtual int64_t dec_ref()
      {
         return ::object::dec_ref();
      }

      virtual bool      remove_item_from_parent();

      tree_item * get_child_by_user_data(uint_ptr iUserData);
      tree_item * find_next_by_user_data(uint_ptr iUserData);
      void get_children(::data::tree_item_ptr_array &ptra);
      ::count get_children_count();
      tree_item * get_parent();
      ::count get_expandable_children_count();
      ::count get_proper_descendant_count();
      tree_item * get_expandable_child(index iIndex);

      bool insert(ERelative erelative, ::data::tree_item * pitemNew);

      index calc_level();
      index get_level() { return m_iLevel >= 0 ? m_iLevel : calc_level(); }
      index get_index();
      
      // index calc_index(index iHint);

      //tree_item * get_previous_or_parent(index * iLevelOffset = NULL);
      //tree_item * get_previous();

      //tree_item * get_next();
      //tree_item * get_next_or_parent(index * iLevelOffset = NULL);
      //tree_item * get_child_or_next(index * iLevelOffset = NULL);
      //tree_item * get_child_next_or_parent(index * iLevelOffset = NULL);

      //tree_item * calc_previous_or_parent(index * iLevelOffset = NULL);
      //tree_item * calc_previous();

      //tree_item * calc_next();
      //tree_item * calc_next_or_parent(index * iLevelOffset = NULL);
      //tree_item * calc_child_or_next(index * iLevelOffset = NULL);
      //tree_item * calc_child_next_or_parent(index * iLevelOffset = NULL);

      tree_item * get_previous_or_parent(index * iLevelOffset = NULL);
      tree_item * get_previous();

      tree_item * get_next();
      tree_item * get_next_or_parent(index * iLevelOffset = NULL);
      tree_item * get_child_or_next(index * iLevelOffset = NULL);
      tree_item * get_child_next_or_parent(index * iLevelOffset = NULL);

      //tree_item * get_previous(bool bParent = true)
      //{
      //   return bParent ? m_ppreviousParent : m_pprevious;
      //}
      //tree_item * get_next(bool bChild=true, bool bParent = true, index * pindexLevel = NULL)
      //{
      //   if (bChild)
      //   {
      //      if (bParent)
      //      {
      //         return m_pparent;
      //      }
      //   }
      //   return bChild ?bParent ? m_ppreviousParent : m_pprevious;
      //}
      tree_item * calc_previous(bool bParent = true);
      tree_item * calc_next(bool bChild, bool bParent = true, index * pindexLevel = NULL);
      

      tree_item * first_child();


      void sort_children(index ( * lpfnCompare )(const sp(tree_item) &, const sp(tree_item) &));

      tree_item * get_item(ETreeNavigation enavigation, index * piLevelOffset = NULL);
      tree_item * get_item(ERelative erelative);

      virtual tree_item * get_proper_item(index iIndex, index * piLevel);
      virtual index get_proper_item_index(tree_item * pitem, index * piLevel);
      virtual ::count get_proper_item_count();

      virtual tree * get_tree();

      virtual string get_text() const;
      virtual index get_image() const;
      virtual image_list * get_image_list() const;


      void SetParent(tree_item * pparent);

      ::count remove_tree_item();
      ::count remove_tree_item_descendants();


      virtual bool is_expanded() const;
      virtual bool is_expandable() const;

      virtual void on_fill_children();

      virtual bool is_descendant(tree_item * pitem);
      virtual bool is_ascendant(tree_item * pitem);

      //virtual void update_pointers();
      //virtual void update_previous_pointers(bool bUpdateNext);
      //virtual void update_next_pointers(bool bUpdatePrevious);

   };


   class CLASS_DECL_AURA tree_item_ptr_array :
      public spa(tree_item)
   {
   public:
   };


} // namespace core


