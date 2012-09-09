#pragma once

class CLASS_DECL_ca image_list :
   virtual public ::radix::object
{
protected:
   size           m_size;
   int            m_iSize;
   int            m_iGrow;
public:
   ::ca::dib_sp   m_spdib;


   ::ca::dib_sp   m_spdibWork;
   ::ca::dib_sp   m_spdibWork2;
   ::ca::dib_sp   m_spdibWork3;


protected:
   bool _grow();
   int _get_alloc_count();
public:


   using ::ex1::request_interface::create;
   bool create(int cx, int cy, UINT nFlags, int nInitial, int nGrow);
    //bool create(const char * lpszBitmapID, int cx, int nGrow, COLORREF crMask);

   int add(::visual::icon * picon);
   int add_icon(const char * lpcsz);
   int add_icon_os_data(void * pvoid);
   int add_matter_icon(const char * lpcszMatter);
   int add_file(const char * lpcsz);
   int add_matter(const char * lpcsz, ::ca::application * papp = NULL);
   int add_std_matter(const char * lpcsz);

   bool draw(::ca::graphics * pdc, int iImage, point pt, int iFlag);
   bool draw(::ca::graphics * pdc, int iImage, point pt, size sz, point ptOffset, int iFlag);
   int get_image_count() const;
   bool create(image_list * pimagelist);
   image_list(::ca::application * papp);
   virtual ~image_list();

#ifdef WINDOWS
   bool get_image_info(int nImage, IMAGEINFO* pImageInfo) const;
#endif

   void remove_all();

};
