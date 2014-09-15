#include "framework.h"


namespace backview
{

#define HIDOUBLETOINT(d) (((d) > (int32_t) (d)) ? ((int32_t) (d)) + 1 : (int32_t) (d))


   TransitionEffect::TransitionEffect(Main & view) :
      element(view.get_app()),
      Helper(view),
      m_tool001(view),
      m_eventStartTransition(view.get_app(), false, true),
      m_eventThreadExit(view.get_app(), false, true)
   {
      m_bRun = true;
      m_eventThreadExit.ResetEvent();
      m_bDestroy = false;
      m_pthreadRunStep = NULL;
      m_tool001.m_iStep = 0;
      m_bTransitionStepRunActive = false;
      m_bTransitionStepPostActive = false;
      m_dwTransitionStepLastRunTime = get_tick_count();
      m_dwTransitionStepPostActive = get_tick_count();
      m_dwLastTransitionTime = get_tick_count();

      m_dwLastTransitionTime = get_tick_count();

      int32_t iStart  = (int32_t) TransitionEffectFirst;
      int32_t iEnd    = (int32_t) TransitionEffectLast;

      //iStart = (int32_t) TransitionEffectSingleStep;
      //iEnd   = (int32_t) TransitionEffectSingleStep;

      //iStart  = (int32_t) TransitionEffectLinearFadingTopBottom;
      //iEnd    = (int32_t) TransitionEffectLinearFadingRightLeft;

      //iStart  = (int32_t) TransitionEffectAccumulLinearFadingTopBottom;
      //iEnd    = (int32_t) TransitionEffectAccumulLinearFadingRightLeft;

      //iStart   = (int32_t) TransitionEffectFlyInTopBottom;
      //iEnd     = (int32_t) TransitionEffectFlyInRightTop;

      //iStart   = (int32_t) TransitionEffectWipeBottom;
      //iEnd     = (int32_t) TransitionEffectWipeIn;

      //iStart   = (int32_t) TransitionEffectScaleBottom;
      //iEnd     = (int32_t) TransitionEffectScaleCenter;

      //iStart   = (int32_t) TransitionEffectpixelate_TopBottom;
      //iEnd     = (int32_t) TransitionEffectpixelate_RightLeft;

      //iStart   = (int32_t) TransitionEffectSquarypixelate_

      //iStart   = (int32_t) TransitionEffectVisual;
      //iEnd     = (int32_t) TransitionEffectVisual;

      //iStart      = (int32_t) TransitionEffectRadialUnveil;
      //iEnd      = (int32_t) TransitionEffectRadialUnveil;

      //iStart   = (int32_t) TransitionEffectpixelate_RightLeft;
      //iEnd     = (int32_t) TransitionEffectRadialUnveil;

      for(int32_t i = iStart; i <= iEnd; i++)
      {
         m_etypea.add((ETransitionEffect) i);
      }

      //iStart = iEnd = (int32_t) VisualEffectPixelExplosion;
      //iStart = iEnd = (int32_t) VisualEffectAlphaPixelExplosion;
      //iStart = iEnd = (int32_t) VisualEffectPixelExplosion2;

      //iStart = iEnd = (int32_t) VisualEffectRotateEx8;
      //iStart = iEnd = (int32_t) VisualEffectRotateEx4;
      //iStart = iEnd = (int32_t) VisualEffectRain1;
      //iStart = iEnd = (int32_t) VisualEffectRotateEx5;
      //iStart = iEnd = (int32_t) VisualEffectRotateEx6;
      //iStart = iEnd = (int32_t) VisualEffectRotateEx7;

      //iStart = iEnd = (int32_t) VisualEffectExpand8;
      //iStart = iEnd = (int32_t) VisualEffectExpand4;
      //iStart = iEnd = (int32_t) VisualEffectExpand5;
      //iStart = iEnd = (int32_t) VisualEffectExpand6;
      //iStart = iEnd = (int32_t) VisualEffectExpand7;

      //iStart = iEnd = (int32_t) VisualEffectRotateBlend;
      //iStart = iEnd = (int32_t) VisualEffectNoPrecisionRotateBlend;
      //iStart = iEnd = (int32_t) VisualEffectNoPrecisionRotatecolor_blend_;
      //iStart = iEnd = (int32_t) VisualEffectNoPrecisionRotateTrackcolor_blend_;
      //iStart = iEnd = (int32_t) VisualEffectRotateEx1;
      //iStart = iEnd = (int32_t) VisualEffectRotateEx2;
      //iStart = iEnd = (int32_t) VisualEffectRotateEx3;

      iStart   = (int32_t) VisualEffectPixelExplosion;
      iEnd     = (int32_t) VisualEffectRotateEx3;

      //iStart   = (int32_t) VisualEffectNoPrecisionRotateTrackcolor_blend_;
      //iEnd     = (int32_t) VisualEffectNoPrecisionRotateTrackcolor_blend_;

      for(int32_t i = iStart; i <= iEnd; i++)
      {
         m_iaVisual.add(i);
      }


      m_bInitialized    = false;
      m_bActive         = false;
      m_iType           = 0;
      m_iVisual         = 0;
   }

   TransitionEffect::~TransitionEffect()
   {
      m_eventThreadExit.ResetEvent();
      m_bDestroy = true;
      m_eventThreadExit.wait(seconds(2));
   }

   void TransitionEffect::StepBack()
   {
      m_bActive = false;

      Main & main = HelperGetMain();

      index iTypeOld = m_iType;
      index iTypeNew = m_iType;
      if(m_etypea[iTypeOld] == TransitionEffectVisual)
      {
         m_iVisual--;
         if(m_iVisual < 0)
         {
            m_iVisual = 0;
            iTypeNew = iTypeOld - 1;
         }
      }
      else
      {
          iTypeNew = iTypeOld - 1;
      }
      if(iTypeNew < 0)
      {
         iTypeNew = m_etypea.get_size() - 1;
         if(m_etypea[iTypeNew] == TransitionEffectVisual)
         {
            m_iVisual = main.GetVisualEffect().GetEffectCount() - 1;
         }
      }
      if(iTypeNew >= m_etypea.get_size())
         iTypeNew = m_etypea.get_size() - 1;
      if(m_etypea[iTypeNew] == TransitionEffectVisual &&
         m_etypea[iTypeOld] != TransitionEffectVisual)
      {
         m_iVisual = main.GetVisualEffect().GetEffectCount() - 1;
      }

      if(iTypeNew < 0 || iTypeNew >= m_etypea.get_size())
         m_iType = 0;
      else
         m_iType = iTypeNew;

   }

   void TransitionEffect::StepNext()
   {
      m_bActive = false;

//         Main & main = HelperGetMain();

      index iTypeOld = m_iType;
      index iTypeNew = m_iType;
      if(m_etypea[iTypeOld] == TransitionEffectVisual)
      {
         m_iVisual++;
         if(m_iVisual >= m_iaVisual.get_size())
         {
            m_iVisual = 0;
            iTypeNew = iTypeOld + 1;
         }
      }
      else
      {
          iTypeNew = iTypeOld + 1;
      }

      if(iTypeNew >= m_etypea.get_size())
      {
         iTypeNew = 0;
         if(m_etypea[iTypeNew] == TransitionEffectVisual)
         {
            m_iVisual = 0;
         }
      }
      if(iTypeNew >= m_etypea.get_size())
         iTypeNew = m_etypea.get_size() - 1;
      if(m_etypea[iTypeNew] == TransitionEffectVisual &&
         m_etypea[iTypeOld] != TransitionEffectVisual)
      {
         m_iVisual = 0;
      }

      if(iTypeNew < 0 || iTypeNew >= m_etypea.get_size())
         m_iType = 0;
      else
         m_iType = iTypeNew;

   }

   void TransitionEffect::Initialize()
   {
      Main & main = HelperGetMain();

      Graphics & graphics = main.GetGraphics();

      single_lock sl1Back(&graphics.m_mutex1Back, FALSE);


      main.OnAfterImageLoaded();
      m_bInitialized = true;
      m_bActive = true;

      HelperGetMain().DeferCheckLayout();
      m_eventStartTransition.SetEvent();

   }

