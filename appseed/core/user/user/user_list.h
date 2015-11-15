#pragma once

class cregexp;

namespace database
{

   class selection;

} // namespace database

class window_redraw_interface;
class image_list;
class simple_list_data;

namespace visual
{
   class CBuffer;
}

namespace user
{


   class list_header;
   class scroll_bar;
   class list;
   class list_column_array;


   class CLASS_DECL_CORE list_column :
      virtual public object
   {
   public:


      index                            m_iKey;
      index                            m_iKeyVisible;
      index                            m_iKeyNonVisible;


      bool                             m_bVisible;
      index                            m_iNextGlobalOrderKey;
      ::user::list_column_array *      m_pcontainer;
      index                            m_iOrder;
      id                               m_uiText;
      UINT                             m_uiSmallBitmap;
      COLORREF                         m_crSmallMask;
      int32_t                              m_iSmallImageWidth;
      index                            m_iSubItem;
      sp(image_list)                     m_pil;
      sp(image_list)                     m_pilHover;
      ::visual::icon_int_map           m_mapIcon;
      size                             m_sizeIcon;
      bool                             m_bIcon;
      int32_t                              m_iWidth;
      bool                             m_bCustomDraw;

      // form list attributes
      bool                             m_bEditOnSecondClick;
      index                            m_iControl;
      ::database::id                   m_datakey;


      list_column();
      list_column(const list_column & pcolumn);
      virtual ~list_column();


      static index CompareOrderSectEndNonVisible(const sp(list_column) & columna, const sp(list_column) & columnb);
      static index CompareOrder(const sp(list_column) & columna, const sp(list_column) & columnb);

      static index CompareKey(const sp(list_column) & columna, const sp(list_column) & columnb);

      bool operator ==(const ::user::list_column & pcolumn) const;
      list_column & operator = (const list_column & column);

   };

   class CLASS_DECL_CORE list_column_array :
      public smart_pointer_array < ::user::list_column >
   {
   public:


      index               m_iFirstGlobalOrderKey;
      list         *       m_plist;


      list_column_array(::aura::application * papp);


      void Initialize(list * plist);
      index MapConfigIdToKey(const ::database::id & key);





      index add(list_column & column);

      void OnChange();

      void remove(index iColumn);


      ::count NonVisibleGetCount();
      index NonVisibleMapSubItemToColumn(index iSubItem);
      void ShowSubItem(index iSubItem, bool bShow);

      index _001GetSubItemKey(index iSubItem);

      list_column * _001GetBySubItem(index iSubItem);
      list_column * _001GetByKey(index iKey);
      list_column * _001GetByConfigId(const ::database::id & key);
      list_column * _001GetVisible(index iKeyVisible);
      list_column * _001GetNonVisible(index iKeyNonVisible);

      list_column * GlobalOrderGetPrevious(index iKey);
      list_column * GlobalOrderGetNext(index iKey);

      index VisibleMapSubItemToColumn(index iSubItem);
      ::count VisibleGetCount();

      ::count get_count();


      void remove_all();
      void GlobalToVisibleOrder();

      void VisibleToGlobalOrder(index iKeyA, index iKeyB);

      void VisibleToGlobalOrder();

      void DISaveOrder();

      void DILoadOrder();

      index VisibleGetOrderFromKey(index iKey);

      index OrderToKey(index iOrder);

   };


   class CLASS_DECL_CORE list_item :
      virtual public mesh_item
   {
   public:

      list *         m_plist;
      list_column *  m_pcolumn;


      list_item(list * plist);

   };

   class CLASS_DECL_CORE draw_list_item :
      virtual public draw_mesh_item,
      virtual public list_item
   {
   public:



      list_column *        m_pcolumnWidth;

      list_column *        m_pcolumnSubItemRect;


      draw_list_item(list * plist);


      sp(image_list) get_image_list();
      bool draw_image();
      bool draw_group_image();
      void update_item_color();
      void set_text_color();
      void draw_text();

   };


