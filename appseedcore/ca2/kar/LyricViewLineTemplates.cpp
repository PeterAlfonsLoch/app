#include "StdAfx.h"

LyricViewLineTemplates LyricViewLineTemplates::null(NULL);

LyricViewLineTemplates::LyricViewLineTemplates(::ca::application * papp)
: ca(papp),
array_app_alloc < LyricViewLineTemplate, LyricViewLineTemplate &>(papp)
{
   m_plines = new LyricViewLines(papp);
   m_iFirstVisible   = -1;
   m_iLastVisible    = -1;
}


LyricViewLineTemplates::~LyricViewLineTemplates()
{
   if(m_plines != NULL)
   {
      delete m_plines;
   }
//    ::base_array<LyricViewLineTemplate, LyricViewLineTemplate &>::~::base_array<LyricViewLineTemplate, LyricViewLineTemplate &>();
}

/*int LyricViewLineTemplates::GetTokenLine(int iToken, LyricViewLineTemplate ** viewLine)
{
    int iLoBound = 0;
   int iHiBound = m_nSize - 1;
   int iIndex = 0;;
   while(true)
   {
      if(iLoBound > iHiBound)
      {
         return -1;
      }
      iIndex = (iHiBound + iLoBound) / 2;
      if(operator[](iIndex).ContainsToken(iToken))
         break;
      else if(iToken < operator[](iIndex).GetFirstToken())
      {
         iHiBound = iIndex - 1;
      }
      else if(iToken > operator[](iIndex).GetLastToken())
      {
         iLoBound = iIndex + 1;
      }
      else
         ASSERT(0);
   }
   *viewLine = &operator[](iIndex);
   return iIndex;
} */

/*int LyricViewLineTemplates::get_at(LyricViewLineTemplate * * pViewLine, LyricViewLineTemplates &viewLines, int iIndex)
{
    int iLineIndex = viewLines.element_at(iIndex).m_iRelativeLineIndex;
    if(iLineIndex >= 0 &&
        iLineIndex < m_nSize)
    {
        *pViewLine = &element_at(iLineIndex);
        return iLineIndex;
    }
    return -1;
} */

/*void LyricViewLineTemplates::OnChildSetVisible(LyricViewLineTemplate *lpViewLine, bool bVisible)
{
    ASSERT(lpViewLine >= m_pData);
    ASSERT(lpViewLine < (m_pData + m_nSize));

    int iLineIndex = ((LPBYTE) lpViewLine - (LPBYTE) m_pData) / sizeof(LyricViewLineTemplate);
    int iIndex;

    ASSERT(&m_pData[iLineIndex] == lpViewLine);

    if(bVisible)
    {
        if(iLineIndex < m_iFirstVisible)
            m_iFirstVisible = iLineIndex;
        else if(iLineIndex > m_iLastVisible)
            m_iLastVisible = iLineIndex;
    }
    else
    {
        iIndex = iLineIndex;
        if(iIndex >= m_iFirstVisible)
            while(!element_at(iIndex).GetVisible())
            {
                iIndex++;
                if(iIndex >= m_nSize)
                    break;
            }
        m_iFirstVisible = iIndex;
        iIndex = iLineIndex;
        if(iIndex <= m_iLastVisible)
            while(!element_at(iIndex).GetVisible())
            {
                iIndex--;
                if(iIndex < 0)
                    break;
            }
        m_iLastVisible = iIndex;
    }

}*/

/*int LyricViewLineTemplates::GetFirstVisibleLineIndex()
{
    return m_iFirstVisible;
}

int LyricViewLineTemplates::GetLastVisibleLineIndex()
{
    return m_iLastVisible;
}*/

void LyricViewLineTemplates::Prepare()
{
   for(int i = 0; i < get_count(); i++)
   {
      element_at(i).m_ptemplates = this;
   }
   m_iFirstVisible   = -1;
   m_iLastVisible    = -1;
}

void LyricViewLineTemplates::Prepare(LyricViewLineTemplate *lpViewLine)
{
    lpViewLine->m_ptemplates = this;
}

/*void LyricViewLineTemplates::SetForegroundDC(::ca::graphics *lpDC)
{
    for(int i = 0 ; i < get_size(); i++)
    {
        element_at(i).SetForegroundDC(lpDC);
    }
}

void LyricViewLineTemplates::SetBackgroundDC(::ca::graphics *lpDC)
{
    for(int i = 0 ; i < get_size(); i++)
    {
        element_at(i).SetBackgroundDC(lpDC);
    }
}

void LyricViewLineTemplates::SetEffect(int iEffect)
{
    for(int i = 0 ; i < get_size(); i++)
    {
        element_at(i).SetTextEffect(iEffect);
    }

}

void LyricViewLineTemplates::SetRenderWindow(::ca::window * pWnd)
{
    for(int i = 0 ; i < get_size(); i++)
    {
        element_at(i).SetRenderWindow(pWnd);
    }
}*/

