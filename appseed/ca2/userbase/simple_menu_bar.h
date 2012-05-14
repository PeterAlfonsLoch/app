#pragma once

class ::userbase::tool_bar_control;
class SimpleMenu;
class CMenuTrackingThreadV033;
class CMenuBarHookV033;

class CLASS_DECL_ca2 simple_menu_bar :
   public simple_toolbar
{
public:


   int                  m_iHover;
/* array_ptr_alloc < SimpleMenuBarButton , SimpleMenuBarButton &>
                        m_buttona;*/

   image_list *         m_pimagelist;
   image_list *         m_pimagelistDisabled;
   int_int_spreadset *  m_prel;

   bool                 m_bTracking;
   int                  m_iTracking;
   UINT                 m_uiResourceID;
   int                  m_iTopMenuCount;
   ::userbase::menu     m_menu;


   simple_menu_bar(::ca::application * papp);
   virtual ~simple_menu_bar();


   using ::simple_toolbar::create;
   BOOL create(::user::interaction* pParentWnd,
      DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP,
      UINT nID = __IDW_TOOLBAR);
   using ::simple_toolbar::CreateEx;
#ifdef WINDOWS
   BOOL CreateEx(::user::interaction* pParentWnd, DWORD dwCtrlStyle = TBSTYLE_FLAT,
      DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP,
      rect rcBorders = rect(0, 0, 0, 0),
      UINT nID = __IDW_TOOLBAR);
#else
   BOOL CreateEx(::user::interaction* pParentWnd, DWORD dwCtrlStyle = 0,
      DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP,
      rect rcBorders = rect(0, 0, 0, 0),
      UINT nID = __IDW_TOOLBAR);
#endif


   LRESULT CALLBACK MessageProc(
        int code,       // hook code
        WPARAM wParam,  // undefined
        LPARAM lParam   // address of structure with message data
        );

   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
   virtual void pre_translate_message(gen::signal_object * pobj);
   protected:
   virtual BOOL pre_create_window(CREATESTRUCT& cs);

   virtual int _001GetHoverItem();
   virtual void OnUpdateHover();
   void _001OnClick(int iItem);
   void _001OnDropDown(int iItem);
   //int _001GetHoverItem();
   //void _001Hover(point pt);
   //void _001Hover();
   //void _001DrawItem(::ca::graphics * pdc, int iItem);
   //int _001HitTest(const POINT * point);
   //bool _001CheckItem(int iItem, bool bCheck);
   //bool _001GetItemRect(int iItem, LPRECT lprect, EElement eelement);
   //virtual void _001OnDraw(::ca::graphics * pdc);
   bool ReloadMenuBar();
   virtual void OnUpdateCmdUI(userbase::frame_window* pTarget, BOOL bDisableIfNoHndler);
   void RemoveAllButtons();

   bool Initialize(
      image_list * pimagelist,
      image_list * pimagelistDisabled,
      int_int_spreadset * prel,
      ::ca::font * pfont);

   //size CalcLayout(DWORD dwMode, int nLength);

   //size CalcFixedLayout(BOOL bStretch, BOOL bHorz);

   //size CalcDynamicLayout(int nLength, DWORD dwMode);
   //static VMSRESULT CalcSize(::userbase::tool_bar_control & tbc, size & size);
   //static VMSRESULT CalcSize(CToolBarCtrl & tbc, size & size);
   VMSRESULT _TrackPopupMenu(point point);
   VMSRESULT _TrackPopupMenu(int iItem);
   bool LoadMenuBar(UINT nIDResource);
   void SetMenuID(UINT nIDResource);

   DECL_GEN_SIGNAL(_001OnMouseMove)
   DECL_GEN_SIGNAL(_001OnNcMouseMove)
   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnKeyDown)
   DECL_GEN_SIGNAL(_001OnDestroy)
   DECL_GEN_SIGNAL(_001OnMenuChar)
   DECL_GEN_SIGNAL(_001OnLButtonDown)
   DECL_GEN_SIGNAL(_001OnTimer)

   virtual int OnMessage(MPARAM mparam, NPARAM nparam, OPARAM oparam);

   DECL_GEN_SIGNAL(_001OnAppLanguage)

   virtual void install_message_handling(::gen::message::dispatch * pdispatch);


};


