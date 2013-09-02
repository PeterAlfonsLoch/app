#include "framework.h"


namespace uinteraction
{


   namespace frame
   {


      frame::frame(sp(::application) papp)
      {
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

      void frame::OnInitializeAppearance()
      {
      }

      void frame::OnAppearanceModeChange()
      {
      }

      int32_t frame::UpdateControlBox()
      {

         return 0;

      }


      void frame::OnMove(sp(::user::interaction) pwnd)
      {

         UNREFERENCED_PARAMETER(pwnd);

      }


      void frame::_001OnDraw(::draw2d::graphics * pca)
      {

         UNREFERENCED_PARAMETER(pca);

      }


      void frame::GetWndClientRect(LPRECT lprect)
      {

         UNREFERENCED_PARAMETER(lprect);

      }

      size frame::GetMinSize()
      {

         return size(100, 100);

      }


      void frame::SetControlBoxButtonId(e_button ebutton, id id)
      {
         m_mapButtonId[ebutton] = id;
         m_mapIdButton[id] = ebutton;
      }

      id frame::GetControlId(e_button ebutton)
      {
         return m_mapButtonId[ebutton];
      }

      frame::e_button frame::GetButtonId(id id)
      {
         return m_mapIdButton[id];
      }

      void frame::hide_button(e_button ebutton, bool bHide)
      {
         m_buttonmapPresent[ebutton] = !bHide;
      }

      bool frame::has_button(e_button ebutton)
      {
         bool bPresent;
         if(m_buttonmapPresent.Lookup(ebutton, bPresent))
            return bPresent;
         else
         {
            m_buttonmapPresent[ebutton] = true;
            return true;
         }
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
      }


      COLORREF frame::get_border_main_body_color()
      {

         return 0;

      }


      bool frame::_000OnLButtonDown(::ca2::message::mouse * pmouse)
      {

         UNREFERENCED_PARAMETER(pmouse);

         return false;

      }

      bool frame::_000OnLButtonUp(::ca2::message::mouse * pmouse)
      {

         UNREFERENCED_PARAMETER(pmouse);

         return false;

      }

      bool frame::_000OnMouseMove(::ca2::message::mouse * pmouse)
      {

         UNREFERENCED_PARAMETER(pmouse);

         return false;

      }

      bool frame::_000OnNcLButtonDown(::ca2::message::mouse * pmouse)
      {

         UNREFERENCED_PARAMETER(pmouse);

         return false;

      }

      bool frame::_000OnNcLButtonUp(::ca2::message::mouse * pmouse)
      {

         UNREFERENCED_PARAMETER(pmouse);

         return false;

      }

      bool frame::_000OnNcMouseMove(::ca2::message::mouse * pmouse)
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


   } // namespace frame


} // namespace frame




