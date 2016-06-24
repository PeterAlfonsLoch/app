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

   class CLASS_DECL_AXIS save_image
   {
   public:


      image::e_format         m_eformat;
      int                     m_iQuality;

      save_image();

   };


   class CLASS_DECL_AXIS dib_sp :
      public ::draw2d::dib_sp
   {
   public:




      class pointer :
         virtual public ::object
      {
      public:

         enum e_disposal
         {
            disposal_undefined = 0,
            disposal_none = 1,
            disposal_background = 2,
            disposal_previous = 3
         };

         rect                 m_rect;
         ::draw2d::dib_sp     m_dib;
         DWORD                m_dwTime;
         e_disposal           m_edisposal;
         COLORREF             m_crTransparent;
         bool                 m_bTransparent;
         bool                 m_bLocalPalette;

         pointer();
         virtual ~pointer();


         virtual bool to(::draw2d::graphics * pgraphics);

      };


      class array :
         virtual public spa(pointer)
      {
      public:


         DWORD                m_dwStart;
         DWORD                m_dwTotal;
         unsigned int         m_uiLoopCount; // 0 - infinite loop
         unsigned int         m_uiLoop;
         int                  m_iTransparentIndex;
         bool                 m_bTransparent;
         COLORREF             m_crTransparent;
         COLORREF             m_crBack;
         BYTE                 m_backgroundIndex;
         ::size               m_sizeLogical;
         ::size               m_size;
         index                m_iLastFrame;
         bool                 m_bStart;
         ::draw2d::dib_sp     m_dibCompose;
         ::array <COLORREF>   m_cra;


         array();
         virtual ~array();


      };

      sp(array)          m_sparray;


      dib_sp();
      dib_sp(const ::aura::allocatorsp & allocer);
      virtual ~dib_sp();

      virtual bool dispose_current_frame();
      virtual bool overlay_frame(int iFrame);
      virtual void defer_update();



      virtual bool load_from_file(var varFile, bool bCache = true);
      virtual bool load_from_matter(const char * pszMatter,bool bCache = true);
      virtual bool read_from_file(::file::buffer_sp  pfile);


      virtual bool save_to_file(var varFile, save_image * psaveimage = NULL);
      virtual bool write_to_file(::file::buffer_sp  pfile, save_image * psaveimage = NULL);

#ifndef  WINDOWS
      virtual bool from(::draw2d::graphics * pgraphics, FIBITMAP * pfibitmap, bool bUnloadFI);
#endif

   };


} // namespace visual


CLASS_DECL_AXIS void draw_freetype_bitmap(::draw2d::dib * m_p,int32_t dx,int32_t dy,void * pftbitmap,int x,int y);
CLASS_DECL_AXIS void draw_freetype_bitmap(::draw2d::dib * m_p,int32_t dx,int32_t dy,void * pftbitmap,int x,int y,byte a,byte r,byte g,byte b);












