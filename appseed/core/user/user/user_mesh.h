#pragma once


class image_list;


namespace database
{


   class selection;


} // namespace database


namespace user
{

   
   class mesh_cache_interface;
   class mesh_data;
   class mesh;
   class list_item;


   class CLASS_DECL_CORE mesh_item:
      virtual public ::object
   {
   public:

      list_item *    m_plistitem;
      mesh *         m_pmesh;
      index          m_iGroup;
      index          m_iItem;
      index          m_iDisplayItem;
      index          m_iColumn;
      index          m_iColumnKey;
      index          m_iOrder;
      index          m_iSubItem;
      index          m_iListItem;
      string         m_strText;
      COLORREF       m_cr;
      int32_t        m_iState;
      index          m_iImage;
      bool           m_bOk;

      index          m_iGroupTopIndex;
      index          m_iGroupCount;

      mesh_item(mesh * pmesh);

   };

   class CLASS_DECL_CORE draw_mesh_item:
      virtual public mesh_item,
      virtual public ::aura::draw_context
   {
   public:

      rect                 m_rectGroup;
      rect                 m_rectItem;
      rect                 m_rectSubItem;
      rect                 m_rectListItem;
      rect                 m_rectImage;
      rect                 m_rectText;
      rect *               m_prectClient;


      index                m_iGroupRectGroup;

      index                m_iItemRectItem;

      index                m_iWidthColumn;
      int32_t                  m_iColumnWidth;

      index                m_iSubItemRectItem;
      index                m_iSubItemRectSubItem;
      index                m_iSubItemRectOrder;
      index                m_iSubItemRectColumn;


      index                m_iListItemRectItem;
      index                m_iListItemRectSubItem;
      index                m_iListItemRectListItem;

      ::draw2d::font *         m_pfont;
      int32_t                  m_iDrawTextFlags;

      draw_mesh_item(mesh * pmesh);


      sp(image_list) get_image_list();
      bool draw_image();
      bool draw_group_image();
      void update_item_color();
      void set_text_color();
      void draw_text();

   };


