#include "StdAfx.h"

LyricViewLines::LyricViewLines(::ca::application * papp) :
ca(papp),
array_app_alloc < LyricViewLine, LyricViewLine & > (papp),
m_selection(papp)
{
   m_iFirstVisibleLine    = -1;
   m_iLastVisibleLine     = -1;
   m_iBBArrangeLine       = -1;
   m_iTool                = -1;
   m_bRenderEnable        = true;
}

LyricViewLines::~LyricViewLines()
{
   //    ::base_array<LyricViewLine, LyricViewLine &>::~::base_array<LyricViewLine, LyricViewLine &>();
}

index LyricViewLines::GetTokenLine(index iToken)
{
   return GetTokenLine(iToken, NULL);
}

index LyricViewLines::GetTokenLine(index iToken, LyricViewLine ** viewLine)
{
//   int iLoBound = 0;
   int iHiBound = this->get_size() - 1;
   int iIndex = 0;
   int iLastNonEmpty = -1;
   while(iIndex <= iHiBound)
   {
      if(!operator[](iIndex).is_empty())
         iLastNonEmpty = iIndex;
      if(operator[](iIndex).ContainsToken(iToken) && !operator[](iIndex).is_empty())
         break;
      if(operator[](iIndex).m_iFirstToken > iToken)
      {
         iIndex = iLastNonEmpty;
         break;
      }
      iIndex++;
   }
   if(viewLine != NULL && iIndex >= 0 && iIndex <= iHiBound)
   {
      *viewLine = &operator[](iIndex);
   }
   if(iIndex > iHiBound)
      return -1;
   return iIndex;
}

/*int LyricViewLines::get_at(LyricViewLine * * pViewLine, LyricViewLines &viewLines, int iIndex)
{
int iLineIndex = viewLines.element_at(iIndex).m_iRelativeLineIndex;
if(iLineIndex >= 0 &&
iLineIndex < m_nSize)
{
*pViewLine = &this->element_at(iLineIndex);
return iLineIndex;
}
return -1;
}*/

void LyricViewLines::OnChildSetVisible(LyricViewLine & viewline)
{
   ASSERT(viewline.GetContainer() == this);

   int iCurrentLine = viewline.GetLine();
   bool bVisible = viewline.IsVisible();

   if(bVisible)
   {
      if(iCurrentLine < m_iFirstVisibleLine ||
         m_iFirstVisibleLine < 0)
         m_iFirstVisibleLine = iCurrentLine;
      if(iCurrentLine > m_iLastVisibleLine)
         m_iLastVisibleLine = iCurrentLine;
   }
   else
   {
      int iLine = iCurrentLine;
      if(iLine <= m_iFirstVisibleLine && m_iFirstVisibleLine >= 0)
      {
         while(!this->element_at(iLine).IsVisible())
         {
            iLine++;
            if(iLine >= this->get_size())
               break;
         }
         if(iLine >= this->get_size())
         {
            m_iFirstVisibleLine = -1;
         }
         else
         {
            m_iFirstVisibleLine = iLine;
         }
      }
      iLine = iCurrentLine;
      if(iLine >= m_iLastVisibleLine)
      {
         while(!this->element_at(iLine).IsVisible())
         {
            iLine--;
            if(iLine < 0)
               break;
         }
         m_iLastVisibleLine = iLine;
      }
   }

}


void LyricViewLines::Prepare()
{
   for(int i = 0; i < this->get_size(); i++)
   {
      LyricViewLine & rline = this->element_at(i);
      rline.m_pContainer = this;
      rline.m_iLineIndex = i;
   }
   m_iLine                 = -1;
   m_iFirstVisibleLine     = -1;
   m_iLastVisibleLine      = -1;
   m_iTool                 = -1;
   m_iBBArrangeLine        = -1;
   m_bRenderEnable         = true;
}

void LyricViewLines::Prepare(LyricViewLine *lpViewLine)
{
   lpViewLine->m_pContainer = this;
}

void LyricViewLines::SetEffect(int iEffect)
{
   for(int i = 0 ; i < this->get_size(); i++)
   {
      this->element_at(i).SetTextEffect(iEffect);
   }

}

