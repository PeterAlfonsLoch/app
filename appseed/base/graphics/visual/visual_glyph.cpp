#include "framework.h"


namespace visual
{


   glyph::glyph()
   {

   }

   glyph::~glyph()
   {

   }

   glyph & glyph::operator = (const glyph & glyph)
   {

      m_ui = glyph.m_ui;

#ifdef WINDOWSEX

      m_gm = glyph.m_gm;

#endif

      m_pointsets.copy(glyph.m_pointsets);

      return *this;

   }

   bool glyph::operator <= (const glyph & glyph) const
   {

      return m_ui < glyph.m_ui;

   }

#ifdef WINDOWSEX

   /****************************************************************************
   *  FUNCTION   : IntFromFixed
   *  RETURNS    : int32_t value approximating the FIXED value.
   ****************************************************************************/
   int32_t NEAR IntFromFixed(FIXED f)
   {
      if (f.fract >= 0x8000)
         return(f.value + 1);
      else
         return(f.value);
   }



   /****************************************************************************
   *  FUNCTION   : fxDiv2
   *  RETURNS    : (val1 + val2)/2 for FIXED values
   ****************************************************************************/
   FIXED NEAR fxDiv2(FIXED fxVal1, FIXED fxVal2)
   {
      long l;

      l = (*((long far *)&(fxVal1)) + *((long far *)&(fxVal2)))/2;
      return(*(FIXED *)&l);
   }

   /****************************************************************************
   *  FUNCTION   : MakeBezierFromLine
   *
   *  PURPOSE    : Converts a line define by two points to a four point Bezier
   *               spline representation of the line in pPts.
   *
   *
   *  RETURNS    : number of Bezier points placed into the pPts POINT array.
   ****************************************************************************/
   UINT MakeBezierFromLine( POINT *pPts, POINT startpt, POINT endpt )
   {
      UINT cTotal = 0;

      // starting point of Bezier
      pPts[cTotal] = startpt;
      cTotal++;

      // 1rst control, pt == endpoint makes Bezier a line
      pPts[cTotal].x = endpt.x;
      pPts[cTotal].y = endpt.y;
      cTotal++;

      // 2nd control, pt == startpoint makes Bezier a line
      pPts[cTotal].x = startpt.x;
      pPts[cTotal].y = startpt.y;
      cTotal++;

      // ending point of Bezier
      pPts[cTotal] = endpt;
      cTotal++;

      return cTotal;
   }

   /****************************************************************************
   *  FUNCTION   : MakeBezierFromQBSpline
   *
   *  PURPOSE    : Converts a quadratic spline in pSline to a four point Bezier
   *               spline in pPts.
   *
   *
   *  RETURNS    : number of Bezier points placed into the pPts POINT array.
   ****************************************************************************/
   UINT MakeBezierFromQBSpline( POINT *pPts, POINTFX *pSpline )
   {
      POINT   P0,         // Quadratic on curve start point
         P1,         // Quadratic control point
         P2;         // Quadratic on curve end point
      UINT    cTotal = 0;

      // Convert the Quadratic points to integer
      P0.x = IntFromFixed( pSpline[0].x );
      P0.y = IntFromFixed( pSpline[0].y );
      P1.x = IntFromFixed( pSpline[1].x );
      P1.y = IntFromFixed( pSpline[1].y );
      P2.x = IntFromFixed( pSpline[2].x );
      P2.y = IntFromFixed( pSpline[2].y );

      // conversion of a quadratic to a cubic

      // Cubic P0 is the on curve start point
      pPts[cTotal] = P0;
      cTotal++;

      // Cubic P1 in terms of Quadratic P0 and P1
      pPts[cTotal].x = P0.x + 2*(P1.x - P0.x)/3;
      pPts[cTotal].y = P0.y + 2*(P1.y - P0.y)/3;
      cTotal++;

      // Cubic P2 in terms of Qudartic P1 and P2
      pPts[cTotal].x = P1.x + 1*(P2.x - P1.x)/3;
      pPts[cTotal].y = P1.y + 1*(P2.y - P1.y)/3;
      cTotal++;

      // Cubic P3 is the on curve end point
      pPts[cTotal] = P2;
      cTotal++;

      return cTotal;
   }