   class CLASS_DECL_CORE mesh:
      virtual public ::user::control,
      public ::sort::compare_interface
   {
   public:

      enum EView
      {
         view_grid,
         view_list,
         view_report,
         view_icon,
      };

      enum ItemState
      {
         ItemStateHover = 1,
         ItemStateSelected = 2,
      };

      enum e_flag
      {
         flag_auto_arrange,
         flag_align_to_grid,
      };


      enum e_element
      {
         element_item,
         element_image,
         element_text,
         element_sub_item,
         element_group_image,
         element_group_item_text,
      };


      class range;
      //class mesh_column_array;

      class mesh_item_range
      {
      public:


         index      m_iLowerBound;
         index      m_iUpperBound;


         void set(index iLowerBoundListItem,index iUpperBoundListItem);



      };

      class CLASS_DECL_CORE sub_item_range
      {
      public:

         index                m_iLowerBound;
         index                m_iUpperBound;
         mesh_item_range      m_meshitemrange;


         sub_item_range();
         sub_item_range(const sub_item_range & subitemrange);

         void set(index iLowerBoundSubItem,index iUpperBoundSubItem,index iLowerBoundListItem,index iUpperBoundListItem);

         bool has_sub_item(index iSubItem) const;

         sub_item_range & operator =(const sub_item_range & subitemrange);

      };

      class CLASS_DECL_CORE item_range
      {
      public:


         index      m_iLowerBound;
         index      m_iUpperBound;
         sub_item_range  m_subitemrange;


         item_range();
         item_range(const item_range & itemrange);


         void offset(index iOffset);
         void set(index iLowerBoundItem,index iUpperBoundItem,index iLowerBoundSubItem,index iUpperBoundSubItem,index iLowerBoundListItem,index iUpperBoundListItem);
         void set_lower_bound(index iLowerBoundItem);
         void set_upper_bound(index iUpperBoundItem);
         bool has_sub_item(index iSubItem) const;
         index get_lower_bound() const;
         index get_upper_bound() const;
         item_range & operator =(const item_range & itemrange);
         bool has_item(index iItem) const;
         void get_item_indexes(index_array & ia) const;

      };

      class CLASS_DECL_CORE range
      {
      public:


         array < item_range > m_itemrangea;


         range(const range & range);
         range();


         range & operator = (const range & range);


         bool has_item(index iItem) const;
         bool has_sub_item(index iItem,index iSubItem) const;
         bool remove_item(index iItem);
         bool OnRemoveItem(index iItem);
         void clear();
         void add_item(const item_range & itemrange);
         item_range & ItemAt(index iIndex);
         ::count get_item_count() const;
         void get_item_indexes(index_array & ia) const;

      };


      class CLASS_DECL_CORE mesh_layout:
         virtual public ::file::serializable
      {
      public:
         mesh_layout();
         virtual ~mesh_layout();

         index_array   m_iaDisplayToStrict;
         int32_t            m_iWidth;

         virtual void write(::file::ostream & ostream) const;
         virtual void read(::file::istream & istream);
      };

      class CLASS_DECL_CORE icon_layout:
         virtual public ::file::serializable
      {
      public:
         icon_layout();
         virtual ~icon_layout();

         index_biunique   m_iaDisplayToStrict;
         int32_t            m_iWidth;

         virtual void write(::file::ostream & ostream) const;
         virtual void read(::file::istream & istream);
      };


      static const UINT MESSAGE_ENDCOLUMNHEADERDRAG;
      static const UINT MESSAGE_COLUMNHEADERTRACK;
      static const UINT MESSAGE_ENDCOLUMNHEADERTRACK;

      // Simple Filter Implementation
      // Base Mesh Side

      enum EFilterState
      {
         FilterStateNoFilter,
         FilterStateSetup,
         FilterStateFilter,
      };


      class CSortInfoItem
      {
      public:
         index    m_iSubItem;
         bool     m_bAscendent;
      };

      class CSortInfo
      {
      public:


         raw_array < CSortInfoItem > m_itema;


      };

      size                             m_sizeTotal;
      size                             m_sizePage;
      ::user::list *                   m_plist; // should be set to this ::user::list if this is a list

      int                              m_iDefaultColumnWidth;
      int_to_int                       m_mapColumnWidth;

      CSortInfo                        m_sortinfo;

      EFilterState                     m_efilterstate;
      index_biunique *                 m_piaFilterIcon;
      index_array *                    m_piaFilterMesh;

      bool                             m_bSelect;
      bool                             m_bHoverSelect;
      bool                             m_bMultiSelect;


      index                            m_iItemDrag;
      index                            m_iItemDrop;
      bool                             m_bDrag;


      // Sort
      bool                             m_bSort;
      bool                             m_bEmboss;


      bool                             m_bSortEnable;
      sp(mesh_cache_interface)         m_pcache;

      LOGFONTW                         m_logfont;
      visual::graphics_extension       m_dcextension;

      index                            m_iClick;

      index                            m_iItemFocus;

      bool                             m_bLockViewUpdate;
      int32_t                          m_iItemHeight;
      int32_t                          m_iItemWidth;

      index                            m_iItemHover;
      index                            m_iSubItemHover;

      index                            m_iLastItemSel;
      index                            m_iLastSubItemSel;
      index                            m_iItemEnter;
      index                            m_iSubItemEnter;
      index                            m_iMouseFlagEnter;
      index                            m_iItemSel;
      index                            m_iSubItemSel;




      range                            m_rangeSelection;
      range                            m_rangeHighlight;



      index                            m_iShiftFirstSelection;
      uint_ptr                         m_uiLButtonDownFlags;
      point                            m_ptLButtonDown;
      uint_ptr                         m_uiLButtonUpFlags;
      point                            m_ptLButtonUp;
      UINT                             m_uiRButtonUpFlags;
      point                            m_ptRButtonUp;
      cregexp                          m_reFilter1;
      int32_t                          m_iFilter1Step;
      bool                             m_bFilter1;

      bool                             m_bTopText;
      string                           m_strTopText;
      rect                             m_rectTopText;
      sp(mesh_data)                    m_pmeshdata;
      ::draw2d::font_sp                m_font;
      ::draw2d::font_sp                m_fontHover;
      ::draw2d::pen_sp                 m_penFocused;
      ::draw2d::pen_sp                 m_penHighlight;
      EView                            m_eview;
      flags < e_flag >                 m_flags;
      icon_layout                      m_iconlayout;
      mesh_layout                      m_meshlayout;
      mutex                            m_mutex;


      index                            m_iTopIndex;
      index                            m_iTopGroup;
      ::count                          m_nDisplayCount;
      ::count                          m_nItemCount;
      ::count                          m_nGroupCount;
      ::count                          m_nColumnCount;


      ::count                          m_nGridItemCount;
      ::count                          m_nGridColumnCount;

      sp(image_list)                   m_pilGroup;
      sp(image_list)                   m_pilGroupHover;
      bool                             m_bGroup;
      bool                             m_bLateralGroup;
      int32_t                          m_iLateralGroupWidth;
      int32_t                          m_iGroupMinHeight;
      index                            m_iGroupHover;

      draw_mesh_item *                 m_pdrawmeshitem;

      mutex                            m_mutexData;

      bool                             m_bAutoCreateMeshHeader;
      bool                             m_bAutoCreateMeshData;

      // This member is only valid if m_pmeshdata is simple_mesh_data object
      // (i.e. a simple_mesh_data class object or a simple_mesh_data based class object)
      // It should match the pointer of m_pmeshdata and yes, may kind
      // of memory waste and dangling appendix in some (or many cases).
      sp(simple_mesh_data)             m_psimplemeshdata;


      int                              m_iLeftMargin;
      int                              m_iTopMargin;

      mesh();
      virtual ~mesh();



      int32_t _001CalcItemWidth(::draw2d::graphics * pdc,index iItem,index iSubItem);
      int32_t _001CalcItemWidth(::draw2d::graphics * pdc,::draw2d::font * pfont,index iItem,index iSubItem);





      virtual void install_message_handling(::message::dispatch * pinterface);

      mesh_data * GetDataInterface();
      void UpdateHover();
      ::draw2d::font * _001GetFont();
      ::draw2d::font * _001GetFontHover();
      ::draw2d::pen * _001GetPenFocused();
      ::draw2d::pen * _001GetPenHighlight();
      virtual void PreSubClassWindow();
      virtual void _OnDraw(::draw2d::graphics * pdc);
      void _001MaximizeColumnWidth(index iColumn);
      int32_t _001CalcItemWidth(index iItem,index iSubItem);
      int32_t _001CalcColumnWidth(index iColumn);
      int32_t _001CalcMeshWidth();
      virtual void _001OnSort();


      virtual void _001OnBeforeDeleteRange(range & range);
      virtual void _001OnDeleteRange(range & range);
      virtual void _001DeleteRange(range & range);

      // Sort
      virtual index _001Compare(index iItem1,index iItem2);
      virtual index _002Compare(index iItem1,index iItem2,index iSubItem);
      virtual index _001DisplayCompare(index iDisplayItem1,index iDisplayItem2);


      virtual bool is_valid_display_item(index iDisplayItem);
      virtual bool is_valid_strict_item(index iStrictItem);


      class size get_item_size();

      void _001OnSort(index iSubItem);
      void _001OnMeshHeaderItemClick(index iHeaderItem);
      void _001OnMeshHeaderItemDblClk(index iHeaderItem);
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
      void _001Select(index iItem,index iSubItem);
      void _001Highlight(index iItem,bool bRedraw);
      void _001RemoveSelection();
      virtual bool _001OnRemoveItem(index iItem);
      bool _001RemoveItem(index iItem,bool bRedraw = true);
      void _001EnsureVisible(index iItem,bool bRedraw = true);
      void _001EnsureVisible(index iItem,range & rangeRedraw);
      void _001ItemScroll(index iItem,bool bRedraw = true);
      index _001ConfigIdToColumnKey(const ::database::id & key);
      index _001ConfigIdToSubItem(const ::database::id & key);
      virtual bool _001HasConfigId(const ::database::id & key);
      void _001GetSelection(::database::id & key,::database::selection & selection);

      //void _001SetSingleColumnMode(bool bHeaderCtrl);
//      bool _001InsertColumn(::user::mesh_column & column);
      virtual void SetDataInterface(mesh_data * pinterface);
      void CacheHint();
      void SetCacheInterface(mesh_cache_interface * pinterface);
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
      virtual id data_get_current_mesh_layout_id();

      virtual bool query_drop(index iDisplayDrop,index iDisplayDrag);
      virtual bool do_drop(index iDisplayDrop,index iDisplayDrag);
      virtual bool defer_drop(index iDisplayDrop,index iDisplayDrag);



      virtual void _001OnDraw(::draw2d::graphics *pdc);

      virtual void _001DrawGroups(draw_mesh_item * pdrawitem,index iGroupFirst,index iGroupLast,index iItemFirst,index iItemLast);

      virtual void _001DrawGroup(draw_mesh_item * pdrawitem);

      virtual void _001DrawItems(draw_mesh_item * pdrawitem,index iItemFirst,index iItemLast);

      virtual void _001DrawItem(draw_mesh_item * pdrawitem);

      virtual void _001DrawSubItem(draw_mesh_item * pdrawitem);

      virtual void _001GetItemImage(mesh_item * pitem);

      virtual void _001GetItemText(mesh_item * pitem);

      virtual void _001GetItemColor(mesh_item * pitem);

      virtual void _001SearchGetItemText(mesh_item * pitem);

      virtual ::count _001GetGroupItemCount(index iGroup);

      virtual ::count _001GetGroupMetaItemCount(index iGroup);

      virtual void _001GetGroupText(mesh_item * pitem);

      virtual void _001GetGroupImage(mesh_item * pitem);

      //virtual void _001InsertColumns();

      virtual ::count _001GetColumnCount();

      virtual void draw_framing(::draw2d::graphics * pgraphics);
//      virtual ::user::mesh_header * create_mesh_header();
      virtual ::user::mesh_data * create_mesh_data();

      void layout();

      virtual bool _001OnUpdateColumnCount(uint32_t dwFlags = 0);
      virtual bool _001OnUpdateItemCount(uint32_t dwFlags = 0);

      void on_change_view_size();


      virtual void _001OnInitialize();


      //      void _001AddColumn(mesh_column & pcolumn);

      virtual void _001GetGroupRect(draw_mesh_item * pitem);
      virtual void _001GetItemRect(draw_mesh_item * pitem);
      virtual void _001GetSubItemRect(draw_mesh_item * pitem);
      virtual void _001GetElementRect(draw_mesh_item * pitem,::user::mesh::e_element eelement);

      //virtual void _001OnColumnChange();

      virtual bool _001SetColumnWidth(index iColumn,int32_t iWidth);

      virtual void _001GetColumnWidth(draw_mesh_item * pdrawitem);

      virtual index _001MapSubItemToOrder(index iSubItem);

      virtual index _001MapOrderToSubItem(index iOrder);

      virtual index _001MapOrderToColumn(index iOrder);

      virtual index _001MapColumnToOrder(index iColumn);

      index _001MapSubItemToColumn(index iSubItem);

      index _001MapColumnToSubItem(index iColumn);

      //void _001DeleteColumn(index iColumn);


      virtual ::count _001GetItemCount();
      virtual ::count _001GetGroupCount();
      virtual bool _001HitTest_(point point,index &iItem,index &iSubItem,index &iListItem,::user::mesh::e_element &eelement);
      virtual bool _001HitTest_(point point,index &iItem,index &iSubItem);
      virtual bool _001HitTest_(POINT pt,index &iItemParam);


      virtual bool _001DisplayHitTest(point point,index &iItem,index &iSubItem,index &iListItem,::user::mesh::e_element &eelement);
      virtual bool _001DisplayHitTest(point point,index &iItem,index &iSubItem);
      virtual bool _001DisplayHitTest(POINT pt,index &iItemParam);

      virtual void _001OnAfterSort();


      //void LayoutHeaderCtrl();

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

      DECL_GEN_SIGNAL(_001OnUpdateMeshViewAutoArrange);

      DECL_GEN_SIGNAL(_001OnMeshViewAutoArrange);


      virtual void _001OnClick(uint_ptr uiFlags,point point);
      virtual void _001OnRightClick(uint_ptr uiFlags,point point);

      void _001GetSelection(range & selection);


      virtual bool _001IsEditing();


      ::count _001GetSelectedItemCount();

      id _001GetColumnTextId(index iColumn);

      //;;void HeaderCtrlLayout();

      //index HeaderCtrlMapColumnToOrder(index iColumn);

      //bool _001OnHeaderCtrlEndDrag(WPARAM wparam,LPARAM lparam);


      bool _001OnHeaderCtrlEndTrack(WPARAM wparam,LPARAM lparam);

      bool _001OnHeaderCtrlTrack(WPARAM wparam,LPARAM lparam);

      void _001ShowSubItem(index iSubItem,bool bShow = true);

      void DISaveOrder();

      void DILoadOrder();

      virtual void _001OnSelectionChange();

      bool _001IsItemVisible(index iItem);

      void _001ClearSelection();

      void _001SetSelection(const range &range);

      void _001AddSelection(const item_range & itemrange);

      index set_cur_sel(index iSel);

      index get_cur_sel();

      void set_cur_sel(const index_array & iaSel);

      void get_cur_sel(index_array & iaSel);

      void _001SetHighlightRange(range & range);

      void _001SetView(EView eview, bool bLayout = true);

      EView _001GetView();


      virtual int32_t get_wheel_scroll_delta();

      virtual void on_change_viewport_offset();

      bool keyboard_focus_is_focusable();

      DECL_GEN_SIGNAL(_001OnVScroll);
      DECL_GEN_SIGNAL(_001OnHScroll);

      virtual void data_update_visible_subitem();

      virtual void defer_create_mesh_data();

      virtual point get_viewport_offset();

      //virtual rect get_scroll_margin();

      virtual void GetClientRect(LPRECT lprect);
      virtual size get_page_size();
      virtual size get_total_size();

   };



} // namespace user




