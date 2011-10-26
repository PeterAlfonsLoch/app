#pragma once

class LyricEventsV2;

typedef struct tag_LyricViewLineShiftEvent
{
    int         nLine;
    double      dRate;
} LYRICVIEWLINESHIFTEVENT, *LPLYRICVIEWLINESHIFTEVENT;

namespace kar
{

   class CLASS_DECL_ca KaraokeBouncingBall :
      public ikar::data_container
   {
   public:
      KaraokeBouncingBall(::ca::application * papp);
      virtual ~KaraokeBouncingBall();

      enum EBallType
      {
         Ball,
         icon,
         image
      };
   
   protected:
      LyricViewLines       m_lyricViewLines;
   
      critical_section     m_csRender;
      rect                m_rectBall;
      rect                m_rectPlacement;
      rect                m_rectClient;
   //    CTransparentWndInterface *           m_ptwi_;
   //    ::ca::graphics *           m_lpBackgroundDC;
   
      size                m_sizeBall;
      ::ca::brush_sp               m_brushBall;
      ::ca::pen_sp                 m_penBall;
      int                  m_iPlayingTokenIndex;
      DWORD                m_dwUpdateHint;
      int                  m_iLineIndex;
      bool                 m_bPendingBBArrange;
      int                  m_iBBArrangeLine;
      double               m_dBBArrangeRate;
      EBallType            m_eballtype;
      int                  m_iBBArrangeNextLine;
      //imedia::CPosition    m_tkPosition;
      imedia::position    m_tkQuarterNote;
   
   public:
      LyricViewLines *     m_pviewlines;
      double               m_dCurrentNoteLeft;
      double               m_dCurrentNoteRight;
      imedia::time         m_iDelay; // in milliseconds
      HICON                m_hiconNormal;
      HICON                m_hiconPressed;
      ::visual::dib_sp     m_dibBall;
      ::visual::dib_sp     m_dibBallShadow;
    
   public:
      void SetBallSize(SIZE size);
      //void SetPosition(imedia::CPosition tkPosition);
      void SetIcons(HICON hicon, HICON hiconPressed = NULL);
      void SetBallType(EBallType balltype);
      int GetBBArrangeLine();
      double GetBBArrangeRate();
      void ClearPendingBBArrange();
      bool HasPendingBBArrange();
       inline DWORD GetUpdateHint()
       {
           return m_dwUpdateHint;
       }
      VMSRESULT Prepare();
      
   //    void SetBackgroundDC(::ca::graphics * pgraphics);
   
       //void SetForegroundDC(::ca::graphics * pgraphics);
  
      //void SetTwi(CTransparentWndInterface * pTwi);

      void SetQuarterNoteDuration(imedia::position tk);



      void SetPlacement(LPRECT lpRect);

      static double GetSplineY(
         double dCycleRate,
         double n);
    
      static double GetSplineX(
           double dCycleRate,
           double x1,
           double x2);

      VMSRESULT to(
         ::ca::graphics *      pdc,
         bool                  bDraw,
         LyricViewLine *      lpline,
         LyricEventsV2 *      pEvents,
         bool bShadow);

   };

}