   /****************************************************************************
   *  FUNCTION   : AppendPolyLineToBezier
   *
   *  PURPOSE    : Converts line segments into their Bezier point
   *               representation and appends them to a list of Bezier points.
   *
   *               WARNING - The array must have at least one valid
   *               start point prior to the address of the element passed.
   *
   *  RETURNS    : number of Bezier points added to the POINT array.
   ****************************************************************************/
   //UINT AppendPolyLineToBezier( LPPOINT pt, POINTFX start, LPTTPOLYCURVE lpCurve )
   UINT AppendPolyLineToBezier(
      point_array      &pointsset,
      POINTFX         start,
      LPTTPOLYCURVE   lpCurve,
      UINT         cTotal )
   {
      int32_t     i;
      //    UINT    cTotal = 0;
      POINT   endpt;
      POINT   startpt;
      POINT   bezier[4];

      endpt.x = IntFromFixed(start.x);
      endpt.y = IntFromFixed(start.y);

      //points.set_size(points.get_size() + lpCurve->cpfx * 3);
      for (i = 0; i < lpCurve->cpfx; i++)
      {
         // define the line segment
         startpt = endpt;
         endpt.x = IntFromFixed(lpCurve->apfx[i].x);
         endpt.y = IntFromFixed(lpCurve->apfx[i].y);

         // convert a line to a bezier representation
         MakeBezierFromLine( bezier, startpt, endpt );

         // append the Bezier to the existing ones
         // Point 0 is Point 3 of previous.
         //      pt[cTotal++] = bezier[1];   // Point 1
         //        pt[cTotal++] = bezier[2];   // Point 2
         //      pt[cTotal++] = bezier[3];   // Point 3
         pointsset.add(bezier[1]);
         pointsset.add(bezier[2]);
         pointsset.add(bezier[3]);


      }

      return cTotal;
   }


   /****************************************************************************
   *  FUNCTION   : AppendQuadBSplineToBezier
   *
   *  PURPOSE    : Converts Quadratic spline segments into their Bezier point
   *               representation and appends them to a list of Bezier points.
   *
   *               WARNING - The array must have at least one valid
   *               start point prior to the address of the element passed.
   *
   *  RETURNS    : number of Bezier points added to the POINT array.
   ****************************************************************************/
   //UINT AppendQuadBSplineToBezier( LPPOINT pt, POINTFX start, LPTTPOLYCURVE lpCurve )
   UINT AppendQuadBSplineToBezier(
      point_array & pointset,
      POINTFX start,
      LPTTPOLYCURVE lpCurve,
      UINT cTotal )

   {
      WORD                i;
      //    UINT                cTotal = 0;
      POINTFX             spline[3];  // a Quadratic is defined by 3 points
      POINT               bezier[4];  // a Cubic by 4

      // The initial A point is on the curve.
      spline[0] = start;

      for (i = 0; i < lpCurve->cpfx;)
      {
         // The B point.
         spline[1] = lpCurve->apfx[i++];

         // Calculate the C point.
         if (i == (lpCurve->cpfx - 1))
         {
            // The last C point is described explicitly
            // i.e. it is on the curve.
            spline[2] = lpCurve->apfx[i++];
         }
         else
         {
            // C is midpoint between B and next B point
            // because that is the on curve point of
            // a Quadratic B-Spline.
            spline[2].x = fxDiv2(
               lpCurve->apfx[i-1].x,
               lpCurve->apfx[i].x
               );
            spline[2].y = fxDiv2(
               lpCurve->apfx[i-1].y,
               lpCurve->apfx[i].y
               );
         }

         // convert the Q Spline to a Bezier
         MakeBezierFromQBSpline( bezier, spline );

         // append the Bezier to the existing ones
         // Point 0 is Point 3 of previous.
         //        pt[cTotal++] = bezier[1];   // Point 1
         //      pt[cTotal++] = bezier[2];   // Point 2
         //    pt[cTotal++] = bezier[3];   // Point 3
         pointset.add(bezier[1]);
         pointset.add(bezier[2]);
         pointset.add(bezier[3]);

         // New A point for next slice of spline is the
         // on curve C point of this B-Spline
         spline[0] = spline[2];
      }

      return cTotal;
   }

