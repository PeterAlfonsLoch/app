#pragma once


namespace fontopus
{


   // attributes
   CLASS_DECL_BOOT bool get_visible();


   // message handling
   CLASS_DECL_BOOT void on_lbutton_up(int32_t x, int32_t y);
   CLASS_DECL_BOOT void on_lbutton_down(int32_t x, int32_t y);
   CLASS_DECL_BOOT void on_mouse_move(int32_t x, int32_t y);
   CLASS_DECL_BOOT void on_char(int32_t iKey, const string & strChar);


   // callback/implementation
   CLASS_DECL_BOOT void draw(ID2D1DeviceContext * pctx);


} // namespace fontopus




