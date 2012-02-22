#include "StdAfx.h"

XfplayerViewLines::XfplayerViewLines(::ca::application * papp) :
   ca(papp)
{
    m_iFirstVisible = -1;
    m_iLastVisible = -1;
}

XfplayerViewLines::~XfplayerViewLines()
{
}



void XfplayerViewLines::OnChildSetVisible(XfplayerViewLine * pline, bool bVisible)
{
   index iLineIndex = FindLine(pline);
   index iIndex;

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
      {
         while(!this->element_at(iIndex).IsVisible())
         {
            iIndex++;
            if(iIndex >= this->get_size())
               break;
         }
      }
      m_iFirstVisible = iIndex;
      iIndex = iLineIndex;
      if(iIndex <= m_iLastVisible)
      {
         while(!this->element_at(iIndex).IsVisible())
         {
            iIndex--;
            if(iIndex < 0)
               break;
         }
      }
      m_iLastVisible = iIndex;
   }

}

index XfplayerViewLines::GetFirstVisibleLineIndex()
{
    return m_iFirstVisible;
}

index XfplayerViewLines::GetLastVisibleLineIndex()
{
    return m_iLastVisible;
}

void XfplayerViewLines::Prepare()
{
   for(int i = 0; i < this->get_size(); i++)
   {
      this->element_at(i).m_pContainer = this;
      this->element_at(i).m_iIndex = i;
   }
}

void XfplayerViewLines::Prepare(XfplayerViewLine *lpViewLine)
{
    lpViewLine->m_pContainer = this;
}

void XfplayerViewLines::set_user_interaction(::user::interaction * pinteraction)
{
   m_pinteraction = pinteraction;
}

void XfplayerViewLines::SetEffect(int iEffect)
{
    for(int i = 0 ; i < this->get_size(); i++)
    {
        this->element_at(i).SetTextEffect(iEffect);
    }
}

void XfplayerViewLines::SetRenderWindow(::ca::window * pWnd)
{
   UNREFERENCED_PARAMETER(pWnd);
}

index XfplayerViewLines::FindLine(XfplayerViewLine * pline)
{
   for(int iLine = 0; iLine < this->get_size(); iLine++)
   {
      if(ptr_at(iLine) == pline)
         return iLine;
   }
   return -1;
}

::user::e_line_hit XfplayerViewLines::hit_test(POINT &ptCursor, index &iLine, strsize &iChar)
{
   for(index i = 0; i < this->get_size(); i++)
   {
      ::user::e_line_hit etest = this->element_at(i).hit_test(ptCursor, iChar);
      if(etest != user::line_hit_none)
      {
         iLine = i;
         return  etest;
      }
   }
   return user::line_hit_none;

}

void XfplayerViewLines::InstallMessageHandling(::gen::message::dispatch *pinterface)
{
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE,    pinterface, this, &XfplayerViewLines::OnMouseMove);
   IGUI_WIN_MSG_LINK(WM_SETCURSOR,    pinterface, this, &XfplayerViewLines::OnSetCursor);
   IGUI_WIN_MSG_LINK(WM_TIMER,        pinterface, this, &XfplayerViewLines::OnTimer);
   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN,  pinterface, this, &XfplayerViewLines::OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP,    pinterface, this, &XfplayerViewLines::OnLButtonUp);
}

void XfplayerViewLines::OnMouseMove(gen::signal_object * pobj)
{
   for(int i = 0; i < this->get_size(); i++)
   {
      this->element_at(i).m_pContainer = this;
      this->element_at(i).m_iIndex = i;
      this->element_at(i).OnMouseMove(pobj);
      if(pobj->m_bRet)
         return;
   }
}

void XfplayerViewLines::OnLButtonDown(gen::signal_object * pobj)
{
   for(int i = 0; i < this->get_size(); i++)
   {
      this->element_at(i).m_pContainer = this;
      this->element_at(i).m_iIndex = i;
      this->element_at(i).OnLButtonDown(pobj);
      if(pobj->m_bRet)
         return;
   }
}

void XfplayerViewLines::OnLButtonUp(gen::signal_object * pobj)
{
   for(int i = 0; i < this->get_size(); i++)
   {
      this->element_at(i).OnLButtonUp(pobj);
      if(pobj->m_bRet)
         return;
   }
}

void XfplayerViewLines::OnTimer(gen::signal_object * pobj)
{

   for(int i = 0; i < this->get_size(); i++)
   {
      this->element_at(i).OnTimer(pobj);
      if(pobj->m_bRet)
         return;
   }
}

void XfplayerViewLines::OnSetCursor(gen::signal_object * pobj)
{
   for(int i = 0; i < this->get_size(); i++)
   {
      this->element_at(i).OnSetCursor(pobj);
      if(pobj->m_bRet)
         return;
   }
}

void XfplayerViewLines::SetBlend(double dBlend)
{
   for(int iLine = 0; iLine < this->get_size(); iLine++)
   {
      ptr_at(iLine)->SetBlend(dBlend);
   }
}


XfplayerViewLineSelection & XfplayerViewLines::GetSelection()
{
   return m_selection;
}

