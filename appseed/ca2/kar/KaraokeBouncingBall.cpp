#include "StdAfx.h"
#include "KaraokeBouncingBall.h"


namespace kar
{

   KaraokeBouncingBall::KaraokeBouncingBall(::ca::application * papp) :
      ca(papp),
      m_lyricViewLines(papp),
      m_brushBall(papp),
      m_penBall(papp),
      m_dibBall(papp),
      m_dibBallShadow(papp)
   {
       m_sizeBall.cx = 49;
       m_sizeBall.cy = 49;
       m_brushBall->CreateSolidBrush(RGB(255, 255, 255));
       m_penBall->CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
       //m_brushBall.CreateSolidBrush(RGB(0, 0, 0));
       //m_penBall.CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
       m_dwUpdateHint = 0;
       m_iDelay = 0;
       m_bPendingBBArrange = false;
       m_eballtype = image;
       m_dibBall.load_from_matter("mplite/yellow_ball.png");
       m_dibBallShadow.load_from_matter("sphere-shadow.png");
   }

   KaraokeBouncingBall::~KaraokeBouncingBall()
   {

   }

   // It calculates vertical position of a function
   // that spline in three points:
   // A(-m,0), B(0,n), C(m,0)

   //double KaraokeBouncingBall::NormalSpline(double dCycleRate, double m, double n)
   double KaraokeBouncingBall::GetSplineY(double dCycleRate, double n)
   {
   //    if(m == 0)
     //  {
       //    return 2.0 * (0.5 - abs(dCycleRate - 0.5)) * n;
   //    }
     //  else
       //{

   //        double x = 2.0 * m * (dCycleRate - 0.5);
   //        return (-n / (m * m)) * x * x + n;

           //double x = 2.0 * (dCycleRate - 0.5);
           //return (-n * x * x) + n;

           double x = 2.0 * (dCycleRate - 0.5);
           return (1.0 - (x * x)) * n;

       //}
   }

   // It calculates vertical position of a function
   // that spline in three points:
   // A(x1,0), B(x1 + x2 / 2, y0), C(x2,0)

   //double KaraokeBouncingBall::Spline(
     //  double x, double y0, double x1, double x2)
   double KaraokeBouncingBall::GetSplineX(
       double dCycleRate,
       double x1,
       double x2)
   {
       return x1 + (x2 - x1) * dCycleRate;
   }


























