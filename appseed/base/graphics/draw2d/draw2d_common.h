#pragma once



namespace draw2d
{

   class graphics;

   CLASS_DECL_BASE void vertical_swap_copy_colorref(int cx, int cy, COLORREF * pcolorrefDst, int iStrideDst, COLORREF * pcolorrefSrc, int iStrideSrc);
   CLASS_DECL_BASE void copy_colorref(int cx, int cy, COLORREF * pcolorrefDst, int iStrideDst, COLORREF * pcolorrefSrc, int iStrideSrc);
   CLASS_DECL_BASE void copy_colorref(int x, int y, int cx, int cy, COLORREF * pcolorrefDst, int iStrideDst, COLORREF * pcolorrefSrc, int iStrideSrc);

} // namespace draw2d

#if defined(CUBE) || defined(VSNORD)


extern "C"
void draw2d_factory_exchange(::aura::application * papp);


#endif