   class CLASS_DECL_CORE list :
      virtual public mesh
   {
   public:



      bool                             m_bAutoCreateListHeader;
      bool                             m_bHeaderCtrl;
      bool                             m_bSingleColumnMode;

      sp(list_header)                  m_plistheader;


      draw_list_item *                 m_pdrawlistitem;

      ::user::list_column_array        m_columna;

      sp(simple_list_data)             m_psimplelistdata;




      list();
      virtual ~list();



      int32_t _001CalcItemWidth(::draw2d::graphics * pdc, index iItem, index iSubItem);
      int32_t _001CalcItemWidth(::draw2d::graphics * pdc, ::draw2d::font * pfont, index iItem, index iSubItem);





      virtual void install_message_handling(::message::dispatch * pinterface);

      //mesh_data * GetDataInterface();
      void UpdateHover();
      ::draw2d::font * _001GetFont();
      ::draw2d::font * _001GetFontHover();
      ::draw2d::pen * _001GetPenFocused();
      ::draw2d::pen * _001GetPenHighlight();
      virtual void PreSubClassWindow();
      virtual void _OnDraw(::draw2d::graphics * pdc);
      void _001MaximizeColumnWidth(index iColumn);
      int32_t _001CalcItemWidth(index iItem, index iSubItem);
      int32_t _001CalcColumnWidth(index iColumn);
      int32_t _001CalcListWidth();
      virtual void _001OnSort();


      virtual void _001OnBeforeDeleteRange(range & range);
      virtual void _001OnDeleteRange(range & range);
      virtual void _001DeleteRange(range & range);

      // Sort
      virtual index _001Compare(index iItem1, index iItem2);
      virtual index _002Compare(index iItem1, index iItem2, index iSubItem);
      virtual index _001DisplayCompare(index iDisplayItem1, index iDisplayItem2);


      virtual bool is_valid_display_item(index iDisplayItem);
      virtual bool is_valid_strict_item(index iStrictItem);


      class size get_item_size();

      void _001OnSort(index iSubItem);
      void _001OnListHeaderItemClick(index iHeaderItem);
      void _001OnListHeaderItemDblClk(index iHeaderItem);
      void Filter1(string & str);
      bool Filter1Step();


      index _001CalcDisplayTopIndex();
      count _001CalcDisplayItemCount();
      int32_t _001GetGroupHeight(index iGroup);


      void FilterInclude(int_array & array);
      void FilterInclude(index iItem);
      void FilterExcludeAll();
      void FilterClose();
      void FilterApply();
      void FilterBegin();
      index StrictToDisplay(index iStrict);
      index DisplayToStrict(index iDisplay);
      void _001Select(index iItem, index iSubItem);
      void _001Highlight(index iItem, bool bRedraw);
      void _001RemoveSelection();
      virtual bool _001OnRemoveItem(index iItem);
      bool _001RemoveItem(index iItem, bool bRedraw = true);
      void _001EnsureVisible(index iItem, bool bRedraw = true);
      void _001EnsureVisible(index iItem, range & rangeRedraw);
      void _001ItemScroll(index iItem, bool bRedraw = true);
      index _001ConfigIdToColumnKey(const ::database::id & key);
      index _001ConfigIdToSubItem(const ::database::id & key);
      virtual bool _001HasConfigId(const ::database::id & key);
      void _001GetSelection(::database::id & key, ::database::selection & selection);

      void _001SetSingleColumnMode(bool bHeaderCtrl);
      bool _001InsertColumn(::user::list_column & column);
      void SetDataInterface(mesh_data * pinterface);
      void CacheHint();
      //void SetCacheInterface(mesh_cache_interface * pinterface);
      //void AddMessageHandling(::message::dispatch * pinterface);
      void _001ShowTopText(bool bShow = true);
      void _001LayoutTopText();
      void _001SetTopText(const unichar * lpcwsz);
      bool DIDDXHeaderLayout(bool bSave);
      virtual void DIOnSectionSet();


      virtual void data_get_DisplayToStrict();
      virtual void data_set_DisplayToStrict();
      virtual id data_get_current_sort_id();
      virtual id data_get_sort_id(EView eview);
      virtual id data_get_current_list_layout_id();

      virtual bool query_drop(index iDisplayDrop, index iDisplayDrag);
      virtual bool do_drop(index iDisplayDrop, index iDisplayDrag);
      virtual bool defer_drop(index iDisplayDrop, index iDisplayDrag);



      bool CreateHeaderCtrl();

      virtual void _001OnDraw(::draw2d::graphics *pdc);

      virtual void _001DrawGroups(draw_list_item * pdrawitem, index iGroupFirst, index iGroupLast, index iItemFirst, index iItemLast);

      virtual void _001DrawGroup(draw_list_item * pdrawitem);

      virtual void _001DrawItems(draw_list_item * pdrawitem, index iItemFirst, index iItemLast);

      virtual void _001DrawItem(draw_list_item * pdrawitem);

      virtual void _001DrawSubItem(draw_list_item * pdrawitem);
      
      //virtual void _001GetItemImage(list_item * pitem);

      //virtual void _001GetItemText(list_item * pitem);

      //virtual void _001GetItemColor(list_item * pitem);

      //virtual void _001SearchGetItemText(list_item * pitem);

      virtual ::count _001GetGroupItemCount(index iGroup);

      virtual ::count _001GetGroupMetaItemCount(index iGroup);

      //virtual void _001GetGroupText(list_item * pitem);

      //virtual void _001GetGroupImage(list_item * pitem);

      virtual void _001InsertColumns();

      ::count _001GetColumnCount();


      virtual ::user::list_header * create_list_header();
      virtual ::user::mesh_data * create_mesh_data();

      void layout();

      virtual bool _001OnUpdateItemCount(uint32_t dwFlags = 0);

      void on_change_view_size();


      virtual void _001OnInitialize();


      virtual void _001AddColumn(list_column & pcolumn);

      virtual void _001GetGroupRect(draw_list_item * pitem);
      virtual void _001GetItemRect(draw_list_item * pitem);
      virtual void _001GetSubItemRect(draw_list_item * pitem);
      virtual void _001GetElementRect(draw_list_item * pitem, ::user::mesh::e_element eelement);

      virtual void _001OnColumnChange();

      virtual bool _001SetColumnWidth(index iColumn, int32_t iWidth) override;
       
      virtual void _001GetColumnWidth(draw_list_item * pdrawitem);
      
      virtual index _001MapSubItemToOrder(index iSubItem) override;
      
      virtual index _001MapOrderToSubItem(index iOrder) override;
      
      virtual index _001MapOrderToColumn(index iOrder) override;
      
      virtual index _001MapColumnToOrder(index iColumn) override;

      index _001MapSubItemToColumn(index iSubItem);

      index _001MapColumnToSubItem(index iColumn);

      void _001DeleteColumn(index iColumn);


      virtual ::count _001GetItemCount();
      virtual ::count _001GetGroupCount();
      bool _001HitTest_(point point, index &iItem, index &iSubItem, index &iListItem, ::user::mesh::e_element &eelement);
      bool _001HitTest_(point point, index &iItem, index &iSubItem);
      bool _001HitTest_(POINT pt, index &iItemParam);


      bool _001DisplayHitTest(point point, index &iItem, index &iSubItem, index &iListItem, ::user::mesh::e_element &eelement);
      bool _001DisplayHitTest(point point, index &iItem, index &iSubItem);
      bool _001DisplayHitTest(POINT pt, index &iItemParam);

      virtual void _001OnAfterSort();


      void LayoutHeaderCtrl();

      void auto_arrange(bool bAutoArrange = true);

      bool get_auto_arrange();

      virtual void on_create_draw_item();

      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnLButtonDblClk);
      DECL_GEN_SIGNAL(_001OnRButtonDown);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnCreate);
      void _001OnTimer(::timer * ptimer);

      DECL_GEN_SIGNAL(_001OnUpdateListViewAutoArrange);

      DECL_GEN_SIGNAL(_001OnListViewAutoArrange);


      virtual void _001OnClick(uint_ptr uiFlags, point point);
      virtual void _001OnRightClick(uint_ptr uiFlags, point point);

      void _001GetSelection(range & selection);


      virtual bool _001IsEditing();


      ::count _001GetSelectedItemCount();

      id _001GetColumnTextId(index iColumn);

      void HeaderCtrlLayout();

      index HeaderCtrlMapColumnToOrder(index iColumn);

      bool _001OnHeaderCtrlEndDrag(WPARAM wparam, LPARAM lparam);


      bool _001OnHeaderCtrlEndTrack(WPARAM wparam, LPARAM lparam);

      bool _001OnHeaderCtrlTrack(WPARAM wparam, LPARAM lparam);

      void _001ShowSubItem(index iSubItem, bool bShow = true);
      void DISaveOrder();

      void DILoadOrder();


      virtual void _001OnSelectionChange();

      virtual void _001UpdateColumns();


      void _001RemoveAllColumns();


      //bool TwiHasTranslucency();

      void _001SetBackBuffer(visual::CBuffer *ptwb);

      void _001CreateImageList(list_column * pcolumn);

      bool _001IsItemVisible(index iItem);

      void _001ClearSelection();

      void _001SetSelection(const range &range);

      void _001AddSelection(const item_range & itemrange);

      index set_cur_sel(index iSel);
      index get_cur_sel();

      void set_cur_sel(const index_array & iaSel);
      void get_cur_sel(index_array & iaSel);

      void _001SetHighlightRange(range & range);

      //void _001SetView(EView eview, bool bLayout = true);

      EView _001GetView();


      virtual int32_t get_wheel_scroll_delta();

      virtual void on_change_viewport_offset();

      bool keyboard_focus_is_focusable();

      DECL_GEN_SIGNAL(_001OnVScroll);
      DECL_GEN_SIGNAL(_001OnHScroll);

      virtual void data_update_visible_subitem();

      virtual void defer_create_mesh_data();

      virtual void on_viewport_offset(::draw2d::graphics * pgraphics);

      virtual void _001OnClip(::draw2d::graphics * pgraphics);

   };


   typedef show < scroll < list > > list_view;

} // namespace user




