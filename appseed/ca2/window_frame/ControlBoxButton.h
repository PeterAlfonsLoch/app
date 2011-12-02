#pragma once

/////////////////////////////////////////////////////////////////////////////
// CButtonV007 ::ax::window

namespace window_frame
{

   class  CLASS_DECL_ca ControlBoxButton :
      virtual public ::user::interaction
   {
   public:



      virtual void UpdateWndRgn() = 0;
      virtual void SetEllipsePens(
           ::ax::pen * ppen,
           ::ax::pen * ppenSel = NULL,
           ::ax::pen * ppenFocus = NULL,
           ::ax::pen * ppenDisabled = NULL) = 0;
      virtual void SetEllipseBrushs(
           ::ax::brush * pbrush,
           ::ax::brush * pbrushSel = NULL,
           ::ax::brush * pbrushFocus = NULL,
           ::ax::brush * pbrushDisabled = NULL) = 0;
       virtual void SetTextColors(
           COLORREF cr,
           COLORREF crSel,
           COLORREF crFocus,
           COLORREF crDisabled) = 0;

   };


} // namespace window_frame

