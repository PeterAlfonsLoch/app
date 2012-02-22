#pragma once


namespace userbase
{


   class CLASS_DECL_ca2 combo_box :
      virtual public ::user::combo_box
   {
   public:


      combo_box();
      virtual ~combo_box();


      virtual bool create(::user::interaction* puiParent, id id);

      count get_count();
      index get_cur_sel();
      index set_cur_sel(index nSelect);
      LCID GetLocale();
      LCID SetLocale(LCID nNewLocale);
      index GetTopIndex();
      index SetTopIndex(index nIndex);
      index InitStorage(count nItems, UINT nBytes);
      void SetHorizontalExtent(UINT nExtent);
      UINT GetHorizontalExtent();
      int SetDroppedWidth(UINT nWidth);
      int GetDroppedWidth();

   #if(WINVER >= 0x0500)
      BOOL GetComboBoxInfo(PCOMBOBOXINFO pcbi);
   #endif   // WINVER >= 0x0500

      // for edit control
      BOOL GetEditSel(strsize & nStartChar, strsize & nEndChar);
      BOOL LimitText(strsize nMaxChars);
      BOOL SetEditSel(strsize nStartChar, strsize nEndChar);

      // for combobox item
      DWORD_PTR GetItemData(index nIndex);
      index SetItemData(index nIndex, DWORD_PTR dwItemData);
      void * GetItemDataPtr(index nIndex);
      index SetItemDataPtr(index nIndex, void * pData);
      index GetLBText(index nIndex, LPTSTR lpszText);
      void GetLBText(index nIndex, string & rString);
      strsize GetLBTextLen(index nIndex);

      int SetItemHeight(index nIndex, UINT cyItemHeight);
      int GetItemHeight(index nIndex);
      index FindStringExact(index nIndexStart, const char * lpszFind);
      int SetExtendedUI(BOOL bExtended = TRUE);
      BOOL GetExtendedUI();
      void GetDroppedControlRect(LPRECT lprect);
      BOOL GetDroppedState();

   // Operations
      // for drop-down combo boxes
      void ShowDropDown(BOOL bShowIt = TRUE);

      // manipulating listbox items
      index AddString(const char * lpszString);
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
#ifdef WINDOWS
      virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
      virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
      virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
      virtual void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
#endif

      virtual BOOL OnChildNotify(UINT, WPARAM, LPARAM, LRESULT*);


   };


} // namespace userbase

