#include "framework.h"


namespace user
{


   namespace uinteraction
   {


      namespace frame
      {


         frame::frame(sp(base_application) papp)
         {

            m_typeinfoControlBox = System.type_info < MetaControlBox >();

            m_rectControlBoxMarginFullScreen.set(0, 0, 0, 0);
            m_rectControlBoxMarginZoomed.set(0, 0, 0, 0);
            m_rectControlBoxMarginNormal.set(0, 0, 0, 0);

            m_rectMarginFullScreen.set(0, 0, 0, 0);
            m_rectMarginZoomed.set(0, 0, 0, 0);
            m_rectMarginNormal.set(5, 5, 5, 5);

            m_iControlBoxRight = 0;
            m_bControlBoxAlignRight = true;

         }


         frame::~frame()
         {
         }

         ::user::front_end_schema * frame::get_user_front_end_schema()
         {

            throw interface_only_exception(get_app());

            return NULL;

         }

         void frame::set_style(const char * pszStyle)
         {

            UNREFERENCED_PARAMETER(pszStyle);

         }


         void frame::OnMove(sp(::user::interaction) pwnd)
         {

            UNREFERENCED_PARAMETER(pwnd);

         }


         void frame::_001OnDraw(::draw2d::graphics * pca)
         {

            UNREFERENCED_PARAMETER(pca);

         }


         size frame::GetMinSize()
         {

            return size(100, 100);

         }


         void frame::OnNcCalcSize(LPRECT lprect)
         {

            UNREFERENCED_PARAMETER(lprect);

         }

         void frame::_000OnBeforeSize(LPCRECT lpcrectWindow)
         {

            UNREFERENCED_PARAMETER(lpcrectWindow);

         }

         void frame::OnActivate()
         {
         }


         void frame::OnAttach()
         {
         }

         bool frame::_000OnCommand(WPARAM wparam, LPARAM lparam, LRESULT & lresult)
         {

            UNREFERENCED_PARAMETER(wparam);
            UNREFERENCED_PARAMETER(lparam);
            UNREFERENCED_PARAMETER(lresult);

            return false;

         }