bool LyricViewLines::UpdateFalseVisibility(
   ::ca::graphics *     pdcForeground,
   ::ca::graphics *      pdcBackground,
   bool                  bDraw,
   ikar::data &  karaokedata,
   visual::font *            pfont)
{
   UNREFERENCED_PARAMETER(pdcForeground);
   UNREFERENCED_PARAMETER(pdcBackground);
   UNREFERENCED_PARAMETER(bDraw);
   UNREFERENCED_PARAMETER(pfont);
   int iFirstLine, iLastLine;
   int iFirstCandidateLine, iLastCandidateLine;
   dword_array dwa;
   dword_array dwaCleared;


   // Calculates the first and the last line eligible for
   // true visiblity
   iFirstCandidateLine = max(0, GetTokenLine(karaokedata.GetDynamicData().m_iPlayingTokenIndex, NULL));
   iFirstLine = iFirstCandidateLine;
   iLastLine = this->get_size() - 1;
   iLastCandidateLine = iLastLine;
   int iLine;
   for(iLine = iFirstLine; iLine <= iLastLine; iLine++)
   {
      LyricViewLine & viewline = get(iLine);
      if(dwa.contains(viewline.m_iRelativeLineIndex))
      {
         iLastCandidateLine = iLine - 1;
         break;
      }
      else
      {
         dwa.add(viewline.m_iRelativeLineIndex);
      }
   }

   // Calculates the first ans last visible lines
   iFirstLine = max(0, min(this->get_size() - 1, GetFirstVisibleLine()));
   iLastLine  = min(this->get_size() - 1, max(0, GetLastVisibleLine()));

   // Clears A
   dwa.remove_all();
   dwaCleared.remove_all();
   for(iLine = iFirstLine; iLine <= iLastLine; iLine++)
   {
      LyricViewLine & viewline = this->element_at(iLine);
      if(viewline.IsVisible())
      {
         if((iLine < iFirstCandidateLine ||
            iLine > iLastCandidateLine)
            && !viewline.IsPlaying(karaokedata.GetDynamicData().m_iPlayingTokenIndex))
         {
            viewline.Show(false);
            /*viewline.to(
               pdcForeground,
               karaokedata,
               false);*/
            dwaCleared.add(viewline.m_iRelativeLineIndex);
         }
      }
   }
   return true;
}

bool LyricViewLines::BBUpdateFalseVisibility(
   ::ca::graphics *     pdcForeground,
   ::ca::graphics *     pdcBackground,
   bool                 bDraw,
   ikar::data &  karaokedata,
   visual::font *          pfont,
   index                  iLineIndex
   )
{
   UNREFERENCED_PARAMETER(pdcForeground);
   UNREFERENCED_PARAMETER(pdcBackground);
   UNREFERENCED_PARAMETER(bDraw);
   UNREFERENCED_PARAMETER(karaokedata);
   UNREFERENCED_PARAMETER(pfont);
   //int iFirstLine, iLastLine;
   int iFirstCandidateLine, iLastCandidateLine;
   dword_array dwa;
   dword_array dwaCleared;

   LyricViewLineTemplates & lvlts = *this->element_at(0).GetTemplate()->GetTemplates();

   // Calculates the first and the last line eligible for
   // true visiblity
   //iFirstCandidateLine = max(0, GetTokenLine(karaokedata.GetDynamicData().m_iPlayingTokenIndex));
   iFirstCandidateLine = max(0, iLineIndex);
   iLastCandidateLine = min(this->get_size() - 1, iFirstCandidateLine + lvlts.get_size() - 1);

   // Calculates the first ans last visible lines
  // iFirstLine = max(0, min(this->get_size() - 1, GetFirstVisibleLine()));
   //iLastLine  = min(this->get_size() - 1, max(0, GetLastVisibleLine()));

   // Clears A
   dwa.remove_all();
   dwaCleared.remove_all();
   for(int iTemplate = 0; iTemplate < lvlts.get_count(); iTemplate++)
   {
      LyricViewLineTemplate & lvt = lvlts.element_at(iTemplate);
      if(lvt.GetLine() != NULL)
      {
         LyricViewLine & viewline = *lvt.GetLine();
         if(viewline.m_iLine < iFirstCandidateLine ||
            viewline.m_iLine > iLastCandidateLine
            || (iTemplate == 0 && (m_dBBArrangeRate * m_dBBArrangeRate * 2.0) >= 1.0))
         {
            viewline.Show(false);
            /*viewline.to(
            pdcForeground,
            lprectClient,
            recta,
            karaokedata,
            NULL,
            false);
            dwaCleared.add(viewline.m_iRelativeLineIndex);*/
         }
      }
   }
   return true;
}


