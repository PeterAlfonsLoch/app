#pragma once


namespace backview
{


   enum e_state
   {

      StateTiming,
      StateLoading,
      StatePreTransition,
      StatePreTransitionResize,
      StateInTransitionEffect,
      StateFinish,

   };


   enum e_event
   {

      event_timer,
      EventLoaded,
      EventPreTransitionFinished,
      EventTransitionEffectFinished,
      EventLoadFailed,
      EventLoadNow,
      EventFlagChanged,
      EventResize,

   };


   enum EImagePlacement
   {

      ImagePlacementZoomAll,
      ImagePlacementStretch,
      ImagePlacementTile,
      ImagePlacementZoomExtend

   };


   enum EInterfaceData
   {

      InterfaceDataEnhancedMetaFile,
      InterfaceDataImagePlacement,
      InterfaceDataNextImagePath,
      InterfaceDataCurrentImagePath,
      InterfaceDataClientRect,

   };


   namespace _graphics
   {


      enum EDib
      {

         DibTemp1,
         DibTemp2,
         DibTemp3,
         DibTemp4,
         DibTemp5,
         DibBuffer,
         DibFrame1,
         DibSource,
         DibFinal,
         DibBack,
         DibTransfer,

      };


   } // namespace _graphics



   enum ETransitionEffect
   {

      TransitionEffectInvalid,
      TransitionEffectStart,
      TransitionEffectFirst = TransitionEffectStart,
      TransitionEffectSingleStep = TransitionEffectFirst,
      TransitionEffectSquarypixelate_,
      TransitionEffectHexagonalpixelate_,
      TransitionEffectCirclypixelate_,
      TransitionEffectEllipsoidalpixelate_,
      TransitionEffectLinearFadingTopBottom,
      TransitionEffectLinearFadingBottomTop,
      TransitionEffectLinearFadingLeftRight,
      TransitionEffectLinearFadingRightLeft,
      TransitionEffectAccumulLinearFadingTopBottom,
      TransitionEffectAccumulLinearFadingBottomTop,
      TransitionEffectAccumulLinearFadingLeftRight,
      TransitionEffectAccumulLinearFadingRightLeft,
      TransitionEffectFlyInTopBottom,
      TransitionEffectFlyInBottomTop,
      TransitionEffectFlyInLeftRight,
      TransitionEffectFlyInRightLeft,
      TransitionEffectFlyInLeftBottom,
      TransitionEffectFlyInLeftTop,
      TransitionEffectFlyInRightBottom,
      TransitionEffectFlyInRightTop,
      TransitionEffectWipeBottom,
      TransitionEffectWipeTop,
      TransitionEffectWipeRight,
      TransitionEffectWipeLeft,
      TransitionEffectWipeMidHorizontal,
      TransitionEffectWipeTopLeft,
      TransitionEffectWipeTopRight,
      TransitionEffectWipeBottomLeft,
      TransitionEffectWipeBottomRight,
      TransitionEffectWipeMidVertical,
      TransitionEffectWipeCenter,
      TransitionEffectWipeIn,
      TransitionEffectScaleBottom,
      TransitionEffectScaleTop,
      TransitionEffectScaleRight,
      TransitionEffectScaleLeft,
      TransitionEffectScaleTopLeft,
      TransitionEffectScaleTopRight,
      TransitionEffectScaleBottomLeft,
      TransitionEffectScaleBottomRight,
      TransitionEffectScaleCenter,
      TransitionEffectpixelate_TopBottom,
      TransitionEffectpixelate_BottomTop,
      TransitionEffectpixelate_LeftRight,
      TransitionEffectpixelate_RightLeft,
      TransitionEffectVisual,
      TransitionEffectRadialUnveil,
      TransitionEffectLast = TransitionEffectRadialUnveil,
      TransitionEffectEnd,

   };


   enum EVisualEffect
   {

      VisualEffectPixelExplosion,
      VisualEffectAlphaPixelExplosion,
      VisualEffectPixelExplosion2,

      VisualEffectRotateEx8,
      VisualEffectRotateEx4,
      VisualEffectRain1,
      VisualEffectRotateEx5,
      VisualEffectRotateEx6,
      VisualEffectRotateEx7,

      VisualEffectExpand8,
      VisualEffectExpand4,
      VisualEffectExpand5,
      VisualEffectExpand6,
      VisualEffectExpand7,

      VisualEffectRotateBlend,
      VisualEffectNoPrecisionRotateBlend,
      VisualEffectNoPrecisionRotatecolor_blend_,
      VisualEffectNoPrecisionRotateTrackcolor_blend_,
      VisualEffectRotateEx1,
      VisualEffectRotateEx2,
      VisualEffectRotateEx3,
      VisualEffectEnd,

   };

} // namespace backview






