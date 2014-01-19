#include "framework.h"


namespace gcom
{


   space::space()
   {

   }

   space::~space()
   {

   }

   void space::align(LPRECT lprectalign, LPRECT lprectspace, e_align ealign, double dRate)
   {
      int32_t cx = 0;
      int32_t cy = 0;
      switch(ealign)
      {
      case align_bottom_left:
         cx = lprectspace->left - lprectalign->left;
         cy = lprectspace->bottom - lprectalign->bottom;

         break;
      case align_left:
         cx = lprectspace->left - lprectalign->left;
         break;
      case align_top:
         cy = lprectspace->top - lprectalign->top;
         break;
      case align_right:
         cx = lprectspace->right - lprectalign->right;
         break;
      case align_bottom:
         cy = lprectspace->bottom - lprectalign->bottom;
         break;
      case align_top_left:
         cx = lprectspace->left - lprectalign->left;
         cy = lprectspace->top - lprectalign->top;
         break;
      case align_top_right:
         cx = lprectspace->right - lprectalign->right;
         cy = lprectspace->top - lprectalign->top;
         break;
      case align_bottom_right:
         cx = lprectspace->right - lprectalign->right;
         cy = lprectspace->bottom - lprectalign->bottom;
         break;
         default:
            break;
      }
      cx = (int32_t) (cx * dRate);
      cy = (int32_t) (cy * dRate);
      lprectalign->left     += cx;
      lprectalign->right    += cx;
      lprectalign->top      += cy;
      lprectalign->bottom   += cy;
   }

   void space::deviate(LPRECT lprectDeviate, LPRECT lprectspace, e_direction edirection, double dRate)
   {

      int32_t dx = lprectspace->right - lprectspace->left;
      int32_t dy = lprectspace->bottom - lprectspace->top;
      dx = (int32_t) (dx * dRate);
      dy = (int32_t) (dy * dRate);

      switch(edirection)
      {
      case direction_left:
         dx = -dx;
         dy = 0;
         break;
      case direction_top:
         dx = 0;
         dy = - dy;
         break;
      case direction_right:
         dy = 0;
         break;
      case direction_bottom:
         dx = 0;
         break;
      case direction_top_left:
         dx = - dx;
         dy = - dy;
         break;
      case direction_top_right:
         dy = - dy;
         break;
      case direction_bottom_right:
         break;
      case direction_bottom_left:
         dx = -dx;
         break;
         default:
            break;
      }

      lprectDeviate->left     += dx;
      lprectDeviate->right    += dx;
      lprectDeviate->top      += dy;
      lprectDeviate->bottom   += dy;

   }

   void space::slice(LPRECT lprectSliced1, LPRECT lprectSlicing, e_direction edirection, double dRate, double dRateEx)
   {
      int32_t cx = lprectSlicing->right - lprectSlicing->left;
      int32_t cy = lprectSlicing->bottom - lprectSlicing->top;

      switch(edirection)
      {
      case direction_left:
         lprectSliced1->left     = lprectSlicing->left + (int32_t) (cx * (1.0 - dRateEx));
         lprectSliced1->right    = lprectSlicing->left + (int32_t) (cx * (1.0 - dRate));
         lprectSliced1->top      = lprectSlicing->top;
         lprectSliced1->bottom   = lprectSlicing->bottom;
         break;
      case direction_top:
         lprectSliced1->left     = lprectSlicing->left;
         lprectSliced1->right    = lprectSlicing->right;
         lprectSliced1->top      = lprectSlicing->top + (int32_t) (cy * (1.0 - dRateEx));
         lprectSliced1->bottom   = lprectSlicing->top + (int32_t) (cy * (1.0 - dRate));
         break;
      case direction_right:
         lprectSliced1->left     = lprectSlicing->left + (int32_t) (cx * dRate);
         lprectSliced1->right    = lprectSlicing->left + (int32_t) (cx * dRateEx);
         lprectSliced1->top      = lprectSlicing->top;
         lprectSliced1->bottom   = lprectSlicing->bottom;
         break;
      case direction_bottom:
         lprectSliced1->left     = lprectSlicing->left;
         lprectSliced1->right    = lprectSlicing->right;
         lprectSliced1->top      = lprectSlicing->top + (int32_t) (cy * dRate);
         lprectSliced1->bottom   = lprectSlicing->top + (int32_t) (cy * dRateEx);
         break;
      case direction_top_left:
         lprectSliced1->left     = lprectSlicing->left + (int32_t) (cx * (1.0 - dRateEx));
         lprectSliced1->right    = lprectSlicing->left + (int32_t) (cx * (1.0 - dRate));
         lprectSliced1->top      = lprectSlicing->top + (int32_t) (cy * (1.0 - dRateEx));
         lprectSliced1->bottom   = lprectSlicing->top + (int32_t) (cy * (1.0 - dRate));
         break;
      case direction_top_right:
         lprectSliced1->left     = lprectSlicing->left + (int32_t) (cx * dRate);
         lprectSliced1->right    = lprectSlicing->left + (int32_t) (cx * dRateEx);
         lprectSliced1->top      = lprectSlicing->top + (int32_t) (cy * (1.0 - dRateEx));
         lprectSliced1->bottom   = lprectSlicing->top + (int32_t) (cy * (1.0 - dRate));
         break;
      case direction_bottom_right:
         lprectSliced1->left     = lprectSlicing->left + (int32_t) (cx * dRate);
         lprectSliced1->right    = lprectSlicing->left + (int32_t) (cx * dRateEx);
         lprectSliced1->top      = lprectSlicing->top + (int32_t) (cy * dRate);
         lprectSliced1->bottom   = lprectSlicing->top + (int32_t) (cy * dRateEx);
         break;
      case direction_bottom_left:
         lprectSliced1->left     = lprectSlicing->left + (int32_t) (cx * (1.0 - dRateEx));
         lprectSliced1->right    = lprectSlicing->left + (int32_t) (cx * (1.0 - dRate));
         lprectSliced1->top      = lprectSlicing->top + (int32_t) (cy * dRate);
         lprectSliced1->bottom   = lprectSlicing->top + (int32_t) (cy * dRateEx);
         break;
         default:
            break;
      }

   }


