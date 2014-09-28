#include "framework.h"
#include <math.h>

double primitive_color_round(double d);

color::color()
{
}

color::color(const color & color)
{
   operator = (color);
}

color::color(COLORREF cr)
{
   operator = (cr);
}

color::color(RGBQUAD quad)
{
   operator = (quad);
}

color::~color()
{

}

/*

proc hls2rgb {h l s} {
    # Posted by frederic.bonnet@ciril.fr
    # h, l and s are floats between 0.0 and 1.0, ditto for r, g and b
    # h = 0   => red
    # h = 1/3 => green
    # h = 2/3 => blue

    set h6 [expr {($h-floor($h))*6}]
    set r [expr {  $h6 <= 3 ? 2-$h6
                            : $h6-4}]
    set g [expr {  $h6 <= 2 ? $h6
                            : $h6 <= 5 ? 4-$h6
                            : $h6-6}]
1    set b [expr {  $h6 <= 1 ? -$h6
                            : $h6 <= 4 ? $h6-2
                            : 6-$h6}]
    set r [expr {$r < 0.0 ? 0.0 : $r > 1.0 ? 1.0 : double($r)}]
    set g [expr {$g < 0.0 ? 0.0 : $g > 1.0 ? 1.0 : double($g)}]
    set b [expr {$b < 0.0 ? 0.0 : $b > 1.0 ? 1.0 : double($b)}]

    set r [expr {(($r-1)*$s+1)*$l}]
    set g [expr {(($g-1)*$s+1)*$l}]
    set b [expr {(($b-1)*$s+1)*$l}]
    return [list $r $g $b]
}

  */

void color::get_hls(
   double & dHParam, double & dLParam, double & dSParam) const
{

   double dR = m_dR;
   double dG = m_dG;
   double dB = m_dB;


   double dCMin = MIN(dR, MIN(dG, dB));;
   double dCMax = MAX(dR, MAX(dG, dB));
   double dA;

   if(dR > dB)
   {
      // Red component intensity is
      // greater than blue component intensity.
      if(dG > dB)
      {
         // Blue component intensity is minimum.
         // The hue must be between (0 / 6) and (2 / 6)
         if(dR > dG)
         {
            // Red component intensity is maximum.
            // The hue goes from red to yellow.
            // The hue must be between (0 / 6) and (1 / 6)
            dA = (dG - dB) / (dR - dB);
            dHParam = dA / 6.0;
         }
         else if(dG > dR)
         {
            // Green component intensity is maximum.
            // The hue goes from yellow to green.
            // The hue must be between (1 / 6) and (2 / 6)
            dA = (dR - dB) / (dG - dB);
            dHParam = (dA + 1.0) / 6.0;
         }
         else // if(dG == dR)
         {
            // Green component intensity is equal
            // red component intensity.
            // The blue component is minimum.
            // The color is yellow-ish
            dHParam = 1.0 / 6.0;
         }
      }
      else if(dG == dB)
      {
         // Green component intensity is equal
         // blue component intensity.
         // The color is red-ish
         dHParam = 0.0 / 6.0;
      }
      else // if(dB > dG)
      {
         // Green component intensity is minimum.
         // Red component intensity is maximum.
         // The color go from magenta to red.
         // The hue must be between (5 / 6) and (6 / 6)
         dA = (dB - dG) / (dR - dG);
         dHParam = (dA + 5.0) / 6.0;
      }
   }
   else if(dB > dR)
   {
      // Blue component intensity is
      // greater than red component intensity.
      if(dG > dB)
      {
         // Red component intensity is minimum.
         // Green component intensity is maximum.
         // The color go from green to cyan.
         // The hue must be between (2 / 6) and (3 / 6)
         dA = (dB - dR) / (dG - dR);
         dHParam = (dA + 2.0) / 6.0;
      }
      else if(dB > dG)
      {
         // Blue component intensity is maximum.
         if(dG > dR)
         {
            // Red component intensity is mimimum.
            // The hue goes from cyan to blue.
            // The hue must be between (3 / 6) and (4 / 6)
            dA = (dG - dR) / (dB - dR);
            dHParam = (dA + 3.0) / 6.0;
         }
         else if(dR > dG)
         {
            // Green component intensity is minimum.
            // The hue goes from blue to magenta.
            // The hue must be between (4 / 6) and (5 / 6)
            dA = (dR - dG) / (dB - dG);
            dHParam = (dA + 4.0) / 6.0;
         }
         else // if(dG == dR)
         {
            // Green component intensity is equal
            // red component intensity.
            // The color is blue-ish
            dHParam = 4.0 / 6.0;
            return;
         }
      }
      else // if(dG == dB)
      {
         // Green component intensity is equal
         // blue component intensity.
         // The red component intensity is minimum.
         // The color is cyan-ish
         dHParam = 3.0 / 6.0;
         return;
      }
   }
   else // if(dR == dB)
   {
      // Red and blue components have equal intensity
      if(dG > dR)
      {
         // The color is green-ish
         dHParam = 2.0 / 6.0;
      }
      else if(dG < dR)
      {
         // The color is magenta-ish
         dHParam = 5.0 / 6.0;
      }
      else // if(dG == dR)
      {
         // All colors have the same intensity
         dHParam = 0.0;
         dLParam = dR;
         dSParam = 0.0;
         return;
      }
   }

   double dCDiff = dCMax - dCMin;
   double dCSum = dCMax + dCMin;
   dLParam = dCSum / 2.0;
   dSParam = dLParam < 0.5 ?
              dCDiff / dCSum :
           dCDiff / (2.0 - dCSum);




}

