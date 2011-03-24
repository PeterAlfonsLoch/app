#include "StdAfx.h"
#include <math.h>


#define M_PI 3.14159265358979323846


namespace gcom
{
   namespace backview
   {

      VisualEffect::VisualEffect(Main & main) :
         ::ca::ca(main.get_app()),
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
//         class imaging & imaging = System.imaging();

         Graphics & graphics = main.GetGraphics();

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();
            
         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
         
         CSingleLock sl1Back(&graphics.m_mutex1Back, FALSE);
         CSingleLock sl2Buffer(&graphics.m_mutex2Buffer, FALSE);
         ::ca::graphics & dcBack = graphics.GetBackDC();
         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
//         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();
//         ::ca::graphics & dcTransfer = graphics.GetFrame1DC();
         
         HelperGetMain().DeferCheckLayout();


         sl1Back.Lock();
         sl2Buffer.Lock();
         dcBack.SelectClipRgn(NULL);
         dcBuffer.SelectClipRgn(NULL);

         int iVisual;

         //transitioneffect.m_iVisual = VisualEffectRotateEx5;
         iVisual = transitioneffect.m_iVisual;
      //      iVisual = VisualEffectRotateEx5;
         switch(iVisual)
         {
         case VisualEffectRotateBlend:
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
         case VisualEffectRotateEx4:
            RenderRotateEx4(recta);
            break;
         case VisualEffectRain1:
            RenderRain1(recta);
            break;
         case VisualEffectRotateEx5:
            RenderRotateEx5(recta);
            break;
         case VisualEffectRotateEx6:
            RenderRotateEx5(recta);
            break;
         case VisualEffectRotateEx7:
            RenderRotateEx7(recta);
            break;
         case VisualEffectRotateEx8:
            RenderRotateEx8(recta);
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
         case VisualEffectPixelExplosion:
            RenderPixelExplosion(recta);
            break;
         case VisualEffectPixelExplosion2:
            RenderPixelExplosion2(recta);
            break;
         case VisualEffectAlphaPixelExplosion:
            RenderAlphaPixelExplosion(recta);
            break;
         default:
            ASSERT(FALSE);
            break;
         }

         CSingleLock sl(&graphics.m_mutex4Transfer, TRUE);
         ::ca::dib * pdibBack = graphics.GetDib(_graphics::DibBack);
         ::ca::dib * pdibTransfer = graphics.GetDib(_graphics::DibTransfer);
         
         pdibTransfer->stretch_dib(pdibBack);
      }

      void VisualEffect::RenderRotateBlend(rect_array & recta)
      {
         Main & main = HelperGetMain();

         TransitionEffect & transitioneffect = main.GetTransitionEffect();


         rect rectClient = tool1.rectClient;
//         int cx = rectClient.width();
//         int cy = rectClient.height();
//         class imaging & imaging = System.imaging();
            
         Graphics & graphics = main.GetGraphics();

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();
            
         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
            
//         ::ca::graphics & dcBack = graphics.GetBackDC();
//         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
//         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();
            

         ::ca::dib * pdibBack = graphics.GetDib(_graphics::DibBack);
         ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
         ::ca::dib * pdib2 = graphics.GetDib(_graphics::DibTemp2);
         ::ca::dib * pdib3 = graphics.GetDib(_graphics::DibTemp3);
         ::ca::dib * pdibBuffer = graphics.GetDib(_graphics::DibBuffer);
//         ::ca::dib * pdibTransfer = graphics.GetDib(_graphics::DibTransfer);

         int cx1 = pdib1->width();
         int cy1 = pdib1->height();
//         int cxm = cx1 / 2;
//         int cym = cy1 / 2;

         if(transitioneffect.m_tool001.m_iStep == 1)
         {
            pdib2->create(cx1, cy1);
            pdib3->create(cx1, cy1);
         }


//         int s1 = rand() * 1 / RAND_MAX + 1;
//         int s2 = rand() * 1 / RAND_MAX + 1;
//         int s3 = rand() * 2 / RAND_MAX + 1;
//         int s4 = rand() * 2 / RAND_MAX + 1;



         
            

            
            RGB(rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX);
                                 
//         BYTE bA = 50;


         GdiFlush();

         //double dmin = min(cx, cy);
         //double dmax = max(cx, cy);abs

         
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

         BLENDFUNCTION bf;

         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 10;
      //   bf.AlphaFormat = AC_SRC_ALPHA;
         bf.AlphaFormat = 0;

         pdib1->get_graphics()->alpha_blend(
            0, 0, cx1, cy1,
            pdib2->get_graphics(),
            0, 0, cx1, cy1,
            bf);


         pdibBack->stretch_dib(pdib1);

         //dcBack.FillSolidRect(0, 0, cx, cy, RGB(0, 0, 0));
         //dcBack.FillSolidRect(100, 100, cx, cy, RGB(255, 255, 255));

         recta.add(rectClient);
      }

      void VisualEffect::RenderNPRotateBlend(rect_array & recta)
      {
         Main & main = HelperGetMain();

         TransitionEffect & transitioneffect = main.GetTransitionEffect();


         rect rectClient = tool1.rectClient;
         tool1.cx = rectClient.width();
         tool1.cy = rectClient.height();
         class imaging & imaging = System.imaging();
            
         Graphics & graphics = main.GetGraphics();

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();
            
         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
            
//         ::ca::graphics & dcBack = graphics.GetBackDC();
//         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
//         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();
            

         ::ca::dib * pdibBack = graphics.GetDib(_graphics::DibBack);
         ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
         ::ca::dib * pdib2 = graphics.GetDib(_graphics::DibTemp2);
         ::ca::dib * pdib3 = graphics.GetDib(_graphics::DibTemp3);
//         ::ca::dib * pdibBuffer = graphics.GetDib(_graphics::DibBuffer);

         

         //pdib1->Vortex(transitioneffect.m_tool001.m_iStep);

         int cx1 = pdib1->width();
         int cy1 = pdib1->height();
         int cxm = cx1 / 2;
         int cym = cy1 / 2;

         if(transitioneffect.m_tool001.m_iStep == 1)
         {
            pdib2->create(cx1, cy1);
            pdib3->create(cx1, cy1);
         }


         int s1 = rand() * 1 / RAND_MAX + 1;
         int s2 = rand() * 1 / RAND_MAX + 1;
         int s3 = rand() * 2 / RAND_MAX + 1;
         int s4 = rand() * 2 / RAND_MAX + 1;

         StepGrow001(
            m_color,
            m_iGrowColor,
            m_iGrowMax);

         
            

            
            RGB(rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX);
                                 
         BYTE bA = 50;


         GdiFlush();

         //double dmin = min(cx, cy);
         //double dmax = max(cx, cy);abs

         
        // ::ca::graphics_sp pdib3->get_graphics();
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

         BLENDFUNCTION bf;

         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 10;
      //   bf.AlphaFormat = AC_SRC_ALPHA;
         bf.AlphaFormat = 0;

         pdib1->get_graphics()->alpha_blend(
            0, 0, cx1, cy1,
            pdib2->get_graphics(),
            0, 0, cx1, cy1,
            bf);

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
         class imaging & imaging = System.imaging();
            
         Graphics & graphics = main.GetGraphics();

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();
            
         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
            
//         ::ca::graphics & dcBack = graphics.GetBackDC();
//         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
//         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();
            

         ::ca::dib * pdibBack = graphics.GetDib(_graphics::DibBack);
         ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
         ::ca::dib * pdib2 = graphics.GetDib(_graphics::DibTemp2);
         ::ca::dib * pdib3 = graphics.GetDib(_graphics::DibTemp3);
//         ::ca::dib * pdibBuffer = graphics.GetDib(_graphics::DibBuffer);

         


         //drawdib.draw(pdibBuffer, spgraphics, 0, 0, cx, cy, 0);

         //dcBack.BitBlt(0, 0, cx, cy, &dcBuffer, 0, 0, SRCCOPY);
         //pdib1->Vortex(transitioneffect.m_tool001.m_iStep);

         int cx1 = pdib1->width();
         int cy1 = pdib1->height();
         int cxm = cx1 / 2;
         int cym = cy1 / 2;

         if(transitioneffect.m_tool001.m_iStep == 1)
         {
            pdib2->create(cx1, cy1);
            pdib3->create(cx1, cy1);
         }


         int s1 = rand() * 1 / RAND_MAX + 1;
         int s2 = rand() * 1 / RAND_MAX + 1;
         int s3 = rand() * 2 / RAND_MAX + 1;
         int s4 = rand() * 2 / RAND_MAX + 1;

         int c1 = rand() * (cx1 - 10) / RAND_MAX + 1;
         int c2 = rand() * (cy1 - 10) / RAND_MAX + 1;
         int c3 = rand() * 10 / RAND_MAX + 1;
         int c4 = rand() * 10 / RAND_MAX + 1;

         StepGrow001(
            m_color,
            m_iGrowColor,
            m_iGrowMax);

         
            

            
            RGB(rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX);
                                 
         BYTE bA = 50;


         GdiFlush();

         //double dmin = min(cx, cy);
         //double dmax = max(cx, cy);abs

         
        // ::ca::graphics_sp pdib3->get_graphics();
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

         BLENDFUNCTION bf;

         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 10;
      //   bf.AlphaFormat = AC_SRC_ALPHA;
         bf.AlphaFormat = 0;

         pdib1->get_graphics()->alpha_blend(
            0, 0, cx1, cy1,
            pdib2->get_graphics(),
            0, 0, cx1, cy1,
            bf);

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
         class imaging & imaging = System.imaging();
            
         Graphics & graphics = main.GetGraphics();

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();
            
         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
            
//         ::ca::graphics & dcBack = graphics.GetBackDC();
//         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
//         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();
            

         ::ca::dib * pdibBack = graphics.GetDib(_graphics::DibBack);
         ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
         ::ca::dib * pdib2 = graphics.GetDib(_graphics::DibTemp2);
         ::ca::dib * pdib3 = graphics.GetDib(_graphics::DibTemp3);
//         ::ca::dib * pdibBuffer = graphics.GetDib(_graphics::DibBuffer);

         
         //drawdib.draw(pdibBuffer, spgraphics, 0, 0, cx, cy, 0);

         //dcBack.BitBlt(0, 0, cx, cy, &dcBuffer, 0, 0, SRCCOPY);
         //pdib1->Vortex(transitioneffect.m_tool001.m_iStep);

         int cx1 = pdib1->width();
         int cy1 = pdib1->height();
         int cxm = cx1 / 2;
         int cym = cy1 / 2;

         if(transitioneffect.m_tool001.m_iStep == 1)
         {
            pdib2->create(cx1, cy1);
            pdib3->create(cx1, cy1);
         }

         int s1 = rand() * 1 / RAND_MAX + 1;
         int s2 = rand() * 1 / RAND_MAX + 1;
         int s3 = rand() * 2 / RAND_MAX + 1;
         int s4 = rand() * 2 / RAND_MAX + 1;

         m_rndgrowVelocity.Step();
         if(m_rndgrowDirectionLatency.Step())
         {
            m_dDirection = ((int) m_dDirection % 360);
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
      //      m_dDirection += 180 + ((int) m_dDirection % 360);
            m_dDirection = -m_dDirection;
         }
         else if(m_ptColorTrack.y > cy1 - 10)
         {
        //    m_dDirection += 180 + ((int) m_dDirection % 360);
            m_dDirection = -m_dDirection;
         }
         else if(m_ptColorTrack.x < 0)
         {
          //  m_dDirection += 180 + ((int) m_dDirection % 360);
            m_dDirection = -m_dDirection;
         }
         else if(m_ptColorTrack.y < 0)
         {
            //m_dDirection += 180 + ((int) m_dDirection % 360);
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


            
            RGB(rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX);
                                 
         BYTE bA = 50;


         GdiFlush();

         //double dmin = min(cx, cy);
         //double dmax = max(cx, cy);abs

        // ::ca::graphics_sp pdib3->get_graphics();
         //pdib3->get_graphics()->CreateCompatibleDC(NULL);
         //pdib3->get_graphics()->SelectObject(pdib3->m_hbitmap);

      //   pdib3->stretch_dib(pdibBuffer);

      //   pdib3->Paste(pdib1);

//         int c1 = rand() * 3 / RAND_MAX;
//         int c2 = rand() * 3 / RAND_MAX;
         int c3 = rand() * 10 / RAND_MAX + 1;
//         int c4 = rand() * 10 / RAND_MAX + 1;


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
            int x1 = m_ptColorTrack.x;
            int y1 = m_ptColorTrack.y;
            int x2 = cx1 - x1;
            int y2 = cy1 - y1;
            ::ca::pen_sp pen(get_app());
            pen->construct(PS_SOLID, 0, m_color.get_rgb());
            ::ca::brush_sp brush(get_app(), m_color.get_rgb());
            pdib1->get_graphics()->SelectObject(brush);
            pdib1->get_graphics()->SelectObject(pen);
            //imaging.color_blend(pdib1->get_graphics(), x, y, c3, c4, m_color.get_rgb(), bA); 
            //imaging.color_blend(pdib1->get_graphics(), cx1 - x, cy1 - y, c3, c4, m_color.get_rgb(), bA); 
            pdib1->get_graphics()->Ellipse(x1, y1, x1 + c3, y1 + c3); 
            pdib1->get_graphics()->Ellipse(x2 - c3, y2 - c3, x2, y2); 
         }

         /*imaging.bitmap_blend(
            pdib1->get_graphics(),
            0, 0, cx1, cy1,
            pdib2->get_graphics(),
            0, 0,
            50);*/

         BLENDFUNCTION bf;

         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 10;
      //   bf.AlphaFormat = AC_SRC_ALPHA;
         bf.AlphaFormat = 0;

         pdib1->get_graphics()->alpha_blend(
            0, 0, cx1, cy1,
            pdib2->get_graphics(),
            0, 0, cx1, cy1,
            bf);

         pdibBack->stretch_dib(pdib1);

         recta.add(rectClient);
      }


