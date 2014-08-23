#pragma once

#ifndef HDS_HORZ
// begin_r_commctrl

#define HDS_HORZ                0x0000
#define HDS_BUTTONS             0x0002
#define HDS_HOTTRACK            0x0004
#define HDS_HIDDEN              0x0008

#define HDS_DRAGDROP            0x0040
#define HDS_FULLDRAG            0x0080
#define HDS_FILTERBAR           0x0100

#if (NTDDI_VERSION >= NTDDI_WINXP)
#define HDS_FLAT                0x0200
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
#define HDS_CHECKBOXES          0x0400
#define HDS_NOSIZING            0x0800
#define HDS_OVERFLOW            0x1000
#endif
// end_r_commctrl

#define HDFT_ISSTRING       0x0000      // HD_ITEM.pvFilter points to a HD_TEXTFILTER
#define HDFT_ISNUMBER       0x0001      // HD_ITEM.pvFilter points to a INT
#define HDFT_ISDATE         0x0002      // HD_ITEM.pvFilter points to a DWORD (dos date)

#define HDFT_HASNOVALUE     0x8000      // clear the filter, by setting this bit

#ifdef UNICODE
#define HD_TEXTFILTER HD_TEXTFILTERW
#define HDTEXTFILTER HD_TEXTFILTERW
#define LPHD_TEXTFILTER LPHD_TEXTFILTERW
#define LPHDTEXTFILTER LPHD_TEXTFILTERW
#else
#define HD_TEXTFILTER HD_TEXTFILTERA
#define HDTEXTFILTER HD_TEXTFILTERA
#define LPHD_TEXTFILTER LPHD_TEXTFILTERA
#define LPHDTEXTFILTER LPHD_TEXTFILTERA
#endif

#endif

namespace user
{


   class list;


   class CLASS_DECL_CORE list_header :
      virtual public database::user::interaction
   {
   public:


      class CLASS_DECL_CORE item
      {
      public:


         UINT    mask;
         int32_t     cxy;
         LPWSTR  pszText;
         HBITMAP hbm;
         int32_t     cchTextMax;
         int32_t     fmt;
         LPARAM  lParam;
         int32_t     iImage;        // index of bitmap in ImageList
         int32_t     iOrder;
         UINT    type;           // [in] filter type (defined what pvFilter is a pointer to)
         void *  pvFilter;       // [in] fillter data see above
         UINT   state;
      };


      enum EElement
      {
         ElementItem,
         ElementItemBox,
         ElementDivider,
      };


      ::draw2d::font_sp                 m_font;
      string                        m_strBuffer;
      visual::graphics_extension    m_dcextension;

      bool                          m_bTrack;
      bool                          m_bHover;
      EElement                      m_eelementHover;
      index                         m_iItemHover;
      bool                          m_bLButtonDown;
      EElement                      m_eelementLButtonDown;
      index                         m_iItemLButtonDown;

      list *                        m_plistctrlinterface;


      list_header(sp(::aura::application) papp);
      virtual ~list_header();

      void install_message_handling(::message::dispatch * pinterface);
      void SetBaseListCtrlInterface(list * pinterface);

      virtual void _001OnDraw(::draw2d::graphics * pdc);
      virtual void DrawItem(::draw2d::item * pdrawitem);


      virtual bool DIDDXColumn(bool bSave);
      virtual bool DIDDXLayout(bool bSave);
      virtual index MapItemToOrder(index iItem);
      virtual index ItemToColumnKey(index iItem);

      virtual int32_t GetDividerWidth();


      bool GetItemRect(
         LPRECT lprect,
         EElement eelement,
         index iItem);

      bool GetItemRect(
         LPRECT lprect,
         EElement eelementLButtonDown,
         index iItemLButtonDown,
         EElement eelement,
         index iItem);

      bool hit_test(
         POINT point,
         EElement & eelement,
         index & iItem);

      bool hit_test(
         POINT point,
         EElement eelementLButtonDown,
         index iItemLButtonDown,
         EElement & eelement,
         index & iItem);

      // Message Handlers
   protected:
      DECL_GEN_VSIGNAL(_001OnLButtonDown);
      DECL_GEN_VSIGNAL(_001OnLButtonUp);
      DECL_GEN_VSIGNAL(_001OnLButtonDblClk);
         DECL_GEN_VSIGNAL(_001OnMouseMove);

   };

} // namespace user



