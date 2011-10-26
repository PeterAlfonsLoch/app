#include "StdAfx.h"

namespace html
{

   namespace impl
   {

      void image::_001OnDraw(data * pdata)
      {
         if(m_pelemental->m_pbase->get_type() == html::base::type_tag)
         {
            ::ca::graphics_sp spgraphics(pdata->get_app());
            spgraphics->CreateCompatibleDC(NULL);
            BLENDFUNCTION bf;
            memset(&bf, 0, sizeof(bf));
            bf.SourceConstantAlpha = 255;
            bf.BlendOp = AC_SRC_OVER;
            bf.AlphaFormat = AC_SRC_ALPHA;
            single_lock lockImage(&pdata->m_imagea[m_iImage]);
            if(lockImage.lock(duration::zero()))
            {
               pdata->m_pdc->alpha_blend(
                  get_x(), get_y(), get_cx(), get_cy(),
                  pdata->m_imagea[m_iImage].m_spdib->get_graphics(),
                  0, 0, get_cx(), get_cy(),
                  bf);
            }
         }
      }

      void image::implement_phase1(data * pdata, ::html::elemental * pelemental)
      {
         elemental::implement_phase1(pdata, pelemental);
         if(pelemental->m_pbase->get_type() == html::base::type_tag)
         {
            m_iImage = pdata->get_image_index(pelemental->m_propertyset["src"]);
            synch_lock lockImage(Sys(pdata->m_papp).get_twf());
            m_cxMax = pdata->m_imagea[m_iImage].m_spdib->width();
            m_cxMin = pdata->m_imagea[m_iImage].m_spdib->height();
         }
      }

      void image::layout_phase3(data * pdata)
      {
         if(m_pelemental->m_pbase->get_type() == html::base::type_tag)
         {
            single_lock lockImage(&pdata->m_imagea[m_iImage]);

            if(lockImage.lock(duration::zero()))
            {
               pdata->m_layoutstate.m_cx = pdata->m_imagea[m_iImage].m_spdib->width();
               if(pdata->m_imagea[m_iImage].m_spdib->height() > pdata->m_layoutstate.m_cy)
               {
                  pdata->m_layoutstate.m_cy = pdata->m_imagea[m_iImage].m_spdib->height();
               }
            }
            else
            {
               pdata->m_layoutstate.m_cx = 0;
               pdata->m_layoutstate.m_cy = 0;
            }

            m_size.cx = pdata->m_imagea[m_iImage].m_spdib->width();
            m_size.cy = pdata->m_imagea[m_iImage].m_spdib->height();
         }
      }

   } // namespace impl

} // namespace html_impl