/* utility routine for HLStoRGB */

/*double HueToRGB(
   double d1,
   double d2,
   double dHue)
{
   /* range check: note values passed add/subtract thirds of range */
/*   if (dHue < 0.0)
      dHue += HLSMAX;
   if (dHue > HLSMAX)
      dHue -= HLSMAX;
   /* return r,g, or b value from this tridrant */
/*   if (dHue < (HLSMAX/6))
      return ( d1 + (((d2-d1)*dHue+(HLSMAX/12))/(HLSMAX/6)) );
   if (dHue < (HLSMAX/2))
      return ( d2 );
   if (dHue < ((HLSMAX*2)/3))
      return ( d1 + (((d2-d1)*(((HLSMAX*2)/3)-dHue)+(HLSMAX/12))/(HLSMAX/6)));
   else
      return ( d1 );
} */

double primitive_color_round(double d)
{
   double n;
   double f;
   f = modf(d, &n);
   if(f > 0.5)
      return n + 1.0;
   else if(f < - 0.5)
      return n - 1.0;
   else
      return n;
}

#define dsin(x) (sin(((x) *2.0 * 3.1415) / 360.0))

void color::set_hls(
   double dH,
   double dL,
   double dS)
{
   ASSERT(dH >= 0.0);
   ASSERT(dH <= 1.0);
   ASSERT(dL >= 0.0);
   ASSERT(dL <= 1.0);
   ASSERT(dS >= 0.0);
   ASSERT(dS <= 1.0);


   double dR, dG, dB;


   if(dH >= 1.0)
      dH = 0.0;
   else if(dH < 0.0)
      dH = 0.0;

   if(dL > 1.0)
      dL = 1.0;
   else if(dL < 0.0)
      dL = 0.0;

   if(dS > 1.0)
      dS = 1.0;
   else if(dS < 0.0)
      dS = 0.0;


   dH *= 6.0;

   double dA = dH - (double) ((int32_t) dH);

   if(dH >= 3.0)
   {
      if(dH >= 4.0)
      {
         if(dH >= 5.0)
         {
            // 5.0
            // magenta to red
            dR = 1.0;
            dG = 0.0;
            dB = 1.0 - dA;
         }
         else
         {
            // 4.0
            // blue to magenta
            dR = dA;
            dG = 0.0;
            dB = 1.0;
         }
      }
      else
      {
         // 3.0
         // cyan to blue
         dR = 0.0;
         dG = 1.0 - dA;
         dB = 1.0;
      }
   }
   else /// if(dH >= 0.0)
   {
      if(dH >= 2.0)
      {
         // 2
         // green to cyan
         dR = 0.0;
         dG = 1.0;
         dB = dA;
      }
      else // (dH >= 0.0 && dH < 2.0)
      {
         if(dH >= 1.0)
         {
            // 1
            // yellow to green
            dR = 1.0 - dA;
            dG = 1.0;
            dB = 0.0;
         }
         else // if(dh >= 0 && dH < 1.0);
         {
            // 0
            // red to yellow
            dR = 1.0;
            dG = dA;
            dB = 0.0;
         }
      }
   }

   double dCMin;
   double dCAdd;
   double dSL = dS * dL;
   if(dL >= 0.5)
   {
      dCMin = dL - dS + dSL;
      dCAdd = 2.0 * dS - 2.0 * dSL;
   }
   else
   {
      dCMin = dL - dSL;
      dCAdd = 2.0 * dSL;
   }


   m_dR      = (dCMin + dR * dCAdd);
   m_dG      = (dCMin + dG * dCAdd);
   m_dB      = (dCMin + dB * dCAdd);

   m_uchR      = (BYTE) primitive_color_round(m_dR * 255.0);
   m_uchG      = (BYTE) primitive_color_round(m_dG * 255.0);
   m_uchB      = (BYTE) primitive_color_round(m_dB * 255.0);

/*   double H = dH * 360.0;


   double d360 = dsin(360.0);

   double R1 = dsin(H) * dL;
   double G1 = dsin(H + 120.0) * dL;
   double B1 = dsin(H + 240.0) * dL;

   double AVERAGE = (R1 + G1 + B1) / 3;

   m_dR = ((R1 - AVERAGE) * dS) + AVERAGE;
   m_dG = ((G1 - AVERAGE) * dS) + AVERAGE;
   m_dB = ((B1 - AVERAGE) * dS) + AVERAGE;

   m_uchR      = (BYTE)primitive_color_round(m_dR * 255.0);
   m_uchG      = (BYTE)primitive_color_round(m_dG * 255.0);
   m_uchB      = (BYTE)primitive_color_round(m_dB * 255.0);*/

}

