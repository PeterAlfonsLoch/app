#pragma once

class LyricEventV1;
class visual::font;
class XfplayerViewLines;

namespace kar
{

   class KaraokeBouncingBall;

   class CLASS_DECL_ca KaraokeView :
      virtual public database::user::interaction,
      virtual public ikar::data_container
   {
   public:
      int                                 _iDebugNote;
      int                                 _iDebugToken;
      double                              _dDebugOldFillRate;

      bool                                m_bHardWriting;

      LyricViewLineTemplates              m_lyrictemplatelines;
      XfplayerViewLines *                 m_plinesTitle;
      bool                                m_bBouncingBall;
      bool                                m_bSuperScriptEmphasis;
      bool                                m_bGradualFilling;
      DWORD                               m_dwAdvancingTime;
      DWORD                               m_dwLastShiftUpdate;
      KaraokeBouncingBall *               m_lpbouncingball;
      bool                                m_bEmbossed;
      COLORREF                            m_crLeft;
      COLORREF                            m_crRight;
      COLORREF                            m_crLeftOutline;
      COLORREF                            m_crRightOutline;
      ::ca::pen_sp                        m_penLeft;
      ::ca::pen_sp                        m_penRight;
      ::ca::pen_sp                        m_penLeftSmall;
      ::ca::pen_sp                        m_penRightSmall;
      ::ca::pen_sp                        m_penLinkLeft;
      ::ca::pen_sp                        m_penLinkRight;
      ::ca::pen_sp                        m_penHoverLeft;
      ::ca::pen_sp                        m_penHoverRight;
      visual::font                        m_fontLyrics;
      double                              m_dScale;
   private:   
      bool                                m_bTitle;
      bool                                m_bTitleVisible;

      
   public:
      double                              m_dLyricFontEmbossWidth;

      KaraokeView(::ca::application * papp);
      virtual ~KaraokeView();

      void SetScale(double dScale);


      virtual bool is_ok_for_rendering();
      
      // Internationalization
      virtual DWORD KaraokeGetDefaultCodePage(const char * lpsz);
      virtual DWORD KaraokeGetOverridingCodePage(const char * lpsz);
      virtual bool KaraokeDoesOverrideCodePage();

      void KaraokeRender(::ca::graphics * pdc);

      virtual bool IsKaraokeBouncingBall();
      void _Translate(string & str);
      void _Translate(string_array & stra);
      void _TranslateAndFormat(string & str, const char * lpszFormat, string_array & wstraArg);
      virtual DWORD KaraokeGetCodePage(const char * lpsz);
      void LayoutTitleLines();
      void SetTitleVisible(bool bVisible);
      virtual int KaraokeGetLyricsDelay();
      virtual void KaraokeGetPosition(imedia::position & position);
      virtual HCURSOR KaraokeGetHandCursor();
      virtual visual::font * GetLyricFont();
      void clear();
   protected:
      virtual void OnLyricEvent(LyricEventV1 *pevent, bool bRepaint);
      
      void PrepareLyricTemplateLines();
      void PrepareLyricLines();
      void LayoutLyricTemplateLines();
      void LayoutKaraokeBouncingBall();
      void LayoutLyricLines();
      bool ShowBouncingBall(bool bShow);

      
      virtual void OnShowBouncingBall(bool bShow);
      virtual LyricViewLines & GetLyricLines();
      virtual VMSRESULT UpdateScreen(rect_array & recta, UINT uiRedraw) = 0;

   };

} // namespace kar

