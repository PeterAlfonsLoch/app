#include "StdAfx.h"


LyricViewLineTemplate::LyricViewLineTemplate(::ca::application * papp) :
   ca(papp)
{
   m_crLinkLeft               = RGB(200, 200, 255);
   m_crLinkRight              = RGB(100, 100, 255);
   m_crLinkLeftOutline        = RGB(0, 0, 200);
   m_crLinkRightOutline       = RGB(150, 150, 200);
   m_crLinkHoverLeft          = RGB(235, 235, 255);
   m_crLinkHoverRight         = RGB(240, 242, 255);
   m_crLinkHoverLeftOutline   = RGB(0, 0, 255);
   m_crLinkHoverRightOutline  = RGB(200, 200, 255);
   m_pline                    = NULL;
}

LyricViewLineTemplate::LyricViewLineTemplate(LyricViewLineTemplates * ptemplates) :
   ca(ptemplates->get_app())
{
   m_pline = NULL;
   m_crLinkLeft               = RGB(200, 200, 255);
   m_crLinkRight              = RGB(100, 100, 255);
   m_crLinkLeftOutline        = RGB(0, 0, 200);
   m_crLinkRightOutline       = RGB(150, 150, 200);
   m_crLinkHoverLeft          = RGB(235, 235, 255);
   m_crLinkHoverRight         = RGB(240, 242, 255);
   m_crLinkHoverLeftOutline   = RGB(0, 0, 255);
   m_crLinkHoverRightOutline  = RGB(200, 200, 255);
   m_ptemplates               = ptemplates;
   m_pline                    = NULL;
}

LyricViewLineTemplate::LyricViewLineTemplate(LyricViewLineTemplate & linetemplate) :
   ca(linetemplate.get_app())
{
   operator =(linetemplate);
}

LyricViewLineTemplate::~LyricViewLineTemplate()
{

}

int LyricViewLineTemplate::SetPens(
   ::ca::pen * ppenLeft, 
   ::ca::pen * ppenRight,
   ::ca::pen * ppenLeftSmall, 
   ::ca::pen * ppenRightSmall,
   ::ca::pen * ppenLinkLeft, 
   ::ca::pen * ppenLinkRight,
   ::ca::pen * ppenHoverLeft, 
   ::ca::pen * ppenHoverRight
   )
{

   m_ppenLeft              = ppenLeft;
   m_ppenRight             = ppenRight;
   m_ppenLeftSmall         = ppenLeftSmall;
   m_ppenRightSmall        = ppenRightSmall;
   m_ppenLinkLeft          = ppenLinkLeft;
   m_ppenLinkRight         = ppenLinkRight;
   m_ppenLinkHoverLeft     = ppenHoverLeft;
   m_ppenLinkHoverRight    = ppenHoverRight;

   LOGPEN leftLogPen;
   LOGPEN rightLogPen;

   m_ppenLeft->GetLogPen(&leftLogPen);
   m_ppenRight->GetLogPen(&rightLogPen);
   
   int cx = max(
      leftLogPen.lopnWidth.x,
      rightLogPen.lopnWidth.x);
   
   int cy = max(
      leftLogPen.lopnWidth.y,
      rightLogPen.lopnWidth.y );
   
   cx = cx / 2 + cx % 2;
   cy = cy / 2 + cy % 2;
    
   m_sizeMargin.cx = cx;
   m_sizeMargin.cy = cy;

   return true;
}

int LyricViewLineTemplate::SetColors(
   COLORREF crLeft, 
   COLORREF crRight,
   COLORREF crLeftOutline, 
   COLORREF crRightOutline)
{
   m_crLeft          = crLeft;
   m_crRight         = crRight;
   m_crLeftOutline   = crLeftOutline;
   m_crRightOutline  = crRightOutline;
   return true;

}






void LyricViewLineTemplate::GetColors(
   COLORREF & crLeft, 
   COLORREF & crRight,
   COLORREF & crLeftOutline, 
   COLORREF & crRightOutline
   )
{
   crLeft         = m_crLeft;
   crRight        = m_crRight;
   crLeftOutline  = m_crLeftOutline;
   crRightOutline = m_crRightOutline;

}

void LyricViewLineTemplate::GetLinkColors(
      COLORREF & crLeft, COLORREF & crRight,
      COLORREF & crLeftOutline, COLORREF & crRightOutline,
      COLORREF & crHoverLeft, COLORREF & crHoverRight,
      COLORREF & crHoverLeftOutline, COLORREF & crHoverRightOutline)
{
    crLeft              = m_crLinkLeft;
    crRight             = m_crLinkRight;
    crLeftOutline       = m_crLinkLeftOutline;
    crRightOutline      = m_crLinkRightOutline;
    crHoverLeft         = m_crLinkHoverLeft;
    crHoverRight        = m_crLinkHoverRight;
    crHoverLeftOutline  = m_crLinkHoverLeftOutline;
    crHoverRightOutline = m_crLinkHoverRightOutline;
}


