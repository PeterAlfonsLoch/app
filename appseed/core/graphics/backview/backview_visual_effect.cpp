#include "framework.h"


#ifndef APPLEOS
#define M_PI 3.14159265358979323846
#endif


namespace backview
{


   VisualEffect::VisualEffect(Main & main) :
      element(main.get_app()),
      Helper(main)
   {
   }

   VisualEffect::~VisualEffect()
   {
   }

   void VisualEffect::RenderBuffer(rect_array & recta)
   {
      Main & main = HelperGetMain();

      TransitionEffect & transitioneffect = main.GetTransitionEffect();

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         InitialRender();
      }

      Interface & iface = main.GetInterface();

      iface.BackViewGetClientRect(tool1.rectClient);

      tool1.cx = tool1.rectClient.width();
      tool1.cy = tool1.rectClient.height();
//         class imaging & imaging = System.visual().imaging();

      Graphics & graphics = main.GetGraphics();

//         ::core::draw_dib & drawdib = graphics.GetDrawDib();

      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      single_lock sl1Back(&graphics.m_mutex1Back, FALSE);
      single_lock sl2Buffer(&graphics.m_mutex2Buffer, FALSE);
      ::draw2d::graphics_sp dcBack = graphics.GetBackDC();
      ::draw2d::graphics_sp dcBuffer = graphics.GetBufferDC();
//         ::draw2d::graphics_sp dcFrame1 = graphics.GetFrame1DC();
//         ::draw2d::graphics_sp dcTransfer = graphics.GetFrame1DC();

      HelperGetMain().DeferCheckLayout();


      sl1Back.lock();
      sl2Buffer.lock();
      dcBack->SelectClipRgn(NULL);
      dcBuffer->SelectClipRgn(NULL);

      //m_iVisual = VisualEffectRotateEx5;
      m_iVisual = transitioneffect.m_iaVisual[transitioneffect.m_iVisual];
   //      m_iVisual = VisualEffectRotateEx5;
      switch(m_iVisual)
      {
      case VisualEffectPixelExplosion:
         RenderPixelExplosion(recta);
         break;
      case VisualEffectAlphaPixelExplosion:
         RenderAlphaPixelExplosion(recta);
         break;
      case VisualEffectPixelExplosion2:
         RenderPixelExplosion2(recta);
         break;
      case VisualEffectRotateEx8:
         RenderRotateEx8(recta);
         break;
      case VisualEffectRotateEx4:
         RenderRotateEx4(recta);
         break;
      case VisualEffectRain1:
         RenderRain1(recta);
         break;
      case VisualEffectRotateBlend:
      case VisualEffectRotateEx5:
         RenderRotateEx5(recta);
         break;
      case VisualEffectRotateEx6:
         RenderRotateEx5(recta);
         break;
      case VisualEffectRotateEx7:
         RenderRotateEx7(recta);
         break;
         RenderRotateBlend(recta);
         //RenderNPRotatecolor_blend_(recta);
         //RenderNPRotateTrackcolor_blend_(recta);
         break;
      case VisualEffectNoPrecisionRotateBlend:
         RenderNPRotateBlend(recta);
         //RenderNPRotateTrackcolor_blend_(recta);
         break;
      case VisualEffectNoPrecisionRotatecolor_blend_:
         RenderNPRotatecolor_blend_(recta);
         //RenderNPRotateTrackcolor_blend_(recta);
         break;
      case VisualEffectNoPrecisionRotateTrackcolor_blend_:
         RenderNPRotateTrackcolor_blend_(recta);
         break;
      case VisualEffectRotateEx1:
         RenderRotateEx1(recta);
         break;
      case VisualEffectRotateEx2:
         RenderRotateEx2(recta);
         break;
      case VisualEffectRotateEx3:
         RenderRotateEx3(recta);
         break;
      case VisualEffectExpand4:
         RenderExpand4(recta);
         break;
      case VisualEffectExpand5:
         RenderExpand5(recta);
         break;
      case VisualEffectExpand6:
         RenderExpand5(recta);
         break;
      case VisualEffectExpand7:
         RenderExpand7(recta);
         break;
      case VisualEffectExpand8:
         RenderExpand8(recta);
         break;
      default:
         ASSERT(FALSE);
         break;
      }

      single_lock sl(&graphics.m_mutex4Transfer, TRUE);
      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);
      ::draw2d::dib_sp pdibTransfer = graphics.GetDib(_graphics::DibTransfer);

      pdibTransfer->stretch_dib(pdibBack);
   }

   void VisualEffect::RenderRotateBlend(rect_array & recta)
   {
      Main & main = HelperGetMain();

      TransitionEffect & transitioneffect = main.GetTransitionEffect();


      rect rectClient = tool1.rectClient;

      Graphics & graphics = main.GetGraphics();

      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);
      ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
      ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
      ::draw2d::dib_sp pdib3 = graphics.GetDib(_graphics::DibTemp3);
      ::draw2d::dib_sp pdibBuffer = graphics.GetDib(_graphics::DibBuffer);

      int32_t cx1 = pdib1->m_size.cx;
      int32_t cy1 = pdib1->m_size.cy;

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         pdib2->create(cx1, cy1);
         pdib3->create(cx1, cy1);
      }



#ifdef WINDOWSEX

      GdiFlush();

#endif

      pdib3->stretch_dib(pdibBuffer);

      StepGrow001(
         m_color,
         m_iGrowColor,
         m_iGrowMax);

      double dAngleOffset = 1.0 * rand() / RAND_MAX;
      if(m_iGrowColor >= 0)
      {
         //m_iGrowColor++;
         m_dAngle += 8.3 + dAngleOffset;
         //if(m_iGrowColor >= 100)
           // m_iGrowColor = -1;
      }
      else
      {
         //m_iGrowColor--;
         m_dAngle -= 8.3 + dAngleOffset;
         //if(m_iGrowColor <= -100)
           // m_iGrowColor = 1;
      }
      pdib2->rotate(pdib3, m_dAngle, 1.009);
   /*   imaging.color_blend(pdib1->get_graphics(), cxm - s1, cym - s2, s3, s4, m_color.get_rgb(), bA);


      // top
      imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 - 1, 1, m_color.get_rgb(), bA);
      // left
      imaging.color_blend(pdib1->get_graphics(), 0, 0, 1, cy1 - 1, m_color.get_rgb(), bA);
      // bottom
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 - 1, cx1 - 1, 1, m_color.get_rgb(), bA);
      // right
      imaging.color_blend(pdib1->get_graphics(), cx1 - 2, 0, 1, cy1 - 1, m_color.get_rgb(), bA);*/


      /*imaging.bitmap_blend(
         pdib1->get_graphics(),
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0,
         50);*/


      pdib2->channel_multiply(::visual::rgba::channel_alpha, 10.0 / 255.0);

      pdib1->get_graphics()->BitBlt(
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0, SRCCOPY);


      pdibBack->stretch_dib(pdib1);

      //dcBack->FillSolidRect(0, 0, cx, cy, ARGB(255, 0, 0, 0));
      //dcBack->FillSolidRect(100, 100, cx, cy, ARGB(255, 255, 255, 255));

      recta.add(rectClient);
   }

   void VisualEffect::RenderNPRotateBlend(rect_array & recta)
   {
      Main & main = HelperGetMain();

      TransitionEffect & transitioneffect = main.GetTransitionEffect();


      rect rectClient = tool1.rectClient;
      tool1.cx = rectClient.width();
      tool1.cy = rectClient.height();
      class imaging & imaging = System.visual().imaging();

      Graphics & graphics = main.GetGraphics();

      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);
      ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
      ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
      ::draw2d::dib_sp pdib3 = graphics.GetDib(_graphics::DibTemp3);

      int32_t cx1 = pdib1->m_size.cx;
      int32_t cy1 = pdib1->m_size.cy;
      int32_t cxm = cx1 / 2;
      int32_t cym = cy1 / 2;

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         pdib2->create(cx1, cy1);
         pdib3->create(cx1, cy1);
      }


      int32_t s1 = rand() * 1 / RAND_MAX + 1;
      int32_t s2 = rand() * 1 / RAND_MAX + 1;
      int32_t s3 = rand() * 2 / RAND_MAX + 1;
      int32_t s4 = rand() * 2 / RAND_MAX + 1;

      StepGrow001(
         m_color,
         m_iGrowColor,
         m_iGrowMax);





         //RGB(255, rand() * 255 / RAND_MAX,
         //rand() * 255 / RAND_MAX,
         //rand() * 255 / RAND_MAX);

      BYTE bA = 50;

#ifdef WINDOWSEX
      GdiFlush();
#endif
      //double dmin = min(cx, cy);
      //double dmax = max(cx, cy);abs


     // ::draw2d::graphics_sp pdib3->get_graphics();
      //pdib3->get_graphics()->CreateCompatibleDC(NULL);
      //pdib3->get_graphics()->SelectObject(pdib3->m_hbitmap);

   //   pdib3->stretch_dib(pdibBuffer);

   //   pdib3->Paste(pdib1);



      double dAngleOffset = (20.0 * rand() / RAND_MAX) - 5.0;
      double dAngle;
      if(m_iGrowColor >= 0)
      {
         dAngle = 10.111 + dAngleOffset;
      }
      else
      {
         dAngle = -10.111 - dAngleOffset;
      }
      pdib2->rotate(pdib1, dAngle, 1.009);
      imaging.color_blend(pdib1->get_graphics(), cxm - s1, cym - s2, s3, s4, m_color.get_rgb(), bA);


      // top
      imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 - 1, 1, m_color.get_rgb(), bA);
      // left
      imaging.color_blend(pdib1->get_graphics(), 0, 0, 1, cy1 - 1, m_color.get_rgb(), bA);
      // bottom
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 - 1, cx1 - 1, 1, m_color.get_rgb(), bA);
      // right
      imaging.color_blend(pdib1->get_graphics(), cx1 - 2, 0, 1, cy1 - 1, m_color.get_rgb(), bA);


      /*imaging.bitmap_blend(
         pdib1->get_graphics(),
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0,
         50);*/

      /*BLENDFUNCTION bf;

      bf.BlendOp     = AC_SRC_OVER;
      bf.BlendFlags  = 0;
      bf.SourceConstantAlpha = 10;
   //   bf.AlphaFormat = AC_SRC_ALPHA;
      bf.AlphaFormat = 0;*/

      pdib2->channel_multiply(::visual::rgba::channel_alpha, 10.0 / 255.0);

      pdib1->get_graphics()->BitBlt(
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0, SRCCOPY);

      pdibBack->stretch_dib(pdib1);

      recta.add(rectClient);
   }

   void VisualEffect::RenderNPRotatecolor_blend_(rect_array & recta)
   {
      Main & main = HelperGetMain();

      TransitionEffect & transitioneffect = main.GetTransitionEffect();

      rect rectClient = tool1.rectClient;
      tool1.cx = rectClient.width();
      tool1.cy = rectClient.height();
      class imaging & imaging = System.visual().imaging();

      Graphics & graphics = main.GetGraphics();

      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);
      ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
      ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
      ::draw2d::dib_sp pdib3 = graphics.GetDib(_graphics::DibTemp3);

      int32_t cx1 = pdib1->m_size.cx;
      int32_t cy1 = pdib1->m_size.cy;
      int32_t cxm = cx1 / 2;
      int32_t cym = cy1 / 2;

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         pdib2->create(cx1, cy1);
         pdib3->create(cx1, cy1);
      }


      int32_t s1 = rand() * 1 / RAND_MAX + 1;
      int32_t s2 = rand() * 1 / RAND_MAX + 1;
      int32_t s3 = rand() * 2 / RAND_MAX + 1;
      int32_t s4 = rand() * 2 / RAND_MAX + 1;

      int32_t c1 = rand() * (cx1 - 10) / RAND_MAX + 1;
      int32_t c2 = rand() * (cy1 - 10) / RAND_MAX + 1;
      int32_t c3 = rand() * 10 / RAND_MAX + 1;
      int32_t c4 = rand() * 10 / RAND_MAX + 1;

      StepGrow001(
         m_color,
         m_iGrowColor,
         m_iGrowMax);





//            ARGB(255, rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX);

      BYTE bA = 50;


#ifdef WINDOWSEX
      GdiFlush();
#endif

      //double dmin = min(cx, cy);
      //double dmax = max(cx, cy);abs


     // ::draw2d::graphics_sp pdib3->get_graphics();
      //pdib3->get_graphics()->CreateCompatibleDC(NULL);
      //pdib3->get_graphics()->SelectObject(pdib3->m_hbitmap);

   //   pdib3->stretch_dib(pdibBuffer);

   //   pdib3->Paste(pdib1);



      double dAngleOffset = (20.0 * rand() / RAND_MAX) - 5.0;
      double dAngle;
      if(m_iGrowColor >= 0)
      {
         dAngle = 10.111 + dAngleOffset;
      }
      else
      {
         dAngle = -10.111 - dAngleOffset;
      }
      pdib2->rotate(pdib1, dAngle, 1.009);
      imaging.color_blend(pdib1->get_graphics(), cxm - s1, cym - s2, s3, s4, m_color.get_rgb(), bA);


      // top
      imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 - 1, 1, m_color.get_rgb(), bA);
      // left
      imaging.color_blend(pdib1->get_graphics(), 0, 0, 1, cy1 - 1, m_color.get_rgb(), bA);
      // bottom
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 - 1, cx1 - 1, 1, m_color.get_rgb(), bA);
      // right
      imaging.color_blend(pdib1->get_graphics(), cx1 - 2, 0, 1, cy1 - 1, m_color.get_rgb(), bA);


      imaging.color_blend(pdib1->get_graphics(), c1, c2, c3, c4, m_color.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 - c1, cy1 - c2, c3, c4, m_color.get_rgb(), bA);

      /*imaging.bitmap_blend(
         pdib1->get_graphics(),
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0,
         50);*/

      pdib2->channel_multiply(::visual::rgba::channel_alpha, 10.0 / 255.0);

      pdib1->get_graphics()->BitBlt(
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0, SRCCOPY);

      pdibBack->stretch_dib(pdib1);

      recta.add(rectClient);
   }

   void VisualEffect::RenderNPRotateTrackcolor_blend_(rect_array & recta)
   {
      Main & main = HelperGetMain();

      TransitionEffect & transitioneffect = main.GetTransitionEffect();

      rect rectClient = tool1.rectClient;
      tool1.cx = rectClient.width();
      tool1.cy = rectClient.height();
      class imaging & imaging = System.visual().imaging();

      Graphics & graphics = main.GetGraphics();

      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);
      ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
      ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
      ::draw2d::dib_sp pdib3 = graphics.GetDib(_graphics::DibTemp3);

      int32_t cx1 = pdib1->m_size.cx;
      int32_t cy1 = pdib1->m_size.cy;
      int32_t cxm = cx1 / 2;
      int32_t cym = cy1 / 2;

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         pdib2->create(cx1, cy1);
         pdib3->create(cx1, cy1);
      }

      int32_t s1 = rand() * 1 / RAND_MAX + 1;
      int32_t s2 = rand() * 1 / RAND_MAX + 1;
      int32_t s3 = rand() * 2 / RAND_MAX + 1;
      int32_t s4 = rand() * 2 / RAND_MAX + 1;

      m_rndgrowVelocity.Step();
      if(m_rndgrowDirectionLatency.Step())
      {
         m_dDirection = ((int32_t) m_dDirection % 360);
         m_dDirectionAddUp = 4.0 * rand() / RAND_MAX - 2.0;

      }
      m_dDirection += m_dDirectionAddUp;

      double dcos = ::cos(m_dDirection * M_PI / 180.0);
      double dsin = ::sin(m_dDirection * M_PI / 180.0);

      StepGrow001(
         m_color,
         m_iGrowColor,
         m_iGrowMax);

      m_ptColorTrack.x += (LONG) (abs(m_rndgrowVelocity.i) * dcos);
      m_ptColorTrack.y += (LONG) (abs(m_rndgrowVelocity.i) * dsin);

      if(m_ptColorTrack.x > cx1 - 10)
      {
   //      m_dDirection += 180 + ((int32_t) m_dDirection % 360);
         m_dDirection = -m_dDirection;
      }
      else if(m_ptColorTrack.y > cy1 - 10)
      {
     //    m_dDirection += 180 + ((int32_t) m_dDirection % 360);
         m_dDirection = -m_dDirection;
      }
      else if(m_ptColorTrack.x < 0)
      {
       //  m_dDirection += 180 + ((int32_t) m_dDirection % 360);
         m_dDirection = -m_dDirection;
      }
      else if(m_ptColorTrack.y < 0)
      {
         //m_dDirection += 180 + ((int32_t) m_dDirection % 360);
         m_dDirection = -m_dDirection;
      }

      if(m_ptColorTrack.x > cx1 - 10)
      {
         m_ptColorTrack.x = cx1 - 10;
      }
      else if(m_ptColorTrack.x < 0)
      {
         m_ptColorTrack.x = 0;
      }

      if(m_ptColorTrack.y > cy1 - 10)
      {
         m_ptColorTrack.y = cy1 - 10;
      }
      else if(m_ptColorTrack.y < 0)
      {
         m_ptColorTrack.y = 0;
      }


//
//            ARGB(255, rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX);

      BYTE bA = 50;


#ifdef WINDOWSEX
      GdiFlush();
#endif

      //double dmin = min(cx, cy);
      //double dmax = max(cx, cy);abs

     // ::draw2d::graphics_sp pdib3->get_graphics();
      //pdib3->get_graphics()->CreateCompatibleDC(NULL);
      //pdib3->get_graphics()->SelectObject(pdib3->m_hbitmap);

   //   pdib3->stretch_dib(pdibBuffer);

   //   pdib3->Paste(pdib1);

//         int32_t c1 = rand() * 3 / RAND_MAX;
//         int32_t c2 = rand() * 3 / RAND_MAX;
      int32_t c3 = rand() * 10 / RAND_MAX + 1;
