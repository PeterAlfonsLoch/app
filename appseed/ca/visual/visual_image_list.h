#pragma once

class CLASS_DECL_ca image_list :
   virtual public ::radix::object
{
public:

   class CLASS_DECL_ca info
   {
   public:


      rect           m_rect;
      ::ca::dib *    m_pdib;

   };


protected:
   size           m_size;
   int32_t            m_iSize;
   int32_t            m_iGrow;
public:
   ::ca::dib_sp   m_spdib;


   ::ca::dib_sp   m_spdibWork;
   ::ca::dib_sp   m_spdibWork2;
   ::ca::dib_sp   m_spdibWork3;


protected:
   bool _grow();
   int32_t _get_alloc_count();
public:


   using ::ex1::request_interface::create;
   bool create(int32_t cx, int32_t cy, UINT nFlags, int32_t nInitial, int32_t nGrow);
   bool realize(::ca::graphics * pdc);
    //bool create(const char * lpszBitmapID, int32_t cx, int32_t nGrow, COLORREF crMask);

   int32_t add(::visual::icon * picon);
   int32_t add_icon(const char * lpcsz);
   int32_t add_icon_os_data(void * pvoid);
   int32_t add_matter_icon(const char * lpcszMatter);
   int32_t add_file(const char * lpcsz);
   int32_t add_matter(const char * lpcsz, ::ca::application * papp = NULL);
   int32_t add_std_matter(const char * lpcsz);

   bool draw(::ca::graphics * pdc, int32_t iImage, point pt, int32_t iFlag);
   bool draw(::ca::graphics * pdc, int32_t iImage, point pt, size sz, point ptOffset, int32_t iFlag);
   int32_t get_image_count() const;
   bool create(image_list * pimagelist);
   image_list(::ca::application * papp);
   virtual ~image_list();

   bool get_image_info(int32_t nImage, info * pinfo) const;

   void remove_all();

};
