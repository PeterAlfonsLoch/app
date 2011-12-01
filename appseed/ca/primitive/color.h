#pragma once



//#define  HLSMAX   100.0 /* H,L, and S vary over 0-HLSMAX */
//#define  RGBMAX   100.0   /* R,G, and B vary over 0-RGBMAX */
                        /* HLSMAX BEST IF DIVISIBLE BY 6 */
                        /* RGBMAX, HLSMAX must each fit in a byte. */
/* Hue is undefined if Saturation is 0 (grey-scale) */
/* This value determines where the Hue scrollbar is */
/* initially set for achromatic colors */
#define UNDEFINED_HUE (HLSMAX*2.0/3.0)

class CLASS_DECL_ca color  
{
public:
   double            m_dR;
   double            m_dG;
   double            m_dB;
   double            m_dA;
   unsigned char     m_uchR;
   unsigned char     m_uchG;
   unsigned char     m_uchB;
   unsigned char     m_uchA;

   class CLASS_DECL_ca hls
   {
   public:
      double m_dH;
      double m_dL;
      double m_dS;
   };

   color();
   color(const color & color);
   color(COLORREF cr);
   color(RGBQUAD quad);
   virtual ~color();

   void hls_mult(double dRateH, double dRateL, double dRateS);
   void hls_rate(double dRateH, double dRateL, double dRateS);
   void set_rgb(COLORREF cr);
   void set_bgr(DWORD dw);
   void set_rgbquad(RGBQUAD quad);
   void get_hls(
      double & dH,
      double & dL,
      double & dS) const;
      
   void set_hls(
      double dHue,
      double dLightness,
      double dSaturation);
   void hls_mult(hls & hls);
   void hls_rate(hls & hls);
   void get_hls(
      hls & hls) const;
   void set_hls(
      const hls & hls);

   DWORD get_rgb() const;
   DWORD get_bgr() const;
   DWORD get_rgba() const;
   DWORD get_bgra() const;
   RGBQUAD get_rgbquad() const;


   operator COLORREF() const;
   operator RGBQUAD() const;

   color & operator = (const color & color);
   color & operator = (COLORREF cr);
   color & operator = (RGBQUAD rgbquad);

};