   void space::slice(LPRECT lprectSliced1, LPRECT lprectSliced2, LPRECT lprectSliced3, LPRECT lprectSlicing, e_direction edirection, double dRate, double dRateEx)
   {

      slice(lprectSliced1, lprectSlicing, edirection, dRate, dRateEx);

      switch(edirection)
      {
      case direction_left:
         ASSERT(FALSE);
         break;
      case direction_top:
         ASSERT(FALSE);
         break;
      case direction_right:
         ASSERT(FALSE);
         break;
      case direction_bottom:
         ASSERT(FALSE);
         break;
      case direction_top_left:
         lprectSliced2->left     = lprectSliced1->right;
         lprectSliced2->right    = lprectSlicing->right;
         lprectSliced2->top      = lprectSliced1->top;
         lprectSliced2->bottom   = lprectSliced1->bottom;

         lprectSliced3->left     = lprectSliced1->left;
         lprectSliced3->right    = lprectSliced1->right;
         lprectSliced3->top      = lprectSliced1->bottom;
         lprectSliced3->bottom   = lprectSlicing->bottom;
         break;
      case direction_top_right:
         lprectSliced2->left     = lprectSlicing->left;
         lprectSliced2->right    = lprectSliced1->left;
         lprectSliced2->top      = lprectSliced1->top;
         lprectSliced2->bottom   = lprectSliced1->bottom;

         lprectSliced3->left     = lprectSliced1->left;
         lprectSliced3->right    = lprectSliced1->right;
         lprectSliced3->top      = lprectSliced1->bottom;
         lprectSliced3->bottom   = lprectSlicing->bottom;
         break;
      case direction_bottom_right:
         lprectSliced2->left     = lprectSlicing->left;
         lprectSliced2->right    = lprectSliced1->left;
         lprectSliced2->top      = lprectSliced1->top;
         lprectSliced2->bottom   = lprectSliced1->bottom;

         lprectSliced3->left     = lprectSliced1->left;
         lprectSliced3->right    = lprectSliced1->right;
         lprectSliced3->top      = lprectSlicing->top;
         lprectSliced3->bottom   = lprectSliced1->top;
         break;
      case direction_bottom_left:
         lprectSliced2->left     = lprectSliced1->right;
         lprectSliced2->right    = lprectSlicing->right;
         lprectSliced2->top      = lprectSliced1->top;
         lprectSliced2->bottom   = lprectSliced1->bottom;

         lprectSliced3->left     = lprectSliced1->left;
         lprectSliced3->right    = lprectSliced1->right;
         lprectSliced3->top      = lprectSlicing->top;
         lprectSliced3->bottom   = lprectSliced1->top;
         break;
         default:
            break;
      }

   }


   void space::get_center(LPPOINT lppoint, LPRECT lprect)
   {

      lppoint->x = (lprect->left + lprect->right) / 2;
      lppoint->y = (lprect->top + lprect->bottom) / 2;

   }


   void space::scale(LPRECT lprectScaling, double dRate)
   {

      point point;
      get_center(&point, lprectScaling);
      int32_t cx = lprectScaling->right - lprectScaling->left;
      int32_t cy = lprectScaling->bottom - lprectScaling->top;

      cx = (int32_t) (cx * dRate);
      cy = (int32_t) (cy * dRate);

      lprectScaling->left     = point.x - cx / 2;
      lprectScaling->right    = lprectScaling->left + cx;
      lprectScaling->top      = point.y - cy / 2;
      lprectScaling->bottom   = lprectScaling->top + cy;

   }


   void space::wipe_in(LPRECT lprect1, LPRECT lprect2, LPRECT lprect3, LPRECT lprect4, LPRECT lprect, double dRate, double dRateEx)
   {

      ::rect rectIn(lprect);
      scale(rectIn, dRate);

      ::rect rectOut(lprect);
      scale(rectOut, dRateEx);

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