      void VisualEffect::InitialRender()
      {
         tool1.page = 0;
            Main & main = HelperGetMain();
            
         Interface & iface = main.GetInterface();

         TransitionEffect & transitioneffect = main.GetTransitionEffect();

         rect rectClient;
         iface.BackViewGetClientRect(rectClient);
         tool1.rectClient = rectClient;
         
         int cx = rectClient.width();
         int cy = rectClient.height();
//         class imaging & imaging = System.imaging();
         
         Graphics & graphics = main.GetGraphics();

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();


         
         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
         
         CSingleLock sl1Back(&graphics.m_mutex1Back, FALSE);
         CSingleLock sl2Buffer(&graphics.m_mutex2Buffer, FALSE);
         ::ca::graphics & dcBack = graphics.GetBackDC();
         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
//         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();
         
         sl1Back.Lock();
         sl2Buffer.Lock();
         dcBack.SelectClipRgn(NULL);
         dcBuffer.SelectClipRgn(NULL);

         dcBack.BitBlt(0, 0, cx, cy, &dcBuffer, 0, 0, SRCCOPY);
         ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
//         ::ca::dib * pdibBuffer = graphics.GetDib(_graphics::DibBuffer);
         ::ca::dib * pdib2 = graphics.GetDib(_graphics::DibTemp2);
//         ::ca::dib * pdibTransfer = graphics.GetDib(_graphics::DibTransfer);


         int cx1 = cx / 4 + 1;
         int cy1 = cy / 4 + 1;

         m_explosion.create(cx1, cy1);
         m_explosion.Reset();

         if(transitioneffect.m_iVisual == VisualEffectRotateEx5)
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

         m_colortrack1a.set_size(12);
         for(int i = 0; i < m_colortrack1a.get_size(); i++)
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

/*         ::ca::graphics & dcTransfer = graphics.GetBackDC();
         pdibTransfer->stretch_dib(pdibBuffer);
         if(main.GetWndInterface() == NULL)
            return;
         main.GetWndInterface()->BackViewFeedback(pdib2->get_graphics());
         pdib1->stretch_dib(pdib2);*/

         m_dAngle = 0.0;
      }

      int VisualEffect::GetEffectCount()
      {
         return (int) VisualEffectEnd;
      }

      void VisualEffect::StepGrow001(
            color & color, 
            int & iGrowColor,
            int & iGrowMax)
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
            int & iGrowColor,
            int & iGrowMax)
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
            int & iGrowColor,
            int & iGrowMax,
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
         class imaging & imaging = System.imaging();
            
         Graphics & graphics = main.GetGraphics();

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();
            
         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
            
//         ::ca::graphics & dcBack = graphics.GetBackDC();
//         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
//         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();

         ::ca::dib * pdibBack = graphics.GetDib(_graphics::DibBack);
         ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
         ::ca::dib * pdib2 = graphics.GetDib(_graphics::DibTemp2);
         ::ca::dib * pdib3 = graphics.GetDib(_graphics::DibTemp3);
//         ::ca::dib * pdibBuffer = graphics.GetDib(_graphics::DibBuffer);

         //drawdib.draw(pdibBuffer, spgraphics, 0, 0, cx, cy, 0);

         //dcBack.BitBlt(0, 0, cx, cy, &dcBuffer, 0, 0, SRCCOPY);
         //pdib1->Vortex(transitioneffect.m_tool001.m_iStep);

         int cx1 = pdib1->width();
         int cy1 = pdib1->height();
         int cxm = cx1 / 2;
         int cym = cy1 / 2;

         if(transitioneffect.m_tool001.m_iStep == 1)
         {
            pdib2->create(cx1, cy1);
            pdib3->create(cx1, cy1);
         }

         int s1 = rand() * 1 / RAND_MAX + 1;
         int s2 = rand() * 1 / RAND_MAX + 1;
         int s3 = rand() * 2 / RAND_MAX + 1;
         int s4 = rand() * 2 / RAND_MAX + 1;

         m_rndgrowVelocity.Step();
         if(m_rndgrowDirectionLatency.Step())
         {
            m_dDirection = ((int) m_dDirection % 360);
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
            m_dDirection += 180 + ((int) m_dDirection % 360);
         }
         else if(m_ptColorTrack.y > cy1 - 10)
         {
            m_dDirection += 180 + ((int) m_dDirection % 360);
         }
         else if(m_ptColorTrack.x < 0)
         {
            m_dDirection += 180 + ((int) m_dDirection % 360);
         }
         else if(m_ptColorTrack.y < 0)
         {
            m_dDirection += 180 + ((int) m_dDirection % 360);
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


            
            RGB(rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX);
                                 
         BYTE bA = 200;


         GdiFlush();

         //double dmin = min(cx, cy);
         //double dmax = max(cx, cy);abs

        // ::ca::graphics_sp pdib3->get_graphics();
         //pdib3->get_graphics()->CreateCompatibleDC(NULL);
         //pdib3->get_graphics()->SelectObject(pdib3->m_hbitmap);

      //   pdib3->stretch_dib(pdibBuffer);

      //   pdib3->Paste(pdib1);

//         int c1 = rand() * 3 / RAND_MAX;
//         int c2 = rand() * 3 / RAND_MAX;
         int c3 = rand() * 10 / RAND_MAX + 1;
//         int c4 = rand() * 10 / RAND_MAX + 1;


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
            int d = c3;
            int r = d / 2;
            int x1 = m_ptColorTrack.x - r;
            int y1 = m_ptColorTrack.y - r;
            int x2 = cx1 - x1 - r;
            int y2 = cy1 - y1 - r;
            ::ca::pen_sp pen(get_app());
            pen->construct(PS_SOLID, 0, colorStrong.get_rgb());
            ::ca::brush_sp brush(get_app());
            brush->construct(colorStrong.get_rgb());
            pdib2->get_graphics()->SelectObject(brush);
            pdib2->get_graphics()->SelectObject(pen);
            //imaging.color_blend(pdib1->get_graphics(), x, y, c3, c4, m_color.get_rgb(), bA); 
            //imaging.color_blend(pdib1->get_graphics(), cx1 - x, cy1 - y, c3, c4, m_color.get_rgb(), bA); 
            pdib2->get_graphics()->Ellipse(x1, y1, x1 + d, y1 + d); 
            pdib2->get_graphics()->Ellipse(x2 - d, y1, x2, y1 + d); 
            pdib2->get_graphics()->Ellipse(x1, y2 - d, x1 + d, y2); 
            pdib2->get_graphics()->Ellipse(x2 - d, y2 - d, x2, y2); 
         }

         /*imaging.bitmap_blend(
            pdib1->get_graphics(),
            0, 0, cx1, cy1,
            pdib2->get_graphics(),
            0, 0,
            50);*/

         BLENDFUNCTION bf;

         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 235;
      //   bf.AlphaFormat = AC_SRC_ALPHA;
         bf.AlphaFormat = 0;

         pdib1->get_graphics()->alpha_blend(
            0, 0, cx1, cy1,
            pdib2->get_graphics(),
            0, 0, cx1, cy1,
            bf);

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
            ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
            m_color.set_rgb(pdib1->GetPixel(
               pdib1->width() / 2,
               pdib1->height() / 2));
         }


            
         rect rectClient = tool1.rectClient;
         tool1.cx = rectClient.width();
         tool1.cy = rectClient.height();
//         class imaging & imaging = System.imaging();
            

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();
            
         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
            
//         ::ca::graphics & dcBack = graphics.GetBackDC();
//         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
//         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();

         ::ca::dib * pdibBack = graphics.GetDib(_graphics::DibBack);
         ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
         ::ca::dib * pdib2 = graphics.GetDib(_graphics::DibTemp2);
         ::ca::dib * pdib3 = graphics.GetDib(_graphics::DibTemp3);