void LyricViewLineTemplate::SetPlacement_(LPCRECT lpcrect, int iJp1Provision)
{
   m_rectPlacement = *lpcrect;
   m_iJp1Provision = iJp1Provision;
}




bool LyricViewLineTemplate::SetTextOffsetMode(ETextOffsetMode etom)
{
   m_etom = etom;
   return true;
}


void LyricViewLineTemplate::relay_event(gen::signal_object * pobj)
{
   LyricViewLine *pline = GetLine();
   if(pline != NULL)
   {
      ASSERT(fx_is_valid_address(pline, sizeof(LyricViewLine), TRUE));
      pline->SetTemplate(this);
      pline->relay_event(pobj);
      if(pobj->m_bRet)
         return;
   }
}

bool LyricViewLineTemplate::SetLine(LyricViewLine *pline)
{
   if(pline == NULL)
      m_pline = NULL;
   else
   {
      m_pline = pline;
   }
   return true;
}

void LyricViewLineTemplate::OnSelStart(LyricViewLine * pline)
{
   m_ptemplates->OnSelStart(pline);
}

void LyricViewLineTemplate::OnSelEnd(LyricViewLine * pline)
{
   UNREFERENCED_PARAMETER(pline);
}



user::e_line_hit LyricViewLineTemplate::hit_test(POINT &ptCursor, int &iLine, int &iToken, int &iChar)
{
   LyricViewLine *pline = GetLine();
   if(pline != NULL)
   {
      user::e_line_hit etest =
         pline->hit_test(ptCursor, iToken, iChar);
      if(etest != ::user::line_hit_none)
      {
         iLine = pline->GetLine();
         return  etest;
      }
   }
   return ::user::line_hit_none;

}

LyricViewLineTemplate & LyricViewLineTemplate::operator = (const LyricViewLineTemplate & linetemplate)
{
   m_ppenLeft                 = linetemplate.m_ppenLeft;
   m_ppenRight                = linetemplate.m_ppenRight;
   m_ppenLeftSmall            = linetemplate.m_ppenLeftSmall;
   m_ppenRightSmall           = linetemplate.m_ppenRightSmall;
   m_ppenLinkLeft             = linetemplate.m_ppenLinkLeft;
   m_ppenLinkRight            = linetemplate.m_ppenLinkRight;
   m_ppenLinkHoverLeft        = linetemplate.m_ppenLinkHoverLeft;
   m_ppenLinkHoverRight       = linetemplate.m_ppenLinkHoverRight;
   m_crLeft                   = linetemplate.m_crLeft;
   m_crRight                  = linetemplate.m_crRight;
   m_crLinkLeft               = linetemplate.m_crLinkLeft;
   m_crLinkRight              = linetemplate.m_crLinkRight;
   m_crLinkLeftOutline        = linetemplate.m_crLinkLeftOutline;
   m_crLinkRightOutline       = linetemplate.m_crLinkRightOutline;
   m_crLinkHoverLeft          = linetemplate.m_crLinkHoverLeft;
   m_crLinkHoverRight         = linetemplate.m_crLinkHoverRight;
   m_crLinkHoverLeftOutline   = linetemplate.m_crLinkHoverLeftOutline;
   m_crLinkHoverRightOutline  = linetemplate.m_crLinkHoverRightOutline;
   m_rectPlacement            = linetemplate.m_rectPlacement;
   m_sizeMargin               = linetemplate.m_sizeMargin;
   m_ptemplates               = linetemplate.m_ptemplates;
   m_iJp1Provision            = linetemplate.m_iJp1Provision;
   m_etom                     = linetemplate.m_etom;
   m_pline                    = linetemplate.m_pline;
   m_bFirstLine               = linetemplate.m_bFirstLine;
   m_etextoffsetmode          = linetemplate.m_etextoffsetmode;
   m_bNeedFullUpdate          = linetemplate.m_bNeedFullUpdate;
   return *this;
      }

void LyricViewLineTemplate::clear()
{
   m_pline = NULL;
}

void LyricViewLineTemplate::OnUpdateFirstLineFlag()
{
   m_etextoffsetmode = IsFirstLine() ? tomClip : tomNoClip;
}

void LyricViewLineTemplate::SetFirstLineFlag(bool bSet)
{
   m_bFirstLine = bSet;
   OnUpdateFirstLineFlag();
}