   /****************************************************************************
   *  FUNCTION   : CloseContour
   *
   *  PURPOSE    : Adds a bezier line to close the circuit defined in pt.
   *
   *
   *  RETURNS    : number of points aded to the pt POINT array.
   ****************************************************************************/
   //UINT CloseContour( LPPOINT pt, UINT cTotal )
   UINT CloseContour(
      point_array & pointset,
      UINT cTotal )
   {
      POINT               endpt,
         startpt;    // definition of a line
      POINT               bezier[4];

      // connect the first and last points by a line segment
      //startpt = pt[cTotal-1];
      //endpt = pt[0];
      startpt = pointset.last_element();
      endpt = pointset.first_element();

      //points.set_size(points.get_size() + 3);
      // convert a line to a bezier representation
      MakeBezierFromLine( bezier, startpt, endpt );

      // append the Bezier to the existing ones
      // Point 0 is Point 3 of previous.
      //    pt[cTotal++] = bezier[1];   // Point 1
      //  pt[cTotal++] = bezier[2];   // Point 2
      //pt[cTotal++] = bezier[3];   // Point 3
      pointset.add(bezier[1]);   // Point 1
      pointset.add(bezier[2]);   // Point 2
      pointset.add(bezier[3]);   // Point 3

      //return 3;
      return cTotal;
   }


   /****************************************************************************
   *  FUNCTION   : DrawT2Outline
   *
   *  PURPOSE    : Decode the GGO_NATIVE outline, create a sequence of Beziers
   *               for each contour, draw with PolyBezier.  color and relative
   *               positioning provided by caller. The coordinates of hDC are
   *               assumed to have MM_TEXT orientation.
   *
   *               The outline data is not scaled. To draw a glyph unhinted
   *               the caller should create the font at its EMSquare size
   *               and retrieve the outline data. Then setup a mapping mode
   *               prior to calling this function.
   *
   *  RETURNS    : none.
   ****************************************************************************/
   void glyph::Initialize(LPTTPOLYGONHEADER lpHeader, uint32_t size, int32_t iFontHiHeight)
   {

      WORD                i;
      UINT                cTotal = 0; // Total points in a contour.
      LPTTPOLYGONHEADER   lpStart;    // the start of the buffer
      LPTTPOLYCURVE       lpCurve;    // the current curve of a contour
      //  LPPOINT             pt;         // the bezier buffer
      POINTFX             ptStart;    // The starting point of a curve
      uint32_t               dwMaxPts = size/sizeof(POINTFX); // MAX possible pts.
      uint32_t               dwBuffSize;

      dwBuffSize = dwMaxPts *     // Maximum possible # of contour points.
         sizeof(POINT) * // sizeof buffer element
         3;             // Worst case multiplier of one additional point
      // of line expanding to three points of a bezier

      lpStart = lpHeader;


      // Loop until we have processed the entire buffer of contours.
      // The buffer may contain one or more contours that begin with
      // a TTPOLYGONHEADER. We have them all when we the end of the buffer.
      //while ((uint32_t)lpHeader < (uint32_t)(((char *)lpStart) + size) && pt != NULL)
      while ((uint32_t)lpHeader < (uint32_t)(((char *)lpStart) + size))
      {
         if (lpHeader->dwType == TT_POLYGON_TYPE)
            // draw each coutour, currently this is the only valid
               // type of contour.
         {
            point_array pointset;
            //pPoints = new CPoints();
            //         pPoints->m_lpPoints = pt;

            //pt = (LPPOINT)malloc( dwBuffSize );
            //         pt = (LPPOINT) new BYTE(dwBuffSize);
            // Convert the starting point. It is an on curve point.
            // All other points are continuous from the "last"
            // point of the contour. Thus the start point the next
            // bezier is always pt[cTotal-1] - the last point of the
            // previous bezier. See PolyBezier.
            pointset.add(
               IntFromFixed(lpHeader->pfxStart.x),
               IntFromFixed(lpHeader->pfxStart.y));
            cTotal = 1;
            //cTotal = 1;
            //pt[0].x = IntFromFixed(lpHeader->pfxStart.x);
            //pt[0].y = IntFromFixed(lpHeader->pfxStart.y);

            // get to first curve of contour -
            // it starts at the next byte beyond header
            lpCurve = (LPTTPOLYCURVE) (lpHeader + 1);

            // Walk this contour and process each curve( or line ) segment
            // and add it to the Beziers
            while ((uint32_t)lpCurve < (uint32_t)(((char *)lpHeader) + lpHeader->cb))
            {
               //**********************************************
               // Format assumption:
               //   The bytes immediately preceding a POLYCURVE
               //   structure contain a valid POINTFX.
               //
               //   If this is first curve, this points to the
               //      pfxStart of the POLYGONHEADER.
               //   Otherwise, this points to the last point of
               //      the previous POLYCURVE.
               //
               //   In either case, this is representative of the
               //      previous curve's last point.
               //**********************************************

               ptStart = *(LPPOINTFX)((char *)lpCurve - sizeof(POINTFX));
               if (lpCurve->wType == TT_PRIM_LINE)
               {
                  // convert the line segments to Bezier segments
                  //cTotal += AppendPolyLineToBezier( &pt[cTotal], ptStart, lpCurve );
                  cTotal = AppendPolyLineToBezier(pointset, ptStart, lpCurve, cTotal );
                  i = lpCurve->cpfx;
               }
               else if (lpCurve->wType == TT_PRIM_QSPLINE)
               {
                  // Decode each Quadratic B-Spline segment, convert to bezier,
                  // and append to the Bezier segments
                  //                    cTotal += AppendQuadBSplineToBezier( &pt[cTotal], ptStart, lpCurve );
                  cTotal = AppendQuadBSplineToBezier(pointset, ptStart, lpCurve, cTotal );
                  i = lpCurve->cpfx;
               }
               else
                  // Oops! A POLYCURVE format we don't understand.
                  ; // error, error, error

               // Move on to next curve in the contour.
               lpCurve = (LPTTPOLYCURVE)&(lpCurve->apfx[i]);
            }

            // add points to close the contour.
            // All contours are implied closed by TrueType definition.
            // Depending on the specific font and glyph being used, these
            // may not always be needed.

            //            if ( pt[cTotal-1].x != pt[0].x || pt[cTotal-1].y != pt[0].y )
            if (pointset.last_element().x != pointset.first_element().x ||
               pointset.last_element().y != pointset.first_element().y )
            {
               //cTotal += CloseContour( pt, cTotal );
               cTotal = CloseContour(pointset, cTotal );
            }

            // flip coordinates to get glyph right side up (Windows coordinates)
            // TT native coordiantes are zero originate at lower-left.
            // Windows MM_TEXT are zero originate at upper-left.
            for (i = 0; i < pointset.get_size(); i++)
               pointset[i].y = iFontHiHeight - pointset[i].y;
            //pt[i].y = 0 - pt[i].y;

            // draw the contour

            //PolyBezier( hDC, pt, cTotal );
            //pPoints->m_dwCount = cTotal;
            m_pointsets.add(pointset);
         }
         else
            // Bad, bail, must have a bogus buffer.
            break; // error, error, error

         // Move on to next Contour.
         // Its header starts immediate after this contour
         lpHeader = (LPTTPOLYGONHEADER)(((char *)lpHeader) + lpHeader->cb);
      }

      // free( pt );
   }


#endif


