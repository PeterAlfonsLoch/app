#include "StdAfx.h"


namespace win
{

   
   region::region(::ca::application * papp) :
      ca(papp)
   { 
      
      m_pregion = NULL;

   }

   region::~region()
   {

   }


   int region::GetRegionData(LPRGNDATA lpRgnData, int nDataSize) const
   { ASSERT(get_os_data() != NULL); return (int)::GetRegionData((HRGN)get_os_data(), nDataSize, lpRgnData); }
   void region::SetRectRgn(int x1, int y1, int x2, int y2)
   { ASSERT(get_os_data() != NULL); ::SetRectRgn((HRGN)get_os_data(), x1, y1, x2, y2); }
   
   void region::SetRectRgn(LPCRECT lpRect)
   { 
      ::SetRectRgn((HRGN)get_os_data(), lpRect->left, lpRect->top, lpRect->right, lpRect->bottom); 
   }

   int region::CombineRgn(const ::ca::region* pRgn1, const ::ca::region* pRgn2, int nCombineMode)
   { ASSERT(get_os_data() != NULL); return ::CombineRgn((HRGN)get_os_data(), (HRGN)pRgn1->get_os_data(),
   (HRGN)pRgn2->get_os_data(), nCombineMode); }
   int region::CopyRgn(const ::ca::region* pRgnSrc)
   { ASSERT(get_os_data() != NULL); return ::CombineRgn((HRGN)get_os_data(), (HRGN)pRgnSrc->get_os_data(), NULL, RGN_COPY); }
   BOOL region::EqualRgn(const ::ca::region* pRgn) const
   { ASSERT(get_os_data() != NULL); return ::EqualRgn((HRGN)get_os_data(), (HRGN)pRgn->get_os_data()); }
   int region::OffsetRgn(int x, int y)
   { ASSERT(get_os_data() != NULL); return ::OffsetRgn((HRGN)get_os_data(), x, y); }
   int region::OffsetRgn(POINT point)
   { ASSERT(get_os_data() != NULL); return ::OffsetRgn((HRGN)get_os_data(), point.x, point.y); }
   int region::GetRgnBox(LPRECT lpRect) const
   { ASSERT(get_os_data() != NULL); return ::GetRgnBox((HRGN)get_os_data(), lpRect); }
   BOOL region::PtInRegion(int x, int y) const
   { ASSERT(get_os_data() != NULL); return ::PtInRegion((HRGN)get_os_data(), x, y); }
   BOOL region::PtInRegion(POINT point) const
   { ASSERT(get_os_data() != NULL); return ::PtInRegion((HRGN)get_os_data(), point.x, point.y); }
   BOOL region::RectInRegion(LPCRECT lpRect) const
   { ASSERT(get_os_data() != NULL); return ::RectInRegion((HRGN)get_os_data(), lpRect); }


} // namespace win