//         int32_t c4 = rand() * 10 / RAND_MAX + 1;


      double dAngleOffset = (20.0 * rand() / RAND_MAX) - 5.0;
      double dAngle;
      if(m_iGrowColor >= 0)
      {


         dAngle = 10.111 + dAngleOffset;
      }
      else
      {

         dAngle = -10.111 - dAngleOffset;
      }
      pdib2->rotate(pdib1, dAngle, 1.009);
      imaging.color_blend(pdib1->get_graphics(), cxm - s1, cym - s2, s3, s4, m_color.get_rgb(), bA);


      // top
      imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 - 1, 1, m_color.get_rgb(), bA);
      // left
      imaging.color_blend(pdib1->get_graphics(), 0, 0, 1, cy1 - 1, m_color.get_rgb(), bA);
      // bottom
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 - 1, cx1 - 1, 1, m_color.get_rgb(), bA);
      // right
      imaging.color_blend(pdib1->get_graphics(), cx1 - 2, 0, 1, cy1 - 1, m_color.get_rgb(), bA);


      {
         int32_t x1 = m_ptColorTrack.x;
         int32_t y1 = m_ptColorTrack.y;
         int32_t x2 = cx1 - x1;
         int32_t y2 = cy1 - y1;
         ::draw2d::brush_sp brush(allocer(), m_color.get_rgb() | (255 << 24));
         pdib1->get_graphics()->SelectObject(brush);
         //imaging.color_blend(pdib1->get_graphics(), x, y, c3, c4, m_color.get_rgb(), bA);
         //imaging.color_blend(pdib1->get_graphics(), cx1 - x, cy1 - y, c3, c4, m_color.get_rgb(), bA);
         pdib1->get_graphics()->FillEllipse(x1, y1, x1 + c3, y1 + c3);
         pdib1->get_graphics()->FillEllipse(x2 - c3, y2 - c3, x2, y2);
      }

      /*imaging.bitmap_blend(
         pdib1->get_graphics(),
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0,
         50);*/

      pdib2->channel_multiply(::visual::rgba::channel_alpha, 10.0 / 255.0);

      pdib1->get_graphics()->BitBlt(
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0, SRCCOPY);

      pdibBack->stretch_dib(pdib1);

      recta.add(rectClient);
   }


   void VisualEffect::InitialRender()
   {
      tool1.page = 0;
         Main & main = HelperGetMain();

      Interface & iface = main.GetInterface();

//         TransitionEffect & transitioneffect = main.GetTransitionEffect();

      rect rectClient;
      iface.BackViewGetClientRect(rectClient);
      tool1.rectClient = rectClient;

      int32_t cx = rectClient.width();
      int32_t cy = rectClient.height();
//         class imaging & imaging = System.visual().imaging();

      Graphics & graphics = main.GetGraphics();

//         ::core::draw_dib & drawdib = graphics.GetDrawDib();



      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      single_lock sl1Back(&graphics.m_mutex1Back, FALSE);
      single_lock sl2Buffer(&graphics.m_mutex2Buffer, FALSE);
      ::draw2d::graphics_sp dcBack = graphics.GetBackDC();
      ::draw2d::graphics_sp dcBuffer = graphics.GetBufferDC();
//         ::draw2d::graphics_sp dcFrame1 = graphics.GetFrame1DC();

      sl1Back.lock();
      sl2Buffer.lock();
      dcBack->SelectClipRgn(NULL);
      dcBuffer->SelectClipRgn(NULL);

      dcBack->BitBlt(0, 0, cx, cy, dcBuffer, 0, 0, SRCCOPY);
      ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
//         ::draw2d::dib_sp pdibBuffer = graphics.GetDib(_graphics::DibBuffer);
      ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
//         ::draw2d::dib_sp pdibTransfer = graphics.GetDib(_graphics::DibTransfer);


      int32_t cx1 = cx / 4 + 1;
      int32_t cy1 = cy / 4 + 1;

      m_explosion.create(cx1, cy1);
      m_explosion.Reset();

      if(m_iVisual == VisualEffectRotateEx5)
      {
         cx1 = cx / 5;
         cy1 = cy / 5;
      }

      pdib1->create(cx1, cy1);
      pdib2->create(cx, cy);

      point      m_ptColorTrack;

      m_rndgrowVelocity.i = 0;
      m_rndgrowVelocity.lbound = 1;
      m_rndgrowVelocity.maxlbound = 1;
      m_rndgrowVelocity.maxubound = 5;
      m_dDirection = 360.0 * rand() / RAND_MAX;
      m_dDirectionAddUp = 0.5;
      m_rndgrowDirectionLatency.i = 0;
      m_rndgrowDirectionLatency.lbound = 0;
      m_rndgrowDirectionLatency.maxlbound = 50;
      m_rndgrowDirectionLatency.maxubound = 100;

      m_colortrack1a.allocate(12);
      for(int32_t i = 0; i < m_colortrack1a.get_size(); i++)
      {
         ColorTrack1 & ct1 = m_colortrack1a[i];
         ct1.m_rndgrowVelocity.i = 0;
         ct1.m_rndgrowVelocity.lbound = 1;
         ct1.m_rndgrowVelocity.maxlbound = 1;
         ct1.m_rndgrowVelocity.maxubound = 5;
         ct1.m_dDirection = 360.0 * rand() / RAND_MAX;
         ct1.m_dDirectionAddUp = 0.5;
         ct1.m_rndgrowDirectionLatency.i = 0;
         ct1.m_rndgrowDirectionLatency.lbound = 0;
         ct1.m_rndgrowDirectionLatency.maxlbound = 50;
         ct1.m_rndgrowDirectionLatency.maxubound = 100;
      }

      m_rndgrowAngleOffsetLatency.i = 0;
      m_rndgrowAngleOffsetLatency.lbound = 0;
      m_rndgrowAngleOffsetLatency.maxlbound = 100;
      m_rndgrowAngleOffsetLatency.maxubound = 200;

      m_dAngle = 0.0;

   }

   int32_t VisualEffect::GetEffectCount()
   {
      return (int32_t) VisualEffectEnd;
   }

   void VisualEffect::StepGrow001(
         color & color,
         int32_t & iGrowColor,
         int32_t & iGrowMax)
   {
      double dH;
      double dL;
      double dS;
      color.get_hls(dH, dL, dS);
      dL = 0.7;
      dS = 0.7;
      if(iGrowColor >= 0)
      {
         iGrowColor++;
         if(iGrowMax <= 0)
         {
            iGrowMax = 100 * rand() / RAND_MAX + 20;
         }
         else if(iGrowMax > 120)
         {
            iGrowMax = 120;
         }
         if(iGrowColor > iGrowMax)
            iGrowColor = -1;

         dH += rand() * 0.003 / RAND_MAX;

         if(dH >= 1.0)
         {
            dH = 1.0;
            iGrowColor = -1;
         }
      }
      else
      {
         iGrowColor--;
         if(iGrowMax >= 0)
         {
            iGrowMax = -100 * rand() / RAND_MAX - 20;
         }
         else if(iGrowMax < -120)
         {
            iGrowMax = -120;
         }
         if(iGrowColor < iGrowMax)
            iGrowColor = 1;

         dH -= rand() * 0.003 / RAND_MAX;

         if(dH < 0.0)
         {
            dH = 0.0;
            iGrowColor = 1;
         }
      }

      color.set_hls(dH, dL, dS);

   }

   void VisualEffect::StepGrow034(
         color & color,
         int32_t & iGrowColor,
         int32_t & iGrowMax)
   {
      double dH;
      double dL;
      double dS;
      color.get_hls(dH, dL, dS);
      dL = 0.7;
      dS = 0.7;
      if(iGrowColor >= 0)
      {
         iGrowColor++;
         if(iGrowMax <= 0)
         {
            iGrowMax = 100 * rand() / RAND_MAX + 20;
         }
         else if(iGrowMax > 120)
         {
            iGrowMax = 120;
         }
         if(iGrowColor > iGrowMax)
            iGrowColor = -1;

         dH += rand() * 0.003 / RAND_MAX;

         if(dH >= 1.0)
         {
            dH = 1.0;
            iGrowColor = -1;
         }
      }
      else
      {
         iGrowColor--;
         if(iGrowMax >= 0)
         {
            iGrowMax = -100 * rand() / RAND_MAX - 20;
         }
         else if(iGrowMax < -120)
         {
            iGrowMax = -120;
         }
         if(iGrowColor < iGrowMax)
            iGrowColor = 1;

         dH -= rand() * 0.003 / RAND_MAX;

         if(dH < 0.0)
         {
            dH = 0.0;
            iGrowColor = 1;
         }
      }

      color.set_hls(dH, dL, dS);

   }

   void VisualEffect::StepGrow001(
         color & color,
         int32_t & iGrowColor,
         int32_t & iGrowMax,
         bool & bGrowColor)
   {
      double dH;
      double dL;
      double dS;
      color.get_hls(dH, dL, dS);
      dL = 0.7;
      dS = 0.7;
      if(iGrowColor >= 0)
      {
         bGrowColor = false;
         iGrowColor++;
         if(iGrowMax <= 0)
         {
            iGrowMax = 100 * rand() / RAND_MAX + 20;
         }
         else if(iGrowMax > 120)
         {
            iGrowMax = 120;
         }
         if(iGrowColor > iGrowMax)
         {
            bGrowColor = true;
            iGrowColor = -1;
         }

         dH += rand() * 0.003 / RAND_MAX;

         if(dH >= 1.0)
         {
            dH = 1.0;
            iGrowColor = -1;
            bGrowColor = true;
         }
      }
      else
      {
         bGrowColor = false;
         iGrowColor--;
         if(iGrowMax >= 0)
         {
            iGrowMax = -100 * rand() / RAND_MAX - 20;
         }
         else if(iGrowMax < -120)
         {
            iGrowMax = -120;
         }
         if(iGrowColor < iGrowMax)
         {
            bGrowColor = true;
            iGrowColor = 1;
         }

         dH -= rand() * 0.003 / RAND_MAX;

         if(dH < 0.0)
         {
            dH = 0.0;
            iGrowColor = 1;
            bGrowColor = true;
         }
      }

      color.set_hls(dH, dL, dS);

   }


   bool VisualEffect::RandomGrow::Step()
   {
      bool b = false;

      if(i >= 0)
      {
         i++;
         if(imax <= 0)
         {
            ASSERT(maxubound >= 0);
            ASSERT(maxlbound >= 0);
            imax = (maxubound - maxlbound) * rand() / RAND_MAX + maxlbound;
         }
         else if(imax > maxubound)
         {
            imax = maxubound;
         }
         if(i > imax)
         {
            i = -lbound;
            b = true;
         }

      }
      else
      {
         i--;
         if(imax >= 0)
         {
            ASSERT(maxubound >= 0);
            ASSERT(maxlbound >= 0);
            imax = (maxlbound - maxubound) * rand() / RAND_MAX - maxlbound;
         }
         else if(imax < -maxubound)
         {
            imax = -maxubound;
         }
         if(i < imax)
         {
            i = lbound;
            b = true;
         }
      }
      return b;
   }
   void VisualEffect::RenderRotateEx1(rect_array & recta)
   {
      Main & main = HelperGetMain();

      TransitionEffect & transitioneffect = main.GetTransitionEffect();

      rect rectClient = tool1.rectClient;

      tool1.cx = rectClient.width();
      tool1.cy = rectClient.height();
      class imaging & imaging = System.visual().imaging();

      Graphics & graphics = main.GetGraphics();

      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);
      ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
      ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
      ::draw2d::dib_sp pdib3 = graphics.GetDib(_graphics::DibTemp3);

      int32_t cx1 = pdib1->m_size.cx;
      int32_t cy1 = pdib1->m_size.cy;
      int32_t cxm = cx1 / 2;
      int32_t cym = cy1 / 2;

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         pdib2->create(cx1, cy1);
         pdib3->create(cx1, cy1);
      }

      int32_t s1 = rand() * 1 / RAND_MAX + 1;
      int32_t s2 = rand() * 1 / RAND_MAX + 1;
      int32_t s3 = rand() * 2 / RAND_MAX + 1;
      int32_t s4 = rand() * 2 / RAND_MAX + 1;

      m_rndgrowVelocity.Step();
      if(m_rndgrowDirectionLatency.Step())
      {
         m_dDirection = ((int32_t) m_dDirection % 360);
         m_dDirectionAddUp = 4.0 * rand() / RAND_MAX - 2.0;

      }
      m_dDirection += m_dDirectionAddUp;

      double dcos = ::cos(m_dDirection * M_PI / 180.0);
      double dsin = ::sin(m_dDirection * M_PI / 180.0);

      StepGrow001(
         m_color,
         m_iGrowColor,
         m_iGrowMax);

      color colorStrong = m_color;

      double dH;
      double dL;
      double dS;
      colorStrong.get_hls(dH, dL, dS);
      dL = 0.3;
      dS = 0.8;
      colorStrong.set_hls(dH, dL, dS);




      m_ptColorTrack.x += (LONG) (abs(m_rndgrowVelocity.i) * dcos);
      m_ptColorTrack.y += (LONG) (abs(m_rndgrowVelocity.i) * dsin);

      if(m_ptColorTrack.x > cx1 - 10)
      {
         m_dDirection += 180 + ((int32_t) m_dDirection % 360);
      }
      else if(m_ptColorTrack.y > cy1 - 10)
      {
         m_dDirection += 180 + ((int32_t) m_dDirection % 360);
      }
      else if(m_ptColorTrack.x < 0)
      {
         m_dDirection += 180 + ((int32_t) m_dDirection % 360);
      }
      else if(m_ptColorTrack.y < 0)
      {
         m_dDirection += 180 + ((int32_t) m_dDirection % 360);
      }

      if(m_ptColorTrack.x > cx1 - 10)
      {
         m_ptColorTrack.x = cx1 - 10;
      }
      else if(m_ptColorTrack.x < 0)
      {
         m_ptColorTrack.x = 0;
      }

      if(m_ptColorTrack.y > cy1 - 10)
      {
         m_ptColorTrack.y = cy1 - 10;
      }
      else if(m_ptColorTrack.y < 0)
      {
         m_ptColorTrack.y = 0;
      }



//            ARGB(255, rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX);

      BYTE bA = 200;


#ifdef WINDOWSEX
      GdiFlush();
#endif

      //double dmin = min(cx, cy);
      //double dmax = max(cx, cy);abs

     // ::draw2d::graphics_sp pdib3->get_graphics();
      //pdib3->get_graphics()->CreateCompatibleDC(NULL);
      //pdib3->get_graphics()->SelectObject(pdib3->m_hbitmap);

   //   pdib3->stretch_dib(pdibBuffer);

   //   pdib3->Paste(pdib1);

//         int32_t c1 = rand() * 3 / RAND_MAX;
//         int32_t c2 = rand() * 3 / RAND_MAX;
      int32_t c3 = rand() * 10 / RAND_MAX + 1;
//         int32_t c4 = rand() * 10 / RAND_MAX + 1;


      double dAngleOffset = (20.0 * rand() / RAND_MAX) - 5.0;
      double dAngle;
      if(m_iGrowColor >= 0)
      {


         dAngle = 10.111 + dAngleOffset;
      }
      else
      {

         dAngle = -10.111 - dAngleOffset;
      }
      pdib2->rotate(pdib1, dAngle, 1.009);
      //pdib2->rotate(pdib1, dAngle, 0.9);
      //pdib2->Paste(pdib1);
      imaging.color_blend(pdib2->get_graphics(), cxm - s1, cym - s2, s3, s4, m_color.get_rgb(), bA);


      // top
      imaging.color_blend(pdib2->get_graphics(), 0, 0, cx1 - 1, 1, m_color.get_rgb(), bA);
      // left
      imaging.color_blend(pdib2->get_graphics(), 0, 0, 1, cy1 - 1, m_color.get_rgb(), bA);
      // bottom
      imaging.color_blend(pdib2->get_graphics(), 0, cy1 - 1, cx1 - 1, 1, m_color.get_rgb(), bA);
      // right
      imaging.color_blend(pdib2->get_graphics(), cx1 - 2, 0, 1, cy1 - 1, m_color.get_rgb(), bA);


      {
         int32_t d = c3;
         int32_t r = d / 2;
         int32_t x1 = m_ptColorTrack.x - r;
         int32_t y1 = m_ptColorTrack.y - r;
         int32_t x2 = cx1 - x1 - r;
         int32_t y2 = cy1 - y1 - r;
         ::draw2d::brush_sp brush(allocer());
         brush->create_solid(colorStrong.get_rgb() | (255 << 24));
         pdib2->get_graphics()->SelectObject(brush);
         //imaging.color_blend(pdib1->get_graphics(), x, y, c3, c4, m_color.get_rgb(), bA);
         //imaging.color_blend(pdib1->get_graphics(), cx1 - x, cy1 - y, c3, c4, m_color.get_rgb(), bA);
         pdib2->get_graphics()->FillEllipse(x1, y1, x1 + d, y1 + d);
         pdib2->get_graphics()->FillEllipse(x2 - d, y1, x2, y1 + d);
         pdib2->get_graphics()->FillEllipse(x1, y2 - d, x1 + d, y2);
         pdib2->get_graphics()->FillEllipse(x2 - d, y2 - d, x2, y2);
      }

      /*imaging.bitmap_blend(
         pdib1->get_graphics(),
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0,
         50);*/

      pdib2->channel_multiply(::visual::rgba::channel_alpha, 10.0 / 255.0);

      pdib1->get_graphics()->BitBlt(
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0, SRCCOPY);

      pdibBack->stretch_dib(pdib1);

      recta.add(rectClient);
   }
   void VisualEffect::RenderRotateEx2(rect_array & recta)
   {
      Main & main = HelperGetMain();

      TransitionEffect & transitioneffect = main.GetTransitionEffect();

      Graphics & graphics = main.GetGraphics();

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
         m_color.set_rgb(pdib1->GetPixel(
            pdib1->m_size.cx / 2,
            pdib1->m_size.cy / 2));
      }



      rect rectClient = tool1.rectClient;
      tool1.cx = rectClient.width();
      tool1.cy = rectClient.height();

      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);
      ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
      ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
      ::draw2d::dib_sp pdib3 = graphics.GetDib(_graphics::DibTemp3);

      int32_t cx1 = pdib1->m_size.cx;
      int32_t cy1 = pdib1->m_size.cy;

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         pdib2->create(cx1, cy1);
         pdib3->create(cx1, cy1);
      }


      rect rcTrackBox;

      rcTrackBox.left   = cx1 * 4 / 9;
      rcTrackBox.top    = cy1 * 4 / 9;
      rcTrackBox.right  = cx1 - rcTrackBox.left;
      rcTrackBox.bottom = cy1 - rcTrackBox.top;

      for(int32_t i = 0; i < m_colortrack1a.get_size(); i++)
      {
         ColorTrack1 & ct1 = m_colortrack1a[i];
         ct1.m_rndgrowVelocity.Step();
         TrackDirection001(
            ct1.m_dDirection,
            ct1.m_dDirectionAddUp,
            ct1.m_rndgrowDirectionLatency);
         ct1.m_dCos = ::cos(ct1.m_dDirection * M_PI / 180.0);
         ct1.m_dSin = ::sin(ct1.m_dDirection * M_PI / 180.0);
         ct1.m_ptColorTrack.x += (LONG) (abs(ct1.m_rndgrowVelocity.i) * ct1.m_dCos);
         ct1.m_ptColorTrack.y += (LONG) (abs(ct1.m_rndgrowVelocity.i) * ct1.m_dSin);
         Constraint001(
            ct1.m_ptColorTrack,
            rcTrackBox,
            ct1.m_dDirection);
         ct1.m_dSize = rand() * 5 / RAND_MAX + 1;
      }

      StepGrow001(
         m_color,
         m_iGrowColor,
         m_iGrowMax);

      StepGrow001(
         m_color2,
         m_iGrowColor2,
         m_iGrowMax2);

      StepGrow001(
         m_color3,
         m_iGrowColor3,
         m_iGrowMax3);

      StepGrow001(
         m_color4,
         m_iGrowColor4,
         m_iGrowMax4);

      color colorStrong1 = m_color;
      color colorStrong2 = m_color2;
      color colorStrong3 = m_color3;
      color colorStrong4 = m_color4;
      color colorStrong5;

      {
         double dH;
         double dL;
         double dS;
         colorStrong1.get_hls(dH, dL, dS);
         dL = 0.3;
         dS = 0.8;
         colorStrong1.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong2.get_hls(dH, dL, dS);
         dL = 0.9;
         dS = 0.5;
         colorStrong2.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong2.get_hls(dH, dL, dS);
         dL = 0.9;
         dS = 0.7;
         colorStrong3.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong4.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong4.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong4.get_hls(dH, dL, dS);
         dL = 0.5;
         dS = 0.5;
         colorStrong5.set_hls(dH, dL, dS);
      }



//            ARGB(255, rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX);

//         BYTE bA = 200;


#ifdef WINDOWSEX
      GdiFlush();
#endif

      //double dmin = min(cx, cy);
      //double dmax = max(cx, cy);abs

     // ::draw2d::graphics_sp pdib3->get_graphics();
      //pdib3->get_graphics()->CreateCompatibleDC(NULL);
      //pdib3->get_graphics()->SelectObject(pdib3->m_hbitmap);

   //   pdib3->stretch_dib(pdibBuffer);

   //   pdib3->Paste(pdib1);

