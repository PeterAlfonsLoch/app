#pragma once

struct FIBITMAP;


#include <ft2build.h>


#include FT_FREETYPE_H

namespace visual
{

   namespace image
   {

      enum e_format
      {
         format_png,
         format_bmp,
         format_gif,
         format_jpeg,
      };

   } // namespace image

   class CLASS_DECL_CORE save_image
   {
   public:


      image::e_format         m_eformat;
      int                     m_iQuality;

      save_image();

   };

   class CLASS_DECL_CORE dib_sp :
      public ::draw2d::dib_sp
   {
   public:

      dib_sp();
      dib_sp(allocatorsp allocer);
      virtual ~dib_sp();





      virtual bool load_from_file(var varFile);
      virtual bool load_from_matter(const char * pszMatter);
      virtual bool read_from_file(::file::buffer_sp  pfile);


      virtual bool save_to_file(var varFile, save_image * psaveimage = NULL);
      virtual bool write_to_file(::file::buffer_sp  pfile, save_image * psaveimage = NULL);


      virtual bool from(::draw2d::graphics * pgraphics, FIBITMAP * pfibitmap, bool bUnloadFI);

      virtual void draw_bitmap(int32_t dx, int32_t dy, FT_Bitmap * bitmap, FT_Int x, FT_Int y);


   };


} // namespace visual




