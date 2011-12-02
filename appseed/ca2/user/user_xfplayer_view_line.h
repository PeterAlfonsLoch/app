#pragma once

#include "user_xfplayer_view_line_selection.h"

class XfplayerViewLines;

class CLASS_DECL_ca XfplayerViewLine  :
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

   XfplayerViewLineSelection   m_selection;

   XfplayerViewLine(::ax::application * papp);
   XfplayerViewLine(const XfplayerViewLine & line);
   XfplayerViewLine(XfplayerViewLines * pContainer);
   virtual ~XfplayerViewLine();
   LPBYTE            m_lpBitmapData;
   ::visual::graphics_extension m_dcextension;

// Attributes
private:
   friend class XfplayerViewLines;
   XfplayerViewLines * m_pContainer;
protected:

   // 08, May 2004 attributes
   ::ax::graphics_sp       m_dc1;
   ::ax::bitmap_sp         m_bmp1;
   ::ax::font_sp           m_font;
   ::ax::font_sp           m_fontLink;
   COLORREF                m_cr;
   COLORREF                m_crOutline;
   rect                    m_rectClient;
   double                  m_floatRateX;
   LOGFONT                 m_logfont;


   // 09, Sept 2004 attributes with change inApril 2010 from dcMain/bmpMain to dibMain
   ::ax::dib_sp            m_dibMain;
   bool                    m_bEnhancedEmboss;
   bool                    m_bCacheEmboss;
   string                  m_wstrCache;

   // Link
   LOGFONT                 m_logfontLink;
   stringa               m_straLink;
   int_array               m_iaLinkStart;
   int_array               m_iaLinkEnd;


   double                  m_dBlend;
   int                     m_nFont;
   rect                    m_rectInvalidate;
   int                     m_iAnimateType;
   double                  m_dAnimateProgress;
   double                  m_dAnimateProgressIncrement;
   int                     m_iTextEffect;
   ::ax::pen *             m_lpPenEmboss;
   COLORREF                m_crForeground;
   ::ax::pen *             m_ppenLyricLeft;
   ::ax::pen *             m_ppenLyricRight;
   size                    m_sizeLyricMargin;
   COLORREF                m_crLyricLeft;
   COLORREF                m_crLyricRight;
public:

   int                     m_iLinkHoverIndex;
   int                     m_iIndex;

   void SetBlend(double d);
   ::ax::font * GetFont();
   bool CalcChar(point pt, int &iChar);
   int GetCharLink(int iChar);
   bool GetCharLink(string & str, int iChar);
   bool CharHasLink(int iChar);
   user::e_line_hit GetLink(string & strUrl, point pt);
   int GetLinkIndex(int iLine, int iChar);
   bool HasLink();
   bool IsInHover();
   void UpdateHover(point & ptCursor);
   void PrepareURLLinks();
   void SetFont(visual::font * pfont);
   void SetFont(::ax::font * pfont);
   void GetLogFont(LOGFONT & lf);

   user::e_line_hit hit_test(const POINT &ptCursorParam, int &iChar);


/*   void CalcCharsPositions(
      ::ax::graphics * pdcForeground,
      visual::font * pFont,
      LPCRECT lpcrect);*/

   void CalcCharsPositions(
      ::ax::graphics * pdcForeground,
      LPCRECT lpcrect);

   void SetColors(COLORREF cr, COLORREF crOutline);

   void EmbossedTextOut(
      ::ax::application * papp,
      ::ax::graphics * pdc,
      const char * lpcsz,
      int left,
      int top,
      int ignore1,
      COLORREF cr,
      COLORREF crOutline,
      int iLen,
      double dBlend);

   void EmbossedTextOut(
      ::ax::application * papp,
      ::ax::graphics * pdc,
      ::ax::graphics * pdcCache,
      const char * lpcsz,
      int iLeft,
      int iTop,
      int iWidth,
      COLORREF cr,
      COLORREF crOutline,
      int iLen,
      double dBlend);

   
   void CacheEmboss(
      ::ax::application * papp,
      ::ax::graphics * pdc, 
      const char * lpcsz, 
      int iLen, 
      ::ax::dib * pdibCache);


   bool IsVisible();
   void Validate(LPCRECT lpcrect = NULL);
   void Invalidate(LPCRECT lpcrect = NULL);
   //void AddVmsFont(visual::font * pfont);
   //int GetVmsFontCount();
   void SetPlacement(LPCRECT lpcrect);
   int SetLyricColors(COLORREF crLeft, COLORREF crRight);
   int SetLyricPens(::ax::pen * ppenLeft, ::ax::pen * ppenRight);
   void SetRenderCriticalSection(::critical_section *pcs);
   void SetAnimateIncrement(double dIncrement);
   int MapToFontEffect(int iLineEffect);
    
   
   void SetForegroundColor(COLORREF cr);
   void SetEmbossPen(::ax::pen * lpPen);
   void SetTextEffect(int iTextEffect);

   void SetAnimateType(int iAnimateType);

   void OnTimerAnimate(::ax::graphics * pdc, rect_array &   rectaModified);

   void Show(bool bShow = true);
   virtual XfplayerViewLine & operator = (const XfplayerViewLine & src);
   void GetRect(LPRECT lpRect);
   void set(LPRECT lpRect);
   void SetAlign(int iAlign);
   static const int AlignLeft;
   static const int AlignRight;

   void SetAutoSize(bool bAutoSize);


   string        m_str;
   int_array   m_iaPosition;
   int         m_iTop;
   int         m_iLeft;
   int         m_iIndent;
   int         m_iRight;
   int         m_iBottom;
   bool        m_bPendingLayoutUpdate;
   bool        m_bVisible;
   bool         m_bAutoSizeX;
   bool         m_bAutoSizeY;
   int         m_iAlign;
   ::user::interaction *        m_hwnd;

// Operations
   
   bool PrepareLine(
      ::ax::graphics * pdc,
      const char * lpcsz,
      int flags,
      LPRECT pRect);

   /*bool PrepareLine(
      ::ax::graphics * pdcForeground,
      const wchar_t * lpcsz,
      int flags,
      visual::font *pFont,
      LPRECT pRect);*/

   void GetPlacement(LPRECT lprect);

   void AddChar(   
      WCHAR wch,
      int &index);

   void AddChar(
      WCHAR wch,
      int &index,
      visual::font * pFont);
   
   bool to(
      ::ax::application * papp,
      ::ax::graphics *                  pdc,
      bool                  bDraw,
      LPRECT               lpRect,
      rect_array &      rectaModified,
      bool                  bRecalcLayout);

   bool to(
      ::ax::application * papp,
      ::ax::graphics *                  pdcForeground,
      bool                  bDraw,
      LPRECT               lpRect,
      rect_array &      rectaModified,
      int   *               count,
      bool                  bRecalcLayout,
      COLORREF               crColor,
      ::ax::pen      &            pen);


   DECL_GEN_SIGNAL(OnMouseMove)
   DECL_GEN_SIGNAL(OnLButtonDown)
   DECL_GEN_SIGNAL(OnLButtonUp)
   DECL_GEN_SIGNAL(OnTimer)
   DECL_GEN_SIGNAL(OnSetCursor)

   XfplayerViewLineSelection::e_state GetSelectionState();
   XfplayerViewLineSelection & GetSelection();
   ::user::interaction * get_interaction();
};