//         ::ca::dib * pdibBuffer = graphics.GetDib(_graphics::DibBuffer);

         //drawdib.draw(pdibBuffer, spgraphics, 0, 0, cx, cy, 0);

         //dcBack.BitBlt(0, 0, cx, cy, &dcBuffer, 0, 0, SRCCOPY);
         //pdib1->Vortex(transitioneffect.m_tool001.m_iStep);

         int cx1 = pdib1->width();
         int cy1 = pdib1->height();
//         int cxm = cx1 / 2;
//         int cym = cy1 / 2;

         if(transitioneffect.m_tool001.m_iStep == 1)
         {
            pdib2->create(cx1, cy1);
            pdib3->create(cx1, cy1);
         }


//         int s1 = rand() * 1 / RAND_MAX + 1;
//         int s2 = rand() * 1 / RAND_MAX + 1;
//         int s3 = rand() * 2 / RAND_MAX + 1;
//         int s4 = rand() * 2 / RAND_MAX + 1;

         rect rcTrackBox;

         rcTrackBox.left   = cx1 * 4 / 9;
         rcTrackBox.top    = cy1 * 4 / 9;
         rcTrackBox.right  = cx1 - rcTrackBox.left;
         rcTrackBox.bottom = cy1 - rcTrackBox.top;

         for(int i = 0; i < m_colortrack1a.get_size(); i++)
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


            
            RGB(rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX);
                                 
//         BYTE bA = 200;


         GdiFlush();

         //double dmin = min(cx, cy);
         //double dmax = max(cx, cy);abs

        // ::ca::graphics_sp pdib3->get_graphics();
         //pdib3->get_graphics()->CreateCompatibleDC(NULL);
         //pdib3->get_graphics()->SelectObject(pdib3->m_hbitmap);

      //   pdib3->stretch_dib(pdibBuffer);

      //   pdib3->Paste(pdib1);

