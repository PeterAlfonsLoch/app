#pragma once



namespace ca
{

   // backlink from ca2.dll on 2012-10-14 11:04 Alameda Princesa Izabel, 3000 - CWB-PR-Brasil

   enum e_alpha_mode
   {
      alpha_mode_set,
      alpha_mode_blend,
   };

   enum e_fill_mode
   {
      fill_mode_winding,
      fill_mode_alternate,
   };


} // namespace ca


class simple_brush;
class simple_bitmap;
class simple_font;
class simple_pen;


class simple_path;


class simple_graphics;


#define GetAValue(rgb)      (LOBYTE((rgb)>>24))
#define ARGB(a, r, g, b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))









