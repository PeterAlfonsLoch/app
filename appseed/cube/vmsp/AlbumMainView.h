#pragma once

class CSongBase;
class AlbumSongList;
class AlbumTree;
class CStrList;
class CDBSongSet;
class AlbumSearchFormView;
class AlbumHtmlView;
class AlbumFrameWnd;
class AlbumSongCheckList;
class simple_list_control;
class CTransparentWndBuffer;
class C017SimpleFolderListCtrl;

typedef struct tag_ContextMenuMessageData
{
    ::ca::window *      m_pMsgWnd;
    ::ca::window *      m_pWnd;
    point      m_point;
} CONTEXTMENUMESSAGEDATA, * LPCONTEXTMENUMESSAGEDATA;

//class AlbumMainView : public BaseDialog
class CLASS_DECL_CA2_CUBE AlbumMainView :
   public ::userbase::view//,
//   public _vmsdb::DBCentralListener
{
public:
    // // DECLARE_DYNCREATE(AlbumMainView)
    enum Timers
    {
        UpdateTimer = 1
    };
    enum UpdateEvents
    {
        UpdateEventTimer = 1,
        UpdateEventUpdated = 2
    };
    enum UpdateStates
    {
        UpdateStateTiming = 1,
        UpdateStateUpdating = 2
    };
    enum EView
    {
        ViewNoView = -1,
        ViewFullList,
      ViewExplorer,
        ViewSongExplorer,
        ViewSearchList,
        ViewNavigator,
        ViewDuplicatesList
    };
// Construction
public:
   void ReserveSelectedItems();
   //void ReserveSelectedItems(AlbumSongList & list);
   //AlbumMainView(::ca::window* pParent = NULL);   // standard constructor
   AlbumMainView(::ca::application * papp);
   virtual ~AlbumMainView();
   static const int cnListCount;
#ifdef _DEBUG
void assert_valid() const;

void dump(dump_context & dumpcontext) const;
#endif

// Attributes
public:

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pdispatch);
   image_list              m_SmallImageList;
   ::ca::bitmap                 m_SmallImageListBitmap;
   image_list              m_SmallImageListV001;
   ::ca::bitmap                 m_SmallImageListBitmapV001;

   //BaseSplitWnd         m_layoutNavigator;
   BaseSplitWnd         m_layoutFull;
//   C017ExExplorerWnd       m_explorer;
   BaseSplitWnd         m_layoutSongExplorer;
   BaseSplitWnd         _layoutSearch;
   BaseSplitWnd         m_layoutDuplicates;
   
protected:
//   C017SimpleFolderListCtrl *  m_pfolderlistctrl;
   AlbumSongList *           m_plistFull;
   AlbumSongList *            m_plistTree;
   AlbumSongList *            m_plistSearch;
   AlbumTree *            m_ptree;
   CDBSongSet *             m_psongsset;
//   CDataSource *             m_pdatasource;
   CStrList *               m_pstrlist;
    AlbumSearchFormView *      m_psearchformview;
    //AlbumHtmlView *         m_phtmlview;
    AlbumSongCheckList *      m_plistDuplicates;
   critical_section         m_cs;
   CTransparentWndBuffer *     m_ptwbListBackBuffer;
private:
    UINT                    m_uiUpdateTimer;
    UINT                    m_uiUpdateState;
    HANDLE                  m_hThreadContextMenu;
    DWORD                   m_dwThreadIdContextMenu;
protected:
    bool                    m_bFullListNeedUpdate;
   bool                    m_bExplorerNeedUpdate;
    bool                    m_bSongExplorerNeedUpdate;
    bool                    m_bSearchListNeedUpdate;
    bool                    m_bHtmlViewNeedUpdate;
    bool                    m_bDuplicatesListNeedUpdate;
    EView               m_eviewCurrent;
    DWORD                   m_dwUpdateTime;
    string                 m_strSearch;

