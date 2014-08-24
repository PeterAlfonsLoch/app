#pragma once


namespace user
{


   namespace wndfrm
   {


      namespace frame
      {


         enum EAppearanceTransparency
         {
            Opaque,
            ClientTransparent,
            Transparent,
         };




         enum EDock
         {
            DockNone = 0,
            DockHalfSide = 0,
            DockFullSide = 1,
            DockTop = 2,
            DockLeft = 4,
            DockRight = 8,
            DockBottom = 16,
            DockAll =
            DockTop
            | DockLeft
            | DockRight
            | DockBottom,
         };

         enum EGrip
         {
            GripNone = 0,
            GripCenterLeft = 1,
            GripTopLeft = 2,
            GripCenterTop = 4,
            GripTopRight = 8,
            GripCenterRight = 16,
            GripBottomRight = 32,
            GripCenterBottom = 64,
            GripBottomLeft = 128,
            GripLeft = GripBottomLeft | GripCenterLeft | GripTopLeft,
            GripTop = GripTopLeft | GripCenterTop | GripTopRight,
            GripRight = GripTopRight | GripCenterRight | GripBottomRight,
            GripBottom = GripBottomLeft | GripCenterBottom | GripBottomRight,
            GripAll = GripLeft | GripTop | GripRight | GripBottom,
         };


      } //namespace frame


   } // namespace wndfrm


} // namespace user