//         int32_t c1 = rand() * 3 / RAND_MAX;
//         int32_t c2 = rand() * 3 / RAND_MAX;
//         int32_t c4 = rand() * 10 / RAND_MAX + 1;


      m_rndgrowAngleOffsetLatency.Step();
      if(m_rndgrowAngleOffsetLatency.i == 0)
      {
         m_dAngleOffsetAddUp = (4.0 * rand() / RAND_MAX) - 2.0;
      }
      m_dAngleOffset += m_dAngleOffsetAddUp;
      m_dAngleOffset = fmod(m_dAngleOffset, 360.0);

      double dAngleOffset = m_dAngleOffset;
      double dAngle;
      if(m_iGrowColor >= 0)
      {


         dAngle = 0.111 + dAngleOffset;
      }
      else
      {

         dAngle = -0.111 - dAngleOffset;
      }
      //pdib2->rotate(pdib1, dAngle, 1.009);
      pdib2->Rotate034(pdib1, dAngle, 0.8);
      //pdib2->Paste(pdib1);
   //   imaging.color_blend(pdib2->get_graphics(), cxm - s1, cym - s2, s3, s4, m_color.get_rgb(), bA);


      // top
      /*imaging.color_blend(pdib2->get_graphics(), 0, 0, cx1 - 1, 1, m_color.get_rgb(), bA);
      // left
      imaging.color_blend(pdib2->get_graphics(), 0, 0, 1, cy1 - 1, m_color.get_rgb(), bA);
      // bottom
      imaging.color_blend(pdib2->get_graphics(), 0, cy1 - 1, cx1 - 1, 1, m_color.get_rgb(), bA);
      // right
      imaging.color_blend(pdib2->get_graphics(), cx1 - 2, 0, 1, cy1 - 1, m_color.get_rgb(), bA);*/


      {
         ::draw2d::pen_sp pen1(allocer());
         pen1->create_solid(1.0, colorStrong1.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush1(allocer(), colorStrong1.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen2(allocer());
         pen2->create_solid(1.0, colorStrong2.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush2(allocer(), colorStrong2.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen3(allocer());
         pen3->create_solid(1.0, colorStrong3.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush3(allocer(), colorStrong3.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen4(allocer());
         pen4->create_solid(1.0, colorStrong4.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush4(allocer(), colorStrong4.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen5(allocer());
         pen5->create_solid(1.0, colorStrong5.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush5(allocer(), colorStrong5.get_rgb() | (255 << 24));
         for(int32_t i = 0; i < m_colortrack1a.get_size(); i++)
         {
            ColorTrack1 & ct1 = m_colortrack1a[i];
            int32_t x1 = ct1.m_ptColorTrack.x;
            int32_t y1 = ct1.m_ptColorTrack.y;
            int32_t d = (int32_t) ct1.m_dSize;
            switch(i % 5)
            {
            case 0:
               {
                  pdib2->get_graphics()->SelectObject(brush1);
                  pdib2->get_graphics()->SelectObject(pen1);
               }
               break;
            case 1:
               {
                  pdib2->get_graphics()->SelectObject(brush2);
                  pdib2->get_graphics()->SelectObject(pen2);
               }
               break;
            case 2:
               {
                  pdib2->get_graphics()->SelectObject(brush3);
                  pdib2->get_graphics()->SelectObject(pen3);
               }
            case 3:
               {
                  pdib2->get_graphics()->SelectObject(brush4);
                  pdib2->get_graphics()->SelectObject(pen4);
               }
            case 4:
               {
                  pdib2->get_graphics()->SelectObject(brush5);
                  pdib2->get_graphics()->SelectObject(pen5);
               }
               break;
            }
            pdib2->get_graphics()->Ellipse(x1, y1, x1 + d, y1 + d);
         }

      }

      /*imaging.bitmap_blend(
         pdib1->get_graphics(),
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0,
         50);*/

      pdib2->channel_multiply(::visual::rgba::channel_alpha, 10.0 / 255.0);

      pdib1->get_graphics()->BitBlt(
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0, SRCCOPY);

      pdibBack->stretch_dib(pdib1);

      recta.add(rectClient);
   }

   void VisualEffect::Constraint001(point & pt, const RECT & rect, double & direction)
   {
      if(pt.x > rect.right)
      {
         direction  += 180 + ((int32_t) direction  % 360);
      }
      else if(pt.y > rect.bottom)
      {
         direction  += 180 + ((int32_t) direction  % 360);
      }
      else if(pt.x < rect.left)
      {
         direction  += 180 + ((int32_t) direction  % 360);
      }
      else if(pt.y < rect.top)
      {
         direction  += 180 + ((int32_t) direction  % 360);
      }

      if(pt.x > rect.right)
      {
         pt.x = rect.right;
      }
      else if(pt.x < rect.left)
      {
         pt.x = rect.left;
      }

      if(pt.y > rect.bottom)
      {
         pt.y = rect.bottom;
      }
      else if(pt.y < rect.top)
      {
         pt.y = rect.top;
      }

   }
   void VisualEffect::TrackDirection001(double &direction, double & directionAddUp, RandomGrow & randomgrow)
   {
      if(randomgrow.Step())
      {
         direction = ((int32_t) direction % 360);
         directionAddUp = 4.0 * rand() / RAND_MAX - 2.0;

      }
      direction += directionAddUp;
   }


   void VisualEffect::RenderRotateEx3(rect_array & recta)
   {
      Main & main = HelperGetMain();

      TransitionEffect & transitioneffect = main.GetTransitionEffect();

      Graphics & graphics = main.GetGraphics();

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
         m_color.set_rgb(pdib1->GetPixel(
            pdib1->m_size.cx / 2,
            pdib1->m_size.cy / 2));
      }



      rect rectClient = tool1.rectClient;
      tool1.cx = rectClient.width();
      tool1.cy = rectClient.height();
      class imaging & imaging = System.visual().imaging();


      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);
      ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
      ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
      ::draw2d::dib_sp pdib3 = graphics.GetDib(_graphics::DibTemp3);

      int32_t cx1 = pdib1->m_size.cx;
      int32_t cy1 = pdib1->m_size.cy;

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         pdib2->create(cx1, cy1);
         pdib3->create(cx1, cy1);
      }


//         int32_t s1 = rand() * 1 / RAND_MAX + 1;
//         int32_t s2 = rand() * 1 / RAND_MAX + 1;
//         int32_t s3 = rand() * 2 / RAND_MAX + 1;
//         int32_t s4 = rand() * 2 / RAND_MAX + 1;

      rect rcTrackBox;

      rcTrackBox.left   = 1;
      rcTrackBox.top    = 1;
      rcTrackBox.right  = cx1 - 1 - rcTrackBox.left;
      rcTrackBox.bottom = cy1 - 1 - rcTrackBox.top;

      rect rcTrackBox2;

      rcTrackBox2.left   = 0;
      rcTrackBox2.top    = 0;
      rcTrackBox2.right  = cx1 - 1 - rcTrackBox2.left;
      rcTrackBox2.bottom = cy1 - 1 - rcTrackBox2.top;

      /*for(int32_t i = 0; i < m_colortrack1a.get_size(); i++)
      {
         ColorTrack1 & ct1 = m_colortrack1a[i];
         ct1.m_rndgrowVelocity.Step();
         TrackDirection001(
            ct1.m_dDirection,
            ct1.m_dDirectionAddUp,
            ct1.m_rndgrowDirectionLatency);
         ct1.m_dCos = ::cos(ct1.m_dDirection * M_PI / 180.0);
         ct1.m_dSin = ::sin(ct1.m_dDirection * M_PI / 180.0);
         ct1.m_ptColorTrack.x += abs(ct1.m_rndgrowVelocity.i) * ct1.m_dCos;
         ct1.m_ptColorTrack.y += abs(ct1.m_rndgrowVelocity.i) * ct1.m_dSin;
         Constraint001(
            ct1.m_ptColorTrack,
            rcTrackBox,
            rcTrackBox2,
            ct1.m_dDirection);
         ct1.m_dSize = rand() * 5 / RAND_MAX + 1;
      }*/

      StepGrow001(
         m_color,
         m_iGrowColor,
         m_iGrowMax);

      StepGrow001(
         m_color2,
         m_iGrowColor2,
         m_iGrowMax2);

      StepGrow001(
         m_color3,
         m_iGrowColor3,
         m_iGrowMax3);

      StepGrow001(
         m_color4,
         m_iGrowColor4,
         m_iGrowMax4);

      color colorStrong1 = m_color;
      color colorStrong3 = m_color2;
      color colorStrong5 = m_color3;
      color colorStrong7 = m_color4;
      color colorStrong2;
      color colorStrong4;
      color colorStrong6;
      color colorStrong8;

      {
         double dH;
         double dL;
         double dS;
         colorStrong1.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong1.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong1.get_hls(dH, dL, dS);
         dL = 0.9;
         dS = 0.7;
         colorStrong2.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong3.get_hls(dH, dL, dS);
         dL = 0.9;
         dS = 0.7;
         colorStrong3.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong3.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.9;
         colorStrong4.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong5.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong5.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong5.get_hls(dH, dL, dS);
         dL = 0.5;
         dS = 0.9;
         colorStrong6.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong7.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong7.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong7.get_hls(dH, dL, dS);
         dL = 0.5;
         dS = 0.9;
         colorStrong8.set_hls(dH, dL, dS);
      }
//
//
//            ARGB(255, rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX);

      BYTE bA = 200;


#ifdef WINDOWSEX
      GdiFlush();
#endif

      //double dmin = min(cx, cy);
      //double dmax = max(cx, cy);abs

     // ::draw2d::graphics_sp pdib3->get_graphics();
      //pdib3->get_graphics()->CreateCompatibleDC(NULL);
      //pdib3->get_graphics()->SelectObject(pdib3->m_hbitmap);

   //   pdib3->stretch_dib(pdibBuffer);

   //   pdib3->Paste(pdib1);

//         int32_t c1 = rand() * 3 / RAND_MAX;
//         int32_t c2 = rand() * 3 / RAND_MAX;
//         int32_t c4 = rand() * 10 / RAND_MAX + 1;


      m_rndgrowAngleOffsetLatency.Step();
      if(m_rndgrowAngleOffsetLatency.i == 0)
      {
         m_dAngleOffsetAddUp = (4.0 * rand() / RAND_MAX) - 2.0;
      }
      m_dAngleOffset += m_dAngleOffsetAddUp;
      m_dAngleOffset = fmod(m_dAngleOffset, 360.0);

      double dAngleOffset = m_dAngleOffset;
      double dAngle;
      if(m_iGrowColor >= 0)
      {
         dAngle = 0.111 + dAngleOffset;
      }
      else
      {

         dAngle = -0.111 - dAngleOffset;
      }
      pdib2->rotate(pdib1, dAngle, 1.05);
      //pdib2->rotate(pdib1, dAngle, 1.009);
      //pdib2->Paste(pdib1);
      //imaging.color_blend(pdib2->get_graphics(), cxm - s1, cym - s2, s3, s4, m_color.get_rgb(), bA);


      // top
      imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 / 2, 1, colorStrong1.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, 0, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);
      // left
      imaging.color_blend(pdib1->get_graphics(), 0, 0, 1, cy1 / 2, colorStrong3.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 / 2, 1, cy1 / 2 - 1, colorStrong4.get_rgb(), bA);
      // bottom
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 - 1, cx1 / 2, 1, colorStrong5.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, cy1 - 1, cx1 / 2 - 1, 1, colorStrong6.get_rgb(), bA);
      // right
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, 0, 1, cy1 / 2, colorStrong7.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, cy1 / 2, 1, cy1 / 2 - 1, colorStrong8.get_rgb(), bA);


   /*   {
         ::draw2d::pen_sp pen1(get_app(), PS_SOLID, 0, colorStrong1.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush1(get_app(), colorStrong1.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen2(get_app(), PS_SOLID, 0, colorStrong2.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush2(get_app(), colorStrong2.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen3(get_app(), PS_SOLID, 0, colorStrong3.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush3(get_app(), colorStrong3.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen4(get_app(), PS_SOLID, 0, colorStrong4.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush4(get_app(), colorStrong4.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen5(get_app(), PS_SOLID, 0, colorStrong5.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush5(get_app(), colorStrong5.get_rgb() | (255 << 24));
         for(int32_t i = 0; i < m_colortrack1a.get_size(); i++)
         {
            ColorTrack1 & ct1 = m_colortrack1a[i];
            int32_t x1 = ct1.m_ptColorTrack.x;
            int32_t y1 = ct1.m_ptColorTrack.y;
            int32_t d = ct1.m_dSize;
            switch(i % 5)
            {
            case 0:
               {
                  pdib1->get_graphics()->SelectObject(brush1);
                  pdib1->get_graphics()->SelectObject(pen1);
               }
               break;
            case 1:
               {
                  pdib1->get_graphics()->SelectObject(brush2);
                  pdib1->get_graphics()->SelectObject(pen2);
               }
               break;
            case 2:
               {
                  pdib1->get_graphics()->SelectObject(brush3);
                  pdib1->get_graphics()->SelectObject(pen3);
               }
            case 3:
               {
                  pdib1->get_graphics()->SelectObject(brush4);
                  pdib1->get_graphics()->SelectObject(pen4);
               }
            case 4:
               {
                  pdib1->get_graphics()->SelectObject(brush5);
                  pdib1->get_graphics()->SelectObject(pen5);
               }
               break;
            }
            pdib1->get_graphics()->Rectangle(x1, y1, x1 + d, y1 + d);
         }

      }*/



      /*imaging.bitmap_blend(
         pdib1->get_graphics(),
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0,
         50);*/

      pdib2->channel_multiply(::visual::rgba::channel_alpha, 10.0 / 255.0);

      pdib1->get_graphics()->BitBlt(
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0, SRCCOPY);

      pdibBack->stretch_dib(pdib1);

      recta.add(rectClient);
   }

   void VisualEffect::Constraint001(
      point & pt,
      LPCRECT lpcrectIn,
      LPCRECT lpcrectOut,
      double & direction)
   {
      rect rectIn(lpcrectIn);

      if(rectIn.contains(pt))
      {
         point ptCenter(
            (rectIn.left + rectIn.right) / 2,
            (rectIn.top + rectIn.bottom) / 2);

         direction  += 180 + ((int32_t) direction  % 360);

         if(pt.x > ptCenter.x)
         {
            pt.x = rectIn.right;
         }
         else
         {
            pt.x = rectIn.left;
         }

         if(pt.y > ptCenter.y)
         {
            pt.y = rectIn.bottom;
         }
         else
         {
            pt.y = rectIn.left;
         }
      }

      if(pt.x > lpcrectOut->right)
      {
         direction  += 180 + ((int32_t) direction  % 360);
      }
      else if(pt.y > lpcrectOut->bottom)
      {
         direction  += 180 + ((int32_t) direction  % 360);
      }
      else if(pt.x < lpcrectOut->left)
      {
         direction  += 180 + ((int32_t) direction  % 360);
      }
      else if(pt.y < lpcrectOut->top)
      {
         direction  += 180 + ((int32_t) direction  % 360);
      }

      if(pt.x > lpcrectOut->right)
      {
         pt.x = lpcrectOut->right;
      }
      else if(pt.x < lpcrectOut->left)
      {
         pt.x = lpcrectOut->left;
      }

      if(pt.y > lpcrectOut->bottom)
      {
         pt.y = lpcrectOut->bottom;
      }
      else if(pt.y < lpcrectOut->top)
      {
         pt.y = lpcrectOut->top;
      }

   }






   void VisualEffect::RenderRotateEx4(rect_array & recta)
   {
      Main & main = HelperGetMain();

      TransitionEffect & transitioneffect = main.GetTransitionEffect();

      Graphics & graphics = main.GetGraphics();

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
         m_color.set_rgb(pdib1->GetPixel(
            pdib1->m_size.cx / 2,
            pdib1->m_size.cy / 2));
      }



      rect rectClient = tool1.rectClient;
      tool1.cx = rectClient.width();
      tool1.cy = rectClient.height();
      class imaging & imaging = System.visual().imaging();


      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);
      ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
      ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
      ::draw2d::dib_sp pdib3 = graphics.GetDib(_graphics::DibTemp3);

      int32_t cx1 = pdib1->m_size.cx;
      int32_t cy1 = pdib1->m_size.cy;

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         pdib2->create(cx1, cy1);
         pdib3->create(cx1, cy1);
      }


//         int32_t s1 = rand() * 1 / RAND_MAX + 1;
//         int32_t s2 = rand() * 1 / RAND_MAX + 1;
//         int32_t s3 = rand() * 2 / RAND_MAX + 1;
//         int32_t s4 = rand() * 2 / RAND_MAX + 1;

      rect rcTrackBox;

      rcTrackBox.left   = 1;
      rcTrackBox.top    = 1;
      rcTrackBox.right  = cx1 - 1 - rcTrackBox.left;
      rcTrackBox.bottom = cy1 - 1 - rcTrackBox.top;

      rect rcTrackBox2;

      rcTrackBox2.left   = 0;
      rcTrackBox2.top    = 0;
      rcTrackBox2.right  = cx1 - 1 - rcTrackBox2.left;
      rcTrackBox2.bottom = cy1 - 1 - rcTrackBox2.top;

      /*for(int32_t i = 0; i < m_colortrack1a.get_size(); i++)
      {
         ColorTrack1 & ct1 = m_colortrack1a[i];
         ct1.m_rndgrowVelocity.Step();
         TrackDirection001(
            ct1.m_dDirection,
            ct1.m_dDirectionAddUp,
            ct1.m_rndgrowDirectionLatency);
         ct1.m_dCos = ::cos(ct1.m_dDirection * M_PI / 180.0);
         ct1.m_dSin = ::sin(ct1.m_dDirection * M_PI / 180.0);
         ct1.m_ptColorTrack.x += abs(ct1.m_rndgrowVelocity.i) * ct1.m_dCos;
         ct1.m_ptColorTrack.y += abs(ct1.m_rndgrowVelocity.i) * ct1.m_dSin;
         Constraint001(
            ct1.m_ptColorTrack,
            rcTrackBox,
            rcTrackBox2,
            ct1.m_dDirection);
         ct1.m_dSize = rand() * 5 / RAND_MAX + 1;
      }*/

      StepGrow001(
         m_color,
         m_iGrowColor,
         m_iGrowMax);

      StepGrow001(
         m_color2,
         m_iGrowColor2,
         m_iGrowMax2);

      StepGrow001(
         m_color3,
         m_iGrowColor3,
         m_iGrowMax3);

      StepGrow001(
         m_color4,
         m_iGrowColor4,
         m_iGrowMax4);

      color colorStrong1 = m_color;
      color colorStrong3 = m_color2;
      color colorStrong5 = m_color3;
      color colorStrong7 = m_color4;
      color colorStrong2;
      color colorStrong4;
      color colorStrong6;
      color colorStrong8;

      {
         double dH;
         double dL;
         double dS;
         colorStrong1.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong1.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong1.get_hls(dH, dL, dS);
         dL = 0.3;
         dS = 0.1;
         colorStrong2.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong3.get_hls(dH, dL, dS);
         dL = 0.9;
         dS = 0.7;
         colorStrong3.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong3.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.9;
         colorStrong4.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong5.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong5.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong5.get_hls(dH, dL, dS);
         dL = 0.5;
         dS = 0.9;
         colorStrong6.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong7.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong7.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong7.get_hls(dH, dL, dS);
         dL = 0.5;
         dS = 0.9;
         colorStrong8.set_hls(dH, dL, dS);
      }


//            ARGB(255, rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX);

      BYTE bA = 200;


#ifdef WINDOWSEX
      GdiFlush();
#endif

      //double dmin = min(cx, cy);
      //double dmax = max(cx, cy);abs

      if(m_bGrowColor0)
      {
         //pdib1->get_graphics()->FillSolidRect(0, 0, cx1, cy1, colorStrong1.get_rgb() | (255 << 24));
      }

     // ::draw2d::graphics_sp pdib3->get_graphics();
      //pdib3->get_graphics()->CreateCompatibleDC(NULL);
      //pdib3->get_graphics()->SelectObject(pdib3->m_hbitmap);

   //   pdib3->stretch_dib(pdibBuffer);

   //   pdib3->Paste(pdib1);

//         int32_t c1 = rand() * 3 / RAND_MAX;
//         int32_t c2 = rand() * 3 / RAND_MAX;
//         int32_t c4 = rand() * 10 / RAND_MAX + 1;


      m_rndgrowAngleOffsetLatency.Step();
      if(m_rndgrowAngleOffsetLatency.i == 1)
      {
         m_dAngleOffsetAddUp = (5.1 * rand() / RAND_MAX) - 2.05;
      }
      double dOffset3 = (1.0 * rand() / RAND_MAX) - .5;
      m_dAngleOffset += min(10.0, min(2.0, m_dAngleOffsetAddUp + dOffset3));
      m_dAngleOffset = fmod(m_dAngleOffset, 360.0);

