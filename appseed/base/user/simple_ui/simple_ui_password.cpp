#include "framework.h"


namespace simple_ui
{




   password::password(sp(::base::application) papp) :
      element(papp),
      edit_box(papp)
   {

   }

   password::~password()
   {
   }




   void password::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      rect rectClient;

      GetClientRect(rectClient);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::draw2d::brush_sp br(allocer());

      br->create_solid(ARGB(184, 255, 255, 240));

      pgraphics->FillRect(rectClient, br);

      simple_ui_draw_focus_rect(pgraphics);

      br->create_solid(ARGB(223, 49, 49, 23));

      pgraphics->SelectObject(br);

      ::draw2d::font_sp f(allocer());

      f->create_pixel_font("Geneva", (int32_t)height(rectClient) * 0.7);

      pgraphics->SelectObject(f);

      string str;

      string strText;

      GetWindowText(strText);

      str.append(strText.get_length(), '*');

      pgraphics->TextOut(rectClient.left + 2, rectClient.top, str);

   }











} // namespace simple_ui



