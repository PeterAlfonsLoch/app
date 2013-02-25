#include "framework.h"


void DoBar(::ca::graphics * pdc, int32_t ileft, int32_t iTop, int32_t cx, int32_t cy, double dAnime)
{
   int32_t iDeltaDark = 23;
      int32_t iDeltaVermelho = 77;
      int32_t iDeltaAzul = 84;
      int32_t iDeltaV1 = 23;
      int32_t iDeltaV2 = 23;
      int32_t iW = 49;
      int32_t x = ileft;
      double dSoft = 184.6;
      int32_t iRight = ileft + cx;
      int32_t iMaxW = iRight - iW;
      COLORREF cr;
      for(x = ileft; x < iMaxW; x+=iW)
      {
       cr = RGB(
         255 - iDeltaVermelho - iDeltaDark,
         ( 255 - (iDeltaV2 / 2.0) +(int32_t) (sin((double)x / dSoft + dAnime)  *( iDeltaV2 / 2.0))) - iDeltaV1 - iDeltaDark,
         255 - iDeltaAzul - 23 - iDeltaDark);
         pdc->FillSolidRect(x, iTop, iW, cy, cr);
      }
      if(x < iRight)
      {
       cr = RGB(
         255 - iDeltaVermelho - iDeltaDark,
         ( 255 - (iDeltaV2 / 2.0) +(int32_t) (sin((double)x / dSoft + dAnime)  *( iDeltaV2 / 2.0))) - iDeltaV1 - iDeltaDark,
         255 - iDeltaAzul - 23 - iDeltaDark);
         pdc->FillSolidRect(x, iTop, iRight - x, cy, cr);
      }
}


file_manager_operation_info_view::file_manager_operation_info_view(::ca::application * papp) :
   ca(papp),
   ::userbase::view(papp)
{
   m_dAnime = 0.0;
}


void file_manager_operation_info_view::OnDraw(::ca::graphics * pdc)
{
   UNREFERENCED_PARAMETER(pdc);
}

void file_manager_operation_info_view::_001OnDraw(::ca::graphics * pdc)
{
      /*::FillRect(hdc, &rectProgress, g_hbrushProgress3);
      rectProgress.left++;
      rectProgress.right--;
      rectProgress.top++;
      rectProgress.bottom--;*/
   rect rectClient;
   GetClientRect(rectClient);
      int32_t iLineCount = 23;
      double dBarHeight = (double) rectClient.height() / (double) iLineCount;
      double dTop = 0.0;
      RECT rectProgress;
      rectProgress = rectClient;
      //rectProgress.left += 23;
      //rectProgress.right -= 23;
      rectProgress.top += (LONG) dTop;
      rectProgress.bottom = (LONG) (dTop + dBarHeight);
      double dProgressL = 0.0;
      double dProgressU;
      double dProgressD = 1.0 / (double) iLineCount;
      RECT rectBar;
      double dProgress;
      dProgress = get_document()->m_thread.get_progress_rate();
      for(int32_t iLine = 0; iLine < iLineCount; iLine++)
      {

         rectBar = rectProgress;
         dProgressU = dProgressL + dProgressD;
         if(dProgress < dProgressU)
         {
            pdc->FillSolidRect(&rectProgress, RGB(255, 240, 200));
         }
         if(dProgress > dProgressL)
         {
            if(dProgress < dProgressU)
            {
               rectBar.right = ((int32_t) ((rectProgress.right - rectProgress.left) * (dProgress - dProgressL) * ((double) iLineCount) )) + rectProgress.left;
            }
            DoBar(pdc, rectBar.left, rectBar.top,
               rectBar.right - rectBar.left, rectBar.bottom - rectBar.top, m_dAnime);
         }
         dTop += dBarHeight;
         rectProgress.top = (LONG) dTop;
         rectProgress.bottom = (LONG) (dTop + dBarHeight);
         dProgressL = dProgressU;
      }
      //::FillRect(hdc, &rectProgress, g_hbrushProgress1);

}

void file_manager_operation_info_view::OnFileOperationStep(int32_t iOperation, bool bFinal)
{
   UNREFERENCED_PARAMETER(iOperation);
   UNREFERENCED_PARAMETER(bFinal);
}

file_manager_operation_document * file_manager_operation_info_view::get_document()
{
   return dynamic_cast < file_manager_operation_document * > (::userbase::view::get_document());
}

void file_manager_operation_info_view::_001OnTimer(::ca::signal_object * pobj)
{
   SCAST_PTR(::ca::message::timer, ptimer, pobj);
   if(ptimer->m_nIDEvent == 123)
   {
   }
}

void file_manager_operation_info_view::_001OnCreate(::ca::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   //SetTimer(123, 184, NULL);
}

void file_manager_operation_info_view::install_message_handling(::ca::message::dispatch * pinterface)
{
   ::userbase::view::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &file_manager_operation_info_view::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &file_manager_operation_info_view::_001OnTimer);
}

void file_manager_operation_info_view::assert_valid() const
{
   ::userbase::view::assert_valid();
}
void file_manager_operation_info_view::dump(dump_context & context) const
{
   ::userbase::view::dump(context);
}