//   primitive_array < CSongBase *> m_cacheArray;
//   ::collection::map <int, int, CSongBase *,CSongBase *> m_cacheMap;
//   int                              m_iCacheNextIndex;


public:
   void DoUpdateView(EView eview, bool bOnlyIfNeeded);
   virtual void TwiOnDraw(::ca::graphics * pdc);
   void UpdateStatus(AlbumSongList * plist);
   enum EView GetCurrentViewIndex();
   VMSRESULT Search(const string & strSearch);

   
    
   void ChangeView(EView iView);
   void OnAfterChangeView();
   void OnBeforeChangeView();
   UINT GetPopupMenuId(UINT nID);
   static DWORD WINAPI ThreadProcOnContextMenu(void *lpParameter);
   AlbumSongList * GetCurrentAlbumSongList();
   void StateMachineUpdate(UINT nIDEvent);
   
   void OnSongsInfoV001Updated();
   void OnSongsUpdated();
   void Update(int iView);
   void ShowStrList(const char * lpctstrField, HTREEITEM hParentItem, HTREEITEM hItem);
   void SetImageLists();
   HRESULT OpenSongsSet(const char * lpSQL, bool bFindInterface);
   HRESULT OpenSongsSetIndexedKey();

   VMSRESULT SearchNow();

   virtual void pre_translate_message(gen::signal_object * pobj);
   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 
   virtual void OnInitialUpdate();

   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
   virtual void OnDraw(::ca::graphics * pgraphics);
   //}}AFX_VIRTUAL

   virtual void layout();
   DECL_GEN_SIGNAL(_001OnDestroy)
   afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnButtonReserve();
   afx_msg void OnClose();
   DECL_GEN_SIGNAL(_001OnCreate)
   afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnItemdblclickStrlist(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnTimer(UINT nIDEvent);
   afx_msg void OnContextMenu(::ca::window* pWnd, point point);
   afx_msg void OnAlbumUpdate();
   afx_msg void OnUpdateAlbumUpdate(cmd_ui * pcmdui);
   afx_msg void OnAlbumReserveSong();
   afx_msg void OnUpdateAlbumReserveSong(cmd_ui * pcmdui);
   afx_msg void OnViewUpdate();
   afx_msg void OnUpdateViewUpdate(cmd_ui * pcmdui);
   afx_msg void OnAlbumFullbuild();
   afx_msg void OnAlbumPartialbuild();
   afx_msg void OnUpdateAlbumPartialbuild(cmd_ui * pcmdui);
   afx_msg void OnSetfocusFulllist(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnOdstatechangedList(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnUpdateAlbumFullbuild(cmd_ui * pcmdui);
   afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
   afx_msg BOOL OnEraseBkgnd(::ca::graphics * pgraphics);
    afx_msg void OnAlbumFullList();
    afx_msg void OnUpdateAlbumFullList(cmd_ui * pcmdui); 
    afx_msg void OnAlbumSearchList() ;
    afx_msg void OnUpdateAlbumSearchList(cmd_ui * pcmdui);
    afx_msg void OnAlbumExplorer();
    afx_msg void OnUpdateAlbumExplorer(cmd_ui * pcmdui);
    afx_msg void OnAlbumSongExplorer();
    afx_msg void OnUpdateAlbumSongExplorer(cmd_ui * pcmdui);
    afx_msg void OnAlbumNavigator(); 
    afx_msg void OnUpdateAlbumNavigator(cmd_ui * pcmdui); 
    afx_msg void OnAlbumDuplicatesList(); 
    afx_msg void OnUpdateAlbumDuplicatesList(cmd_ui * pcmdui);
   afx_msg void OnMsword9();
   afx_msg void OnUpdateMsword9(cmd_ui * pcmdui);
   afx_msg void OnViewNotepad();
   afx_msg void OnExploreUp();
   //}}AFX_MSG

    afx_msg LRESULT OnUserMessage(WPARAM wParam, LPARAM lParam);

   ()
};


