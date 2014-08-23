#pragma once


namespace user
{


   class combo_list;


   class CLASS_DECL_CORE combo_box : 
      virtual public ::user::edit_plain_text
   {
   public:


      enum e_style
      {
         
         style_verisimple,
         style_simply,

      };


      index                      m_iSel;
      string                     m_strText;
      bool                       m_bCaseSensitiveMatch;

      sp(combo_list)             m_plist;

      sp(type)                   m_typeComboList;

      e_style                    m_estyle;

      bool                       m_bEdit;



      combo_box(sp(::aura::application) papp);
      virtual ~combo_box();


      virtual void install_message_handling(::message::dispatch * pdispatch);


      virtual void _001OnDraw(::draw2d::graphics * pdc);
      virtual void _001OnDrawVerisimple(::draw2d::graphics * pdc);
      virtual void _001OnDrawSimply(::draw2d::graphics * pdc);
      virtual void _001OnDrawStaticText(::draw2d::graphics * pdc);


      virtual void _001SetCurSel(index iSel, ::action::context actioncontext);
      virtual index _001GetCurSel();

      virtual void _001SetCurSelByData(uint_ptr ui, ::action::context actioncontext);

      virtual void _001GetText(string & str) const;
      virtual void _001SetText(const string & str, ::action::context actioncontext);


      virtual void _001GetListText(index iSel, string & str) const;
      virtual index _001FindListText(const string & str) const;
      virtual count _001GetListCount() const;


      virtual bool get_element_rect(LPRECT lprect, e_element eelement) const;
      virtual e_element hit_test(point pt) const;

      virtual void get_simple_drop_down_open_arrow_path(point_array & pointa) const;


      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnSetFocus);
      DECL_GEN_SIGNAL(_001OnMouseMove);

      virtual void _001ShowDropDown(bool bShow = true);
      virtual void _001ToggleDropDown();


      void defer_create_combo_list();



      virtual void layout();

      virtual void _001OnAfterChangeText(::action::context actioncontext);

      virtual void _001OnInitialUpdate(signal_details * pobj);



      virtual bool create_window(const RECT & rect, sp(::user::interaction) puiParent, id id);

      //::count get_count();
      //index get_cur_sel();
      //index set_cur_sel(index nSelect);
      LCID GetLocale();
      LCID SetLocale(LCID nNewLocale);
      index GetTopIndex();
      index SetTopIndex(index nIndex);
      index InitStorage(::count nItems, UINT nBytes);
      void SetHorizontalExtent(UINT nExtent);
      UINT GetHorizontalExtent();
      int32_t SetDroppedWidth(UINT nWidth);
      int32_t GetDroppedWidth();

   #if defined(WINDOWSEX) && (WINVER >= 0x0500)
      bool GetComboBoxInfo(PCOMBOBOXINFO pcbi);
   #endif   // WINVER >= 0x0500

      // for edit control
      bool GetEditSel(strsize & nStartChar, strsize & nEndChar);
      bool LimitText(strsize nMaxChars);
      bool SetEditSel(strsize nStartChar, strsize nEndChar);

      // for combobox item
      uint_ptr GetItemData(index nIndex);
      index SetItemData(index nIndex, uint_ptr dwItemData);
      void * GetItemDataPtr(index nIndex);
      index SetItemDataPtr(index nIndex, void * pData);
      index GetLBText(index nIndex, char * lpszText);
      void GetLBText(index nIndex, string & rString);
      strsize GetLBTextLen(index nIndex);

      int32_t SetItemHeight(index nIndex, UINT cyItemHeight);
      int32_t GetItemHeight(index nIndex);
      index FindStringExact(index nIndexStart, const char * lpszFind);
      int32_t SetExtendedUI(bool bExtended = TRUE);
      bool GetExtendedUI();
      void GetDroppedControlRect(LPRECT lprect);
      bool GetDroppedState();

   // Operations
      // for drop-down combo boxes
      void ShowDropDown(bool bShowIt = TRUE);

      // manipulating listbox items
      virtual index AddString(const char * lpszString, uint_ptr dwItemData = 0);
      index DeleteString(index nIndex);
      index InsertString(index nIndex, const char * lpszString);
      void ResetContent();
      index Dir(index attr, const char * lpszWildCard);

      // selection helpers
      index FindString(index nStartAfter, const char * lpszString);
      index SelectString(index nStartAfter, const char * lpszString);

      // Clipboard operations
      void clear();
      void copy();
      void Cut();
      void Paste();

   // Overridables (must override draw, measure and compare for owner draw)
#ifdef WINDOWSEX
      virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
      virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
      virtual int32_t CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
      virtual void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
#endif

      virtual bool OnChildNotify(::message::base * pbase);


   };


} //  namespace user



