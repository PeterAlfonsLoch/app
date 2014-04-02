#include "framework.h"


namespace uinteraction
{



   namespace frame
   {


      appearance::CTool001::CTool001(sp(base_application) papp) :
         element(papp)
      {
      }

      appearance::appearance(WorkSet * pworkset) :
         element(pworkset->get_app())
      {
         m_ptool001 = new CTool001(get_app());
         m_bAutomaticModeSwitching = true;
         m_pwndframeworkdownupinterface = this;
         m_bEnabled = true;
         m_pworkset = pworkset;
         m_bUseNc = false;
         m_nTransparency = Transparent;
      }

      appearance::~appearance()
      {

      }

      sp(::user::interaction) appearance::get_window()
      {
         return m_pworkset->GetRegionWindow();
      }

      bool appearance::update()
      {
         if(m_pworkset == NULL)
            return false;


         try
         {

            m_pworkset->m_pframeschema->on_initialize_appearance();

         }
         catch(...)
         {

         }

         //      sp(::user::interaction) pwnd = get_window();

         return true;
      }


      void appearance::Enable(bool bEnable)
      {

         m_bEnabled = bEnable;

         if(m_pworkset != NULL)
         {

            if(m_pworkset->m_pframeschema != NULL)
            {

               m_pworkset->m_pframeschema->title_bar_layout(false);

            }

         }

      }


      bool appearance::IsEnabled()
      {
         return m_bEnabled;
      }

      void appearance::SetAppearanceMode(EAppearanceMode emode)
      {
         if(m_pworkset == NULL)
            return;
         ASSERT(m_pworkset != NULL);

         EAppearanceMode emodeOld = m_emode;
         EAppearanceMode emodeNew = emode;

         m_emode = emode;

         if(emodeOld != emodeNew
            && m_pworkset->m_pframeschema != NULL)
         {
            ASSERT(m_pworkset->m_pframeschema != NULL);
            m_pworkset->m_pframeschema->on_appearance_mode_change();
         }
      }


      void appearance::SetTransparency(EAppearanceTransparency nTransparency)
      {
         m_nTransparency = nTransparency;
      }

      void appearance::SetAppearanceMode()
      {
         sp(::user::interaction) pwnd = get_window();

         if(pwnd == NULL)
            return;
         if(pwnd->IsZoomed())
            SetAppearanceMode(AppearanceModeZoomed);
         else if(pwnd->IsIconic())
            SetAppearanceMode(AppearanceModeIconic);
         else
            SetAppearanceMode(AppearanceModeNormal);
      }

      EAppearanceMode appearance::GetAppearanceMode()
      {
         return m_emode;
      }



      bool appearance::IsZoomed()
      {
         return GetAppearanceMode() == AppearanceModeZoomed;
      }

      bool appearance::IsFullScreen()
      {
         return GetAppearanceMode() == AppearanceModeFullScreen;
      }

      bool appearance::IsIconic()
      {
         return GetAppearanceMode() == AppearanceModeIconic;
      }

      bool appearance::WndFrameworkDownUpGetUpEnable()
      {
         CWorkSetDownUpInterface * pinterface = m_pwndframeworkdownupinterface;
         //dynamic_cast<CWorkSetDownUpInterface *>(get_draw_window());
         if(pinterface != NULL
            && pinterface != this)
         {
            return pinterface->WndFrameworkDownUpGetUpEnable();
         }
         else
            return false;
      }

      bool appearance::WndFrameworkDownUpGetDownEnable()
      {

         CWorkSetDownUpInterface * pinterface = m_pwndframeworkdownupinterface;
         //dynamic_cast<CWorkSetDownUpInterface *>(get_draw_window());
         if(pinterface != NULL
            && pinterface != this)
         {
            return pinterface->WndFrameworkDownUpGetDownEnable();
         }
         else
            return false;
      }


      void appearance::frame_Attach()
      {
         CWorkSetDownUpInterface * pinterface = m_pwndframeworkdownupinterface;
         if(pinterface != NULL
            && pinterface != this)
         {
            return pinterface->frame_Attach();
         }
      }

