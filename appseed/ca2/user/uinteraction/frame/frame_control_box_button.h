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
            ::ca::pen * ppen,
            ::ca::pen * ppenSel = ::null(),
            ::ca::pen * ppenFocus = ::null(),
            ::ca::pen * ppenDisabled = ::null()) = 0;
         virtual void SetEllipseBrushs(
            ::ca::brush * pbrush,
            ::ca::brush * pbrushSel = ::null(),
            ::ca::brush * pbrushFocus = ::null(),
            ::ca::brush * pbrushDisabled = ::null()) = 0;
         virtual void SetTextColors(
            COLORREF cr,
            COLORREF crSel,
            COLORREF crFocus,
            COLORREF crDisabled) = 0;

      };


   } // namespace frame

   
} // namespace uinteraction