//         int c1 = rand() * 3 / RAND_MAX;
//         int c2 = rand() * 3 / RAND_MAX;
//         int c4 = rand() * 10 / RAND_MAX + 1;


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
            ::ca::pen_sp pen1(get_app());
            pen1->construct(PS_SOLID, 0, colorStrong1.get_rgb());
            ::ca::brush_sp brush1(get_app(), colorStrong1.get_rgb());
            ::ca::pen_sp pen2(get_app());
            pen2->construct(PS_SOLID, 0, colorStrong2.get_rgb());
            ::ca::brush_sp brush2(get_app(), colorStrong2.get_rgb());
            ::ca::pen_sp pen3(get_app());
            pen3->construct(PS_SOLID, 0, colorStrong3.get_rgb());
            ::ca::brush_sp brush3(get_app(), colorStrong3.get_rgb());
            ::ca::pen_sp pen4(get_app());
            pen4->construct(PS_SOLID, 0, colorStrong4.get_rgb());
            ::ca::brush_sp brush4(get_app(), colorStrong4.get_rgb());
            ::ca::pen_sp pen5(get_app());
            pen5->construct(PS_SOLID, 0, colorStrong5.get_rgb());
            ::ca::brush_sp brush5(get_app(), colorStrong5.get_rgb());
            for(int i = 0; i < m_colortrack1a.get_size(); i++)
            {
               ColorTrack1 & ct1 = m_colortrack1a[i];
               int x1 = ct1.m_ptColorTrack.x;
               int y1 = ct1.m_ptColorTrack.y;
               int d = (int) ct1.m_dSize;
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

         BLENDFUNCTION bf;

         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 205;
      //   bf.AlphaFormat = AC_SRC_ALPHA;
         bf.AlphaFormat = 0;

         pdib1->get_graphics()->alpha_blend(
            0, 0, cx1, cy1,
            pdib2->get_graphics(),
            0, 0, cx1, cy1,
            bf);

         pdibBack->stretch_dib(pdib1);

         recta.add(rectClient);
      }

      void VisualEffect::Constraint001(point & pt, LPCRECT lpcrect, double & direction)
      {
         if(pt.x > lpcrect->right)
         {
            direction  += 180 + ((int) direction  % 360);
         }
         else if(pt.y > lpcrect->bottom)
         {
            direction  += 180 + ((int) direction  % 360);
         }
         else if(pt.x < lpcrect->left)
         {
            direction  += 180 + ((int) direction  % 360);
         }
         else if(pt.y < lpcrect->top)
         {
            direction  += 180 + ((int) direction  % 360);
         }

         if(pt.x > lpcrect->right)
         {
            pt.x = lpcrect->right;
         }
         else if(pt.x < lpcrect->left)
         {
            pt.x = lpcrect->left;
         }

         if(pt.y > lpcrect->bottom)
         {
            pt.y = lpcrect->bottom;
         }
         else if(pt.y < lpcrect->top)
         {
            pt.y = lpcrect->top;
         }

      }
      void VisualEffect::TrackDirection001(double &direction, double & directionAddUp, RandomGrow & randomgrow)
      {
         if(randomgrow.Step())
         {
            direction = ((int) direction % 360);
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
            ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
            m_color.set_rgb(pdib1->GetPixel(
               pdib1->width() / 2,
               pdib1->height() / 2));
         }


            
         rect rectClient = tool1.rectClient;
         tool1.cx = rectClient.width();
         tool1.cy = rectClient.height();
         class imaging & imaging = System.imaging();
            

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();
            
         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
            
//         ::ca::graphics & dcBack = graphics.GetBackDC();
//         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
//         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();

         ::ca::dib * pdibBack = graphics.GetDib(_graphics::DibBack);
         ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
         ::ca::dib * pdib2 = graphics.GetDib(_graphics::DibTemp2);
         ::ca::dib * pdib3 = graphics.GetDib(_graphics::DibTemp3);
//         ::ca::dib * pdibBuffer = graphics.GetDib(_graphics::DibBuffer);

         //drawdib.draw(pdibBuffer, spgraphics, 0, 0, cx, cy, 0);

         //dcBack.BitBlt(0, 0, cx, cy, &dcBuffer, 0, 0, SRCCOPY);
         //pdib1->Vortex(transitioneffect.m_tool001.m_iStep);

         int cx1 = pdib1->width();
         int cy1 = pdib1->height();
//         int cxm = cx1 / 2;
//         int cym = cy1 / 2;

         if(transitioneffect.m_tool001.m_iStep == 1)
         {
            pdib2->create(cx1, cy1);
            pdib3->create(cx1, cy1);
         }


//         int s1 = rand() * 1 / RAND_MAX + 1;
//         int s2 = rand() * 1 / RAND_MAX + 1;
//         int s3 = rand() * 2 / RAND_MAX + 1;
//         int s4 = rand() * 2 / RAND_MAX + 1;

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

         /*for(int i = 0; i < m_colortrack1a.get_size(); i++)
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

            
            RGB(rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX);
                                 
         BYTE bA = 200;


         GdiFlush();

         //double dmin = min(cx, cy);
         //double dmax = max(cx, cy);abs

        // ::ca::graphics_sp pdib3->get_graphics();
         //pdib3->get_graphics()->CreateCompatibleDC(NULL);
         //pdib3->get_graphics()->SelectObject(pdib3->m_hbitmap);

      //   pdib3->stretch_dib(pdibBuffer);

      //   pdib3->Paste(pdib1);

//         int c1 = rand() * 3 / RAND_MAX;
//         int c2 = rand() * 3 / RAND_MAX;
//         int c4 = rand() * 10 / RAND_MAX + 1;


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
            ::ca::pen_sp pen1(get_app(), PS_SOLID, 0, colorStrong1.get_rgb());
            ::ca::brush_sp brush1(get_app(), colorStrong1.get_rgb());
            ::ca::pen_sp pen2(get_app(), PS_SOLID, 0, colorStrong2.get_rgb());
            ::ca::brush_sp brush2(get_app(), colorStrong2.get_rgb());
            ::ca::pen_sp pen3(get_app(), PS_SOLID, 0, colorStrong3.get_rgb());
            ::ca::brush_sp brush3(get_app(), colorStrong3.get_rgb());
            ::ca::pen_sp pen4(get_app(), PS_SOLID, 0, colorStrong4.get_rgb());
            ::ca::brush_sp brush4(get_app(), colorStrong4.get_rgb());
            ::ca::pen_sp pen5(get_app(), PS_SOLID, 0, colorStrong5.get_rgb());
            ::ca::brush_sp brush5(get_app(), colorStrong5.get_rgb());
            for(int i = 0; i < m_colortrack1a.get_size(); i++)
            {
               ColorTrack1 & ct1 = m_colortrack1a[i];
               int x1 = ct1.m_ptColorTrack.x;
               int y1 = ct1.m_ptColorTrack.y;
               int d = ct1.m_dSize;
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

         BLENDFUNCTION bf;

         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 127;
      //   bf.AlphaFormat = AC_SRC_ALPHA;
         bf.AlphaFormat = 0;

         pdib1->get_graphics()->alpha_blend(
            0, 0, cx1, cy1,
            pdib2->get_graphics(),
            0, 0, cx1, cy1,
            bf);

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

            direction  += 180 + ((int) direction  % 360);

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
            direction  += 180 + ((int) direction  % 360);
         }
         else if(pt.y > lpcrectOut->bottom)
         {
            direction  += 180 + ((int) direction  % 360);
         }
         else if(pt.x < lpcrectOut->left)
         {
            direction  += 180 + ((int) direction  % 360);
         }
         else if(pt.y < lpcrectOut->top)
         {
            direction  += 180 + ((int) direction  % 360);
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
            ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
            m_color.set_rgb(pdib1->GetPixel(
               pdib1->width() / 2,
               pdib1->height() / 2));
         }


            
         rect rectClient = tool1.rectClient;
         tool1.cx = rectClient.width();
         tool1.cy = rectClient.height();
         class imaging & imaging = System.imaging();
            

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();
            
         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
            
//         ::ca::graphics & dcBack = graphics.GetBackDC();
//         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
//         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();
            
         ::ca::dib * pdibBack = graphics.GetDib(_graphics::DibBack);
         ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
         ::ca::dib * pdib2 = graphics.GetDib(_graphics::DibTemp2);
         ::ca::dib * pdib3 = graphics.GetDib(_graphics::DibTemp3);
//         ::ca::dib * pdibBuffer = graphics.GetDib(_graphics::DibBuffer);

         //drawdib.draw(pdibBuffer, spgraphics, 0, 0, cx, cy, 0);

         //dcBack.BitBlt(0, 0, cx, cy, &dcBuffer, 0, 0, SRCCOPY);
         //pdib1->Vortex(transitioneffect.m_tool001.m_iStep);

         int cx1 = pdib1->width();
         int cy1 = pdib1->height();
//         int cxm = cx1 / 2;
//         int cym = cy1 / 2;

         if(transitioneffect.m_tool001.m_iStep == 1)
         {
            pdib2->create(cx1, cy1);
            pdib3->create(cx1, cy1);
         }


//         int s1 = rand() * 1 / RAND_MAX + 1;
//         int s2 = rand() * 1 / RAND_MAX + 1;
//         int s3 = rand() * 2 / RAND_MAX + 1;
//         int s4 = rand() * 2 / RAND_MAX + 1;

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

         /*for(int i = 0; i < m_colortrack1a.get_size(); i++)
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

            
            RGB(rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX);
                                 
         BYTE bA = 200;


         GdiFlush();

         //double dmin = min(cx, cy);
         //double dmax = max(cx, cy);abs

         if(m_bGrowColor0)
         {
            //pdib1->get_graphics()->FillSolidRect(0, 0, cx1, cy1, colorStrong1.get_rgb());
         }
         
        // ::ca::graphics_sp pdib3->get_graphics();
         //pdib3->get_graphics()->CreateCompatibleDC(NULL);
         //pdib3->get_graphics()->SelectObject(pdib3->m_hbitmap);

      //   pdib3->stretch_dib(pdibBuffer);

      //   pdib3->Paste(pdib1);

//         int c1 = rand() * 3 / RAND_MAX;
//         int c2 = rand() * 3 / RAND_MAX;
//         int c4 = rand() * 10 / RAND_MAX + 1;


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
         ::ca::pen_sp pen1(get_app());
         pen1->construct(PS_SOLID, 1, colorStrong1.get_rgb());
         pdib1->get_graphics()->SelectObject(pen1);
         int margin = 10;
         int w = margin * 2;
         pdib1->get_graphics()->MoveTo(margin, margin);
         
         int imax = cx1 - margin;
         int jmax = cx1 / 2;
         int rmax = jmax * RAND_MAX;
         int rhalf = RAND_MAX / 2;
         int j = 0;
         int r1 = 0;
         int r2 = 0;
         int i;
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
            int x2 = cx1 / 2;
            int y2 = cy1 / 2;
            int w2 = cx1 / 2 - 1;
            int h2 = cy1 / 2 - 1;

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
            ::ca::pen_sp pen1(get_app(), PS_SOLID, 0, colorStrong1.get_rgb());
            ::ca::brush_sp brush1(get_app(), colorStrong1.get_rgb());
            ::ca::pen_sp pen2(get_app(), PS_SOLID, 0, colorStrong2.get_rgb());
            ::ca::brush_sp brush2(get_app(), colorStrong2.get_rgb());
            ::ca::pen_sp pen3(get_app(), PS_SOLID, 0, colorStrong3.get_rgb());
            ::ca::brush_sp brush3(get_app(), colorStrong3.get_rgb());
            ::ca::pen_sp pen4(get_app(), PS_SOLID, 0, colorStrong4.get_rgb());
            ::ca::brush_sp brush4(get_app(), colorStrong4.get_rgb());
            ::ca::pen_sp pen5(get_app(), PS_SOLID, 0, colorStrong5.get_rgb());
            ::ca::brush_sp brush5(get_app(), colorStrong5.get_rgb());
            for(int i = 0; i < m_colortrack1a.get_size(); i++)
            {
               ColorTrack1 & ct1 = m_colortrack1a[i];
               int x1 = ct1.m_ptColorTrack.x;
               int y1 = ct1.m_ptColorTrack.y;
               int d = ct1.m_dSize;
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

         BLENDFUNCTION bf;

         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 127;
         bf.AlphaFormat = 0;

         pdib1->get_graphics()->alpha_blend(
            0, 0, cx1, cy1,
            pdib2->get_graphics(),
            0, 0, cx1, cy1,
            bf);

         pdibBack->stretch_dib(pdib1);

         recta.add(rectClient);
      }




      void VisualEffect::RenderRain1(rect_array & recta)
      {
         Main & main = HelperGetMain();

         TransitionEffect & transitioneffect = main.GetTransitionEffect();
         Graphics & graphics = main.GetGraphics();

         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
            
//         ::ca::graphics & dcBack = graphics.GetBackDC();
//         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
//         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();

         ::ca::dib * pdibBack = graphics.GetDib(_graphics::DibBack);
         ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
         ::ca::dib * pdib2 = graphics.GetDib(_graphics::DibTemp2);
         ::ca::dib * pdib3 = graphics.GetDib(_graphics::DibTemp3);
         ::ca::dib * pdib4 = graphics.GetDib(_graphics::DibTemp4);
         ::ca::dib * pdibBuffer = graphics.GetDib(_graphics::DibBuffer);
         if(transitioneffect.m_tool001.m_iStep == 1)
         {
            ::ca::dib * pdibFrame1 = graphics.GetDib(_graphics::DibFrame1);
            tool1.dmod = 4.2;
            tool1.dminsize = 0;
            int cx1 = tool1.cx / 4;
            int cy1 = tool1.cy / 4;
            pdib1->create(cx1, cy1);
            pdib2->create(cx1, cy1);
            pdib3->create(cx1, cy1);
            pdib4->create(cx1, cy1);
            tool1.dalpha = 0;
            m_water.create(cx1, cy1);
            pdib1->get_graphics()->SetStretchBltMode(HALFTONE);
            pdib1->stretch_dib(pdibBuffer);
            pdib3->get_graphics()->SetStretchBltMode(HALFTONE);
            pdib3->stretch_dib(pdibFrame1);
         }
         int cx1 = pdib1->width();
         int cy1 = pdib1->height();
            
         
         pdib4->get_graphics()->BitBlt(0, 0, cx1, cy1, pdib3->get_graphics(), 0, 0, SRCCOPY);
         
         System.imaging().bitmap_blend(
            pdib4->get_graphics(),
            null_point(), pdib1->size(),
            pdib1->get_graphics(),
            null_point(),
            (BYTE) max(min(255, tool1.dalpha), 0));

         int iReturnPoint = transitioneffect.m_tool001.m_iStepCount * 5 / 21;

         m_water.to(pdib4->get_data(), pdib2->get_data());

         int mod = max(1, (int) tool1.dmod);
         if((tool1.frame % mod) == 0)
         {
            int x = rand() * cx1 / RAND_MAX;
            int y = rand() * cy1 / RAND_MAX;
            int r = (int) (rand() * min(tool1.dminsize, 60.0) / RAND_MAX + min(tool1.dminsize / 2, 60.0));
            int h = rand() * 100 / RAND_MAX;
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
            ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
            m_color.set_rgb(pdib1->GetPixel(
               pdib1->width() / 2,
               pdib1->height() / 2));
         }
            
         rect rectClient = tool1.rectClient;
         tool1.cx = rectClient.width();
         tool1.cy = rectClient.height();
         class imaging & imaging = System.imaging();
            

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();
            
         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
            
//         ::ca::graphics & dcBack = graphics.GetBackDC();
//         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
//         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();

         ::ca::dib * pdibBack = graphics.GetDib(_graphics::DibBack);
         ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
         ::ca::dib * pdib2 = graphics.GetDib(_graphics::DibTemp2);
         ::ca::dib * pdib3 = graphics.GetDib(_graphics::DibTemp3);
         ::ca::dib * pdib4 = graphics.GetDib(_graphics::DibTemp4);
//         ::ca::dib * pdibBuffer = graphics.GetDib(_graphics::DibBuffer);

         int cx1 = pdib1->width();
         int cy1 = pdib1->height();
//         int cxm = cx1 / 2;
//         int cym = cy1 / 2;

         if(transitioneffect.m_tool001.m_iStep == 1)
         {
            if(m_pointa.get_size() != cx1)
            {
               m_pointa.set_size(cx1);
               m_pointa1.set_size(cx1);
               m_pointa2.set_size(cx1);

               for(int i = 0; i < cx1; i++)
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

         if(transitioneffect.m_iVisual == VisualEffectRotateEx6)
         {
            pdib2->Fill(0, 0, 0, 0);
            pdib3->Fill(0, 0, 0, 0);
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
         
         ::ca::pen_sp pen1(get_app());
         pen1->construct(PS_SOLID, 1, colorStrong1.get_rgb());
         ::ca::pen_sp penWhite(get_app());
         penWhite->construct(PS_SOLID, 3, RGB(205, 205, 205));
         int margin1 = cx1 / 8;
         int margin2 = cy1 / 2;
         int w = cy1 / 3;

         double jmul = (double) cy1 / (cx1 * 2.0); 

         double delta = w;
         
         
         int imax = cx1 - margin1;
         int jmax = cx1 / 2;
         int rmax = jmax * RAND_MAX;
         double rhalf = RAND_MAX / 2.0;
         int j = 0;
//         int r1 = 0;
//         int r2 = 0;


         double offset;

         double jres;
         int i;
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
            m_pointa[i].y = (int) max(margin2 - jres, min(margin2 + jres, m_pointa[i - 1].y + offset));
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
            m_pointa[i].y = (int) max(margin2 - jres, min(margin2 + jres, m_pointa[i + 1].y + offset));
            m_pointa[i].y = (m_pointa[i].y + margin2) / 2;
            j++;
         }

         bool bWhite;
         bWhite = false;
         if(transitioneffect.m_iVisual == VisualEffectRotateEx5)
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

         imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 , cy1, RGB(0, 0, 0), 10);

         GdiFlush();


         if(transitioneffect.m_iVisual == VisualEffectRotateEx6)
         {
            keeper < bool > keepTransferVoid (&HelperGetMain().GetInterface().m_bTransferVoid, true, false, true);
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
         

         BLENDFUNCTION bf;

         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 127;
         bf.AlphaFormat = 0;

         pdib1->get_graphics()->alpha_blend(
            0, 0, cx1, cy1,
            pdib2->get_graphics(),
            0, 0, cx1, cy1,
            bf);

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
            ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
            m_color.set_rgb(pdib1->GetPixel(
               pdib1->width() / 2,
               pdib1->height() / 2));
         }


            
         rect rectClient = tool1.rectClient;
         tool1.cx = rectClient.width();
         tool1.cy = rectClient.height();
         class imaging & imaging = System.imaging();
            

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();
            
         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
            
//         ::ca::graphics & dcBack = graphics.GetBackDC();
//         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
//         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();
            
         ::ca::dib * pdibBack = graphics.GetDib(_graphics::DibBack);
         ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
         ::ca::dib * pdib2 = graphics.GetDib(_graphics::DibTemp2);
         ::ca::dib * pdib3 = graphics.GetDib(_graphics::DibTemp3);
//         ::ca::dib * pdibBuffer = graphics.GetDib(_graphics::DibBuffer);

         //drawdib.draw(pdibBuffer, spgraphics, 0, 0, cx, cy, 0);

         //dcBack.BitBlt(0, 0, cx, cy, &dcBuffer, 0, 0, SRCCOPY);
         //pdib1->Vortex(transitioneffect.m_tool001.m_iStep);

         int cx1 = pdib1->width();
         int cy1 = pdib1->height();
//         int cxm = cx1 / 2;
//         int cym = cy1 / 2;

         if(transitioneffect.m_tool001.m_iStep == 1)
         {
            if(m_pointa.get_size() != cx1)
            {
               m_pointa.set_size(cx1);
               m_pointa1.set_size(cx1);
               m_pointa2.set_size(cx1);

               for(int i = 0; i < cx1; i++)
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


//         int s1 = rand() * 1 / RAND_MAX + 1;
//         int s2 = rand() * 1 / RAND_MAX + 1;
//         int s3 = rand() * 2 / RAND_MAX + 1;
//         int s4 = rand() * 2 / RAND_MAX + 1;

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

         /*for(int i = 0; i < m_colortrack1a.get_size(); i++)
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

            
            RGB(rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX);
                                 
//         BYTE bA = 200;


         GdiFlush();

         //double dmin = min(cx, cy);
         //double dmax = max(cx, cy);abs

         if(m_bGrowColor0)
         {
            //pdib1->get_graphics()->FillSolidRect(0, 0, cx1, cy1, colorStrong1.get_rgb());
         }
         
        // ::ca::graphics_sp pdib3->get_graphics();
         //pdib3->get_graphics()->CreateCompatibleDC(NULL);
         //pdib3->get_graphics()->SelectObject(pdib3->m_hbitmap);

      //   pdib3->stretch_dib(pdibBuffer);

      //   pdib3->Paste(pdib1);

//         int c1 = rand() * 3 / RAND_MAX;
//         int c2 = rand() * 3 / RAND_MAX;
//         int c4 = rand() * 10 / RAND_MAX + 1;



         
         
         
         
         
         
         
         
         
         
         
         
         
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
         ::ca::pen_sp pen1(get_app());
         pen1->construct(PS_SOLID, 1, colorStrong1.get_rgb());
         ::ca::pen_sp penWhite(get_app());
         penWhite->construct(PS_SOLID, 3, RGB(205, 205, 205));
         int margin1 = 10;
//         int margin2 = cy1 / 2;
         int w = cy1 / 3;

         int delta = 5;
         
         
         int imax = cx1 - margin1;
         int jmax = cx1 / 2;
         int rmax = jmax * RAND_MAX;
         int rhalf = RAND_MAX / 2;
         int j = 0;
         int r1 = 0;
         int r2 = 0;


         int offset;
         int i;
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

         imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 , cy1, RGB(34, 34, 34), 10);

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
            ::ca::pen_sp pen1(get_app(), PS_SOLID, 0, colorStrong1.get_rgb());
            ::ca::brush_sp brush1(get_app(), colorStrong1.get_rgb());
            ::ca::pen_sp pen2(get_app(), PS_SOLID, 0, colorStrong2.get_rgb());
            ::ca::brush_sp brush2(get_app(), colorStrong2.get_rgb());
            ::ca::pen_sp pen3(get_app(), PS_SOLID, 0, colorStrong3.get_rgb());
            ::ca::brush_sp brush3(get_app(), colorStrong3.get_rgb());
            ::ca::pen_sp pen4(get_app(), PS_SOLID, 0, colorStrong4.get_rgb());
            ::ca::brush_sp brush4(get_app(), colorStrong4.get_rgb());
            ::ca::pen_sp pen5(get_app(), PS_SOLID, 0, colorStrong5.get_rgb());
            ::ca::brush_sp brush5(get_app(), colorStrong5.get_rgb());
            for(int i = 0; i < m_colortrack1a.get_size(); i++)
            {
               ColorTrack1 & ct1 = m_colortrack1a[i];
               int x1 = ct1.m_ptColorTrack.x;
               int y1 = ct1.m_ptColorTrack.y;
               int d = ct1.m_dSize;
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

         BLENDFUNCTION bf;

         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 127;
      //   bf.AlphaFormat = AC_SRC_ALPHA;
         bf.AlphaFormat = 0;

         pdib1->get_graphics()->alpha_blend(
            0, 0, cx1, cy1,
            pdib2->get_graphics(),
            0, 0, cx1, cy1,
            bf);

         pdibBack->stretch_dib(pdib1);

         recta.add(rectClient);
      }




      PixelExplosion::PixelExplosion()
      {

         m_iWidth = 0;
         m_iHeight = 0;

         m_bDrawWithLight = TRUE;
         m_iLightModifier = 1;
         m_iHpage = 0;
         m_density = 5;
      }

      PixelExplosion::~PixelExplosion()
      {
         // Cleanup
      }
      void PixelExplosion::create(int iWidth,int iHeight)
      {
         m_pointa.set_size(iWidth * iHeight);
         m_pointaM.set_size(iWidth * iHeight);


         m_iWidth = iWidth;
         m_iHeight = iHeight;

         // Set our page to 0
         m_iHpage = 0;

      }
      void PixelExplosion::FlattenWater()
      {
         // clear our height fields
      }
      void PixelExplosion::to(DWORD* pSrcImage,DWORD* pTargetImage)
      {
         int i = 0;
         
         // Yes they have to be the same size...(for now)
         DrawWaterNoLight(m_iHpage,pSrcImage,pTargetImage);
         if(i == 2)
         {
            Calc2(m_iHpage, (int)m_density);
         }
         else
         {
            CalcWater(m_iHpage, (int) m_density);
         }


         m_iHpage ^= 1;

      }

      void PixelExplosion::CalcWater(int npage, int density)
      {
         UNREFERENCED_PARAMETER(npage);
         UNREFERENCED_PARAMETER(density);
         int imin = - m_iWidth / 2;
         int imax = m_iWidth / 2;
         int jmin = - m_iHeight / 2;
         int jmax = m_iHeight / 2;
         int i, j;
         int x, y;

         double dr;
         double dcos;
         double dsin;



         double dmax = min(m_iWidth, m_iHeight);

         double dm = dmax / 3;
         
         if(m_minradius > 0.0)
         {
            dm = m_minradius;
         }


         double m, n;


         int k = 0;
         for(y = 0, j = jmin; j < jmax; j++, y++)
         {
            for(x = 0, i = imin; i < imax; i++, x++)
            {
               m = m_pointa[k].x;
               n = m_pointa[k].y;


               dr = sqrt(m * m + n * n);
               double d;
               if(abs(dr) < dm)
               {
                  double da = rand() * 3.1415 * 2 / RAND_MAX;
                  dcos = cos(da);
                  dsin = sin(da);
                  dr = rand() * dm * 1.2 / RAND_MAX;;
                  d = 1.0;
               }
               else
               {
                  
                  dcos = m / dr;
                  dsin = n / dr;
               }

               d = dr / dmax;
               

               //d = sqrt(d);

               // i = x + y * width
               m_pointa[k].x = dr * dcos * (rand() * density * d / RAND_MAX + 1.0);
               m_pointa[k].y = dr * dsin * (rand() * density * d / RAND_MAX + 1.0);
               //m_pointa[k].x = dr * dcos * (1000 * 0.2 * d / RAND_MAX + 1.0);
               //m_pointa[k].y = dr * dsin * (1000 * 0.2 * d / RAND_MAX + 1.0);
               //m_pointa[k].x = dr * dcos * 1.2 * d;
               //m_pointa[k].y = dr * dsin * 1.2 * d;
               k++;
            }
         }


      }

      void PixelExplosion::Calc2(int npage, int density)
      {
         UNREFERENCED_PARAMETER(npage);
         UNREFERENCED_PARAMETER(density);
         m_z *= 1.1;

         int imin = - m_iWidth / 2;
         int imax = m_iWidth / 2;
         int jmin = - m_iHeight / 2;
         int jmax = m_iHeight / 2;
         int i, j;
         int x, y;

         double dr;
         double dcos;
         double dsin;

         double dmax = sqrt((double) (imax * imax + jmax * jmax));

         if(m_z > dmax) m_z = dmax;
         //double dmax = min(m_iWidth, m_iHeight);
         //double dmax = max(m_iWidth, m_iHeight) * 2;

         double m, n, o;


         int k = 0;
         for(y = 0, j = jmin; j < jmax; j++, y++)
         {
            for(x = 0, i = imin; i < imax; i++, x++)
            {
               m = m_pointa[k].x;
               n = m_pointa[k].y;
               o = m_pointa[k].z;


               dr = sqrt(m * m + n * n);
               double d;
               if(dr < 10.0)
               {
                  double da = rand() * 3.1415 * 2 / RAND_MAX;
                  dcos = cos(da);
                  dsin = sin(da);
                  //dr = 1.0;
                  dr = max(2.0, d);
                  //o = 0;
               }
               else
               {
                  
                  dcos = m / dr;
                  dsin = n / dr;
               }

               d = m_z;
               

               //d = sqrt(d);

               //int rnd = 
               // i = x + y * width
               //m_pointa[k].x = dr * dcos * (rand() * 0.5 * d / RAND_MAX + 1.0);
               //m_pointa[k].y = dr * dsin * (rand() * 0.5 * d / RAND_MAX + 1.0);
               m_pointa[k].x = i * d;
               m_pointa[k].y = j * d;
               //m_pointa[k].x = dr * dcos * 1.2 * d;
               //m_pointa[k].y = dr * dsin * 1.2 * d;
               k++;
            }
         }


      }
      void PixelExplosion::SmoothWater(int npage)
      {
         UNREFERENCED_PARAMETER(npage);
      }

      void PixelExplosion::CalcWaterBigFilter(int npage, int density)
      {
         UNREFERENCED_PARAMETER(npage);
         UNREFERENCED_PARAMETER(density);
      }

      void PixelExplosion::Reset()
      {
         m_z = 0.1;
         int imin = - m_iWidth / 2;
         int imax = m_iWidth / 2;
         int jmin = - m_iHeight / 2;
         int jmax = m_iHeight / 2;

         double max = imax * imax + jmax * jmax;
         //double max = max(imax, jmax) * 2;
      //   max = 2 * max;

         int k = 0;
         int i, j;
         for(j = jmin; j < jmax; j++)
         {
            for(i = imin; i < imax; i++)
            {

               m_pointaM[k].x = i;
               m_pointaM[k].x = j;
               m_pointaM[k].z = sqrt(max - (i * i + j * j));
               m_pointa[k].x = i;
               m_pointa[k].y = j;
               m_pointa[k].z = m_pointaM[k].z;
               k++;
            }
         }

      }

      void PixelExplosion::HeightBox (int x, int y, int radius, int height, int page)
      {
         UNREFERENCED_PARAMETER(x);
         UNREFERENCED_PARAMETER(y);
         UNREFERENCED_PARAMETER(radius);
         UNREFERENCED_PARAMETER(height);
         UNREFERENCED_PARAMETER(page);
      }


      void PixelExplosion::WarpBlob(int x, int y, int radius, int height, int page)
      {
         UNREFERENCED_PARAMETER(x);
         UNREFERENCED_PARAMETER(y);
         UNREFERENCED_PARAMETER(radius);
         UNREFERENCED_PARAMETER(height);
         UNREFERENCED_PARAMETER(page);
      }

      void PixelExplosion::SineBlob(int x, int y, int radius, int height, int page)
      {
         UNREFERENCED_PARAMETER(x);
         UNREFERENCED_PARAMETER(y);
         UNREFERENCED_PARAMETER(radius);
         UNREFERENCED_PARAMETER(height);
         UNREFERENCED_PARAMETER(page);
      }

      void PixelExplosion::DrawWaterNoLight(int page,DWORD* pSrcImage,DWORD* pTargetImage)
      {
         UNREFERENCED_PARAMETER(page);
      //  int ox, oy;
        int x, y;

         int mx = m_iWidth / 2;
         int my = m_iHeight / 2;


//        int offset=m_iWidth + 1;


        for (y = 0; y < m_iHeight; y++)
        {
          for (x = 0; x < m_iWidth; x++)
          {
             int i = x + y * m_iWidth;
             int newx = (int) m_pointa[i].x + mx;
             if(newx < 0 || newx >= m_iWidth)
                continue;
             int newy = (int) m_pointa[i].y + my;
             if(newy < 0 || newy >= m_iHeight)
                continue;
             
             pTargetImage[newx + newy * m_iWidth] =
                  pSrcImage[x + y * m_iWidth];
       
          }
        }
      }

      inline COLORREF PixelExplosion::GetShiftedColor(COLORREF color,int shift)
      {
         long R;
         long G;
         long B;
         int ir;
         int ig;
         int ib;

         R = rgba_get_r(color)-shift;
         G = rgba_get_g(color)-shift;
         B = rgba_get_b(color)-shift;

         ir = (R < 0) ? 0 : (R > 255) ? 255 : R;
         ig = (G < 0) ? 0 : (G > 255) ? 255 : G;
         ib = (B < 0) ? 0 : (B > 255) ? 255 : B;

         return RGB(ir,ig,ib);
      }


      void VisualEffect::RenderAlphaPixelExplosion(rect_array & recta)
      {
         Main & main = HelperGetMain();

         TransitionEffect & transitioneffect = main.GetTransitionEffect();
         Graphics & graphics = main.GetGraphics();

         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
            
//         ::ca::graphics & dcBack = graphics.GetBackDC();
         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
//         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();

         ::ca::dib * pdibBack = graphics.GetDib(_graphics::DibBack);
         ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
         ::ca::dib * pdib2 = graphics.GetDib(_graphics::DibTemp2);
         ::ca::dib * pdib3 = graphics.GetDib(_graphics::DibTemp3);
         ::ca::dib * pdib4 = graphics.GetDib(_graphics::DibTemp4);
         ::ca::dib * pdibBuffer = graphics.GetDib(_graphics::DibBuffer);
         if(transitioneffect.m_tool001.m_iStep == 1)
         {
            ::ca::dib * pdibFrame1 = graphics.GetDib(_graphics::DibFrame1);

            tool1.dmod = 4.2;
            tool1.dminsize = 0;
            int cx1 = tool1.cx / 4;
            int cy1 = tool1.cy / 4;
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
            pdib1->stretch_dib(pdibBuffer);
            pdib3->get_graphics()->SetStretchBltMode(HALFTONE);
            pdib3->stretch_dib(pdibFrame1);
         }
         int cx1 = pdib1->width();
         int cy1 = pdib1->height();

            
         pdib3->Fill(0, 0, 0);
         
         pdib4->get_graphics()->BitBlt(0, 0, cx1, cy1, &dcBuffer, 0, 0, SRCCOPY);

         GdiFlush();
         
         /*System.imaging().bitmap_blend(
            pdib4->get_graphics(),
            0, 0, cx1, cy1,
            pdib1->get_graphics(),
            0, 0,
            (BYTE) max(min(255, tool1.dalpha), 0));*/

         int iReturnPoint = transitioneffect.m_tool001.m_iStepCount * 5 / 21;

         m_explosion.to(pdib4->get_data(), pdib3->get_data());

         /*int mod = max(1, (int) tool1.dmod);
         if((tool1.frame % mod) == 0)
         {
            int x = rand() * cx1 / RAND_MAX;
            int y = rand() * cy1 / RAND_MAX;
            int r = rand() * min(tool1.dminsize, 60.0) / RAND_MAX + min(tool1.dminsize / 2, 60.0);
            int h = rand() * 100 / RAND_MAX;
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
         //dcBack.FillSolidRect(0, 0, cx, cy, RGB(0, 0, 0));
         //dcBack.FillSolidRect(100, 100, cx, cy, RGB(255, 255, 255));
         //pdibBack->stretch_dib(pdib2);

         BLENDFUNCTION bf;

         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 50;
      //   bf.AlphaFormat = AC_SRC_ALPHA;
         bf.AlphaFormat = 0;

         //pdib3->get_graphics()->BitBlt(0, 0, cx1, cy1, &dcBack, 0, 0, SRCCOPY);
         pdib1->get_graphics()->alpha_blend(
            0, 0, cx1, cy1,
            pdib3->get_graphics(),
            0, 0, cx1, cy1,
            bf);

         pdibBack->stretch_dib(pdib1);

         recta.add(tool1.rectClient);
      }

      void VisualEffect::RenderPixelExplosion(rect_array & recta)
      {
         Main & main = HelperGetMain();

         TransitionEffect & transitioneffect = main.GetTransitionEffect();
         Graphics & graphics = main.GetGraphics();

         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
            
//         ::ca::graphics & dcBack = graphics.GetBackDC();
//         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
//         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();

         ::ca::dib * pdibBack = graphics.GetDib(_graphics::DibBack);
         ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
         ::ca::dib * pdib2 = graphics.GetDib(_graphics::DibTemp2);
         ::ca::dib * pdib3 = graphics.GetDib(_graphics::DibTemp3);
         ::ca::dib * pdib4 = graphics.GetDib(_graphics::DibTemp4);
         ::ca::dib * pdibBuffer = graphics.GetDib(_graphics::DibBuffer);
         if(transitioneffect.m_tool001.m_iStep == 1)
         {
//            ::ca::dib * pdibFrame1 = graphics.GetDib(_graphics::DibFrame1);

            tool1.dmod = 4.2;
            tool1.dminsize = 0;
            int cx1 = tool1.cx / 4;
            int cy1 = tool1.cy / 4;
            pdib1->create(cx1, cy1);
            pdib2->create(cx1, cy1);
            pdib3->create(cx1, cy1);
            pdib4->create(cx1, cy1);
            tool1.dalpha = 0;

            m_explosion.m_density = 1.5;
            m_explosion.m_minradius = 0.0;
            m_explosion.create(cx1, cy1);
            m_explosion.Reset();

            pdib1->get_graphics()->FillSolidRect(0, 0, cx1, cy1, RGB(0, 0, 0));
            pdib3->get_graphics()->SetStretchBltMode(HALFTONE);
            pdib3->stretch_dib(pdibBuffer);
         }

         pdib4->get_graphics()->from(pdib1->size(), pdib3->get_graphics(), SRCCOPY);
         
         System.imaging().bitmap_blend(
            pdib4->get_graphics(),
            null_point(), pdib1->size(),
            pdib1->get_graphics(),
            null_point(),
            (BYTE) max(min(255, tool1.dalpha), 0));

         int iReturnPoint = transitioneffect.m_tool001.m_iStepCount * 5 / 21;

         m_explosion.to(pdib4->get_data(), pdib2->get_data());

         /*int mod = max(1, (int) tool1.dmod);
         if((tool1.frame % mod) == 0)
         {
            int x = rand() * cx1 / RAND_MAX;
            int y = rand() * cy1 / RAND_MAX;
            int r = rand() * min(tool1.dminsize, 60.0) / RAND_MAX + min(tool1.dminsize / 2, 60.0);
            int h = rand() * 100 / RAND_MAX;
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
         //dcBack.FillSolidRect(0, 0, cx, cy, RGB(0, 0, 0));
         //dcBack.FillSolidRect(100, 100, cx, cy, RGB(255, 255, 255));
         pdibBack->stretch_dib(pdib2);

         recta.add(tool1.rectClient);
      }

      void VisualEffect::RenderPixelExplosion2(rect_array & recta)
      {
      Main & main = HelperGetMain();

         TransitionEffect & transitioneffect = main.GetTransitionEffect();
         Graphics & graphics = main.GetGraphics();

         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
            
//         ::ca::graphics & dcBack = graphics.GetBackDC();
         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
//         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();

         ::ca::dib * pdibBack = graphics.GetDib(_graphics::DibBack);
         ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
         ::ca::dib * pdib2 = graphics.GetDib(_graphics::DibTemp2);
         ::ca::dib * pdib3 = graphics.GetDib(_graphics::DibTemp3);
         ::ca::dib * pdib4 = graphics.GetDib(_graphics::DibTemp4);
         ::ca::dib * pdibBuffer = graphics.GetDib(_graphics::DibBuffer);
         if(transitioneffect.m_tool001.m_iStep == 1)
         {
            ::ca::dib * pdibFrame1 = graphics.GetDib(_graphics::DibFrame1);

            tool1.dmod = 4.2;
            tool1.dminsize = 0;
            int cx1 = tool1.cx / 4;
            int cy1 = tool1.cy / 4;
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
         int cx1 = pdib1->width();
         int cy1 = pdib1->height();

         pdib3->Fill(0, 0, 0);
         
         pdib4->get_graphics()->BitBlt(0, 0, cx1, cy1, &dcBuffer, 0, 0, SRCCOPY);

         GdiFlush();
         
         /*System.imaging().bitmap_blend(
            pdib4->get_graphics(),
            0, 0, cx1, cy1,
            pdib1->get_graphics(),
            0, 0,
            (BYTE) max(min(255, tool1.dalpha), 0));*/

         int iReturnPoint = transitioneffect.m_tool001.m_iStepCount * 5 / 21;

         m_explosion.to(pdib4->get_data(), pdib3->get_data());

         /*int mod = max(1, (int) tool1.dmod);
         if((tool1.frame % mod) == 0)
         {
            int x = rand() * cx1 / RAND_MAX;
            int y = rand() * cy1 / RAND_MAX;
            int r = rand() * min(tool1.dminsize, 60.0) / RAND_MAX + min(tool1.dminsize / 2, 60.0);
            int h = rand() * 100 / RAND_MAX;
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
            ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
            m_color.set_rgb(pdib1->GetPixel(
               pdib1->width() / 2,
               pdib1->height() / 2));
         }


            
         rect rectClient = tool1.rectClient;
         tool1.cx = rectClient.width();
         tool1.cy = rectClient.height();
         class imaging & imaging = System.imaging();
            

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();
            
         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
            
//         ::ca::graphics & dcBack = graphics.GetBackDC();
//         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
///         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();

         ::ca::dib * pdibBack = graphics.GetDib(_graphics::DibBack);
         ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
         ::ca::dib * pdib2 = graphics.GetDib(_graphics::DibTemp2);
         ::ca::dib * pdib3 = graphics.GetDib(_graphics::DibTemp3);
//         ::ca::dib * pdibBuffer = graphics.GetDib(_graphics::DibBuffer);

         int cx1 = pdib1->width();
         int cy1 = pdib1->height();
//         int cxm = cx1 / 2;
//         int cym = cy1 / 2;

         if(transitioneffect.m_tool001.m_iStep == 1)
         {
            pdib2->create(cx1, cy1);
            pdib3->create(cx1, cy1);
         }


//         int s1 = rand() * 1 / RAND_MAX + 1;
//         int s2 = rand() * 1 / RAND_MAX + 1;
//         int s3 = rand() * 2 / RAND_MAX + 1;
//         int s4 = rand() * 2 / RAND_MAX + 1;

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

         /*for(int i = 0; i < m_colortrack1a.get_size(); i++)
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

            
            RGB(rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX);
                                 
//         BYTE bA = 200;


         GdiFlush();

         //double dmin = min(cx, cy);
         //double dmax = max(cx, cy);abs

         if(m_bGrowColor0)
         {
            //pdib1->get_graphics()->FillSolidRect(0, 0, cx1, cy1, colorStrong1.get_rgb());
         }
         
//         int c1 = rand() * 3 / RAND_MAX;
//         int c2 = rand() * 3 / RAND_MAX;
//         int c4 = rand() * 10 / RAND_MAX + 1;


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
         ::ca::pen_sp pen1(get_app());
         pen1->construct(PS_SOLID, 1, colorStrong1.get_rgb());
         pdib1->get_graphics()->SelectObject(pen1);
         int marginx = cx1 / 12;
         int marginy = cy1 * 5 / 11;
         int w = marginx * 2;
         pdib1->get_graphics()->MoveTo(marginx, marginy);
         
         int imax = cx1 - marginx;
         int jmax = cx1 / 2;
         int rmax = jmax * RAND_MAX;
         int rhalf = RAND_MAX / 2;
         int j = 0;
         int r1 = 0;
         int r2 = 0;
         int i;
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

         imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1, cy1, RGB(0, 0, 0), 10);

      /*   {
            ::ca::pen_sp pen1(get_app(), PS_SOLID, 0, colorStrong1.get_rgb());
            ::ca::brush_sp brush1(get_app(), colorStrong1.get_rgb());
            ::ca::pen_sp pen2(get_app(), PS_SOLID, 0, colorStrong2.get_rgb());
            ::ca::brush_sp brush2(get_app(), colorStrong2.get_rgb());
            ::ca::pen_sp pen3(get_app(), PS_SOLID, 0, colorStrong3.get_rgb());
            ::ca::brush_sp brush3(get_app(), colorStrong3.get_rgb());
            ::ca::pen_sp pen4(get_app(), PS_SOLID, 0, colorStrong4.get_rgb());
            ::ca::brush_sp brush4(get_app(), colorStrong4.get_rgb());
            ::ca::pen_sp pen5(get_app(), PS_SOLID, 0, colorStrong5.get_rgb());
            ::ca::brush_sp brush5(get_app(), colorStrong5.get_rgb());
            for(int i = 0; i < m_colortrack1a.get_size(); i++)
            {
               ColorTrack1 & ct1 = m_colortrack1a[i];
               int x1 = ct1.m_ptColorTrack.x;
               int y1 = ct1.m_ptColorTrack.y;
               int d = ct1.m_dSize;
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

         BLENDFUNCTION bf;

         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 127;
      //   bf.AlphaFormat = AC_SRC_ALPHA;
         bf.AlphaFormat = 0;

         pdib1->get_graphics()->alpha_blend(
            0, 0, cx1, cy1,
            pdib2->get_graphics(),
            0, 0, cx1, cy1,
            bf);

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
            ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
            m_color.set_rgb(pdib1->GetPixel(
               pdib1->width() / 2,
               pdib1->height() / 2));
         }


            
         rect rectClient = tool1.rectClient;
         tool1.cx = rectClient.width();
         tool1.cy = rectClient.height();
         class imaging & imaging = System.imaging();
            

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();
            
         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
            
//         ::ca::graphics & dcBack = graphics.GetBackDC();
//         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
//         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();
            
         ::ca::dib * pdibBack = graphics.GetDib(_graphics::DibBack);
         ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
         ::ca::dib * pdib2 = graphics.GetDib(_graphics::DibTemp2);
         ::ca::dib * pdib3 = graphics.GetDib(_graphics::DibTemp3);
//         ::ca::dib * pdibBuffer = graphics.GetDib(_graphics::DibBuffer);

         //drawdib.draw(pdibBuffer, spgraphics, 0, 0, cx, cy, 0);

         //dcBack.BitBlt(0, 0, cx, cy, &dcBuffer, 0, 0, SRCCOPY);
         //pdib1->Vortex(transitioneffect.m_tool001.m_iStep);

         int cx1 = pdib1->width();
         int cy1 = pdib1->height();
//         int cxm = cx1 / 2;
//         int cym = cy1 / 2;

         if(transitioneffect.m_tool001.m_iStep == 1)
         {
            pdib2->create(cx1, cy1);
            pdib3->create(cx1, cy1);
         }


//         int s1 = rand() * 1 / RAND_MAX + 1;
//         int s2 = rand() * 1 / RAND_MAX + 1;
//         int s3 = rand() * 2 / RAND_MAX + 1;
//         int s4 = rand() * 2 / RAND_MAX + 1;

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

         /*for(int i = 0; i < m_colortrack1a.get_size(); i++)
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

            
            RGB(rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX);
                                 
         BYTE bA = 200;


         GdiFlush();

         //double dmin = min(cx, cy);
         //double dmax = max(cx, cy);abs

         if(m_bGrowColor0)
         {
            //pdib1->get_graphics()->FillSolidRect(0, 0, cx1, cy1, colorStrong1.get_rgb());
         }
         
        // ::ca::graphics_sp pdib3->get_graphics();
         //pdib3->get_graphics()->CreateCompatibleDC(NULL);
         //pdib3->get_graphics()->SelectObject(pdib3->m_hbitmap);

      //   pdib3->stretch_dib(pdibBuffer);

      //   pdib3->Paste(pdib1);

//         int c1 = rand() * 3 / RAND_MAX;
//         int c2 = rand() * 3 / RAND_MAX;
//         int c4 = rand() * 10 / RAND_MAX + 1;


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
         ::ca::pen_sp pen1(get_app());
         pen1->construct(PS_SOLID, 1, colorStrong1.get_rgb());
         pdib1->get_graphics()->SelectObject(pen1);
         int margin = 10;
         int w = margin * 2;
         pdib1->get_graphics()->MoveTo(margin, margin);
         
         int imax = cx1 - margin;
         int jmax = cx1 / 2;
         int rmax = jmax * RAND_MAX;
         int rhalf = RAND_MAX / 2;
         int j = 0;
         int r1 = 0;
         int r2 = 0;
         int i;
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
            int x2 = cx1 / 2;
            int y2 = cy1 / 2;
            int w2 = cx1 / 2 - 1;
            int h2 = cy1 / 2 - 1;

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
            ::ca::pen_sp pen1(get_app(), PS_SOLID, 0, colorStrong1.get_rgb());
            ::ca::brush_sp brush1(get_app(), colorStrong1.get_rgb());
            ::ca::pen_sp pen2(get_app(), PS_SOLID, 0, colorStrong2.get_rgb());
            ::ca::brush_sp brush2(get_app(), colorStrong2.get_rgb());
            ::ca::pen_sp pen3(get_app(), PS_SOLID, 0, colorStrong3.get_rgb());
            ::ca::brush_sp brush3(get_app(), colorStrong3.get_rgb());
            ::ca::pen_sp pen4(get_app(), PS_SOLID, 0, colorStrong4.get_rgb());
            ::ca::brush_sp brush4(get_app(), colorStrong4.get_rgb());
            ::ca::pen_sp pen5(get_app(), PS_SOLID, 0, colorStrong5.get_rgb());
            ::ca::brush_sp brush5(get_app(), colorStrong5.get_rgb());
            for(int i = 0; i < m_colortrack1a.get_size(); i++)
            {
               ColorTrack1 & ct1 = m_colortrack1a[i];
               int x1 = ct1.m_ptColorTrack.x;
               int y1 = ct1.m_ptColorTrack.y;
               int d = ct1.m_dSize;
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

         BLENDFUNCTION bf;

         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 127;
         bf.AlphaFormat = 0;

         pdib1->get_graphics()->alpha_blend(
            0, 0, cx1, cy1,
            pdib2->get_graphics(),
            0, 0, cx1, cy1,
            bf);

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
            ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
            m_color.set_rgb(pdib1->GetPixel(
               pdib1->width() / 2,
               pdib1->height() / 2));
         }
            
         rect rectClient = tool1.rectClient;
         tool1.cx = rectClient.width();
         tool1.cy = rectClient.height();
         class imaging & imaging = System.imaging();
            

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();
            
         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
            
//         ::ca::graphics & dcBack = graphics.GetBackDC();
//         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
//         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();

         ::ca::dib * pdibBack = graphics.GetDib(_graphics::DibBack);
         ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
         ::ca::dib * pdib2 = graphics.GetDib(_graphics::DibTemp2);
         ::ca::dib * pdib3 = graphics.GetDib(_graphics::DibTemp3);
         ::ca::dib * pdib4 = graphics.GetDib(_graphics::DibTemp4);
//         ::ca::dib * pdibBuffer = graphics.GetDib(_graphics::DibBuffer);

         int cx1 = pdib1->width();
         int cy1 = pdib1->height();
//         int cxm = cx1 / 2;
//         int cym = cy1 / 2;

         if(transitioneffect.m_tool001.m_iStep == 1)
         {
            if(m_pointa.get_size() != cx1)
            {
               m_pointa.set_size(cx1);
               m_pointa1.set_size(cx1);
               m_pointa2.set_size(cx1);

               for(int i = 0; i < cx1; i++)
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

         if(transitioneffect.m_iVisual == VisualEffectExpand6)
         {
            pdib2->Fill(0, 0, 0, 0);
            pdib3->Fill(0, 0, 0, 0);
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
         
         ::ca::pen_sp pen1(get_app());
         pen1->construct(PS_SOLID, 1, colorStrong1.get_rgb());
         ::ca::pen_sp penWhite(get_app());
         penWhite->construct(PS_SOLID, 3, RGB(205, 205, 205));
         int margin1 = cx1 / 8;
         int margin2 = cy1 / 2;
         int w = cy1 / 3;

         double jmul = (double) cy1 / (cx1 * 2.0); 

         double delta = w;
         
         
         int imax = cx1 - margin1;
         int jmax = cx1 / 2;
         int rmax = jmax * RAND_MAX;
         double rhalf = RAND_MAX / 2.0;
         int j = 0;
//         int r1 = 0;
//         int r2 = 0;


         double offset;

         double jres;
         int i;
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
         if(transitioneffect.m_iVisual == VisualEffectRotateEx5)
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

         imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 , cy1, RGB(0, 0, 0), 10);

         GdiFlush();


         if(transitioneffect.m_iVisual == VisualEffectRotateEx6)
         {
            

            keeper < bool > keepTransferVoid (&HelperGetMain().GetInterface().m_bTransferVoid, true, false, true);


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
         

         BLENDFUNCTION bf;

         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 127;
         bf.AlphaFormat = 0;

         pdib1->get_graphics()->alpha_blend(
            0, 0, cx1, cy1,
            pdib2->get_graphics(),
            0, 0, cx1, cy1,
            bf);

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
            ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
            m_color.set_rgb(pdib1->GetPixel(
               pdib1->width() / 2,
               pdib1->height() / 2));
         }


            
         rect rectClient = tool1.rectClient;
         tool1.cx = rectClient.width();
         tool1.cy = rectClient.height();
         class imaging & imaging = System.imaging();
            

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();
            
         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
            
//         ::ca::graphics & dcBack = graphics.GetBackDC();
//         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
//         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();
            
         ::ca::dib * pdibBack = graphics.GetDib(_graphics::DibBack);
         ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
         ::ca::dib * pdib2 = graphics.GetDib(_graphics::DibTemp2);
         ::ca::dib * pdib3 = graphics.GetDib(_graphics::DibTemp3);
//         ::ca::dib * pdibBuffer = graphics.GetDib(_graphics::DibBuffer);

         //drawdib.draw(pdibBuffer, spgraphics, 0, 0, cx, cy, 0);

         //dcBack.BitBlt(0, 0, cx, cy, &dcBuffer, 0, 0, SRCCOPY);
         //pdib1->Vortex(transitioneffect.m_tool001.m_iStep);

         int cx1 = pdib1->width();
         int cy1 = pdib1->height();
//         int cxm = cx1 / 2;
//         int cym = cy1 / 2;

         if(transitioneffect.m_tool001.m_iStep == 1)
         {
            if(m_pointa.get_size() != cx1)
            {
               m_pointa.set_size(cx1);
               m_pointa1.set_size(cx1);
               m_pointa2.set_size(cx1);

               for(int i = 0; i < cx1; i++)
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


//         int s1 = rand() * 1 / RAND_MAX + 1;
//         int s2 = rand() * 1 / RAND_MAX + 1;
//         int s3 = rand() * 2 / RAND_MAX + 1;
//         int s4 = rand() * 2 / RAND_MAX + 1;

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

         /*for(int i = 0; i < m_colortrack1a.get_size(); i++)
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

            
            RGB(rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX);
                                 
//         BYTE bA = 200;


         GdiFlush();

         //double dmin = min(cx, cy);
         //double dmax = max(cx, cy);abs

         if(m_bGrowColor0)
         {
            //pdib1->get_graphics()->FillSolidRect(0, 0, cx1, cy1, colorStrong1.get_rgb());
         }
         
        // ::ca::graphics_sp pdib3->get_graphics();
         //pdib3->get_graphics()->CreateCompatibleDC(NULL);
         //pdib3->get_graphics()->SelectObject(pdib3->m_hbitmap);

      //   pdib3->stretch_dib(pdibBuffer);

      //   pdib3->Paste(pdib1);

//         int c1 = rand() * 3 / RAND_MAX;
//         int c2 = rand() * 3 / RAND_MAX;
//         int c4 = rand() * 10 / RAND_MAX + 1;



         
         
         
         
         
         
         
         
         
         
         
         
         
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
         ::ca::pen_sp pen1(get_app());
         pen1->construct(PS_SOLID, 1, colorStrong1.get_rgb());
         ::ca::pen_sp penWhite(get_app());
         penWhite->construct(PS_SOLID, 3, RGB(205, 205, 205));
         int margin1 = 10;
//         int margin2 = cy1 / 2;
         int w = cy1 / 3;

         int delta = 5;
         
         
         int imax = cx1 - margin1;
         int jmax = cx1 / 2;
         int rmax = jmax * RAND_MAX;
         int rhalf = RAND_MAX / 2;
         int j = 0;
         int r1 = 0;
         int r2 = 0;


         int offset;
         int i;
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

         imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1 , cy1, RGB(34, 34, 34), 10);

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
            ::ca::pen_sp pen1(get_app(), PS_SOLID, 0, colorStrong1.get_rgb());
            ::ca::brush_sp brush1(get_app(), colorStrong1.get_rgb());
            ::ca::pen_sp pen2(get_app(), PS_SOLID, 0, colorStrong2.get_rgb());
            ::ca::brush_sp brush2(get_app(), colorStrong2.get_rgb());
            ::ca::pen_sp pen3(get_app(), PS_SOLID, 0, colorStrong3.get_rgb());
            ::ca::brush_sp brush3(get_app(), colorStrong3.get_rgb());
            ::ca::pen_sp pen4(get_app(), PS_SOLID, 0, colorStrong4.get_rgb());
            ::ca::brush_sp brush4(get_app(), colorStrong4.get_rgb());
            ::ca::pen_sp pen5(get_app(), PS_SOLID, 0, colorStrong5.get_rgb());
            ::ca::brush_sp brush5(get_app(), colorStrong5.get_rgb());
            for(int i = 0; i < m_colortrack1a.get_size(); i++)
            {
               ColorTrack1 & ct1 = m_colortrack1a[i];
               int x1 = ct1.m_ptColorTrack.x;
               int y1 = ct1.m_ptColorTrack.y;
               int d = ct1.m_dSize;
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

         BLENDFUNCTION bf;

         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 127;
      //   bf.AlphaFormat = AC_SRC_ALPHA;
         bf.AlphaFormat = 0;

         pdib1->get_graphics()->alpha_blend(
            0, 0, cx1, cy1,
            pdib2->get_graphics(),
            0, 0, cx1, cy1,
            bf);

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
            ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
            m_color.set_rgb(pdib1->GetPixel(
               pdib1->width() / 2,
               pdib1->height() / 2));
         }


            
         rect rectClient = tool1.rectClient;
         tool1.cx = rectClient.width();
         tool1.cy = rectClient.height();
         class imaging & imaging = System.imaging();
            

//         ::ca::draw_dib & drawdib = graphics.GetDrawDib();
            
         ASSERT(graphics.GetBufferDC().get_os_data() != NULL);
            
//         ::ca::graphics & dcBack = graphics.GetBackDC();
//         ::ca::graphics & dcBuffer = graphics.GetBufferDC();
//         ::ca::graphics & dcFrame1 = graphics.GetFrame1DC();

         ::ca::dib * pdibBack = graphics.GetDib(_graphics::DibBack);
         ::ca::dib * pdib1 = graphics.GetDib(_graphics::DibTemp1);
         ::ca::dib * pdib2 = graphics.GetDib(_graphics::DibTemp2);
         ::ca::dib * pdib3 = graphics.GetDib(_graphics::DibTemp3);
//         ::ca::dib * pdibBuffer = graphics.GetDib(_graphics::DibBuffer);

         int cx1 = pdib1->width();
         int cy1 = pdib1->height();
//         int cxm = cx1 / 2;
//         int cym = cy1 / 2;

         if(transitioneffect.m_tool001.m_iStep == 1)
         {
            pdib2->create(cx1, cy1);
            pdib3->create(cx1, cy1);
         }

//         int s1 = rand() * 1 / RAND_MAX + 1;
//         int s2 = rand() * 1 / RAND_MAX + 1;
//         int s3 = rand() * 2 / RAND_MAX + 1;
//         int s4 = rand() * 2 / RAND_MAX + 1;

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

         /*for(int i = 0; i < m_colortrack1a.get_size(); i++)
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

            
            RGB(rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX,
            rand() * 255 / RAND_MAX);
                                 
//         BYTE bA = 200;


         GdiFlush();

         //double dmin = min(cx, cy);
         //double dmax = max(cx, cy);abs

         if(m_bGrowColor0)
         {
            //pdib1->get_graphics()->FillSolidRect(0, 0, cx1, cy1, colorStrong1.get_rgb());
         }
         
//         int c1 = rand() * 3 / RAND_MAX;
//         int c2 = rand() * 3 / RAND_MAX;
//         int c4 = rand() * 10 / RAND_MAX + 1;


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
         ::ca::pen_sp pen1(get_app());
         pen1->construct(PS_SOLID, 1, colorStrong1.get_rgb());
         pdib1->get_graphics()->SelectObject(pen1);
         int marginx = cx1 / 12;
         int marginy = cy1 * 5 / 11;
         int w = marginx * 2;
         pdib1->get_graphics()->MoveTo(marginx, marginy);
         
         int imax = cx1 - marginx;
         int jmax = cx1 / 2;
         int rmax = jmax * RAND_MAX;
         int rhalf = RAND_MAX / 2;
         int j = 0;
         int r1 = 0;
         int r2 = 0;
         int i;
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

         imaging.color_blend(pdib1->get_graphics(), 0, 0, cx1, cy1, RGB(0, 0, 0), 10);

      /*   {
            ::ca::pen_sp pen1(get_app(), PS_SOLID, 0, colorStrong1.get_rgb());
            ::ca::brush_sp brush1(get_app(), colorStrong1.get_rgb());
            ::ca::pen_sp pen2(get_app(), PS_SOLID, 0, colorStrong2.get_rgb());
            ::ca::brush_sp brush2(get_app(), colorStrong2.get_rgb());
            ::ca::pen_sp pen3(get_app(), PS_SOLID, 0, colorStrong3.get_rgb());
            ::ca::brush_sp brush3(get_app(), colorStrong3.get_rgb());
            ::ca::pen_sp pen4(get_app(), PS_SOLID, 0, colorStrong4.get_rgb());
            ::ca::brush_sp brush4(get_app(), colorStrong4.get_rgb());
            ::ca::pen_sp pen5(get_app(), PS_SOLID, 0, colorStrong5.get_rgb());
            ::ca::brush_sp brush5(get_app(), colorStrong5.get_rgb());
            for(int i = 0; i < m_colortrack1a.get_size(); i++)
            {
               ColorTrack1 & ct1 = m_colortrack1a[i];
               int x1 = ct1.m_ptColorTrack.x;
               int y1 = ct1.m_ptColorTrack.y;
               int d = ct1.m_dSize;
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

         BLENDFUNCTION bf;

         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 127;
      //   bf.AlphaFormat = AC_SRC_ALPHA;
         bf.AlphaFormat = 0;

         pdib1->get_graphics()->alpha_blend(
            0, 0, cx1, cy1,
            pdib2->get_graphics(),
            0, 0, cx1, cy1,
            bf);

         pdibBack->stretch_dib(pdib1);

         recta.add(rectClient);
      }

   } // namespace backview

} // namespace gcom