//         double dAngleOffset = m_dAngleOffset;
      double dAngle;
      if(m_rndgrowAngleOffsetLatency.i > 50)
      {
         //dAngle = 10.111 + dAngleOffset;
         dAngle = m_dAngleOffset;
      }
      else
      {

         //dAngle = -10.111 - dAngleOffset;
         dAngle = -m_dAngleOffset;
      }
      pdib2->rotate(pdib1, dAngle, 1.09);
      //pdib2->rotate(pdib1, dAngle, 1.009);
      //pdib2->Paste(pdib1);
      //imaging.color_blend(pdib2->get_graphics(), cxm - s1, cym - s2, s3, s4, m_color.get_rgb(), bA);


      // top
   /*   imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 / 2, 1, colorStrong1.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, 0, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);
      // left
      imaging.color_blend(pdib1->get_graphics(), 0, 0, 1, cy1 / 2, colorStrong3.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 / 2, 1, cy1 / 2 - 1, colorStrong4.get_rgb(), bA);
      // bottom
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 - 1, cx1 / 2, 1, colorStrong5.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, cy1 - 1, cx1 / 2 - 1, 1, colorStrong6.get_rgb(), bA);
      // right
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, 0, 1, cy1 / 2, colorStrong7.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, cy1 / 2, 1, cy1 / 2 - 1, colorStrong8.get_rgb(), bA);*/

      // top1
      ::draw2d::pen_sp pen1(allocer());
      pen1->create_solid(1, colorStrong1.get_rgb() | (255 << 24));
      pdib1->get_graphics()->SelectObject(pen1);
      int32_t margin = 10;
      int32_t w = margin * 2;
      pdib1->get_graphics()->MoveTo(margin, margin);

      int32_t imax = cx1 - margin;
      int32_t jmax = cx1 / 2;
      int32_t rmax = jmax * RAND_MAX;
      int32_t rhalf = RAND_MAX / 2;
      int32_t j = 0;
      int32_t r1 = 0;
      int32_t r2 = 0;
      int32_t i;
      for(i = margin; i < jmax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 3 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 5 / rmax;
         }
         pdib1->get_graphics()->LineTo(i, r1 + r2 + margin + ((rand() - rhalf) * j * w / rmax));
         j++;
      }
      for(; i < imax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 3 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 5 / rmax;
         }
         pdib1->get_graphics()->LineTo(i, r1 + r2 + margin + ((rand() - rhalf) * j * w / rmax));
         j--;
      }

      pdib1->get_graphics()->MoveTo(margin, cy1 - margin);

      for(i = margin; i < jmax; i++)
      {
         pdib1->get_graphics()->LineTo(i, cy1 - margin + ((rand() - rhalf) * j * w / rmax));
         j++;
      }
      for(; i < imax; i++)
      {
         pdib1->get_graphics()->LineTo(i, cy1 - margin + ((rand() - rhalf) * j * w / rmax));
         j--;
      }

      pdib1->get_graphics()->MoveTo(margin, margin);

      // vertical
      imax = cy1 - margin;
      jmax = cy1 / 2;
      rmax = jmax * RAND_MAX;
      rhalf = RAND_MAX / 2;
      j = 0;
      r1 = 0;
      r2 = 0;
      for(i = margin; i < jmax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 3 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 5 / rmax;
         }
         pdib1->get_graphics()->LineTo(r1 + r2 + margin + ((rand() - rhalf) * j * w / rmax), i);
         j++;
      }
      for(; i < imax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 3 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 5 / rmax;
         }
         pdib1->get_graphics()->LineTo(r1 + r2 + margin + ((rand() - rhalf) * j * w / rmax), i);
         j--;
      }

      pdib1->get_graphics()->MoveTo(cx1 - margin, margin);

      for(i = margin; i < jmax; i++)
      {
         pdib1->get_graphics()->LineTo(cx1 - margin + ((rand() - rhalf) * j * w / rmax), i);
         j++;
      }
      for(; i < imax; i++)
      {
         pdib1->get_graphics()->LineTo(cx1 - margin + ((rand() - rhalf) * j * w / rmax), i);
         j--;
      }

      //imaging.color_blend(pdib1->get_graphics(), 0, cy1 * 2 / 3, cx1 / 2, 1, , bA);
      //imaging.color_blend(pdib1->get_graphics(), cx1 / 2, cy1 * 2 / 3, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);

      {
         int32_t x2 = cx1 / 2;
         int32_t y2 = cy1 / 2;
         int32_t w2 = cx1 / 2 - 1;
         int32_t h2 = cy1 / 2 - 1;

         // top
         imaging.color_blend(pdib1->get_graphics(),  0, 0, w2, 1, colorStrong2.get_rgb(), bA);
         imaging.color_blend(pdib1->get_graphics(), x2, 0, w2, 1, colorStrong2.get_rgb(), bA);
         // left
         imaging.color_blend(pdib1->get_graphics(), 0,  0, 1, h2, colorStrong2.get_rgb(), bA);
         imaging.color_blend(pdib1->get_graphics(), 0, y2, 1, h2, colorStrong2.get_rgb(), bA);
         // bottom
         imaging.color_blend(pdib1->get_graphics(),  0, cy1 - 1, w2, 1, colorStrong2.get_rgb(), bA);
         imaging.color_blend(pdib1->get_graphics(), x2, cy1 - 1, w2, 1, colorStrong2.get_rgb(), bA);
         // right
         imaging.color_blend(pdib1->get_graphics(), cx1 - 1, 0, 1, h2, colorStrong2.get_rgb(), bA);
         imaging.color_blend(pdib1->get_graphics(), cx1 - 1, y2, 1, h2, colorStrong2.get_rgb(), bA);
      }

   /*   {
         ::draw2d::pen_sp pen1(get_app(), PS_SOLID, 0, colorStrong1.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush1(get_app(), colorStrong1.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen2(get_app(), PS_SOLID, 0, colorStrong2.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush2(get_app(), colorStrong2.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen3(get_app(), PS_SOLID, 0, colorStrong3.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush3(get_app(), colorStrong3.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen4(get_app(), PS_SOLID, 0, colorStrong4.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush4(get_app(), colorStrong4.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen5(get_app(), PS_SOLID, 0, colorStrong5.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush5(get_app(), colorStrong5.get_rgb() | (255 << 24));
         for(int32_t i = 0; i < m_colortrack1a.get_size(); i++)
         {
            ColorTrack1 & ct1 = m_colortrack1a[i];
            int32_t x1 = ct1.m_ptColorTrack.x;
            int32_t y1 = ct1.m_ptColorTrack.y;
            int32_t d = ct1.m_dSize;
            switch(i % 5)
            {
            case 0:
               {
                  pdib1->get_graphics()->SelectObject(brush1);
                  pdib1->get_graphics()->SelectObject(pen1);
               }
               break;
            case 1:
               {
                  pdib1->get_graphics()->SelectObject(brush2);
                  pdib1->get_graphics()->SelectObject(pen2);
               }
               break;
            case 2:
               {
                  pdib1->get_graphics()->SelectObject(brush3);
                  pdib1->get_graphics()->SelectObject(pen3);
               }
            case 3:
               {
                  pdib1->get_graphics()->SelectObject(brush4);
                  pdib1->get_graphics()->SelectObject(pen4);
               }
            case 4:
               {
                  pdib1->get_graphics()->SelectObject(brush5);
                  pdib1->get_graphics()->SelectObject(pen5);
               }
               break;
            }
            pdib1->get_graphics()->Rectangle(x1, y1, x1 + d, y1 + d);
         }

      }*/



      /*imaging.bitmap_blend(
         pdib1->get_graphics(),
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0,
         50);*/

      pdib2->channel_multiply(::visual::rgba::channel_alpha, 10.0 / 255.0);

      pdib1->get_graphics()->BitBlt(
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0, SRCCOPY);

      pdibBack->stretch_dib(pdib1);

      recta.add(rectClient);
   }




   void VisualEffect::RenderRain1(rect_array & recta)
   {
      Main & main = HelperGetMain();

      TransitionEffect & transitioneffect = main.GetTransitionEffect();
      Graphics & graphics = main.GetGraphics();

      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);
      ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
      ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
      ::draw2d::dib_sp pdib3 = graphics.GetDib(_graphics::DibTemp3);
      ::draw2d::dib_sp pdib4 = graphics.GetDib(_graphics::DibTemp4);
      ::draw2d::dib_sp pdibBuffer = graphics.GetDib(_graphics::DibBuffer);
      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         ::draw2d::dib_sp pdibFrame1 = graphics.GetDib(_graphics::DibFrame1);
         tool1.dmod = 4.2;
         tool1.dminsize = 0;
         int32_t cx1 = tool1.cx / 4;
         int32_t cy1 = tool1.cy / 4;
         pdib1->create(cx1, cy1);
         pdib2->create(cx1, cy1);
         pdib3->create(cx1, cy1);
         pdib4->create(cx1, cy1);
         tool1.dalpha = 0;
         m_water.create(cx1, cy1);
         pdib4->get_graphics()->SetStretchBltMode(HALFTONE);
         pdib4->stretch_dib(pdibFrame1);
         pdib3->get_graphics()->SetStretchBltMode(HALFTONE);
         pdib3->stretch_dib(pdibBuffer);
      }
      int32_t cx1 = pdib1->m_size.cx;
      int32_t cy1 = pdib1->m_size.cy;



      //pdib4->get_graphics()->BitBlt(0, 0, cx1, cy1, pdib3->get_graphics(), 0, 0, SRCCOPY);


      ::index iReturnPoint = transitioneffect.m_tool001.m_iStepCount * 5 / 21;

      if(transitioneffect.m_tool001.m_iStep >= iReturnPoint * 2)
      {

         System.visual().imaging().bitmap_blend(
            pdib4->get_graphics(),
            null_point(), pdib1->size(),
            pdib3->get_graphics(),
            null_point(),
            10);
      }

      pdib4->fill_channel(0, visual::rgba::channel_alpha);
      pdib2->fill_channel(0, visual::rgba::channel_alpha);

      m_water.to(pdib4->get_data(), pdib2->get_data());

      pdib4->fill_channel(255, visual::rgba::channel_alpha);
      pdib2->fill_channel(255, visual::rgba::channel_alpha);

      int32_t mod = max(1, (int32_t) tool1.dmod);
      if((tool1.frame % mod) == 0)
      {
         int32_t x = rand() * cx1 / RAND_MAX;
         int32_t y = rand() * cy1 / RAND_MAX;
         int32_t r = (int32_t) (rand() * min(tool1.dminsize, 60.0) / RAND_MAX + min(tool1.dminsize / 2, 60.0));
         int32_t h = rand() * 100 / RAND_MAX;
         if(transitioneffect.m_tool001.m_iStep < iReturnPoint)
         {
            tool1.dminsize += 0.5;
         }
         else
         {
            tool1.dminsize -= 0.5;
         }
         m_water.HeightBlob(x, y,
                     r, h, tool1.page);
      }

      if(tool1.dminsize > 20 || tool1.dalpha > 0)
         tool1.dalpha += 0.5;
      if(transitioneffect.m_tool001.m_iStep < iReturnPoint)
      {
         tool1.dmod -= 0.01;
         tool1.frame++;
      }
      else
      {
         tool1.dmod += 0.01;
         tool1.frame--;
      }
      tool1.page ^= 1;

      pdibBack->stretch_dib(pdib2);

      recta.add(tool1.rectClient);
   }


   void VisualEffect::RenderRotateEx5(rect_array & recta)
   {
      Main & main = HelperGetMain();

      TransitionEffect & transitioneffect = main.GetTransitionEffect();

      Graphics & graphics = main.GetGraphics();

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
         m_color.set_rgb(pdib1->GetPixel(
            pdib1->m_size.cx / 2,
            pdib1->m_size.cy / 2));
      }

      rect rectClient = tool1.rectClient;
      tool1.cx = rectClient.width();
      tool1.cy = rectClient.height();
      class imaging & imaging = System.visual().imaging();


      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);
      ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
      ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
      ::draw2d::dib_sp pdib3 = graphics.GetDib(_graphics::DibTemp3);
      ::draw2d::dib_sp pdib4 = graphics.GetDib(_graphics::DibTemp4);

      int32_t cx1 = pdib1->m_size.cx;
      int32_t cy1 = pdib1->m_size.cy;

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         if(m_pointa.get_size() != cx1)
         {
            m_pointa.allocate(cx1);
            m_pointa1.allocate(cx1);
            m_pointa2.allocate(cx1);

            for(int32_t i = 0; i < cx1; i++)
            {
               m_pointa[i].y = cy1 / 2;
               m_pointa1[i].y = 0;
               m_pointa1[i].y = 0;
            }
         }
      }

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         pdib2->create(cx1, cy1);
         pdib3->create(cx1, cy1);
         pdib4->create(tool1.cx, tool1.cy);
      }

      if(m_iVisual == VisualEffectRotateEx6)
      {
         pdib2->FillByte(0);
         pdib3->FillByte(0);
      }

      StepGrow034(
         m_color,
         m_iGrowColor,
         m_iGrowMax);

      color colorStrong1 = m_color;

      {
         double dH;
         double dL;
         double dS;
         colorStrong1.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong1.set_hls(dH, dL, dS);
      }

      ::draw2d::pen_sp pen1(allocer());
      pen1->create_solid(1, colorStrong1.get_rgb() | (255 << 24));
      ::draw2d::pen_sp penWhite(allocer());
      penWhite->create_solid(3, ARGB(255, 205, 205, 205));
      int32_t margin1 = cx1 / 8;
      int32_t margin2 = cy1 / 2;
      int32_t w = cy1 / 3;

      double jmul = (double) cy1 / (cx1 * 2.0);

      double delta = w;


      int32_t imax = cx1 - margin1;
      int32_t jmax = cx1 / 2;
      int32_t rmax = jmax * RAND_MAX;
      double rhalf = RAND_MAX / 2.0;
      int32_t j = 0;
//         int32_t r1 = 0;
//         int32_t r2 = 0;


      double offset;

      double jres;
      int32_t i;
      for(i = margin1; i < jmax; i++)
      {
         /*if((i % 5) == 0)
         {
             r1 = (rand() - rhalf) * j * 1 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 2 / rmax;
         }*/
         m_pointa[i].x = i;
         //offset = r1 + r2 + ((rand() - rhalf) * j * delta / rmax);
         jres = j * jmul;
         offset = (rand() - rhalf) * j * delta / rmax;
         m_pointa[i].y = (int32_t) max(margin2 - jres, min(margin2 + jres, m_pointa[i - 1].y + offset));
         m_pointa[i].y = (m_pointa[i].y + margin2) / 2;
         j++;
      }
      j = 0;
      for(i = imax - 1; i >= jmax; i--)
      {
         /*if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 1 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 2 / rmax;
         }*/
         m_pointa[i].x = i;
         //offset = r1 + r2 + ((rand() - rhalf) * j * delta / rmax);
         jres = j * jmul;
         offset = ((rand() - rhalf) * j * delta / rmax);
         m_pointa[i].y = (int32_t) max(margin2 - jres, min(margin2 + jres, m_pointa[i + 1].y + offset));
         m_pointa[i].y = (m_pointa[i].y + margin2) / 2;
         j++;
      }

      bool bWhite;
      bWhite = false;
      if(m_iVisual == VisualEffectRotateEx5)
      {
         pdib1->get_graphics()->SelectObject(penWhite);
         pdib1->get_graphics()->MoveTo(m_pointa[margin1].x, m_pointa[margin1].y);
         for(i = margin1; i < imax; i++)
         {
            pdib1->get_graphics()->LineTo(m_pointa[i].x, m_pointa[i].y);
         }
      }
      pdib1->get_graphics()->SelectObject(pen1);
      pdib1->get_graphics()->MoveTo(m_pointa[margin1].x, m_pointa[margin1].y);
      for(i = margin1; i < imax; i++)
      {
         pdib1->get_graphics()->LineTo(m_pointa[i].x, m_pointa[i].y);
      }

      imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 , cy1, ARGB(255, 0, 0, 0), 10);

#ifdef WINDOWSEX
      GdiFlush();
#endif


      if(m_iVisual == VisualEffectRotateEx6)
      {
         keep < bool > keepTransferVoid (&HelperGetMain().GetInterface().m_bTransferVoid, true, false, true);
         pdib4->get_graphics()->SetStretchBltMode(HALFTONE);
         pdib4->stretch_dib(pdib1);
         HelperGetMain().GetInterface().BackViewFeedback(pdib4->get_graphics());
         pdib1->get_graphics()->SetStretchBltMode(HALFTONE);
         pdib1->stretch_dib(pdib4);
      }



      m_rndgrowAngleOffsetLatency.Step();
      if(m_rndgrowAngleOffsetLatency.i == 0)
      {
         m_dAngleOffsetAddUp = (10.0 * rand() / RAND_MAX) - 5.0;
      }

      m_dAngleOffset = m_dAngleOffsetAddUp;
      m_dAngleOffset = fmod(m_dAngleOffset, 360.0);

      double dAngleOffset = m_dAngleOffset;
      double dAngle;
      if(m_iGrowColor >= 0)
      {
         dAngle = 1.511 + dAngleOffset;
      }
      else
      {

         dAngle = -1.511 - dAngleOffset;
      }
      pdib2->Rotate034(pdib1, dAngle, 0.95);


      pdib2->channel_multiply(::visual::rgba::channel_alpha, 127.0 / 255.0);

      pdib1->get_graphics()->BitBlt(
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0, SRCCOPY);
      pdibBack->stretch_dib(pdib1);

      recta.add(rectClient);
   }

   void VisualEffect::RenderRotateEx7(rect_array & recta)
   {
      Main & main = HelperGetMain();

      TransitionEffect & transitioneffect = main.GetTransitionEffect();

      Graphics & graphics = main.GetGraphics();

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
         m_color.set_rgb(pdib1->GetPixel(
            pdib1->m_size.cx / 2,
            pdib1->m_size.cy / 2));
      }



      rect rectClient = tool1.rectClient;
      tool1.cx = rectClient.width();
      tool1.cy = rectClient.height();
      class imaging & imaging = System.visual().imaging();


      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);
      ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
      ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
      ::draw2d::dib_sp pdib3 = graphics.GetDib(_graphics::DibTemp3);

      int32_t cx1 = pdib1->m_size.cx;
      int32_t cy1 = pdib1->m_size.cy;

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         if(m_pointa.get_size() != cx1)
         {
            m_pointa.allocate(cx1);
            m_pointa1.allocate(cx1);
            m_pointa2.allocate(cx1);

            for(int32_t i = 0; i < cx1; i++)
            {
               m_pointa[i].y = cy1 / 2;
               m_pointa1[i].y = 0;
               m_pointa1[i].y = 0;
            }
         }
      }

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         pdib2->create(cx1, cy1);
         pdib3->create(cx1, cy1);
      }


//         int32_t s1 = rand() * 1 / RAND_MAX + 1;
//         int32_t s2 = rand() * 1 / RAND_MAX + 1;
//         int32_t s3 = rand() * 2 / RAND_MAX + 1;
//         int32_t s4 = rand() * 2 / RAND_MAX + 1;

      rect rcTrackBox;

      rcTrackBox.left   = 1;
      rcTrackBox.top    = 1;
      rcTrackBox.right  = cx1 - 1 - rcTrackBox.left;
      rcTrackBox.bottom = cy1 - 1 - rcTrackBox.top;

      rect rcTrackBox2;

      rcTrackBox2.left   = 0;
      rcTrackBox2.top    = 0;
      rcTrackBox2.right  = cx1 - 1 - rcTrackBox2.left;
      rcTrackBox2.bottom = cy1 - 1 - rcTrackBox2.top;

      /*for(int32_t i = 0; i < m_colortrack1a.get_size(); i++)
      {
         ColorTrack1 & ct1 = m_colortrack1a[i];
         ct1.m_rndgrowVelocity.Step();
         TrackDirection001(
            ct1.m_dDirection,
            ct1.m_dDirectionAddUp,
            ct1.m_rndgrowDirectionLatency);
         ct1.m_dCos = ::cos(ct1.m_dDirection * M_PI / 180.0);
         ct1.m_dSin = ::sin(ct1.m_dDirection * M_PI / 180.0);
         ct1.m_ptColorTrack.x += abs(ct1.m_rndgrowVelocity.i) * ct1.m_dCos;
         ct1.m_ptColorTrack.y += abs(ct1.m_rndgrowVelocity.i) * ct1.m_dSin;
         Constraint001(
            ct1.m_ptColorTrack,
            rcTrackBox,
            rcTrackBox2,
            ct1.m_dDirection);
         ct1.m_dSize = rand() * 5 / RAND_MAX + 1;
      }*/

      StepGrow034(
         m_color,
         m_iGrowColor,
         m_iGrowMax);

      /*StepGrow001(
         m_color2,
         m_iGrowColor2,
         m_iGrowMax2);

      StepGrow001(
         m_color3,
         m_iGrowColor3,
         m_iGrowMax3);

      StepGrow001(
         m_color4,
         m_iGrowColor4,
         m_iGrowMax4);*/

      color colorStrong1 = m_color;
      color colorStrong3 = m_color2;
      color colorStrong5 = m_color3;
      color colorStrong7 = m_color4;
      color colorStrong2;
      color colorStrong4;
      color colorStrong6;
      color colorStrong8;

      {
         double dH;
         double dL;
         double dS;
         colorStrong1.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong1.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong1.get_hls(dH, dL, dS);
         dL = 0.3;
         dS = 0.1;
         colorStrong2.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong3.get_hls(dH, dL, dS);
         dL = 0.9;
         dS = 0.7;
         colorStrong3.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong3.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.9;
         colorStrong4.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong5.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong5.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong5.get_hls(dH, dL, dS);
         dL = 0.5;
         dS = 0.9;
         colorStrong6.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong7.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong7.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong7.get_hls(dH, dL, dS);
         dL = 0.5;
         dS = 0.9;
         colorStrong8.set_hls(dH, dL, dS);
      }

