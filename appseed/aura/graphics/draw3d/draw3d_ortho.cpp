#include "framework.h"

#include <math.h>


namespace draw3d
{


   int_array ortho::draw_ortho_plain_wire_frame(::box * pbox,int iHint,int bA,bool bFirst)
   {

      double dA = bA / 255.0;

      array < point3d >  p = pbox->vertices();

      m_pdc->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::draw2d::pen_sp pen(m_pdc->allocer());

      double zmin = p[0].z;
      double zmax = p[0].z;

      index i;

      for(i = 1; i < p.get_count(); i++)
      {
         if(p[i].z < zmin)
            zmin = p[i].z;
         else if(p[i].z > zmax)
            zmax = p[i].z;
      }

      for(i = 0; i < p.get_count(); i++)
      {

         p[i].z -= zmin;

      }

      zmax -=zmin;

      double d;

      if(zmax <= 0.0)
         d = 0.0;
      else
         d = 0.5 / zmax;


      int_array  p1;
      int_array  p2;



      p1.add(0);
      p2.add(1);

      p1.add(1);
      p2.add(2);

      p1.add(2);
      p2.add(3);

      p1.add(3);
      p2.add(0);



      p1.add(4);
      p2.add(5);

      p1.add(5);
      p2.add(6);

      p1.add(6);
      p2.add(7);

      p1.add(7);
      p2.add(4);



      p1.add(0);
      p2.add(4);

      p1.add(1);
      p2.add(5);

      p1.add(2);
      p2.add(6);

      p1.add(3);
      p2.add(7);

      int iMax;

      i = 0;
      int_array ia;

      while(p1.get_count() > 0)
      {

         iMax = 0;

         for(index j = 0; j < p1.get_count(); j++)
         {

            if((p[p1[j]].z + p[p2[j]].z) >(p[p1[iMax]].z + p[p2[iMax]].z))
            {
               iMax = j;
            }

         }

         if((bFirst && i < 6) || (!bFirst && i >= 6))
         {

            ia.add_unique(p1[iMax]);
            ia.add_unique(p2[iMax]);

            double r = (p[p1[iMax]].z + p[p2[iMax]].z) * d;

            ::color ca;

            double dPeriod = (5000) * 11;

            if(iHint == 0)
            {

               ca.set_hls(fmod(::get_tick_count(),dPeriod) / dPeriod,0.84 - r / 2.0,1.0 - r);
            }
            else
            {
               ca.set_hls(fmod(::get_tick_count() + dPeriod / 2,dPeriod) / dPeriod,0.84 - r / 2.0,1.0 - r);
            }

            COLORREF clr = ca.get_rgb();


            pen->create_solid((1.05 - r) * 10.0,ARGB((int)(dA * (255.0 - r * 200.0)),ca.m_uchR,ca.m_uchG,ca.m_uchB));
            if(i < 6)
            {
               pen->m_etype = ::draw2d::pen::type_dot;
            }
            else
            {
               pen->m_etype = ::draw2d::pen::type_solid;
            }
            m_pdc->SelectObject(pen);
            m_pdc->draw_line((float)p[p1[iMax]].x,(float)p[p1[iMax]].y,(float)p[p2[iMax]].x,(float)p[p2[iMax]].y);
         }
         p1.remove_at(iMax);
         p2.remove_at(iMax);

         i++;
      }


      //pen->create_solid(1.0,ARGB(255,((int)(clr)),((int)(clr)),((int)(clr)))); m_pdc->SelectObject(pen)

      //SET_PCOLOR((p02.z + p03.z) / (2.0 * z));
      //m_pdc->draw_line((float)p02.x,(float)p02.y,(float)p03.x,(float)p03.y);
      //SET_PCOLOR((p03.z + p04.z) / (2.0 * z));
      //m_pdc->draw_line((float)p03.x,(float)p03.y,(float)p04.x,(float)p04.y);
      //SET_PCOLOR((p04.z + p01.z) / (2.0 * z));
      //m_pdc->draw_line((float)p04.x,(float)p04.y,(float)p01.x,(float)p01.y);

      //m_pdc->MoveTo(p05.x,p05.y);
      //SET_PCOLOR((p05.z + p06.z) / (2.0 * z));
      //m_pdc->LineTo(p06.x,p06.y);
      //SET_PCOLOR((p06.z + p07.z) / (2.0 * z));
      //m_pdc->LineTo(p07.x,p07.y);
      //SET_PCOLOR((p07.z + p08.z) / (2.0 * z));
      //m_pdc->LineTo(p08.x,p08.y);
      //SET_PCOLOR((p08.z + p05.z) / (2.0 * z));
      //m_pdc->LineTo(p05.x,p05.y);

      //SET_PCOLOR((p01.z + p05.z) / (2.0 * z));
      //m_pdc->draw_line((float)p01.x,(float)p01.y,(float)p05.x,(float)p05.y);
      //SET_PCOLOR((p02.z + p06.z) / (2.0 * z));
      //m_pdc->draw_line((float)p02.x,(float)p02.y,(float)p06.x,(float)p06.y);
      //SET_PCOLOR((p03.z + p07.z) / (2.0 * z));
      //m_pdc->draw_line((float)p03.x,(float)p03.y,(float)p07.x,(float)p07.y);
      //SET_PCOLOR((p04.z + p08.z) / (2.0 * z));
      //m_pdc->draw_line((float)p04.x,(float)p04.y,(float)p08.x,(float)p08.y);

      return ia;
   }