uint32_t color::get_rgb() const
{
   return m_uchR | (m_uchG << 8) | (m_uchB << 16);
}

uint32_t color::get_bgr() const
{
   return m_uchB | (m_uchG << 8) | (m_uchR << 16);
}

uint32_t color::get_rgba() const
{
   return m_uchR | (m_uchG << 8) | (m_uchB << 16) | (m_uchA << 24);
}

uint32_t color::get_bgra() const
{
   return m_uchB | (m_uchG << 8) | (m_uchR << 16) | (m_uchA << 24);
}

RGBQUAD color::get_rgbquad() const
{
   RGBQUAD quad;
   quad.rgbBlue      = m_uchB;
   quad.rgbGreen     = m_uchG;
   quad.rgbRed       = m_uchR;
   quad.rgbReserved  = m_uchA;
   return quad;
}

color::operator COLORREF() const
{
   return get_rgba();
}

color::operator RGBQUAD() const
{
   return get_rgbquad();
}

void color::set_rgb(COLORREF cr)
{
   m_uchR   = rgb_get_r_value(cr);
   m_uchG   = rgb_get_g_value(cr);
   m_uchB   = rgb_get_b_value(cr);
   m_uchA   = rgb_get_a_value(cr);
   m_dR     = m_uchR / 255.0;
   m_dG     = m_uchG / 255.0;
   m_dB     = m_uchB / 255.0;
   m_dA     = m_uchA / 255.0;
}

void color::set_bgr(uint32_t bgr)
{
   m_uchR   = bgr_get_r_value(bgr);
   m_uchG   = bgr_get_g_value(bgr);
   m_uchB   = bgr_get_b_value(bgr);
   m_uchA   = bgr_get_a_value(bgr);
   m_dR     = m_uchR / 255.0;
   m_dG     = m_uchG / 255.0;
   m_dB     = m_uchB / 255.0;
   m_dA     = m_uchA / 255.0;
}


