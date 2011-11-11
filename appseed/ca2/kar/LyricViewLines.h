#pragma once

class LyricEventsV2;
class window_redraw_interface;

class CLASS_DECL_ca LyricViewLines :
   public array_app_alloc < LyricViewLine, LyricViewLine &>
{
public:
   kar::LyricViewLineSelection   m_selection;
   index                         m_iFirstVisibleLine;
   index                         m_iLastVisibleLine;
   index                         m_iLine;
   double                        m_dBBArrangeRate;
   index                         m_iBBArrangeLine;
   bool                          m_bBBArrange;
   index                         m_iTool;
   int_array                     m_iaNoteGetNoteFillRate;
   index                         m_iTokenGetNoteFillRate;
   bool                          m_bRenderEnable;
   double                        m_dLastBBArrangeRate;
   index                         m_iBBPendingLine;
   DWORD                         m_dwBBPendingTime;
   kar::KaraokeView *            m_pkaraokeview;

   LyricViewLines(::ca::application * papp);
   virtual ~LyricViewLines();

   void PrepareURLLinks();
   void SetKaraokeView(kar::KaraokeView * pview);
   kar::KaraokeView * GetKaraokeView();
   void RenderEnable(bool bEnable = true);
   bool IsRenderEnabled();
   LyricViewLine & Lookup(index iLine);
   count GetLineCount();
   void RemoveAllLines();
   LyricViewLine & get(index iLine);
   kar::LyricViewLineSelection & GetSelection();
   kar::LyricViewLineSelection::e_state GetSelectionState();
   LyricViewLine & add_new_line();
   void InvalidateAll();

   virtual ::ca::application * get_app() const;
   
   bool GetLink(string & str, int iLine, int iToken, int iChar);

   void GetTokenX_(
        int iTokenIndex,
        double * pdLeft,
        double * pdRight);

    bool GetTokenBBCenter(
        int iTokenIndex,
        double * pdLeft,
        double * pdRight);

   bool BBArrange(
      ::ca::graphics *     pdcForeground,
      ::ca::graphics *      pdcBackground,
      bool                  bDraw,
      index                  iLineIndex,
      ikar::data &  karaokedata,
      visual::font *          pfont,
      double               dRate);

    bool BBUpdateFalseVisibility(
      ::ca::graphics *     pdcForeground,
      ::ca::graphics *     pdcBackground,
      bool                 bDraw,
      ikar::data &  karaokedata,
      visual::font *          pfont,
      index                  iLineIndex);
   
   
   bool Arrange(
      ::ca::graphics *     pdcForeground,
      ::ca::graphics *     pdcBackground,
      bool                 bDraw,
      ikar::data &  karaokedata,
      visual::font *          pfont);


   bool UpdateFalseVisibility(
      ::ca::graphics *     pdcForeground,
      ::ca::graphics *     pdcBackground,
      bool                 bDraw,
      ikar::data &  karaokedata,
      visual::font *          pfont);
   
   
   bool UpdateTrueVisibility(
      ::ca::graphics *     pdcForeground,
      ::ca::graphics *     pdcBackground,
      bool                 bDraw,
      ikar::data &  karaokedata,
      visual::font *          pfont);
   
   void SetEffect(int iEffect);
   void Prepare(LyricViewLine * lpViewLine);
   void Prepare();
    
   index GetFirstVisibleLine();
   index GetLastVisibleLine();
   void OnChildSetVisible(LyricViewLine & viewline);
   index GetTokenLine(index iToken, LyricViewLine ** viewLine);
   index GetTokenLine(index iToken);
   
   double GetNoteFillRate(imedia::time time, imedia::position position, LyricEventsV2 * pEvents);
   void GetBBNoteFillRate(imedia::time time, imedia::position position, LyricEventsV2 * pEvents, double * pdRate, double * pdBegX, double * pdEndX);
   
};

template<> inline index BaseSortCompare<LyricViewLine &>(LyricViewLine & line1, LyricViewLine & line2)
{
   return line1.GetLine() - line2.GetLine();
}


