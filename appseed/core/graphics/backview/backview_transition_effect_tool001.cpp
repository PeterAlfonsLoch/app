#include "framework.h"


namespace backview
{


   TransitionEffect::Tool001::Tool001(Main & viewinterface) :
      element(viewinterface.get_app()),
      Helper(viewinterface)
   {
   }

   #define HIDOUBLETOINT(d) (((d) > (int32_t) (d)) ? ((int32_t) (d)) + 1 : (int32_t) (d))

   void TransitionEffect::Tool001::Start(
      int32_t cx, int32_t cy, double dRate, double dRateEx)
   {
      m_cx = cx;
      m_cy = cy;
      m_dRate = dRate;
      m_dRateEx = dRateEx;
   }

   void TransitionEffect::Tool001::Initialize(ETransitionEffect eeffect, int32_t cx, int32_t cy, TransitionEffect & effect)
   {
//         Main & viewinterface = HelperGetMain();

      m_iStepRepeatCount = 1;
      m_etransitioneffect = eeffect;
      m_cx = cx;
      m_cy = cy;
      m_iFrame = -1;
      switch(eeffect)
      {
      case TransitionEffectSingleStep:
         {
            m_iStepCount = 200;
            HelperGetMain().GetTransitionEffect().m_dwDelay = 50;
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
            const int32_t iFrameCount = 24;
            m_data.m_sliceframe.m_iFrameCount = iFrameCount;
            m_iStepCount = iFrameCount + 1;
            HelperGetMain().GetTransitionEffect().m_dwDelay = 50;
         }
         break;
      case TransitionEffectWipeTop:
      case TransitionEffectWipeBottom:
      case TransitionEffectWipeRight:
      case TransitionEffectWipeLeft:
         {
            HelperGetMain().GetTransitionEffect().m_dwDelay = 50;
            int32_t iFrameCount = MAX(4, cy / 16);
            m_data.m_sliceframe.m_iFrameCount = iFrameCount;
            m_iStepCount = iFrameCount + 1;
         }
         break;
      case TransitionEffectWipeBottomRight:
      case TransitionEffectWipeTopRight:
      case TransitionEffectWipeBottomLeft:
      case TransitionEffectWipeTopLeft:
         {

            const int32_t iFrameCount = MAX(4, cy / 32);
            m_data.m_sliceframe.m_iFrameCount = iFrameCount;
            m_iStepCount = iFrameCount + 1;
         }
         break;
      case TransitionEffectWipeCenter:
      case TransitionEffectWipeIn:
      case TransitionEffectWipeMidHorizontal:
      case TransitionEffectWipeMidVertical:
         {
            const int32_t iFrameCount = MAX(4, cy / 32);
            m_data.m_sliceframe.m_iFrameCount = iFrameCount;
            m_iStepCount = iFrameCount + 1;
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
      case TransitionEffectScaleCenter:
         {
            effect.m_dwDelay = 60;
            const int32_t iFrameCount = MAX(4, cy / 16);
            m_data.m_sliceframe.m_iFrameCount = iFrameCount;
            m_iStepCount = iFrameCount;
         }
         break;
      case TransitionEffectCirclypixelate_:
      case TransitionEffectEllipsoidalpixelate_:
         {

            const int32_t tilesx = MAX(4, cx / 48);
            const int32_t tilesy = MAX(4, cy / 48);
            const int32_t tiles = tilesx * tilesy;

            m_data.m_tiles.m_iTilesX = tilesx;
            m_data.m_tiles.m_iTilesY = tilesy;
            m_data.m_tiles.m_iTiles = tiles;

            m_ia.allocate(tiles);
            for(int32_t i = 0; i < tiles; i++)
            {
               m_ia.element_at(i) = i;
            }
            m_iStepCount = tiles + 1;
            effect.m_dwDelay = 10;
         }
         break;

      case TransitionEffectSquarypixelate_:
         {
            m_phi = System.math().RandRange(70, 110) * 3.1415 / 180.0;
            POINT pointaBigRect[4];
            GetRect(pointaBigRect, rect(0, 0, cx, cy));
            m_size.cx = 64;
            m_size.cy = 64;
            System.geometry().rotate((m_cx / 2), (m_cy / 2), pointaBigRect, 4, m_phi);
            rect rectBigRect;
            GetSimplePolyBox(rectBigRect, pointaBigRect, 4);
            int32_t iDimension = MAX(rectBigRect.width(), rectBigRect.height());
            int32_t imax = m_size.cx == 0 ? iDimension : (iDimension / (m_size.cx * 2)) + 1;
            int32_t jmax = m_size.cy == 0 ? iDimension : (iDimension / (m_size.cy * 2)) + 1;
            POINT pointaRect[4];
            rect rect;
            class rect rectClient(0, 0, m_cx, m_cy);
            for(int32_t i =  -imax; i <= imax; i++)
            {
               for(int32_t j = -jmax; j <= jmax; j++)
               {
                  GetRotateRect(i, j, pointaRect);
                  GetSimplePolyBox(rect, pointaRect, 4);
                  if(rect.intersect(rectClient, rect))
                  {
                     m_pointa.add(point(i, j));
                  }
               }
            }
            m_iStepCount = m_pointa.get_size() + 1;
            effect.m_dwDelay = 10;
         }
         break;
      case TransitionEffectHexagonalpixelate_:
         {
            effect.m_dwDelay = 10;
            m_phi = System.math().RandRange(70, 110) * 3.1415 / 180.0;
            POINT pointaBigRect[4];
            GetRect(pointaBigRect, rect(0, 0, cx, cy));
            System.geometry().rotate((m_cx / 2), (m_cy / 2), pointaBigRect, 4, m_phi);
            rect rectBigRect;
            GetSimplePolyBox(rectBigRect, pointaBigRect, 4);
            m_iRadius = 48;
            int32_t & iRadius = m_iRadius;
            int32_t iDimension = MAX(rectBigRect.width(), rectBigRect.height());
            int32_t mCount = ((int32_t) ((iDimension / (2.0 + 3.0 * iRadius)) + 2)) + 2;
            int32_t nCount = ((int32_t) HIDOUBLETOINT(iDimension / (iRadius * sqrt(3.0)))) + 2;
            int32_t mExCount = mCount + 1;
            int32_t nExCount = nCount + 1;
            int32_t imax = (mCount + mExCount) / 2;
            int32_t jmax = (nCount + nExCount) / 2;
            POINT pointaHexagon[6];
            rect rect;
            class rect rectClient(0, 0, m_cx, m_cy);
            for(int32_t i =  -imax; i <= imax; i++)
            {
               for(int32_t j = -jmax; j <= jmax; j++)
               {
                  GetRotateHexagon(i, j,  pointaHexagon);
                  GetSimplePolyBox(rect, pointaHexagon, 6);
                  if(rect.intersect(rectClient, rect))
                  {
                     m_pointa.add(point(i, j));
                  }
               }
            }
            m_iStepCount = m_pointa.get_size() + 1;
         }
         break;
      case TransitionEffectAccumulLinearFadingBottomTop:
      case TransitionEffectAccumulLinearFadingTopBottom:
      case TransitionEffectAccumulLinearFadingLeftRight:
      case TransitionEffectAccumulLinearFadingRightLeft:
         {
            m_iStepRepeatCount = 128;

            effect.m_dwDelay = 5;

            //double dPow = 1.0 / 2.5;
            //const int32_t iMaxGroupCount = 256;
            const int32_t iMaxGroupCount = 127;
            const int32_t iTileCount = MAX(4, cy / 8);
            int32_t iGroupCount = MIN(256, iMaxGroupCount);
            const int32_t iFrameCount = iTileCount;

            //m_dAlpha = ceil(255.0 / pow(iGroupCount, dPow));

            m_data.m_sliceframe.m_iTileCount = iTileCount;
            m_data.m_sliceframe.m_iFrameCount = iFrameCount;
            m_data.m_sliceframe.m_iGroupCount = iGroupCount;
//               int32_t iTileExCount = MAX(iTileCount - iFrameCount + 1, 0);
            for(int32_t iFrame = - iGroupCount; iFrame < iFrameCount; iFrame++)
            {
               for(int32_t iGroup =  0; iGroup < iGroupCount; iGroup++)
               {
                  int32_t iTile = iGroup + iFrame;
                  if(iTile >= 0
                     && iTile < iTileCount)
                  {
                     m_pointa.add(point(iTile, iGroup));
                  }
               }
            }
            m_ia.allocate(iTileCount);
            for(int32_t i = 0; i < iTileCount; i++)
            {
               m_ia.element_at(i) = 0;
            }
            m_iStepCount = m_pointa.get_size() + 1;
         }

         break;
      case TransitionEffectLinearFadingBottomTop:
      case TransitionEffectLinearFadingTopBottom:
      case TransitionEffectLinearFadingLeftRight:
      case TransitionEffectLinearFadingRightLeft:
         {
            effect.m_dwDelay = 84;
            m_iStepRepeatCount = 1;
            const int32_t iTileCount = 1;
            const int32_t iFrameCount = 49;
            m_data.m_sliceframe.m_iTileCount = iTileCount;
            m_data.m_sliceframe.m_iFrameCount = iFrameCount;
            m_iStepCount = iTileCount * iFrameCount + 1;
         }
         break;
      case TransitionEffectpixelate_BottomTop:
      case TransitionEffectpixelate_TopBottom:
      case TransitionEffectpixelate_LeftRight:
      case TransitionEffectpixelate_RightLeft:
         {
            m_iStepRepeatCount = 1;

            effect.m_dwDelay = 200;

            int32_t c1 = 0;
            int32_t c2 = 0;

            switch(eeffect)
            {
               case TransitionEffectpixelate_BottomTop:
               case TransitionEffectpixelate_TopBottom:
                  c1 = cy;
                  c2 = cx;
                  break;
               case TransitionEffectpixelate_LeftRight:
               case TransitionEffectpixelate_RightLeft:
                  c1 = cx;
                  c2 = cy;
                  break;
               default:
                  ASSERT(FALSE);
                  break;
            }

            m_data.m_alphapixelate.m_c1 = c1;
            m_data.m_alphapixelate.m_c2 = c2;


            int32_t iSize;

            {
               double dSize;
               double dMaxSize = c1;
               double dMinSize = 1.0;
               double dRate = sqrt(2.0);

               for(dSize = dMinSize; dSize <= dMaxSize; dSize *= dRate)
               {
                   m_ia.add((int32_t) dSize);
               }

               for(dSize /= dRate; dSize >= dMinSize; dSize /= dRate)
               {
                   m_ia.add((int32_t) dSize);
               }

            }



            for(int32_t i = 0; i < m_ia.get_size(); i++)
            {

               iSize = m_ia[i];

               ASSERT(iSize >= 1);

               if(iSize < 64)
                  iSize = 64;

               index j = 0;

               index iStartIndex = m_pointa.get_size();

               for(; j < c1; j += iSize)
               {
                  m_pointa.add(point(i, j));
                  m_pointa2.add(point(iSize, iStartIndex));
               }

               m_pointa.add(point(i, c1));
               m_pointa2.add(point(iSize, iStartIndex));

            }

            m_iStepCount = m_pointa.get_size() + 1;
            m_data.m_alphapixelate.m_iSizeIndex = -1;
         }
         break;
      case TransitionEffectRadialUnveil:
         {
            m_data.m_radialunveil.m_iRadiusIncrement = 20;
            m_data.m_radialunveil.m_iRadius = 0;
            m_pointa.remove_all();

            int32_t c1 = MAX(cx, cy) * 3 / 2;
            int32_t dim = 1;
            int32_t ca = 0;
            while(dim < c1)
            {
               m_pointa.add(point(dim, 50));
               dim += m_data.m_radialunveil.m_iRadiusIncrement + ca;
               ca += 10;
            }
            m_iStepCount = m_pointa.get_size();
            m_iStepRepeatCount = 1;

            effect.m_dwDelay = 50;

         }
         break;
      case TransitionEffectVisual:
         {
            m_iStepRepeatCount = 1;

         switch(effect.m_iVisual)
         {
         case VisualEffectRotateBlend:
            m_iStepCount = 360;
            break;
         case VisualEffectNoPrecisionRotateBlend:
            m_iStepCount = 360;
            break;
         case VisualEffectNoPrecisionRotatecolor_blend_:
            m_iStepCount = 480;
            break;
         case VisualEffectNoPrecisionRotateTrackcolor_blend_:
            m_iStepCount = 720;
            break;
         case VisualEffectRotateEx1:
            m_iStepCount = 720;
            break;
         case VisualEffectRotateEx2:
            m_iStepCount = 720;
            break;
         case VisualEffectRotateEx3:
            m_iStepCount = 720;
            break;
         case VisualEffectRotateEx4:
            m_iStepCount = 600;
            break;
         case VisualEffectRain1:
            m_iStepCount = 900;
            break;
         case VisualEffectRotateEx5:
            m_iStepCount = 500;
            break;
         case VisualEffectRotateEx6:
            m_iStepCount = 500;
            break;
         case VisualEffectRotateEx7:
            m_iStepCount = 600;
            break;
         case VisualEffectRotateEx8:
            m_iStepCount = 600;
            break;
         case VisualEffectPixelExplosion:
            m_iStepCount = 50;
            break;
         case VisualEffectPixelExplosion2:
            m_iStepCount = 50;
            break;
         case VisualEffectAlphaPixelExplosion:
            m_iStepCount = 50;
            break;
         default:
            m_iStepCount = 50;
            break;
         }

            m_iStepCount *= 2;
            effect.m_dwDelay = 84;

         }
         break;
      default:
         break;
      }
   }


   void TransitionEffect::Tool001::Go()
   {
      ETransitionEffect etransitioneffect = m_etransitioneffect;

      const int32_t & cx = m_cx;
      const int32_t & cy = m_cy;
//         const double dRate = m_dRate;
//         const double dRateEx = m_dRateEx;
      rect & rectUpdate = m_rect;
      point & point = m_point;
      rect & rectA = m_rectA;
      rect & rectB = m_rectB;

      switch(etransitioneffect)
      {
      case TransitionEffectLinearFadingTopBottom:
         {
            GetSliceRect(rectUpdate, AlignTop);
         }
         break;
      case TransitionEffectLinearFadingBottomTop:
         {
            GetSliceRect(rectUpdate, AlignBottom);
         }
         break;
      case TransitionEffectLinearFadingLeftRight:
         {
            GetSliceRect(rectUpdate, AlignLeft);
         }
         break;
      case TransitionEffectLinearFadingRightLeft:
         {
            GetSliceRect(rectUpdate, AlignRight);
         }
         break;
      case TransitionEffectAccumulLinearFadingTopBottom:
         {
            GetSliceRect(rectUpdate, AlignTop);
         }
         break;
      case TransitionEffectAccumulLinearFadingBottomTop:
         {
            GetSliceRect(rectUpdate, AlignBottom);
         }
         break;
      case TransitionEffectAccumulLinearFadingLeftRight:
         {
            GetSliceRect(rectUpdate, AlignLeft);
         }
         break;
      case TransitionEffectAccumulLinearFadingRightLeft:
         {
            GetSliceRect(rectUpdate, AlignRight);
         }
         break;
      case TransitionEffectFlyInTopBottom:
         {
            GetRect(rectUpdate, AlignTop);
            point.x = 0;
            point.y = rectUpdate.bottom - cy;
         }
         break;
      case TransitionEffectFlyInBottomTop:
         {
            GetRect(rectUpdate, AlignBottom);
            point.x = 0;
            point.y = 0;
         }
         break;
      case TransitionEffectFlyInLeftRight:
         {
            GetRect(rectUpdate, AlignLeft);
            point.x = rectUpdate.right - cx;
            point.y = 0;
         }
         break;
      case TransitionEffectFlyInRightLeft:
         {
            GetRect(rectUpdate, AlignRight);
            point.x = 0;
            point.y = 0;
         }
         break;
      case TransitionEffectFlyInLeftBottom:
         {
            GetRect(rectUpdate, AlignTopRight);
            point.x = rectUpdate.right - cx;
            point.y = rectUpdate.bottom - cy;
         }
         break;
      case TransitionEffectFlyInLeftTop:
         {
            GetRect(rectUpdate, AlignRightBottom);
            point.x = cx - rectUpdate.right;
            point.y = 0;
         }
         break;
      case TransitionEffectFlyInRightBottom:
         {
            GetRect(rectUpdate, AlignLeftTop);
            point.x = 0;
            point.y = rectUpdate.bottom - cy;
         }
         break;
      case TransitionEffectFlyInRightTop:
         {
            GetRect(rectUpdate, AlignBottomLeft);
            point.x = 0;
            point.y = 0;
         }
         break;
      case TransitionEffectWipeTopRight:
      case TransitionEffectWipeBottomRight:
      case TransitionEffectWipeTopLeft:
      case TransitionEffectWipeBottomLeft:
         {
            GetRectAB(rectA, rectB);
         }
         break;
      case TransitionEffectWipeCenter:
      case TransitionEffectWipeIn:
      case TransitionEffectWipeMidHorizontal:
      case TransitionEffectWipeMidVertical:
         {
            GetRect(rectUpdate, AlignCenter);
         }
         break;
      case TransitionEffectScaleBottom:
         {
            GetRect(rectA, AlignTop);
            rectB.set(
               0, 0,
               cx, cy);
         }
         break;
      case TransitionEffectScaleTop:
         {
            GetRect(rectA, AlignBottom);
            rectB.set(
               0, 0,
               cx, cy);
         }
         break;
      case TransitionEffectScaleRight:
         {
            GetRect(rectA, AlignLeft);
            rectB.set(
               0, 0,
               cx, cy);
         }
         break;
      case TransitionEffectScaleLeft:
         {
            GetRect(rectA, AlignRight);
            rectB.set(
               0, 0,
               cx, cy);
         }
         break;
      case TransitionEffectScaleTopRight:
         {
            GetRect(rectA, AlignTopRight);
            rectB.set(
               0, 0,
               cx, cy);
         }
         break;
      case TransitionEffectScaleBottomRight:
         {
            GetRect(rectA, AlignRightBottom);
            rectB.set(
               0, 0,
               cx, cy);
         }
         break;
      case TransitionEffectScaleTopLeft:
         {
            GetRect(rectA, AlignLeftTop);
            rectB.set(
               0, 0,
               cx, cy);
         }
         break;
      case TransitionEffectScaleBottomLeft:
         {
            GetRect(rectA, AlignBottomLeft);
            rectB.set(
               0, 0,
               cx, cy);
         }
         break;
      case TransitionEffectScaleCenter:
         {
            GetRect(rectA, AlignCenter);
            rectB.set(
               0, 0,
               cx, cy);
         }
         break;
      case TransitionEffectWipeTop:
      case TransitionEffectWipeBottom:
      case TransitionEffectWipeRight:
      case TransitionEffectWipeLeft:
         {
            GetRect(rectUpdate);
         }
         break;
      case TransitionEffectpixelate_TopBottom:
         {
            GetSliceRect(rectUpdate, AlignTop);
         }
         break;
      case TransitionEffectpixelate_BottomTop:
         {
            GetSliceRect(rectUpdate, AlignBottom);
         }
         break;
      case TransitionEffectpixelate_LeftRight:
         {
            GetSliceRect(rectUpdate, AlignLeft);
         }
         break;
      case TransitionEffectpixelate_RightLeft:
         {
            GetSliceRect(rectUpdate, AlignRight);
         }
         break;
      default:
         ASSERT(FALSE);
         break;
      }
   }

   void TransitionEffect::Tool001::GetRect(LPRECT lprect)
   {
      GetRect(lprect, m_dRate, m_dRateEx);
   }

   void TransitionEffect::Tool001::GetRect(LPRECT lprect, double dRate, double dRateEx)
   {
      const int32_t & cx = m_cx;
      const int32_t & cy = m_cy;
//         rect & rectUpdate = m_rect;
//         point & point = m_point;
//         rect & rectA = m_rectA;
//         rect & rectB = m_rectB;
      switch(m_etransitioneffect)
      {
      case TransitionEffectWipeBottom:
         {
            lprect->left = 0;
            lprect->right = lprect->left + cx;
            lprect->top = (int32_t) (dRate * cy);
            lprect->bottom = (int32_t) (dRateEx * cy);
         }
         break;
      case TransitionEffectWipeTop:
         {
            lprect->left = 0;
            lprect->right = lprect->left + cx;
            lprect->top = (int32_t) ((1.0 - dRateEx) * cy);
            lprect->bottom = (int32_t) (1.0 - dRate) * cy;
         }
         break;
      case TransitionEffectWipeRight:
         {
            lprect->left =  (int32_t) (dRate * cx);
            lprect->right =  (int32_t) (dRateEx * cx);
            lprect->top = 0;
            lprect->bottom = lprect->top + cy;;
         }
         break;
      case TransitionEffectWipeLeft:
         {
            lprect->left =  (int32_t) ((1.0 - dRateEx) * cx);
            lprect->right =  (int32_t) ((1.0 - dRate) * cx);
            lprect->top = 0;
            lprect->bottom = lprect->top + cy;;
         }
         break;
      case TransitionEffectWipeTopRight:
         {
            GetRect(lprect, AlignTopRight, dRate);
         }
         break;
      case TransitionEffectWipeBottomRight:
         {
            GetRect(lprect, AlignRightBottom, dRate);
         }
         break;
      case TransitionEffectWipeTopLeft:
         {
            GetRect(lprect, AlignLeftTop, dRate);
         }
         break;
      case TransitionEffectWipeBottomLeft:
         {
            GetRect(lprect, AlignBottomLeft, dRate);
         }
         break;
      case TransitionEffectWipeCenter:
         {
            GetRect(lprect, AlignCenter, dRate);
         }
         break;
      case TransitionEffectWipeIn:
         {
            GetRect(lprect, AlignCenterOut, dRate);
         }
         break;
      default:
         ASSERT(FALSE);
         break;
      }

   }


   void TransitionEffect::Tool001::GetRectAB(LPRECT lprectA, LPRECT lprectB)
   {
//         const int32_t & cx = m_cx;
//         const int32_t & cy = m_cy;
      const double dRate = m_dRate;
      const double dRateEx = m_dRateEx;
      rect & rectUpdate = m_rect;
//         point & point = m_point;

      rect rectUpdatePrevious;

      GetRect(rectUpdatePrevious, dRate, dRate);
      GetRect(rectUpdate, dRateEx, dRateEx);

      *lprectA = rectUpdate;
      *lprectB = rectUpdate;


      switch(m_etransitioneffect)
      {
      case TransitionEffectWipeTopRight:
         {
            lprectA->left     = rectUpdatePrevious.right;
            lprectB->right    = lprectA->left;
            lprectB->top      = rectUpdatePrevious.bottom;
         }
         break;
      case TransitionEffectWipeBottomRight:
         {
            lprectB->bottom   = rectUpdatePrevious.top;
            lprectA->left     = rectUpdatePrevious.right;;
            lprectA->top      = lprectB->bottom;
         }
         break;
      case TransitionEffectWipeTopLeft:
         {
            lprectA->right = rectUpdatePrevious.left;
            lprectB->left = lprectA->right;
            lprectB->top = rectUpdatePrevious.bottom;
         }
         break;
      case TransitionEffectWipeBottomLeft:
         {
            lprectB->bottom   = rectUpdatePrevious.top;
            lprectA->right    = rectUpdatePrevious.left;
            lprectA->top      = lprectB->bottom;
         }
         break;
      default:
         ASSERT(FALSE);
         break;
      }
   }

   void TransitionEffect::Tool001::GetRectABCD(LPRECT lprectA, LPRECT lprectB, LPRECT lprectC, LPRECT lprectD)
   {
      rect & rectUpdate = m_rect;
      const double dRate = m_dRate;
      const double dRateEx = m_dRateEx;

      rect rectUpdatePrevious;

      GetRect(rectUpdatePrevious, dRate, dRate);
      GetRect(rectUpdate, dRateEx, dRateEx);

      switch(m_etransitioneffect)
      {
      case TransitionEffectWipeCenter:
      case TransitionEffectWipeIn:
         {
            GetSliceRect(lprectA, AlignLeft);
            GetSliceRect(lprectB, AlignTop);
            GetSliceRect(lprectC, AlignRight);
            GetSliceRect(lprectD, AlignBottom);
            ::IntersectRect(lprectB, lprectB, rectUpdatePrevious);
            ::IntersectRect(lprectD, lprectD, rectUpdatePrevious);
         }
         break;
      default:
         ASSERT(FALSE);
         break;
      }
   }
   void TransitionEffect::Tool001::GetRect(
      LPRECT lprect,
      EAlign ealign)
   {
      GetRect(lprect, ealign, m_dRate);
   }

   void TransitionEffect::Tool001::GetRect(
      LPRECT lprect,
      EAlign ealign,
      double dRate)
   {
      GetRect(lprect, ealign, m_cx, m_cy, dRate);
   }

   void TransitionEffect::Tool001::GetRect(
      LPRECT   lprect,
      EAlign   ealign,
      int32_t      cx,
      int32_t      cy,
      double   dRate)
   {

      switch(ealign)
      {
      case AlignTop:
         {
            lprect->left = 0;
            lprect->right = lprect->left + cx;
            lprect->top = (int32_t) (dRate * cy);
            lprect->bottom = cy;
         }
         break;
      case AlignBottom:
         {
            lprect->left = 0;
            lprect->right = lprect->left + cx;
            lprect->top = 0;
            lprect->bottom = (int32_t) (1.0 - dRate) * cy;
         }
         break;
      case AlignLeft:
         {
            lprect->left =  0;
            lprect->right =  (int32_t) (dRate * cx);
            lprect->top = 0;
            lprect->bottom = lprect->top + cy;;
         }
         break;
      case AlignRight:
         {
            lprect->left =  (int32_t) ((1.0 - dRate) * cx);
            lprect->right =  cx;
            lprect->top = 0;
            lprect->bottom = lprect->top + cy;;
         }
         break;
      case AlignTopRight:
         {
            lprect->left = 0;
            lprect->right = (int32_t) (dRate * cx);
            lprect->top = 0;
            lprect->bottom = (int32_t) (dRate * cy);
         }
         break;
      case AlignRightBottom:
         {
            lprect->left = 0;
            lprect->right = (int32_t) (dRate * cx);
            lprect->top = (int32_t) ((1.0 - dRate) * cy);
            lprect->bottom = cy;
         }
         break;
      case AlignLeftTop:
         {
            lprect->left = (int32_t) ((1.0 - dRate) * cx);
            lprect->right =  cx;
            lprect->top = 0;
            lprect->bottom = (int32_t) (dRate * cy);
         }
         break;
      case AlignBottomLeft:
         {
            lprect->left =  (int32_t) ((1.0 - dRate) * cx);
            lprect->right =  cx;
            lprect->top = (int32_t) ((1.0 - dRate) * cy);
            lprect->bottom = cy;;
         }
         break;
      case AlignCenter:
         {
            double dHalfRate = dRate / 2.0;
            lprect->left =  (int32_t) ((0.5 - dHalfRate) * (cx));
            lprect->right =  (int32_t) (dHalfRate * cx);
            lprect->top = (int32_t) ((0.5 - dHalfRate) * (cy));
            lprect->bottom = (int32_t) (dHalfRate * cy);
         }
         break;
      case AlignCenterOut:
         {
            double dHalfRate = 0.5 - (dRate / 2.0);
            lprect->left =  (int32_t) ((0.5 - dHalfRate) * (cx));
            lprect->right =  (int32_t) (dHalfRate * cx);
            lprect->top = (int32_t) ((0.5 - dHalfRate) * (cy));
            lprect->bottom = (int32_t) (dHalfRate * cy);
         }
         break;
      default:
         ASSERT(FALSE);
         break;
      }

   }

   void TransitionEffect::Tool001::GetSliceRect(
      LPRECT lprect,
      EAlign ealign)
   {
      GetSliceRect(lprect, ealign, m_dRate, m_dRateEx);
   }

   void TransitionEffect::Tool001::GetSliceRect(
      LPRECT   lprect,
      EAlign   ealign,
      double   dRate,
      double   dRatePlus // greater rate
      )
   {

      GetSliceRect(m_cx, m_cy, lprect, ealign, dRate, dRatePlus);

   }

   void TransitionEffect::Tool001::GetSliceRect(
      int32_t cx,
      int32_t cy,
      LPRECT   lprect,
      EAlign   ealign,
      double   dRate,
      double   dRatePlus // greater rate
      )
   {

      switch(ealign)
      {
      case AlignTop:
         {
            lprect->left = 0;
            lprect->right = lprect->left + cx;
            lprect->top = (int32_t) (dRate * cy);
            lprect->bottom = (int32_t) (dRatePlus * cy);
         }
         break;
      case AlignBottom:
         {
            lprect->left = 0;
            lprect->right = lprect->left + cx;
            lprect->top = (int32_t) ((1.0 - dRatePlus) * cy);
            lprect->bottom = (int32_t) ((1.0 - dRate) * cy);
         }
         break;
      case AlignLeft:
         {
            lprect->left =  (int32_t) (dRate * cx);
            lprect->right =  (int32_t) (dRatePlus * cx);
            lprect->top = 0;
            lprect->bottom = lprect->top + cy;;
         }
         break;
      case AlignRight:
         {
            lprect->left =  (int32_t) ((1.0 - dRatePlus) * cx);
            lprect->right =  (int32_t) ((1.0 - dRate) * cx);
            lprect->top = 0;
            lprect->bottom = lprect->top + cy;;
         }
         break;
      case AlignTopRight:
         {
            lprect->left = (int32_t) (dRate * cx);
            lprect->right = (int32_t) (dRatePlus * cx);
            lprect->top = (int32_t) (dRate * cy);
            lprect->bottom = (int32_t) (dRatePlus * cy);
         }
         break;
      case AlignRightBottom:
         {
            lprect->left = (int32_t) (dRate * cx);;
            lprect->right = (int32_t) (dRatePlus * cx);
            lprect->top = (int32_t) ((1.0 - dRatePlus) * cy);
            lprect->bottom = (int32_t) ((1.0 - dRate) * cy);
         }
         break;
      case AlignLeftTop:
         {
            lprect->left = (int32_t) ((1.0 - dRatePlus) * cx);
            lprect->right =  (int32_t) ((1.0 - dRate) * cx);
            lprect->top = (int32_t) (dRate * cy);
            lprect->bottom = (int32_t) (dRatePlus * cy);
         }
         break;
      case AlignBottomLeft:
         {
            lprect->left =  (int32_t) ((1.0 - dRatePlus) * cx);
            lprect->right =  (int32_t) ((1.0 - dRate) * cx);
            lprect->top = (int32_t) ((1.0 - dRatePlus) * cy);
            lprect->bottom = (int32_t) ((1.0 - dRate) * cy);
         }
         break;
      case AlignCenter:
         {
            double dHalfRate = dRatePlus / 2.0;
            lprect->left =  (int32_t) ((0.5 - dHalfRate) * (cx));
            lprect->right =  (int32_t) (dHalfRate * cx);
            lprect->top = (int32_t) ((0.5 - dHalfRate) * (cy));
            lprect->bottom = (int32_t) (dHalfRate * cy);
         }
         break;
      default:
         ASSERT(FALSE);
         break;
      }

   }

   void TransitionEffect::Tool001::
      GetHorizontalHexagon(LPRECT lprect, LPPOINT lppointa)
   {
      int32_t y1 = lprect->top;
      int32_t y3 = lprect->bottom;
      int32_t y2 = (y1 + y3) / 2;
      int32_t x1 = lprect->left;
      int32_t x4 = lprect->right;
      double  dr = (x4 - x1) / 2.0;
      int32_t x2 = (int32_t) (x1 + dr / 2);
      int32_t x3 = x1 + HIDOUBLETOINT(dr * 1.5);

      lppointa[0] = point(x1, y2);
      lppointa[1] = point(x2, y1);
      lppointa[2] = point(x3, y1);
      lppointa[3] = point(x4, y2);
      lppointa[4] = point(x3, y3);
      lppointa[5] = point(x2, y3);

   }

   int32_t TransitionEffect::Tool001::FindRandomEnglobingEllipse(LPCRECT lpcrect, LPRECT lprectEllipse, int32_t iMaxRand)
   {
//         Main & viewinterface = HelperGetMain();

      int32_t iRandX = (int32_t) System.math().RandRange(-iMaxRand, iMaxRand);
      int32_t iRandY = (int32_t) System.math().RandRange(-iMaxRand, iMaxRand);

      rect rect(lpcrect);

      double dMaxSide = MAX(rect.width(), rect.height());

      double dAdd = MAX(abs(iRandX), abs(iRandY));

      double dSide = dMaxSide + dAdd;

      double dRadius = dSide / sqrt(2.0);

      double dDiff = dSide - dRadius;

      int32_t iLContrib = iRandX < 0 ? iRandX : 0;
      int32_t iRContrib = iRandX > 0 ? iRandX : 0;
      int32_t iTContrib = iRandY < 0 ? iRandY : 0;
      int32_t iBContrib = iRandY > 0 ? iRandY : 0;

      lprectEllipse->left = (int32_t) (rect.left + iLContrib   - dDiff);
      lprectEllipse->top = (int32_t) (rect.top + iTContrib - dDiff);
      lprectEllipse->right = (int32_t) (rect.right + iRContrib   + dDiff);
      lprectEllipse->bottom = (int32_t) (rect.bottom + iBContrib   + dDiff);

      return 1;
   }


   int32_t TransitionEffect::Tool001::FindRandomEnglobingCircle(LPCRECT lpcrect, LPRECT lprectCircle, int32_t iMaxRand)
   {
//         Main & viewinterface = HelperGetMain();

      int32_t iRand = (int32_t) System.math().RandRange(-iMaxRand, iMaxRand);

      rect rect(lpcrect);

      double dMaxSide = MAX(rect.width(), rect.height());

      double dAdd = abs(iRand);

      double dSide = dMaxSide + dAdd;

      double dRadius = dSide / sqrt(2.0);

      double dDiff = dSide - dRadius;

      int32_t iLContrib = iRand < 0 ? iRand : 0;
      int32_t iRContrib = iRand > 0 ? iRand : 0;
      int32_t iTContrib = iRand < 0 ? iRand : 0;
      int32_t iBContrib = iRand > 0 ? iRand : 0;

      lprectCircle->left = (int32_t) (rect.left + iLContrib   - dDiff);
      lprectCircle->top = (int32_t) (rect.top + iTContrib - dDiff);
      lprectCircle->right = (int32_t) (rect.right + iRContrib   + dDiff);
      lprectCircle->bottom = (int32_t) (rect.bottom + iBContrib   + dDiff);

      return 1;
   }


   void TransitionEffect::Tool001::Finalize()
   {

      m_ia.remove_all();
      m_pointa.remove_all();
      m_pointa2.remove_all();

   }
   void TransitionEffect::Tool001::GetRect(LPPOINT lppoint, LPCRECT lpcrect)
   {
      lppoint[0].x = (int32_t) lpcrect->left;
      lppoint[0].y = (int32_t) lpcrect->top;
      lppoint[1].x = (int32_t) lpcrect->right;
      lppoint[1].y = (int32_t) lpcrect->top;
      lppoint[2].x = (int32_t) lpcrect->right;
      lppoint[2].y = (int32_t) lpcrect->bottom;
      lppoint[3].x = (int32_t) lpcrect->left;
      lppoint[3].y = (int32_t) lpcrect->bottom;
   }


   void TransitionEffect::EnableEffect(ETransitionEffect eeffect)
   {
      if(m_etypea.find_first(eeffect) < 0)
      {
         m_etypea.add(eeffect);
      }
   }

   void TransitionEffect::DisableEffect(ETransitionEffect eeffect)
   {
      m_etypea.remove(eeffect);
   }

   void TransitionEffect::Tool001::GetSimplePolyBox(LPRECT lprect, LPPOINT lppoint, int32_t iCount)
   {
      if(iCount <= 0)
         return;
      int32_t left = lppoint[0].x;
      int32_t right = left;
      int32_t top = lppoint[0].y;
      int32_t bottom = top;
      for(int32_t i = 1; i < iCount; i++)
      {
         if(lppoint[i].x < left)
            left = lppoint[i].x;
         else if(lppoint[i].x > right)
            right = lppoint[i].x;
         if(lppoint[i].y < top)
            top= lppoint[i].y;
         else if(lppoint[i].y > bottom)
            bottom = lppoint[i].y;
      }
      lprect->left = left;
      lprect->right = right;
      lprect->top = top;
      lprect->bottom = bottom;
   }


   void TransitionEffect::Tool001::
   GetRotateRect(
      int32_t w,
      int32_t h,
      int32_t i,
      int32_t j,
      double phi,
      LPPOINT lppoint)
   {
      rect rect;
      TranslateRect(rect, w, h, i, j);
      GetRect(lppoint, rect);
      System.geometry().rotate((m_cx / 2), (m_cy / 2), lppoint, 4, phi);
   }

   void TransitionEffect::Tool001::
   GetRotateRect(
      int32_t i,
      int32_t j,
      LPPOINT lppoint)
   {
      GetRotateRect(
         m_size.cx,
         m_size.cy,
         i,
         j,
         m_phi,
         lppoint);

   }

   void TransitionEffect::Tool001::TranslateRect(LPRECT lprect, int32_t w, int32_t h, int32_t i, int32_t j)
   {
      int32_t dx = (m_cx - w) / 2;
      int32_t dy = (m_cy - h) / 2;
      lprect->left = dx + w * i;
      lprect->right = lprect->left + w;
      lprect->top = dy + h * j;
      lprect->bottom = lprect->top + h;
   }

   void TransitionEffect::Tool001::
   GetRotateHexagon(
      int32_t iRadius,
      int32_t i,
      int32_t j,
      double phi,
      LPPOINT lppoint)
   {
      double d3Sqrt = sqrt(3.0);
      bool bEx = (abs(i) % 2 == 0) ^
         (abs(j) % 2 == 0);
      i /= 2;
      j /= 2;
      double dLeft = (m_cx - 3.0 * iRadius) / 2;
      double dRight;
      double dTop = (m_cy - iRadius * d3Sqrt) / 2;
      double dBottom;
      if(bEx)
      {
         dLeft += iRadius * (3.0 * i - 1.5);
         dTop +=  iRadius * (d3Sqrt * (j - 0.5));
      }
      else
      {
         dLeft += iRadius * (3.0 * i);
         dTop +=  iRadius * (d3Sqrt * (j));
      }
      rect rect;
      dRight  = dLeft + iRadius * 2.05  + 1;
      dBottom = dTop + iRadius * sqrt(3.1) + 1;
      rect.left = (int32_t) dLeft;
      rect.top = (int32_t) dTop;
      rect.right = (int32_t) dRight;
      rect.bottom = (int32_t) dBottom;

      GetHorizontalHexagon(rect, lppoint);
      System.geometry().rotate((m_cx / 2), (m_cy / 2), lppoint, 6, phi);
   }

   void TransitionEffect::Tool001::
   GetRotateHexagon(
      int32_t i,
      int32_t j,
      LPPOINT lppoint)
   {
      GetRotateHexagon(
         m_iRadius,
         i,
         j,
         m_phi,
         lppoint);
   }


} // namespace backview