bool LyricViewLines::UpdateTrueVisibility(
   ::ca::graphics *      pdcForeground,
   ::ca::graphics *      pdcBackground,
   bool                  bDraw,
   ikar::data &  karaokedata,
   visual::font *            pfont)
{
   UNREFERENCED_PARAMETER(pdcForeground);
   UNREFERENCED_PARAMETER(pdcBackground);
   UNREFERENCED_PARAMETER(bDraw);
   UNREFERENCED_PARAMETER(pfont);

   int iFirstEligibleIndex;
   LyricViewLine * lpviewline = NULL;

   // Calculates the first and the last line eligible for
   // true visiblity
   iFirstEligibleIndex = GetTokenLine(karaokedata.GetDynamicData().m_iPlayingTokenIndex, NULL);

   if(iFirstEligibleIndex >= 0)
   {
      lpviewline = &this->element_at(iFirstEligibleIndex);
      if(!lpviewline->IsVisible())
      {
         if(lpviewline->IsPlaying(karaokedata.GetDynamicData().m_iPlayingTokenIndex))
         {
            lpviewline->Show();
            //lpviewline->to(
              // pdcForeground,
               //karaokedata,
               //false);
         }
      }
   }
   return true;
}

bool LyricViewLines::Arrange(
   ::ca::graphics *     pdcForeground,
   ::ca::graphics *     pdcBackground,
   bool                  bDraw,
   ikar::data &  karaokedata,
   visual::font *            pfont)
{
   int iLineIndex;
   LyricViewLine * lpviewline;
   iLineIndex = GetTokenLine(karaokedata.GetDynamicData().m_iPlayingTokenIndex, &lpviewline);

   if(iLineIndex < 0)
      iLineIndex = 0;

   if(m_iLine != iLineIndex)
   {
      return BBArrange(
         pdcForeground,
         pdcBackground,
         bDraw,
         iLineIndex,
         karaokedata,
         pfont,
         0.0);

   }
   return VMSR_SUCCESS;

}