//
//            ARGB(255, rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX);

//         BYTE bA = 200;


#ifdef WINDOWSEX
      GdiFlush();
#endif

      //double dmin = min(cx, cy);
      //double dmax = max(cx, cy);abs

      if(m_bGrowColor0)
      {
         //pdib1->get_graphics()->FillSolidRect(0, 0, cx1, cy1, colorStrong1.get_rgb() | (255 << 24));
      }

     // ::draw2d::graphics_sp pdib3->get_graphics();
      //pdib3->get_graphics()->CreateCompatibleDC(NULL);
      //pdib3->get_graphics()->SelectObject(pdib3->m_hbitmap);

   //   pdib3->stretch_dib(pdibBuffer);

   //   pdib3->Paste(pdib1);

//         int32_t c1 = rand() * 3 / RAND_MAX;
//         int32_t c2 = rand() * 3 / RAND_MAX;
//         int32_t c4 = rand() * 10 / RAND_MAX + 1;
















      /*   m_rndgrowAngleOffsetLatency.Step();
      if(m_rndgrowAngleOffsetLatency.i == 1)
      {
         m_dAngleOffsetAddUp = (5.1 * rand() / RAND_MAX) - 2.05;
      }
      double dOffset3 = (1.0 * rand() / RAND_MAX) - .5;
      m_dAngleOffset += min(10.0, min(2.0, m_dAngleOffsetAddUp + dOffset3));
      m_dAngleOffset = fmod(m_dAngleOffset, 360.0);

      double dAngleOffset = m_dAngleOffset;
      double dAngle;
      if(m_rndgrowAngleOffsetLatency.i > 50)
      {
         //dAngle = 10.111 + dAngleOffset;
         dAngle = m_dAngleOffset;
      }
      else
      {

         //dAngle = -10.111 - dAngleOffset;
         dAngle = -m_dAngleOffset;
      }
      pdib2->rotate(pdib1, dAngle, 0.95);*/
























      //pdib2->rotate(pdib1, dAngle, 1.009);
      //pdib2->Paste(pdib1);
      //imaging.color_blend(pdib2->get_graphics(), cxm - s1, cym - s2, s3, s4, m_color.get_rgb(), bA);


      // top
   /*   imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 / 2, 1, colorStrong1.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, 0, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);
      // left
      imaging.color_blend(pdib1->get_graphics(), 0, 0, 1, cy1 / 2, colorStrong3.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 / 2, 1, cy1 / 2 - 1, colorStrong4.get_rgb(), bA);
      // bottom
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 - 1, cx1 / 2, 1, colorStrong5.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, cy1 - 1, cx1 / 2 - 1, 1, colorStrong6.get_rgb(), bA);
      // right
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, 0, 1, cy1 / 2, colorStrong7.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, cy1 / 2, 1, cy1 / 2 - 1, colorStrong8.get_rgb(), bA);*/

      // top1
      ::draw2d::pen_sp pen1(allocer());
      pen1->create_solid(1, colorStrong1.get_rgb() | (255 << 24));
      ::draw2d::pen_sp penWhite(allocer());
      penWhite->create_solid(3, ARGB(255, 205, 205, 205));
      int32_t margin1 = 10;
//         int32_t margin2 = cy1 / 2;
      int32_t w = cy1 / 3;

      int32_t delta = 5;


      int32_t imax = cx1 - margin1;
      int32_t jmax = cx1 / 2;
      int32_t rmax = jmax * RAND_MAX;
      int32_t rhalf = RAND_MAX / 2;
      int32_t j = 0;
      int32_t r1 = 0;
      int32_t r2 = 0;


      int32_t offset;
      int32_t i;
      for(i = margin1; i < jmax; i++)
      {
         if((i % 5) == 0)
         {
             r1 = (rand() - rhalf) * j * 1 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 2 / rmax;
         }
         m_pointa[i].x = i;
         offset = r1 + r2 + ((rand() - rhalf) * j * delta / rmax);
         m_pointa[i].y = max(- j * w , min( j * w , m_pointa[i].y + offset));
         j++;
      }
      for(; i < imax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 1 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 2 / rmax;
         }
         m_pointa[i].x = i;
         offset = r1 + r2 + ((rand() - rhalf) * j * delta / rmax);
         m_pointa[i].y = max(- j * w , min( j * w , m_pointa[i].y + offset));
         j--;
      }
      pdib1->get_graphics()->SelectObject(penWhite);
      pdib1->get_graphics()->MoveTo(m_pointa[margin1].x, m_pointa[margin1].y);
      for(i = margin1; i < imax; i++)
      {
         pdib1->get_graphics()->LineTo(m_pointa[i].x, m_pointa[i].y);
      }
      pdib1->get_graphics()->SelectObject(pen1);
      pdib1->get_graphics()->MoveTo(m_pointa[margin1].x, m_pointa[margin1].y);
      for(i = margin1; i < imax; i++)
      {
         pdib1->get_graphics()->LineTo(m_pointa[i].x, m_pointa[i].y);
      }

      imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 , cy1, ARGB(255, 34, 34, 34), 10);

   /*   pdib1->get_graphics()->MoveTo(margin1, cy1 - margin2);

      for(i = margin1; i < jmax; i++)
      {
         pdib1->get_graphics()->LineTo(i, cy1 - margin2 + ((rand() - rhalf) * j * w / rmax));
         j++;
      }
      for(; i < imax; i++)
      {
         pdib1->get_graphics()->LineTo(i, cy1 - margin2 + ((rand() - rhalf) * j * w / rmax));
         j--;
      }

      pdib1->get_graphics()->MoveTo(margin2, margin1);

      // vertical
      imax = cy1 - margin1;
      jmax = cy1 / 2;
      rmax = jmax * RAND_MAX;
      rhalf = RAND_MAX / 2;
      j = 0;
      r1 = 0;
      r2 = 0;
      for(i = margin1; i < jmax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 3 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 5 / rmax;
         }
         pdib1->get_graphics()->LineTo(r1 + r2 + margin2 + ((rand() - rhalf) * j * w / rmax), i);
         j++;
      }
      for(; i < imax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 3 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 5 / rmax;
         }
         pdib1->get_graphics()->LineTo(r1 + r2 + margin2 + ((rand() - rhalf) * j * w / rmax), i);
         j--;
      }

      pdib1->get_graphics()->MoveTo(cx1 - margin2, margin1);

      for(i = margin1; i < jmax; i++)
      {
         pdib1->get_graphics()->LineTo(cx1 - margin2 + ((rand() - rhalf) * j * w / rmax), i);
         j++;
      }
      for(; i < imax; i++)
      {
         pdib1->get_graphics()->LineTo(cx1 - margin2 + ((rand() - rhalf) * j * w / rmax), i);
         j--;
      }*/

      //imaging.color_blend(pdib1->get_graphics(), 0, cy1 * 2 / 3, cx1 / 2, 1, , bA);
      //imaging.color_blend(pdib1->get_graphics(), cx1 / 2, cy1 * 2 / 3, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);

      // top
     /* imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 / 2, 1, colorStrong2.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, 0, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);
      // left
      imaging.color_blend(pdib1->get_graphics(), 0, 0, 1, cy1 / 2, colorStrong2.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 / 2, 1, cy1 / 2 - 1, colorStrong2.get_rgb(), bA);
      // bottom
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 - 1, cx1 / 2, 1, colorStrong2.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, cy1 - 1, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);
      // right
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, 0, 1, cy1 / 2, colorStrong2.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, cy1 / 2, 1, cy1 / 2 - 1, colorStrong2.get_rgb(), bA);


   //   pdib1->get_graphics()->FillSolidRect(0, 0, cx1 / 2, cy1 / 2, 0);*/
   /*   {
         ::draw2d::pen_sp pen1(get_app(), PS_SOLID, 0, colorStrong1.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush1(get_app(), colorStrong1.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen2(get_app(), PS_SOLID, 0, colorStrong2.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush2(get_app(), colorStrong2.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen3(get_app(), PS_SOLID, 0, colorStrong3.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush3(get_app(), colorStrong3.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen4(get_app(), PS_SOLID, 0, colorStrong4.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush4(get_app(), colorStrong4.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen5(get_app(), PS_SOLID, 0, colorStrong5.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush5(get_app(), colorStrong5.get_rgb() | (255 << 24));
         for(int32_t i = 0; i < m_colortrack1a.get_size(); i++)
         {
            ColorTrack1 & ct1 = m_colortrack1a[i];
            int32_t x1 = ct1.m_ptColorTrack.x;
            int32_t y1 = ct1.m_ptColorTrack.y;
            int32_t d = ct1.m_dSize;
            switch(i % 5)
            {
            case 0:
               {
                  pdib1->get_graphics()->SelectObject(brush1);
                  pdib1->get_graphics()->SelectObject(pen1);
               }
               break;
            case 1:
               {
                  pdib1->get_graphics()->SelectObject(brush2);
                  pdib1->get_graphics()->SelectObject(pen2);
               }
               break;
            case 2:
               {
                  pdib1->get_graphics()->SelectObject(brush3);
                  pdib1->get_graphics()->SelectObject(pen3);
               }
            case 3:
               {
                  pdib1->get_graphics()->SelectObject(brush4);
                  pdib1->get_graphics()->SelectObject(pen4);
               }
            case 4:
               {
                  pdib1->get_graphics()->SelectObject(brush5);
                  pdib1->get_graphics()->SelectObject(pen5);
               }
               break;
            }
            pdib1->get_graphics()->Rectangle(x1, y1, x1 + d, y1 + d);
         }

      }*/

         m_rndgrowAngleOffsetLatency.Step();
      if(m_rndgrowAngleOffsetLatency.i == 0)
      {
         m_dAngleOffsetAddUp = (10.0 * rand() / RAND_MAX) - 5.0;
      }
      //m_dAngleOffset += m_dAngleOffsetAddUp;
      m_dAngleOffset = m_dAngleOffsetAddUp;
      m_dAngleOffset = fmod(m_dAngleOffset, 360.0);

      double dAngleOffset = m_dAngleOffset;
      double dAngle;
      if(m_iGrowColor >= 0)
      {
         dAngle = 1.511 + dAngleOffset;
      }
      else
      {

         dAngle = -1.511 - dAngleOffset;
      }
      pdib2->Rotate034(pdib1, dAngle, 0.95);


      /*imaging.bitmap_blend(
         pdib1->get_graphics(),
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0,
         50);*/

      pdib2->channel_multiply(::visual::rgba::channel_alpha, 127.0 / 255.0);

      pdib1->get_graphics()->BitBlt(
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0, SRCCOPY);

      pdibBack->stretch_dib(pdib1);

      recta.add(rectClient);
   }





   void VisualEffect::RenderAlphaPixelExplosion(rect_array & recta)
   {
      Main & main = HelperGetMain();

      TransitionEffect & transitioneffect = main.GetTransitionEffect();
      Graphics & graphics = main.GetGraphics();

      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      ::draw2d::graphics_sp dcBuffer = graphics.GetBufferDC();
      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);
      ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
      ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
      ::draw2d::dib_sp pdib3 = graphics.GetDib(_graphics::DibTemp3);
      ::draw2d::dib_sp pdib4 = graphics.GetDib(_graphics::DibTemp4);
      ::draw2d::dib_sp pdibBuffer = graphics.GetDib(_graphics::DibBuffer);
      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         ::draw2d::dib_sp pdibFrame1 = graphics.GetDib(_graphics::DibFrame1);

         tool1.dmod = 4.2;
         tool1.dminsize = 0;
         int32_t cx1 = tool1.cx / 4;
         int32_t cy1 = tool1.cy / 4;
         pdib1->create(cx1, cy1);
         pdib2->create(cx1, cy1);
         pdib3->create(cx1, cy1);
         pdib4->create(cx1, cy1);
         tool1.dalpha = 0;

         m_explosion.m_density = 1.5;
         m_explosion.m_minradius = 0.0;
         m_explosion.create(cx1, cy1);
         m_explosion.Reset();

         pdib1->get_graphics()->SetStretchBltMode(HALFTONE);
         pdib1->stretch_dib(pdibFrame1);
         pdib3->get_graphics()->SetStretchBltMode(HALFTONE);
         pdib3->stretch_dib(pdibBuffer);
         pdib3->Fill(0, 0, 0, 0);
         pdib4->get_graphics()->BitBlt(0, 0, cx1, cy1, dcBuffer, 0, 0, SRCCOPY);
      }

      int32_t cx1 = pdib1->m_size.cx;
      int32_t cy1 = pdib1->m_size.cy;



      ::index iReturnPoint = transitioneffect.m_tool001.m_iStepCount * 5 / 21;

      m_explosion.to(pdib4->get_data(), pdib3->get_data());

      /*int32_t mod = max(1, (int32_t) tool1.dmod);
      if((tool1.frame % mod) == 0)
      {
         int32_t x = rand() * cx1 / RAND_MAX;
         int32_t y = rand() * cy1 / RAND_MAX;
         int32_t r = rand() * min(tool1.dminsize, 60.0) / RAND_MAX + min(tool1.dminsize / 2, 60.0);
         int32_t h = rand() * 100 / RAND_MAX;
         if(transitioneffect.m_tool001.m_iStep < iReturnPoint)
         {
            tool1.dminsize += 0.5;
         }
         else
         {
            tool1.dminsize -= 0.5;
         }
         m_water.HeightBlob(x, y,
                     r, h, tool1.page);
      }*/

      //m_explostion.CalcPixelExplosion(0, 0);


      if(tool1.dminsize > 20 || tool1.dalpha > 0)
         tool1.dalpha += 0.5;
      if(transitioneffect.m_tool001.m_iStep < iReturnPoint)
      {
         tool1.dmod -= 0.001;
         tool1.frame++;
      }
      else
      {
         tool1.dmod += 0.001;
         tool1.frame--;
      }
      tool1.page ^= 1;
      //dcBack->FillSolidRect(0, 0, cx, cy, ARGB(255, 0, 0, 0));
      //dcBack->FillSolidRect(100, 100, cx, cy, ARGB(255, 255, 255, 255));
      //pdibBack->stretch_dib(pdib2);

      //pdib2->channel_multiply(::visual::rgba::channel_alpha, 50.0 / 255.0);

      System.visual().imaging().bitmap_blend(
         pdib1->get_graphics(),
         null_point(), size(cx1, cy1),
         pdib3->get_graphics(),
         null_point(), 25);

      pdibBack->stretch_dib(pdib1);

      recta.add(tool1.rectClient);
   }

   void VisualEffect::RenderPixelExplosion(rect_array & recta)
   {
      Main & main = HelperGetMain();

      TransitionEffect & transitioneffect = main.GetTransitionEffect();
      Graphics & graphics = main.GetGraphics();

      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);
      ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
      ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
      ::draw2d::dib_sp pdib3 = graphics.GetDib(_graphics::DibTemp3);
      ::draw2d::dib_sp pdib4 = graphics.GetDib(_graphics::DibTemp4);
      ::draw2d::dib_sp pdibBuffer = graphics.GetDib(_graphics::DibBuffer);
      if(transitioneffect.m_tool001.m_iStep == 1)
      {
//            ::draw2d::dib_sp pdibFrame1 = graphics.GetDib(_graphics::DibFrame1);

         tool1.dmod = 4.2;
         tool1.dminsize = 0;
         int32_t cx1 = tool1.cx / 4;
         int32_t cy1 = tool1.cy / 4;
         pdib1->create(cx1, cy1);
         pdib2->create(cx1, cy1);
         pdib3->create(cx1, cy1);
         pdib4->create(cx1, cy1);
         tool1.dalpha = 0;

         m_explosion.m_density = 1.5;
         m_explosion.m_minradius = 0.0;
         m_explosion.create(cx1, cy1);
         m_explosion.Reset();

         pdib1->get_graphics()->FillSolidRect(0, 0, cx1, cy1, ARGB(0, 0, 0, 0));
         pdib3->get_graphics()->SetStretchBltMode(HALFTONE);
         pdib3->stretch_dib(pdibBuffer);
      }

      pdib4->get_graphics()->from(pdib1->size(), pdib3->get_graphics(), SRCCOPY);

      System.visual().imaging().bitmap_blend(
         pdib4->get_graphics(),
         null_point(), pdib1->size(),
         pdib1->get_graphics(),
         null_point(),
         (BYTE) max(min(255, tool1.dalpha), 0));

      ::index iReturnPoint = transitioneffect.m_tool001.m_iStepCount * 5 / 21;

      m_explosion.to(pdib4->get_data(), pdib2->get_data());

      /*int32_t mod = max(1, (int32_t) tool1.dmod);
      if((tool1.frame % mod) == 0)
      {
         int32_t x = rand() * cx1 / RAND_MAX;
         int32_t y = rand() * cy1 / RAND_MAX;
         int32_t r = rand() * min(tool1.dminsize, 60.0) / RAND_MAX + min(tool1.dminsize / 2, 60.0);
         int32_t h = rand() * 100 / RAND_MAX;
         if(transitioneffect.m_tool001.m_iStep < iReturnPoint)
         {
            tool1.dminsize += 0.5;
         }
         else
         {
            tool1.dminsize -= 0.5;
         }
         m_water.HeightBlob(x, y,
                     r, h, tool1.page);
      }*/

   //   CalcPixelExplosion(0, 0);


      if(tool1.dminsize > 20 || tool1.dalpha > 0)
         tool1.dalpha += 0.5;
      if(transitioneffect.m_tool001.m_iStep < iReturnPoint)
      {
         tool1.dmod -= 0.01;
         tool1.frame++;
      }
      else
      {
         tool1.dmod += 0.01;
         tool1.frame--;
      }
      tool1.page ^= 1;
      //dcBack->FillSolidRect(0, 0, cx, cy, ARGB(255, 0, 0, 0));
      //dcBack->FillSolidRect(100, 100, cx, cy, ARGB(255, 255, 255, 255));
      pdibBack->stretch_dib(pdib2);

      recta.add(tool1.rectClient);
   }

   void VisualEffect::RenderPixelExplosion2(rect_array & recta)
   {
   Main & main = HelperGetMain();

      TransitionEffect & transitioneffect = main.GetTransitionEffect();
      Graphics & graphics = main.GetGraphics();

      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      ::draw2d::graphics_sp dcBuffer = graphics.GetBufferDC();

      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);
      ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
      ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
      ::draw2d::dib_sp pdib3 = graphics.GetDib(_graphics::DibTemp3);
      ::draw2d::dib_sp pdib4 = graphics.GetDib(_graphics::DibTemp4);
      ::draw2d::dib_sp pdibBuffer = graphics.GetDib(_graphics::DibBuffer);
      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         ::draw2d::dib_sp pdibFrame1 = graphics.GetDib(_graphics::DibFrame1);

         tool1.dmod = 4.2;
         tool1.dminsize = 0;
         int32_t cx1 = tool1.cx / 4;
         int32_t cy1 = tool1.cy / 4;
         pdib1->create(cx1, cy1);
         pdib2->create(cx1, cy1);
         pdib3->create(cx1, cy1);
         pdib4->create(cx1, cy1);
         tool1.dalpha = 0;

         m_explosion.m_density = 1.8;
         m_explosion.m_minradius = 1.7;
         m_explosion.create(cx1, cy1);
         m_explosion.Reset();

         pdib1->get_graphics()->SetStretchBltMode(HALFTONE);
         pdib1->stretch_dib(pdibBuffer);
         pdib3->get_graphics()->SetStretchBltMode(HALFTONE);
         pdib3->stretch_dib(pdibFrame1);
      }
      int32_t cx1 = pdib1->m_size.cx;
      int32_t cy1 = pdib1->m_size.cy;

      pdib3->Fill(0, 0, 0, 0);

      pdib4->get_graphics()->BitBlt(0, 0, cx1, cy1, dcBuffer, 0, 0, SRCCOPY);

#ifdef WINDOWSEX
      GdiFlush();
