#pragma once


namespace visual
{


   class CLASS_DECL_ca2 api :
      virtual public ::ca2::object
   {
   public:


      api(sp(::ca2::application) papp);
      virtual ~api();


      bool open();

      bool close();

      void DrawAndFillBeziers(
         ::ca2::graphics                     *pdc,
         LPPOINT             lppoints,
         int32_t                  iCount,
         double               dRateX,
         LPPOINT               lppointOffset);

      void DrawBeziers(
         ::ca2::graphics                     *pdc,
         LPPOINT             lppoints,
         int32_t                  iCount,
         double               dRateX,
         LPPOINT               lppointOffset);

      void DrawAndFillBeziers(
         ::ca2::graphics                     *pdc,
         array<point_array, point_array &> *
                            lpglyph,
         double               dRateX,
         LPPOINT               lppointOffset);

      void EmbossedTextOut(
            ::ca2::graphics *                pdc,
            LPCRECT               lpcrect,
            double               dRateX,
            double               dHeight,
            const char *         psz);

      void EmbossedTextOut(
         ::ca2::graphics *                pdc,
         LPCRECT               lpcrect,
         double               dRateX,
         double               dHeight,
         const char *         psz,
         LPINT                  lpiCharsPositions,
         int32_t                  iCharsPositions,
         int32_t                  iOffset);

      void EmbossedTextOut(
         ::ca2::graphics *             pdc,
         const char *      lpcsz,
         int32_t               iLeft,
         int32_t               iTop,
         int32_t               iWidht,
         COLORREF          crText,
         COLORREF          crOutline,
         int32_t               iLen);


      void SimpleTextOut(
         ::ca2::graphics               *pdc,
         LPCRECT            lpcrect,
         double            dRateX,
         double            dHeight,
         const char *      psz,
         LPINT               lpiCharsPositions,
         int32_t               iCharsPositions,
         int32_t               iOffset);


   };


} // namespace visual



