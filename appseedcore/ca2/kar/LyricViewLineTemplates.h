#pragma once

class CTransparentWndInterface;

class CLASS_DECL_ca LyricViewLineTemplates :
   virtual public array_app_alloc < LyricViewLineTemplate, LyricViewLineTemplate &>,
   virtual public gen::signalizable
{
public:
   LyricViewLineTemplates(::ca::application * papp);

   virtual ~LyricViewLineTemplates();
protected:
   int                  m_iFirstVisible;
   int                  m_iLastVisible;
   LyricViewLines *     m_plines;
public:
   void InstallMessageHandling(::user::win::message::dispatch * pinterface);
   void SetKaraokeView(kar::KaraokeView * pview);
   void InvalidateAll();
   void clear_lines();
   user::e_line_hit hit_test(POINT & ptCursor, int &iLine, int &iToken, int &iChar);
   LyricViewLines & GetLines();
   void OnSelEnd(LyricViewLine * pline);
   void OnSelStart(LyricViewLine * pline);
   void relay_event(gen::signal_object * pobj);
   void SetRenderWindow(::ca::window * pWnd);
   bool    m_bEmbossed;
//   void SetEffect(int iEffect);
//   void SetBackgroundDC(::ca::graphics * lpDC);
//   void SetForegroundDC(::ca::graphics * lpDC);
   void Prepare(LyricViewLineTemplate * lpViewLine);
   void Prepare();
    
   //int GetFirstVisibleLineIndex();
    //int GetLastVisibleLineIndex();
//   void OnChildSetVisible(LyricViewLineTemplate * lpViewLine, bool bVisible);
//   int get_at(LyricViewLineTemplate ** pViewLine, XfplayerViewLines & viewLines, int iIndex);
//   int GetTokenLine(int iToken, LyricViewLineTemplate ** viewLine);

   static LyricViewLineTemplates null;
   
   DECL_GEN_SIGNAL(OnMouseMove)
   DECL_GEN_SIGNAL(OnLButtonDown)
   DECL_GEN_SIGNAL(OnLButtonUp)
   DECL_GEN_SIGNAL(OnTimer)
   DECL_GEN_SIGNAL(OnSetCursor)
   
};