#endif

      /*System.visual().imaging().bitmap_blend(
         pdib4->get_graphics(),
         0, 0, cx1, cy1,
         pdib1->get_graphics(),
         0, 0,
         (BYTE) max(min(255, tool1.dalpha), 0));*/

      ::index iReturnPoint = transitioneffect.m_tool001.m_iStepCount * 5 / 21;

      m_explosion.to(pdib4->get_data(), pdib3->get_data());

      /*int32_t mod = max(1, (int32_t) tool1.dmod);
      if((tool1.frame % mod) == 0)
      {
         int32_t x = rand() * cx1 / RAND_MAX;
         int32_t y = rand() * cy1 / RAND_MAX;
         int32_t r = rand() * min(tool1.dminsize, 60.0) / RAND_MAX + min(tool1.dminsize / 2, 60.0);
         int32_t h = rand() * 100 / RAND_MAX;
         if(transitioneffect.m_tool001.m_iStep < iReturnPoint)
         {
            tool1.dminsize += 0.5;
         }
         else
         {
            tool1.dminsize -= 0.5;
         }
         m_water.HeightBlob(x, y,
                     r, h, tool1.page);
      }*/

      //m_explostion.CalcPixelExplosion(0, 0);


      if(tool1.dminsize > 20 || tool1.dalpha > 0)
         tool1.dalpha += 0.5;
      if(transitioneffect.m_tool001.m_iStep < iReturnPoint)
      {
         tool1.dmod -= 0.01;
         tool1.frame++;
      }
      else
      {
         tool1.dmod += 0.01;
         tool1.frame--;
      }
      tool1.page ^= 1;

      pdibBack->stretch_dib(pdib3);

      recta.add(tool1.rectClient);
   }


   void VisualEffect::RenderRotateEx8(rect_array & recta)
   {
      Main & main = HelperGetMain();

      TransitionEffect & transitioneffect = main.GetTransitionEffect();

      Graphics & graphics = main.GetGraphics();

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
         m_color.set_rgb(pdib1->GetPixel(
            pdib1->m_size.cx / 2,
            pdib1->m_size.cy / 2));
      }



      rect rectClient = tool1.rectClient;
      tool1.cx = rectClient.width();
      tool1.cy = rectClient.height();
      class imaging & imaging = System.visual().imaging();


      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);
      ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
      ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
      ::draw2d::dib_sp pdib3 = graphics.GetDib(_graphics::DibTemp3);

      int32_t cx1 = pdib1->m_size.cx;
      int32_t cy1 = pdib1->m_size.cy;

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         pdib2->create(cx1, cy1);
         pdib3->create(cx1, cy1);
         pdib2->Fill(0, 0, 0, 0);
         pdib3->Fill(0, 0, 0, 0);
      }


//         int32_t s1 = rand() * 1 / RAND_MAX + 1;
//         int32_t s2 = rand() * 1 / RAND_MAX + 1;
//         int32_t s3 = rand() * 2 / RAND_MAX + 1;
//         int32_t s4 = rand() * 2 / RAND_MAX + 1;

      rect rcTrackBox;

      rcTrackBox.left   = 1;
      rcTrackBox.top    = 1;
      rcTrackBox.right  = cx1 - 1 - rcTrackBox.left;
      rcTrackBox.bottom = cy1 - 1 - rcTrackBox.top;

      rect rcTrackBox2;

      rcTrackBox2.left   = 0;
      rcTrackBox2.top    = 0;
      rcTrackBox2.right  = cx1 - 1 - rcTrackBox2.left;
      rcTrackBox2.bottom = cy1 - 1 - rcTrackBox2.top;

      /*for(int32_t i = 0; i < m_colortrack1a.get_size(); i++)
      {
         ColorTrack1 & ct1 = m_colortrack1a[i];
         ct1.m_rndgrowVelocity.Step();
         TrackDirection001(
            ct1.m_dDirection,
            ct1.m_dDirectionAddUp,
            ct1.m_rndgrowDirectionLatency);
         ct1.m_dCos = ::cos(ct1.m_dDirection * M_PI / 180.0);
         ct1.m_dSin = ::sin(ct1.m_dDirection * M_PI / 180.0);
         ct1.m_ptColorTrack.x += abs(ct1.m_rndgrowVelocity.i) * ct1.m_dCos;
         ct1.m_ptColorTrack.y += abs(ct1.m_rndgrowVelocity.i) * ct1.m_dSin;
         Constraint001(
            ct1.m_ptColorTrack,
            rcTrackBox,
            rcTrackBox2,
            ct1.m_dDirection);
         ct1.m_dSize = rand() * 5 / RAND_MAX + 1;
      }*/

      StepGrow001(
         m_color,
         m_iGrowColor,
         m_iGrowMax);

      StepGrow001(
         m_color2,
         m_iGrowColor2,
         m_iGrowMax2);

      StepGrow001(
         m_color3,
         m_iGrowColor3,
         m_iGrowMax3);

      StepGrow001(
         m_color4,
         m_iGrowColor4,
         m_iGrowMax4);

      color colorStrong1 = m_color;
      color colorStrong3 = m_color2;
      color colorStrong5 = m_color3;
      color colorStrong7 = m_color4;
      color colorStrong2;
      color colorStrong4;
      color colorStrong6;
      color colorStrong8;

      {
         double dH;
         double dL;
         double dS;
         colorStrong1.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong1.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong1.get_hls(dH, dL, dS);
         dL = 0.3;
         dS = 0.1;
         colorStrong2.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong3.get_hls(dH, dL, dS);
         dL = 0.9;
         dS = 0.7;
         colorStrong3.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong3.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.9;
         colorStrong4.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong5.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong5.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong5.get_hls(dH, dL, dS);
         dL = 0.5;
         dS = 0.9;
         colorStrong6.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong7.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong7.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong7.get_hls(dH, dL, dS);
         dL = 0.5;
         dS = 0.9;
         colorStrong8.set_hls(dH, dL, dS);
      }


//            ARGB(255, rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX);

//         BYTE bA = 200;


#ifdef WINDOWSEX
      GdiFlush();
#endif

      //double dmin = min(cx, cy);
      //double dmax = max(cx, cy);abs

      if(m_bGrowColor0)
      {
         //pdib1->get_graphics()->FillSolidRect(0, 0, cx1, cy1, colorStrong1.get_rgb() | (255 << 24));
      }

//         int32_t c1 = rand() * 3 / RAND_MAX;
//         int32_t c2 = rand() * 3 / RAND_MAX;
//         int32_t c4 = rand() * 10 / RAND_MAX + 1;


      m_rndgrowAngleOffsetLatency.Step();
      if(m_rndgrowAngleOffsetLatency.i == 1)
      {
         m_dAngleOffsetAddUp = (5.1 * rand() / RAND_MAX) - 2.05;
      }
      double dOffset3 = (1.0 * rand() / RAND_MAX) - .5;
      m_dAngleOffset += min(10.0, min(2.0, m_dAngleOffsetAddUp + dOffset3));
      m_dAngleOffset = fmod(m_dAngleOffset, 360.0);

//         double dAngleOffset = m_dAngleOffset;
      double dAngle;
      if(m_rndgrowAngleOffsetLatency.i > 50)
      {
         //dAngle = 10.111 + dAngleOffset;
         dAngle = m_dAngleOffset;
      }
      else
      {

         //dAngle = -10.111 - dAngleOffset;
         dAngle = -m_dAngleOffset;
      }
      pdib2->Rotate034(pdib1, dAngle, 1.09);
      //pdib2->rotate(pdib1, dAngle, 1.009);
      //pdib2->Paste(pdib1);
      //imaging.color_blend(pdib2->get_graphics(), cxm - s1, cym - s2, s3, s4, m_color.get_rgb(), bA);


      // top
   /*   imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 / 2, 1, colorStrong1.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, 0, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);
      // left
      imaging.color_blend(pdib1->get_graphics(), 0, 0, 1, cy1 / 2, colorStrong3.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 / 2, 1, cy1 / 2 - 1, colorStrong4.get_rgb(), bA);
      // bottom
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 - 1, cx1 / 2, 1, colorStrong5.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, cy1 - 1, cx1 / 2 - 1, 1, colorStrong6.get_rgb(), bA);
      // right
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, 0, 1, cy1 / 2, colorStrong7.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, cy1 / 2, 1, cy1 / 2 - 1, colorStrong8.get_rgb(), bA);*/

      // top1
      ::draw2d::pen_sp pen1(allocer());
      pen1->create_solid(1, colorStrong1.get_rgb() | (255 << 24));
      pdib1->get_graphics()->SelectObject(pen1);
      int32_t marginx = cx1 / 12;
      int32_t marginy = cy1 * 5 / 11;
      int32_t w = marginx * 2;
      pdib1->get_graphics()->MoveTo(marginx, marginy);

      int32_t imax = cx1 - marginx;
      int32_t jmax = cx1 / 2;
      int32_t rmax = jmax * RAND_MAX;
      int32_t rhalf = RAND_MAX / 2;
      int32_t j = 0;
      int32_t r1 = 0;
      int32_t r2 = 0;
      int32_t i;
      for(i = marginx; i < jmax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 3 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 5 / rmax;
         }
         pdib1->get_graphics()->LineTo(i, r1 + r2 + marginy + ((rand() - rhalf) * j * w / rmax));
         j++;
      }
      for(; i < imax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 3 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 5 / rmax;
         }
         pdib1->get_graphics()->LineTo(i, r1 + r2 + marginy + ((rand() - rhalf) * j * w / rmax));
         j--;
      }

      pdib1->get_graphics()->MoveTo(marginx, cy1 - marginy);

      for(i = marginx; i < jmax; i++)
      {
         pdib1->get_graphics()->LineTo(i, cy1 - marginy + ((rand() - rhalf) * j * w / rmax));
         j++;
      }
      for(; i < imax; i++)
      {
         pdib1->get_graphics()->LineTo(i, cy1 - marginy + ((rand() - rhalf) * j * w / rmax));
         j--;
      }

      pdib1->get_graphics()->MoveTo(marginx, marginy);

      // vertical
   //   imax = cy1 - margin;
      jmax = cy1 / 2;
      rmax = jmax * RAND_MAX;
      rhalf = RAND_MAX / 2;
      j = 0;
      r1 = 0;
      r2 = 0;
     /* for(i = margin; i < jmax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 3 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 5 / rmax;
         }
         pdib1->get_graphics()->LineTo(r1 + r2 + marginy + ((rand() - rhalf) * j * w / rmax), i);
         j++;
      }
      for(; i < imax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 3 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 5 / rmax;
         }
         pdib1->get_graphics()->LineTo(r1 + r2 + marginy + ((rand() - rhalf) * j * w / rmax), i);
         j--;
      }*/

   /*   pdib1->get_graphics()->MoveTo(cx1 - margin, margin);

      for(i = margin; i < jmax; i++)
      {
         pdib1->get_graphics()->LineTo(cx1 - margin + ((rand() - rhalf) * j * w / rmax), i);
         j++;
      }
      for(; i < imax; i++)
      {
         pdib1->get_graphics()->LineTo(cx1 - margin + ((rand() - rhalf) * j * w / rmax), i);
         j--;
      }*/

      //imaging.color_blend(pdib1->get_graphics(), 0, cy1 * 2 / 3, cx1 / 2, 1, , bA);
      //imaging.color_blend(pdib1->get_graphics(), cx1 / 2, cy1 * 2 / 3, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);

      // top
      /*imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 / 2, 1, colorStrong2.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, 0, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);
      // left
      imaging.color_blend(pdib1->get_graphics(), 0, 0, 1, cy1 / 2, colorStrong2.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 / 2, 1, cy1 / 2 - 1, colorStrong2.get_rgb(), bA);
      // bottom
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 - 1, cx1 / 2, 1, colorStrong2.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, cy1 - 1, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);
      // right
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, 0, 1, cy1 / 2, colorStrong2.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, cy1 / 2, 1, cy1 / 2 - 1, colorStrong2.get_rgb(), bA);*/

      imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1, cy1, ARGB(255, 0, 0, 0), 10);

   /*   {
         ::draw2d::pen_sp pen1(get_app(), PS_SOLID, 0, colorStrong1.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush1(get_app(), colorStrong1.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen2(get_app(), PS_SOLID, 0, colorStrong2.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush2(get_app(), colorStrong2.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen3(get_app(), PS_SOLID, 0, colorStrong3.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush3(get_app(), colorStrong3.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen4(get_app(), PS_SOLID, 0, colorStrong4.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush4(get_app(), colorStrong4.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen5(get_app(), PS_SOLID, 0, colorStrong5.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush5(get_app(), colorStrong5.get_rgb() | (255 << 24));
         for(int32_t i = 0; i < m_colortrack1a.get_size(); i++)
         {
            ColorTrack1 & ct1 = m_colortrack1a[i];
            int32_t x1 = ct1.m_ptColorTrack.x;
            int32_t y1 = ct1.m_ptColorTrack.y;
            int32_t d = ct1.m_dSize;
            switch(i % 5)
            {
            case 0:
               {
                  pdib1->get_graphics()->SelectObject(brush1);
                  pdib1->get_graphics()->SelectObject(pen1);
               }
               break;
            case 1:
               {
                  pdib1->get_graphics()->SelectObject(brush2);
                  pdib1->get_graphics()->SelectObject(pen2);
               }
               break;
            case 2:
               {
                  pdib1->get_graphics()->SelectObject(brush3);
                  pdib1->get_graphics()->SelectObject(pen3);
               }
            case 3:
               {
                  pdib1->get_graphics()->SelectObject(brush4);
                  pdib1->get_graphics()->SelectObject(pen4);
               }
            case 4:
               {
                  pdib1->get_graphics()->SelectObject(brush5);
                  pdib1->get_graphics()->SelectObject(pen5);
               }
               break;
            }
            pdib1->get_graphics()->Rectangle(x1, y1, x1 + d, y1 + d);
         }

      }*/



      /*imaging.bitmap_blend(
         pdib1->get_graphics(),
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0,
         50);*/

      pdib2->channel_multiply(::visual::rgba::channel_alpha, 127.0 / 255.0);

      pdib1->get_graphics()->BitBlt(
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0, SRCCOPY);
      pdibBack->stretch_dib(pdib1);

      recta.add(rectClient);
   }


   void VisualEffect::RenderExpand4(rect_array & recta)
   {
      Main & main = HelperGetMain();

      TransitionEffect & transitioneffect = main.GetTransitionEffect();

      Graphics & graphics = main.GetGraphics();

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
         m_color.set_rgb(pdib1->GetPixel(
            pdib1->m_size.cx / 2,
            pdib1->m_size.cy / 2));
      }



      rect rectClient = tool1.rectClient;
      tool1.cx = rectClient.width();
      tool1.cy = rectClient.height();
      class imaging & imaging = System.visual().imaging();


      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);
      ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
      ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
      ::draw2d::dib_sp pdib3 = graphics.GetDib(_graphics::DibTemp3);

      int32_t cx1 = pdib1->m_size.cx;
      int32_t cy1 = pdib1->m_size.cy;

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         pdib2->create(cx1, cy1);
         pdib3->create(cx1, cy1);
      }


      rect rcTrackBox;

      rcTrackBox.left   = 1;
      rcTrackBox.top    = 1;
      rcTrackBox.right  = cx1 - 1 - rcTrackBox.left;
      rcTrackBox.bottom = cy1 - 1 - rcTrackBox.top;

      rect rcTrackBox2;

      rcTrackBox2.left   = 0;
      rcTrackBox2.top    = 0;
      rcTrackBox2.right  = cx1 - 1 - rcTrackBox2.left;
      rcTrackBox2.bottom = cy1 - 1 - rcTrackBox2.top;

      /*for(int32_t i = 0; i < m_colortrack1a.get_size(); i++)
      {
         ColorTrack1 & ct1 = m_colortrack1a[i];
         ct1.m_rndgrowVelocity.Step();
         TrackDirection001(
            ct1.m_dDirection,
            ct1.m_dDirectionAddUp,
            ct1.m_rndgrowDirectionLatency);
         ct1.m_dCos = ::cos(ct1.m_dDirection * M_PI / 180.0);
         ct1.m_dSin = ::sin(ct1.m_dDirection * M_PI / 180.0);
         ct1.m_ptColorTrack.x += abs(ct1.m_rndgrowVelocity.i) * ct1.m_dCos;
         ct1.m_ptColorTrack.y += abs(ct1.m_rndgrowVelocity.i) * ct1.m_dSin;
         Constraint001(
            ct1.m_ptColorTrack,
            rcTrackBox,
            rcTrackBox2,
            ct1.m_dDirection);
         ct1.m_dSize = rand() * 5 / RAND_MAX + 1;
      }*/

      StepGrow001(
         m_color,
         m_iGrowColor,
         m_iGrowMax);

      StepGrow001(
         m_color2,
         m_iGrowColor2,
         m_iGrowMax2);

      StepGrow001(
         m_color3,
         m_iGrowColor3,
         m_iGrowMax3);

      StepGrow001(
         m_color4,
         m_iGrowColor4,
         m_iGrowMax4);

      color colorStrong1 = m_color;
      color colorStrong3 = m_color2;
      color colorStrong5 = m_color3;
      color colorStrong7 = m_color4;
      color colorStrong2;
      color colorStrong4;
      color colorStrong6;
      color colorStrong8;

      {
         double dH;
         double dL;
         double dS;
         colorStrong1.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong1.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong1.get_hls(dH, dL, dS);
         dL = 0.3;
         dS = 0.1;
         colorStrong2.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong3.get_hls(dH, dL, dS);
         dL = 0.9;
         dS = 0.7;
         colorStrong3.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong3.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.9;
         colorStrong4.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong5.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong5.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong5.get_hls(dH, dL, dS);
         dL = 0.5;
         dS = 0.9;
         colorStrong6.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong7.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong7.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong7.get_hls(dH, dL, dS);
         dL = 0.5;
         dS = 0.9;
         colorStrong8.set_hls(dH, dL, dS);
      }


//            ARGB(255, rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX);

      BYTE bA = 200;


#ifdef WINDOWSEX
      GdiFlush();
#endif

      //double dmin = min(cx, cy);
      //double dmax = max(cx, cy);abs

      if(m_bGrowColor0)
      {
         //pdib1->get_graphics()->FillSolidRect(0, 0, cx1, cy1, colorStrong1.get_rgb() | (255 << 24));
      }

     // ::draw2d::graphics_sp pdib3->get_graphics();
      //pdib3->get_graphics()->CreateCompatibleDC(NULL);
      //pdib3->get_graphics()->SelectObject(pdib3->m_hbitmap);

   //   pdib3->stretch_dib(pdibBuffer);

   //   pdib3->Paste(pdib1);

//         int32_t c1 = rand() * 3 / RAND_MAX;
//         int32_t c2 = rand() * 3 / RAND_MAX;
//         int32_t c4 = rand() * 10 / RAND_MAX + 1;


      m_rndgrowAngleOffsetLatency.Step();
      if(m_rndgrowAngleOffsetLatency.i == 1)
      {
         m_dAngleOffsetAddUp = (5.1 * rand() / RAND_MAX) - 2.05;
      }
      double dOffset3 = (1.0 * rand() / RAND_MAX) - .5;
      m_dAngleOffset += min(10.0, min(2.0, m_dAngleOffsetAddUp + dOffset3));
      m_dAngleOffset = fmod(m_dAngleOffset, 360.0);

