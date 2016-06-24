#include "framework.h"

#define unequal(a, b, n) ((a) > (b) - (n))

#define pixel(x, y) (ba[(pointer->m_rect.height() - (y) - 1) * iScan + (x)])

bool detect_8bit_borders(::draw2d::dib * pdibCompose, ::visual::dib_sp::array * pdiba, ::visual::dib_sp::pointer * pointer, int uFrameIndex, byte * ba, int iScan, array < COLORREF > & cra, int transparentIndex);

bool gif_load_frame(::draw2d::dib * pdibCompose, ::visual::dib_sp::array * pdiba, ::visual::dib_sp::pointer * pointer, int uFrameIndex, byte * ba, int iScan, array < COLORREF > & cra, int transparentIndex)
{

   pointer->m_dib->map();

   COLORREF cr;

   COLORREF crBack = 0;

   if (uFrameIndex <= 0)
   {

      detect_8bit_borders(pdibCompose, pdiba, pointer, uFrameIndex, ba, iScan, cra, transparentIndex);
   
   }

   pointer->m_bTransparent = pdiba->m_bTransparent;

   if (pdiba->m_bTransparent)
   {

      {

         int w = pointer->m_dib->m_iScan / sizeof(COLORREF);

         for (index y = 0; y < pointer->m_rect.height(); y++)
         {

            for (index x = 0; x < pointer->m_rect.width(); x++)
            {

               index iIndex = pixel(x, y);

               if (iIndex >= cra.get_count())
               {

                  pointer->m_dib->m_pcolorref[y*w + x] = 0;

                  continue;

               }
               if (iIndex == transparentIndex)
               {

                  pointer->m_bTransparent = true;
                  pointer->m_dib->m_pcolorref[y*w + x] = 0;

                  continue;

               }

               COLORREF cr = cra[iIndex];
               //if (pdiba->m_bTransparent)
               //{

               //   byte r = argb_get_r_value(cr);
               //   byte g = argb_get_g_value(cr);
               //   byte b = argb_get_b_value(cr);
               //   byte mean = (r + g + b) / 3;
               //   if (mean > 127)
               //   {

               //      pointer->m_dib->m_pcolorref[y*w + x] = ARGB(mean, r, g, b);

               //      continue;
               //   }




               //}


               pointer->m_dib->m_pcolorref[y*w + x] = cr;

            }

         }

      }


      if (uFrameIndex > 0 && pdiba->element_at(uFrameIndex - 1)->m_edisposal == ::visual::dib_sp::pointer::disposal_background)
      {

         pdibCompose->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         COLORREF crBack = pdiba->m_crBack;

         byte bAlpha = argb_get_a_value(crBack);

         if (bAlpha == 0)
         {

            crBack = 0;

         }
         else
         {

            output_debug_string("non zero alpha");

         }

         ::rect r = pdiba->element_at(uFrameIndex - 1)->m_rect;

         r.offset(5, 5);

         pdibCompose->get_graphics()->FillSolidRect(r, crBack);

      }

      pdibCompose->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::point pt = pointer->m_rect.top_left();

      ::size sz = pointer->m_rect.size();

      pdibCompose->get_graphics()->BitBlt(pt + point(5, 5), sz, pointer->m_dib->get_graphics());

      pointer->m_dib->from(pdibCompose);

      if (pointer->m_bTransparent)
      {

         crBack = pdiba->m_crTransparent;

         pdiba->m_iTransparentIndex = transparentIndex;

         pdiba->m_bTransparent = true;

      }
      else
      {

         crBack = pointer->m_crTransparent;

         size s = pointer->m_dib->m_size;

         int cx = s.cx;

         int cy = s.cy;

         if (pointer->m_rect.size() == pdiba->m_size)
         {

            if (pixel(0, 0) == pixel(cx - 1, 0)) // && pointer->m_rect.left == 0 && pointer->m_rect.top == 0 && pointer->m_rect.right == pdiba->m_size.cx)
            {

               transparentIndex = pixel(0, 0);

               pdiba->m_iTransparentIndex = transparentIndex;

            }
            else if (pixel(0, cy - 1) == pixel(cx - 1, cy - 1))// && pointer->m_rect.left == 0 && pointer->m_rect.bottom == pdiba->m_size.cy && pointer->m_rect.right == pdiba->m_size.cx)
            {

               transparentIndex = pixel(0, cy - 1);

               pdiba->m_iTransparentIndex = transparentIndex;

            }
            else
            {

               transparentIndex = pdiba->m_iTransparentIndex;

            }

         }
         else
         {

            transparentIndex = pdiba->m_iTransparentIndex;

         }

      }

      double dA1 = argb_get_a_value(crBack);

      double dR1 = argb_get_r_value(crBack);

      double dG1 = argb_get_g_value(crBack);

      double dB1 = argb_get_b_value(crBack);

      bool bUnequal = true;

      double dUnequal = 32.0;

      double dUnequalScaleDown = 1.00;

      double dUnequalRate = 6.0;

      double dUnequalAddUp = 63.00;

      double dUnequalDarken = 0.5;

      double dTransparent = 4.0;

      int w = pointer->m_dib->m_iScan / sizeof(COLORREF);

      int i = 0;

      index x;

      index y;

      bool bTransparent;
//      goto skip1;


      for (index iPass = 0; iPass < 1; iPass++)
      {

         for (y = 0; y < pointer->m_dib->m_size.cy; y++)
         {

            bTransparent = false;

            for (x = 0; x < pointer->m_dib->m_size.cx; x++)
            {

               index iPixel = y * w + x;

               cr = pointer->m_dib->m_pcolorref[iPixel];

               double dA = argb_get_a_value(cr);

               double dR = argb_get_r_value(cr);

               double dG = argb_get_g_value(cr);

               double dB = argb_get_b_value(cr);

               if (dA <= dTransparent)
               {

                  bTransparent = true;

                  continue;

               }

               if (bUnequal && bTransparent)
               {

                  if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
                  {

                     double dA2;

                     if (dR1 < 127)
                     {

                        dA2 = MAX(dR, MAX(dG, dB)) * dUnequalRate + dUnequalAddUp;

                     }
                     else
                     {

                        dA2 = (255.0 - MIN(dR,   MIN(dG, dB))) * dUnequalRate + dUnequalAddUp;

                     }


                     dA = dA * dA2 / 255.0;

                     pointer->m_dib->m_pcolorref[iPixel] = ARGB(
                        (byte)dA,
                        (byte)(dR * dR * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dG * dG * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dB * dB * dA * dUnequalDarken / (255.0 * 255.0)));

                     continue;

                  }
                  else
                  {

                     bTransparent = false;

                  }

               }
               else
               {

                  bTransparent = false;

               }

               //pointer->m_dib->m_pcolorref[iPixel] = ARGB((byte)255, (byte)dR, (byte)dG, (byte)dB);

            }



            x--;

            for (; x >= 0; x--)
            {

               index iPixel = y * w + x;

               cr = pointer->m_dib->m_pcolorref[iPixel];

               double dA = argb_get_a_value(cr);

               double dR = argb_get_r_value(cr);

               double dG = argb_get_g_value(cr);

               double dB = argb_get_b_value(cr);

               if (dA <= dTransparent)
               {

                  bTransparent = true;

                  continue;

               }

               if (bUnequal && bTransparent)
               {

                  if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
                  {

                     double dA2;

                     if (dR1 < 127)
                     {

                        dA2 = MAX(dR, MAX(dG, dB)) * dUnequalRate + dUnequalAddUp;

                     }
                     else
                     {

                        dA2 = (255.0 - MIN(dR,   MIN(dG, dB))) * dUnequalRate + dUnequalAddUp;

                     }

                     dA = dA * dA2 / 255.0;

                     pointer->m_dib->m_pcolorref[iPixel] = ARGB(
                        (byte)dA,
                        (byte)(dR * dR * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dG * dG * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dB * dB * dA * dUnequalDarken / (255.0 * 255.0)));

                     continue;

                  }
                  else
                  {

                     bTransparent = false;

                  }

               }
               else
               {

                  bTransparent = false;

               }

               //pointer->m_dib->m_pcolorref[iPixel] = ARGB((byte)255, (byte)dR, (byte)dG, (byte)dB);

            }

         }


         dUnequal *= dUnequalScaleDown;


         for (x = 0; x < pointer->m_dib->m_size.cx; x++)
         {

            for (y = 0; y < pointer->m_dib->m_size.cy; y++)
            {

               index iPixel = y * w + x;

               cr = pointer->m_dib->m_pcolorref[iPixel];

               double dA = argb_get_a_value(cr);

               double dR = argb_get_r_value(cr);

               double dG = argb_get_g_value(cr);

               double dB = argb_get_b_value(cr);

               if (dA <= dTransparent)
               {

                  bTransparent = true;

                  continue;

               }

               if (bUnequal && bTransparent)
               {

                  if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
                  {

                     double dA2;

                     if (dR1 < 127)
                     {

                        dA2 = MAX(dR, MAX(dG, dB)) * dUnequalRate + dUnequalAddUp;

                     }
                     else
                     {

                        dA2 = (255.0 - MIN(dR,   MIN(dG, dB))) * dUnequalRate + dUnequalAddUp;

                     }

                     dA = dA * dA2 / 255.0;

                     pointer->m_dib->m_pcolorref[iPixel] = ARGB(
                        (byte)dA,
                        (byte)(dR * dR * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dG * dG * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dB * dB * dA * dUnequalDarken / (255.0 * 255.0)));

                     continue;

                  }
                  else
                  {

                     bTransparent = false;

                  }

               }
               else
               {

                  bTransparent = false;

               }

               //pointer->m_dib->m_pcolorref[iPixel] = ARGB((byte)255, (byte)dR, (byte)dG, (byte)dB);

            }

            bTransparent = pointer->m_rect.bottom == pdiba->m_size.cy; // borders transparent?

            y--;

            for (; y >= 0; y--)
            {

               index iPixel = y * w + x;

               cr = pointer->m_dib->m_pcolorref[iPixel];

               double dA = argb_get_a_value(cr);

               double dR = argb_get_r_value(cr);

               double dG = argb_get_g_value(cr);

               double dB = argb_get_b_value(cr);

               if (dA <= dTransparent)
               {

                  bTransparent = true;

                  continue;

               }

               if (bUnequal && bTransparent)
               {

                  if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
                  {

                     double dA2;

                     if (dR1 < 127)
                     {

                        dA2 = MAX(dR, MAX(dG, dB)) * dUnequalRate + dUnequalAddUp;

                     }
                     else
                     {

                        dA2 = (255.0 - MIN(dR,   MIN(dG, dB))) * dUnequalRate + dUnequalAddUp;

                     }

                     dA = dA * dA2 / 255.0;

                     pointer->m_dib->m_pcolorref[iPixel] = ARGB(
                        (byte)dA,
                        (byte)(dR * dR * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dG * dG * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dB * dB * dA * dUnequalDarken / (255.0 * 255.0)));

                     continue;

                  }
                  else
                  {

                     bTransparent = false;

                  }

               }
               else
               {

                  bTransparent = false;

               }

               //pointer->m_dib->m_pcolorref[iPixel] = ARGB((byte)255, (byte)dR, (byte)dG, (byte)dB);

            }

         }



         dUnequal *= dUnequalScaleDown;



         for (y = 0; y < pointer->m_dib->m_size.cy; y++)
         {

            bTransparent = pointer->m_rect.left == 0; // borders transparent?

            for (x = 0; x < pointer->m_dib->m_size.cx && y + x < pointer->m_dib->m_size.cy; x++)
            {

               index iPixel = (y + x) * w + x;

               cr = pointer->m_dib->m_pcolorref[iPixel];

               double dA = argb_get_a_value(cr);

               double dR = argb_get_r_value(cr);

               double dG = argb_get_g_value(cr);

               double dB = argb_get_b_value(cr);

               if (dA <= dTransparent)
               {

                  bTransparent = true;

                  continue;

               }

               if (bUnequal && bTransparent)
               {

                  if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
                  {

                     double dA2;

                     if (dR1 < 127)
                     {

                        dA2 = MAX(dR, MAX(dG, dB)) * dUnequalRate + dUnequalAddUp;

                     }
                     else
                     {

                        dA2 = (255.0 - MIN(dR,   MIN(dG, dB))) * dUnequalRate + dUnequalAddUp;

                     }

                     dA = dA * dA2 / 255.0;

                     pointer->m_dib->m_pcolorref[iPixel] = ARGB(
                        (byte)dA,
                        (byte)(dR * dR * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dG * dG * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dB * dB * dA * dUnequalDarken / (255.0 * 255.0)));

                     continue;

                  }
                  else
                  {

                     bTransparent = false;

                  }

               }
               else
               {

                  bTransparent = false;

               }

               //pointer->m_dib->m_pcolorref[iPixel] = ARGB((byte)255, (byte)dR, (byte)dG, (byte)dB);

            }

            bTransparent = pointer->m_rect.right == pdiba->m_size.cx; // borders transparent?

            x--;

            for (; x >= 0; x--)
            {

               index iPixel = (y + x) * w + x;

               cr = pointer->m_dib->m_pcolorref[iPixel];

               double dA = argb_get_a_value(cr);

               double dR = argb_get_r_value(cr);

               double dG = argb_get_g_value(cr);

               double dB = argb_get_b_value(cr);

               if (dA <= dTransparent)
               {

                  bTransparent = true;

                  continue;

               }

               if (bUnequal && bTransparent)
               {

                  if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
                  {

                     double dA2;

                     if (dR1 < 127)
                     {

                        dA2 = MAX(dR, MAX(dG, dB)) * dUnequalRate + dUnequalAddUp;

                     }
                     else
                     {

                        dA2 = (255.0 - MIN(dR,   MIN(dG, dB))) * dUnequalRate + dUnequalAddUp;

                     }

                     dA = dA * dA2 / 255.0;

                     pointer->m_dib->m_pcolorref[iPixel] = ARGB(
                        (byte)dA,
                        (byte)(dR * dR * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dG * dG * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dB * dB * dA * dUnequalDarken / (255.0 * 255.0)));

                     continue;

                  }
                  else
                  {

                     bTransparent = false;

                  }

               }
               else
               {

                  bTransparent = false;

               }

//               // pointer->m_dib->m_pcolorref[iPixel] = ARGB((byte)dA, (byte)dR, (byte)dG, (byte)dB);

            }

         }



         dUnequal *= dUnequalScaleDown;


         for (y = 0; y < pointer->m_dib->m_size.cy; y++)
         {

            bTransparent = pointer->m_rect.left == 0; // borders transparent?

            for (x = 0; x < pointer->m_dib->m_size.cx && y - x >= 0; x++)
            {

               index iPixel = (y - x) * w + x;

               cr = pointer->m_dib->m_pcolorref[iPixel];

               double dA = argb_get_a_value(cr);

               double dR = argb_get_r_value(cr);

               double dG = argb_get_g_value(cr);

               double dB = argb_get_b_value(cr);

               if (dA <= dTransparent)
               {

                  bTransparent = true;

                  continue;

               }

               if (bUnequal && bTransparent)
               {

                  if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
                  {

                     double dA2;

                     if (dR1 < 127)
                     {

                        dA2 = MAX(dR, MAX(dG, dB)) * dUnequalRate + dUnequalAddUp;

                     }
                     else
                     {

                        dA2 = (255.0 - MIN(dR,   MIN(dG, dB))) * dUnequalRate + dUnequalAddUp;

                     }

                     dA = dA * dA2 / 255.0;

                     pointer->m_dib->m_pcolorref[iPixel] = ARGB(
                        (byte)dA,
                        (byte)(dR * dR * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dG * dG * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dB * dB * dA * dUnequalDarken / (255.0 * 255.0)));

                     continue;

                  }
                  else
                  {

                     bTransparent = false;

                  }

               }
               else
               {

                  bTransparent = false;

               }

  //             // pointer->m_dib->m_pcolorref[iPixel] = ARGB((byte)dA, (byte)dR, (byte)dG, (byte)dB);

            }

            bTransparent = pointer->m_rect.right == pdiba->m_size.cx; // borders transparent?

            x--;

            for (; x >= 0; x--)
            {

               index iPixel = (y - x) * w + x;

               cr = pointer->m_dib->m_pcolorref[iPixel];

               double dA = argb_get_a_value(cr);

               double dR = argb_get_r_value(cr);

               double dG = argb_get_g_value(cr);

               double dB = argb_get_b_value(cr);

               if (dA <= dTransparent)
               {

                  bTransparent = true;

                  continue;

               }

               if (bUnequal && bTransparent)
               {

                  if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
                  {

                     double dA2;

                     if (dR1 < 127)
                     {

                        dA2 = MAX(dR, MAX(dG, dB)) * dUnequalRate + dUnequalAddUp;

                     }
                     else
                     {

                        dA2 = (255.0 - MIN(dR,   MIN(dG, dB))) * dUnequalRate + dUnequalAddUp;

                     }

                     dA = dA * dA2 / 255.0;

                     pointer->m_dib->m_pcolorref[iPixel] = ARGB(
                        (byte)dA,
                        (byte)(dR * dR * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dG * dG * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dB * dB * dA * dUnequalDarken / (255.0 * 255.0)));

                     continue;

                  }
                  else
                  {

                     bTransparent = false;

                  }

               }
               else
               {

                  bTransparent = false;

               }

               // pointer->m_dib->m_pcolorref[iPixel] = ARGB((byte)dA, (byte)dR, (byte)dG, (byte)dB);

            }

         }



         dUnequal *= dUnequalScaleDown;



         for (x = 0; x < pointer->m_dib->m_size.cx; x++)
         {

            bTransparent = pointer->m_rect.top == 0; // borders transparent?

            for (y = pointer->m_dib->m_size.cy - 1; y >= 0 && x + (y - pointer->m_dib->m_size.cy + 1) < pointer->m_dib->m_size.cx; y--)
            {

               index iPixel = y * w + x + (y - pointer->m_dib->m_size.cy + 1);

               cr = pointer->m_dib->m_pcolorref[iPixel];

               double dA = argb_get_a_value(cr);

               double dR = argb_get_r_value(cr);

               double dG = argb_get_g_value(cr);

               double dB = argb_get_b_value(cr);

               if (dA <= dTransparent)
               {

                  bTransparent = true;

                  continue;

               }

               if (bUnequal && bTransparent)
               {

                  if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
                  {

                     double dA2;

                     if (dR1 < 127)
                     {

                        dA2 = MAX(dR, MAX(dG, dB)) * dUnequalRate + dUnequalAddUp;

                     }
                     else
                     {

                        dA2 = (255.0 - MIN(dR,   MIN(dG, dB))) * dUnequalRate + dUnequalAddUp;

                     }

                     dA = dA * dA2 / 255.0;

                     pointer->m_dib->m_pcolorref[iPixel] = ARGB(
                        (byte)dA,
                        (byte)(dR * dR * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dG * dG * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dB * dB * dA * dUnequalDarken / (255.0 * 255.0)));

                     continue;

                  }
                  else
                  {

                     bTransparent = false;

                  }

               }
               else
               {

                  bTransparent = false;

               }

               // pointer->m_dib->m_pcolorref[iPixel] = ARGB((byte)dA, (byte)dR, (byte)dG, (byte)dB);

            }

            bTransparent = false;

            y++;

            for (; y < pointer->m_dib->m_size.cy; y++)
            {

               index iPixel = y * w + x + (y - pointer->m_dib->m_size.cy + 1);

               cr = pointer->m_dib->m_pcolorref[iPixel];

               double dA = argb_get_a_value(cr);

               double dR = argb_get_r_value(cr);

               double dG = argb_get_g_value(cr);

               double dB = argb_get_b_value(cr);

               if (dA <= dTransparent)
               {

                  bTransparent = true;

                  continue;

               }

               if (bUnequal && bTransparent)
               {

                  if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
                  {

                     double dA2;

                     if (dR1 < 127)
                     {

                        dA2 = MAX(dR, MAX(dG, dB)) * dUnequalRate + dUnequalAddUp;

                     }
                     else
                     {

                        dA2 = (255.0 - MIN(dR,   MIN(dG, dB))) * dUnequalRate + dUnequalAddUp;

                     }

                     dA = dA * dA2 / 255.0;

                     pointer->m_dib->m_pcolorref[iPixel] = ARGB(
                        (byte)dA,
                        (byte)(dR * dR * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dG * dG * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dB * dB * dA * dUnequalDarken / (255.0 * 255.0)));

                     continue;

                  }
                  else
                  {

                     bTransparent = false;

                  }

               }
               else
               {

                  bTransparent = false;

               }

               // pointer->m_dib->m_pcolorref[iPixel] = ARGB((byte)dA, (byte)dR, (byte)dG, (byte)dB);

            }

         }

         dUnequal *= dUnequalScaleDown;



         for (x = 0; x < pointer->m_dib->m_size.cx; x++)
         {

            bTransparent = false;

            for (y = 0; y < pointer->m_dib->m_size.cy  && x + y < pointer->m_dib->m_size.cx; y++)
            {

               index iPixel = y * w + x + y;

               cr = pointer->m_dib->m_pcolorref[iPixel];

               double dA = argb_get_a_value(cr);

               double dR = argb_get_r_value(cr);

               double dG = argb_get_g_value(cr);

               double dB = argb_get_b_value(cr);

               if (dA <= dTransparent)
               {

                  bTransparent = true;

                  continue;

               }

               if (bUnequal && bTransparent)
               {

                  if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
                  {

                     double dA2;

                     if (dR1 < 127)
                     {

                        dA2 = MAX(dR, MAX(dG, dB)) * dUnequalRate + dUnequalAddUp;

                     }
                     else
                     {

                        dA2 = (255.0 - MIN(dR,   MIN(dG, dB))) * dUnequalRate + dUnequalAddUp;

                     }

                     dA = dA * dA2 / 255.0;

                     pointer->m_dib->m_pcolorref[iPixel] = ARGB(
                        (byte)dA,
                        (byte)(dR * dR * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dG * dG * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dB * dB * dA * dUnequalDarken / (255.0 * 255.0)));

                     continue;

                  }
                  else
                  {

                     bTransparent = false;

                  }

               }
               else
               {

                  bTransparent = false;

               }

               // pointer->m_dib->m_pcolorref[iPixel] = ARGB((byte)dA, (byte)dR, (byte)dG, (byte)dB);

            }

            bTransparent = false;

            y--;

            for (; y >= 0; y--)
            {

               index iPixel = y * w + x + y;

               cr = pointer->m_dib->m_pcolorref[iPixel];

               double dA = argb_get_a_value(cr);

               double dR = argb_get_r_value(cr);

               double dG = argb_get_g_value(cr);

               double dB = argb_get_b_value(cr);

               if (dA <= dTransparent)
               {

                  bTransparent = true;

                  continue;

               }

               if (bUnequal && bTransparent)
               {

                  if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
                  {

                     double dA2;

                     if (dR1 < 127)
                     {

                        dA2 = MAX(dR, MAX(dG, dB)) * dUnequalRate + dUnequalAddUp;

                     }
                     else
                     {

                        dA2 = (255.0 - MIN(dR,   MIN(dG, dB))) * dUnequalRate + dUnequalAddUp;

                     }

                     dA = dA * dA2 / 255.0;

                     pointer->m_dib->m_pcolorref[iPixel] = ARGB(
                        (byte)dA,
                        (byte)(dR * dR * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dG * dG * dA * dUnequalDarken / (255.0 * 255.0)),
                        (byte)(dB * dB * dA * dUnequalDarken / (255.0 * 255.0)));

                     continue;

                  }
                  else
                  {

                     bTransparent = false;

                  }

               }
               else
               {

                  bTransparent = false;

               }

               // pointer->m_dib->m_pcolorref[iPixel] = ARGB((byte)dA, (byte)dR, (byte)dG, (byte)dB);

            }

         }




      }



//   skip1:;




      pdibCompose->from(pointer->m_dib);


      pointer->m_dib->create(pdiba->m_size);

      pointer->m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

      pointer->m_dib->get_graphics()->BitBlt(null_point(), pdiba->m_size, pdibCompose->get_graphics(), point(5, 5));








      if (true)
      {


         visual::fastblur f(pointer->m_dib->allocer());

         //draw2d::dib_sp d(pointer->m_dib->allocer());

         //d->create(pointer->m_dib->m_size);

         //Sys(pointer->m_dib->get_app()).visual().imaging().channel_spread(f->get_graphics(),
         // null_point(), f->m_size, pdibCompose->get_graphics(), null_point(), 3, 1);


         f.initialize(pointer->m_dib->m_size + size(10, 10), 1);

         f->channel_copy(::visual::rgba::channel_red, ::visual::rgba::channel_alpha, pdibCompose);

         f->channel_invert(::visual::rgba::channel_red);

         f.blur();
         f->channel_multiply(::visual::rgba::channel_red, 1.4);
         f.blur();
         
         //      f.blur();

         f->channel_invert(::visual::rgba::channel_red);

         draw2d::dib_sp d(pointer->m_dib->allocer());

         d->create(pdiba->m_size);

         d->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         d->get_graphics()->BitBlt(null_point(), pdiba->m_size, f->get_graphics(), point(5, 5));

         pointer->m_dib->div_alpha();

         pointer->m_dib->channel_copy(::visual::rgba::channel_alpha, ::visual::rgba::channel_red, d);

         pointer->m_dib->mult_alpha();






      }
























   }
   else
   {

      int w = pointer->m_dib->m_iScan / sizeof(COLORREF);

      for (index y = 0; y < pointer->m_rect.height(); y++)
      {

         for (index x = 0; x < pointer->m_rect.width(); x++)
         {

            index iIndex = pixel(x, y);

            if (iIndex >= cra.get_count())
            {

               pointer->m_dib->m_pcolorref[y*w + x] = 0;

               continue;

            }

            if (iIndex == transparentIndex)
            {

               pointer->m_dib->m_pcolorref[y*w + x] = 0;

               continue;

            }

            COLORREF cr = cra[iIndex];

            byte bA = argb_get_a_value(cr);

            pointer->m_dib->m_pcolorref[y*w + x] = cr;

         }

      }

      if (uFrameIndex > 0 && pdiba->element_at(uFrameIndex - 1)->m_edisposal == ::visual::dib_sp::pointer::disposal_background)
      {

         pdibCompose->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         COLORREF crBack = pdiba->m_crBack;

         byte bAlpha = argb_get_a_value(crBack);

         if (bAlpha == 0)
         {

            crBack = 0;

         }
         else
         {

            output_debug_string("non zero alpha");

         }

         ::rect r = pdiba->element_at(uFrameIndex - 1)->m_rect;

         pdibCompose->get_graphics()->FillSolidRect(r, crBack);

      }

      pdibCompose->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::point pt = pointer->m_rect.top_left();

      ::size sz = pointer->m_rect.size();

      if (uFrameIndex <= 0)
      {

         pdibCompose->create(pdiba->m_size);

      }

      pdibCompose->get_graphics()->BitBlt(pt, sz, pointer->m_dib->get_graphics());

      pointer->m_dib->from(pdibCompose);

   }

   return true;

}