   void glyph::clear()
   {

      //   m_lpBodyData = NULL;
      //   m_lpOutlineData  = NULL;

#ifdef WINDOWSEX

      memset(&m_gm, 0, sizeof(m_gm));

#else

      throw todo(get_thread_app());

#endif


   }


   void glyph::GetGlyphRect(int32_t x, int32_t y, LPRECT lpRect)
   {

#ifdef WINDOWSEX

      lpRect->left      = x - m_gm.gmptGlyphOrigin.x;
      lpRect->top       = y - m_gm.gmptGlyphOrigin.y;
      lpRect->right     = x + m_gm.gmBlackBoxX;
      lpRect->bottom    = y + m_gm.gmBlackBoxY;

#else

      throw todo(get_thread_app());

#endif


   }


   void glyph::DrawGlyph(::draw2d::graphics * pdc, bool bFill, double dRateX, LPPOINT lppointOffset)
   {

      UNREFERENCED_PARAMETER(pdc);
      UNREFERENCED_PARAMETER(bFill);
      UNREFERENCED_PARAMETER(dRateX);
      UNREFERENCED_PARAMETER(lppointOffset);

      //System.visual().api().DrawAndFillBeziers(pdc, &m_pointsets, dRateX, lppointOffset);

   }


} // namespace visual


