#include "framework.h"


namespace html
{


   namespace impl
   {


      void image::_001OnDraw(data * pdata)
      {

         if(m_pelemental->m_pbase->get_type() == ::html::base::type_tag)
         {

            pdata->m_pdc->set_alpha_mode(::ca::alpha_mode_blend);

            pdata->m_pdc->BitBlt((int32_t) get_x(), (int32_t) get_y(), (int32_t) get_cx(), (int32_t) get_cy(), 
                                 pdata->m_imagea[m_iImage].m_spdib->get_graphics(), 0, 0, SRCCOPY);

         }

      }


      void image::implement_phase1(data * pdata, ::html::elemental * pelemental)
      {
         elemental::implement_phase1(pdata, pelemental);
         if(pelemental->m_pbase->get_type() == ::html::base::type_tag)
         {
            m_iImage = pdata->get_image_index(pelemental->m_propertyset["src"]);
            synch_lock lockImage(Sys(pdata->m_papp).get_twf());
            m_cxMax = (float) pdata->m_imagea[m_iImage].m_spdib->cx;
            m_cxMin = (float) pdata->m_imagea[m_iImage].m_spdib->cy;
         }
      }

      void image::layout_phase3(data * pdata)
      {
         if(m_pelemental->m_pbase->get_type() == ::html::base::type_tag)
         {
            single_lock lockImage(&pdata->m_imagea[m_iImage]);

            if(lockImage.lock(duration::zero()))
            {
               pdata->m_layoutstate.m_cx = (float) pdata->m_imagea[m_iImage].m_spdib->cx;
               if(pdata->m_imagea[m_iImage].m_spdib->cy > pdata->m_layoutstate.m_cy)
               {
                  pdata->m_layoutstate.m_cy = (float) pdata->m_imagea[m_iImage].m_spdib->cy;
               }
            }
            else
            {
               pdata->m_layoutstate.m_cx = 0;
               pdata->m_layoutstate.m_cy = 0;
            }

            m_box.set_cxy(pdata->m_imagea[m_iImage].m_spdib->size());

         }

      }


   } // namespace impl


} // namespace html_impl