   void TransitionEffect::_Final()
   {
      m_bActive = false;


      m_tool001.Finalize();
      m_bInitialized = false;

   }

   void TransitionEffect::Restart()
   {

      rect rectClient;

      Main & main = HelperGetMain();

      Interface & iface = main.GetInterface();
      iface.BackViewGetClientRect(rectClient);

      int32_t cx = rectClient.width();
      int32_t cy = rectClient.height();

      m_tool001.m_iStep = 1;
      m_tool001.m_iStepCount = -1;
      m_dwDelay = 200;

      m_tool001.Initialize(m_etypea[m_iType], cx, cy, *this);

      main.OnAfterImageLoaded();


   }

   bool TransitionEffect::TestEnd()
   {
      if(m_tool001.m_iStepCount > 1
         && m_tool001.m_iStep >= m_tool001.m_iStepCount)
      {
         m_bActive = false;
         return true;
      }

      if(!m_bActive)
         return true ;

      return false;

   }

   void TransitionEffect::End()
   {
      Main & main = HelperGetMain();
      main.ImageChangePostEvent(EventTransitionEffectFinished);

   }

   void TransitionEffect::Reset()
   {
      m_tool001.m_ia.remove_all();
      m_tool001.m_iStep = 0;
   }

   void TransitionEffect::RunStepProcLevel2()
   {

//         Main & viewinterface = HelperGetMain();

      keep <bool> keepTransitionStepRunActive(
         &m_bTransitionStepRunActive,
         true,
         false,
true);


      int32_t iRepeat = CalcRepeatCount();


      rect_array recta;

      while(!TestEnd() && iRepeat > 0)
      {
         RunStepProcLevel1(recta);
         iRepeat--;
      }

      /*rect_array * precta = new rect_array;
      precta->copy(recta);
      viewinterface.GetInterface().BackViewPostMessage(
         Interface::BackViewWparamUpdateScreenBaseRectArray,
         (LPARAM) precta);*/

      m_dwLastTransitionTime = get_tick_count();
      m_dwTransitionStepLastRunTime = get_tick_count();
      m_bTransitionStepPostActive = false;

      if(TestEnd())
      {
         End();
      }

   }

   void TransitionEffect::RunStepProcLevel1(rect_array & recta)
   {

//         Main & viewinterface = HelperGetMain();

      if(TestEnd())
         return;

      if(m_tool001.m_iStep == 1
         && m_tool001.m_ia.get_size() <= 0)
      {
         synch_lock sl(&user_mutex());

         RenderBuffer(recta);
      }
      else
      {
         if(m_tool001.m_ia.get_size() <= 0)
         {
            synch_lock sl(&user_mutex());

            RenderBuffer(recta);
         }
         else
         {
            rect rect;
            for(int32_t i = 0; i < 1 && m_tool001.m_ia.get_size(); i++)
            {
               synch_lock sl(&user_mutex());

               RenderBuffer(recta);
            }
         }
      }

      Sleep(m_dwDelay);

      m_tool001.m_iStep++;
   }

/*   void TransitionEffect::RunStep_()
   {
      m_evRunStep.SetEvent();
   }*/


   void TransitionEffect::RenderBuffer(rect_array & recta)
   {

      if(!m_bInitialized)
         Initialize();


      recta.remove_all();

      Main & main = HelperGetMain();

      if(m_etypea[m_iType] == TransitionEffectVisual)
      {
         main.GetVisualEffect().RenderBuffer(recta);
         return;
      }

      main.DeferCheckLayout();

      Interface & iface = main.GetInterface();
      rect rectClient;
      iface.BackViewGetClientRect(rectClient);

      int32_t cx = rectClient.width();
      int32_t cy = rectClient.height();

      class imaging & imaging = System.visual().imaging();

      Graphics & graphics = main.GetGraphics();

      single_lock sl1Back(&graphics.m_mutex1Back, FALSE);

      single_lock sl2Buffer(&graphics.m_mutex2Buffer, FALSE);

      if(!sl1Back.lock(millis(184)))
         return;

      if(!sl2Buffer.lock(millis(184)))
         return;

      ::draw2d::graphics_sp dcBack = graphics.GetBackDC();

      ::draw2d::graphics_sp dcBuffer = graphics.GetBufferDC();

      ::draw2d::graphics_sp dcFrame1 = graphics.GetFrame1DC();

      ::draw2d::bitmap_sp bitmapBuffer = graphics.GetBufferBitmap();

      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);

      if(dcBack.is_null() || dcBack->get_os_data() == NULL)
      {
         End();
         return;
      }
      if(dcBuffer->get_os_data() == NULL)
      {
         End();
         return;
      }


      dcBack->SelectClipRgn(NULL);
      dcBuffer->SelectClipRgn(NULL);

      if(bitmapBuffer->get_os_data() == NULL)
      {
         End();
         return;
      }

//         class size  sizeBack2 = bitmapBuffer->get_size();