bool LyricViewLines::BBArrange(
   ::ca::graphics *      pdcForeground,
   ::ca::graphics *      pdcBackground,
   bool                  bDraw,
   index                  iLineIndex,
   ikar::data &  karaokedata,
   visual::font *            pfont,
   double               dRate)
{


   DWORD dwTime = GetTickCount();

   int i;
   //if(m_iLineIndex == iLineIndex)
   // return VMSR_SUCCESS;

   // pending line is a line that is not in its final placement
   // after the first line has finished to be placed and other
   // lines are in their places yet.

   rect rect;

   iLineIndex = GetTokenLine(karaokedata.GetDynamicData().m_iPlayingTokenIndex);


   if(iLineIndex < 0)
      iLineIndex = 0;

   if(iLineIndex >= this->get_size())
      return false;

   {
      ikar::dynamic_data & dynamicdata = karaokedata.GetDynamicData();
      ikar::static_data & staticdata = karaokedata.GetStaticData();
      LyricViewLine & rvl = this->element_at(iLineIndex);
      if(rvl.GetLastToken() - 1 == dynamicdata.m_iPlayingTokenIndex)
      {

         EventsTracksV1 * peventsarray
            = &staticdata.m_eventsTracksForPositionCB;

         LyricEventsV2 * pevents;
         if(peventsarray == NULL ||
            peventsarray->get_size() <= 0)
            pevents = NULL;
         else
         {
            pevents = (LyricEventsV2 *) peventsarray->element_at(0);
            ASSERT(pevents != NULL);
            ASSERT(pevents->GetClassOrder() == 2);
         }
         int iLastNote = pevents->GetTokenLastNote(dynamicdata.m_iPlayingTokenIndex);
         if(iLastNote == dynamicdata.m_iPlayingNoteIndex)
         {
            if(dRate >= 1.0)
            {
               iLineIndex++;
               dRate = 0.0;
            }
         }
      }
   }

   bool bSameRate = dRate == m_dBBArrangeRate;

   if(!bSameRate)
      m_dBBArrangeRate = dRate;

   bool bSameLine = iLineIndex == m_iBBArrangeLine;

   if(!bSameLine)
   {
      m_iBBArrangeLine = iLineIndex;
   }

   if(bSameLine && bSameRate && m_iBBPendingLine == 0)
   {
      return true;
   }


   int iOldLine = m_iLine;
   m_iLine = iLineIndex;

   //TRACE("LyricViewLines::BBArrange oldline=%d line=%d\n", iOldLine, iLineIndex);

   if(this->get_size() <= 0)
      return false;

   LyricViewLineTemplates & lvlts = *this->element_at(0).GetTemplate()->GetTemplates();

   long ly;


   // Hide lyric ::view lines that are out of range
   BBUpdateFalseVisibility(
      pdcForeground,
      pdcBackground,
      bDraw,
      karaokedata,
      pfont,
      iLineIndex);

   // Make visible lyric ::view lines that shoulb be shown
   int iCount = lvlts.get_size();

   for(i = 0; i < iCount; i++)
   {
      if(iLineIndex + i >= this->get_size())
      {
         lvlts[i].SetLine(NULL);
         continue;
      }

      LyricViewLine & rvl = this->element_at(iLineIndex + i);
      LyricViewLineTemplate & lvlt = lvlts.element_at(i);

      // Show only if it is not visible or if the template is not correct
      if(!rvl.IsVisible()
         || rvl.GetTemplate() != &lvlt
         || lvlt.GetLine() != &rvl)
      {
         rvl.SetTemplate(&lvlt);
         if(!rvl.IsVisible()
         && (i != 0 || (m_dBBArrangeRate * m_dBBArrangeRate * 2.0) < 1.0)
         && (i != 1 || (m_dBBArrangeRate * m_dBBArrangeRate) < 1.0)
         && (i != 2 || (m_dBBArrangeRate * m_dBBArrangeRate) < 2.0)
         && (i != 3 || (m_dBBArrangeRate * m_dBBArrangeRate) < 3.0)
         )
         {
            rvl.Show();
         }
         //         rvl.Show();
         //       rvl.Invalidate();
         //      rvl.to(
         //         pdcForeground,
         //         lprect,
         //         rectaModified,
         //       karaokedata,
         //      count,
         //      false);

      }
   }

   // msPause is the time in milliseconds that is waited
   // before the next pending line is going to be processed.
   const DWORD msPause = 75;
   // msTransition is the time in milliseconds that the
   // transition effect takes to be completed.
   const DWORD msTransition = 400;
   // msTotal is the total time taken by a pending line to
   // take its final placement
   const DWORD msTotal = msPause + msTransition;


   if(iLineIndex > iOldLine)
   {
      string strLine;
      this->element_at(iLineIndex).m_tokenaRaw.GetText(strLine);
      if(strLine.has_char())
      {
         m_dBBArrangeRate = 0.0;
      }
      m_iBBPendingLine = 1;
      m_dwBBPendingTime = dwTime;
   }
   else
   {

      // if there is at least a pending line,
      // and the pause period has finished.
      if(m_iBBPendingLine > 0)
      {
         int iNewPendingLine = 1 + ((dwTime - m_dwBBPendingTime) / msTotal);
         if(iNewPendingLine >= lvlts.get_size())
         {
            m_iBBPendingLine = 0;
         }
         else
         {
            m_iBBPendingLine = iNewPendingLine;
         }
      }
   }

   for(i = 0; i < lvlts.get_size(); i++)
   {
      LyricViewLineTemplate & lvlt = lvlts.element_at(i);

      if(lvlt.GetLine() == NULL)
         return NULL;

      LyricViewLine & viewline =  *lvlt.GetLine();

      lvlt.GetPlacement_(rect);

      if(i == 0)
      {
         ly = (long) (- dRate * rect.height());
         ly = -(ly * ly) * 2 / rect.height();
         //if(ly <= -rect.height())
         //{
           // viewline.m_bVisible = false;
         //}
      }
      else if(i == 1 && m_iBBPendingLine == 0)
      {
         ly = (long) (- dRate * rect.height());
         ly = -(ly * ly) / rect.height();
      }
      else if(i == 2 && m_iBBPendingLine == 0 && lvlts.element_at(1).GetLine()->GetMainString().is_empty())
      {
         ly = (long) (- dRate * rect.height() * 2);
         ly = -(ly * ly) / (rect.height() * 2);
      }
      else if(i == 3 && m_iBBPendingLine == 0 && lvlts.element_at(1).GetLine()->GetMainString().is_empty() && lvlts.element_at(2).GetLine()->GetMainString().is_empty())
      {
         ly = (long) (- dRate * rect.height() * 3);
         ly = -(ly * ly) / (rect.height() * 3);
      }
      else
      {
         if(m_iBBPendingLine == 0)
         {
            ly = 0;
         }
         else if(i < m_iBBPendingLine)
         {
            ly = 0;
         }
         else if(i > m_iBBPendingLine)
         {
            ly = rect.height();
         }
         else // i == m_iBBPendingLine
         {
            if(((dwTime - m_dwBBPendingTime) % msTotal) < msPause)
            {
               ly = rect.height();
            }
            else
            {
               double d = ((double) (((dwTime - m_dwBBPendingTime) % msTotal) - msPause) / (double) msTransition);
               ly = (long) ((1.0 - d) *  rect.height());
            }
         }
      }

      if(ly != viewline.GetOffsetY())
      {
         if(m_iBBPendingLine == 0 && i == 1 && ly == 0)
         {
            ly = 0;
         }

         viewline.SetOffsetY(ly);

      }
   }




   /*    for(int i = 0; i < iLineIndex; i++)
   {
   LyricViewLine & rvl = this->element_at(i);
   if(rvl.GetVisible())
   {
   rvl.SetVisible(false);
   rvl.RenderLyricLine(
   lprect,
   prgnaModified,
   iTokenIndex,
   iNoteIndex,
   XFPLYR_LINE_RENDER_CLEAR,
   count,
   pFonts,
   pEvents);

   }
   }
   for(i = iLineIndex + lvlts.get_size(); i < this->get_size(); i++)
   {
   LyricViewLine & rvl = this->element_at(i);
   if(rvl.GetVisible())
   {
   rvl.SetVisible(false);
   rvl.RenderLyricLine(
   lprect,
   prgnaModified,
   iTokenIndex,
   iNoteIndex,
   XFPLYR_LINE_RENDER_CLEAR,
   count,
   pFonts,
   pEvents);
   }
   }*/

   //return true;



   /*   bool bSameLine = iLineIndex == m_iBBArrangeLine;
   if(!bSameLine)
   {
   m_iBBArrangeLine = iLineIndex;
   }

   if(!bSameLine || ! bSameRate)
   {
   int iStartIndex;
   int iEndIndex;

   iStartIndex = GetFirstVisibleLine();
   if(iStartIndex < 0)
   iStartIndex = 0;
   if(iStartIndex >= this->get_size())
   iStartIndex = this->get_size() - 1;
   iEndIndex = GetLastVisibleLine();
   //        if(iEndIndex < iStartIndex)
   //          iEndIndex = iStartIndex;
   if(iEndIndex >= this->get_size())
   iEndIndex = this->get_size() - 1;

   for(i = iStartIndex; i <= iEndIndex; i++)
   {
   LyricViewLine & rvl = this->element_at(i);
   if(rvl.IsVisible())
   {
   rvl.Show(false);
   rvl.to(
   pdcForeground,
   lprect,
   rectaModified,
   karaokedata,
   count,
   false);

   }
   }

   int iSize = lvlts.get_size();

   if(iLineIndex + iSize > this->get_size())
   iSize = this->get_size() - iLineIndex;

   for(i = 0; i < iSize; i++)
   {
   //        if(iLineIndex + i
   LyricViewLine & rvl = this->element_at(iLineIndex + i);
   //         if(m_iBBPendingLine <= 0
   //          || i < m_iBBPendingLine)
   //     {
   rvl.SetTemplate(&lvlts.element_at(i));
   //   }
   //        rvl.SetStatus(rvl.StatusNew);
   //        if(!rvl.GetVisible())
   //      {
   rvl.Show();
   rvl.to(
   pdcForeground,
   lprect,
   rectaModified,
   karaokedata,
   count,
   false);
   //    }
   }
   }*/
   //   if(bExceeded)
   //   {
   //      return VMSR_E_FAIL;
   //   }
   //   else
   //   {
   return true;
   //   }*/
}