   VMSRESULT KaraokeBouncingBall::to(
      ::ca::graphics *                     pdc,
      bool                     bDraw,
      LyricViewLine *         lpline,
      LyricEventsV2 *         plyricevents, // must be Normalized
      bool bShadowNow)
   {

      if(plyricevents == NULL)
         return VMSR_E_FAIL;

      single_lock slRender(&m_csRender, TRUE);

      ikar::data & data = GetKaraokeData();
      ikar::dynamic_data & dynamicdata = data.GetDynamicData();
//      ikar::static_data & staticdata = data.GetStaticData();
      ikar::karaoke * pinterface = data.GetInterface();
      imedia::position position = dynamicdata.m_position;
      imedia::time time = dynamicdata.m_time;

      rect rectPlacement = m_rectPlacement;
      rect rectBall = m_rectBall;


      if(bDraw)
      {
         rectBall.inflate(2, 2, 2, 2);
      }


      imedia::position tkCurrentNote;
      imedia::position tkNextNote;

      {
         imedia::position tkOldPosition = position;
         imedia::time iMsPosition  = pinterface->PositionToTime(position);
         iMsPosition -= m_iDelay;
         position = pinterface->TimeToPosition(iMsPosition);
      }

      int iCurrentToken    = plyricevents->GetPositionToken(position);
      int iCurrentNote     = plyricevents->GetPositionNote(position);
      int iNextToken       = iCurrentToken + 1;
//      int iLineLastToken   = lpline->GetLastToken();
      int iLastNote        = plyricevents->GetTokenLastNote(iCurrentToken);

      //bool bLineLastToken  = iLineLastToken == iCurrentToken;
      bool bTokenLastNote  = iLastNote == iCurrentNote;

      imedia::position tkLastNote;
      if(iLastNote < 0)
      {
         tkLastNote = 0;
      }
      else
      {
         tkLastNote = plyricevents->m_tkaNotesPosition.element_at(iLastNote);
      }

      double dRate;
      double dBegX;
      double dEndX;

      m_lyricViewLines.GetBBNoteFillRate(
         time,
         position,
         plyricevents,
         &dRate,
         &dBegX,
         &dEndX);



      double dDeltaX;

      double dCurrentTokenLeft   = 0.0;
      double dCurrentTokenRight  = 0.0;
      double dNextTokenLeft      = 0.0;
      double dNextTokenRight     = 0.0;

      iNextToken = iCurrentToken + 1;

      if(iCurrentToken >= 0)
      {
         lpline->GetContainer()->GetTokenX_(
            iCurrentToken,
            &dCurrentTokenLeft,
            &dCurrentTokenRight);
      }
      else
      {
         dCurrentTokenLeft = m_rectClient.left;
         dCurrentTokenRight = dCurrentTokenLeft;
      }

      dDeltaX              = (dCurrentTokenRight - dCurrentTokenLeft);
      dCurrentTokenLeft    += dDeltaX * 0.50;
      dCurrentTokenRight   -= dDeltaX * 0.10;

      int iLineIndex = lpline->GetContainer()->GetTokenLine(iCurrentToken);

      lpline->GetContainer()->GetTokenX_(
         iNextToken,
         &dNextTokenLeft,
         &dNextTokenRight);

      dDeltaX              = (dNextTokenRight - dNextTokenLeft);
      dNextTokenLeft       += dDeltaX * 0.50;
      dNextTokenRight      -= dDeltaX * 0.10;

      dDeltaX = (dCurrentTokenRight - dCurrentTokenLeft);

      if(bTokenLastNote)
      {
         m_dCurrentNoteLeft   = dCurrentTokenLeft + dDeltaX * dBegX;
         m_dCurrentNoteRight  = dNextTokenLeft;
      }
      else
      {
         m_dCurrentNoteLeft   = dCurrentTokenLeft + dDeltaX * dBegX;
         m_dCurrentNoteRight  = dCurrentTokenLeft + dDeltaX * dEndX;
      }

      string strLine;
      lpline->m_tokenaRaw.GetText(strLine);

      if((m_dCurrentNoteRight < m_dCurrentNoteLeft && m_iBBArrangeLine == lpline->m_iLineIndex)
         || iLineIndex == -1)
      //if(bTokenLastNote && bLineLastToken)
      {
         double d = dRate;
         if(d >= m_dBBArrangeRate) //  || !m_bPendingBBArrange)
         {
            m_bPendingBBArrange = true;
            m_dBBArrangeRate = d;
         }
         if(m_dBBArrangeRate >= 1.0)
         {
            m_bPendingBBArrange = false;
         }
      }
      else if(m_iBBArrangeLine != lpline->m_iLineIndex && strLine.has_char())
      {
         m_bPendingBBArrange = false;
         m_iBBArrangeLine = lpline->m_iLineIndex;
         m_dBBArrangeRate = 0.0;
      }

      int iBallCompress = m_sizeBall.cy * 2 / 3;
      int iBallMinHeight = m_sizeBall.cy - iBallCompress;
      int iBallMinWidth = m_sizeBall.cx;
      int iBallMaxWidth = iBallMinWidth * 3 / 2;
      int iCompressPathHeight = rectPlacement.height() * 3 / 5;

      double dx = GetSplineX(dRate, m_dCurrentNoteLeft, m_dCurrentNoteRight);
      double dy = GetSplineY(dRate, rectPlacement.height());

      int ix = (int) dx;
      int iy = m_rectClient.bottom - (int) dy + iBallMinHeight;
      int iBallHeight;
      int iBallWidth;
      bool bShadow;
      if(dy < iCompressPathHeight)
      {
         bShadow = true;
         iBallHeight = (int) (iBallMinHeight + (dy * iBallCompress/ iCompressPathHeight));
         iBallWidth = (int) (iBallMaxWidth - dy * (iBallMaxWidth - iBallMinWidth) / iCompressPathHeight);
         ix -= (iBallWidth - iBallMinWidth) / 2;
      }
      else
      {
         bShadow = false;
         iBallHeight = m_sizeBall.cy;
         iBallWidth = iBallMinWidth;
      }

      rectBall.set(
            ix,
            iy - (iBallWidth - iBallMinWidth) / 2,
            ix + iBallWidth,
            iy + iBallHeight);

      if(bDraw)
      {
         if(m_eballtype == image)
         {
            if(System.savings().is_warning(gen::resource_processing))
            {
               TRACE("KaraokeBouncingBall::to :: System is warning to save \"processing\" resource");
               TRACE("KaraokeBouncingBall::to :: Going to change ball type from \"image\" to \"vectorial ball\"");
               System.savings().clear_warning(gen::resource_processing);
               m_eballtype = Ball;
            }
            class rect rectShadow;
            double d = GetSplineY(dRate, 1.0);
            int iMidW = (int) ((iBallMinWidth / 2) + ((iBallMaxWidth - iBallMinWidth / 2) * d));
            if(iMidW >= 5 && bShadowNow)
            {
               rectShadow.left = rectBall.center().x - iMidW;
               rectShadow.right = rectBall.center().x + iMidW;
               //rectShadow.top = rectPlacement.bottom - rectShadow.width() / 5;
               rectShadow.top = m_rectClient.bottom + iBallMinHeight + (iBallMaxWidth - iBallMinWidth) / 2;
               rectShadow.bottom = rectShadow.top + rectShadow.width() / 3;
               visual::dib_sp dib(get_app());
               visual::dib_sp dib2(get_app());
               visual::dib_sp dib12(get_app());
               dib->create(rectShadow.size());
               dib2->create(m_dibBallShadow->size());
               dib12->create(rectShadow.size());
               ::ca::draw_dib_sp drawdib(get_app());
               dib->get_graphics()->SetStretchBltMode(HALFTONE);
               dib2->from(m_dibBallShadow->get_graphics());
               dib2->channel_copy(visual::rgba::channel_red, visual::rgba::channel_alpha);
               dib12->get_graphics()->SetStretchBltMode(HALFTONE);
               drawdib->draw(
                  dib->get_graphics(),
                  0,
                  0,
                  rectShadow.width(),
                  rectShadow.height(),
                  m_dibBallShadow,
                  0, 0,
                  m_dibBallShadow->width(),
                  m_dibBallShadow->height(),
                  SRCCOPY);
               drawdib->draw(
                  dib12->get_graphics(),
                  0,
                  0,
                  rectShadow.width(),
                  rectShadow.height(),
                  dib2,
                  0, 0,
                  dib2->width(),
                  dib2->height(),
                  SRCCOPY);
               dib12->channel_copy(visual::rgba::channel_alpha, visual::rgba::channel_red);
               dib12->channel_multiply(visual::rgba::channel_alpha, 1.0 - d);
               //System.imaging().blur(dib->get_graphics(), null_point(), rectBall.size(), dib->get_graphics(), null_point(), -1);
               //System.imaging().blur(dib2->get_graphics(), null_point(), rectBall.size(), dib2->get_graphics(), null_point(), -1);
               //dib->get_graphics()->SetStretchBltMode(HALFTONE);
               //dib->get_graphics()->StretchBlt(0, 0, rectBall.width(), rectBall.height(), m_dibBall->get_graphics(), 0, 0, m_dibBall->width(), m_dibBall->height(), SRCCOPY);
               System.imaging().bitmap_blend(pdc, rectShadow.top_left(), rectShadow.size(), dib->get_graphics(), null_point(), dib12->get_graphics(), null_point());
            }
            if(!bShadowNow)
            {
               visual::dib_sp dib(get_app());
               visual::dib_sp dib2(get_app());
               visual::dib_sp dib12(get_app());
               dib->create(rectBall.size());
               dib2->create(m_dibBall->size());
               dib12->create(rectBall.size());
               ::ca::draw_dib_sp drawdib(get_app());
               dib->get_graphics()->SetStretchBltMode(HALFTONE);
               dib2->from(m_dibBall->get_graphics());
               dib2->channel_copy(visual::rgba::channel_red, visual::rgba::channel_alpha);
               dib12->get_graphics()->SetStretchBltMode(HALFTONE);
               drawdib->draw(
                  dib->get_graphics(),
                  0,
                  0,
                  rectBall.width(),
                  rectBall.height(),
                  m_dibBall,
                  0, 0,
                  m_dibBall->width(),
                  m_dibBall->height(),
                  SRCCOPY);
               drawdib->draw(
                  dib12->get_graphics(),
                  0,
                  0,
                  rectBall.width(),
                  rectBall.height(),
                  dib2,
                  0, 0,
                  dib2->width(),
                  dib2->height(),
                  SRCCOPY);
               dib12->channel_copy(visual::rgba::channel_alpha, visual::rgba::channel_red);
               //System.imaging().blur(dib->get_graphics(), null_point(), rectBall.size(), dib->get_graphics(), null_point(), -1);
               //System.imaging().blur(dib2->get_graphics(), null_point(), rectBall.size(), dib2->get_graphics(), null_point(), -1);
               //dib->get_graphics()->SetStretchBltMode(HALFTONE);
               //dib->get_graphics()->StretchBlt(0, 0, rectBall.width(), rectBall.height(), m_dibBall->get_graphics(), 0, 0, m_dibBall->width(), m_dibBall->height(), SRCCOPY);
               System.imaging().bitmap_blend(pdc, rectBall.top_left(), rectBall.size(), dib->get_graphics(), null_point(), dib12->get_graphics(), null_point());
            }
         }
         else if(m_eballtype == Ball)
         {

            pdc->SelectObject(m_penBall);

            pdc->SelectObject(m_brushBall);

            pdc->FillEllipse(rectBall);

            pdc->DrawEllipse(rectBall);

         }
         else
         {
            if(dy < 5.0)
            {
               DrawIconEx(
                  (HDC)pdc->get_os_data(),
                  rectBall.left, rectBall.top,
                  m_hiconPressed,
                  rectBall.width(), rectBall.height(),
                  0, NULL, DI_NORMAL);
            }
            else
            {

               DrawIconEx(
                  (HDC)pdc->get_os_data(),
                  rectBall.left, rectBall.top,
                  m_hiconNormal,
                  rectBall.width(), rectBall.height(),
                  0, NULL, DI_NORMAL);
            }

         }
      }
      if(bDraw)
      {
         m_rectBall = rectBall;
      }

      return VMSR_SUCCESS;

   }

