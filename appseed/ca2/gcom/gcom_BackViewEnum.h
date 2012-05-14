// BackViewInterface.h: interface for the CBackViewInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__BACKVIEWENUM_H__0EC60A81_3AEA_453D_B687_F57CA5976D70__INCLUDED_)
#define __BACKVIEWENUM_H__0EC60A81_3AEA_453D_B687_F57CA5976D70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace gcom
{
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
            ImagePlacementZoomAll = 1,
            ImagePlacementStretch = 2,
            ImagePlacementTile = 3,
            ImagePlacementZoomExtend = 4
         };

         enum EInterfaceData
         {
            InterfaceDataEnhancedMetaFile,
            InterfaceDataImagePlacement,
            InterfaceDataNextImagePath,
            InterfaceDataCurrentImagePath,
            InterfaceDataClientRect,
         };

   } // namespace backview

} // namespace gcom

#endif // !defined(__BACKVIEWENUM_H__0EC60A81_3AEA_453D_B687_F57CA5976D70__INCLUDED_)