   int_array ortho::draw_ortho_plain_fill(::box * pbox,int iHint,int bA,bool bFirst,::draw2d::dib * pdib)
   {
      ::draw2d::bitmap bm;

      point pt[3];

      int_array ia;

      double dA = bA / 255.0;

      array < point3d > p = pbox->vertices();
      array < int_array > f = pbox->faces();

      m_pdc->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::draw2d::pen_sp pen(m_pdc->allocer());

      double zmin = 1000000.0;
      double zmax = -1000000.0;

      index i;
      index j;

      for(i = 0; i < f.get_count(); i++)
      {
         for(j = 0; j < f[i].get_count(); j++)
         {
            if(p[f[i][j]].z < zmin)
               zmin = p[f[i][j]].z;
            else if(p[f[i][j]].z > zmax)
               zmax = p[f[i][j]].z;
         }
      }

      for(i = 0; i < p.get_count(); i++)
      {
         //for(j = 0; j < f[i].get_count(); j++)
         {

            p[i].z -= zmin;

         }

      }

      zmax -=zmin;

      double d;

      if(zmax <= 0.0)
         d = 0.0;
      else
         d = 1.0 / (zmax * 3.0);


      int iMax;

      i = 0;

      int_array iaf;

      ::lemon::array::set_sequence(iaf,0,5);


      while(f.get_count() > 0)
      {

         iMax = 0;

         for(j = 0; j < f.get_count(); j++)
         {

            if((p[f[j][0]].z + p[f[j][1]].z + p[f[j][2]].z) >(p[f[iMax][0]].z + p[f[iMax][1]].z + p[f[iMax][2]].z))
            {
               iMax = j;
            }

         }

         if((bFirst && i < 3) || (!bFirst && i >= 3))
         {

            int iFace = iaf[iMax];

            ia.add_unique(iFace);

            double r = (p[f[iMax][0]].z + p[f[iMax][1]].z + p[f[iMax][2]].z) * d;

            ::color ca;

            double dPeriod = (5000) * 11;

            if(iHint == 0)
            {

               ca.set_hls(fmod(::get_tick_count(),dPeriod) / dPeriod,0.84 - r / 2.0,1.0 - r);
            }
            else
            {
               ca.set_hls(fmod(::get_tick_count() + dPeriod / 2,dPeriod) / dPeriod,0.84 - r / 2.0,1.0 - r);
            }

            COLORREF clr = ca.get_rgb();


            /*pen->create_solid((1.05 - r) * 10.0,ARGB((int)(dA * (255.0 - r * 200.0)),ca.m_uchR,ca.m_uchG,ca.m_uchB));
            if(i < 6)
            {
            pen->m_etype = ::draw2d::pen::type_dot;
            }
            else
            {
            pen->m_etype = ::draw2d::pen::type_solid;
            }
            m_pdc->SelectObject(pen);*/

            pdib->Fill((int)(dA * (184.0 - r * 128.0)),ca.m_uchR,ca.m_uchG,ca.m_uchB);

            pt[0]=point((int64_t)p[f[iMax][0]].x,(int64_t)p[f[iMax][0]].y);
            pt[1]=point((int64_t)p[f[iMax][1]].x,(int64_t)p[f[iMax][1]].y);
            pt[2]=point((int64_t)p[f[iMax][2]].x,(int64_t)p[f[iMax][2]].y);

            m_pdc->PlgBlt(pt,pdib->get_graphics(),0,0,pdib->m_size.cx,pdib->m_size.cx,bm,0,0);
         }

         f.remove_at(iMax);
         iaf.remove_at(iMax);

         i++;

      }


      //pen->create_solid(1.0,ARGB(255,((int)(clr)),((int)(clr)),((int)(clr)))); m_pdc->SelectObject(pen)

      //SET_PCOLOR((p02.z + p03.z) / (2.0 * z));
      //m_pdc->draw_line((float)p02.x,(float)p02.y,(float)p03.x,(float)p03.y);
      //SET_PCOLOR((p03.z + p04.z) / (2.0 * z));
      //m_pdc->draw_line((float)p03.x,(float)p03.y,(float)p04.x,(float)p04.y);
      //SET_PCOLOR((p04.z + p01.z) / (2.0 * z));
      //m_pdc->draw_line((float)p04.x,(float)p04.y,(float)p01.x,(float)p01.y);

      //m_pdc->MoveTo(p05.x,p05.y);
      //SET_PCOLOR((p05.z + p06.z) / (2.0 * z));
      //m_pdc->LineTo(p06.x,p06.y);
      //SET_PCOLOR((p06.z + p07.z) / (2.0 * z));
      //m_pdc->LineTo(p07.x,p07.y);
      //SET_PCOLOR((p07.z + p08.z) / (2.0 * z));
      //m_pdc->LineTo(p08.x,p08.y);
      //SET_PCOLOR((p08.z + p05.z) / (2.0 * z));
      //m_pdc->LineTo(p05.x,p05.y);

      //SET_PCOLOR((p01.z + p05.z) / (2.0 * z));
      //m_pdc->draw_line((float)p01.x,(float)p01.y,(float)p05.x,(float)p05.y);
      //SET_PCOLOR((p02.z + p06.z) / (2.0 * z));
      //m_pdc->draw_line((float)p02.x,(float)p02.y,(float)p06.x,(float)p06.y);
      //SET_PCOLOR((p03.z + p07.z) / (2.0 * z));
      //m_pdc->draw_line((float)p03.x,(float)p03.y,(float)p07.x,(float)p07.y);
      //SET_PCOLOR((p04.z + p08.z) / (2.0 * z));
      //m_pdc->draw_line((float)p04.x,(float)p04.y,(float)p08.x,(float)p08.y);

      return ia;
   }


} // namespace draw3d