      void appearance::frame_Detach()
      {
         CWorkSetDownUpInterface * pinterface = m_pwndframeworkdownupinterface;
         if(pinterface != NULL
            && pinterface != this)
         {
            return pinterface->frame_Detach();
         }
      }


      void appearance::SetDownUpInterface(CWorkSetDownUpInterface *pinterface)
      {
         m_pwndframeworkdownupinterface = pinterface;
      }

      void appearance::UpdateAppearanceMode(bool bFullScreen)
      {
         sp(::user::interaction) pwnd = m_pworkset->get_draw_window();

         if(pwnd->IsIconic())
         {
            m_emode = AppearanceModeIconic;
         }
         else if(pwnd->IsZoomed())
         {
            m_emode = AppearanceModeZoomed;
         }
         else if(bFullScreen)
         {
            m_emode = AppearanceModeFullScreen;
         }
         else
         {
            m_emode = AppearanceModeNormal;
         }
      }

      void appearance::SetAutomaticModeSwitching(bool bSetting)
      {
         m_bAutomaticModeSwitching = bSetting;
      }

      bool appearance::IsInAutomaticModeSwitching()
      {

         sp(::database::user::interaction) pui =  (get_window().m_p);

         if(pui != NULL && !pui->does_display_match())
            return false;

         if(GetAppearanceMode() == AppearanceModeFullScreen)
            return false;

         return m_bAutomaticModeSwitching;

      }

      void appearance::CTool001::Update(::draw2d::graphics * pdc, LPCRECT lpcrect,
         COLORREF crHighlight,
         COLORREF crLight,
         COLORREF crBody,
         COLORREF crShadow,
         COLORREF crDkShadow)
      {

         UNREFERENCED_PARAMETER(crLight);

         m_penHighlight->create_solid(1, crHighlight);
         m_penLight->create_solid(1, crHighlight);
         m_penShadow->create_solid(1, crShadow);
         m_penDkShadow->create_solid(1, crDkShadow);
         m_brushNull->create_null();
         m_brushBody->create_solid(crBody);

         m_colorbezieraOutsideBorder.remove_all();
         rect rectClient(lpcrect);
         rect rectA(rectClient);
         rectA.deflate(3, 3, 3, 3);
         rect rectB(rectClient);
         rectB.deflate(18, 18, 18, 18);
         rect rectC(rectClient);
         rectC.deflate(7, 7, 7, 7);

         const int32_t ciStart = 4;
         const int32_t ciCurve = 2;


         CColorBezier bezier;




         // top left corner

         // top left corner - bottom left corner
         bezier.m_pointset.add(rectA.left, rectB.top + ciStart);
         bezier.m_pointset.add(rectA.left, rectB.top + ciCurve);
         bezier.m_pointset.add(rectA.left + ciCurve, rectB.top);
         bezier.m_pointset.add(rectA.left + ciStart, rectB.top);
         bezier.m_ppen = m_penHighlight;
         m_colorbezieraOutsideBorder.add(bezier);


         // top left corner - bottom horizontal
         bezier.clear();
         bezier.m_pointset.add(rectA.left + ciStart, rectB.top);
         bezier.m_pointset.add(rectC.left - ciStart, rectB.top);
         bezier.m_pointset.add(rectC.left - ciStart, rectB.top);
         bezier.m_pointset.add(rectC.left - ciStart, rectB.top);
         bezier.m_ppen = m_penLight;
         m_colorbezieraOutsideBorder.add(bezier);

         // top left corner - bottom middle corner
         bezier.clear();
         bezier.m_pointset.add(rectC.left - ciStart, rectB.top);
         bezier.m_pointset.add(rectC.left - ciCurve, rectB.top);
         bezier.m_pointset.add(rectC.left, rectB.top - ciCurve);
         bezier.m_pointset.add(rectC.left, rectB.top - ciStart);
         bezier.m_ppen = m_penDkShadow;
         m_colorbezieraOutsideBorder.add(bezier);

         // top left corner - middle vertical
         bezier.clear();
         bezier.m_pointset.add(rectC.left, rectB.top - ciStart);
         bezier.m_pointset.add(rectC.left, rectC.top + ciStart);
         bezier.m_pointset.add(rectC.left, rectC.top + ciStart);
         bezier.m_pointset.add(rectC.left, rectC.top + ciStart);
         bezier.m_ppen = m_penLight;
         m_colorbezieraOutsideBorder.add(bezier);

         // top left corner - middle corner
         bezier.clear();
         bezier.m_pointset.add(rectC.left, rectC.top + ciStart);
         bezier.m_pointset.add(rectC.left, rectC.top + ciCurve);
         bezier.m_pointset.add(rectC.left + ciCurve, rectC.top);
         bezier.m_pointset.add(rectC.left + ciStart, rectC.top);
         bezier.m_ppen = m_penHighlight;
         m_colorbezieraOutsideBorder.add(bezier);

         // top left corner - middle horizontal
         bezier.clear();
         bezier.m_pointset.add(rectC.left + ciStart, rectC.top);
         bezier.m_pointset.add(rectB.left - ciStart, rectC.top);
         bezier.m_pointset.add(rectB.left - ciStart, rectC.top);
         bezier.m_pointset.add(rectB.left - ciStart, rectC.top);
         bezier.m_ppen = m_penLight;
         m_colorbezieraOutsideBorder.add(bezier);

         // top left corner - bottom middle corner
         bezier.clear();
         bezier.m_pointset.add(rectB.left - ciStart, rectC.top);
         bezier.m_pointset.add(rectB.left - ciCurve, rectC.top);
         bezier.m_pointset.add(rectB.left, rectC.top - ciCurve);
         bezier.m_pointset.add(rectB.left, rectC.top - ciStart);
         bezier.m_ppen = m_penDkShadow;
         m_colorbezieraOutsideBorder.add(bezier);

         // top left corner - right vertical
         bezier.clear();
         bezier.m_pointset.add(rectB.left, rectC.top - ciStart);
         bezier.m_pointset.add(rectB.left, rectA.top + ciStart);
         bezier.m_pointset.add(rectB.left, rectA.top + ciStart);
         bezier.m_pointset.add(rectB.left, rectA.top + ciStart);
         bezier.m_ppen = m_penLight;
         m_colorbezieraOutsideBorder.add(bezier);


      }

