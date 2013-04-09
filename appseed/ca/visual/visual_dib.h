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

   class CLASS_DECL_ca save_image
   {
   public:
      
      
      image::e_format       m_eformat;


      save_image();

   };

   class CLASS_DECL_ca dib_sp :
      public ::ca::dib_sp
   {
   public:
      
      dib_sp();
      dib_sp(::ca::allocer allocer);
      virtual ~dib_sp();


      


      virtual bool load_from_file(var varFile);
      virtual bool load_from_matter(const char * pszMatter);
      virtual bool read_from_file(sp(::ca::file) pfile);
      

      virtual bool save_to_file(var varFile, save_image * psaveimage = ::null());
      virtual bool write_to_file(sp(::ca::file) pfile, save_image * psaveimage = ::null());


   };

} // namespace visual
