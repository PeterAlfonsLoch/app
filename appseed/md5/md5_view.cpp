#include "StdAfx.h"


namespace md5
{

   
   view::view(::ca::application * papp) :
      ca(papp),
      ::userbase::view(papp)
   {
   }

   view::~view()
   {
   }

#ifdef _DEBUG
   void view::assert_valid() const
   {
	   ::userbase::view::assert_valid();
   }

   void view::dump(dump_context& dc) const
   {
	   ::userbase::view::dump(dc);
   }
#endif //_DEBUG


   void view:: _001OnDraw(::ca::graphics * pdc)
   {

      pdc->TextOutA(10, 10, get_document()->m_strCheckMd5);
      pdc->TextOutA(10, 50, get_document()->m_thread.m_strFile);
      pdc->TextOutA(10, 110, get_document()->m_thread.m_strStatus);

      if(get_document()->m_thread.m_bReady)
      {
         if(get_document()->m_strCheckMd5.CompareNoCase(get_document()->m_thread.m_strMd5) == 0)
         {
            pdc->SetTextColor(RGB(100, 180, 100));
         }
         else
         {
            pdc->SetTextColor(RGB(255, 100, 100));
         }
         pdc->TextOutA(10, 100, get_document()->m_thread.m_strMd5);
      }
      else
      {
         class rect rect;

         rect.left   = 10;
         rect.top    = 100;
         rect.right  = rect.left + 400;
         rect.bottom = rect.top + 25;

         pdc->Draw3dRect(rect, RGB(0, 128, 0), RGB(0, 128, 0));
         rect.deflate(1, 1);
         pdc->Draw3dRect(rect, RGB(255, 255, 255), RGB(255, 255, 255));
         rect.deflate(1, 1);
         rect.right = rect.left + rect.width() * get_document()->m_thread.m_dProgress;
         pdc->FillSolidRect(rect, RGB(0, 128, 0));
      }

   }

   document * view::get_document()
   {
      return dynamic_cast < document * > (::userbase::view::get_document());
   }

} // namespace md5