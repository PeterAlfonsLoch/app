#pragma once


namespace userbase
{


   class tool_bar_control;


} // namespace userbase


class SimpleMenu;
class CMenuTrackingThreadV033;
class CMenuBarHookV033;

class CLASS_DECL_ca2 simple_menu_bar :
   public simple_toolbar
{
public:


   int32_t                  m_iHover;
/* smart_pointer_array < SimpleMenuBarButton , SimpleMenuBarButton &>
                        m_buttona;*/

   image_list *         m_pimagelist;
   image_list *         m_pimagelistDisabled;
   int_int_spreadset *  m_prel;

   bool                 m_bTracking;
   int32_t                  m_iTracking;
   UINT                 m_uiResourceID;
   int32_t                  m_iTopMenuCount;
   ::userbase::menu     m_menu;


   simple_menu_bar(::ca::application * papp);
   virtual ~simple_menu_bar();


   using ::simple_toolbar::create;
   bool create(::user::interaction* pParentWnd,
      uint32_t dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP,
      UINT nID = __IDW_TOOLBAR);
   using ::simple_toolbar::CreateEx;
#ifdef WINDOWSEX
   bool CreateEx(::user::interaction* pParentWnd, uint32_t dwCtrlStyle = TBSTYLE_FLAT,
      uint32_t dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP,
      rect rcBorders = rect(0, 0, 0, 0),
      UINT nID = __IDW_TOOLBAR);
#else
   bool CreateEx(::user::interaction* pParentWnd, uint32_t dwCtrlStyle = 0,
      uint32_t dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP,
      rect rcBorders = rect(0, 0, 0, 0),
      UINT nID = __IDW_TOOLBAR);
#endif


   LRESULT CALLBACK MessageProc(
        int32_t code,       // hook code
        WPARAM wParam,  // undefined
        LPARAM lParam   // address of structure with message data
        );

   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
   virtual void pre_translate_message(::ca::signal_object * pobj);
   protected:
   virtual bool pre_create_window(CREATESTRUCT& cs);

   virtual int32_t _001GetHoverItem();
   virtual void OnUpdateHover();
   void _001OnClick(int32_t iItem);
   void _001OnDropDown(int32_t iItem);
   //int32_t _001GetHoverItem();
   //void _001Hover(point pt);
   //void _001Hover();
   //void _001DrawItem(::ca::graphics * pdc, int32_t iItem);
   //int32_t _001HitTest(const POINT * point);
   //bool _001CheckItem(int32_t iItem, bool bCheck);
   //bool _001GetItemRect(int32_t iItem, LPRECT lprect, EElement eelement);
   //virtual void _001OnDraw(::ca::graphics * pdc);
   bool ReloadMenuBar();
   virtual void OnUpdateCmdUI(::userbase::frame_window* pTarget, bool bDisableIfNoHndler);
   void RemoveAllButtons();

   bool Initialize(
      image_list * pimagelist,
      image_list * pimagelistDisabled,
      int_int_spreadset * prel,
      ::ca::font * pfont);

   //size CalcLayout(uint32_t dwMode, int32_t nLength);

   //size CalcFixedLayout(bool bStretch, bool bHorz);

   //size CalcDynamicLayout(int32_t nLength, uint32_t dwMode);
   //static VMSRESULT CalcSize(::userbase::tool_bar_control & tbc, size & size);
   //static VMSRESULT CalcSize(CToolBarCtrl & tbc, size & size);
   VMSRESULT _TrackPopupMenu(point point);
   VMSRESULT _TrackPopupMenu(int32_t iItem);
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

   virtual int32_t OnMessage(MPARAM mparam, NPARAM nparam, OPARAM oparam);

   DECL_GEN_SIGNAL(_001OnAppLanguage)

   virtual void install_message_handling(::ca::message::dispatch * pdispatch);


};


