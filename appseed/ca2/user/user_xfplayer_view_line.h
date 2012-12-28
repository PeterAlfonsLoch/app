#pragma once


#include "user_xfplayer_view_line_selection.h"


class XfplayerViewLines;


class CLASS_DECL_ca2 XfplayerViewLine  :
   virtual public ::radix::object
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
   int32_t                              m_iTop;
   int32_t                              m_iLeft;
   int32_t                              m_iIndent;
   int32_t                              m_iRight;
   int32_t                              m_iBottom;
   bool                             m_bPendingLayoutUpdate;
   bool                             m_bVisible;
   bool                             m_bAutoSizeX;
   bool                             m_bAutoSizeY;
   int32_t                              m_iAlign;
   ::user::interaction *            m_oswindow;


private:


   friend class XfplayerViewLines;
   XfplayerViewLines *              m_pContainer;


protected:
   //int32_t

   // 08, May 2004 attributes
   ::ca::graphics_sp                m_dc1;
   ::ca::bitmap_sp                  m_bmp1;
   ::ca::font_sp                    m_font;
   ::ca::font_sp                    m_fontLink;
   COLORREF                         m_cr;
   COLORREF                         m_crOutline;
   rect                             m_rectClient;
   double                           m_floatRateX;
   LOGFONT                          m_logfont;


   // 09, Sept 2004 attributes with change inApril 2010 from dcMain/bmpMain to dibMain
   ::ca::dib_sp                     m_dibMain;
   bool                             m_bEnhancedEmboss;
   bool                             m_bCacheEmboss;
   string                           m_wstrCache;

   // Link
   LOGFONT                          m_logfontLink;
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
   ::ca::pen *                      m_lpPenEmboss;
   COLORREF                         m_crForeground;
   ::ca::pen *                      m_ppenLyricLeft;
   ::ca::pen *                      m_ppenLyricRight;
   size                             m_sizeLyricMargin;
   COLORREF                         m_crLyricLeft;
   COLORREF                         m_crLyricRight;

public:

   XfplayerViewLine(::ca::application * papp);
   XfplayerViewLine(const XfplayerViewLine & line);
   XfplayerViewLine(XfplayerViewLines * pContainer);
   virtual ~XfplayerViewLine();
   
   
   void SetBlend(double d);
   ::ca::font * GetFont();
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
   void SetFont(::ca::font * pfont);
   void GetLogFont(LOGFONT & lf);

   user::e_line_hit hit_test(const POINT &ptCursorParam, strsize &iChar);


/*   void CalcCharsPositions(
      ::ca::graphics * pdcForeground,
      visual::font * pFont,
      LPCRECT lpcrect);*/

   void CalcCharsPositions(
      ::ca::graphics * pdcForeground,
      LPCRECT lpcrect);

   void SetColors(COLORREF cr, COLORREF crOutline);

   void EmbossedTextOut(
      ::ca::application * papp,
      ::ca::graphics * pdc,
      const char * lpcsz,
      int32_t left,
      int32_t top,
      int32_t ignore1,
      COLORREF cr,
      COLORREF crOutline,
      strsize iLen,
      double dBlend);

   void EmbossedTextOut(
      ::ca::application * papp,
      ::ca::graphics * pdc,
      ::ca::dib * pdibCache,
      const char * lpcsz,
      int32_t iLeft,
      int32_t iTop,
      int32_t iWidth,
      COLORREF cr,
      COLORREF crOutline,
      strsize iLen,
      double dBlend);

   
   void CacheEmboss(
      ::ca::application * papp,
      ::ca::graphics * pdc, 
      const char * lpcsz, 
      strsize iLen, 
      ::ca::dib * pdibCache);


   bool IsVisible();
   void Validate(LPCRECT lpcrect = NULL);
   void Invalidate(LPCRECT lpcrect = NULL);
   //void AddVmsFont(visual::font * pfont);
   //int32_t GetVmsFontCount();
   void SetPlacement(LPCRECT lpcrect);
   int32_t SetLyricColors(COLORREF crLeft, COLORREF crRight);
   int32_t SetLyricPens(::ca::pen * ppenLeft, ::ca::pen * ppenRight);
   void SetRenderCriticalSection(::critical_section *pcs);
   void SetAnimateIncrement(double dIncrement);
   int32_t MapToFontEffect(int32_t iLineEffect);
    
   
   void SetForegroundColor(COLORREF cr);
   void SetEmbossPen(::ca::pen * lpPen);
   void SetTextEffect(int32_t iTextEffect);

   void SetAnimateType(int32_t iAnimateType);

   void OnTimerAnimate(::ca::graphics * pdc, rect_array &   rectaModified);

   void Show(bool bShow = true);
   virtual XfplayerViewLine & operator = (const XfplayerViewLine & src);
   void GetRect(LPRECT lpRect);
   void set(LPRECT lpRect);
   void SetAlign(int32_t iAlign);
   static const int32_t AlignLeft;
   static const int32_t AlignRight;

   void SetAutoSize(bool bAutoSize);



// Operations
   
   bool PrepareLine(
      ::ca::graphics * pdc,
      const char * lpcsz,
      int32_t flags,
      LPRECT pRect);

   /*bool PrepareLine(
      ::ca::graphics * pdcForeground,
      const wchar_t * lpcsz,
      int32_t flags,
      visual::font *pFont,
      LPRECT pRect);*/

   void GetPlacement(LPRECT lprect);

   void AddChar(   
      WCHAR wch,
      strsize &index);

   void AddChar(
      WCHAR wch,
      strsize &index,
      visual::font * pFont);
   
   bool to(
      ::ca::application * papp,
      ::ca::graphics *                  pdc,
      bool                  bDraw,
      LPRECT               lpRect,
      rect_array &      rectaModified,
      bool                  bRecalcLayout);

   bool to(
      ::ca::application * papp,
      ::ca::graphics *                  pdcForeground,
      bool                  bDraw,
      LPRECT               lpRect,
      rect_array &      rectaModified,
      strsize   *               count,
      bool                  bRecalcLayout,
      COLORREF               crColor,
      ::ca::pen      &            pen);


   DECL_GEN_SIGNAL(OnMouseMove)
   DECL_GEN_SIGNAL(OnLButtonDown)
   DECL_GEN_SIGNAL(OnLButtonUp)
   DECL_GEN_SIGNAL(OnTimer)
   DECL_GEN_SIGNAL(OnSetCursor)

   XfplayerViewLineSelection::e_state GetSelectionState();
   XfplayerViewLineSelection & GetSelection();
   ::user::interaction * get_interaction();


};



