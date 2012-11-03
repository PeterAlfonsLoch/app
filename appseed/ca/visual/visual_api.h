#pragma once

namespace visual
{

   class CLASS_DECL_ca api
   {


   public:
      bool Start();
      static bool GetProcsAddress();
      api();
      virtual ~api();

      static HINSTANCE g_hinstanceGdipp;
      static bool g_bGdipp;
      static bool g_bGdiEnabled;
      inline static bool IsGdippEnabled()
      {
         return g_bGdipp && g_bGdiEnabled;
      }


      static void (* lpDrawAndFillBeziers1)(
         ::ca::graphics *          pdc,
         LPPOINT          lppoints,
         int            iCount,
         float            fRateX,
         LPPOINT         lppointOffset);

      static void (* lpDrawAndFillBeziers2)(
         ::ca::graphics *          pdc,
         base_array<point_array, point_array &> *      lpglyph,
         float            fRateX,
         LPPOINT         lppointOffset);

      static void (* lpEmbossedTextOut1)(
         ::ca::graphics *          pdc,
         LPCRECT         lpcrect,
         float            fRateX,
         float            fHeight,
         const char *   psz);

      static void (* lpEmbossedTextOut2)(
         ::ca::graphics *          pdc,
         LPCRECT         lpcrect,
         float            fRateX,
         float            fHeight,
         const char *   psz,
         LPINT            lpiCharsPositions,
         int            iCharsPositions,
         int            iOffset);

      static bool (* lpStartup)();

      static bool (* lpShutdown)();

      static bool open();

      static bool close();

      static void DrawAndFillBeziers(
         ::ca::graphics                     *pdc,
         LPPOINT             lppoints,
         int                  iCount,
         double               dRateX,
         LPPOINT               lppointOffset);

      static void DrawBeziers(
         ::ca::graphics                     *pdc,
         LPPOINT             lppoints,
         int                  iCount,
         double               dRateX,
         LPPOINT               lppointOffset);

      static void DrawAndFillBeziers(
         ::ca::graphics                     *pdc,
         base_array<point_array, point_array &> *
                            lpglyph,
         double               dRateX,
         LPPOINT               lppointOffset);

      static void EmbossedTextOut(
            ::ca::graphics *                pdc,
            LPCRECT               lpcrect,
            double               dRateX,
            double               dHeight,
            const char *         psz);

      static void EmbossedTextOut(
         ::ca::graphics *                pdc,
         LPCRECT               lpcrect,
         double               dRateX,
         double               dHeight,
         const char *         psz,
         LPINT                  lpiCharsPositions,
         int                  iCharsPositions,
         int                  iOffset);

      static void EmbossedTextOut(
         ::ca::graphics *             pdc,
         const char *      lpcsz,
         int               iLeft,
         int               iTop,
         int               iWidht,
         COLORREF          crText,
         COLORREF          crOutline,
         int               iLen);


      static void SimpleTextOut(
         ::ca::graphics               *pdc,
         LPCRECT            lpcrect,
         double            dRateX,
         double            dHeight,
         const char *      psz,
         LPINT               lpiCharsPositions,
         int               iCharsPositions,
         int               iOffset);

#ifdef WINDOWS
      static void EnableOpenGL(oswindow oswindow, HDC & hdc, HGLRC & hrc);
      static void DisableOpenGL(oswindow oswindow, HDC hDC, HGLRC hRC);
#endif

   };

} // namespace visual
