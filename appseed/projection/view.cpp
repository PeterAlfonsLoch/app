#include "StdAfx.h"
#include <math.h>


namespace projection
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::userbase::view(papp),
      m_dibSphere(get_app()),
      m_dibSphereBack(get_app()),
      m_dibHit(get_app()),
      m_dibBack(get_app()),
      m_dibBuf(get_app()),
      m_dib(get_app()),
      m_dib2(get_app()),
      m_dib3(get_app()),
      m_penWhite(get_app()),
      m_brush84(get_app()),
      m_brushWhite(get_app()),
      m_brushYellow(get_app()),
      m_brushGreen(get_app()),
      m_brushGray(get_app())
   {
      m_plotter.set_latitude0(0.0);
      m_plotter.set_longitude0(0.0);
      m_plotter.m_dR = 270;
      m_plotter.m_dPi = System.math().GetPi();
      m_plotter.m_d90 = m_plotter.m_dPi / 2.0;
      m_plotter.m_d270 = 3.0 * m_plotter.m_dPi / 2.0;
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

   void view::install_message_handling(::user::win::message::dispatch * pdispatch)
   {
      ::userbase::view::install_message_handling(pdispatch);
      USER_MESSAGE_LINK(message_create, pdispatch, this, &view::on_create);
      IGUI_WIN_MSG_LINK(WM_TIMER, pdispatch, this, &view::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pdispatch, this, &view::_001OnMouseMove);
   }



   void view::on_create(gen::signal_object * pobj)
   {
      pobj->previous();
      if(pobj->m_bRet)
         return;

      

      m_dibSphere.load_from_matter("image/green_globe_1.png");
      m_dibSphereBack.load_from_matter("image/green_globe_1_back.png");


      m_penWhite->CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

      m_brush84->CreateSolidBrush(RGB(84, 84, 84));
      m_brushWhite->CreateSolidBrush(RGB(255, 255, 255));

      m_brushYellow->CreateSolidBrush(RGB(120, 103, 51));
      m_brushGreen->CreateSolidBrush(RGB(52, 103, 51));
      m_brushGray->CreateSolidBrush(RGB(185, 185, 185));

      string strCountries;
      strCountries = Application.file().as_string("matter://uni/geo/countries.json");

      stringa straCountries;
      straCountries.explode("\n", strCountries);


      var_array varaCountries;
      var * pvarCountry;
      country * pcountry;

      varaCountries.set_size(straCountries.get_size() - 2);
//      MessageBox(NULL, "box1", "box1", MB_OK);

      for(int i = 1; i < straCountries.get_upper_bound(); i++)
      {
         string strLine = straCountries[i];
         strLine.trim();
         pvarCountry = varaCountries.ptr_at(i - 1);
         const char * pszJson = strLine;
         pvarCountry->parse_json(pszJson);
      }
  //    MessageBox(NULL, "box2", "box2", MB_OK);
      m_globe.m_countrya.set_size(varaCountries.get_size());

      for(int i = 0; i < varaCountries.get_size(); i++)
      {
         var & var = varaCountries[i];
         pcountry = m_globe.m_countrya.ptr_at(i);
         pcountry->m_strName    = var["info"]["name"];
         pcountry->m_strIso2    = var["info"]["iso2"];
         pcountry->m_strIso2Low = pcountry->m_strIso2;
         pcountry->m_strIso2Low.make_lower();
         pcountry->m_strIso3    = var["info"]["iso3"];
         pcountry->m_dLat       = var["info"]["lat"].get_double();
         pcountry->m_dLon       = var["info"]["lon"].get_double();
         for(int j = 0; j < var["parts"].propset().m_propertya.get_count(); j++)
         {
            pcountry->add_region_part(m_plotter, var["parts"].propset().m_propertya[j].get_value().vara());
         }
         
      }


      m_globe.m_bOk = true;

      SetTimer(15111984, 20, NULL);

   }
   void view::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(user::win::message::timer, ptimer, pobj);
      if(ptimer->m_nIDEvent == 15111984)
      {
         
      }
   }

   void view::_001OnMouseMove(gen::signal_object * pobj)
   {
      SCAST_PTR(user::win::message::mouse, pmouse, pobj);
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      
   }

   view::globe::globe()
   {
      m_bOk = false;
   }

   double view::plotter::to_elevation(double latitude)
   {
      return ((latitude + 90.0) / 180.0) * m_dPi - m_dPi/2.0;
   }
   
   double view::plotter::to_azimuth(double longitude)
   {
      return ((longitude + 180.0) / 360.0) * m_dPi * 2.0 - m_dPi;
   }

   void view::plotter::set_latitude0(double latitude0)
   {
      m_dLatitude0      = latitude0;
      m_elevation0      = to_elevation(latitude0);;
      m_sinElevation0   = sin(m_elevation0);
      m_cosElevation0   = cos(m_elevation0);
   }

   void view::plotter::set_longitude0(double longitude0)
   {
      m_dLongitude0     = longitude0;
      m_azimuth0        = to_azimuth(longitude0);
      m_sinAzimuth0     = sin(m_azimuth0);
      m_cosAzimuth0     = cos(m_azimuth0);
   }


   void view::region:: ortographic(plotter & plotter, double_point_array & pta)
   {
      double dR = plotter.m_dR;
//      double latitude;
//      double longitude;
//      double elevation;
//      double azimuth;
      double cosc;
      double xo;
      double yo;
      double theta;
      double x1;
      double y1;


      pta.set_size(m_pta.get_count());

      bool ignore = true;
      for(int i = 0; i < m_pta.get_count(); i++)
      {
         double cosAzimuthDiff = m_regionpta[i].m_cosAzimuth * plotter.m_cosAzimuth0  + m_regionpta[i].m_sinAzimuth * plotter.m_sinAzimuth0;
         double sinAzimuthDiff = m_regionpta[i].m_sinAzimuth * plotter.m_cosAzimuth0 - m_regionpta[i].m_cosAzimuth * plotter.m_sinAzimuth0;
         // work out if the point is visible
         cosc = m_regionpta[i].m_sinElevation*plotter.m_sinElevation0+plotter.m_cosElevation0*m_regionpta[i].m_cosElevation*cosAzimuthDiff;
         if(cosc >= 0.0)
         {
               // this point is visible, so do not ignore this region
               ignore = false;
         }
         // orthographic projection
         xo = dR * m_regionpta[i].m_cosElevation * sinAzimuthDiff;
         yo = -dR * ((plotter.m_cosElevation0 * m_regionpta[i].m_sinElevation)-plotter.m_sinElevation0*m_regionpta[i].m_cosElevation*cosAzimuthDiff);
         if(cosc < 0.0)
         {
               // this point is on the far side of the globe.  Truncate it to lie on the rim.
               theta = atan2(yo,xo);
               double cosTheta = cos(theta);
               double sinTheta = sin(theta);
               x1 = dR + dR * cosTheta;
               y1 = dR + dR * sinTheta;
               pta[i].x = x1;
               pta[i].y = y1;
         }
         else
         {
               pta[i].x = dR + xo;
               pta[i].y = dR + yo;
         }
      }
      if(ignore)
      {
         pta.remove_all();
      }
   }


   void view::region::back_ortographic(plotter & plotter, double_point_array & pta)
   {
      double dR = plotter.m_dR;
//      double latitude;
//      double longitude;
//      double elevation;
//      double azimuth;
      double cosc;
      double xo;
      double yo;
      double theta;
      double x1;
      double y1;


      pta.set_size(m_pta.get_count());

      bool ignore = true;
      for(int i = 0; i < m_pta.get_count(); i++)
      {
         double cosAzimuthDiff = m_regionpta[i].m_cosAzimuth * plotter.m_cosAzimuth0  + m_regionpta[i].m_sinAzimuth * plotter.m_sinAzimuth0;
         double sinAzimuthDiff = m_regionpta[i].m_sinAzimuth * plotter.m_cosAzimuth0 - m_regionpta[i].m_cosAzimuth * plotter.m_sinAzimuth0;
         // work out if the point is visible
         cosc = m_regionpta[i].m_sinElevation*plotter.m_sinElevation0+plotter.m_cosElevation0*m_regionpta[i].m_cosElevation*cosAzimuthDiff;
         if(cosc <= 0.0)
         {
               // this point is visible, so do not ignore this region
               ignore = false;
         }
         // orthographic projection
         xo = dR * m_regionpta[i].m_cosElevation * sinAzimuthDiff;
         yo = -dR * ((plotter.m_cosElevation0 * m_regionpta[i].m_sinElevation)-plotter.m_sinElevation0*m_regionpta[i].m_cosElevation*cosAzimuthDiff);
         if(cosc > 0.0)
         {
               // this point is on the far side of the globe.  Truncate it to lie on the rim.
               theta = atan2(yo,xo);
               double cosTheta = cos(theta);
               double sinTheta = sin(theta);
               x1 = dR + dR * cosTheta;
               y1 = dR + dR * sinTheta;
               pta[i].x = x1;
               pta[i].y = y1;
         }
         else
         {
               pta[i].x = dR + xo;
               pta[i].y = dR + yo;
         }
      }
      if(ignore)
      {
         pta.remove_all();
      }
   }

   void view::region:: ortographic(plotter & plotter)
   {
      double dR = plotter.m_dR;
//      double latitude;
//      double longitude;
//      double elevation;
//      double azimuth;
      double cosc;
      double xo;
      double yo;
      double theta;
      double x1;
      double y1;

      if(m_ipta.get_size()    == m_pta.get_count()
      && m_dLastLatitude0     == plotter.m_dLatitude0
      && m_dLastLongitude0    == plotter.m_dLongitude0
      && m_dLastR             == plotter.m_dR)
         return;

      m_ipta.set_size(m_pta.get_count());
      m_dLastLatitude0     = plotter.m_dLatitude0;
      m_dLastLongitude0    = plotter.m_dLongitude0;
      m_dLastR             = plotter.m_dR;

      m_bIgnore = true;
      for(int i = 0; i < m_pta.get_count(); i++)
      {
         double cosAzimuthDiff = m_regionpta[i].m_cosAzimuth * plotter.m_cosAzimuth0  + m_regionpta[i].m_sinAzimuth * plotter.m_sinAzimuth0;
         double sinAzimuthDiff = m_regionpta[i].m_sinAzimuth * plotter.m_cosAzimuth0 - m_regionpta[i].m_cosAzimuth * plotter.m_sinAzimuth0;
         // work out if the point is visible
         cosc = m_regionpta[i].m_sinElevation*plotter.m_sinElevation0+plotter.m_cosElevation0*m_regionpta[i].m_cosElevation*cosAzimuthDiff;
         if(m_bIgnore && cosc >= 0.0)
         {
               // this point is visible, so do not ignore this region
               m_bIgnore = false;
         }
         // orthographic projection
         xo = dR * m_regionpta[i].m_cosElevation * sinAzimuthDiff;
         yo = -dR * ((plotter.m_cosElevation0 * m_regionpta[i].m_sinElevation)-plotter.m_sinElevation0*m_regionpta[i].m_cosElevation*cosAzimuthDiff);
         if(cosc < 0.0)
         {
               // this point is on the far side of the globe.  Truncate it to lie on the rim.
               theta = atan2(yo,xo);
               double cosTheta = cos(theta);
               double sinTheta = sin(theta);
               x1 = dR + dR * cosTheta;
               y1 = dR + dR * sinTheta;
               m_ipta[i].x = (LONG) x1;
               m_ipta[i].y = (LONG) y1;
         }
         else
         {
               m_ipta[i].x = (LONG) (dR + xo);
               m_ipta[i].y = (LONG) (dR + yo);
         }
      }
   }

   void view::region::back_ortographic(plotter & plotter)
   {
      double dR = plotter.m_dR;
//      double latitude;
//      double longitude;
//      double elevation;
//      double azimuth;
      double cosc;
      double xo;
      double yo;
      double theta;
      double x1;
      double y1;

      if(m_iptaBack.get_size()    == m_pta.get_count()
      && m_dLastBackLatitude0     == plotter.m_dLatitude0
      && m_dLastBackLongitude0    == plotter.m_dLongitude0
      && m_dLastBackR             == plotter.m_dR)
         return;

      m_iptaBack.set_size(m_pta.get_count());
      m_dLastBackLatitude0       = plotter.m_dLatitude0;
      m_dLastBackLongitude0      = plotter.m_dLongitude0;
      m_dLastBackR               = plotter.m_dR;


      m_bIgnoreBack = true;
      for(int i = 0; i < m_pta.get_count(); i++)
      {
         double cosAzimuthDiff = m_regionpta[i].m_cosAzimuth * plotter.m_cosAzimuth0  + m_regionpta[i].m_sinAzimuth * plotter.m_sinAzimuth0;
         double sinAzimuthDiff = m_regionpta[i].m_sinAzimuth * plotter.m_cosAzimuth0 - m_regionpta[i].m_cosAzimuth * plotter.m_sinAzimuth0;
         // work out if the point is visible
         cosc = m_regionpta[i].m_sinElevation*plotter.m_sinElevation0+plotter.m_cosElevation0*m_regionpta[i].m_cosElevation*cosAzimuthDiff;
         if(m_bIgnoreBack && cosc <= 0.0)
         {
               // this point is visible, so do not ignore this region
               m_bIgnoreBack = false;
         }
         // orthographic projection
         xo = dR * m_regionpta[i].m_cosElevation * sinAzimuthDiff;
         yo = -dR * ((plotter.m_cosElevation0 * m_regionpta[i].m_sinElevation)-plotter.m_sinElevation0*m_regionpta[i].m_cosElevation*cosAzimuthDiff);
         if(cosc > 0.0)
         {
               // this point is on the far side of the globe.  Truncate it to lie on the rim.
               theta = atan2(yo,xo);
               double cosTheta = cos(theta);
               double sinTheta = sin(theta);
               x1 = dR + dR * cosTheta;
               y1 = dR + dR * sinTheta;
               m_iptaBack[i].x = (LONG) x1;
               m_iptaBack[i].y = (LONG) y1;
         }
         else
         {
               m_iptaBack[i].x = (LONG) (dR + xo);
               m_iptaBack[i].y = (LONG) (dR + yo);
         }
      }
   }

   void view::country::add_region_part(plotter & plotter, var_array & vara)
   {
      region * pregion = m_regiona.add_new();
      region_point regionpt;
      for(int i = 0; i < vara.get_count(); i++)
      {
         double x = vara[i][1].get_double();
         double y = vara[i][0].get_double();
         pregion->m_pta.add(x, y);
         regionpt.m_elevation       = plotter.to_elevation(x);
         regionpt.m_cosElevation    = cos(regionpt.m_elevation);
         regionpt.m_sinElevation    = sin(regionpt.m_elevation);
         regionpt.m_azimuth         = plotter.to_azimuth(y);
         regionpt.m_cosAzimuth      = cos(regionpt.m_azimuth);
         regionpt.m_sinAzimuth      = sin(regionpt.m_azimuth);
         pregion->m_regionpta.add(regionpt);
      }
   }



   void view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }


   string view::hit_test(point pt) 
   {

      if(!m_globe.m_bOk)
         return "";

      int cx = (int) (m_plotter.m_dR * 2.0);
      int cy = (int) (m_plotter.m_dR * 2.0);

      int iCount = m_globe.m_countrya.get_count();

      ::ca::brush_sp brush(get_app());
      brush->CreateSolidBrush(RGB(255, 255, 255));
      m_dibHit->create(cx, cy);
      m_dibHit->get_graphics()->SelectObject(brush);
      m_dibHit->get_graphics()->SelectObject(::GetStockObject(NULL_PEN));
      for(int i = 0; i < iCount; i++)
      {
         country & country = m_globe.m_countrya[i];
         for(int j = 0; j < country.m_regiona.get_count(); j++)
         {
            region & region = country.m_regiona[j];
            region.ortographic(m_plotter);
            if(region.m_ipta.get_count() >= 2 && !region.m_bIgnore && region.m_ipta.bounding_rect_contains_pt(pt))
            {
               m_dibHit->Fill(0, 0, 0, 0);
               m_dibHit->get_graphics()->Polygon(region.m_ipta.get_data(), region.m_ipta.get_count());
               if(m_dibHit->get_data()[pt.x + pt.y * cy] != 0)
                  return country.m_strIso2;
            }
         }
      }

      for(int i = 0; i < iCount; i++)
      {
         country & country = m_globe.m_countrya[i];
         string strName = country.m_strName;
         for(int j = 0; j < country.m_regiona.get_count(); j++)
         {
            region & region = country.m_regiona[j];
            region.back_ortographic(m_plotter);
            if(region.m_iptaBack.get_count() >= 2 && !region.m_bIgnoreBack && region.m_iptaBack.bounding_rect_contains_pt(pt))
            {
               m_dibHit->Fill(0, 0, 0, 0);
               m_dibHit->get_graphics()->Polygon(region.m_iptaBack.get_data(), region.m_iptaBack.get_count());
               if(m_dibHit->get_data()[pt.x + pt.y * cy] != 0)
                  return country.m_strIso2;
            }
         }
      }

      return "";
   }



   void view:: _001OnDraw(::ca::graphics * pdcScreen)
   {

      if(!m_globe.m_bOk)
         return;

      m_plotter.set_longitude0(::GetTickCount() / 200.0);

      point pt;

      Application.get_cursor_pos(&pt);

      ScreenToClient(&pt);

      string strCountry = hit_test(pt);



      int cx = (int) (m_plotter.m_dR * 2.0);
      int cy = (int) (m_plotter.m_dR * 2.0);

      int iCount = m_globe.m_countrya.get_count();

      m_dibBack->create(cx, cy);
      m_dibBuf->create(cx, cy);
      m_dib->create(cx, cy);
      m_dib->get_graphics()->SelectObject(m_penWhite);
      m_dib->get_graphics()->SelectObject(::GetStockObject(NULL_BRUSH));
      m_dib2->create(cx, cy);
      m_dib2->get_graphics()->SelectObject(::GetStockObject(NULL_PEN));
      m_dib2->get_graphics()->SetPolyFillMode(WINDING);
      m_dib3->create(cx, cy);
      m_dib3->get_graphics()->SelectObject(::GetStockObject(NULL_PEN));
      m_dib3->get_graphics()->SetPolyFillMode(WINDING);

      ::ca::graphics * pdc = m_dibBuf->get_graphics();

      pdc->BitBlt(0, 0, cx, cy, pdcScreen, 0, 0, SRCCOPY);

      if(m_straCountries.get_size() > 0)
      {
         if(strCountry.has_char() && m_straCountries.contains_ci(strCountry))
         {
            m_strCountrySel = strCountry;
         }
         else
         {
            m_strCountrySel.Empty();
         }
         m_strCountrySel.make_lower();
         
         m_dibBuf->copy(m_dibBack);
         m_dib->Fill(0, 0, 0, 0);
         m_dib2->Fill(0, 0, 0, 0);
         m_dib2->get_graphics()->SelectObject(m_brush84);
         m_dib3->Fill(0, 0, 0, 0);

         enum e_brush
         {
            brush_none,
            brush_yellow,
            brush_green,
            brush_gray,
         } ebrush;
         ebrush = brush_none;
         bool bSelGone  = false;
         stringa straCountries = m_straCountriesLow;
         for(int i = 0; i < iCount; i++)
         {
            country & country = m_globe.m_countrya[i];
            string strName = country.m_strName;
            if(!bSelGone && country.m_strIso2Low.Compare(m_strCountrySel) == 0)
            {
               if(ebrush != brush_yellow)
               {
                  ebrush = brush_yellow;
                  m_dib3->get_graphics()->SelectObject(m_brushYellow);
               }
            }
            else if(straCountries.get_count() > 0 && straCountries.contains(country.m_strIso2Low))
            {
               straCountries.remove(country.m_strIso2Low);
               if(ebrush != brush_green)
               {
                  ebrush = brush_green;
                  m_dib3->get_graphics()->SelectObject(m_brushGreen);
               }
            }
            else
            {
               if(ebrush != brush_gray)
               {
                  ebrush = brush_gray;
                  m_dib3->get_graphics()->SelectObject(m_brushGray);
               }
            }
            for(int j = 0; j < country.m_regiona.get_count(); j++)
            {
               region & region = country.m_regiona[j];
               region.back_ortographic(m_plotter);
               if(region.m_iptaBack.get_count() >= 2 && !region.m_bIgnoreBack)
               {
                  m_dib->get_graphics()->Polygon(region.m_iptaBack.get_data(), region.m_iptaBack.get_count());
                  m_dib2->get_graphics()->Polygon(region.m_iptaBack.get_data(), region.m_iptaBack.get_count());
                  m_dib3->get_graphics()->Polygon(region.m_iptaBack.get_data(), region.m_iptaBack.get_count());
               }
            }
         }
         //m_dib->channel_copy(visual::rgba::channel_alpha, visual::rgba::channel_green);
         //m_dib2->channel_copy(visual::rgba::channel_alpha, visual::rgba::channel_green);

         //m_dibBuf->Blend(
         //System.imaging().bitmap_blend(pdc, point(0, 0), size(cx, cy), m_dib3->get_graphics(), point(0, 0), m_dib2->get_graphics(), point(0, 0));
         //System.imaging().bitmap_blend(pdc, point(0, 0), size(cx, cy), m_dibBack->get_graphics(), point(0, 0), m_dib->get_graphics(), point(0, 0));
         m_dibBuf->blend(m_dib3, m_dib2);
         m_dibBuf->blend(m_dibBack, m_dib);








         m_dibBuf->copy(m_dibBack);
         m_dib->Fill(0, 0, 0, 0);
         m_dib2->Fill(0, 0, 0, 0);
         m_dib2->get_graphics()->SelectObject(m_brushWhite);
         m_dib3->Fill(0, 0, 0, 0);
         straCountries = m_straCountriesLow;

         bSelGone  = false;
         for(int i = 0; i < iCount; i++)
         {
            country & country = m_globe.m_countrya[i];
            string strName = country.m_strName;
            if(!bSelGone && country.m_strIso2Low.Compare(m_strCountrySel) == 0)
            {
               if(ebrush != brush_yellow)
               {
                  ebrush = brush_yellow;
                  m_dib3->get_graphics()->SelectObject(m_brushYellow);
               }
            }
            else if(straCountries.get_count() > 0 && straCountries.contains(country.m_strIso2Low))
            {
               straCountries.remove(country.m_strIso2Low);
               if(ebrush != brush_green)
               {
                  ebrush = brush_green;
                  m_dib3->get_graphics()->SelectObject(m_brushGreen);
               }
            }
            else
            {
               if(ebrush != brush_gray)
               {
                  ebrush = brush_gray;
                  m_dib3->get_graphics()->SelectObject(m_brushGray);
               }
            }
            for(int j = 0; j < country.m_regiona.get_count(); j++)
            {
               region & region = country.m_regiona[j];
               region.ortographic(m_plotter);
               if(region.m_ipta.get_count() >= 2 && !region.m_bIgnore)
               {
                  m_dib->get_graphics()->Polygon(region.m_ipta.get_data(), region.m_ipta.get_count());
                  m_dib2->get_graphics()->Polygon(region.m_ipta.get_data(), region.m_ipta.get_count());
                  m_dib3->get_graphics()->Polygon(region.m_ipta.get_data(), region.m_ipta.get_count());
               }
            }
         }
         /*m_dib->channel_copy(visual::rgba::channel_alpha, visual::rgba::channel_green);
         m_dib2->channel_copy(visual::rgba::channel_alpha, visual::rgba::channel_green);


         System.imaging().bitmap_blend(pdc, point(0, 0), size(cx, cy), m_dib3->get_graphics(), point(0, 0), m_dib2->get_graphics(), point(0, 0));
         System.imaging().bitmap_blend(pdc, point(0, 0), size(cx, cy), m_dibBack->get_graphics(), point(0, 0), m_dib->get_graphics(), point(0, 0));*/

         m_dibBuf->blend(m_dib3, m_dib2);
         m_dibBuf->blend(m_dibBack, m_dib);

      }
      else
      {

         m_strCountrySel = strCountry;

         m_dibBack->get_graphics()->BitBlt(0, 0, cx, cy, pdc, 0, 0, SRCCOPY);
         m_dib->get_graphics()->FillSolidRect(0, 0, cx, cy, 0);
         m_dib2->get_graphics()->SelectObject(m_brush84);


         for(int i = 0; i < iCount; i++)
         {
            country & country = m_globe.m_countrya[i];
            string strName = country.m_strName;
            for(int j = 0; j < country.m_regiona.get_count(); j++)
            {
               region & region = country.m_regiona[j];
               region.back_ortographic(m_plotter);
               if(region.m_iptaBack.get_count() >= 2 && !region.m_bIgnoreBack)
               {
                  m_dib->get_graphics()->Polygon(region.m_iptaBack.get_data(), region.m_iptaBack.get_count());
                  m_dib2->get_graphics()->Polygon(region.m_iptaBack.get_data(), region.m_iptaBack.get_count());
               }
            }
         }
         m_dib->channel_copy(visual::rgba::channel_alpha, visual::rgba::channel_green);
         m_dib2->channel_copy(visual::rgba::channel_alpha, visual::rgba::channel_green);


         System.imaging().bitmap_blend(pdc, point(0, 0), size(cx, cy), m_dibSphereBack->get_graphics(), point(0, 0), m_dib2->get_graphics(), point(0, 0));
         System.imaging().bitmap_blend(pdc, point(0, 0), size(cx, cy), m_dibBack->get_graphics(), point(0, 0), m_dib->get_graphics(), point(0, 0));






         m_dibBack->get_graphics()->BitBlt(0, 0, cx, cy, pdc, 0, 0, SRCCOPY);
         m_dib->get_graphics()->FillSolidRect(0, 0, cx, cy, 0);
         m_dib2->get_graphics()->FillSolidRect(0, 0, cx, cy, 0);
         m_dib2->get_graphics()->SelectObject(m_brushWhite);
         for(int i = 0; i < iCount; i++)
         {
            country & country = m_globe.m_countrya[i];
            string strName = country.m_strName;
            for(int j = 0; j < country.m_regiona.get_count(); j++)
            {
               region & region = country.m_regiona[j];
               region.ortographic(m_plotter);
               if(region.m_ipta.get_count() >= 2 && !region.m_bIgnore)
               {
                  m_dib->get_graphics()->Polygon(region.m_ipta.get_data(), region.m_ipta.get_count());
                  m_dib2->get_graphics()->Polygon(region.m_ipta.get_data(), region.m_ipta.get_count());
               }
            }
         }
         m_dib->channel_copy(visual::rgba::channel_alpha, visual::rgba::channel_green);
         m_dib2->channel_copy(visual::rgba::channel_alpha, visual::rgba::channel_green);





         System.imaging().bitmap_blend(pdc, point(0, 0), size(cx, cy), m_dibSphere->get_graphics(), point(0, 0), m_dib2->get_graphics(), point(0, 0));
         System.imaging().bitmap_blend(pdc, point(0, 0), size(cx, cy), m_dibBack->get_graphics(), point(0, 0), m_dib->get_graphics(), point(0, 0));
      }

      pdcScreen->BitBlt(0, 0, cx, cy, pdc, 0, 0, SRCCOPY);

      if(m_strCountrySel.has_char())
      {
         country * pcountry = get_country_by_iso2(m_strCountrySel);
         string strName = pcountry->m_strName;
         pdcScreen->TextOut(0, 0, strName);
      }

   }



   document * view::get_document()
   {
      return dynamic_cast < document * > (::userbase::view::get_document());
   }


   view::country * view::get_country_by_iso2(const char * pszIso2)
   {
      for(int i = 0; i < m_globe.m_countrya.get_size(); i++)
      {
         if(m_globe.m_countrya[i].m_strIso2.CompareNoCase(pszIso2) == 0)
            return m_globe.m_countrya.ptr_at(i);
      }
      return NULL;
   }

   view::country * view::get_country_by_iso3(const char * pszIso3)
   {
      for(int i = 0; i < m_globe.m_countrya.get_size(); i++)
      {
         if(m_globe.m_countrya[i].m_strIso3.CompareNoCase(pszIso3) == 0)
            return m_globe.m_countrya.ptr_at(i);
      }
      return NULL;
   }


} // namespace projection
