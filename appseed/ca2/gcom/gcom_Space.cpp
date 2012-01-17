#include "StdAfx.h"

namespace gcom
{

   Space::Space()
   {

   }

   Space::~Space()
   {

   }

   void Space::Align(LPRECT lprectAlign, LPRECT lprectSpace, EAlign ealign, double dRate)
   {
      int cx = 0;
      int cy = 0;
      switch(ealign)
      {
      case ::gcom::AlignBottomLeft:
         cx = lprectSpace->left - lprectAlign->left;
         cy = lprectSpace->bottom - lprectAlign->bottom;
      
         break;
      case ::gcom::AlignLeft:
         cx = lprectSpace->left - lprectAlign->left;
         break;
      case ::gcom::AlignTop:
         cy = lprectSpace->top - lprectAlign->top;
         break;
      case ::gcom::AlignRight:
         cx = lprectSpace->right - lprectAlign->right;
         break;
      case ::gcom::AlignBottom:
         cy = lprectSpace->bottom - lprectAlign->bottom;
         break;
      case ::gcom::AlignTopLeft:
         cx = lprectSpace->left - lprectAlign->left;
         cy = lprectSpace->top - lprectAlign->top;
         break;
      case ::gcom::AlignTopRight:
         cx = lprectSpace->right - lprectAlign->right;
         cy = lprectSpace->top - lprectAlign->top;
         break;
      case ::gcom::AlignBottomRight:
         cx = lprectSpace->right - lprectAlign->right;
         cy = lprectSpace->bottom - lprectAlign->bottom;
         break;

      }
      cx = (int) (cx * dRate);
      cy = (int) (cy * dRate);
      lprectAlign->left     += cx;
      lprectAlign->right    += cx;
      lprectAlign->top      += cy;
      lprectAlign->bottom   += cy;
   }

   void Space::Deviate(LPRECT lprectDeviate, LPRECT lprectSpace, EDirection edirection, double dRate)
   {

      int dx = lprectSpace->right - lprectSpace->left;
      int dy = lprectSpace->bottom - lprectSpace->top;
      dx = (int) (dx * dRate);
      dy = (int) (dy * dRate);

      switch(edirection)
      {
      case ::gcom::DirectionLeft:
         dx = -dx;
         dy = 0;
         break;
      case ::gcom::DirectionTop:
         dx = 0;
         dy = - dy;
         break;
      case ::gcom::DirectionRight:
         dy = 0;
         break;
      case ::gcom::DirectionBottom:
         dx = 0;
         break;
      case ::gcom::DirectionTopLeft:
         dx = - dx;
         dy = - dy;
         break;
      case ::gcom::DirectionTopRight:
         dy = - dy;
         break;
      case ::gcom::DirectionBottomRight:
         break;
      case ::gcom::DirectionBottomLeft:
         dx = -dx;
         break;
      }

      lprectDeviate->left     += dx;
      lprectDeviate->right    += dx;
      lprectDeviate->top      += dy;
      lprectDeviate->bottom   += dy;

   }

