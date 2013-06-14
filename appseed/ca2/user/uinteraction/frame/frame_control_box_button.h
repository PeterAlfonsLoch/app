#pragma once



namespace uinteraction
{


   namespace frame
   {


      class  CLASS_DECL_ca2 ControlBoxButton :
         virtual public ::user::interaction
      {
      public:



         virtual void UpdateWndRgn() = 0;
         virtual void SetEllipsePens(
            ::ca2::pen * ppen,
            ::ca2::pen * ppenSel = NULL,
            ::ca2::pen * ppenFocus = NULL,
            ::ca2::pen * ppenDisabled = NULL) = 0;
         virtual void SetEllipseBrushs(
            ::ca2::brush * pbrush,
            ::ca2::brush * pbrushSel = NULL,
            ::ca2::brush * pbrushFocus = NULL,
            ::ca2::brush * pbrushDisabled = NULL) = 0;
         virtual void SetTextColors(
            COLORREF cr,
            COLORREF crSel,
            COLORREF crFocus,
            COLORREF crDisabled) = 0;

      };


   } // namespace frame

   
} // namespace uinteraction




