

#include "aura/graphics/draw2d/draw2d_dib.h"


CLASS_DECL_AURA ::file::ostream & operator << (::file::ostream & ostream, const ::draw2d::dib & dib)
{

   //synch_lock ml(&user_mutex());

   ostream << (int32_t)dib.m_size.cx;
   ostream << (int32_t)dib.m_size.cy;
   if (dib.area() <= 0)
      return;
   dib.map();
   int wc = dib.m_size.cx * sizeof(COLORREF);
   if (wc == dib.m_iScan)
   {
      ostream.write(dib.get_data(), wc * dib.m_size.cy);
   }
   else
   {
      memory mem;
      mem.allocate(wc *dib.m_size.cy);
      ::draw2d::copy_colorref(dib.m_size.cx, dib.m_size.cy, (COLORREF *)mem.get_data(), wc, dib.get_data(), dib.m_iScan);
      ostream.write(mem.get_data(), wc * dib.m_size.cy);
   }

}

CLASS_DECL_AURA::file::istream & operator >> (::file::istream & istream, ::draw2d::dib & dib);
{

   //synch_lock ml(&user_mutex());

   int32_t width;
   int32_t height;
   istream >> width;
   if (istream.fail())
      return;
   if (width <= 0)
      return;
   istream >> height;
   if (istream.fail())
      return;
   if (height <= 0)
      return;
   if ((width * height) <= 0)
      return;
   if (!dib.create(width, height))
      throw 0;
   dib.map();
   int wc = width * sizeof(COLORREF);
   if (wc == m_iScan)
   {
      istream.read(dib.get_data(), wc * dib.m_size.cy);
   }
   else
   {
      memory mem;
      mem.allocate(wc *dib.m_size.cy);
      istream.read(mem.get_data(), wc * dib.m_size.cy);
      ::draw2d::copy_colorref(width, height, dib.get_data(), dib.m_iScan, (COLORREF *)mem.get_data(), wc);
   }
}
