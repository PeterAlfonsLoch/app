#pragma once


#include "user_interaction.h"


namespace user
{

   class frame_window;
   class control_bar;


} // namespace user


class BaseDockBar;
class BaseDockContext;
class BaseDockState;

#define CBRS_DRAGMOVE            0x01000000L
/*#undef CBRS_ALL
#define CBRS_ALL            0x0140ffffL*/





// Standard control bars (IDW = interaction_impl ID)
#define __IDW_CONTROLBAR_FIRST        0xE800
#define __IDW_CONTROLBAR_LAST         0xE8FF

#define __IDW_TOOLBAR                 0xE800  // main Toolbar for interaction_impl
//#define "status_bar"              0xE801  // Status bar interaction_impl
#define __IDW_PREVIEW_BAR             0xE802  // PrintPreview Dialog Bar
#define __IDW_RESIZE_BAR              0xE803  // OLE in-place resize bar
#define __IDW_REBAR                   0xE804  // COMCTL32 "rebar" Bar
#define __IDW_DIALOGBAR               0xE805  // dialogBar

// Note: If your application supports docking toolbars, you should
//  not use the following IDs for your own toolbars.  The IDs chosen
//  are at the top of the first 32 such that the bars will be hidden
//  while in print preview mode, and are not likely to conflict with
//  IDs your application may have used succesfully in the past.

#define __IDW_DOCKBAR_TOP             0xE81B
#define __IDW_DOCKBAR_LEFT            0xE81C
#define __IDW_DOCKBAR_RIGHT           0xE81D
#define __IDW_DOCKBAR_BOTTOM          0xE81E
#define __IDW_DOCKBAR_FLOAT           0xE81F

// Macro for mapping standard control bars to bitmask (limit of 32)
#define __CONTROLBAR_MASK(nIDC)   (1L << (nIDC - __IDW_CONTROLBAR_FIRST))



// layout Modes for CalcDynamicLayout
#define LM_STRETCH  0x01    // same meaning as bStretch in CalcFixedLayout.  If set, ignores nLength
// and returns dimensions based on LM_HORZ state, otherwise LM_HORZ is used
// to determine if nLength is the desired horizontal or vertical length
// and dimensions are returned based on nLength
#define LM_HORZ     0x02    // same as bHorz in CalcFixedLayout
#define LM_MRUWIDTH 0x04    // Most Recently Used Dynamic width
#define LM_HORZDOCK 0x08    // Horizontal Docked Dimensions
#define LM_VERTDOCK 0x10    // Vertical Docked Dimensions
#define LM_LENGTHY  0x20    // set if nLength is a height instead of a width
#define LM_COMMIT   0x40    // Remember MRUWidth


/////////////////////////////////////////////////////////////////////////////
// BaseControlBarInfo - used for docking serialization

class BaseControlBarInfo
{
public:
   // Implementation
   BaseControlBarInfo();

   // Attributes
   UINT m_nBarID;      // ID of this bar
   bool m_bVisible;    // visibility of this bar
   bool m_bFloating;   // whether floating or not
   bool m_bHorz;       // orientation of floating dockbar
   bool m_bDockBar;    // TRUE if a dockbar
   point m_pointPos;  // topleft point of interaction_impl

   UINT m_nMRUWidth;   // MRUWidth for Dynamic Toolbars
   bool m_bDocking;    // TRUE if this bar has a DockContext
   UINT m_uMRUDockID;  // most recent docked dockbar
   rect m_rectMRUDockPos; // most recent docked position
   uint32_t m_dwMRUFloatStyle; // most recent floating orientation
   point m_ptMRUFloatPos; // most recent floating position

   primitive_array < void * > m_arrBarID;   // bar IDs for bars contained within this one
   ::user::control_bar * m_pBar;    // bar which this refers to (transient)

   //   void Serialize(CArchive& ar, BaseDockState* pDockState);
   bool LoadState(const char * lpszProfileName, int32_t nIndex, BaseDockState* pDockState);
   bool SaveState(const char * lpszProfileName, int32_t nIndex);
};

