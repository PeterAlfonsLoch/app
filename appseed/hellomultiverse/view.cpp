#include "StdAfx.h"
#include <math.h>


namespace hellomultiverse
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::userbase::view(papp),
      m_dib(papp),
      m_dibColor(papp),
      m_font(papp)
   {

      m_dib.initialize(800, 600, 2);
      m_dibColor->create(800, 600);


      m_strHelloMultiverse = "Hello Multiverse!!";


      LOGFONT lf;
      memset(&lf, 0, sizeof(lf));
      strcpy(lf.lfFaceName, "Lucida Sans Unicode");
      lf.lfWeight = 800;
      lf.lfHeight = 240;
      m_font->CreatePointFontIndirect(&lf);


   }

   view::~view()
   {
   }

#ifdef _DEBUG
   void view::assert_valid() const
   {
	   ::userbase::view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
	   ::userbase::view::dump(dumpcontext);
   }
#endif 


   void view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }


   void view:: _001OnDraw(::ca::graphics * pdc)
   {

      rect rectClient;
      GetClientRect(rectClient);

      int iCount = 20;
      int i = ::GetTickCount()  / 100 % iCount;
      int iBlur;
      if(i <= (iCount / 2))
         iBlur = i;
      else
         iBlur = iCount - i;


      m_dib->Fill(0, 0, 0, 0);

      m_dib->get_graphics()->SetTextColor(RGB(255, 255, 255));
      m_dib->get_graphics()->SetBkMode(TRANSPARENT);
      m_dib->get_graphics()->SelectObject(m_font);

      m_dib->get_graphics()->TextOut(50, 50, m_strHelloMultiverse);

      m_dib.blur();
      for(int i = 0; i < iBlur; i++)
      {
         if((i % 2) == 0)
            m_dib.blur();
      }

      ::color c;


      double dPeriod = (1984 + 1977) * 11;

      c.set_hls(fmod(::GetTickCount(), dPeriod) / dPeriod, 0.49, 0.84);

      m_dibColor->Fill(c.m_uchR, c.m_uchG, c.m_uchB);

      m_dib->channel_copy(::visual::rgba::channel_alpha, ::visual::rgba::channel_green);
      m_dib->channel_from(::visual::rgba::channel_red, m_dibColor);
      m_dib->channel_from(::visual::rgba::channel_green, m_dibColor);
      m_dib->channel_from(::visual::rgba::channel_blue, m_dibColor);

      for(int i = 0; i < iBlur + 1; i++)
      {
         if((i % 2) == 1)
            System.imaging().true_blend(pdc, null_point(), rectClient.size(), m_dib->get_graphics(), null_point());
      }

      pdc->SelectObject(m_font);
      pdc->SetTextColor(RGB(255, 255, 255));
      pdc->SetBkMode(TRANSPARENT);
      pdc->TextOutA(50, 50, m_strHelloMultiverse);


   }



   document * view::get_document()
   {
      return dynamic_cast < document * > (::userbase::view::get_document());
   }

} // namespace hellomultiverse
