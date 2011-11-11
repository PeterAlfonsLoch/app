#pragma once

class image_list;

namespace user
{

   class scroll_bar;

   class CLASS_DECL_ca tree_draw_item
   {
   public:
      ::ex1::tree_item *      m_pitem;
      ::ca::graphics *        m_pdc;
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


   class CLASS_DECL_ca tree :
      virtual public scroll_view,
      virtual public ::ex1::tree
   {
   public:

      enum ETimer
      {
         TimerClick,
         TimerHover,
      };

      ::visual::graphics_extension  m_dcextension;
      comparable_array < tree * >   m_treeptra;
      index                         m_dwFirstVisibleItem;
      index                         m_iItemCount;
      index                         m_iClick;
      UINT                          m_uiLButtonUpFlags;
      point                         m_ptLButtonUp;
      ::ex1::tree_item *            m_pitemFirstVisible;
      index                         m_iFirstVisibleItemLevel;
      index                         m_iFirstVisibleItemProperIndex;
      int                           m_iCurrentViewWidth;
      COLORREF                      m_crText;
      COLORREF                      m_crTextSelected;
      COLORREF                      m_crTextHighlight;
      COLORREF                      m_crTextSelectedHighlight;
      dword_array                   m_dwaItemState;
      image_list *                  m_pimagelist;
      index                         m_iImageCollapse;
      index                         m_iImageExpand;

      tree(::ca::application * papp);
      virtual ~tree();

      virtual void _001OnDrawBackground(::ca::graphics * pdc);
      virtual void _001OnDraw(::ca::graphics * pdc);
      virtual void _001DrawItem(tree_draw_item & data);

      void SetScrollSizes();

      void layout();

      void _001GetViewRect(rect64 * lprect);

      void _001OnTreeDataChange();
      ::ex1::tree_item * CalcFirstVisibleItem(index & iLevel, index & iProperIndex);
      virtual int _001CalcCurrentViewWidth();
      void _001SelectItem(::ex1::tree_item * pitem);
      count _001GetVisibleItemCount();
      void _001SetCollapseImage(HICON hicon);
      void _001SetExpandImage(HICON hicon);
      void UpdateHover();
      virtual void _001OnOpenItem(::ex1::tree_item * pitem);
      void _001ExpandItem(::ex1::tree_item * pitem, bool bExpand = true, bool bRedraw = true, bool bLayout = true);
      virtual void _001OnItemExpand(::ex1::tree_item * pitem);
      virtual void _001OnItemCollapse(::ex1::tree_item * pitem);
      virtual bool _001GetItemElementRect(LPRECT lprect, tree_draw_item & drawitem, ::user::e_tree_element eelement);
      virtual void install_message_handling(::user::win::message::dispatch * pdispatch);
      int _001GetItemHeight();
      virtual index _001GetIndentation();
      
      

      ::ex1::tree_item * _001HitTest(POINT pt, ::user::e_tree_element & eelement);
      void _001OnClick(UINT uiFlags, point point);


      image_list * get_image_list();

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

      virtual bool can_merge(::user::interaction * pui);
      virtual bool merge(::user::interaction * pui);

   };

} // namespace user