//         double dAngleOffset = m_dAngleOffset;
      double dAngle;
      if(m_rndgrowAngleOffsetLatency.i > 50)
      {
         //dAngle = 10.111 + dAngleOffset;
         dAngle = m_dAngleOffset;
      }
      else
      {

         //dAngle = -10.111 - dAngleOffset;
         dAngle = -m_dAngleOffset;
      }
      //pdib2->rotate(pdib1, dAngle, 1.09);
      //pdib2->rotate(pdib1, dAngle, 1.009);
      //pdib2->Paste(pdib1);
      //imaging.color_blend(pdib2->get_graphics(), cxm - s1, cym - s2, s3, s4, m_color.get_rgb(), bA);


      // top
   /*   imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 / 2, 1, colorStrong1.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, 0, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);
      // left
      imaging.color_blend(pdib1->get_graphics(), 0, 0, 1, cy1 / 2, colorStrong3.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 / 2, 1, cy1 / 2 - 1, colorStrong4.get_rgb(), bA);
      // bottom
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 - 1, cx1 / 2, 1, colorStrong5.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, cy1 - 1, cx1 / 2 - 1, 1, colorStrong6.get_rgb(), bA);
      // right
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, 0, 1, cy1 / 2, colorStrong7.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, cy1 / 2, 1, cy1 / 2 - 1, colorStrong8.get_rgb(), bA);*/

      // top1
      ::draw2d::pen_sp pen1(allocer());
      pen1->create_solid(1, colorStrong1.get_rgb() | (255 << 24));
      pdib1->get_graphics()->SelectObject(pen1);
      int32_t margin = 10;
      int32_t w = margin * 2;
      pdib1->get_graphics()->MoveTo(margin, margin);

      int32_t imax = cx1 - margin;
      int32_t jmax = cx1 / 2;
      int32_t rmax = jmax * RAND_MAX;
      int32_t rhalf = RAND_MAX / 2;
      int32_t j = 0;
      int32_t r1 = 0;
      int32_t r2 = 0;
      int32_t i;
      for(i = margin; i < jmax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 3 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 5 / rmax;
         }
         pdib1->get_graphics()->LineTo(i, r1 + r2 + margin + ((rand() - rhalf) * j * w / rmax));
         j++;
      }
      for(; i < imax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 3 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 5 / rmax;
         }
         pdib1->get_graphics()->LineTo(i, r1 + r2 + margin + ((rand() - rhalf) * j * w / rmax));
         j--;
      }

      pdib1->get_graphics()->MoveTo(margin, cy1 - margin);

      for(i = margin; i < jmax; i++)
      {
         pdib1->get_graphics()->LineTo(i, cy1 - margin + ((rand() - rhalf) * j * w / rmax));
         j++;
      }
      for(; i < imax; i++)
      {
         pdib1->get_graphics()->LineTo(i, cy1 - margin + ((rand() - rhalf) * j * w / rmax));
         j--;
      }

      pdib1->get_graphics()->MoveTo(margin, margin);

      // vertical
      imax = cy1 - margin;
      jmax = cy1 / 2;
      rmax = jmax * RAND_MAX;
      rhalf = RAND_MAX / 2;
      j = 0;
      r1 = 0;
      r2 = 0;
      for(i = margin; i < jmax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 3 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 5 / rmax;
         }
         pdib1->get_graphics()->LineTo(r1 + r2 + margin + ((rand() - rhalf) * j * w / rmax), i);
         j++;
      }
      for(; i < imax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 3 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 5 / rmax;
         }
         pdib1->get_graphics()->LineTo(r1 + r2 + margin + ((rand() - rhalf) * j * w / rmax), i);
         j--;
      }

      pdib1->get_graphics()->MoveTo(cx1 - margin, margin);

      for(i = margin; i < jmax; i++)
      {
         pdib1->get_graphics()->LineTo(cx1 - margin + ((rand() - rhalf) * j * w / rmax), i);
         j++;
      }
      for(; i < imax; i++)
      {
         pdib1->get_graphics()->LineTo(cx1 - margin + ((rand() - rhalf) * j * w / rmax), i);
         j--;
      }

      //imaging.color_blend(pdib1->get_graphics(), 0, cy1 * 2 / 3, cx1 / 2, 1, , bA);
      //imaging.color_blend(pdib1->get_graphics(), cx1 / 2, cy1 * 2 / 3, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);

      {
         int32_t x2 = cx1 / 2;
         int32_t y2 = cy1 / 2;
         int32_t w2 = cx1 / 2 - 1;
         int32_t h2 = cy1 / 2 - 1;

         // top
         imaging.color_blend(pdib1->get_graphics(),  0, 0, w2, 1, colorStrong2.get_rgb(), bA);
         imaging.color_blend(pdib1->get_graphics(), x2, 0, w2, 1, colorStrong2.get_rgb(), bA);
         // left
         imaging.color_blend(pdib1->get_graphics(), 0,  0, 1, h2, colorStrong2.get_rgb(), bA);
         imaging.color_blend(pdib1->get_graphics(), 0, y2, 1, h2, colorStrong2.get_rgb(), bA);
         // bottom
         imaging.color_blend(pdib1->get_graphics(),  0, cy1 - 1, w2, 1, colorStrong2.get_rgb(), bA);
         imaging.color_blend(pdib1->get_graphics(), x2, cy1 - 1, w2, 1, colorStrong2.get_rgb(), bA);
         // right
         imaging.color_blend(pdib1->get_graphics(), cx1 - 1, 0, 1, h2, colorStrong2.get_rgb(), bA);
         imaging.color_blend(pdib1->get_graphics(), cx1 - 1, y2, 1, h2, colorStrong2.get_rgb(), bA);
      }

   /*   {
         ::draw2d::pen_sp pen1(get_app(), PS_SOLID, 0, colorStrong1.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush1(get_app(), colorStrong1.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen2(get_app(), PS_SOLID, 0, colorStrong2.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush2(get_app(), colorStrong2.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen3(get_app(), PS_SOLID, 0, colorStrong3.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush3(get_app(), colorStrong3.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen4(get_app(), PS_SOLID, 0, colorStrong4.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush4(get_app(), colorStrong4.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen5(get_app(), PS_SOLID, 0, colorStrong5.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush5(get_app(), colorStrong5.get_rgb() | (255 << 24));
         for(int32_t i = 0; i < m_colortrack1a.get_size(); i++)
         {
            ColorTrack1 & ct1 = m_colortrack1a[i];
            int32_t x1 = ct1.m_ptColorTrack.x;
            int32_t y1 = ct1.m_ptColorTrack.y;
            int32_t d = ct1.m_dSize;
            switch(i % 5)
            {
            case 0:
               {
                  pdib1->get_graphics()->SelectObject(brush1);
                  pdib1->get_graphics()->SelectObject(pen1);
               }
               break;
            case 1:
               {
                  pdib1->get_graphics()->SelectObject(brush2);
                  pdib1->get_graphics()->SelectObject(pen2);
               }
               break;
            case 2:
               {
                  pdib1->get_graphics()->SelectObject(brush3);
                  pdib1->get_graphics()->SelectObject(pen3);
               }
            case 3:
               {
                  pdib1->get_graphics()->SelectObject(brush4);
                  pdib1->get_graphics()->SelectObject(pen4);
               }
            case 4:
               {
                  pdib1->get_graphics()->SelectObject(brush5);
                  pdib1->get_graphics()->SelectObject(pen5);
               }
               break;
            }
            pdib1->get_graphics()->Rectangle(x1, y1, x1 + d, y1 + d);
         }

      }*/



      /*imaging.bitmap_blend(
         pdib1->get_graphics(),
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0,
         50);*/

      pdib2->channel_multiply(::visual::rgba::channel_alpha, 127.0 / 255.0);

      pdib1->get_graphics()->BitBlt(
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0, SRCCOPY);

      pdibBack->stretch_dib(pdib1);

      recta.add(rectClient);
   }






   void VisualEffect::RenderExpand5(rect_array & recta)
   {
      Main & main = HelperGetMain();

      TransitionEffect & transitioneffect = main.GetTransitionEffect();

      Graphics & graphics = main.GetGraphics();

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
         m_color.set_rgb(pdib1->GetPixel(
            pdib1->m_size.cx / 2,
            pdib1->m_size.cy / 2));
      }

      rect rectClient = tool1.rectClient;
      tool1.cx = rectClient.width();
      tool1.cy = rectClient.height();
      class imaging & imaging = System.visual().imaging();


      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);
      ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
      ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
      ::draw2d::dib_sp pdib3 = graphics.GetDib(_graphics::DibTemp3);
      ::draw2d::dib_sp pdib4 = graphics.GetDib(_graphics::DibTemp4);

      int32_t cx1 = pdib1->m_size.cx;
      int32_t cy1 = pdib1->m_size.cy;

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         if(m_pointa.get_size() != cx1)
         {
            m_pointa.allocate(cx1);
            m_pointa1.allocate(cx1);
            m_pointa2.allocate(cx1);

            for(int32_t i = 0; i < cx1; i++)
            {
               m_pointa[i].y = cy1 / 2;
               m_pointa1[i].y = 0;
               m_pointa1[i].y = 0;
            }
         }
      }

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         pdib2->create(cx1, cy1);
         pdib3->create(cx1, cy1);
         pdib4->create(tool1.cx, tool1.cy);
      }

      if(m_iVisual == VisualEffectExpand6)
      {
         pdib2->FillByte(0);
         pdib3->FillByte(0);
      }

      StepGrow034(
         m_color,
         m_iGrowColor,
         m_iGrowMax);

      color colorStrong1 = m_color;

      {
         double dH;
         double dL;
         double dS;
         colorStrong1.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong1.set_hls(dH, dL, dS);
      }

      ::draw2d::pen_sp pen1(allocer());
      pen1->create_solid(1, colorStrong1.get_rgb() | (255 << 24));
      ::draw2d::pen_sp penWhite(allocer());
      penWhite->create_solid(3, ARGB(255, 205, 205, 205));
      int32_t margin1 = cx1 / 8;
      int32_t margin2 = cy1 / 2;
      int32_t w = cy1 / 3;

      double jmul = (double) cy1 / (cx1 * 2.0);

      double delta = w;


      int32_t imax = cx1 - margin1;
      int32_t jmax = cx1 / 2;
      int32_t rmax = jmax * RAND_MAX;
      double rhalf = RAND_MAX / 2.0;
      int32_t j = 0;
//         int32_t r1 = 0;
//         int32_t r2 = 0;


      double offset;

      double jres;
      int32_t i;
      for(i = margin1; i < jmax; i++)
      {
         /*if((i % 5) == 0)
         {
             r1 = (rand() - rhalf) * j * 1 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 2 / rmax;
         }*/
         m_pointa[i].x = i;
         //offset = r1 + r2 + ((rand() - rhalf) * j * delta / rmax);
         jres = j * jmul;
         offset = (rand() - rhalf) * j * delta / rmax;
         m_pointa[i].y = (LONG) max(margin2 - jres, min(margin2 + jres, m_pointa[i - 1].y + offset));
         m_pointa[i].y = (LONG) (m_pointa[i].y + margin2) / 2;
         j++;
      }
      j = 0;
      for(i = imax - 1; i >= jmax; i--)
      {
         /*if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 1 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 2 / rmax;
         }*/
         m_pointa[i].x = i;
         //offset = r1 + r2 + ((rand() - rhalf) * j * delta / rmax);
         jres = j * jmul;
         offset = ((rand() - rhalf) * j * delta / rmax);
         m_pointa[i].y = (LONG) max(margin2 - jres, min(margin2 + jres, m_pointa[i + 1].y + offset));
         m_pointa[i].y = (LONG) (m_pointa[i].y + margin2) / 2;
         j++;
      }

      bool bWhite;
      bWhite = false;
      if(m_iVisual == VisualEffectRotateEx5)
      {
         pdib1->get_graphics()->SelectObject(penWhite);
         pdib1->get_graphics()->MoveTo(m_pointa[margin1].x, m_pointa[margin1].y);
         for(i = margin1; i < imax; i++)
         {
            pdib1->get_graphics()->LineTo(m_pointa[i].x, m_pointa[i].y);
         }
      }
      pdib1->get_graphics()->SelectObject(pen1);
      pdib1->get_graphics()->MoveTo(m_pointa[margin1].x, m_pointa[margin1].y);
      for(i = margin1; i < imax; i++)
      {
         pdib1->get_graphics()->LineTo(m_pointa[i].x, m_pointa[i].y);
      }

      imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 , cy1, ARGB(255, 0, 0, 0), 10);

#ifdef WINDOWSEX
      GdiFlush();
#endif

      if(m_iVisual == VisualEffectRotateEx6)
      {


         keep < bool > keepTransferVoid (&HelperGetMain().GetInterface().m_bTransferVoid, true, false, true);


         pdib4->stretch_dib(pdib1);
         HelperGetMain().GetInterface().BackViewFeedback(pdib4->get_graphics());
         pdib1->get_graphics()->SetStretchBltMode(HALFTONE);
         pdib1->stretch_dib(pdib4);
         keepTransferVoid.KeepAway();
      }



      m_rndgrowAngleOffsetLatency.Step();
      if(m_rndgrowAngleOffsetLatency.i == 0)
      {
         m_dAngleOffsetAddUp = (10.0 * rand() / RAND_MAX) - 5.0;
      }

      m_dAngleOffset = m_dAngleOffsetAddUp;
      m_dAngleOffset = fmod(m_dAngleOffset, 360.0);

      double dAngleOffset = m_dAngleOffset;
      double dAngle;
      if(m_iGrowColor >= 0)
      {
         dAngle = 1.511 + dAngleOffset;
      }
      else
      {

         dAngle = -1.511 - dAngleOffset;
      }
      //pdib2->Rotate034(pdib1, dAngle, 0.95);


      pdib2->channel_multiply(::visual::rgba::channel_alpha, 127.0 / 255.0);

      pdib1->get_graphics()->BitBlt(
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0, SRCCOPY);

      pdibBack->stretch_dib(pdib1);

      recta.add(rectClient);
   }

   void VisualEffect::RenderExpand7(rect_array & recta)
   {
      Main & main = HelperGetMain();

      TransitionEffect & transitioneffect = main.GetTransitionEffect();

      Graphics & graphics = main.GetGraphics();

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
         m_color.set_rgb(pdib1->GetPixel(
            pdib1->m_size.cx / 2,
            pdib1->m_size.cy / 2));
      }



      rect rectClient = tool1.rectClient;
      tool1.cx = rectClient.width();
      tool1.cy = rectClient.height();
      class imaging & imaging = System.visual().imaging();


      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);
      ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
      ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
      ::draw2d::dib_sp pdib3 = graphics.GetDib(_graphics::DibTemp3);

      int32_t cx1 = pdib1->m_size.cx;
      int32_t cy1 = pdib1->m_size.cy;

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         if(m_pointa.get_size() != cx1)
         {
            m_pointa.allocate(cx1);
            m_pointa1.allocate(cx1);
            m_pointa2.allocate(cx1);

            for(int32_t i = 0; i < cx1; i++)
            {
               m_pointa[i].y = cy1 / 2;
               m_pointa1[i].y = 0;
               m_pointa1[i].y = 0;
            }
         }
      }

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         pdib2->create(cx1, cy1);
         pdib3->create(cx1, cy1);
      }


//         int32_t s1 = rand() * 1 / RAND_MAX + 1;
//         int32_t s2 = rand() * 1 / RAND_MAX + 1;
//         int32_t s3 = rand() * 2 / RAND_MAX + 1;
//         int32_t s4 = rand() * 2 / RAND_MAX + 1;

      rect rcTrackBox;

      rcTrackBox.left   = 1;
      rcTrackBox.top    = 1;
      rcTrackBox.right  = cx1 - 1 - rcTrackBox.left;
      rcTrackBox.bottom = cy1 - 1 - rcTrackBox.top;

      rect rcTrackBox2;

      rcTrackBox2.left   = 0;
      rcTrackBox2.top    = 0;
      rcTrackBox2.right  = cx1 - 1 - rcTrackBox2.left;
      rcTrackBox2.bottom = cy1 - 1 - rcTrackBox2.top;

      /*for(int32_t i = 0; i < m_colortrack1a.get_size(); i++)
      {
         ColorTrack1 & ct1 = m_colortrack1a[i];
         ct1.m_rndgrowVelocity.Step();
         TrackDirection001(
            ct1.m_dDirection,
            ct1.m_dDirectionAddUp,
            ct1.m_rndgrowDirectionLatency);
         ct1.m_dCos = ::cos(ct1.m_dDirection * M_PI / 180.0);
         ct1.m_dSin = ::sin(ct1.m_dDirection * M_PI / 180.0);
         ct1.m_ptColorTrack.x += abs(ct1.m_rndgrowVelocity.i) * ct1.m_dCos;
         ct1.m_ptColorTrack.y += abs(ct1.m_rndgrowVelocity.i) * ct1.m_dSin;
         Constraint001(
            ct1.m_ptColorTrack,
            rcTrackBox,
            rcTrackBox2,
            ct1.m_dDirection);
         ct1.m_dSize = rand() * 5 / RAND_MAX + 1;
      }*/

      StepGrow034(
         m_color,
         m_iGrowColor,
         m_iGrowMax);

      /*StepGrow001(
         m_color2,
         m_iGrowColor2,
         m_iGrowMax2);

      StepGrow001(
         m_color3,
         m_iGrowColor3,
         m_iGrowMax3);

      StepGrow001(
         m_color4,
         m_iGrowColor4,
         m_iGrowMax4);*/

      color colorStrong1 = m_color;
      color colorStrong3 = m_color2;
      color colorStrong5 = m_color3;
      color colorStrong7 = m_color4;
      color colorStrong2;
      color colorStrong4;
      color colorStrong6;
      color colorStrong8;

      {
         double dH;
         double dL;
         double dS;
         colorStrong1.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong1.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong1.get_hls(dH, dL, dS);
         dL = 0.3;
         dS = 0.1;
         colorStrong2.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong3.get_hls(dH, dL, dS);
         dL = 0.9;
         dS = 0.7;
         colorStrong3.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong3.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.9;
         colorStrong4.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong5.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong5.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong5.get_hls(dH, dL, dS);
         dL = 0.5;
         dS = 0.9;
         colorStrong6.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong7.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong7.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong7.get_hls(dH, dL, dS);
         dL = 0.5;
         dS = 0.9;
         colorStrong8.set_hls(dH, dL, dS);
      }


//            ARGB(255, rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX);

//         BYTE bA = 200;


#ifdef WINDOWSEX
      GdiFlush();
#endif

      //double dmin = min(cx, cy);
      //double dmax = max(cx, cy);abs

      if(m_bGrowColor0)
      {
         //pdib1->get_graphics()->FillSolidRect(0, 0, cx1, cy1, colorStrong1.get_rgb() | (255 << 24));
      }

     // ::draw2d::graphics_sp pdib3->get_graphics();
      //pdib3->get_graphics()->CreateCompatibleDC(NULL);
      //pdib3->get_graphics()->SelectObject(pdib3->m_hbitmap);

   //   pdib3->stretch_dib(pdibBuffer);

   //   pdib3->Paste(pdib1);

//         int32_t c1 = rand() * 3 / RAND_MAX;
//         int32_t c2 = rand() * 3 / RAND_MAX;
//         int32_t c4 = rand() * 10 / RAND_MAX + 1;
















      /*   m_rndgrowAngleOffsetLatency.Step();
      if(m_rndgrowAngleOffsetLatency.i == 1)
      {
         m_dAngleOffsetAddUp = (5.1 * rand() / RAND_MAX) - 2.05;
      }
      double dOffset3 = (1.0 * rand() / RAND_MAX) - .5;
      m_dAngleOffset += min(10.0, min(2.0, m_dAngleOffsetAddUp + dOffset3));
      m_dAngleOffset = fmod(m_dAngleOffset, 360.0);

      double dAngleOffset = m_dAngleOffset;
      double dAngle;
      if(m_rndgrowAngleOffsetLatency.i > 50)
      {
         //dAngle = 10.111 + dAngleOffset;
         dAngle = m_dAngleOffset;
      }
      else
      {

         //dAngle = -10.111 - dAngleOffset;
         dAngle = -m_dAngleOffset;
      }
      pdib2->rotate(pdib1, dAngle, 0.95);*/
























      //pdib2->rotate(pdib1, dAngle, 1.009);
      //pdib2->Paste(pdib1);
      //imaging.color_blend(pdib2->get_graphics(), cxm - s1, cym - s2, s3, s4, m_color.get_rgb(), bA);


      // top
   /*   imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 / 2, 1, colorStrong1.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, 0, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);
      // left
      imaging.color_blend(pdib1->get_graphics(), 0, 0, 1, cy1 / 2, colorStrong3.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 / 2, 1, cy1 / 2 - 1, colorStrong4.get_rgb(), bA);
      // bottom
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 - 1, cx1 / 2, 1, colorStrong5.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, cy1 - 1, cx1 / 2 - 1, 1, colorStrong6.get_rgb(), bA);
      // right
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, 0, 1, cy1 / 2, colorStrong7.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, cy1 / 2, 1, cy1 / 2 - 1, colorStrong8.get_rgb(), bA);*/

      // top1
      ::draw2d::pen_sp pen1(allocer());
      pen1->create_solid(1, colorStrong1.get_rgb() | (255 << 24));
      ::draw2d::pen_sp penWhite(allocer());
      penWhite->create_solid(3, ARGB(255, 205, 205, 205));
      int32_t margin1 = 10;
