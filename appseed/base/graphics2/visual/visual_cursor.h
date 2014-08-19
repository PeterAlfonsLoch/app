#pragma once


namespace visual
{


   class CLASS_DECL_BASE cursor :
      virtual public ::object
   {
   public:


      e_cursor                m_ecursor;
      ::draw2d::dib_sp        m_dib;
      //::draw2d::dib_sp        m_dibWork;
      //::draw2d::dib_sp        m_dibWork2;
      size                    m_szHotspotOffset;

#ifdef WINDOWSEX

      HCURSOR                 m_hcursor;

#endif


      cursor(sp(::axis::application) papp);

      bool to(::draw2d::graphics * pgraphics, point pt);


#ifdef WINDOWSEX

      HCURSOR get_HCURSOR();

#endif


   };


   typedef sp(cursor) cursor_sp;


} // namespace visual



#ifdef WINDOWSEX

// Derived from Microsoft KB318876!!
// on 2014-06-29!! During World Cup Games 2014!! Oitavas de Final, third game between Nederland and Mexico!!
// Thank you God!!
// Thank you Microsoft!!
// Thank you Pappi!! Pelo passeio no Mercado Municipal de Curitiba com a Mummi e pelo almoço com o-bento de sushi e onigiri delicioso!!
// Obrigado Mummi por tudo!! E por hoje também e por propiciar isso tudo!! Por falar tão profundamente do Chico Xavier mesmo com muitas dúvidas minhas!!
// Obrigado Carlos!! Você poderia colaborar, não é!!
// Meu Deus me ajude!!

HBITMAP CreateAlphaBitmapV5(::draw2d::dib * pdib);
HICON CreateAlphaIcon(::draw2d::dib * pdib,bool bIcon = true,int xHotSpot = 0,int yHotSpot = 0);
HCURSOR CreateAlphaCursor(::draw2d::dib * pdib,int xHotSpot,int yHotSpot);

#endif