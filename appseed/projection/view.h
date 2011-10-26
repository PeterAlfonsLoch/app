#pragma once

namespace projection
{

   class document;

   class CLASS_DECL_CA2_PROJECTION view :
      public ::userbase::view
   {
   public:

      class CLASS_DECL_CA2_PROJECTION plotter
      {
      public:


         double m_dLatitude0;
         double m_dLongitude0;


         double m_elevation0;
         double m_azimuth0;
         double m_cosElevation0;
         double m_sinElevation0;
         double m_cosAzimuth0;
         double m_sinAzimuth0;
         double m_dR;
         double m_dPi;
         double m_d90;
         double m_d270;

         double to_elevation(double latitude);
         double to_azimuth(double longitude);

         void set_latitude0(double latitude0);
         void set_longitude0(double longitude0);

      };



      class region_point
      {
      public:


         double   m_elevation;
         double   m_cosElevation;
         double   m_sinElevation;
         double   m_azimuth;
         double   m_cosAzimuth;
         double   m_sinAzimuth;


      };

      class CLASS_DECL_CA2_PROJECTION region
      {
      public:

         double_point_array            m_pta;
         raw_array < region_point >    m_regionpta;

         point_array                   m_ipta;
         bool                          m_bIgnore;

         point_array                   m_iptaBack;
         bool                          m_bIgnoreBack;

         double                        m_dLastLatitude0;
         double                        m_dLastLongitude0;
         double                        m_dLastR;
         
         double                        m_dLastBackLatitude0;
         double                        m_dLastBackLongitude0;
         double                        m_dLastBackR;

         void ortographic(plotter & plotter, double_point_array & pta);
         void back_ortographic(plotter & plotter, double_point_array & pta);
         void ortographic(plotter & plotter);
         void back_ortographic(plotter & plotter);
      };

      class CLASS_DECL_CA2_PROJECTION country
      {
      public:


         string         m_strName;
         string         m_strIso3;
         string         m_strIso2;
         string         m_strIso2Low;
         double         m_dLat;
         double         m_dLon;

         array_ptr_alloc < region > m_regiona;
         

         void add_region_part(plotter & plotter, var_array & varPart);

      };


      class CLASS_DECL_CA2_PROJECTION globe
      {
      public:

         
         bool                          m_bOk;
         array_ptr_alloc < country >   m_countrya;



         globe();

     

    
      };



      globe                m_globe;
      plotter              m_plotter;
      ::visual::dib_sp     m_dibSphere;
      ::visual::dib_sp     m_dibSphereBack;
      stringa              m_straCountries;
      stringa              m_straCountriesLow;
      ::ca::dib_sp         m_dibHit;
      ::ca::dib_sp         m_dibBuf;
      ::ca::dib_sp         m_dibBack;
      ::ca::dib_sp         m_dib;
      ::ca::dib_sp         m_dib2;
      ::ca::dib_sp         m_dib3;
      ::ca::pen_sp         m_penWhite;
      ::ca::brush_sp       m_brush84;
      ::ca::brush_sp       m_brushWhite;
      ::ca::brush_sp       m_brushYellow;
      ::ca::brush_sp       m_brushGreen;
      ::ca::brush_sp       m_brushGray;
      string               m_strCountrySel;
      
       


      string m_strServer;


      view(::ca::application * papp);
	   virtual ~view();

   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

      virtual void install_message_handling(::user::win::message::dispatch * pinterface);


      virtual void _001OnDraw(::ca::graphics * pdc);

      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

      document * get_document();

      string hit_test(point pt);


      country * get_country_by_iso2(const char * pszIso2);
      country * get_country_by_iso3(const char * pszIso3);


      DECL_GEN_SIGNAL(on_create)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnMouseMove)

   };

} // namespace projection