   void Space::Slice(LPRECT lprectSliced1, LPRECT lprectSlicing, EDirection edirection, double dRate, double dRateEx)
   {
      int cx = lprectSlicing->right - lprectSlicing->left;
      int cy = lprectSlicing->bottom - lprectSlicing->top;
   
      switch(edirection)
      {
      case ::gcom::DirectionLeft:
         lprectSliced1->left     = lprectSlicing->left + (int) (cx * (1.0 - dRateEx));
         lprectSliced1->right    = lprectSlicing->left + (int) (cx * (1.0 - dRate));
         lprectSliced1->top      = lprectSlicing->top;
         lprectSliced1->bottom   = lprectSlicing->bottom;
         break;
      case ::gcom::DirectionTop:
         lprectSliced1->left     = lprectSlicing->left;
         lprectSliced1->right    = lprectSlicing->right;
         lprectSliced1->top      = lprectSlicing->top + (int) (cy * (1.0 - dRateEx));
         lprectSliced1->bottom   = lprectSlicing->top + (int) (cy * (1.0 - dRate));
         break;
      case ::gcom::DirectionRight:
         lprectSliced1->left     = lprectSlicing->left + (int) (cx * dRate);
         lprectSliced1->right    = lprectSlicing->left + (int) (cx * dRateEx);
         lprectSliced1->top      = lprectSlicing->top;
         lprectSliced1->bottom   = lprectSlicing->bottom;
         break;
      case ::gcom::DirectionBottom:
         lprectSliced1->left     = lprectSlicing->left;
         lprectSliced1->right    = lprectSlicing->right;
         lprectSliced1->top      = lprectSlicing->top + (int) (cy * dRate);
         lprectSliced1->bottom   = lprectSlicing->top + (int) (cy * dRateEx);
         break;
      case ::gcom::DirectionTopLeft:
         lprectSliced1->left     = lprectSlicing->left + (int) (cx * (1.0 - dRateEx));
         lprectSliced1->right    = lprectSlicing->left + (int) (cx * (1.0 - dRate));
         lprectSliced1->top      = lprectSlicing->top + (int) (cy * (1.0 - dRateEx));
         lprectSliced1->bottom   = lprectSlicing->top + (int) (cy * (1.0 - dRate));
         break;
      case ::gcom::DirectionTopRight:
         lprectSliced1->left     = lprectSlicing->left + (int) (cx * dRate);
         lprectSliced1->right    = lprectSlicing->left + (int) (cx * dRateEx);
         lprectSliced1->top      = lprectSlicing->top + (int) (cy * (1.0 - dRateEx));
         lprectSliced1->bottom   = lprectSlicing->top + (int) (cy * (1.0 - dRate));
         break;
      case ::gcom::DirectionBottomRight:
         lprectSliced1->left     = lprectSlicing->left + (int) (cx * dRate);
         lprectSliced1->right    = lprectSlicing->left + (int) (cx * dRateEx);
         lprectSliced1->top      = lprectSlicing->top + (int) (cy * dRate);
         lprectSliced1->bottom   = lprectSlicing->top + (int) (cy * dRateEx);
         break;
      case ::gcom::DirectionBottomLeft:
         lprectSliced1->left     = lprectSlicing->left + (int) (cx * (1.0 - dRateEx));
         lprectSliced1->right    = lprectSlicing->left + (int) (cx * (1.0 - dRate));
         lprectSliced1->top      = lprectSlicing->top + (int) (cy * dRate);
         lprectSliced1->bottom   = lprectSlicing->top + (int) (cy * dRateEx);
         break;
      }

   }
   void Space::Slice(LPRECT lprectSliced1, LPRECT lprectSliced2, LPRECT lprectSliced3, LPRECT lprectSlicing, EDirection edirection, double dRate, double dRateEx)
   {
      Slice(lprectSliced1, lprectSlicing, edirection, dRate, dRateEx);
   
      switch(edirection)
      {
      case ::gcom::DirectionLeft:
         ASSERT(FALSE);
         break;
      case ::gcom::DirectionTop:
         ASSERT(FALSE);
         break;
      case ::gcom::DirectionRight:
         ASSERT(FALSE);
         break;
      case ::gcom::DirectionBottom:
         ASSERT(FALSE);
         break;
      case ::gcom::DirectionTopLeft:
         lprectSliced2->left     = lprectSliced1->right;
         lprectSliced2->right    = lprectSlicing->right;
         lprectSliced2->top      = lprectSliced1->top;
         lprectSliced2->bottom   = lprectSliced1->bottom;

         lprectSliced3->left     = lprectSliced1->left;
         lprectSliced3->right    = lprectSliced1->right;
         lprectSliced3->top      = lprectSliced1->bottom;
         lprectSliced3->bottom   = lprectSlicing->bottom;
         break;
      case ::gcom::DirectionTopRight:
         lprectSliced2->left     = lprectSlicing->left;
         lprectSliced2->right    = lprectSliced1->left;
         lprectSliced2->top      = lprectSliced1->top;
         lprectSliced2->bottom   = lprectSliced1->bottom;

         lprectSliced3->left     = lprectSliced1->left;
         lprectSliced3->right    = lprectSliced1->right;
         lprectSliced3->top      = lprectSliced1->bottom;
         lprectSliced3->bottom   = lprectSlicing->bottom;
         break;
      case ::gcom::DirectionBottomRight:
         lprectSliced2->left     = lprectSlicing->left;
         lprectSliced2->right    = lprectSliced1->left;
         lprectSliced2->top      = lprectSliced1->top;
         lprectSliced2->bottom   = lprectSliced1->bottom;

         lprectSliced3->left     = lprectSliced1->left;
         lprectSliced3->right    = lprectSliced1->right;
         lprectSliced3->top      = lprectSlicing->top;
         lprectSliced3->bottom   = lprectSliced1->top;
         break;
      case ::gcom::DirectionBottomLeft:
         lprectSliced2->left     = lprectSliced1->right;
         lprectSliced2->right    = lprectSlicing->right;
         lprectSliced2->top      = lprectSliced1->top;
         lprectSliced2->bottom   = lprectSliced1->bottom;

         lprectSliced3->left     = lprectSliced1->left;
         lprectSliced3->right    = lprectSliced1->right;
         lprectSliced3->top      = lprectSlicing->top;
         lprectSliced3->bottom   = lprectSliced1->top;
         break;
      }

   }

   void Space::GetCenter(LPPOINT lppoint, LPRECT lprect)
   {
      lppoint->x = (lprect->left + lprect->right) / 2;
      lppoint->y = (lprect->top + lprect->bottom) / 2;
   }
   void Space::Scale(LPRECT lprectScaling, double dRate)
   {
      point point;
      GetCenter(&point, lprectScaling);
      int cx = lprectScaling->right - lprectScaling->left;
      int cy = lprectScaling->bottom - lprectScaling->top;

      cx = (int) (cx * dRate);
      cy = (int) (cy * dRate);

      lprectScaling->left     = point.x - cx / 2;
      lprectScaling->right    = lprectScaling->left + cx;
      lprectScaling->top      = point.y - cy / 2;
      lprectScaling->bottom   = lprectScaling->top + cy;


   }

   void Space::WipeIn(LPRECT lprect1, LPRECT lprect2, LPRECT lprect3, LPRECT lprect4, LPRECT lprect, double dRate, double dRateEx)
   {
      rect rectIn(lprect);
      Scale(rectIn, dRate);

      rect rectOut(lprect);
      Scale(rectOut, dRateEx);

      lprect1->left     = rectIn.left;
      lprect1->right    = rectOut.right;
      lprect1->top      = rectOut.top;
      lprect1->bottom   = rectIn.top;

      lprect2->left     = rectIn.right;
      lprect2->right    = rectOut.right;
      lprect2->top      = rectIn.top;
      lprect2->bottom   = rectOut.bottom;

      lprect3->left     = rectOut.left;
      lprect3->right    = rectIn.right;
      lprect3->top      = rectIn.bottom;
      lprect3->bottom   = rectOut.bottom;

      lprect4->left     = rectOut.left;
      lprect4->right    = rectIn.left;
      lprect4->top      = rectOut.top;
      lprect4->bottom   = rectIn.bottom;
   }

} // namespace gcom