void LyricViewLineTemplates::relay_event(gen::signal_object * pobj)
{
   SCAST_PTR(user::win::message::base, pbase, pobj);
   if(pbase->m_uiMessage != WM_MOUSEMOVE
    || pbase->m_uiMessage != WM_TIMER
    || pbase->m_uiMessage != WM_LBUTTONDOWN
    || pbase->m_uiMessage != WM_LBUTTONUP)
   {
      return;
   }

   for(int i = 0; i < get_size(); i++)
   {
      element_at(i).relay_event(pobj);
      if(pobj->m_bRet)
         return;
   }
}

void LyricViewLineTemplates::OnSelStart(LyricViewLine * pline)
{
   UNREFERENCED_PARAMETER(pline);
}

void LyricViewLineTemplates::OnSelEnd(LyricViewLine * pline)
{
   UNREFERENCED_PARAMETER(pline);
}

LyricViewLines & LyricViewLineTemplates::GetLines()
{
   return *m_plines;
}

user::e_line_hit LyricViewLineTemplates::hit_test(POINT &ptCursor, int &iLine, int &iToken, int &iChar)
{
   for(int i = 0; i < get_size(); i++)
   {
      user::e_line_hit etest =
         element_at(i).hit_test(ptCursor, iLine, iToken, iChar);
      if(etest != ::user::line_hit_none)
      {
         return  etest;
      }
   }
   return ::user::line_hit_none;
}

void LyricViewLineTemplates::clear_lines()
{
   for(int i = 0; i < get_size(); i++)
   {
      LyricViewLineTemplate & linetemplate = element_at(i);
      linetemplate.clear();
   }
   m_plines->RemoveAllLines();
}

void LyricViewLineTemplates::InvalidateAll()
{
   m_plines->InvalidateAll();
}

void LyricViewLineTemplates::SetKaraokeView(kar::KaraokeView *pview)
{
   m_plines->SetKaraokeView(pview);
}

void LyricViewLineTemplates::InstallMessageHandling(::user::win::message::dispatch *pinterface)
{
   ::user::win::message::connect(
      WM_MOUSEMOVE,
      pinterface, 
      this, 
      &LyricViewLineTemplates::OnMouseMove);
   ::user::win::message::connect(
      WM_SETCURSOR,
      pinterface, 
      this, 
      &LyricViewLineTemplates::OnSetCursor);
   ::user::win::message::connect(
      WM_TIMER,
      pinterface, 
      this, 
      &LyricViewLineTemplates::OnTimer);
   ::user::win::message::connect(
      WM_LBUTTONDOWN,
      pinterface, 
      this, 
      &LyricViewLineTemplates::OnLButtonDown);
   ::user::win::message::connect(
      WM_LBUTTONUP,
      pinterface, 
      this, 
      &LyricViewLineTemplates::OnLButtonUp);

}

void LyricViewLineTemplates::OnMouseMove(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   for(int i = 0; i < get_size(); i++)
   {
      if(element_at(i).OnMouseMove(pmouse->m_nFlags, pmouse->m_pt))
      {
         pmouse->m_bRet = true;
         return;
      }
   }
   pmouse->m_bRet  = false;
}

void LyricViewLineTemplates::OnLButtonDown(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   for(int i = 0; i < get_size(); i++)
   {
      if(element_at(i).OnLButtonDown(pmouse->m_nFlags, pmouse->m_pt))
      {
         pmouse->set_lresult(1);
         pmouse->m_bRet = true;
         return;
      }
   }
   pmouse->m_bRet = false;
   return;
}

void LyricViewLineTemplates::OnLButtonUp(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   for(int i = 0; i < get_size(); i++)
   {
      if(element_at(i).OnLButtonUp(pmouse->m_nFlags, pmouse->m_pt))
      {
         pmouse->set_lresult(1);
         pmouse->m_bRet = true;
         return;
      }
   }
   pmouse->m_bRet = false;
   return;
}

void LyricViewLineTemplates::OnTimer(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::timer, ptimer, pobj);
   for(int i = 0; i < get_size(); i++)
   {
      if(element_at(i).OnTimer(ptimer->m_nIDEvent))
      {
         ptimer->m_bRet = false;
         return;
      }
   }
   ptimer->m_bRet = false;
}

void LyricViewLineTemplates::OnSetCursor(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::set_cursor, psetcursor, pobj)
   for(int i = 0; i < get_size(); i++)
   {
      if(element_at(i).OnSetCursor(
         (HWND) psetcursor->m_pWnd->get_os_data(), 
         psetcursor->m_nHitTest, 
         psetcursor->m_message))
      {
         psetcursor->m_bRet = true;
         return;
      }
   }
   psetcursor->m_bRet = false;
}


bool LyricViewLineTemplate::IsEmbossed()
{
    return m_ptemplates->m_bEmbossed;
}

void LyricViewLine::GetPlacement(LPRECT lprect)
{
   m_ptemplate->GetPlacement_(lprect);
}
