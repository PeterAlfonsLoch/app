#include "framework.h"

XfplayerViewLines::XfplayerViewLines(::aura::application * papp) :
   object(papp)
{

   defer_create_mutex();
   m_iFirstVisible = -1;
   m_iLastVisible = -1;
   m_pinteraction = NULL;

}

XfplayerViewLines::~XfplayerViewLines()
{
}



void XfplayerViewLines::OnChildSetVisible(XfplayerViewLine * pline, bool bVisible)
{
   synch_lock sl(m_pmutex);
   index iLineIndex = FindLine(pline);
   index iIndex;

   if (bVisible)
   {
      if (iLineIndex < m_iFirstVisible)
         m_iFirstVisible = iLineIndex;
      else if (iLineIndex > m_iLastVisible)
         m_iLastVisible = iLineIndex;
   }
   else
   {
      iIndex = iLineIndex;
      if (iIndex >= m_iFirstVisible)
      {
         while (!this->element_at(iIndex)->IsVisible())
         {
            iIndex++;
            if (iIndex >= this->get_size())
               break;
         }
      }
      m_iFirstVisible = iIndex;
      iIndex = iLineIndex;
      if (iIndex <= m_iLastVisible)
      {
         while (!this->element_at(iIndex)->IsVisible())
         {
            iIndex--;
            if (iIndex < 0)
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
   synch_lock sl(m_pmutex);
   for (int32_t i = 0; i < this->get_size(); i++)
   {
      this->element_at(i)->m_pContainer = this;
      this->element_at(i)->m_iIndex = i;
   }
}

void XfplayerViewLines::Prepare(XfplayerViewLine *lpViewLine)
{
   synch_lock sl(m_pmutex);
   lpViewLine->m_pContainer = this;
}

void XfplayerViewLines::set_user_interaction(sp(::user::interaction) pinteraction)
{
   m_pinteraction = pinteraction;
}

void XfplayerViewLines::SetEffect(int32_t iEffect)
{
   synch_lock sl(m_pmutex);
   for (int32_t i = 0; i < this->get_size(); i++)
   {
      this->element_at(i)->SetTextEffect(iEffect);
   }
}

void XfplayerViewLines::SetRenderWindow(::window_sp pwindow)
{
   UNREFERENCED_PARAMETER(pwindow);
}

index XfplayerViewLines::FindLine(XfplayerViewLine * pline)
{
   synch_lock sl(m_pmutex);
   for (int32_t iLine = 0; iLine < this->get_size(); iLine++)
   {
      if (element_at(iLine) == pline)
         return iLine;
   }
   return -1;
}

::user::e_line_hit XfplayerViewLines::hit_test(POINT &ptCursor, index &iLine, strsize &iChar)
{
   synch_lock sl(m_pmutex);
   for (index i = 0; i < this->get_size(); i++)
   {
      ::user::e_line_hit etest = this->element_at(i)->hit_test(ptCursor, iChar);
      if (etest != ::user::line_hit_none)
      {
         iLine = i;
         return  etest;
      }
   }
   return ::user::line_hit_none;

}

void XfplayerViewLines::InstallMessageHandling(::message::dispatch *pinterface)
{
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &XfplayerViewLines::OnMouseMove);
   IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &XfplayerViewLines::OnSetCursor);
   //IGUI_WIN_MSG_LINK(WM_TIMER,        pinterface, this, &XfplayerViewLines::OnTimer);
   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &XfplayerViewLines::OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &XfplayerViewLines::OnLButtonUp);
}

void XfplayerViewLines::OnMouseMove(signal_details * pobj)
{
   synch_lock sl(m_pmutex);
   for (int32_t i = 0; i < this->get_size(); i++)
   {
      this->element_at(i)->m_pContainer = this;
      this->element_at(i)->m_iIndex = i;
      this->element_at(i)->OnMouseMove(pobj);
      if (pobj->m_bRet)
         return;
   }
}

void XfplayerViewLines::OnLButtonDown(signal_details * pobj)
{
   synch_lock sl(m_pmutex);
   for (int32_t i = 0; i < this->get_size(); i++)
   {
      this->element_at(i)->m_pContainer = this;
      this->element_at(i)->m_iIndex = i;
      this->element_at(i)->OnLButtonDown(pobj);
      if (pobj->m_bRet)
         return;
   }
}

void XfplayerViewLines::OnLButtonUp(signal_details * pobj)
{
   synch_lock sl(m_pmutex);
   for (int32_t i = 0; i < this->get_size(); i++)
   {
      this->element_at(i)->OnLButtonUp(pobj);
      if (pobj->m_bRet)
         return;
   }
}

void XfplayerViewLines::_001OnTimer(::timer * ptimer)
{
   synch_lock sl(m_pmutex);
   for (int32_t i = 0; i < this->get_size(); i++)
   {
      this->element_at(i)->_001OnTimer(ptimer);
      if (ptimer->m_bRet)
         return;
   }
}

void XfplayerViewLines::OnSetCursor(signal_details * pobj)
{
   synch_lock sl(m_pmutex);
   for (int32_t i = 0; i < this->get_size(); i++)
   {
      this->element_at(i)->OnSetCursor(pobj);
      if (pobj->m_bRet)
         return;
   }
}

void XfplayerViewLines::SetBlend(double dBlend)
{
   synch_lock sl(m_pmutex);
   for (int32_t iLine = 0; iLine < this->get_size(); iLine++)
   {
      element_at(iLine)->SetBlend(dBlend);
   }
}


XfplayerViewLineSelection & XfplayerViewLines::GetSelection()
{
   return m_selection;
}


void XfplayerViewLines::get_sel_text(string & strSelText, const char * pszLineSeparator)
{
   synch_lock sl(m_pmutex);
   index iLineStart;
   index iCharStart;
   index iLineEnd;
   index iCharEnd;

   m_selection.GetNormalSelection(iLineStart, iCharStart, iLineEnd, iCharEnd);

   if (iLineEnd >= iLineStart)
   {

      if (iLineStart < 0)
         return;

      if (iLineEnd < 0)
         return;

      if (iLineEnd == iLineStart)
      {

         strSelText = element_at(iLineStart)->m_str.Mid(iCharStart, iCharEnd - iCharStart + 1);

      }
      else
      {

         strSelText = element_at(iLineStart)->m_str.Mid(iCharStart);

         for (index iLine = iLineStart + 1; iLine < iLineEnd; iLine++)
         {

            strSelText += pszLineSeparator;

            strSelText += element_at(iLine)->m_str;

         }

         if (iLineEnd > iLineStart)
         {

            strSelText += pszLineSeparator;

            strSelText += element_at(iLineEnd)->m_str.Mid(0, iCharEnd + 1);

         }
      }

   }

}

string XfplayerViewLines::get_sel_text(const char * pszLineSeparator)
{

   string strSelText;

   get_sel_text(strSelText, pszLineSeparator);

   return strSelText;

}


void XfplayerViewLines::get_text(string & strText, const char * pszLineSeparator)
{
   synch_lock sl(m_pmutex);
   if (get_count() > 0)
   {

      strText = element_at(0)->m_str;

   }

   for (int32_t iLine = 1; iLine < get_count(); iLine++)
   {

      strText += pszLineSeparator;

      strText += element_at(iLine)->m_str;

   }

}

string XfplayerViewLines::get_text(const char * pszLineSeparator)
{

   string strText;

   get_text(strText, pszLineSeparator);

   return strText;

}
