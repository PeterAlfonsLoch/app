#pragma once

class rect_array;

namespace user
{

   class CLASS_DECL_ca window_redraw_interface  
   {
   public:

      virtual bool Redraw(rect_array & recta) = 0;
      virtual bool Redraw(LPCRECT lprect = NULL, ::ca::rgn * prgn = NULL) = 0;
      virtual bool Redraw(::ca::graphics * pdc) = 0;

   };


} // namespace user