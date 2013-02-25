#include "framework.h"

/*

namespace visual
{

   clip::clip() :
      m_pdc(NULL),
      m_pwnd(NULL),
      m_bAcquired(false)
   {
//      m_rgn.create_rect(0, 0, 0, 0);
//      m_rgnOld.create_rect(0, 0, 0, 0);
   }

   //////////////////////////////////////////////////
   // Function : clip
   //
   // Purpose:
   // Construct a clip instance.and execute the clipping.
   //
   // Output:
   // No return value
   //
   // Camilo S. Tsumanuma
   //
   //////////////////////////////////////////////////
   clip::clip(::ca::window * pwnd, ::ca::graphics * pdc)
   {
      ASSERT(pwnd != NULL);
      ASSERT(pdc != NULL);
//      m_rgn.create_rect(0, 0, 0, 0);
      //m_rgnOld.create_rect(0, 0, 0, 0);
      Do(pwnd, pdc);
   }

   //////////////////////////////////////////////////
   // Function : clip
   //
   // Purpose:
   // Construct a clip instance.and execute the clipping.
   //
   // Output:
   // No return value
   //
   // Camilo S. Tsumanuma
   //
   //////////////////////////////////////////////////
   clip::clip(::ca::graphics * pdc, ::ca::region * prgn)
   {
      ASSERT(pdc != NULL);
//      m_rgn.create_rect(0, 0, 0, 0);
  //    m_rgnOld.create_rect(0, 0, 0, 0);
      Do(pdc, prgn);
   }

   //////////////////////////////////////////////////
   // Function : clip
   //
   // Purpose:
   // Construct a clip instance.and execute the clipping.
   //
   // Output:
   // No return value
   //
   // Camilo S. Tsumanuma
   //
   //////////////////////////////////////////////////
   clip::clip(::ca::graphics * pdc, LPCRECT lpcrect)
   {
      ASSERT(pdc != NULL);
//      m_rgn.create_rect(0, 0, 0, 0);
  //    m_rgnOld.create_rect(0, 0, 0, 0);
      Do(pdc, lpcrect);
   }

   //////////////////////////////////////////////////
   // Function : ~clip
   //
   // Purpose:
   // Destruct a clip instance.
   // Undo clipping if it has be done.
   //
   // Output:
   // No return value
   //
   // Camilo S. Tsumanuma
   //
   //////////////////////////////////////////////////
   clip::~clip()
   {
      if(m_bAcquired)
      {
         Undo();
      }
   }

   //////////////////////////////////////////////////
   // Function : Do
   //
   // Purpose:
   // Destruct a clip instance.
   // Undo clipping if it has be done.
   //
   // Output:
   // No return value
   //
   // Camilo S. Tsumanuma
   //
   //////////////////////////////////////////////////
   void clip::Do(
      ::ca::graphics * pdc, // the clipped device context
      ::ca::region * prgn)
   {
      ASSERT(pdc != NULL);

      m_bAcquired = true;
      m_pwnd = NULL;
      m_pdc = pdc;

      point ptViewportOrg = pdc->GetViewportOrg();

      ::ca::region & rgn = m_rgn;
      int32_t & iOldType = m_iOldType;
      ::ca::region & rgnOld = m_rgnOld;

      rgn.CopyRgn(prgn);
      rgn.OffsetRgn(ptViewportOrg);

#ifdef WINDOWS

      if((iOldType = ::GetClipRgn((HDC)pdc->get_os_data(), (HRGN) rgnOld.get_os_data())) == 1)
      {
         rgn.CombineRgn(&rgn, &rgnOld, RGN_AND);
      }

#else

      throw todo(::ca::get_thread_app());

#endif

      pdc->SelectClipRgn(&rgn);

   }

   //////////////////////////////////////////////////
   // Function : Do
   //
   // Purpose:
   // Destruct a clip instance.
   // Undo clipping if it has be done.
   //
   // Output:
   // No return value
   //
   // Camilo S. Tsumanuma
   //
   //////////////////////////////////////////////////
   void clip::Do(
      ::ca::graphics * pdc, // the clipped device context
      LPCRECT lpcrect)
   {
      ASSERT(pdc != NULL);

      m_bAcquired = true;
      m_pwnd = NULL;
      m_pdc = pdc;

      point ptViewportOrg = pdc->GetViewportOrg();

      ::ca::region & rgn = m_rgn;
      int32_t & iOldType = m_iOldType;
      ::ca::region & rgnOld = m_rgnOld;

      rect rectUpdate(lpcrect);
      rectUpdate.offset(ptViewportOrg);
      rgn.SetRectRgn(rectUpdate);

#ifdef WINDOWS

      if((iOldType = ::GetClipRgn((HDC)pdc->get_os_data(), (HRGN) rgnOld.get_os_data()))
         == 1)
      {
         rgn.CombineRgn(&rgn, &rgnOld, RGN_AND);
      }

#else

      throw todo(::ca::get_thread_app());

#endif

      pdc->SelectClipRgn(&rgn);

   }

   //////////////////////////////////////////////////
   // Function : Do
   //
   // Purpose:
   // Destruct a clip instance.
   // Undo clipping if it has be done.
   //
   // Output:
   // No return value
   //
   // Camilo S. Tsumanuma
   //
   //////////////////////////////////////////////////
   void clip::Do(
      ::ca::window * pwnd, // ::ca::window that will draw at the clipped device context
      ::ca::graphics * pdc // the clipped device context
      )
   {
      ASSERT(pwnd != NULL);
      ASSERT(pdc != NULL);

      m_bAcquired = true;
      m_pwnd = pwnd;
      m_pdc = pdc;

      rect rectUpdate;

      point ptViewportOrg = pdc->GetViewportOrg();

      pwnd->GetClientRect(rectUpdate);

      ::user::interaction * pwndParent = pwnd->get_parent();

      if(pwndParent != NULL)
      {
         rect rectParent;
         pwndParent->GetClientRect(rectParent);
         pwndParent->ClientToScreen(rectParent);
         pwnd->ScreenToClient(rectParent);
         rectUpdate.intersect(rectUpdate, rectParent);
      }

      rectUpdate.offset(ptViewportOrg);

      ::ca::region & rgn = m_rgn;
      int32_t & iOldType = m_iOldType;
      ::ca::region & rgnOld = m_rgnOld;

      rgn.SetRectRgn(rectUpdate);

#ifdef WINDOWS

      if((iOldType = ::GetClipRgn((HDC)pdc->get_os_data(), (HRGN) rgnOld.get_os_data()))
         == 1)
      {
         rect rectTest1;
         rgnOld.get_bounding_box(rectTest1);
         rgn.CombineRgn(&rgn, &rgnOld, RGN_AND);
         rect rectTest2;
         rgn.get_bounding_box(rectTest2);
      }

#else

      throw todo(::ca::get_thread_app());

#endif

      pdc->SelectClipRgn(&rgn);

   }

   //////////////////////////////////////////////////
   // Function : Undo
   //
   // Purpose:
   // Undo clipping if it has be done.
   //
   // Output:
   // No return value
   //
   // Camilo S. Tsumanuma
   //
   //////////////////////////////////////////////////
   void clip::Undo()
   {
      ASSERT(m_bAcquired);
      if(m_bAcquired)
      {

         int32_t  & iOldType = m_iOldType;
         ::ca::region & rgnOld   = m_rgnOld;
         ::ca::graphics * pdc = m_pdc;
         if(iOldType == 1)
            pdc->SelectClipRgn(&rgnOld);
         else
            pdc->SelectClipRgn(NULL);
      }
   }

} // namespace visual


*/