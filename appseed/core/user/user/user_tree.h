#pragma once


class image_list;


namespace user
{


   class scroll_bar;


   class CLASS_DECL_CORE tree_draw_item
   {
   public:
      sp(::data::tree_item)      m_pitem;
      ::draw2d::graphics *       m_pdc;
      index                      m_iItem;
      index                      m_iIndentation;
      index                      m_iItemHeight;
      rect                       m_rectClient;
      rect                       m_rect;
   };


   enum e_tree_element
   {
      tree_element_expand_box,
      tree_element_image,
      tree_element_text,
   };


   class CLASS_DECL_CORE tree :
      virtual public scroll_view
   {
   public:


      enum ETimer
      {

         TimerClick,
         TimerHover,

      };


      spa(::data::tree)             m_treeptra;
      spa(::data::tree)             m_treeptraBound;
      ::data::tree_item_ptr_array   m_itemptraSelected;
      sp(::data::tree_item)         m_pitemHover;

      ::visual::graphics_extension  m_dcextension;
      index                         m_dwFirstVisibleItem;
      index                         m_iItemCount;
      index                         m_iClick;
      UINT                          m_uiLButtonUpFlags;
      point                         m_ptLButtonUp;
      sp(::data::tree_item)         m_pitemFirstVisible;
      index                         m_iFirstVisibleItemLevel;
      index                         m_iFirstVisibleItemProperIndex;
      int32_t                       m_iCurrentViewWidth;
      //COLORREF                      m_crTextSelected;
      //COLORREF                      m_crTextHighlight;
      //COLORREF                      m_crTextSelectedHighlight;
      uint_array                  m_dwaItemState;
      sp(image_list)                m_pimagelist;
      index                         m_iImageCollapse;
      index                         m_iImageExpand;
      int32_t                       m_iItemHeight;



      bool                          m_bHoverStart;
      DWORD                         m_dwHoverStart;
      DWORD                         m_dwHoverEnd;
      BYTE                          m_uchHoverAlpha;
      BYTE                          m_uchHoverAlphaInit;




      tree(sp(::base::application) papp);
      virtual ~tree();

      virtual void _001OnDrawBackground(::draw2d::graphics * pdc);
      virtual void _001OnDraw(::draw2d::graphics * pdc);
      virtual void _001DrawItem(tree_draw_item & data);

      void layout();

      virtual sp(::data::tree) find_tree(::data::tree_item * pitem) const;
      virtual sp(::data::tree_item) find(::data::item * pitem, index * piIndex = NULL);
      virtual bool contains(::data::item * pitem);
      virtual bool contains(::data::tree_item * pitem);


      void _001GetViewRect(LPRECT lprect);

      void _001OnTreeDataChange();
      sp(::data::tree_item) CalcFirstVisibleItem(index & iLevel, index & iProperIndex);
      virtual int32_t _001CalcCurrentViewWidth();
      void _001SelectItem(::data::tree_item * pitem);
      count _001GetVisibleItemCount();
      void _001SetCollapseImage(const char * pszMatter);
      void _001SetExpandImage(const char * pszMatter);
      void UpdateHover();
      virtual void _001OnOpenItem(::data::tree_item * pitem, ::action::context actioncontext);
      virtual void _001OnItemContextMenu(::data::tree_item * pitem, ::action::context actioncontext, ::user::tree * ptree, point pt);
      void _001ExpandItem(::data::tree_item * pitem, ::action::context actioncontext, bool bExpand = true, bool bRedraw = true, bool bLayout = true);
      virtual void _001OnItemExpand(::data::tree_item * pitem, ::action::context actioncontext);
      virtual void _001OnItemCollapse(::data::tree_item * pitem, ::action::context actioncontext);
      virtual bool _001GetItemElementRect(LPRECT lprect, tree_draw_item & drawitem, ::user::e_tree_element eelement);
      virtual void install_message_handling(::message::dispatch * pdispatch);
      int32_t _001GetItemHeight();
      virtual index _001GetIndentation();

      sp(::data::tree_item) _001HitTest(POINT pt, ::user::e_tree_element & eelement);
      
      void _001OnClick(uint_ptr uiFlags, point point);

      void _001OnRightClick(uint_ptr uiFlags, point point);

      virtual void perform_click();

      virtual void perform_right_click(uint_ptr uiFlags, point pt);

      virtual int32_t get_wheel_scroll_delta();

      virtual void _001OnUpdateScrollPosition();

      sp(image_list) get_image_list();

      // Overrides
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnLButtonDblClk);
      DECL_GEN_SIGNAL(_001OnRButtonDown);
      DECL_GEN_SIGNAL(_001OnRButtonUp);
      DECL_GEN_SIGNAL(_001OnTimer);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnVScroll);
      DECL_GEN_SIGNAL(_001OnHScroll);


      virtual bool      hover(::data::tree_item * pitem);
      virtual bool      hover(::data::item * pitem, index i = 0);

      virtual bool      is_hover(const ::data::tree_item * pitem) const;
      virtual bool      is_hover(const ::data::item * pitem) const;


      virtual ::count   clear_selection();




      virtual bool      is_selected(const ::data::tree_item * pitem) const;
      virtual bool      is_selected(const ::data::item * pitem) const;

      virtual ::count   selection_add(::data::tree_item_ptr_array & itemptra);
      virtual bool      selection_add(::data::tree_item * pitem);
      virtual bool      selection_add(::data::item * pitem, index i = 0);

      virtual ::count   selection_set(::data::tree_item_ptr_array & itemptra);
      virtual bool      selection_set(::data::tree_item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      selection_set(::data::item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      selection_set(index iIndex, ::data::item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);

      virtual ::count   selection_remove(::data::tree_item_ptr_array & itemptra);
      virtual bool      selection_remove(::data::tree_item * pitem);
      virtual bool      selection_remove(::data::item * pitem, index i = 0);


      virtual bool      can_merge(const ::data::tree * ptree) const;
      virtual bool      merge(::data::tree * ptree, bool bBind);

      virtual sp(::data::tree_item) get_proper_item(index iIndex, index * piLevel, index * piCount = NULL);
      virtual index     get_proper_item_index(::data::tree_item *pitemParam, index * piLevel);
      virtual index     get_proper_item_count();

      virtual void      _001EnsureVisible(::data::tree_item * pitem);

      virtual void on_update(sp(::user::impact) pSender, LPARAM lHint, ::object* pHint);

   };


} // namespace user


#pragma once

namespace user
{

   class CLASS_DECL_CORE tree_window :
      virtual public ::user::tree
   {
   public:
      tree_window(sp(::base::application) papp);
      virtual ~tree_window();

      virtual void install_message_handling(::message::dispatch * pinterface);
   };

} // namespace user
