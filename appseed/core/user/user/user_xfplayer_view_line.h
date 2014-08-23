#pragma once


#include "user_xfplayer_view_line_selection.h"


class XfplayerViewLines;


class CLASS_DECL_CORE XfplayerViewLine  :
   virtual public ::object
{
public:


   enum EAnimate
   {
      AnimateNoAnimate = 0,
      AnimateRHL = 1 // Rotates Horizontally Left
   };


   enum EEffect
   {
      EffectSimple = 0,
      EffectEmbossed = 1
   };


   XfplayerViewLineSelection        m_selection;
   LPBYTE                           m_lpBitmapData;
   ::visual::graphics_extension     m_dcextension;

   index                            m_iLinkHoverIndex;
   index                            m_iIndex;

   string                           m_str;
   int_array                        m_iaPosition;

   rect                                m_rect;

   int32_t                              m_iIndent;
   bool                             m_bPendingLayoutUpdate;
   bool                             m_bVisible;
   bool                             m_bAutoSizeX;
   bool                             m_bAutoSizeY;
   int32_t                              m_iAlign;
   sp(::user::interaction)            m_oswindow;
   XfplayerViewLines *              m_pContainer;

   // 08, May 2004 attributes
   ::draw2d::graphics_sp                m_dc1;
   ::draw2d::bitmap_sp                  m_bmp1;
   ::draw2d::font_sp                    m_font;
   ::draw2d::font_sp                    m_fontLink;
   COLORREF                         m_cr;
   COLORREF                         m_crOutline;
   rect                             m_rectClient;
   double                           m_floatRateX;
   LOGFONTW                          m_logfont;


   // 09, Sept 2004 attributes with change inApril 2010 from dcMain/bmpMain to dibMain
   ::draw2d::dib_sp                     m_dibMain;
   bool                             m_bEnhancedEmboss;
   bool                             m_bCacheEmboss;
   string                           m_strCache;

   // Link
   LOGFONTW                          m_logfontLink;
   stringa                          m_straLink;
   index_array                      m_iaLinkStart;
   index_array                      m_iaLinkEnd;


   double                           m_dBlend;
   int32_t                              m_nFont;
   rect                             m_rectInvalidate;
   int32_t                              m_iAnimateType;
   double                           m_dAnimateProgress;
   double                           m_dAnimateProgressIncrement;
   int32_t                              m_iTextEffect;
   ::draw2d::pen *                      m_lpPenEmboss;
   COLORREF                         m_crForeground;
   ::draw2d::pen *                      m_ppenLyricLeft;
   ::draw2d::pen *                      m_ppenLyricRight;
   size                             m_sizeLyricMargin;
   COLORREF                         m_crLyricLeft;
   COLORREF                         m_crLyricRight;

   XfplayerViewLine(sp(::aura::application) papp);
   XfplayerViewLine(const XfplayerViewLine & line);
   XfplayerViewLine(XfplayerViewLines * pContainer);
   virtual ~XfplayerViewLine();


   void SetBlend(double d);
   ::draw2d::font * GetFont();
   bool CalcChar(point pt, strsize &iChar);
   index GetCharLink(strsize iChar);
   bool GetCharLink(string & str, strsize iChar);
   bool CharHasLink(strsize iChar);
   user::e_line_hit GetLink(string & strUrl, point pt);
   index GetLinkIndex(index iLine, strsize iChar);
   bool HasLink();
   bool IsInHover();
   void UpdateHover(point & ptCursor);
   void PrepareURLLinks();
   void SetFont(visual::font * pfont);
   void SetFont(::draw2d::font * pfont);
   void GetLogFont(LOGFONTW & lf);

   user::e_line_hit hit_test(const POINT &ptCursorParam, strsize &iChar);


/*   void CalcCharsPositions(
      ::draw2d::graphics * pdcForeground,
      visual::font * pFont,
      const RECT & rect);*/

   void CalcCharsPositions(
      ::draw2d::graphics * pdcForeground,
      const RECT & rect);

   void SetColors(COLORREF cr, COLORREF crOutline);

   void EmbossedTextOut(
      ::draw2d::graphics * pdc,
      const char * lpcsz,
      int32_t left,
      int32_t top,
      int32_t ignore1,
      COLORREF cr,
      COLORREF crOutline,
      strsize iLen,
      double dBlend);

   void EmbossedTextOut(
      ::draw2d::graphics * pdc,
      ::draw2d::dib * pdibCache,
      const char * lpcsz,
      int32_t iLeft,
      int32_t iTop,
      int32_t iWidth,
      COLORREF cr,
      COLORREF crOutline,
      strsize iLen,
      double dBlend);


   void CacheEmboss(
      ::draw2d::graphics * pdc,
      const char * lpcsz,
      strsize iLen,
      ::draw2d::dib * pdibCache);


   bool IsVisible();
   void Validate(const RECT & rect = ::null_rect());
   void Invalidate(const RECT & rect = ::null_rect());
   //void AddVmsFont(visual::font * pfont);
   //int32_t GetVmsFontCount();
   void SetPlacement(const RECT & rect);
   int32_t SetLyricColors(COLORREF crLeft, COLORREF crRight);
   int32_t SetLyricPens(::draw2d::pen * ppenLeft, ::draw2d::pen * ppenRight);
   void SetRenderCriticalSection(::critical_section *pcs);
   void SetAnimateIncrement(double dIncrement);
   int32_t MapToFontEffect(int32_t iLineEffect);


   void SetForegroundColor(COLORREF cr);
   void SetEmbossPen(::draw2d::pen * lpPen);
   void SetTextEffect(int32_t iTextEffect);

   void SetAnimateType(int32_t iAnimateType);

   void OnTimerAnimate(::draw2d::graphics * pdc, rect_array &   rectaModified);

   void Show(bool bShow = true);
   virtual XfplayerViewLine & operator = (const XfplayerViewLine & src);
   void GetPlacement(LPRECT lpRect);
   void SetPlaement(const RECT & rect);
   void SetAlign(int32_t iAlign);
   static const int32_t AlignLeft;
   static const int32_t AlignRight;

   void SetAutoSize(bool bAutoSize);



   bool PrepareLine(::draw2d::graphics * pdc, const string & str, int32_t flags, const RECT & rect);

   void AddChar(
      WCHAR wch,
      strsize &index);

   void AddChar(
      WCHAR wch,
      strsize &index,
      visual::font * pFont);

   bool to(::draw2d::graphics * pdc, bool bDraw, const RECT & rect, rect_array & rectaModified, bool bRecalcLayout);

   bool to(::draw2d::graphics * pdc, bool bDraw, const RECT & rect, rect_array & rectaModified, strsize * count, bool bRecalcLayout, COLORREF crColor, ::draw2d::pen_sp sppen);


   DECL_GEN_SIGNAL(OnMouseMove);
   DECL_GEN_SIGNAL(OnLButtonDown);
   DECL_GEN_SIGNAL(OnLButtonUp);
   DECL_GEN_SIGNAL(OnTimer);
   DECL_GEN_SIGNAL(OnSetCursor);

   XfplayerViewLineSelection::e_state GetSelectionState();
   XfplayerViewLineSelection & GetSelection();
   sp(::user::interaction) get_interaction();


};