void color::set_rgbquad(RGBQUAD quad)
{
   m_uchR   = quad.rgbRed;
   m_uchG   = quad.rgbGreen;
   m_uchB   = quad.rgbBlue;
   m_uchA   = quad.rgbReserved;
   m_dR     = m_uchR / 255.0;
   m_dG     = m_uchG / 255.0;
   m_dB     = m_uchB / 255.0;
   m_dA     = m_uchA / 255.0;
}

void color::hls_rate(double dRateH, double dRateL, double dRateS)
{
    double dH, dL, dS;

    get_hls(dH, dL, dS);

    dH = dRateH >= 0 ?
       (1.0 - dH) * dRateH + dH :
       (1.0 + dRateH) * dH;
    dL = dRateL >= 0 ?
       (1.0 - dL) * dRateL + dL :
       (1.0 + dRateL) * dL;
    dS = dRateS >= 0 ?
       (1.0 - dS) * dRateS + dS :
       (1.0 + dRateS) * dS;

    if(dH > 1.0)
        dH = 1.0;
    else if(dH < 0.0)
        dH = 0.0;

    if(dL > 1.0)
        dL = 1.0;
    else if(dL < 0.0)
        dL = 0.0;

    if(dS > 1.0)
        dS = 1.0;
    else if(dS < 0.0)
        dS = 0.0;

    set_hls(dH, dL, dS);
}

void color::hls_mult(double dMultH, double dMultL, double dMultS)
{
    double dH, dL, dS;

    get_hls(dH, dL, dS);

    dH = dMultH * dH;
    dL = dMultL * dL;
    dS = dMultS * dS;

    if(dH > 1.0)
        dH = 1.0;
    else if(dH < 0.0)
        dH = 0.0;

    if(dL > 1.0)
        dL = 1.0;
    else if(dL < 0.0)
        dL = 0.0;

    if(dS > 1.0)
        dS = 1.0;
    else if(dS < 0.0)
        dS = 0.0;

    set_hls(dH, dL, dS);
}

void color::hls_mult(hls & hls)
{
   hls_mult(hls.m_dH, hls.m_dL, hls.m_dS);
}
void color::hls_rate(hls & hls)
{
   hls_rate(hls.m_dH, hls.m_dL, hls.m_dS);
}
void color::get_hls(
   hls & hls) const
{
   get_hls(hls.m_dH, hls.m_dL, hls.m_dS);
}
void color::set_hls(
   const hls & hls)
{
   set_hls(hls.m_dH, hls.m_dL, hls.m_dS);
}














/*
void CColor::get_hls(LPBYTE H, LPBYTE L, LPBYTE S)
{
   double dHue, dLightness, dSaturation;
   // input RGB values
   double dRed = m_bRed;
   double dGreen = m_bGreen;
   double dBlue = m_bBlue;
   // MAX and MIN RGB values
   double dMax, dMin;
   // intermediate value: % of spread from MAX
   double dRedDelta, dGreenDelta, dBlueDelta;
   // calculate lightness
   dMax = MAX(MAX(dRed, dGreen), dBlue);
   dMin = MIN(MIN(dRed, dGreen), dBlue);
   dLightness = (BYTE) (((dMax + dMin) * HLSMAX) + RGBMAX) / (2 * RGBMAX);
   if(dMax == dMin)
   {
      // r=g=b --> achromatic case
      dSaturation = 0;                     // saturation
      dHue = UNDEFINED_HUE;             // hue
   }
   else
   {
      // chromatic case
      // saturation
      if (dLightness <= (HLSMAX / 2.0))
         dSaturation = (((dMax - dMin) * HLSMAX) + ((dMax + dMin) / 2.0) )
         / (dMax + dMin);
      else
         dSaturation = (((dMax - dMin) * HLSMAX) + ((2.0 * RGBMAX - dMax - dMin) / 2.0))
            / (2.0 * RGBMAX - dMax - dMin);

      // hue
      dRedDelta   = ( ((dMax-dRed  )*(HLSMAX/6.0)) + ((dMax-dMin)/2.0) ) / (dMax-dMin);
      dGreenDelta = ( ((dMax-dGreen)*(HLSMAX/6.0)) + ((dMax-dMin)/2.0) ) / (dMax-dMin);
      dBlueDelta   = ( ((dMax-dBlue )*(HLSMAX/6.0)) + ((dMax-dMin)/2.0) ) / (dMax-dMin);

      if (dRed == dMax)
         dHue = dBlueDelta - dGreenDelta;
      else if (dGreen == dMax)
         dHue= (HLSMAX/3.0) + dRedDelta - dBlueDelta;
      else // B == cMax
         dHue = ((2.0*HLSMAX)/3.0) + dGreenDelta - dRedDelta;
      if (dHue < 0)
         dHue += HLSMAX;
      if (dHue > HLSMAX)
         dHue -= HLSMAX;
   }
   *H = (BYTE) dHue;
   *L = (BYTE) dLightness;
   *S = (BYTE) dSaturation;
}*/

