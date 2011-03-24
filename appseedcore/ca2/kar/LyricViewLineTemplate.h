#pragma once

class CTransparentWndInterface;
class LyricViewLine;

class CLASS_DECL_ca LyricViewLineTemplate :
   virtual public ::radix::object
{
public:
   friend class LyricViewLineTemplates;

   enum ETextOffsetMode
   {
      tomClip,
      tomNoClip
   };

   ETextOffsetMode            m_etextoffsetmode;
   ::ca::pen *                m_ppenLeft;
   ::ca::pen *                m_ppenRight;
   ::ca::pen *                m_ppenLeftSmall;
   ::ca::pen *                m_ppenRightSmall;
   ::ca::pen *                m_ppenLinkLeft;
   ::ca::pen *                m_ppenLinkRight;
   ::ca::pen *                m_ppenLinkHoverLeft;
   ::ca::pen *                m_ppenLinkHoverRight;

   COLORREF                   m_crLeft;
   COLORREF                   m_crRight;
   COLORREF                   m_crLeftOutline;
   COLORREF                   m_crRightOutline;
   COLORREF                     m_crLinkLeft;
   COLORREF                     m_crLinkRight;
   COLORREF                     m_crLinkLeftOutline;
   COLORREF                     m_crLinkRightOutline;
   COLORREF                     m_crLinkHoverLeft;
   COLORREF                     m_crLinkHoverRight;
   COLORREF                     m_crLinkHoverLeftOutline;
   COLORREF                     m_crLinkHoverRightOutline;
   rect                       m_rectPlacement;
   size                       m_sizeMargin;
   LyricViewLineTemplates *   m_ptemplates;
   int                        m_iJp1Provision;
   bool                       m_bFirstLine;
   enum ETextOffsetMode       m_etom;
   LyricViewLine *            m_pline;
   bool                       m_bNeedFullUpdate;
   ::ca::dib_sp               m_dibAlphaBlend;

   LyricViewLineTemplate(::ca::application * papp);
   LyricViewLineTemplate(LyricViewLineTemplate & linetemplate);
   LyricViewLineTemplate(LyricViewLineTemplates  * ptemplates);
   virtual ~LyricViewLineTemplate();

   ::ca::dib * get_bb_alpha_blend();

   void SetPlacement_(LPCRECT lpcrect, int iJp1Provision);

   void GetColors(
      COLORREF & crLeft, 
      COLORREF & crRight,
      COLORREF & crOutlineLeft, 
      COLORREF & crOutlineRight);
   void GetLinkColors(
      COLORREF & crLeft, COLORREF & crRight,
      COLORREF & crLeftOutline, COLORREF & crRightOutline,
      COLORREF & crHoverLeft, COLORREF & crHoverRight,
      COLORREF & crHoverLeftOutLine, COLORREF & crHoverRightOutline);
   void GetPens(
      ::ca::pen ** pppenLeft, ::ca::pen ** pppenRight,
      ::ca::pen ** pppenLeftSmall, ::ca::pen ** pppenRightSmall);
   void GetLinkPens(
      ::ca::pen *& ppenLeft, ::ca::pen *& ppenRight,
      ::ca::pen *& ppenHoverLeft, ::ca::pen *& ppenHoverRight);
   void GetMargin(SIZE & size);
   void GetPlacement_(LPRECT lpRect);
   int SetPens(
      ::ca::pen * ppenLeft, 
      ::ca::pen * ppenRight,
      ::ca::pen * ppenLeftSmall, 
      ::ca::pen * ppenRightSmall,
      ::ca::pen * ppenLinkLeft,
      ::ca::pen * ppenLinkRight,
      ::ca::pen * ppenHoverLeft, 
      ::ca::pen * ppenHoverRight);


   int SetColors(
      COLORREF crLeft, 
      COLORREF crRight,
      COLORREF crLeftOutline, 
      COLORREF crRightOutline);

   LyricViewLineTemplate & operator = (const LyricViewLineTemplate & linetemplate);


   bool IsEmbossed();
   
   BOOL OnSetCursor(HWND hwnd, UINT uiHitTest, UINT uiMessage);
   bool IsFirstLine();
   void SetFirstLineFlag(bool bSet = true);
   void OnUpdateFirstLineFlag();
   void clear();
   user::e_line_hit hit_test(POINT & ptCursor, int &iLine, int &iToken, int &iChar);
   void OnSelEnd(LyricViewLine *pline);
   void OnSelStart(LyricViewLine *pline);
   bool SetLine(LyricViewLine * pline);
   LyricViewLine * GetLine();
   void relay_event(gen::signal_object * pobj);
   ETextOffsetMode GetTextOffsetMode();
   bool SetTextOffsetMode(ETextOffsetMode etom);
   LyricViewLineTemplates * GetTemplates();
    
    
   bool OnMouseMove(UINT user, point pt);
   bool OnLButtonDown(UINT user, point pt);
   bool OnLButtonUp(UINT user, point pt);
   bool OnTimer(UINT user);
};



