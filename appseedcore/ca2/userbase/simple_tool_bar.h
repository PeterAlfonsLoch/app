#pragma once


#define TBSTYLE_ALIGN_LEFT     0x10000
#define TBSTYLE_ALIGN_RIGHT    0x30000
#define TBSTYLE_ALIGN_CENTER   0x20000
#define TBSTYLE_ALIGN_TOP      0x40000
#define TBSTYLE_ALIGN_BOTTOM   0x80000
#define TBSTYLE_ALIGN_VCENTER  0xC0000

class image_list;

class simple_toolbar_item
{
public:
   simple_toolbar_item();
   int      m_iIndex;
   int      m_iImage;
   ::visual::dib_sp m_spdib;
   id       m_id;
   BYTE     m_fsState;
   BYTE     m_fsStyle;
   string   m_str;
   rect     m_rect;
};


class CLASS_DECL_ca simple_toolbar :
   public ::userbase::control_bar
{

public:

   enum EElement
   {
      ElementItem,
      ElementItemHover,
      ElementItemPress,
      ElementImage,
      ElementImageHover,
      ElementImagePress,
      ElementText,
      ElementTextHover,
      ElementTextPress,
   };


   bool             m_bTransparentBackground;
   bool             m_bSimpleLayout;
   array_ptr_alloc < simple_toolbar_item, simple_toolbar_item & >
                    m_itema;
   int              m_iHover;

   size             m_sizeButton;
   size             m_sizeImage;
#ifdef WINDOWS
    HRSRC           m_hRsrcImageWell; // handle to loaded resource for image well
#endif
   HINSTANCE        m_hInstImageWell; // instance handle to load image well from
   HBITMAP          m_hbmImageWell; // contains color mapped button images
//   image_list *    m_pimagelist;
//   image_list *    m_pimagelistHue;
//   image_list *    m_pimagelistBlend;
//   image_list *    m_pimagelistHueLight;
   //bool           m_bInternalImageList;
   int              m_iButtonPressItem;
   bool             m_bDelayedButtonLayout;
   ::ca::dib_sp     m_dibDraft;

   ::ca::font_sp    m_font;



   simple_toolbar(::ca::application * papp);
   virtual ~simple_toolbar();


   using ::userbase::control_bar::create;
   BOOL create(::user::interaction* pParentWnd,
      DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP,
      id nID = "AFX_IDW_TOOLBAR");
   using ::user::interaction::CreateEx;
#ifdef WINDOWS
   BOOL CreateEx(::user::interaction* pParentWnd, DWORD dwCtrlStyle = TBSTYLE_FLAT,
      DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP,
      rect rcBorders = rect(0, 0, 0, 0),
      id nID = "AFX_IDW_TOOLBAR");
#else
   BOOL CreateEx(::user::interaction* pParentWnd, DWORD dwCtrlStyle = 0,
      DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP,
      rect rcBorders = rect(0, 0, 0, 0),
      id nID = "AFX_IDW_TOOLBAR");
#endif


   int WrapToolBar(int nCount, int nWidth);
   void SizeToolBar( int nCount, int nLength, BOOL bVert = FALSE);

   size CalcDynamicLayout(int nLength, DWORD dwMode);
   size CalcLayout(DWORD dwMode, int nLength = -1);
   //bool CalcSize(size & size, bool bHorz);
   size CalcSize(int nCount);
   virtual void OnBarStyleChange(DWORD dwOldStyle, DWORD dwNewStyle);
   virtual size CalcFixedLayout(BOOL bStretch, BOOL bHorz);


   void RemoveAllTools();
   virtual int _001GetHoverItem();
   virtual void OnUpdateHover();
   void SetItemImage(int iItem, int iImage);
   void GetButtonText(int i, string & str);
   void SetButtonStyle(int nIndex, UINT nStyle);
   UINT GetButtonStyle(int iButton);
   bool SetItemStyle(int iItem, BYTE bStyle);
   int GetItemStyle(int iItem);
   void _001SetImageList(image_list * pimagelist);
   void _001DiscardImageList();
   void _001OnClick(int iItem);
   int _001HitTest(point pt);
   void _001Hover(point pt, bool bRedraw = true);
   void _001Hover(bool bRedraw = true);


   void layout();


   void _001DrawItem(::ca::graphics * pdc, int iItem);
   bool _001GetItemRect(int iItem, LPRECT lprect);
   bool _001GetItemRect(int iItem, LPRECT lprect, EElement eelement);
   bool _001SetItem(int iItem, simple_toolbar_item * pitem);
   bool _001GetItem(int iItem, simple_toolbar_item * pitem);
   //bool _SetButton(int nIndex, TBBUTTON * pbutton);
   //bool _GetButton(int nIndex, TBBUTTON * pbutton);
   int _001GetItemCount();

/*
   BOOL LoadToolBar(const char * lpszResourceName);
   BOOL LoadToolBar(UINT nIDResource);
   BOOL LoadBitmap(const char * lpszResourceName);
   BOOL LoadBitmap(UINT nIDResource);
*/

   BOOL LoadXmlToolBar(const char * lpszFileName);



//   bool SetButtons(const UINT* lpIDArray, int nIDCount);
   void SetSizes(SIZE sizeButton, SIZE sizeImage);

   void OnUpdateCmdUI(userbase::frame_window* pTarget, BOOL bDisableIfNoHndler);


   void TransparentEraseNonClient(::ca::graphics * pdc);
   void SetTransparentBackground(bool bSet);
   virtual void _001OnDraw(::ca::graphics * pdc);
   size CalcSimpleLayout();

   void _001OnImageListAttrib();
   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnMouseMove)
   DECL_GEN_SIGNAL(_001OnLButtonDown)
   DECL_GEN_SIGNAL(_001OnTimer)
   DECL_GEN_SIGNAL(_001OnLButtonUp)
   DECL_GEN_SIGNAL(_001OnNcCalcSize)
   DECL_GEN_SIGNAL(_001OnNcHitTest)
   DECL_GEN_SIGNAL(_001OnMove)
   DECL_GEN_SIGNAL(_001OnMouseLeave)

   virtual void install_message_handling(::user::win::message::dispatch * pdispatch);


};
