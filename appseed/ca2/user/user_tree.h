#pragma once


class image_list;


namespace user
{


   class scroll_bar;


   class CLASS_DECL_ca2 tree_draw_item
   {
   public:
      sp(::ca2::tree_item)      m_pitem;
      ::ca2::graphics *        m_pdc;
      index                   m_iItem;
      index                   m_iIndentation;
      index                   m_iItemHeight;
      rect                    m_rectClient;
      rect                    m_rect;
   };


   enum e_tree_element
   {
      tree_element_expand_box,
      tree_element_image,
      tree_element_text,
   };


   class CLASS_DECL_ca2 tree :
      virtual public scroll_view,
      public ::ca2::tree
   {
   public:

      enum ETimer
      {
         TimerClick,
         TimerHover,
      };

      ::visual::graphics_extension  m_dcextension;
      comparable_array < sp(tree) >   m_treeptra;
      index                         m_dwFirstVisibleItem;
      index                         m_iItemCount;
      index                         m_iClick;
      UINT                          m_uiLButtonUpFlags;
      point                         m_ptLButtonUp;
      sp(::ca2::tree_item)             m_pitemFirstVisible;
      index                         m_iFirstVisibleItemLevel;
      index                         m_iFirstVisibleItemProperIndex;
      int32_t                       m_iCurrentViewWidth;
      COLORREF                      m_crText;
      COLORREF                      m_crTextSelected;
      COLORREF                      m_crTextHighlight;
      COLORREF                      m_crTextSelectedHighlight;
      uint32_array                  m_dwaItemState;
      sp(image_list)                  m_pimagelist;
      index                         m_iImageCollapse;
      index                         m_iImageExpand;
      int32_t                       m_iItemHeight;



      bool                          m_bHoverStart;
      DWORD                         m_dwHoverStart;
      DWORD                         m_dwHoverEnd;
      BYTE                          m_uchHoverAlpha;
      BYTE                          m_uchHoverAlphaInit;
      

      tree(sp(::ca2::application) papp);
      virtual ~tree();

      virtual void _001OnDrawBackground(::ca2::graphics * pdc);
      virtual void _001OnDraw(::ca2::graphics * pdc);
      virtual void _001DrawItem(tree_draw_item & data);

      void layout();

      void _001GetViewRect(LPRECT lprect);

      void _001OnTreeDataChange();
      sp(::ca2::tree_item) CalcFirstVisibleItem(index & iLevel, index & iProperIndex);
      virtual int32_t _001CalcCurrentViewWidth();
      void _001SelectItem(sp(::ca2::tree_item) pitem);
      count _001GetVisibleItemCount();
      void _001SetCollapseImage(const char * pszMatter);
      void _001SetExpandImage(const char * pszMatter);
      void UpdateHover();
      virtual void _001OnOpenItem(sp(::ca2::tree_item) pitem);
      void _001ExpandItem(sp(::ca2::tree_item) pitem, bool bExpand = true, bool bRedraw = true, bool bLayout = true);
      virtual void _001OnItemExpand(sp(::ca2::tree_item) pitem);
      virtual void _001OnItemCollapse(sp(::ca2::tree_item) pitem);
      virtual bool _001GetItemElementRect(LPRECT lprect, tree_draw_item & drawitem, ::user::e_tree_element eelement);
      virtual void install_message_handling(::ca2::message::dispatch * pdispatch);
      int32_t _001GetItemHeight();
      virtual index _001GetIndentation();
      
      

      sp(::ca2::tree_item) _001HitTest(POINT pt, ::user::e_tree_element & eelement);
      void _001OnClick(UINT uiFlags, point point);


      virtual void perform_click();


      virtual int32_t get_wheel_scroll_delta();

      virtual void _001OnUpdateScrollPosition();


      sp(image_list) get_image_list();

      virtual COLORREF get_background_color();

      // Overrides
      DECL_GEN_SIGNAL(_001OnMouseMove)
      DECL_GEN_SIGNAL(_001OnMouseLeave)
      DECL_GEN_SIGNAL(_001OnLButtonDown)
      DECL_GEN_SIGNAL(_001OnLButtonUp)
      DECL_GEN_SIGNAL(_001OnLButtonDblClk)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnVScroll)
      DECL_GEN_SIGNAL(_001OnHScroll)

      virtual bool can_merge(sp(::user::interaction) pui);
      virtual bool merge(sp(::user::interaction) pui);


   };


} // namespace user


#pragma once

namespace user
{

   class CLASS_DECL_ca2 tree_window :
      virtual public ::user::tree
   {
   public:
      tree_window(sp(::ca2::application) papp);
      virtual ~tree_window();

      virtual void install_message_handling(::ca2::message::dispatch * pinterface);
   };

} // namespace user