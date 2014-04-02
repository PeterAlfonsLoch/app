#pragma once


namespace uinteraction
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
         button_close,
         button_up,
         button_down,
         button_minimize,
         button_restore,
         button_maximize,
         button_notify_icon,
      };


   } // namespace frame


} // namespace frame





