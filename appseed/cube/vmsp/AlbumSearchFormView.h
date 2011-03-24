#pragma once


class AlbumSongList;

class AFX_EXT_CLASS AlbumSearchFormView :
   public form_view
{
public:
   ::ca::brush_sp       m_brushBackground;
   COLORREF             m_crBackground;
   COLORREF             m_crForeground;
   simple_button         m_buttonSelectAll;
   simple_button         m_buttonSelectNone;
   simple_button         m_buttonSearch;
   AlbumSongList *      m_plist;

   AlbumSearchFormView(::ca::application * papp);


   string GetSearchText();
   int GetSearchMask();

   virtual void OnInitialUpdate();
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   virtual void _001InitializeFormPreData();
   bool SetAlbumSongList(AlbumSongList * plist);
   VMSRESULT SearchNow();
   void FillSearchCombo(string strSearchText);
   void UpdateSearchEnable();
   virtual ~AlbumSearchFormView();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   afx_msg HBRUSH OnCtlColor(::ca::graphics * pgraphics, ::ca::window* pWnd, UINT nCtlColor);
   afx_msg void OnButtonSearch();
   afx_msg void OnButtonSelectall();
   afx_msg void OnButtonSelectnone();
   afx_msg void OnChangeEdit();
   afx_msg void OnEditchangeComboSearch();
   afx_msg void OnSelendokComboSearch();
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

