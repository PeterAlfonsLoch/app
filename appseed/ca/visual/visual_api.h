#pragma once


namespace visual
{


   class CLASS_DECL_ca api :
      virtual public ::radix::object
   {
   public:


      api(::ca::application * papp);
      virtual ~api();


      bool open();

      bool close();

      void DrawAndFillBeziers(
         ::ca::graphics                     *pdc,
         LPPOINT             lppoints,
         int32_t                  iCount,
         double               dRateX,
         LPPOINT               lppointOffset);

      void DrawBeziers(
         ::ca::graphics                     *pdc,
         LPPOINT             lppoints,
         int32_t                  iCount,
         double               dRateX,
         LPPOINT               lppointOffset);

      void DrawAndFillBeziers(
         ::ca::graphics                     *pdc,
         base_array<point_array, point_array &> *
                            lpglyph,
         double               dRateX,
         LPPOINT               lppointOffset);

      void EmbossedTextOut(
            ::ca::graphics *                pdc,
            LPCRECT               lpcrect,
            double               dRateX,
            double               dHeight,
            const char *         psz);

      void EmbossedTextOut(
         ::ca::graphics *                pdc,
         LPCRECT               lpcrect,
         double               dRateX,
         double               dHeight,
         const char *         psz,
         LPINT                  lpiCharsPositions,
         int32_t                  iCharsPositions,
         int32_t                  iOffset);

      void EmbossedTextOut(
         ::ca::graphics *             pdc,
         const char *      lpcsz,
         int32_t               iLeft,
         int32_t               iTop,
         int32_t               iWidht,
         COLORREF          crText,
         COLORREF          crOutline,
         int32_t               iLen);


      void SimpleTextOut(
         ::ca::graphics               *pdc,
         LPCRECT            lpcrect,
         double            dRateX,
         double            dHeight,
         const char *      psz,
         LPINT               lpiCharsPositions,
         int32_t               iCharsPositions,
         int32_t               iOffset);


   };


} // namespace visual