//         int32_t margin2 = cy1 / 2;
      int32_t w = cy1 / 3;

      int32_t delta = 5;


      int32_t imax = cx1 - margin1;
      int32_t jmax = cx1 / 2;
      int32_t rmax = jmax * RAND_MAX;
      int32_t rhalf = RAND_MAX / 2;
      int32_t j = 0;
      int32_t r1 = 0;
      int32_t r2 = 0;


      int32_t offset;
      int32_t i;
      for(i = margin1; i < jmax; i++)
      {
         if((i % 5) == 0)
         {
             r1 = (rand() - rhalf) * j * 1 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 2 / rmax;
         }
         m_pointa[i].x = i;
         offset = r1 + r2 + ((rand() - rhalf) * j * delta / rmax);
         m_pointa[i].y = max(- j * w , min( j * w , m_pointa[i].y + offset));
         j++;
      }
      for(; i < imax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 1 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 2 / rmax;
         }
         m_pointa[i].x = i;
         offset = r1 + r2 + ((rand() - rhalf) * j * delta / rmax);
         m_pointa[i].y = max(- j * w , min( j * w , m_pointa[i].y + offset));
         j--;
      }
      pdib1->get_graphics()->SelectObject(penWhite);
      pdib1->get_graphics()->MoveTo(m_pointa[margin1].x, m_pointa[margin1].y);
      for(i = margin1; i < imax; i++)
      {
         pdib1->get_graphics()->LineTo(m_pointa[i].x, m_pointa[i].y);
      }
      pdib1->get_graphics()->SelectObject(pen1);
      pdib1->get_graphics()->MoveTo(m_pointa[margin1].x, m_pointa[margin1].y);
      for(i = margin1; i < imax; i++)
      {
         pdib1->get_graphics()->LineTo(m_pointa[i].x, m_pointa[i].y);
      }

      imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 , cy1, ARGB(255, 34, 34, 34), 10);

   /*   pdib1->get_graphics()->MoveTo(margin1, cy1 - margin2);

      for(i = margin1; i < jmax; i++)
      {
         pdib1->get_graphics()->LineTo(i, cy1 - margin2 + ((rand() - rhalf) * j * w / rmax));
         j++;
      }
      for(; i < imax; i++)
      {
         pdib1->get_graphics()->LineTo(i, cy1 - margin2 + ((rand() - rhalf) * j * w / rmax));
         j--;
      }

      pdib1->get_graphics()->MoveTo(margin2, margin1);

      // vertical
      imax = cy1 - margin1;
      jmax = cy1 / 2;
      rmax = jmax * RAND_MAX;
      rhalf = RAND_MAX / 2;
      j = 0;
      r1 = 0;
      r2 = 0;
      for(i = margin1; i < jmax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 3 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 5 / rmax;
         }
         pdib1->get_graphics()->LineTo(r1 + r2 + margin2 + ((rand() - rhalf) * j * w / rmax), i);
         j++;
      }
      for(; i < imax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 3 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 5 / rmax;
         }
         pdib1->get_graphics()->LineTo(r1 + r2 + margin2 + ((rand() - rhalf) * j * w / rmax), i);
         j--;
      }

      pdib1->get_graphics()->MoveTo(cx1 - margin2, margin1);

      for(i = margin1; i < jmax; i++)
      {
         pdib1->get_graphics()->LineTo(cx1 - margin2 + ((rand() - rhalf) * j * w / rmax), i);
         j++;
      }
      for(; i < imax; i++)
      {
         pdib1->get_graphics()->LineTo(cx1 - margin2 + ((rand() - rhalf) * j * w / rmax), i);
         j--;
      }*/

      //imaging.color_blend(pdib1->get_graphics(), 0, cy1 * 2 / 3, cx1 / 2, 1, , bA);
      //imaging.color_blend(pdib1->get_graphics(), cx1 / 2, cy1 * 2 / 3, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);

      // top
     /* imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 / 2, 1, colorStrong2.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, 0, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);
      // left
      imaging.color_blend(pdib1->get_graphics(), 0, 0, 1, cy1 / 2, colorStrong2.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 / 2, 1, cy1 / 2 - 1, colorStrong2.get_rgb(), bA);
      // bottom
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 - 1, cx1 / 2, 1, colorStrong2.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, cy1 - 1, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);
      // right
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, 0, 1, cy1 / 2, colorStrong2.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, cy1 / 2, 1, cy1 / 2 - 1, colorStrong2.get_rgb(), bA);


   //   pdib1->get_graphics()->FillSolidRect(0, 0, cx1 / 2, cy1 / 2, 0);*/
   /*   {
         ::draw2d::pen_sp pen1(get_app(), PS_SOLID, 0, colorStrong1.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush1(get_app(), colorStrong1.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen2(get_app(), PS_SOLID, 0, colorStrong2.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush2(get_app(), colorStrong2.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen3(get_app(), PS_SOLID, 0, colorStrong3.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush3(get_app(), colorStrong3.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen4(get_app(), PS_SOLID, 0, colorStrong4.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush4(get_app(), colorStrong4.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen5(get_app(), PS_SOLID, 0, colorStrong5.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush5(get_app(), colorStrong5.get_rgb() | (255 << 24));
         for(int32_t i = 0; i < m_colortrack1a.get_size(); i++)
         {
            ColorTrack1 & ct1 = m_colortrack1a[i];
            int32_t x1 = ct1.m_ptColorTrack.x;
            int32_t y1 = ct1.m_ptColorTrack.y;
            int32_t d = ct1.m_dSize;
            switch(i % 5)
            {
            case 0:
               {
                  pdib1->get_graphics()->SelectObject(brush1);
                  pdib1->get_graphics()->SelectObject(pen1);
               }
               break;
            case 1:
               {
                  pdib1->get_graphics()->SelectObject(brush2);
                  pdib1->get_graphics()->SelectObject(pen2);
               }
               break;
            case 2:
               {
                  pdib1->get_graphics()->SelectObject(brush3);
                  pdib1->get_graphics()->SelectObject(pen3);
               }
            case 3:
               {
                  pdib1->get_graphics()->SelectObject(brush4);
                  pdib1->get_graphics()->SelectObject(pen4);
               }
            case 4:
               {
                  pdib1->get_graphics()->SelectObject(brush5);
                  pdib1->get_graphics()->SelectObject(pen5);
               }
               break;
            }
            pdib1->get_graphics()->Rectangle(x1, y1, x1 + d, y1 + d);
         }

      }*/

         m_rndgrowAngleOffsetLatency.Step();
      if(m_rndgrowAngleOffsetLatency.i == 0)
      {
         m_dAngleOffsetAddUp = (10.0 * rand() / RAND_MAX) - 5.0;
      }
      //m_dAngleOffset += m_dAngleOffsetAddUp;
      m_dAngleOffset = m_dAngleOffsetAddUp;
      m_dAngleOffset = fmod(m_dAngleOffset, 360.0);

      double dAngleOffset = m_dAngleOffset;
      double dAngle;
      if(m_iGrowColor >= 0)
      {
         dAngle = 1.511 + dAngleOffset;
      }
      else
      {

         dAngle = -1.511 - dAngleOffset;
      }
      //pdib2->Rotate034(pdib1, dAngle, 0.95);


      /*imaging.bitmap_blend(
         pdib1->get_graphics(),
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0,
         50);*/

      pdib2->channel_multiply(::visual::rgba::channel_alpha, 127.0 / 255.0);

      pdib1->get_graphics()->BitBlt(
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0, SRCCOPY);

      pdibBack->stretch_dib(pdib1);

      recta.add(rectClient);
   }




   void VisualEffect::RenderExpand8(rect_array & recta)
   {
      Main & main = HelperGetMain();

      TransitionEffect & transitioneffect = main.GetTransitionEffect();

      Graphics & graphics = main.GetGraphics();

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
         m_color.set_rgb(pdib1->GetPixel(
            pdib1->m_size.cx / 2,
            pdib1->m_size.cy / 2));
      }



      rect rectClient = tool1.rectClient;
      tool1.cx = rectClient.width();
      tool1.cy = rectClient.height();
      class imaging & imaging = System.visual().imaging();


      ASSERT(graphics.GetBufferDC()->get_os_data() != NULL);

      ::draw2d::dib_sp pdibBack = graphics.GetDib(_graphics::DibBack);
      ::draw2d::dib_sp pdib1 = graphics.GetDib(_graphics::DibTemp1);
      ::draw2d::dib_sp pdib2 = graphics.GetDib(_graphics::DibTemp2);
      ::draw2d::dib_sp pdib3 = graphics.GetDib(_graphics::DibTemp3);

      int32_t cx1 = pdib1->m_size.cx;
      int32_t cy1 = pdib1->m_size.cy;

      if(transitioneffect.m_tool001.m_iStep == 1)
      {
         pdib2->create(cx1, cy1);
         pdib3->create(cx1, cy1);
      }

//         int32_t s1 = rand() * 1 / RAND_MAX + 1;
//         int32_t s2 = rand() * 1 / RAND_MAX + 1;
//         int32_t s3 = rand() * 2 / RAND_MAX + 1;
//         int32_t s4 = rand() * 2 / RAND_MAX + 1;

      rect rcTrackBox;

      rcTrackBox.left   = 1;
      rcTrackBox.top    = 1;
      rcTrackBox.right  = cx1 - 1 - rcTrackBox.left;
      rcTrackBox.bottom = cy1 - 1 - rcTrackBox.top;

      rect rcTrackBox2;

      rcTrackBox2.left   = 0;
      rcTrackBox2.top    = 0;
      rcTrackBox2.right  = cx1 - 1 - rcTrackBox2.left;
      rcTrackBox2.bottom = cy1 - 1 - rcTrackBox2.top;

      /*for(int32_t i = 0; i < m_colortrack1a.get_size(); i++)
      {
         ColorTrack1 & ct1 = m_colortrack1a[i];
         ct1.m_rndgrowVelocity.Step();
         TrackDirection001(
            ct1.m_dDirection,
            ct1.m_dDirectionAddUp,
            ct1.m_rndgrowDirectionLatency);
         ct1.m_dCos = ::cos(ct1.m_dDirection * M_PI / 180.0);
         ct1.m_dSin = ::sin(ct1.m_dDirection * M_PI / 180.0);
         ct1.m_ptColorTrack.x += abs(ct1.m_rndgrowVelocity.i) * ct1.m_dCos;
         ct1.m_ptColorTrack.y += abs(ct1.m_rndgrowVelocity.i) * ct1.m_dSin;
         Constraint001(
            ct1.m_ptColorTrack,
            rcTrackBox,
            rcTrackBox2,
            ct1.m_dDirection);
         ct1.m_dSize = rand() * 5 / RAND_MAX + 1;
      }*/

      StepGrow001(
         m_color,
         m_iGrowColor,
         m_iGrowMax);

      StepGrow001(
         m_color2,
         m_iGrowColor2,
         m_iGrowMax2);

      StepGrow001(
         m_color3,
         m_iGrowColor3,
         m_iGrowMax3);

      StepGrow001(
         m_color4,
         m_iGrowColor4,
         m_iGrowMax4);

      color colorStrong1 = m_color;
      color colorStrong3 = m_color2;
      color colorStrong5 = m_color3;
      color colorStrong7 = m_color4;
      color colorStrong2;
      color colorStrong4;
      color colorStrong6;
      color colorStrong8;

      {
         double dH;
         double dL;
         double dS;
         colorStrong1.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong1.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong1.get_hls(dH, dL, dS);
         dL = 0.3;
         dS = 0.1;
         colorStrong2.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong3.get_hls(dH, dL, dS);
         dL = 0.9;
         dS = 0.7;
         colorStrong3.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong3.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.9;
         colorStrong4.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong5.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong5.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong5.get_hls(dH, dL, dS);
         dL = 0.5;
         dS = 0.9;
         colorStrong6.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong7.get_hls(dH, dL, dS);
         dL = 0.7;
         dS = 0.8;
         colorStrong7.set_hls(dH, dL, dS);
      }
      {
         double dH;
         double dL;
         double dS;
         colorStrong7.get_hls(dH, dL, dS);
         dL = 0.5;
         dS = 0.9;
         colorStrong8.set_hls(dH, dL, dS);
      }


//            ARGB(255, rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX,
//            rand() * 255 / RAND_MAX);

//         BYTE bA = 200;


#ifdef WINDOWSEX
      GdiFlush();
#endif

      //double dmin = min(cx, cy);
      //double dmax = max(cx, cy);abs

      if(m_bGrowColor0)
      {
         //pdib1->get_graphics()->FillSolidRect(0, 0, cx1, cy1, colorStrong1.get_rgb() | (255 << 24));
      }

//         int32_t c1 = rand() * 3 / RAND_MAX;
//         int32_t c2 = rand() * 3 / RAND_MAX;
//         int32_t c4 = rand() * 10 / RAND_MAX + 1;


      m_rndgrowAngleOffsetLatency.Step();
      if(m_rndgrowAngleOffsetLatency.i == 1)
      {
         m_dAngleOffsetAddUp = (5.1 * rand() / RAND_MAX) - 2.05;
      }
      double dOffset3 = (1.0 * rand() / RAND_MAX) - .5;
      m_dAngleOffset += min(10.0, min(2.0, m_dAngleOffsetAddUp + dOffset3));
      m_dAngleOffset = fmod(m_dAngleOffset, 360.0);

//         double dAngleOffset = m_dAngleOffset;
      double dAngle;
      if(m_rndgrowAngleOffsetLatency.i > 50)
      {
         //dAngle = 10.111 + dAngleOffset;
         dAngle = m_dAngleOffset;
      }
      else
      {

         //dAngle = -10.111 - dAngleOffset;
         dAngle = -m_dAngleOffset;
      }
      //pdib2->Rotate034(pdib1, dAngle, 1.09);
      //pdib2->rotate(pdib1, dAngle, 1.009);
      //pdib2->Paste(pdib1);
      //imaging.color_blend(pdib2->get_graphics(), cxm - s1, cym - s2, s3, s4, m_color.get_rgb(), bA);


      // top
   /*   imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 / 2, 1, colorStrong1.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, 0, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);
      // left
      imaging.color_blend(pdib1->get_graphics(), 0, 0, 1, cy1 / 2, colorStrong3.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 / 2, 1, cy1 / 2 - 1, colorStrong4.get_rgb(), bA);
      // bottom
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 - 1, cx1 / 2, 1, colorStrong5.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, cy1 - 1, cx1 / 2 - 1, 1, colorStrong6.get_rgb(), bA);
      // right
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, 0, 1, cy1 / 2, colorStrong7.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, cy1 / 2, 1, cy1 / 2 - 1, colorStrong8.get_rgb(), bA);*/

      // top1
      ::draw2d::pen_sp pen1(allocer());
      pen1->create_solid(1, colorStrong1.get_rgb() | (255 << 24));
      pdib1->get_graphics()->SelectObject(pen1);
      int32_t marginx = cx1 / 12;
      int32_t marginy = cy1 * 5 / 11;
      int32_t w = marginx * 2;
      pdib1->get_graphics()->MoveTo(marginx, marginy);

      int32_t imax = cx1 - marginx;
      int32_t jmax = cx1 / 2;
      int32_t rmax = jmax * RAND_MAX;
      int32_t rhalf = RAND_MAX / 2;
      int32_t j = 0;
      int32_t r1 = 0;
      int32_t r2 = 0;
      int32_t i;
      for(i = marginx; i < jmax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 3 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 5 / rmax;
         }
         pdib1->get_graphics()->LineTo(i, r1 + r2 + marginy + ((rand() - rhalf) * j * w / rmax));
         j++;
      }
      for(; i < imax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 3 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 5 / rmax;
         }
         pdib1->get_graphics()->LineTo(i, r1 + r2 + marginy + ((rand() - rhalf) * j * w / rmax));
         j--;
      }

      pdib1->get_graphics()->MoveTo(marginx, cy1 - marginy);

      for(i = marginx; i < jmax; i++)
      {
         pdib1->get_graphics()->LineTo(i, cy1 - marginy + ((rand() - rhalf) * j * w / rmax));
         j++;
      }
      for(; i < imax; i++)
      {
         pdib1->get_graphics()->LineTo(i, cy1 - marginy + ((rand() - rhalf) * j * w / rmax));
         j--;
      }

      pdib1->get_graphics()->MoveTo(marginx, marginy);

      // vertical
   //   imax = cy1 - margin;
      jmax = cy1 / 2;
      rmax = jmax * RAND_MAX;
      rhalf = RAND_MAX / 2;
      j = 0;
      r1 = 0;
      r2 = 0;
     /* for(i = margin; i < jmax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 3 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 5 / rmax;
         }
         pdib1->get_graphics()->LineTo(r1 + r2 + marginy + ((rand() - rhalf) * j * w / rmax), i);
         j++;
      }
      for(; i < imax; i++)
      {
         if((i % 5) == 0)
         {
            r1 = (rand() - rhalf) * j * 3 / rmax;
         }
         if((i % 7) == 0)
         {
            r2 = (rand() - rhalf) * j * 5 / rmax;
         }
         pdib1->get_graphics()->LineTo(r1 + r2 + marginy + ((rand() - rhalf) * j * w / rmax), i);
         j--;
      }*/

   /*   pdib1->get_graphics()->MoveTo(cx1 - margin, margin);

      for(i = margin; i < jmax; i++)
      {
         pdib1->get_graphics()->LineTo(cx1 - margin + ((rand() - rhalf) * j * w / rmax), i);
         j++;
      }
      for(; i < imax; i++)
      {
         pdib1->get_graphics()->LineTo(cx1 - margin + ((rand() - rhalf) * j * w / rmax), i);
         j--;
      }*/

      //imaging.color_blend(pdib1->get_graphics(), 0, cy1 * 2 / 3, cx1 / 2, 1, , bA);
      //imaging.color_blend(pdib1->get_graphics(), cx1 / 2, cy1 * 2 / 3, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);

      // top
      /*imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 / 2, 1, colorStrong2.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, 0, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);
      // left
      imaging.color_blend(pdib1->get_graphics(), 0, 0, 1, cy1 / 2, colorStrong2.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 / 2, 1, cy1 / 2 - 1, colorStrong2.get_rgb(), bA);
      // bottom
      imaging.color_blend(pdib1->get_graphics(), 0, cy1 - 1, cx1 / 2, 1, colorStrong2.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 / 2, cy1 - 1, cx1 / 2 - 1, 1, colorStrong2.get_rgb(), bA);
      // right
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, 0, 1, cy1 / 2, colorStrong2.get_rgb(), bA);
      imaging.color_blend(pdib1->get_graphics(), cx1 - 1, cy1 / 2, 1, cy1 / 2 - 1, colorStrong2.get_rgb(), bA);*/

      imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1, cy1, ARGB(255, 0, 0, 0), 10);

   /*   {
         ::draw2d::pen_sp pen1(get_app(), PS_SOLID, 0, colorStrong1.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush1(get_app(), colorStrong1.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen2(get_app(), PS_SOLID, 0, colorStrong2.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush2(get_app(), colorStrong2.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen3(get_app(), PS_SOLID, 0, colorStrong3.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush3(get_app(), colorStrong3.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen4(get_app(), PS_SOLID, 0, colorStrong4.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush4(get_app(), colorStrong4.get_rgb() | (255 << 24));
         ::draw2d::pen_sp pen5(get_app(), PS_SOLID, 0, colorStrong5.get_rgb() | (255 << 24));
         ::draw2d::brush_sp brush5(get_app(), colorStrong5.get_rgb() | (255 << 24));
         for(int32_t i = 0; i < m_colortrack1a.get_size(); i++)
         {
            ColorTrack1 & ct1 = m_colortrack1a[i];
            int32_t x1 = ct1.m_ptColorTrack.x;
            int32_t y1 = ct1.m_ptColorTrack.y;
            int32_t d = ct1.m_dSize;
            switch(i % 5)
            {
            case 0:
               {
                  pdib1->get_graphics()->SelectObject(brush1);
                  pdib1->get_graphics()->SelectObject(pen1);
               }
               break;
            case 1:
               {
                  pdib1->get_graphics()->SelectObject(brush2);
                  pdib1->get_graphics()->SelectObject(pen2);
               }
               break;
            case 2:
               {
                  pdib1->get_graphics()->SelectObject(brush3);
                  pdib1->get_graphics()->SelectObject(pen3);
               }
            case 3:
               {
                  pdib1->get_graphics()->SelectObject(brush4);
                  pdib1->get_graphics()->SelectObject(pen4);
               }
            case 4:
               {
                  pdib1->get_graphics()->SelectObject(brush5);
                  pdib1->get_graphics()->SelectObject(pen5);
               }
               break;
            }
            pdib1->get_graphics()->Rectangle(x1, y1, x1 + d, y1 + d);
         }

      }*/



      /*imaging.bitmap_blend(
         pdib1->get_graphics(),
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0,
         50);*/

      pdib2->channel_multiply(::visual::rgba::channel_alpha, 127.0 / 255.0);

      pdib1->get_graphics()->BitBlt(
         0, 0, cx1, cy1,
         pdib2->get_graphics(),
         0, 0, SRCCOPY);

      pdibBack->stretch_dib(pdib1);

      recta.add(rectClient);
   }

} // namespace backview





