#pragma once


namespace user
{


   namespace wndfrm
   {


      namespace frame
      {


         enum EHitTest
         {
            HitTestNone,
            HitTestClient,
            HitTestSizingLeft,
            HitTestSizingTopLeft,
            HitTestSizingTop,
            HitTestSizingTopRight,
            HitTestSizingRight,
            HitTestSizingBottomRight,
            HitTestSizingBottom,
            HitTestSizingBottomLeft,
            HitTestMove,
         };

         enum e_button
         {
            button_none,
            button_begin,
            // TO Begin - TIGHTLY ORDERED Begin (relations : e_stock_icon[button_close:stock_icon_close,...])
            button_close = button_begin,
            button_up,
            button_down,
            button_minimize,
            button_restore,
            button_maximize,
            button_notify_icon,
            button_dock,
            // TO END - TIGHTLY ORDERED End
            button_end = button_dock
         };


      } // namespace frame


   } // namespace frame


} // namespace user