      rect rectUpdate;
      switch(m_etypea[m_iType])
      {
      case TransitionEffectSingleStep:
         {
            if(m_tool001.m_iStep == m_tool001.m_iStepCount / 2)
            {
               //dcBack->FillSolidRect(100, 10, 50, 50, ARGB(20, 30, 40, 20));

               rectUpdate = rectClient;
               dcBack->BitBlt(
                  rectUpdate.left, rectUpdate.top,
                  rectUpdate.width(), rectUpdate.height(),
                  dcBuffer,
                  rectUpdate.left, rectUpdate.top,
                  SRCCOPY);

/*                  drawdib.draw(
                  dcBack,
                  rectUpdate.left, rectUpdate.top,
                  rectUpdate.width(), rectUpdate.height(),
                  graphics.GetDib(_graphics::DibBuffer),
                  rectUpdate.left, rectUpdate.top,
                  rectUpdate.width(), rectUpdate.height(),
                  SRCCOPY);
*/
               recta.add(rectUpdate);
            }
         }
         break;
      case TransitionEffectSquarypixelate_:
         {
            if(m_tool001.m_iStep > 0)
            {
               if(m_tool001.m_pointa.get_size() <= 0)
                  break;
               index iIndex = (index) System.math().RandRange(0, m_tool001.m_pointa.get_size() - 1);



               if(m_tool001.m_iStep <= 0)
                        break;;
               point point;
               try
               {
                        point = m_tool001.m_pointa.element_at(iIndex);
                        if(m_tool001.m_iStep <= 0)
                           break;
                        m_tool001.m_pointa.remove_at(iIndex);
               }
               catch(...)
               {
                        break;
               }
               POINT pointa[4];
               m_tool001.GetRotateRect(point.x, point.y, pointa);
               ::draw2d::region_sp rgnClip(allocer());
               rgnClip->create_polygon(pointa, 4, ::draw2d::fill_mode_winding);

               //dcBack->SelectClipRgn(NULL);
               dcBack->SelectClipRgn(rgnClip);
               m_tool001.GetSimplePolyBox(&rectUpdate, pointa, 4);

               /*               if(lprect != NULL)
               {
               *lprect = rectUpdate;
            }*/

               dcBack->BitBlt(
                  rectUpdate.left, rectUpdate.top,
                  rectUpdate.width(), rectUpdate.height(),
                  dcBuffer,
                  rectUpdate.left, rectUpdate.top,
                  SRCCOPY);
               /*drawdib.draw(
                  dcBack,
                  rectUpdate.left, rectUpdate.top,
                  rectUpdate.width(), rectUpdate.height(),
                  graphics.GetDib(_graphics::DibBuffer),
                  rectUpdate.left, rectUpdate.top,
                  rectUpdate.width(), rectUpdate.height(),
                  SRCCOPY);*/
               dcBack->SelectClipRgn(NULL);
               recta.add(rectUpdate);
            }
         }
         break;
      case TransitionEffectHexagonalpixelate_:
         {
            if(m_tool001.m_iStep > 0)
            {
               index iIndex = (index) System.math().RandRange(0, m_tool001.m_pointa.get_size() - 1);

               if(m_tool001.m_iStep <= 0)
                  break;
               point point;
               try
               {
                  point = m_tool001.m_pointa.element_at(iIndex);
                  if(m_tool001.m_iStep <= 0)
                     break;
                  m_tool001.m_pointa.remove_at(iIndex);
               }
               catch(...)
               {
                  break;
               }
               POINT pointa[6];
               m_tool001.GetRotateHexagon(point.x, point.y, pointa);
               ::draw2d::region_sp rgnClip(allocer());
               rgnClip->create_polygon(pointa, 6, ::draw2d::fill_mode_winding);
               dcBack->SelectClipRgn(rgnClip);
               m_tool001.GetSimplePolyBox(rectUpdate, pointa, 6);

               /*               if(lprect != NULL)
               {
               *lprect = rectUpdate;
                  }*/

               dcBack->BitBlt(
                  rectUpdate.left, rectUpdate.top,
                  rectUpdate.width(), rectUpdate.height(),
                  dcBuffer,
                  rectUpdate.left, rectUpdate.top,
                  SRCCOPY);
               dcBack->SelectClipRgn(NULL);
            }
            recta.add(rectUpdate);
         }
         break;
      case TransitionEffectCirclypixelate_:
      case TransitionEffectEllipsoidalpixelate_:
         {
            int32_t finalX = 0;
            int32_t finalY = 0;
            int32_t finalW = cx;
            int32_t finalH = cy;

            const int32_t tilesx = MAX(4, m_tool001.m_data.m_tiles.m_iTilesX);
            const int32_t tilesy = MAX(4, m_tool001.m_data.m_tiles.m_iTilesY);
//               const int32_t tiles = MAX(16, m_tool001.m_data.m_tiles.m_iTiles);


            if(m_tool001.m_iStep > 0)
            {
               if(m_tool001.m_ia.get_size() > 0)
               {
                  index iIndex = (index) System.math().RandRange(0, m_tool001.m_ia.get_size() - 1);

                  //                  SendMessage(WM_USER, USERMESSAGE_WPARAM_RAND_LPINT, (LPARAM) &iRand);

                  /*                  int32_t iIndex =
                  m_math.LinearMap(
                  0, m_tool001.m_ia.get_size() - 1,
                  iRand, 0, RAND_MAX);*/
                  if(m_tool001.m_iStep <= 0)
                     break;
                  int32_t iStep = 0;
                  try
                  {
                     iStep = m_tool001.m_ia.element_at(iIndex);
                     if(m_tool001.m_iStep <= 0)
                        break;
                     m_tool001.m_ia.remove_at(iIndex);
                  }
                  catch(...)
                  {
                     break;
                  }

                  int32_t i = iStep % tilesx;
                  int32_t j = iStep / tilesx;
                  double dUpdateH = (double) finalH / tilesy;
                  double dUpdateW = (double) finalW / tilesx;
                  double dX = dUpdateW * i;
                  double dY = dUpdateH * j;
                  rectUpdate.set(
                     (int32_t) dX,
                     (int32_t) dY,
                     (int32_t) (dX + dUpdateW + 1.0),
                     (int32_t) (dY + dUpdateH + 1.0));
               }
               else
               {
                  rectUpdate.set(finalX, finalY, finalX + finalW, finalY + finalH);
               }
               /*               if(lprect != NULL)
               {
               *lprect = rectUpdate;
                  }*/

               ::draw2d::region_sp rgnClip(allocer());
               if(m_etypea[m_iType] == TransitionEffectCirclypixelate_
                  || m_etypea[m_iType] == TransitionEffectEllipsoidalpixelate_)
               {
                  rect rectEllipse;
                  if(m_etypea[m_iType] == TransitionEffectCirclypixelate_)
                  {
                     m_tool001.FindRandomEnglobingCircle(rectUpdate, rectEllipse, 64);
                  }
                  else
                  {
                     m_tool001.FindRandomEnglobingEllipse(rectUpdate, rectEllipse, 64);
                  }
                  rectUpdate = rectEllipse;
                  rgnClip->create_oval(rectUpdate);
                  dcBack->SelectClipRgn(rgnClip);
                  dcBack->BitBlt(
                     rectUpdate.left, rectUpdate.top,
                     rectUpdate.width(), rectUpdate.height(),
                     dcBuffer,
                     rectUpdate.left, rectUpdate.top,
                     SRCCOPY);
                  dcBack->SelectClipRgn(NULL);
               }
               else
               {
                  dcBack->BitBlt(
                     rectUpdate.left, rectUpdate.top,
                     rectUpdate.width(), rectUpdate.height(),
                     dcBuffer,
                     rectUpdate.left, rectUpdate.top,
                     SRCCOPY);

               }
               recta.add(rectUpdate);
            }

         }
         break;
      case TransitionEffectLinearFadingBottomTop:
      case TransitionEffectLinearFadingTopBottom:
      case TransitionEffectLinearFadingLeftRight:
      case TransitionEffectLinearFadingRightLeft:
         {

            int32_t finalX = 0;
            int32_t finalY = 0;
            int32_t finalW = cx;
            int32_t finalH = cy;

            ::rect & rectUpdate = m_tool001.m_rect;

            if(m_tool001.m_iStep == 1)
            {

               graphics.GetDib(_graphics::DibTemp1)->from(pdibBack);

            }

            pdibBack->from(graphics.GetDib(_graphics::DibTemp1));

            double dRate = ((double) (m_tool001.m_iStep + 1.0)) / ((double) m_tool001.m_iStepCount);

            rectUpdate.set(finalX, finalY, finalX + finalW, finalY + finalH);

            dcBack->set_alpha_mode(::draw2d::alpha_mode_blend);

            dcBack->alpha_blend(rectUpdate.size(), dcBuffer, dRate);

            recta.add(rectUpdate);

         }
         break;
      case TransitionEffectAccumulLinearFadingBottomTop:
      case TransitionEffectAccumulLinearFadingTopBottom:
      case TransitionEffectAccumulLinearFadingLeftRight:
      case TransitionEffectAccumulLinearFadingRightLeft:
         {
            int32_t finalX = 0;
            int32_t finalY = 0;
            int32_t finalW = cx;
            int32_t finalH = cy;

            ::rect & rectUpdate = m_tool001.m_rect;

            const int32_t iTileCount = m_tool001.m_data.m_sliceframe.m_iTileCount;
            //            const int32_t iFrameCount = m_tool001.m_data.m_sliceframe.m_iFrameCount;
            const int32_t iTileMax = iTileCount - 1;
            int32_t iGroupCount = m_tool001.m_data.m_sliceframe.m_iGroupCount;

            index iIndex = m_tool001.m_iStep - 1;
            iIndex = MIN(iIndex, m_tool001.m_pointa.get_size() -1);
            if(iIndex >= 0)
            {
               point point = m_tool001.m_pointa.element_at(iIndex);
               int32_t iTile = point.x;
               //int32_t iFrame = point.y;
               int32_t iGroup = point.y;
               //int32_t iGroup = iTile - iFrame;
               double dRate = (double) iTile / iTileMax;
               double dRateMinus = (double) (iTile - 1) / iTileMax;



               //int32_t iFrameComplement = iFrameCount - iFrame;
               //int32_t iFrameExp = iFrameComplement * iFrameComplement * iFrameComplement;
               //int32_t iFrameStd = iFrame * 2;
               //               int32_t iFrameStd = iFrame;
               //>int32_t iFrameEx = iFrameStd * iFrameStd * iFrameStd;
               //int32_t iFrameEx = iFrameStd * iFrameStd;
               //               int32_t iFrameEx = iFrameStd;
               //               int32_t iFrameStdCount = iFrameCount - 1;
               //int32_t iFrameCountEx = iFrameStdCount * iFrameStdCount * iFrameStdCount;
               //int32_t iFrameCountEx = iFrameStdCount * iFrameStdCount;
               //               int32_t iFrameCountEx = iFrameStdCount;
               double dAlpha = m_tool001.m_dAlpha;
               /*            double dAlpha = viewinterface.m_math.LinearMap(
               (double) 35, (double) 255,
               (double) iFrameEx,
               (double) 0, (double) iFrameCountEx);*/
               //dAlpha /= 8.0;

               //m_dwDelay = (uint32_t) MIN(10, dAlpha * 10 / 255);
             //  m_dwDelay = 0;

               int32_t iAlphaAccumul = 0;;


               if(m_tool001.m_iStep > 0
                  && m_tool001.m_iStepCount > 0)
               {
                  m_tool001.Start(
                     cx, cy,
                     dRateMinus, dRate);
                  m_tool001.Go();
                  iAlphaAccumul = m_tool001.m_ia.element_at(iTile);
                  //                  if(iFrame == iFrameStdCount)
                  if(iGroup == 0)
                  {
                     dAlpha = 255.0;
                  }
                  else
                  {
                     //dAlpha = MAX(1.0, 255.0 / pow((double) (iGroup), 2.0));
            //         dAlpha = 255.0 * pow((double) (iGroupCount - iGroup) / iGroupCount, 2.5);
//
  //                               if(iFrame == iFrameCount - 1)
    //        {
      //         dAlpha = 255.0;
        //    }
          //  else
            {
               double dExp = 3.4;
               double dMin = 4.0;
               dAlpha = 140.0 * ::pow((iGroupCount - 1.0 - iGroup) / (iGroupCount - 1.0), dExp) + dMin;
            }

                     /*                     dAlpha = iAlphaAccumul / 2.0 + MAX(5.0, 255.0 / iFrameCount);
                     dAlpha = dAlpha / 255.0;
                     dAlpha *= dAlpha;
                     dAlpha *= dAlpha;
                     dAlpha *= 255.0;
                     dAlpha = iAlphaAccumul / 2.0 + MAX(2.0, 127.0 / iFrameCount);
                     dAlpha = MAX(2.0, MIN(255.0, dAlpha));*/
                  }
                  if(iAlphaAccumul <= 255)
                  {
                     iAlphaAccumul = (int32_t) ((dAlpha * 255.0 +
                        iAlphaAccumul * (255.0 - dAlpha)) / 255);
                  }
                  if(iAlphaAccumul >= 255)
                  {
                     m_tool001.m_ia.element_at(iTile) = 256;
                  }
                  else
                  {
                     m_tool001.m_ia.element_at(iTile) = iAlphaAccumul;
                  }
               }
               else
               {
                  rectUpdate.set(finalX, finalY, finalX + finalW, finalY + finalH);
               }
               /*            if(lprect != NULL)
               {
               *lprect = rectUpdate;
            }*/



               if(iAlphaAccumul >= 0
                  && iAlphaAccumul <= 255)
               {
/*                  imaging.bitmap_blend(
                     dcBack,
                     rectUpdate.left,
                     rectUpdate.top,
                     rectUpdate.width(),
                     rectUpdate.height(),
                     dcBuffer,
                     rectUpdate.left,
                     rectUpdate.top,
                     (BYTE) dAlpha);*/

                  graphics.GetDib(_graphics::DibTemp1)->create(rectUpdate.width(), rectUpdate.height());
                  graphics.GetDib(_graphics::DibTemp2)->create(rectUpdate.width(), rectUpdate.height());

                  graphics.GetDib(_graphics::DibTemp1)->get_graphics()->BitBlt(
                     0, 0,
                     rectUpdate.width(),
                     rectUpdate.height(),
                     dcBack,
                     rectUpdate.left,
                     rectUpdate.top,
                     SRCCOPY);

                  graphics.GetDib(_graphics::DibTemp2)->get_graphics()->BitBlt(
                     0, 0,
                     rectUpdate.width(),
                     rectUpdate.height(),
                     dcBuffer,
                     rectUpdate.left,
                     rectUpdate.top,
                     SRCCOPY);

                  imaging.bitmap_blend(
                     graphics.GetDib(_graphics::DibTemp1)->get_graphics(),
                     null_point(),
                     rectUpdate.size(),
                     graphics.GetDib(_graphics::DibTemp2)->get_graphics(),
                     null_point(),
                     (BYTE) dAlpha);

                  dcBack->from(
                     rectUpdate.top_left(),
                     rectUpdate.size(),
                     graphics.GetDib(_graphics::DibTemp1)->get_graphics(),
                     null_point(),
                     SRCCOPY);


               }
               recta.add(rectUpdate);
            }
         }
         break;
      case TransitionEffectFlyInBottomTop:
      case TransitionEffectFlyInTopBottom:
      case TransitionEffectFlyInLeftRight:
      case TransitionEffectFlyInRightLeft:
      case TransitionEffectFlyInLeftTop:
      case TransitionEffectFlyInLeftBottom:
      case TransitionEffectFlyInRightBottom:
      case TransitionEffectFlyInRightTop:
         {
//               int32_t finalX = 0;
//               int32_t finalY = 0;
//               int32_t finalW = cx;
//               int32_t finalH = cy;

            const int32_t iFrameCount = MAX(1, m_tool001.m_data.m_sliceframe.m_iFrameCount);
            const int32_t iFrameMax = iFrameCount -1;



            ::index iFrame = m_tool001.m_iStep - 1;
            double dFrameStd = 1.0 - ((double) iFrame / iFrameMax);
            double dRate = 1.0 - dFrameStd * dFrameStd;
            double dComplementRate = 1.0 - dRate;

            rect rectBound;
            graphics.GetFinalPlacement(rectBound);

            rect rect(rectBound);

            ::gcom::space space;
            space.deviate(rect, rectBound, GetDirection(m_etypea[m_iType]), dComplementRate);

            class rect rectIntersect;
            rectIntersect.intersect(rect, rectBound);

            dcBack->BitBlt(
               rectIntersect.left,
               rectIntersect.top,
               rectIntersect.width(),
               rectIntersect.height(),
               dcBuffer,
               rectIntersect.left - rect.left + rectBound.left,
               rectIntersect.top - rect.top + rectBound.top,
               SRCCOPY);

            recta.add(rectIntersect);

         }
         break;
      case TransitionEffectWipeTop:
      case TransitionEffectWipeBottom:
      case TransitionEffectWipeRight:
      case TransitionEffectWipeLeft:
         {
//               int32_t finalX = 0;
//               int32_t finalY = 0;
//               int32_t finalW = cx;
//               int32_t finalH = cy;

            const int32_t iFrameCount = MAX(4, m_tool001.m_data.m_sliceframe.m_iFrameCount);
            const int32_t iFrameMax = iFrameCount;

            ::index iFrame = m_tool001.m_iStep - 1;
            double dFrameStd = 1.0 - ((double) iFrame / iFrameMax);
            double dFrameStdPlus = 1.0 - ((double) (iFrame + 1) / iFrameMax);
            double dRate = 1.0 - dFrameStd * dFrameStd;

            double dRatePlus = 1.0 - dFrameStdPlus * dFrameStdPlus;


            rect rect;
            graphics.GetFinalPlacement(rect);

            ::gcom::space space;

            space.slice(rect, rectClient, GetDirection(get_type()), dRate, dRatePlus);

            dcBack->BitBlt(
               rect.left,
               rect.top,
               rect.width(),
               rect.height(),
               dcBuffer,
               rect.left,
               rect.top,
               SRCCOPY);
            recta.add(rect);
         }
         break;
      case TransitionEffectWipeTopLeft:
      case TransitionEffectWipeTopRight:
      case TransitionEffectWipeBottomLeft:
      case TransitionEffectWipeBottomRight:
         {
//               int32_t finalX = 0;
//               int32_t finalY = 0;
//               int32_t finalW = cx;
//               int32_t finalH = cy;

            const int32_t iFrameCount = MAX(4, m_tool001.m_data.m_sliceframe.m_iFrameCount);
            const int32_t iFrameMax = iFrameCount - 1;

            ::index iFrame = m_tool001.m_iStep - 1;
//               double dFrameStdMinus = 1.0 - ((double) (iFrame - 1)/ iFrameMax);
            double dFrameStd = 1.0 - ((double) iFrame / iFrameMax);
            double dFrameStdPlus = 1.0 - ((double) (iFrame + 1) / iFrameMax);
//               double dRateMinus = 1.0 - dFrameStdMinus * dFrameStdMinus;
            double dRate = 1.0 - dFrameStd * dFrameStd;
            double dRatePlus = 1.0 - dFrameStdPlus * dFrameStdPlus;

            ::rect rectA;
            ::rect rectB;
            ::rect rectC;
//               ::rect & rectUpdate = m_tool001.m_rect;




            rect rect;
            graphics.GetFinalPlacement(rect);


            ::gcom::space space;
            space.slice(rectA, rectB, rectC, rect, GetDirection(get_type()), dRate, dRatePlus);


            dcBack->BitBlt(
               rectA.left,
               rectA.top,
               rectA.width(),
               rectA.height(),
               dcBuffer,
               rectA.left,
               rectA.top,
               SRCCOPY);
            dcBack->BitBlt(
               rectB.left,
               rectB.top,
               rectB.width(),
               rectB.height(),
               dcBuffer,
               rectB.left,
               rectB.top,
               SRCCOPY);
            dcBack->BitBlt(
               rectC.left,
               rectC.top,
               rectC.width(),
               rectC.height(),
               dcBuffer,
               rectC.left,
               rectC.top,
               SRCCOPY);
            recta.add(rectA);
            recta.add(rectB);
            recta.add(rectC);
         }
         break;
      case TransitionEffectWipeCenter:
         {

            const int32_t iFrameCount = MAX(4, m_tool001.m_data.m_sliceframe.m_iFrameCount);
            const int32_t iFrameMax = iFrameCount - 1;

            ::index iFrame = m_tool001.m_iStep - 1;
            double dFrameStd = 1.0 - ((double) iFrame / iFrameMax);
            double dRate = 1.0 - dFrameStd * dFrameStd;

            rect rect;
            graphics.GetFinalPlacement(rect);

            ::gcom::space space;
            space.scale(rect, dRate);


            dcBack->BitBlt(
               rect.left,
               rect.top,
               rect.width(),
               rect.height(),
               dcBuffer,
               rect.left,
               rect.top,
               SRCCOPY);
            recta.add(rect);
         }
         break;
      case TransitionEffectWipeIn:
         {

            const int32_t iFrameCount = MAX(4, m_tool001.m_data.m_sliceframe.m_iFrameCount);
            const int32_t iFrameMax = iFrameCount - 1;

            ::index iFrame = m_tool001.m_iStep - 1;
            double dFrameStd = 1.0 - ((double) iFrame / iFrameMax);
            double dFrameStdPlus = 1.0 - ((double) (iFrame + 1) / iFrameMax);
            double dRate = 1.0 - dFrameStd * dFrameStd;
            double dRatePlus = 1.0 - dFrameStdPlus * dFrameStdPlus;

            ::rect rectA;
            ::rect rectB;
            ::rect rectC;
            ::rect rectD;

            class rect rect;
            graphics.GetFinalPlacement(rect);

            ::gcom::space space;
            space.wipe_in(
               rectA,
               rectB,
               rectC,
               rectD,
               rect,
               1.0 - dRatePlus,
               1.0 - dRate);

            dcBack->BitBlt(
               rectA.left,
               rectA.top,
               rectA.width(),
               rectA.height(),
               dcBuffer,
               rectA.left,
               rectA.top,
               SRCCOPY);
            dcBack->BitBlt(
               rectB.left,
               rectB.top,
               rectB.width(),
               rectB.height(),
               dcBuffer,
               rectB.left,
               rectB.top,
               SRCCOPY);
            dcBack->BitBlt(
               rectC.left,
               rectC.top,
               rectC.width(),
               rectC.height(),
               dcBuffer,
               rectC.left,
               rectC.top,
               SRCCOPY);
            dcBack->BitBlt(
               rectD.left,
               rectD.top,
               rectD.width(),
               rectD.height(),
               dcBuffer,
               rectD.left,
               rectD.top,
               SRCCOPY);
            recta.add(rectA);
            recta.add(rectB);
            recta.add(rectC);
            recta.add(rectD);
         }
         break;
      case TransitionEffectWipeMidHorizontal:
         {

            const int32_t iFrameCount = MAX(4, m_tool001.m_data.m_sliceframe.m_iFrameCount);
            const int32_t iFrameMax = iFrameCount - 1;

            ::index iFrame = m_tool001.m_iStep - 1;
            double dFrameStd = 1.0 - ((double) iFrame / iFrameMax);
            double dRate = dFrameStd * dFrameStd;

            rect rect;
            graphics.GetFinalPlacement(rect);

            double dy = (rect.height() / 2) * dRate;

            rect.top += (long) dy;
            rect.bottom -= (long) dy;

            dcBack->BitBlt(
               rect.left,
               rect.top,
               rect.width(),
               rect.height(),
               dcBuffer,
               rect.left,
               rect.top,
               SRCCOPY);
            recta.add(rect);
         }
         break;
      case TransitionEffectWipeMidVertical:
         {

            const int32_t iFrameCount = MAX(4, m_tool001.m_data.m_sliceframe.m_iFrameCount);
            const int32_t iFrameMax = iFrameCount - 1;

            ::index iFrame = m_tool001.m_iStep - 1;
            double dFrameStd = 1.0 - ((double) iFrame / iFrameMax);
            double dRate = dFrameStd * dFrameStd;

            rect rect;
            graphics.GetFinalPlacement(rect);

            double dx = (rect.width() / 2) * dRate;

            rect.left += (long) dx;
            rect.right -= (long) dx;

            dcBack->BitBlt(
               rect.left,
               rect.top,
               rect.width(),
               rect.height(),
               dcBuffer,
               rect.left,
               rect.top,
               SRCCOPY);
            recta.add(rect);
         }
         break;
      case TransitionEffectScaleBottom:
      case TransitionEffectScaleTop:
      case TransitionEffectScaleRight:
      case TransitionEffectScaleLeft:
      case TransitionEffectScaleTopLeft:
      case TransitionEffectScaleTopRight:
      case TransitionEffectScaleBottomLeft:
      case TransitionEffectScaleBottomRight:
         {
//               int32_t finalX = 0;
//               int32_t finalY = 0;
//               int32_t finalW = cx;
//               int32_t finalH = cy;

            const int32_t iFrameCount = MAX(4, m_tool001.m_data.m_sliceframe.m_iFrameCount);
            const int32_t iFrameMax = iFrameCount - 1;

            ::index iFrame = m_tool001.m_iStep - 1;
            double dFrameStd = 1.0 - ((double) iFrame / iFrameMax);

            double dRate = dFrameStd * dFrameStd * dFrameStd;

            rect rectBound;
            graphics.GetFinalPlacement(rectBound);


            class rect rect(rectBound);

            ::gcom::space space;

            space.deviate(rect, rectClient, GetDirection(get_type()), dRate);

            rect.intersect(rect, rectBound);

            dcBack->SetStretchBltMode(HALFTONE);
            dcBack->StretchBlt(
               rect.left,
               rect.top,
               rect.width(),
               rect.height(),
               dcBuffer,
               rectBound.left,
               rectBound.top,
               rectBound.width(),
               rectBound.height(),
               SRCCOPY);

            dcBack->SelectClipRgn(NULL);

            recta.add(rect);
         }
         break;
      case TransitionEffectScaleCenter:
         {
//               int32_t finalX = 0;
//               int32_t finalY = 0;
//               int32_t finalW = cx;
//               int32_t finalH = cy;

            const int32_t iFrameCount = MAX(4, m_tool001.m_data.m_sliceframe.m_iFrameCount);
            const int32_t iFrameMax = iFrameCount - 1;

            ::index iFrame = m_tool001.m_iStep - 1;
            double dFrameStd = 1.0 - ((double) iFrame / iFrameMax);

            double dRate = dFrameStd * dFrameStd;

            rect rect = rectClient;

            ::gcom::space space;

            space.scale(rect, dRate);



            dcBack->StretchBlt(
               rectClient.left,
               rectClient.top,
               rectClient.width(),
               rectClient.height(),
               dcBuffer,
               rect.left,
               rect.top,
               rect.width(),
               rect.height(),
               SRCCOPY);
            dcBack->SelectClipRgn(NULL);
            recta.add(rectClient);
         }
         break;
      case TransitionEffectpixelate_BottomTop:
      case TransitionEffectpixelate_TopBottom:
      case TransitionEffectpixelate_LeftRight:
      case TransitionEffectpixelate_RightLeft:
         {


            rect rectBound;
            graphics.GetFinalPlacement(rectBound);



            int32_t finalX = rectBound.left;
            int32_t finalY = rectBound.top;
            int32_t finalW = rectBound.width();
            int32_t finalH = rectBound.height();


            rect rectDest;

            rectDest.left = 0;
            rectDest.top = 0;
            rectDest.right = finalW;
            rectDest.bottom = finalH;


            ::rect rectUpdate;

            int32_t c1 = m_tool001.m_data.m_alphapixelate.m_c1;
            ::index iIndex = m_tool001.m_iStep - 1;
            ::index iSizeIndex = m_tool001.m_pointa[iIndex].x;
            int32_t iSize = m_tool001.m_ia[iSizeIndex];
            int32_t nextc = m_tool001.m_pointa[iIndex].y;
            int32_t ca;

            if(iIndex <= 0 || nextc == 0)
            {
               ca = 0;
            }
            else
            {
               ca = m_tool001.m_pointa[iIndex - 1].y;
            }


            m_dwDelay = 84;

            ::draw2d::dib_sp pdib = graphics.GetDib(7);

            if(iIndex >= 0)
            {
               double dRateMinus = (double) ca / (double) c1;
               double dRate = (double) nextc / (double) c1;

               if(dRateMinus < 0.0)
                  dRateMinus = 0.0;
               else if(dRateMinus > 1.0)
                  dRateMinus = 1.0;

               if(dRate < 0.0)
                  dRate = 0.0;
               else if(dRate > 1.0)
                  dRate = 1.0;

               if(dRateMinus > dRate)
                  dRateMinus = dRate;

               double dAlpha;

               {
                  double dBeginSpanTime = 0.30;
                  double dEndSpanTime = 0.05;
                  double dTime = (double) m_tool001.m_iStep / (double) m_tool001.m_iStepCount;
                  double dRate = 8.0;
                  double dMiddle = 0.87;
                  double dMiddleAlpha = 107.0;

                  if(dTime < dMiddle)
                  {
                     if(dTime < dBeginSpanTime)
                     {
                        dAlpha = 0.0;
                     }
                     else
                     {
                        dAlpha = dMiddleAlpha * ::pow(2.7182, ((dTime * (1.0 / (1.0 - (dBeginSpanTime + dEndSpanTime)))) - dMiddle) * dRate);
                     }
                  }
                  else
                  {
                     if(dTime > (1.0 - dEndSpanTime))
                     {
                        dAlpha = 255.0;
                     }
                     else
                     {
                        dAlpha = dMiddleAlpha + (255.0 - dMiddleAlpha) * (1.0 - ::pow(2.7182, (dMiddle - (dTime * (1.0 / (1.0 - (dBeginSpanTime + dEndSpanTime))))) * dRate));
                     }
                  }
               }




               if(nextc == 0)
               {

                  m_tool001.m_data.m_alphapixelate.m_iSizeIndex = (int32_t) iSizeIndex;

/*                     ::draw2d::dib_sp pdib2 = graphics.GetDib(2);

                  ::draw2d::dib_sp pdib3 = graphics.GetDib(3);

                  ::draw2d::dib_sp pdib4 = graphics.GetDib(4);

                  ::draw2d::dib_sp pdib5 = graphics.GetDib(5);

                  ::draw2d::dib_sp pdib6 = graphics.GetDib(6);

                  pdib->create(xPixelMod, yPixelMod);

                  pdib2->create(xPixelMod, yPixelMod);

                  pdib3->create(finalW, finalH);

                  pdib4->create(finalW, finalH);

                  pdib5->create(xPixelMod, yPixelMod);

                  pdib6->create(xPixelMod, yPixelMod);

                  pdib5->get_graphics()->SetStretchBltMode(0);
                  pdib6->get_graphics()->SetStretchBltMode(0);
                  dcBuffer->SetStretchBltMode(0);
                  dcFrame1.SetStretchBltMode(0);

                  pdib5->get_graphics()->StretchBlt(
                     0, 0,
                     xPixelMod, yPixelMod,
                     dcBuffer,
                     finalX, finalY,
                     finalW, finalH,
                     SRCCOPY);

                  pdib6->get_graphics()->StretchBlt(
                     0, 0,
                     xPixelMod, yPixelMod,
                     &dcFrame1,
                     finalX, finalY,
                     finalW, finalH,
                     SRCCOPY);


                  pdib3->get_graphics()->SetStretchBltMode(0);
                  pdib4->get_graphics()->SetStretchBltMode(0);
                  pdib5->get_graphics()->SetStretchBltMode(0);
                  pdib6->get_graphics()->SetStretchBltMode(0);

                  pdib3->get_graphics()->StretchBlt(
                     0, 0,
                     finalW, finalH,
                     pdib5->get_graphics(),
                     0, 0,
                     xPixelMod, yPixelMod,
                     SRCCOPY);

                  pdib4->get_graphics()->StretchBlt(
                     0, 0,
                     finalW, finalH,
                     pdib6->get_graphics(),
                     0, 0,
                     xPixelMod, yPixelMod,
                     SRCCOPY);

                  pdib->get_graphics()->SetStretchBltMode(0);
                  pdib2->get_graphics()->SetStretchBltMode(0);
                  pdib3->get_graphics()->SetStretchBltMode(0);
                  pdib4->get_graphics()->SetStretchBltMode(0);

                  pdib->get_graphics()->StretchBlt(
                     0, 0,
                     xPixelMod, yPixelMod,
                     pdib3->get_graphics(),
                     0, 0,
                     finalW, finalH,
                     SRCCOPY);

                  pdib2->get_graphics()->StretchBlt(
                     0, 0,
                     xPixelMod, yPixelMod,
                     pdib4->get_graphics(),
                     0, 0,
                     finalW, finalH,
                     SRCCOPY);*/

                  pdib->create(finalW, finalH);

                  pdib->get_graphics()->BitBlt(0, 0, finalW, finalH, dcFrame1, 0, 0, SRCCOPY);

                  const int32_t dSpan = 16;

                  if(iSizeIndex == m_tool001.m_ia.get_size() - 1)
                  {
                     dAlpha = 255.0;
                  }
                  else
                  {
                     if(dAlpha < dSpan)
                        dAlpha = 0.0;
                     else if(dAlpha > 255 - dSpan)
                        dAlpha = 255.0;
                     else
                     {
                        dAlpha = (dAlpha - dSpan) * 255.0 / (255.0 - dSpan * 2);
                     }
                  }

                  imaging.bitmap_blend(
                     pdib->get_graphics(),
                     null_point(),
                     size(finalW, finalH),
                     dcBuffer,
                     point(finalX, finalY),
                     (byte)(dAlpha));

                  pdib->pixelate(iSize);
               }

               switch(m_etypea[m_iType])
               {
               case TransitionEffectpixelate_TopBottom:
                  {
                     m_tool001.GetSliceRect(finalW, finalH, rectDest, ::backview::TransitionEffect::Tool001::AlignTop, dRateMinus, dRate);
                  }
                  break;
               case TransitionEffectpixelate_BottomTop:
                  {
                     m_tool001.GetSliceRect(finalW, finalH, rectDest, ::backview::TransitionEffect::Tool001::AlignBottom, dRateMinus, dRate);
                  }
                  break;
               case TransitionEffectpixelate_LeftRight:
                  {
                     m_tool001.GetSliceRect(finalW, finalH, rectDest, ::backview::TransitionEffect::Tool001::AlignLeft, dRateMinus, dRate);
                  }
                  break;
               case TransitionEffectpixelate_RightLeft:
                  {
                     m_tool001.GetSliceRect(finalW, finalH, rectDest, ::backview::TransitionEffect::Tool001::AlignRight, dRateMinus, dRate);
                  }
                  break;
                  default:
                     break;
               }

               rectDest.offset(rectBound.top_left());

               rectDest.right +=1;
               rectDest.bottom +=1;


               dcBack->BitBlt(
                  rectDest.left,
                  rectDest.top,
                  MIN(rectDest.width(), finalW),
                  MIN(rectDest.height(), finalH),
                  pdib->get_graphics(),
                  rectDest.left - rectBound.left,
                  rectDest.top - rectBound.top,
                  SRCCOPY);


               recta.add(rectDest);

            }
         }
         break;
         case TransitionEffectRadialUnveil:
            {
//                  ::draw2d::dib_sp pdibT1 = graphics.GetDib(1977); // Radial Fill (White, Radius = 256 pixels)
               ::draw2d::dib_sp pdibT2 = graphics.GetDib(1977); // Radial Fill (White, Radius = 256 pixels)

               ::index iIndex = m_tool001.m_iStep - 1;
               m_tool001.m_data.m_radialunveil.m_iRadius += m_tool001.m_data.m_radialunveil.m_iRadiusIncrement;

               m_dwDelay = m_tool001.m_pointa[iIndex].y;

               int32_t r = m_tool001.m_pointa[iIndex].x;
               int32_t d = r * 2;



               int32_t xm = cx / 2;
               int32_t ym = cy / 2;
               int32_t x1 = MAX(0, xm - r);
               int32_t x2 = MIN(cx, xm + r);
               int32_t y1 = MAX(0, ym - r);
               int32_t y2 = MIN(cy, ym + r);


               int32_t xOff = 0;
               int32_t yOff = 0;
               if(r > xm)
                  xOff = pdibT2->m_size.cx * (r - xm) / d;

               if(r > ym)
                  yOff = pdibT2->m_size.cy * (r - ym) / d;

               int32_t wWindow = MIN(cx, d);
               int32_t hWindow = MIN(cy, d);

//                  double xrate = (double) wWindow / d;
//                  double yrate = (double) hWindow / d;

               ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
               ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
               //::draw2d::dib_sp pdib3 = graphics.GetDib(_graphics::DibTemp3);

               pdib1->create(wWindow, hWindow);
               pdib2->create(wWindow, hWindow);
               //pdib3->create(wWindow, hWindow);

               //pdib1->get_graphics()->SetStretchBltMode(HALFTONE);
               pdib1->get_graphics()->StretchBlt(
                  0,
                  0,
                  wWindow,
                  hWindow,
                  pdibT2->get_graphics(),
                  xOff,
                  yOff,
                  pdibT2->m_size.cx - xOff * 2,
                  pdibT2->m_size.cy - yOff * 2,
                  SRCCOPY);

               pdib2->get_graphics()->BitBlt(
                  0, 0,
                  wWindow, hWindow,
                  dcBuffer,
                  x1, y1,
                  SRCCOPY);


               pdib2->channel_from(visual::rgba::channel_alpha,  pdib1);

               /*drawdib.draw(
                  pdib1->get_graphics(),
                  0, 0,
                  wWindow, hWindow,
                  pdibT2,
                  xOff, yOff,
                  pdibT2->width() - 2 * xOff -1,
                  pdibT2->width() - 2 * yOff -1, 0);*/


               /*dc2.BitBlt(0, 0, wWindow, hWindow, pdib1->get_graphics(), 0, 0, SRCCOPY);
               dc2.BitBlt(0, 0, wWindow, hWindow, NULL, 0, 0, DSTINVERT);

               dc3.FillSolidRect(0, 0, wWindow, hWindow, 0xff000000);
               dc2.BitBlt(0, 0, wWindow, hWindow, &dc3, 0, 0, SRCAND);*/

               /*StretchDIBits(
                  dc2,
                  0, 0,
                  wWindow, hWindow,
                  xOff, yOff,
                  pdibT2->width() - 2 * xOff,
                  pdibT2->height() - 2 * yOff,
                  pdibT2->m_pcolorref,
                  &pdibT2->m_Info,
                  DIB_RGB_COLORS,
                  SRCCOPY);*/

//                  ::draw2d::dib_sp pdibBuffer = graphics.GetDib(100);
               /*StretchDIBits(
                  pdib1->get_graphics(),
                  0, 0,
                  wWindow, hWindow,
                  x1, y1,
                  wWindow, hWindow,
                  pdibBuffer->m_pcolorref,
                  &pdibBuffer->m_Info,
                  DIB_RGB_COLORS,
                  SRCPAINT);*/



               //dcBack->BitBlt(x1, y1, wWindow, hWindow, &dcFrame1, x1, y1, SRCCOPY);
               //dcBack->BitBlt(x1, y1, wWindow, hWindow, pdib1->get_graphics(),
                 // x1, y1, SRCCOPY);

               //dcBack->BitBlt(x1, y1, wWindow, hWindow, pdib1->get_graphics(),
                 // x1, y1, SRCCOPY);

               dcBack->set_alpha_mode(::draw2d::alpha_mode_set);

               dcBack->BitBlt(x1, y1, wWindow, hWindow, pdib2->get_graphics(), 0, 0, SRCCOPY);


               /*drawdib.draw(
                  dcBack,
                  x1, y1,
                  d, d,
                  pdib1,
                  0, 0,
                  d, d,
                  DDF_HALFTONE);*/
               //dcBack->BitBlt(xm - r, ym - r, 2 * r, 2 * r, pdib1->get_graphics(), 0, 0, SRCCOPY);
               rectUpdate.set(x1, y1, x2, y2);
               recta.add(rectUpdate);
            }
            break;
         default:
            break;

      }