bool LyricViewLineTemplate::OnMouseMove(UINT user, point pt)
{
   LyricViewLine *pline = GetLine();
   if(pline != NULL)
   {
      ASSERT(fx_is_valid_address(pline, sizeof(LyricViewLine), TRUE));
//      pline->SetTemplate(this);
      if(pline->OnMouseMove(user, pt))
         return true;
   }
   return false;
}

bool LyricViewLineTemplate::OnLButtonDown(UINT user, point pt)
{
   LyricViewLine *pline = GetLine();
   if(pline != NULL)
   {
      ASSERT(fx_is_valid_address(pline, sizeof(LyricViewLine), TRUE));
      pline->SetTemplate(this);
      if(pline->OnLButtonDown(user, pt))
         return true;
   }
   return false;
}

bool LyricViewLineTemplate::OnLButtonUp(UINT user, point pt)
{
   LyricViewLine *pline = GetLine();
   if(pline != NULL)
   {
      ASSERT(fx_is_valid_address(pline, sizeof(LyricViewLine), TRUE));
      pline->SetTemplate(this);
      if(pline->OnLButtonUp(user, pt))
         return true;
   }
   return false;

}

bool LyricViewLineTemplate::OnTimer(UINT user)
{
   LyricViewLine *pline = GetLine();
   if(pline != NULL)
   {
      ASSERT(fx_is_valid_address(pline, sizeof(LyricViewLine), TRUE));
//      pline->SetTemplate(this);
      if(pline->OnTimer(user))
         return true;
   }
   return false;

}

BOOL LyricViewLineTemplate::OnSetCursor(HWND hwnd, UINT uiHitTest, UINT uiMessage)
{
   LyricViewLine *pline = GetLine();
   if(pline != NULL)
   {
      ASSERT(fx_is_valid_address(pline, sizeof(LyricViewLine), TRUE));
//      pline->SetTemplate(this);
      if(pline->OnSetCursor(hwnd, uiHitTest, uiMessage))
         return TRUE;
   }
   return FALSE;

}


::ca::dib * LyricViewLineTemplate::get_bb_alpha_blend()
{
   if(!IsFirstLine())
      return NULL;
   if(m_dibAlphaBlend.m_p == NULL)
   {
      m_dibAlphaBlend.create(get_app());
   }
   if(m_dibAlphaBlend.m_p == NULL)
      return NULL;
   if(m_dibAlphaBlend->size() != m_rectPlacement.size())
   {
      m_dibAlphaBlend->create(m_rectPlacement.size());
      int iH = m_dibAlphaBlend->height()  / 2;
      for(int i = 0; i < m_dibAlphaBlend->height(); i++)
      {
         int iAlpha;
         if(i < (m_dibAlphaBlend->height() - iH))
         {
            iAlpha = 0;
         }
         else
         {
            iAlpha = (i - m_dibAlphaBlend->height() + iH) * 255  / iH;
         }
         m_dibAlphaBlend->horizontal_line(i, 0, 0, 0, max(min(255, iAlpha), 0));
      }
   }
   return m_dibAlphaBlend;
}


void LyricViewLineTemplate::GetPlacement_(LPRECT lpRect)
{
    *lpRect = m_rectPlacement;
}

LyricViewLineTemplate::ETextOffsetMode LyricViewLineTemplate::GetTextOffsetMode()
{
   return m_etextoffsetmode;
   

}

inline bool LyricViewLineTemplate::IsFirstLine()
{
   return m_bFirstLine;
}

void LyricViewLineTemplate::GetMargin(SIZE & size)
{
    size = m_sizeMargin;
}

void LyricViewLineTemplate::GetPens(
   ::ca::pen **pppenLeft, ::ca::pen **pppenRight,
   ::ca::pen **pppenLeftSmall, ::ca::pen **pppenRightSmall)
{
   *pppenLeft         = m_ppenLeft;
   *pppenRight        = m_ppenRight;
   *pppenLeftSmall    = m_ppenLeftSmall;
   *pppenRightSmall   = m_ppenRightSmall;
}

void LyricViewLineTemplate::GetLinkPens(
   ::ca::pen *& ppenLeft, ::ca::pen *& ppenRight,
   ::ca::pen *& ppenHoverLeft, ::ca::pen *& ppenHoverRight)
{
   ppenLeft          = m_ppenLinkLeft;
   ppenRight         = m_ppenLinkRight;
   ppenHoverLeft     = m_ppenLinkHoverLeft;
   ppenHoverRight    = m_ppenLinkHoverRight;

}

LyricViewLineTemplates * LyricViewLineTemplate::GetTemplates()
{
    return m_ptemplates;
}

LyricViewLine * LyricViewLineTemplate::GetLine()
{
   return m_pline;
}

