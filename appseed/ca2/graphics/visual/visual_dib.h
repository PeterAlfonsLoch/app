#pragma once

struct FIBITMAP;

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

   class CLASS_DECL_ca2 save_image
   {
   public:


      image::e_format       m_eformat;


      save_image();

   };

   class CLASS_DECL_ca2 dib_sp :
      public ::draw2d::dib_sp
   {
   public:

      dib_sp();
      dib_sp(allocatorsp allocer);
      virtual ~dib_sp();





      virtual bool load_from_file(var varFile);
      virtual bool load_from_matter(const char * pszMatter);
      virtual bool read_from_file(sp(::file::file) pfile);


      virtual bool save_to_file(var varFile, save_image * psaveimage = NULL);
      virtual bool write_to_file(sp(::file::file) pfile, save_image * psaveimage = NULL);


   };

} // namespace visual
