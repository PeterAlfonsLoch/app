#include "StdAfx.h"
#include <math.h>


namespace alatel
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
      pdc->SetBkMode(TRANSPARENT);
      pdc->SelectClipRgn(NULL);

      class rect rectClient;

      GetClientRect(rectClient);

      ::imaging & imaging = Application.imaging();

      DWORD dwPeriod = 1984;


      if(GetTypedParent < alatel::frame >() == NULL || GetTypedParent < alatel::frame >()->GetParent() == NULL)
      {

         byte uchAlpha = (byte) (50 + (((sin(((((double)(::GetTickCount() % dwPeriod)) * 2.0 * 3.1415) / ((double) dwPeriod))) + 1.0) / 2.0) * 100));

         imaging.color_blend(pdc, rectClient, RGB(50, 185, 205), uchAlpha); 
      }
      else
      {
         pdc->FillSolidRect(rectClient, RGB(255, 255, 255));
      }


      ::ca::font_sp font(get_app());

      font->CreatePointFont(84 + min(rectClient.width(), rectClient.height()), "Times New Roman");


      string strTime;

      class time time = ::time::get_current_time();

      strTime = time.Format("%H:%M");

      pdc->SetTextColor(RGB(0, 84, 77));

      pdc->SelectObject(font);
      class size sizeText = pdc->GetTextExtent(strTime);
      pdc->TextOutA(rectClient.center().x - sizeText.cx / 2, rectClient.center().y - sizeText.cy / 2, strTime);

   }

} // namespace alatel