namespace user
{

   
   class CLASS_DECL_BASE control_bar :
      virtual public ::user::interaction
   {
   public:

      
      // support for delayed hide/show
      enum StateFlags
      {
         
         delayHide = 1, 
         delayShow = 2, 
         tempHide = 4, 
         statusSet = 8
            
      };

      
      // info about bar (for status bar and toolbar)
      int32_t m_cxLeftBorder, m_cxRightBorder;
      int32_t m_cyTopBorder, m_cyBottomBorder;
      int32_t m_cxDefaultGap;         // default gap value
      UINT m_nMRUWidth;   // For dynamic resizing.
      bool  m_bDockTrack;

      // array of elements
      //int32_t m_nCount;
      //void * m_pData;        // m_nCount elements - type depends on derived class

      UINT m_nStateFlags;

      // support for docking
      uint32_t m_dwStyle;    // creation style (used for layout)
      uint32_t m_dwDockStyle;// indicates how bar can be docked
      sp(::user::frame_window) m_pDockSite; // current dock site, if dockable
      BaseDockBar* m_pDockBar;   // current dock bar, if dockable
      BaseDockContext* m_pDockContext;   // used during dragging
      uint32_t m_dwCtrlStyle;

      
      
      control_bar();
      virtual ~control_bar();

      // for styles specific to ::user::control_bar
      uint32_t GetBarStyle();
      void SetBarStyle(uint32_t dwStyle);

      bool m_bAutoDelete;

      // getting and setting border space
      void SetBorders(const RECT & rect);
      void SetBorders(int32_t cxLeft = 0, int32_t cyTop = 0, int32_t cxRight = 0, int32_t cyBottom = 0);
      rect GetBorders();

      sp(::user::frame_window) GetDockingFrame();
      bool IsFloating();
      virtual size CalcFixedLayout(bool bStretch, bool bHorz);
      virtual size CalcDynamicLayout(int32_t nLength, uint32_t nMode);

      // Operations
      void EnableDocking(uint32_t dwDockStyle);

      // Overridables
      virtual void OnUpdateCmdUI(sp(::user::frame_window) pTarget, bool bDisableIfNoHndler) = 0;

      virtual void _001OnDraw(::draw2d::graphics * pdc);
      
      using ::user::interaction::message_handler;
      virtual void message_handler(signal_details * pobj);
#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif
      virtual void DelayShow(bool bShow);
      virtual bool IsVisible();
      virtual uint32_t RecalcDelayShow(__SIZEPARENTPARAMS* lpLayout);

      virtual bool IsDockBar();
      virtual bool DestroyWindow();
      virtual void OnBarStyleChange(uint32_t dwOldStyle, uint32_t dwNewStyle);


      virtual void pre_translate_message(signal_details * pobj);
      virtual bool pre_create_window(::user::create_struct& cs);
      virtual void PostNcDestroy();

      virtual void DoPaint(::draw2d::graphics * pgraphics);
      void DrawBorders(::draw2d::graphics * pgraphics, rect& rect);
      void DrawGripper(::draw2d::graphics * pgraphics, const rect& rect);

      // implementation helpers
      void CalcInsideRect(rect& rect, bool bHorz) const; // adjusts borders etc
      //bool AllocElements(int32_t nElements, int32_t cbElement);
      virtual bool SetStatusText(int32_t nHit);
      void ResetTimer(UINT nEvent, UINT nTime);
      void EraseNonClient();
      void EraseNonClient(::draw2d::graphics * pdc);

      void GetBarInfo(BaseControlBarInfo* pInfo);
      void SetBarInfo(BaseControlBarInfo* pInfo, sp(::user::frame_window) pFrameWnd);

      DECL_GEN_SIGNAL(_001OnTimer);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnCtlColor);
      DECL_GEN_SIGNAL(_001OnWindowPosChanging);
      DECL_GEN_SIGNAL(_001OnSizeParent);
      DECL_GEN_SIGNAL(_001OnHelpHitTest);
      DECL_GEN_SIGNAL(_001OnInitialUpdate);
      DECL_GEN_SIGNAL(_001OnIdleUpdateCmdUI);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonDblClk);
      DECL_GEN_SIGNAL(_001OnMouseActivate);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      //DECL_GEN_SIGNAL(_001OnShowWindow);
      //DECL_GEN_SIGNAL(_001OnCancelMode);

      //   DECL_GEN_SIGNAL(_001OnPaint);
      //   virtual void _001OnDraw(::draw2d::graphics * pdc);

      virtual void install_message_handling(::message::dispatch * pinterface);

      friend class ::user::frame_window;
      friend class BaseDockBar;


   };


} // namespace user