/*
// utility routine for HLStoRGB

double HueToRGB(
   double d1,
   double d2,
   double dHue)
{
   // range check: note values passed add/subtract thirds of range
   if (dHue < 0.0)
      dHue += HLSMAX;
   if (dHue > HLSMAX)
      dHue -= HLSMAX;
   // return r,g, or b value from this tridrant
   if (dHue < (HLSMAX/6))
      return ( d1 + (((d2-d1)*dHue+(HLSMAX/12))/(HLSMAX/6)) );
   if (dHue < (HLSMAX/2))
      return ( d2 );
   if (dHue < ((HLSMAX*2)/3))
      return ( d1 + (((d2-d1)*(((HLSMAX*2)/3)-dHue)+(HLSMAX/12))/(HLSMAX/6)));
   else
      return ( d1 );
}

void CColor::set_hls(
   double dHue,
   double dLightness,
   double dSaturation)
{
   double dRed, dGreen, dBlue;        // RGB component values
   double dMagic1, dMagic2;       // calculated magic numbers (really!)

   if (dSaturation == 0.0)
   {
      //achromatic case
      dRed = dGreen = dBlue = (dLightness * RGBMAX) / HLSMAX;
      if (dHue != UNDEFINED_HUE)
      {
         // ERROR
      }
   }
   else
   {
      // chromatic case
      // set up magic numbers
      if (dLightness <= (HLSMAX / 2.0))
         dMagic2 = (dLightness * (HLSMAX + dSaturation) + (HLSMAX/2.0))/HLSMAX;
      else
         dMagic2 = dLightness + dSaturation - ((dLightness * dSaturation) + (HLSMAX/2.0))/HLSMAX;
      dMagic1 = 2.0 * dLightness- dMagic2;

      // get RGB, change units from HLSMAX to RGBMAX
      dRed   = (HueToRGB(dMagic1, dMagic2, dHue+(HLSMAX/3.0))*RGBMAX +
         (HLSMAX/2.0))/HLSMAX;
      dGreen   = (HueToRGB(dMagic1, dMagic2, dHue)*RGBMAX + (HLSMAX/2.0)) / HLSMAX;
      dBlue   = (HueToRGB(dMagic1, dMagic2, dHue-(HLSMAX/3.0))*RGBMAX +
         (HLSMAX/2))/HLSMAX;
   }
   m_bBlue      = (BYTE) dBlue;
   m_bGreen   = (BYTE) dGreen;
   m_bRed      = (BYTE) dRed;


}

uint32_t CColor::get_rgb()
{
   return RGB(m_bRed, m_bGreen, m_bBlue);
}*/


color & color::operator = (const color & color)
{
   if(&color != this)
   {
      m_dR     = color.m_dR;
      m_dG     = color.m_dG;
      m_dB     = color.m_dB;
      m_dA     = color.m_dA;
      m_uchR   = color.m_uchR;
      m_uchG   = color.m_uchG;
      m_uchB   = color.m_uchB;
      m_uchA   = color.m_uchA;
   }
   return *this;
}

color & color::operator = (COLORREF cr)
{
   set_rgb(cr);
   return *this;
}

color & color::operator = (RGBQUAD rgbquad)
{
   set_rgbquad(rgbquad);
   return *this;
}