void LyricViewLines::GetTokenX_(int iTokenIndex, double * pdLeft, double * pdRight)
{
   int iLineIndex;
   LyricViewLine * lpviewline;
   string str;
   while(true)
   {
      if(0 <= (iLineIndex =
         GetTokenLine(iTokenIndex, &lpviewline)))
      {
         if(lpviewline == NULL)
         {
            *pdLeft = 0.0;
            *pdRight = 1.0;
            return;
         }
         int iRelativeToken = iTokenIndex - lpviewline->m_iFirstToken;
         if(iRelativeToken < 0
            || iRelativeToken >= lpviewline->m_iTokenCount)
         {
            *pdLeft = 0.0;
            *pdRight = 1.0;
            return;
         }
         lpviewline->m_tokenaMain[iRelativeToken]. GetText(str);
         if(str.is_empty())
         {
            iTokenIndex++;
         }
         else
         {
            lpviewline->GetTokenX_(iTokenIndex, pdLeft, pdRight);
            return;
         }
      }
      else
      {
         break;
      }
   }
   *pdLeft = 0.0;
   *pdRight = 1.0;
   return;
}

bool LyricViewLines::GetTokenBBCenter(int iTokenIndex, double * pdLeft, double * pdRight)
{
   int iLineIndex;
   LyricViewLine * lpviewline;
   string str;
   while(true)
   {
      if(0 <= (iLineIndex =
         GetTokenLine(iTokenIndex, &lpviewline)))
      {
         lpviewline->m_tokenaMain[
            iTokenIndex -
               lpviewline->m_iFirstToken].
               GetText(str);
            if(str.is_empty())
            {
               iTokenIndex++;
            }
            else
            {
               return lpviewline->GetTokenBBCenter(iTokenIndex, pdLeft, pdRight);
            }

      }
      else
      {
         break;
      }
   }
   *pdLeft = 0.0;
   *pdRight = 0.0;
   return false;
}



