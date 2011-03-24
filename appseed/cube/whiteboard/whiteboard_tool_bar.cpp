#include "StdAfx.h"

namespace whiteboard
{

   toolbar::toolbar(::ca::application * papp) :
      ca(papp),
      simple_toolbar(papp)
   {
      m_hbrushBackgroundOriginal = NULL;
   }

   toolbar::~toolbar()
   {
   }


    // BEGIN_MESSAGE_MAP(toolbar, ::userbase::tool_bar)
    // END_MESSAGE_MAP()



   // toolbar message handlers


   void toolbar::ChangeBackgroundColor(COLORREF cr)
   {
      HBRUSH hbrush = ::CreateSolidBrush(cr);
      ChangeBackgroundBrush(hbrush);
   }

   void toolbar::ChangeBackgroundBrush(HBRUSH hbrush)
   {
//      HGDIOBJ hgdiobjOld = (HGDIOBJ)
  //       ::SetClassLong(_get_handle(), GCL_HBRBACKGROUND, (LONG) hbrush);
      HGDIOBJ hgdiobjOld = (HGDIOBJ) NULL;
      if(m_hbrushBackgroundOriginal == NULL)
      {
         m_hbrushBackgroundOriginal = (HBRUSH) hgdiobjOld;
      }
      else if(m_hbrushBackgroundOriginal != hgdiobjOld)
      {
         ::DeleteObject(hgdiobjOld);
      }
      RedrawWindow();
   }

   void toolbar::SetOriginalBackground()
   {
      ChangeBackgroundBrush(m_hbrushBackgroundOriginal);
   }


   /*Public Sub ChangeTBBack(TB As Object, PNewBack As Long, pType As enuTBType)
   Dim lTBWnd      As Long
       Select Case pType
           Case enuTB_FLAT     'FLAT button Style Toolbar
               'Apply directly to TB Hwnd
               delete_object SetClassLong(TB.hwnd, GCL_HBRBACKGROUND, PNewBack)        
           Case enuTB_STANDARD 'STANDARD button Style Toolbar
               lTBWnd = FindWindowEx(TB.hwnd, 0, "msvb_lib_toolbar", vbNullString) 'find Hwnd first
               delete_object SetClassLong(lTBWnd, GCL_HBRBACKGROUND, PNewBack)      'Set new Back
       End Select
   End Sub*/

} // namespace whiteboard