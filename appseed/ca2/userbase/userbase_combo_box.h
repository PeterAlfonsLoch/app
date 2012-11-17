#pragma once


namespace userbase
{


   class CLASS_DECL_ca2 combo_box :
      virtual public ::user::combo_box
   {
   public:


      combo_box(::ca::application * papp);
      virtual ~combo_box();


      virtual bool create(::user::interaction* puiParent, id id);

      //count get_count();
      //index get_cur_sel();
      //index set_cur_sel(index nSelect);
      LCID GetLocale();
      LCID SetLocale(LCID nNewLocale);
      index GetTopIndex();
      index SetTopIndex(index nIndex);
      index InitStorage(count nItems, UINT nBytes);
      void SetHorizontalExtent(UINT nExtent);
      UINT GetHorizontalExtent();
      int SetDroppedWidth(UINT nWidth);
      int GetDroppedWidth();

   #if defined(WINDOWSEX) && (WINVER >= 0x0500)
      bool GetComboBoxInfo(PCOMBOBOXINFO pcbi);
   #endif   // WINVER >= 0x0500

      // for edit control
      bool GetEditSel(strsize & nStartChar, strsize & nEndChar);
      bool LimitText(strsize nMaxChars);
      bool SetEditSel(strsize nStartChar, strsize nEndChar);

      // for combobox item
      dword_ptr GetItemData(index nIndex);
      index SetItemData(index nIndex, dword_ptr dwItemData);
      void * GetItemDataPtr(index nIndex);
      index SetItemDataPtr(index nIndex, void * pData);
      index GetLBText(index nIndex, LPTSTR lpszText);
      void GetLBText(index nIndex, string & rString);
      strsize GetLBTextLen(index nIndex);

      int SetItemHeight(index nIndex, UINT cyItemHeight);
      int GetItemHeight(index nIndex);
      index FindStringExact(index nIndexStart, const char * lpszFind);
      int SetExtendedUI(bool bExtended = TRUE);
      bool GetExtendedUI();
      void GetDroppedControlRect(LPRECT lprect);
      bool GetDroppedState();

   // Operations
      // for drop-down combo boxes
      void ShowDropDown(bool bShowIt = TRUE);

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
#ifdef WINDOWSEX
      virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
      virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
      virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
      virtual void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
#endif

      virtual bool OnChildNotify(UINT, WPARAM, LPARAM, LRESULT*);


   };


} // namespace userbase