bool LyricViewLines::GetLink(string &str, int iLine, int iToken, int iChar)
{
   return this->element_at(iLine).GetLink(str, iToken, iChar);
}

void LyricViewLines::InvalidateAll()
{
   for(int iLine = 0; iLine < this->get_size(); iLine++)
   {
      this->element_at(iLine).Invalidate();
   }
}

LyricViewLine & LyricViewLines::add_new_line()
{
   LyricViewLine * pline = add_new();
   pline->m_pContainer = this;
   pline->SetLine(get_upper_bound());
   return *pline;
}

kar::LyricViewLineSelection::e_state LyricViewLines::GetSelectionState()
{
   return GetSelection().m_estate;
}






void LyricViewLines::RemoveAllLines()
{
   remove_all();
}




LyricViewLine & LyricViewLines::Lookup(index iLine)
{
//   int iIndex = 0;
   //   if(SortFind(LyricViewLine::GetLine, iLine, iIndex))
   {
      //    if(m_linemap.get_size() <= iLine)
      //      {
      //       m_linemap.set_at_grow(iLine, iIndex);
      //  }
      return this->element_at(iLine);
   }
   //   else
   // {
   //      return *((LyricViewLine *) NULL);
   // }

}

void LyricViewLines::GetBBNoteFillRate(
                                       imedia::time time,
                                       imedia::position position,
                                       LyricEventsV2 * pevents,
                                       double * pdRate,
                                       double * pdBegX,
                                       double * pdEndX)
{
   int iTokenIndex = pevents->GetPositionToken(position);
   int iNoteIndex = pevents->GetPositionNote(position);
   if(iNoteIndex >= pevents->m_msaNotesDuration.get_size())
   {
      *pdRate = 1.0;
      *pdBegX = 0.0;
      *pdEndX = 1.0;
   }
   else if(iNoteIndex < 0)
   {
      *pdRate = 0.0;
      *pdBegX = 0.0;
      *pdEndX = 1.0;
   }
   else
   {
      imedia::time timeNote = pevents->m_msaNotesPosition[iNoteIndex];
      imedia::time timeSpan;
      int iCount = pevents->m_riiTokenNote.b(iTokenIndex).get_count();
      if(time > timeNote)
      {
         timeSpan = time - timeNote;
      }
      else
      {
         timeSpan = 0;
      }
      imedia::time msElapsed = timeSpan;
      imedia::time msTotalLength = pevents->m_msaNotesDuration[iNoteIndex];
      if(msElapsed <= 0)
      {
         *pdRate = 0.0;
      }
      else if(iCount == 0 || msTotalLength == 0)
      {
         *pdRate = 1.0;
      }
      else
      {
         *pdRate = ((double) msElapsed) / ((double) msTotalLength);
      }

      if(*pdRate < 0.0)
         *pdRate = 0.0;
      else if(*pdRate > 1.0)
         *pdRate = 1.0;

      if(iCount == 0)
      {
         *pdBegX = 0.0;
         *pdEndX = 1.0;
      }
      else
      {
         msTotalLength = 0;
         imedia::time msUntilLength = 0;
         for(int i = 0; i < iCount - 1; i++)
         {
            int iIndex = pevents->m_riiTokenNote.b(iTokenIndex)[i];
            if(pevents->m_dwaBeatNote.find_first(iIndex) < 0)
            {
               msTotalLength += pevents->m_msaNotesDuration[iIndex];
               if(iIndex < iNoteIndex)
               {
                  msUntilLength += pevents->m_msaNotesDuration[iIndex];
               }
            }
         }
         if(msTotalLength == 0)
         {
            *pdBegX = 0.0;
            *pdEndX = 1.0;
         }
         else
         {
            *pdBegX = ((int) msUntilLength) / ((int) msTotalLength);
            if(pevents->m_dwaBeatNote.find_first(iNoteIndex) >= 0)
            {
               *pdEndX = *pdBegX;
            }
            else
            {
               *pdEndX = ((int)msUntilLength + (int) pevents->m_msaNotesDuration[iNoteIndex])
                  / ((int) msTotalLength);
            }
         }
      }
   }
}