         void frame::layout()
         {

            reset_layout();

            rect rectWindow;

            rect rectClient;

            sp(::user::interaction) pwndDraw = get_draw_window();

            update_window_client_rect();

            pwndDraw->GetWindowRect(rectWindow);

            pwndDraw->GetClientRect(rectClient);

            get_window_client_rect(rectClient);

            sp(::user::interaction) pwnd = get_window();

            ::user::frame_window * pfrmwnd =
               dynamic_cast <::user::frame_window *>(pwnd.m_p);

            if (pfrmwnd != NULL)
            {
               if (pwnd->GetStyle() & FWS_SNAPTOBARS)
               {
                  rect rect(0, 0, 32767, 32767);
                  pwnd->RepositionBars(0, 0xffff, "pane_first", pwnd->reposQuery,
                     &rect, &rect, FALSE);
                  rect.offset(rectClient.top_left());
                  class rect rectBorder;
                  pfrmwnd->GetBorderRect(rectBorder);
                  pwnd->RepositionBars(0, 0xffff, "pane_first", pwnd->reposExtra,
                     &rectBorder, &rect, TRUE);
                  pfrmwnd->SetBorderRect(rectBorder);
                  pwnd->CalcWindowRect(&rect);
                  OnNcCalcSize(&rect);
                  //rect rectSnap(0, 0, 0, 0);
                  //CalcWndClient(rectSnap, rectSnap);
                  //rect.deflate(rectSnap);
                  pwnd->SetWindowPos(0, 0, 0, rect.width(), rect.height(),
                     SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);

               }
               else
               {
                  rect rectBorder;
                  pfrmwnd->GetBorderRect(rectBorder);
                  pwnd->RepositionBars(0, 0xffff, "pane_first", pwnd->reposExtra, &rectBorder, &rectClient);
                  pfrmwnd->SetBorderRect(rectBorder);
               }
            }

            title_bar_layout(false);

            update_drawing_objects();

            update_window();

            update_window_region(rectWindow);

            if (pwnd->IsWindowVisible())
            {
               pwnd->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

#if !defined(METROWIN) && !defined(LINUX) && !defined(MACOS)
               RedrawWindow(NULL,
                  m_pworkset->m_rectPending,
                  NULL,
                  RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
#endif

               m_pworkset->m_rectPending.set(0, 0, 0, 0);
            }



         }


         COLORREF frame::get_border_main_body_color()
         {

            return 0;

         }


         bool frame::_000OnLButtonDown(::message::mouse * pmouse)
         {

            UNREFERENCED_PARAMETER(pmouse);

            return false;

         }

         bool frame::_000OnLButtonUp(::message::mouse * pmouse)
         {

            UNREFERENCED_PARAMETER(pmouse);

            return false;

         }

         bool frame::_000OnMouseMove(::message::mouse * pmouse)
         {

            UNREFERENCED_PARAMETER(pmouse);

            return false;

         }

         bool frame::_000OnNcLButtonDown(::message::mouse * pmouse)
         {

            UNREFERENCED_PARAMETER(pmouse);

            return false;

         }

         bool frame::_000OnNcLButtonUp(::message::mouse * pmouse)
         {

            UNREFERENCED_PARAMETER(pmouse);

            return false;

         }

         bool frame::_000OnNcMouseMove(::message::mouse * pmouse)
         {

            UNREFERENCED_PARAMETER(pmouse);

            return false;

         }

         bool frame::_000OnNcHitTest(point pt, LRESULT & nHitTest)
         {

            UNREFERENCED_PARAMETER(pt);
            UNREFERENCED_PARAMETER(nHitTest);

            return false;

         }

         bool frame::_000OnTimer(UINT nIDEvent)
         {

            UNREFERENCED_PARAMETER(nIDEvent);

            return false;

         }

         bool frame::_000OnSize(UINT nType, int32_t cx, int32_t cy)
         {

            UNREFERENCED_PARAMETER(nType);
            UNREFERENCED_PARAMETER(cx);
            UNREFERENCED_PARAMETER(cy);

            return false;

         }

         bool frame::_000OnMove(int32_t x, int32_t y)
         {

            UNREFERENCED_PARAMETER(x);
            UNREFERENCED_PARAMETER(y);

            return false;

         }


         //int32_t frame::get_margin()
         //{
         //   int32_t iMargin = m_iMargin;

         //   /*            if (get_appearance()->GetAppearance() == AppearanceZoomed
         //   || get_appearance()->GetAppearance() == AppearanceFullScreen)
         //   {
         //   iMargin = 0;
         //   }*/

         //   return iMargin;
         //}

         void frame::reset_layout()
         {

            m_spcontrolbox->reset_layout();

            m_iCaptionHeight = calc_caption_height();


            /*         m_rectControlBoxMarginFullScreen.left = 0;
                     m_rectControlBoxMarginFullScreen.top = 0;
                     m_rectControlBoxMarginFullScreen.right = 0;
                     m_rectControlBoxMarginFullScreen.bottom = 0;

                     m_rectControlBoxMarginZoomed.left = 0;
                     m_rectControlBoxMarginZoomed.top = 0;
                     m_rectControlBoxMarginZoomed.right = 0;
                     m_rectControlBoxMarginZoomed.bottom = 0;

                     m_rectControlBoxMarginNormal.left = m_iMargin + 3;
                     m_rectControlBoxMarginNormal.top = 3;
                     m_rectControlBoxMarginNormal.right = m_iMargin - 3;
                     m_rectControlBoxMarginNormal.bottom = 0;*/


         }


         int32_t frame::get_caption_height()
         {

            return m_iCaptionHeight;

         }


         int32_t frame::calc_caption_height()
         {

            if (m_pworkset->get_appearance()->GetAppearance() == AppearanceFullScreen)
               return 0;

            rect * prectControlBoxMargin = get_control_box_margin_rect();

            rect * prectMargin = get_margin_rect();

            int32_t iMargin = prectMargin->top + prectControlBoxMargin->top + prectControlBoxMargin->bottom;

            int32_t iCaptionHeight = 0;

            iCaptionHeight = max(m_spcontrolbox->calc_control_box_height() + iMargin, iCaptionHeight);

            return iCaptionHeight;

         }


         int32_t frame::title_bar_layout(bool bInitialControlBoxPosition)
         {

            appearance * pappearance = m_pworkset->get_appearance();

            sp(::user::interaction) pwndDraw = get_draw_window();

            rect * prectControlBoxMargin = get_control_box_margin_rect();

            rect * prectMargin = get_margin_rect();

            int32_t iCaptionHeight = get_caption_height();

            int32_t iButtonSize = m_spcontrolbox->get_button_size();

            rect rectClient;

            pwndDraw->GetWindowRect(rectClient);

            int32_t cx = rectClient.width();

            rect rect;

            m_rectCaption.left = rectClient.left + prectMargin->left + prectControlBoxMargin->left;
            m_rectCaption.top = rectClient.top + prectMargin->top + prectControlBoxMargin->top;
            m_rectCaption.right = rectClient.right - +prectMargin->right + prectControlBoxMargin->right;
            m_rectCaption.bottom = m_rectCaption.top + iButtonSize;


            int iControlBoxHeight = m_spcontrolbox->calc_control_box_height();


            if (bInitialControlBoxPosition)
            {

               int iControlBoxWidthFullScreen = m_spcontrolbox->calc_control_box_full_screen_width();
               int iControlBoxWidthZoomed = m_spcontrolbox->calc_control_box_zoomed_width();
               int iControlBoxWidthNormal = m_spcontrolbox->calc_control_box_normal_width();

               m_rectControlBoxFullScreen.left = cx / 2 - iControlBoxWidthFullScreen / 2;
               m_rectControlBoxFullScreen.right = cx / 2 + iControlBoxWidthFullScreen / 2;
               m_rectControlBoxFullScreen.top = 0;
               m_rectControlBoxFullScreen.bottom = m_rectControlBoxFullScreen.top + iControlBoxHeight;

               m_rectControlBoxZoomed.right = cx - m_rectControlBoxMarginZoomed.right - m_rectMarginZoomed.right;
               m_rectControlBoxZoomed.left = m_rectControlBoxZoomed.right - iControlBoxWidthZoomed;
               m_rectControlBoxZoomed.top = m_rectMarginZoomed.top + m_rectControlBoxMarginZoomed.top;
               m_rectControlBoxZoomed.bottom = m_rectControlBoxZoomed.top + iControlBoxHeight;

               m_rectControlBoxNormal.right = cx - m_rectControlBoxMarginNormal.right - m_rectMarginNormal.right;
               m_rectControlBoxNormal.left = m_rectControlBoxNormal.right - iControlBoxWidthNormal;
               m_rectControlBoxNormal.top = m_rectMarginNormal.top + m_rectControlBoxMarginNormal.top;
               m_rectControlBoxNormal.bottom = m_rectControlBoxNormal.top + iControlBoxHeight;

            }


            ::rect * prectControlBox;

            ::rect rectParent;

            int iControlBoxRightMargin;

            if (m_pworkset->IsFullScreen())
            {

               prectControlBox = &m_rectControlBoxFullScreen;

               Application.get_screen_rect(rectParent);


            }
            else if (pappearance->IsZoomed())
            {

               prectControlBox = &m_rectControlBoxZoomed;

               pwndDraw->GetWindowRect(rectParent);

            }
            else
            {

               prectControlBox = &m_rectControlBoxNormal;

               pwndDraw->GetWindowRect(rectParent);

            }

            rectParent -= rectParent.top_left();

            iControlBoxRightMargin = prectControlBoxMargin->right;

            int x;

            if (!bInitialControlBoxPosition)
            {

               if (m_bControlBoxAlignRight)
               {

                  x = rectClient.width() - m_iControlBoxRight - prectControlBox->width();

               }
               else
               {

                  x = prectControlBox->left;

               }

            }
            else
            {

               x = prectControlBox->left;

            }


            if (x > rectParent.width() - prectMargin->right - prectControlBoxMargin->right - prectControlBox->width())
               x = rectParent.width() - prectMargin->right - prectControlBoxMargin->right - prectControlBox->width();

            if (x < rectParent.left + prectMargin->left + prectControlBoxMargin->left)
               x = rectParent.left + prectMargin->left + prectControlBoxMargin->left;

            int y = prectMargin->top + prectControlBoxMargin->top;

            prectControlBox->top = y;

            prectControlBox->bottom = y + iControlBoxHeight;

            prectControlBox->right = x + prectControlBox->width();

            prectControlBox->left = x;

            get_control_box()->defer_set_window_pos(
               ZORDER_TOP,
               prectControlBox->left,
               prectControlBox->top,
               prectControlBox->width(),
               prectControlBox->height(), SWP_SHOWWINDOW);

            m_rectWindow = rectClient;

            m_pointWindowIcon.x = prectMargin->left + prectControlBoxMargin->left + 5;

            m_pointWindowIcon.y = prectMargin->top + prectControlBoxMargin->top;

            if (pappearance->m_picon != NULL)
            {

               m_rectWindowText.left = m_pointWindowIcon.x + 16 + 2;

            }
            else
            {

               m_rectWindowText.left = m_pointWindowIcon.x;

            }

            m_rectWindowText.top = prectControlBox->top;
            m_rectWindowText.right = rectClient.width() - prectMargin->right;
            m_rectWindowText.bottom = prectControlBox->bottom;

            m_rectCaptionTextBk.left = prectMargin->left;
            m_rectCaptionTextBk.top = prectMargin->top;
            m_rectCaptionTextBk.right = rectClient.width() - prectMargin->right;
            m_rectCaptionTextBk.bottom = prectControlBox->bottom + prectControlBoxMargin->bottom;

            m_rectCaptionTextBk.bottom = prectControlBox->bottom + prectControlBoxMargin->bottom;

            return 0;

         }


         void frame::on_initialize_appearance()
         {

            if (m_spcontrolbox.is_null())
            {
               m_spcontrolbox = Application.alloc(m_typeinfoControlBox);
               m_spcontrolbox->m_pworkset = m_pworkset;
               sp(::user::interaction) pwnd = m_pworkset->get_draw_window();
               m_spcontrolbox->create(pwnd, 1);
            }

            m_spcontrolbox->update_control_box_buttons();

            on_style_change();

            update_drawing_objects();

            update_window();

         }



         sp(control_box) frame::get_control_box()
         {

            return m_spcontrolbox;

         }


         void frame::update_window_style()
         {

         }


         void frame::update_window()
         {

            update_window_style();

         }


         void frame::get_window_client_rect(LPRECT lprect)
         {
            *lprect = m_rectClient;
         }

         void frame::get_draw_client_rect(LPRECT lprect)
         {
            rect rect;
            get_window_client_rect(rect);
            rect.offset(-rect.top_left());
            *lprect = rect;
         }


         void frame::update_drawing_objects()
         {

         }


         void frame::update_window_client_rect()
         {

            sp(::user::interaction) pwnd = get_window();

            ASSERT(pwnd != NULL);

            if (pwnd == NULL)
               return;

            rect rectClient;

            pwnd->::user::interaction::GetClientRect(rectClient);

            calc_window_client_rect(m_rectClient, rectClient);

         }


         sp(::user::interaction) frame::get_draw_window()
         {

            return get_window();

         }


         sp(::user::interaction) frame::get_window()
         {
            try
            {
               return m_pworkset->GetEventWindow();
            }
            catch (...)
            {
               return NULL;
            }

         }


         void frame::update_window_region(LPCRECT lpcrect)
         {

            UNREFERENCED_PARAMETER(lpcrect);

         }


         void frame::on_style_change()
         {

         }

         void frame::calc_window_client_rect(LPRECT lprect, LPCRECT lprectWindow)
         {

            rect rect(lprectWindow);

            ::rect * prectMargin = get_margin_rect();

            rect.deflate(prectMargin->left, get_caption_height(), prectMargin->bottom, prectMargin->right);

            *lprect = rect;

         }


         rect * frame::get_margin_rect()
         {

            if (m_pworkset->get_appearance()->GetAppearance() == AppearanceFullScreen)
            {

               return &m_rectMarginFullScreen;

            }
            else if (m_pworkset->get_appearance()->GetAppearance() == AppearanceZoomed)
            {

               return &m_rectMarginZoomed;

            }
            else
            {

               return &m_rectMarginNormal;

            }

         }


         rect * frame::get_control_box_margin_rect()
         {

            if (m_pworkset->get_appearance()->GetAppearance() == AppearanceFullScreen)
            {

               return &m_rectControlBoxMarginFullScreen;

            }
            else if (m_pworkset->get_appearance()->GetAppearance() == AppearanceZoomed)
            {

               return &m_rectControlBoxMarginZoomed;

            }
            else
            {

               return &m_rectControlBoxMarginNormal;

            }

         }


         rect * frame::get_control_box_rect()
         {

            if(m_pworkset->get_appearance()->GetAppearance() == AppearanceFullScreen)
            {

               return &m_rectControlBoxFullScreen;

            }
            else if(m_pworkset->get_appearance()->GetAppearance() == AppearanceZoomed)
            {

               return &m_rectControlBoxZoomed;

            }
            else
            {

               return &m_rectControlBoxNormal;

            }

         }


      } // namespace frame


   } // namespace frame



} // namespace user












