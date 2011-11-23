#pragma once

namespace ikar
{
   class ikar::data;
}

namespace kar
{
   class KaraokeView;
}

class LyricViewLines;
class LyricViewLineTemplate;
class LyricEventsV2;
class CTransparentWndInterface;
class window_redraw_interface;


#define XFPLYR_BREAK_LINE_FEED 1

class CLASS_DECL_ca LyricViewLine :
   virtual public ::radix::object
{
   friend class LyricViewLines;
public:

   class OnVisible
   {
   public:
      OnVisible(::ca::application * papp);
      ::ca::font_sp    m_font;
      ::ca::font_sp    m_fontInt;
      ::ca::font_sp    m_fontExt;
      ::ca::font_sp    m_fontLink;
      ::ca::font_sp    m_fontJp1;
   };

   enum ERenderResult
   {
      XFPLYR_LINE_NULL = 0,
      XFPLYR_LINE_SUCCESS = 1,
      XFPLYR_LINE_SUCCESS_LAST_LINE = 2,
      XFPLYR_LINE_SUCCESS_NO_LINE = 3,
      XFPLYR_LINE_PAGE_BREAK = 8,
      XFPLYR_LINE_ERROR_OUT_OF_BOUND =  -4,
   };

   class CTokenSet;


   class CToken
   {
   public:
      string                  m_str;
      int_array               m_iaPosition;
      int                     m_iStartIndex;
      int                     m_iNextIndex;
      ::ca::dib_sp            m_dibEmboss;

      int GetEndPosition();
      bool CalcChar(point point, int &iChar);
      int Right();
      int Left();
      int width();
      CToken();
      CToken(const CToken & src);
      virtual ~CToken();
      //int GetLinkIndex(int iChar);
      bool RawToJp1();
      bool Prepare();
      void SetPosition(int iChar, int iPosition);
      bool RawToMain(DWORD dwCP);
      int get_position();
      int GetStartIndex();
      void SetStartIndex(int iIndex);
      void SetPosition(int iPosition);
      int get_position(int iChar);
      void GetText(string & str);
      bool AddChar(string tch);
      bool clear();

      CToken & operator = (const CToken & token);

      int GetCharCount();
      bool GetLink(string & str, int iChar);
   };

   class CTokenSet : public array_ptr_alloc<CToken, CToken &>
   {
   public:
      bool HasLink();
      
      void GetText(string & str);
      int GetEndPosition();
      bool CalcChar(point point, int &iToken, int &iChar);
      bool Prepare();
      CTokenSet();
      virtual ~CTokenSet();
      int GetFirstToken();
      void SetLine(LyricViewLine * pline);

      int_array   m_iaCharToken;
      int_array   m_iaChar; // ::collection::map a token set char to a token char



      LyricViewLine * m_pline;

   };

   class CTokenJp1 : public CToken
   {   
   public:
      CTokenJp1();
      CTokenJp1(const CTokenJp1 & token);
      virtual ~CTokenJp1();
      LOGFONT m_logfont;
      float m_floatRateX;

      CTokenJp1 & operator = (const CToken & token);
      CTokenJp1 & operator = (const CTokenJp1 & token);
   };

   class CTokenJp1Set : public base_array<CTokenJp1, const CTokenJp1 &>
   {
   public:
      void copy(const CTokenJp1Set & src);
      bool Prepare();
      CTokenJp1Set();
      virtual ~CTokenJp1Set();
      void copy(const CTokenSet & src);
   };

   enum Animates
   {
      AnimateNoAnimate = 0,
      AnimateRHL = 1 // Rotates Horizontally Left
   };

   enum Effects
   {
      EffectSimple = 0,
      EffectEmbossed = 1
   };
   LPBYTE            m_lpBitmapData;

public:
   LyricViewLines *    m_pContainer;
   int                  m_iStatus;

   OnVisible  *         m_ponvisible;

   // Link
   LOGFONT              m_logfontLink;
   stringa            m_straLink;
   int_array         m_iaLink;
   int_array         m_iaCharLink;

   rect_array      m_rectaInvalidate;
   int                  m_iLinkHoverIndex;
   int                  m_iLinkHoverToken;
   int                  m_iLine;
   imedia::time         m_msPlayStart;
   
   void SetTokenCount(int iCount);
   void CommonConstruct();
   point                   m_ptTextOffset;
   int                     m_iAnimateType;
   double                  m_dAnimateProgress;
   double                  m_dAnimateProgressIncrement;
   int                     m_iTextEffect;
   ::ca::pen *                  m_lpPenEmboss;
   COLORREF                m_crForeground;
   LOGFONT                  m_logfont;
   LOGFONT                  m_logfontInt;
   LOGFONT                 m_logfontExt;

   ::ca::dib_sp               m_dibWork;
   ::ca::dib_sp               m_dibWork2;
   ::ca::dib_sp               m_dibWork3;
   ::ca::dib_sp               m_dibWorkB;
   ::ca::dib_sp               m_dibWorkB2;
   ::ca::dib_sp               m_dibWorkB3;
   
   bool                    m_iLinkCount;
   LyricViewLineTemplate * m_ptemplate;
   int                     m_iTokenCount;
   int                     m_iFirstToken;
   int                     m_iLastToken;
   double                  m_dNoteFillRate;
   imedia::time             m_dwNoteMsLength;
   int                     m_iFillRateNote;
   int                     m_iFillRateToken;


   //dib                     m_dib1;
   ::ca::dib_sp            m_dibMain;
   bool                    m_bCacheEmboss;

   
   DWORD                   m_dwBBTime;
   int                     m_iBBCount;
   CTokenSet               m_tokenaRaw;
   CTokenSet               m_tokenaMain;
   CTokenJp1Set            m_tokenaJp1;
   int                     m_iNotesLength;
   int                     m_iIndent;
   
   //BOOL                  m_bFirstLine;
   int                     m_nFont;
   int                     m_iMiddle;

   int                     m_iMiddleInvalidateStart;
   int                     m_iMiddleInvalidateEnd;

   int                     m_iLastMiddle;
   DWORD                   m_dwCleanTime;
   DWORD                     m_dwNewTime;
   int                     m_iLineIndex;
   int                     m_iRelativeLineIndex;
   bool                    m_bPendingLayoutUpdate;
   bool                    m_bVisible;
   bool                     m_bAutoSizeX;
   bool                     m_bAutoSizeY;



   int                     m_iAlign;

   float                     m_floatRateX;

protected:
   bool                    m_bEnhancedEmboss;
public:
   
   
public:
   LyricViewLine(::ca::application * papp);
   LyricViewLine(const LyricViewLine & line);
   virtual ~LyricViewLine();



   BOOL OnSetCursor(HWND hwnd, UINT uiHitTest, UINT uiMessage);
   void PrepareURLLinks();
   int GetLinkIndex(int iToken, int iChar);
   bool GetLink(string & str, int iToken, int iChar);
   bool HasLink(int iToken, int iChar);
   bool HasLink();
   kar::KaraokeView * GetKaraokeView();
   int GetTokenCount();
   bool IsFirstLine();
   bool is_empty();
   bool ContainsToken(int iTokenIndex);
   kar::LyricViewLineSelection & GetSelection();
   void SetPlayStartTime();
   imedia::time GetPlayStartTime();
   void SetPlayStartTime(imedia::time itime);
   int GetLine();
   void SetLine(int iLine);
   bool HasPlayed(int iPlayingTokenIndex);
   bool IsPlaying(int iPlayingTokenIndex);
   /*int CalcMiddle(
      int iPlayingTokenIndex,
      int iPlayingNoteIndex,
      LyricEventsV2 * pevent);*/

   int GetMiddle(LyricEventsV2 * pevent);


   void Invalidate(
      LPCRECT lpcrect = NULL);
   void Invalidate(
      int iPlayingTokenIndex,
      int iPlayingNoteIndex,
      LyricEventsV2 * pevent);
   user::e_line_hit GetLink(string & str, const POINT & ptCursor);
   bool IsInHover();
   void UpdateHover(point & ptCursor);
   //bool GetLink(string & str, int iToken, int iChar);
   user::e_line_hit hit_test(const POINT & ptCursor, int &iToken, int &iChar);
   void GetSelRect(LPRECT lprect);
   bool CalcChar(point pt, int &iToken, int &iChar);
   virtual void relay_event(gen::signal_object * pobj);
   int GetMainTokenIndex(int iChar);
   string GetMainString();
   void InValidate(LPCRECT lpcrect = NULL);
   void Validate();

   kar::LyricViewLineSelection::e_state GetSelectionState();


   int GetMainPosition(int iChar);
   CToken & GetCharTokenMain(int iChar);
   bool SetMainPosition(int iChar, int iPosition);
   
   bool GetMainString(string & strMain);
   
   

   bool CalcMainTokenSet(DWORD dwCP);
   

   bool GetTokenText(string & str);
   
   void SetPlacement(LPCRECT lprect, int iJp1Provision);
   
   void GetPlacement(LPRECT lprect);

   LyricViewLines * GetContainer();
   
   bool GetTokenX_(int iTokenIndex, double * pdLeft, double * pdRight);

   bool GetTokenBBCenter(
     int iTokenIndex,
     double * pdLeft,
     double * pdRight);


   void SetTemplate(LyricViewLineTemplate * ptemplate);
   LyricViewLineTemplate * GetTemplate();
   void SetAnimateIncrement(double dIncrement);
   int MapToFontEffect(int iLineEffect);
   primitive_array < visual::font *> * GetFonts();
   void SetForegroundColor(COLORREF cr);
   void SetEmbossPen(::ca::pen * lpPen);

   void SetTextEffect(int iTextEffect);
   void SetAnimateType(int iAnimateType);
   void OnTimerAnimate(::ca::region * pModifiedRgn);
   bool IsVisible();
   void Show(bool bShow = true);
   void SetNewTime();
   void SetPendingLayoutUpdate(bool bPending = true);
   int GetLastToken();
   int GetFirstToken();
    
   void SetAlign(int iAlign);
   static const int AlignLeft;
   static const int AlignRight;

   void SetAutoSize(bool bAutoSize);

   bool IsNewTimedOut();
   bool IsCleanTimedOut();
   
   void CalcMainLayout(::ca::graphics * pdcForeground, visual::font * pfont);
   void CalcJp1Layout(::ca::graphics * pdcForeground, visual::font * pfont);
   void CalcNotesPositions(LyricEventsV2 * pEvents);

   void UpdateFillRate(double msElapsed, double msLength, int iTokenNoteOffset, int iTokenNoteCount);
   void Reset();

   ERenderResult Prepare(
      DWORD                dwCP,
      ::ca::graphics *     pdcForeground,
      stringa *          ptokena,
      int                  tokenIndex,
      int *                nextTokenIndex,
      int                  flags,
      LPCRECT              lpcrect,
      LyricEventsV2 *      pEvents);
   
   ERenderResult to(
      ::ca::graphics *     pgdi,
      ikar::data &  karaokedata,
      bool                  bUpdate);

   virtual LyricViewLine & operator =(const LyricViewLine & viewline);

   void SetPlayingToken(int iIndex);
   
   bool OnMouseMove(UINT user, point pt);
   bool OnLButtonDown(UINT user, point pt);
   bool OnLButtonUp(UINT user, point pt);
   bool OnTimer(UINT user);

public:
   bool MaybeURL(const char * lpcsz);
   void SetNoteFillRate(double dFillRate);
   void SetNoteMsLength(imedia::time dwMsLength);
   double GetFillRate();
   void CacheEmboss(::ca::graphics * pdc, const char * lpcsz, int iLen);

/*   void EmbossedTextOut(
      ::ca::graphics *             pdc,
      const char *      lpcsz,
      int               left,
      int               top,
      int               ignore1,
      COLORREF          cr,
      COLORREF          crOutline,
      int               iLen);   */

   void EmbossedTextOut(
      ::ca::graphics *  pdc,
      ::ca::graphics *  pdcCache,
      const char *      lpcsz,
      int               left,
      int               top,
      int               ignore1,
      COLORREF          cr,
      COLORREF          crOutline,
      int               iLen,
      bool              bBegin,
      bool              bEnd);   

   point GetOffset();
   int GetOffsetY();
   void SetOffsetY(int iy);
#ifndef _DEBUG
   void * operator new(size_t st);
   void operator delete (void *);
#endif

};