double LyricViewLines::GetNoteFillRate(
                                       imedia::time time,
                                       imedia::position position,
                                       LyricEventsV2 * pevents)
{
   int iTokenIndex = pevents->GetPositionToken(position);
   int iNoteIndex = pevents->GetPositionNote(position);
   double dFillRate;
   if(iNoteIndex >= pevents->m_msaNotesDuration.get_size())
   {
      dFillRate = 1.0;
   }
   else if(iNoteIndex < 0)
   {
      dFillRate = 0.0;
   }
   else
   {
      imedia::time timeToken = pevents->m_msaTokensPosition[iTokenIndex];
      imedia::time timeSpan;
      if(time > timeToken)
      {
         timeSpan = time - timeToken;
      }
      else
      {
         timeSpan = 0;
      }
      imedia::time msElapsed = timeSpan;
      imedia::time msTotalLength = 0;
      imedia::time msUntilLength = 0;
      int iUntil = 0;
      int iCount = pevents->m_riiTokenNote.b(iTokenIndex).get_count();
      for(int i = 0; i < iCount; i++)
      {
         int iIndex = pevents->m_riiTokenNote.b(iTokenIndex)[i];
         msTotalLength += pevents->m_msaNotesDuration[iIndex];
         if(iIndex <= iNoteIndex)
         {
            iUntil = i;
            msUntilLength += pevents->m_msaNotesDuration[iIndex];
         }
      }
      double dFillRate;
      if(msElapsed <= 0)
      {
         dFillRate = 0.0;
      }
      else if(msTotalLength == 0.0)
      {
         dFillRate = 1.0;
      }
      else if(iCount <= 1)
      {
         dFillRate = 0.33 + ((0.67 * (double) (msElapsed)) / ((double) msTotalLength));
      }
      else
      {
         dFillRate = ((iUntil + 1) * 0.33 / iCount) + (0.33 * msUntilLength / msTotalLength) + ((0.33 * (double) (msElapsed)) / ((double) msTotalLength));
      }

      if(dFillRate < 0.0)
         dFillRate = 0.0;
      else if(dFillRate > 1.0)
         dFillRate = 1.0;
   }
   return dFillRate;
}


void LyricViewLines::RenderEnable(bool bEnable)
{
   m_bRenderEnable = bEnable;
}

kar::KaraokeView * LyricViewLines::GetKaraokeView()
{
   return m_pkaraokeview;
}

void LyricViewLines::SetKaraokeView(kar::KaraokeView *pview)
{
   m_pkaraokeview =pview;
}


void LyricViewLines::PrepareURLLinks()
{
   for(int i = 0; i < this->get_size(); i++)
   {
      LyricViewLine &line = this->element_at(i);
      line.PrepareURLLinks();
   }

}

::ca::application * LyricViewLines::get_app() const
{
   return array_app_alloc < LyricViewLine, LyricViewLine &>::get_app();
}


index LyricViewLines::GetFirstVisibleLine()
{
    return m_iFirstVisibleLine;
}

index LyricViewLines::GetLastVisibleLine()
{
    return m_iLastVisibleLine;
}

bool LyricViewLines::IsRenderEnabled()
{
   return m_bRenderEnable;
}

LyricViewLine & LyricViewLines::get(index iLine)
{
   return this->element_at(iLine);
}

count LyricViewLines::GetLineCount()
{
   return this->get_size();
}

