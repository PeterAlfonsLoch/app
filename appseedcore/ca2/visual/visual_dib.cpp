#include "StdAfx.h"
#include "include/FreeImage.h"

namespace visual
{
   dib_sp::dib_sp()
   {
   }

   dib_sp::dib_sp(::ca::application * papp) :
      ::ca::dib_sp(papp)
   {
   }

   dib_sp::~dib_sp()
   {
   }


   bool dib_sp::from(::ca::graphics * pgraphics, FIBITMAP *pfibitmap, bool bUnloadFI)
   {
      if(pfibitmap == NULL)
           return false;

      BITMAPINFO * pbi = FreeImage_GetInfo(pfibitmap);
      void * pdata = FreeImage_GetBits(pfibitmap);

      if(!m_p->create(pbi->bmiHeader.biWidth, pbi->bmiHeader.biHeight))
         return false;

      m_p->dc_select(false);

      if(pbi->bmiHeader.biHeight != SetDIBits(
         (HDC) pgraphics->get_os_data(),
         (HBITMAP) m_p->get_bitmap()->get_os_data(),
         0,
         pbi->bmiHeader.biHeight,
         pdata,
         pbi,
         DIB_RGB_COLORS))
      {
         m_p->dc_select(true);
         if(bUnloadFI)
         {
            FreeImage_Unload(pfibitmap);
         }
         return false;
      }

      if(pbi->bmiHeader.biBitCount <= 24 && FreeImage_GetTransparencyCount(pfibitmap) <= 0)
      {
         m_p->fill_channel(0xff, ::visual::rgba::channel_alpha);
      }

      m_p->dc_select(true);
       
      if(bUnloadFI)
      {
         FreeImage_Unload(pfibitmap);
      }
      return true;
   }


   bool dib_sp::load_from_file(var varFile)
   {
      FIBITMAP * pfi = System.imaging().LoadImageFile(varFile, get_app());
      if(pfi == NULL)
         return false;
      ::ca::graphics_sp spgraphics(get_app());
      spgraphics->CreateCompatibleDC(NULL);
      if(!from(spgraphics, pfi, true))
         return false;
      return true;
   }

   bool dib_sp::load_from_matter(const char * pszMatter)
   {
      return load_from_file(System.dir().matter(pszMatter));
   }





} // namespace visual