   void KaraokeBouncingBall::SetPlacement(LPRECT lprect)
   {
       m_rectPlacement = lprect;
       m_rectClient = m_rectPlacement;

       int cx = m_sizeBall.cx / 2;
       int cy = m_sizeBall.cy / 2;

       m_rectClient.deflate(
           cx,
           cy,
           cx,
           cy);
   }

   //void KaraokeBouncingBall::SetForegroundDC(::ca::graphics * pgraphics)
   //{
     //  pdcForeground = pgraphics;
   //}
   /*void KaraokeBouncingBall::SetTwi(CTransparentWndInterface *pTwi)
   {
       m_ptwi_ = pTwi;
   }
   void KaraokeBouncingBall::SetBackgroundDC(::ca::graphics * pgraphics)
   {
       m_lpBackgroundDC = pgraphics;
   }*/

   void KaraokeBouncingBall::SetQuarterNoteDuration(imedia::position tk)
   {
       m_tkQuarterNote = tk;
   }

   VMSRESULT KaraokeBouncingBall::Prepare()
   {
      m_iPlayingTokenIndex    = -1;
      m_iBBArrangeLine        = 0;
      m_iBBArrangeNextLine    = 0;
      m_bPendingBBArrange     = true;
      return VMSR_SUCCESS;
   }

   bool KaraokeBouncingBall::HasPendingBBArrange()
   {
       return m_bPendingBBArrange;
   }

   void KaraokeBouncingBall::ClearPendingBBArrange()
   {
       m_bPendingBBArrange = false;
   }

   double KaraokeBouncingBall::GetBBArrangeRate()
   {
       return m_dBBArrangeRate;
   }

   int KaraokeBouncingBall::GetBBArrangeLine()
   {
       return m_iBBArrangeLine;
   }

   void KaraokeBouncingBall::SetBallType(EBallType balltype)
   {
       m_eballtype = balltype;
       if(m_eballtype == icon)
       {
           ICONINFO ii;
           GetIconInfo(m_hiconNormal, &ii);
       }

   }

   void KaraokeBouncingBall::SetIcons(HICON hiconNormal, HICON hiconPressed)
   {
       m_hiconNormal = hiconNormal;
       m_hiconPressed = hiconPressed;
       SetBallType(icon);
   }

   void KaraokeBouncingBall::SetBallSize(SIZE size)
   {
      m_sizeBall = size;
   }

} // namespace kar