      single_lock sl(&graphics.m_mutex4Transfer, TRUE);
      ::draw2d::graphics_sp dcTransfer = graphics.GetTransferDC();
      ::draw2d::region_sp rgnTransferClip(allocer());
      rgnTransferClip->create_rect(graphics.m_rectFinalPlacement);
      //dcTransfer.SelectClipRgn(rgnTransferClip);

      for(int32_t i = 0; i < recta.get_size(); i++)
      {
         ::rect rectTransfer = recta[i];

         dcTransfer->BitBlt(
            rectTransfer.left, rectTransfer.top,
            rectTransfer.width(), rectTransfer.height(),
            dcBack,
            rectTransfer.left, rectTransfer.top,
            SRCCOPY);

      }
      dcTransfer->SelectClipRgn(NULL);
   }

   int32_t TransitionEffect::CalcRepeatCount()
   {
      int32_t iStepRepeatCount = m_tool001.m_iStepRepeatCount;
      switch(get_type())
      {
      case TransitionEffectpixelate_BottomTop:
      case TransitionEffectpixelate_TopBottom:
      case TransitionEffectpixelate_LeftRight:
      case TransitionEffectpixelate_RightLeft:
         {
            const int32_t c1 = m_tool001.m_data.m_alphapixelate.m_c1;
//               const int32_t c2 = m_tool001.m_data.m_alphapixelate.m_c2;

            ::index iIndex = m_tool001.m_iStep - 1;
            int32_t iSizeIndex = m_tool001.m_pointa[iIndex].x;
            int32_t iSize = m_tool001.m_ia[iSizeIndex];

            if(iSize < 64)
               iSize = 64;

            ////iStepRepeatCount = 1c1 / (iSize * 8);
            //iStepRepeatCount = 1;
//               int32_t dwTotalTime = 1000;
            int32_t iStepCount = c1 / iSize;
            if(c1 % iSize == 0)
               iStepCount++;
            int32_t iStartStep = m_tool001.m_pointa2[iIndex].y;
            int32_t iStep = (int32_t) (iIndex - iStartStep);
            iStepRepeatCount = iStepCount / 8;
            if(iStep > iStepCount - iStepCount / 4)
               iStepRepeatCount = iStepCount - iStep - 1;
         }
         break;
      default:
         break;

      }
      iStepRepeatCount = MAX(1, iStepRepeatCount);
      return iStepRepeatCount;

   }

   bool TransitionEffect::IsActive()
   {
      return m_tool001.m_iStep > 0;
   }

   void TransitionEffect::OnNoPrecisionThousandMillisTimer()
   {
      if(m_pthreadRunStep == NULL)
         m_pthreadRunStep = CreateRunStepThread();
   }


   void TransitionEffect::OnTimer()
   {
      return;

      Main & main = HelperGetMain();

      uint32_t dwTime = get_tick_count();
      if(dwTime - m_dwTransitionStepLastRunTime >= 5 + m_dwDelay
         && !m_bTransitionStepRunActive
         && (!m_bTransitionStepPostActive
         || dwTime - m_dwTransitionStepPostActive >= 2000))
      {
      /*            if(dwTime - m_dwTransitionStepLastRunTime >= 200)
      {
            TRACE("dwTime - m_dwTransitionStepLastRunTime >= 200 %d\n",  dwTime - m_dwTransitionStepLastRunTime);
            }
            if(!m_bTransitionStepRunActive)
            {
            TRACE("!m_bTransitionStepRunActive\n");
            }
            if(!m_bTransitionStepPostActive)
            {
            TRACE("!m_bTransitionStepPostActive\n");
            }
            if(dwTime - m_dwTransitionStepPostActive >= 2000)
            {
            TRACE("!m_bTransitionStepPostActive % d\n", dwTime - m_dwTransitionStepPostActive);
      }*/
         m_bTransitionStepPostActive = true;
         m_dwTransitionStepPostActive = get_tick_count();
         main.GetInterface().BackViewPostMessage(Interface::MessageBackViewDequeue, 18, 0);
      }
      else
      {
         ASSERT(TRUE);
      }

   }


   ::thread * TransitionEffect::CreateRunStepThread()
   {

      return __begin_thread(get_app(), ThreadProcRunStep, this, ::multithreading::priority_normal, 0, 0, NULL);

   }

   void TransitionEffect::_Init()
   {

      synch_lock slUserMutex(&user_mutex());

      Main & main = HelperGetMain();

      Graphics & graphics = main.GetGraphics();

      //ASSERT(graphics.GetBufferDC().get_os_data() != NULL);

      single_lock sl1Back(&graphics.m_mutex1Back, FALSE);

      ::draw2d::graphics_sp dcFrame1 = graphics.GetFrame1DC();
      ::draw2d::graphics_sp dcTransfer = graphics.GetTransferDC();

      Interface & iface = main.GetInterface();

      rect rectClient;
      iface.BackViewGetClientRect(rectClient);

      int32_t cx = rectClient.width();
      int32_t cy = rectClient.height();

      single_lock sl(&graphics.m_mutex4Transfer, TRUE);

      if(dcTransfer.is_set()
         && dcTransfer->get_os_data() != NULL)
      {
         dcFrame1->BitBlt(0, 0, cx, cy, dcTransfer, 0, 0, SRCCOPY);
      }
      sl.unlock();
      //graphics.GetDib(_graphics::DibFrame1)->from(dcBack, (HBITMAP) *dcBack->get_current_bitmap());

      m_tool001.m_iStep = 1;
      m_tool001.m_iStepCount = -1;
      m_dwDelay = 200;

      m_tool001.Initialize(get_type(), cx, cy, *this);
   }

   UINT c_cdecl TransitionEffect::ThreadProcRunStep(LPVOID lpParameter)
   {
      TransitionEffect * peffect = (TransitionEffect *) lpParameter;
      srand((uint32_t) time(NULL));
      manual_reset_event event(peffect->get_app());

      event.ResetEvent();

//         ::multimedia::e_result mmr;
//         int32_t iResolution = 25;
      UINT uiRet = 0;
      try
      {
         while(peffect->m_bRun)
         {
            while(!peffect->m_bActive && peffect->m_bRun)
            {
               if(peffect->m_bDestroy)
                  break;
               peffect->m_eventStartTransition.wait(seconds(0.5));
               peffect->m_eventStartTransition.ResetEvent();
            }
            if(peffect->m_bDestroy)
               break;
            if(!peffect->m_bRun)
               break;

            peffect->_Init();
            if(peffect->m_bDestroy)
               break;
            if(!peffect->m_bRun)
               break;

            while(!peffect->TestEnd())
            {
               if(peffect->m_bDestroy)
                  break;
            if(!peffect->m_bRun)
               break;

               /*mmr = timeSetEvent(
                  MAX(natural(iResolution), peffect->m_dwDelay),
                  iResolution,  // 5 ms resolution
                  (LPTIMECALLBACK) (HANDLE) event,
                  NULL,
                  TIME_ONESHOT | TIME_CALLBACK_EVENT_SET);*/

               event.wait(millis(5));

               peffect->RunStepProcLevel2();

               if(peffect->TestEnd())
                  break;
            if(!peffect->m_bRun)
               break;

               //event.wait(seconds(3));
               event.ResetEvent();
            }
            if(peffect->m_bDestroy)
               break;
            if(!peffect->m_bRun)
               break;
            peffect->_Final();
            peffect->StepNext();
         }
      }
      catch(...)
      {
         try
         {
            peffect->m_pthreadRunStep = NULL;
         }
         catch(...)
         {
         }
         uiRet = (UINT) -3;
      }
      peffect->m_eventThreadExit.SetEvent();
      return uiRet;
   }

   ETransitionEffect TransitionEffect::get_type()
   {
      if(m_iType < 0
         || m_iType >= m_etypea.get_size())
         return TransitionEffectInvalid;
      return m_etypea[m_iType];
   }

   ::gcom::e_align TransitionEffect::GetAlign(ETransitionEffect eeffect)
   {
      switch(eeffect)
      {
      case TransitionEffectFlyInBottomTop:
         return ::gcom::align_top;
      case TransitionEffectFlyInTopBottom:
         return ::gcom::align_bottom;
      case TransitionEffectFlyInLeftRight:
         return ::gcom::align_right;
      case TransitionEffectFlyInRightLeft:
         return ::gcom::align_left;
      case TransitionEffectFlyInLeftTop:
         return ::gcom::align_top_right;
      case TransitionEffectFlyInLeftBottom:
         return ::gcom::align_bottom_right;
      case TransitionEffectFlyInRightBottom:
         return ::gcom::align_bottom_left;
      case TransitionEffectFlyInRightTop:
         return ::gcom::align_top_left;
      default:
         return ::gcom::align_none;
      }

   }

   ::gcom::e_direction TransitionEffect::GetDirection(ETransitionEffect eeffect)
   {
      switch(eeffect)
      {
      case TransitionEffectFlyInBottomTop:
         return ::gcom::direction_top;
      case TransitionEffectFlyInTopBottom:
         return ::gcom::direction_bottom;
      case TransitionEffectFlyInLeftRight:
         return ::gcom::direction_right;
      case TransitionEffectFlyInRightLeft:
         return ::gcom::direction_left;
      case TransitionEffectFlyInLeftTop:
         return ::gcom::direction_top_right;
      case TransitionEffectFlyInLeftBottom:
         return ::gcom::direction_bottom_right;
      case TransitionEffectFlyInRightBottom:
         return ::gcom::direction_bottom_left;
      case TransitionEffectFlyInRightTop:
         return ::gcom::direction_top_left;
      case TransitionEffectWipeTop:
         return ::gcom::direction_top;
      case TransitionEffectWipeBottom:
         return ::gcom::direction_bottom;
      case TransitionEffectWipeRight:
         return ::gcom::direction_right;
      case TransitionEffectWipeLeft:
         return ::gcom::direction_left;
      case TransitionEffectWipeTopLeft:
         return ::gcom::direction_top_left;
      case TransitionEffectWipeTopRight:
         return ::gcom::direction_top_right;
      case TransitionEffectWipeBottomLeft:
         return ::gcom::direction_bottom_left;
      case TransitionEffectWipeBottomRight:
         return ::gcom::direction_bottom_right;
      case TransitionEffectScaleTop:
         return ::gcom::direction_top;
      case TransitionEffectScaleBottom:
         return ::gcom::direction_bottom;
      case TransitionEffectScaleRight:
         return ::gcom::direction_right;
      case TransitionEffectScaleLeft:
         return ::gcom::direction_left;
      case TransitionEffectScaleTopLeft:
         return ::gcom::direction_top_left;
      case TransitionEffectScaleTopRight:
         return ::gcom::direction_top_right;
      case TransitionEffectScaleBottomLeft:
         return ::gcom::direction_bottom_left;
      case TransitionEffectScaleBottomRight:
         return ::gcom::direction_bottom_right;
      default:
         return ::gcom::direction_none;
      }

   }

} // namespace backview








