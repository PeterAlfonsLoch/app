#pragma once



namespace uinteraction
{


   namespace frame
   {


      class  CLASS_DECL_CORE control_box_button :
         virtual public ::user::interaction
      {
      public:



         virtual void UpdateWndRgn() = 0;
         virtual void SetEllipsePens(
            ::draw2d::pen * ppen,
            ::draw2d::pen * ppenSel = NULL,
            ::draw2d::pen * ppenFocus = NULL,
            ::draw2d::pen * ppenDisabled = NULL) = 0;
         virtual void SetEllipseBrushs(
            ::draw2d::brush * pbrush,
            ::draw2d::brush * pbrushSel = NULL,
            ::draw2d::brush * pbrushFocus = NULL,
            ::draw2d::brush * pbrushDisabled = NULL) = 0;
         virtual void SetTextColors(
            COLORREF cr,
            COLORREF crSel,
            COLORREF crFocus,
            COLORREF crDisabled) = 0;

      };


   } // namespace frame

   
} // namespace uinteraction