      void appearance::CTool001::draw(::draw2d::graphics * pdc)
      {

         pdc->SelectObject(m_brushBody);

         ::draw2d::pen_sp pen(allocer());

         pen->create_solid(0, RGB(255, 255, 255));

         pdc->SelectObject(pen);

         point pt(0, 0);

         System.visual().api().DrawAndFillBeziers(
            pdc,
            m_pointsetBody.get_data(),
            (int32_t) m_pointsetBody.get_size(),
            1.0,
            &pt);

         for(int32_t i = 0; i < m_colorbezieraOutsideBorder.get_size(); i++)
         {
            CColorBezier & bezier = m_colorbezieraOutsideBorder[i];
            bezier.draw(*m_brushNull, pdc);
         }

      }

      void appearance::CTool001::CColorBezier::draw(::draw2d::brush & brush, ::draw2d::graphics * pdc)
      {
         pdc->SelectObject(&brush);
         pdc->SelectObject(m_ppen);
         point pt(0, 0);

         Sys(pdc->get_app()).visual().api().DrawAndFillBeziers(
            pdc,
            m_pointset.get_data(),
            (int32_t) m_pointset.get_size(),
            1.0,
            &pt);

      }

      void  appearance::CTool001::CColorBezier::clear()
      {
         m_pointset.remove_all();
      }

      bool appearance::IsNotifyIconEnabled()
      {
         return m_pworkset->IsNotifyIconEnabled();
      }


      sp(::uinteraction::frame::control_box_button) appearance::get_box_button(e_button ebutton)
      {

         throw interface_only_exception(get_app());

         return NULL;

      }


   } // namespace frame


} // namespace uinteraction






