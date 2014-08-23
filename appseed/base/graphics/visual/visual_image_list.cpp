#include "framework.h"

#ifndef METROWIN
#include "freeimage/Source/freeimage.h"
#endif

image_list::image_list(sp(::aura::application) papp) :
   element(papp),
   m_spdib(allocer()),
   m_spdibWork(allocer()),
   m_spdibWork2(allocer()),
   m_spdibWork3(allocer())
{

   m_iSize = 0;
   m_iGrow = 1;
   m_size.cx = 0;
   m_size.cy = 0;

}


image_list::~image_list()
{

}


bool image_list::create(int32_t cx, int32_t cy)
{

   return create(cx, cy, 0, 0, 0);

}

bool image_list::create(int32_t cx, int32_t cy, UINT nFlags, int32_t nInitial, int32_t nGrow)
{

   UNREFERENCED_PARAMETER(nFlags);

   if(cx <= 0)
      return false;

   if(cy <= 0)
      return false;

   if(nInitial < 0)
      return false;

   if(nGrow < 1)
      nGrow = 1;

   m_iSize = 0;
   m_iGrow = nGrow;

   m_size.cx = cx;
   m_size.cy = cy;

   m_spdib->create(m_size.cx * m_iSize, m_size.cy);

   return true;

}


bool image_list::realize(::draw2d::graphics * pdc)
{

   return m_spdib->realize(pdc);

}


bool image_list::create(sp(image_list) pimagelist)
{
   m_spdib->Paste(pimagelist->m_spdib);
   m_size   = pimagelist->m_size;

   m_iSize  = pimagelist->m_iSize;
   m_iGrow  = pimagelist->m_iGrow;
   m_size   = pimagelist->m_size;

   return true;
}

/*bool image_list::create(const char * lpszBitmapID, int32_t cx, int32_t nGrow, COLORREF crMask)
{
   ::draw2d::bitmap bitmap;
   if(!bitmap.LoadBitmap(lpszBitmapID))
      return false;

   BITMAP bm;
   if(!bitmap.GetBitmap(&bm))
      return false;

   m_spdib->create(bm.bmWidth, bm.bmHeight);

   ::draw2d::graphics_sp spgraphics(allocer());
   spgraphics->CreateCompatibleDC(NULL);
   spgraphics->SelectObject(bitmap);
   m_spdib->from(spgraphics);
   m_spdib->channel_mask(192, 255, 0, visual::rgba::channel_alpha);

   m_size.cx = cx;
   m_size.cy = bm.bmHeight;

   return true;
}
*/

int32_t image_list::get_image_count() const
{

   return m_iSize;

}

bool image_list::draw(::draw2d::graphics *pdc, int32_t iImage, point pt, int32_t iFlag)
{

   UNREFERENCED_PARAMETER(iFlag);

   return pdc->BitBlt(pt.x, pt.y, m_size.cx, m_size.cy, m_spdib->get_graphics(), iImage * m_size.cx, 0, SRCCOPY);

}


bool image_list::draw(::draw2d::graphics *pdc, int32_t iImage, point pt, int32_t iFlag, BYTE alpha)
{

   UNREFERENCED_PARAMETER(iFlag);

   if(alpha == 255)
      return draw(pdc, iImage, pt, iFlag);

   return System.visual().imaging().color_blend(pdc, pt, m_size, m_spdib->get_graphics(), point(iImage * m_size.cx, 0), alpha / 255.0);

}

bool image_list::draw(::draw2d::graphics * pdc, int32_t iImage, point pt, size sz, point ptOffset, int32_t iFlag)
{

   UNREFERENCED_PARAMETER(iFlag);

   sz.cx = MIN(m_size.cx, sz.cx);
   sz.cy = MIN(m_size.cy, sz.cy);
   ptOffset.x = MIN(m_size.cx, ptOffset.x);
   ptOffset.y = MIN(m_size.cy, ptOffset.y);

   return pdc->BitBlt(pt.x, pt.y, sz.cx, sz.cy, m_spdib->get_graphics(), iImage * m_size.cx + ptOffset.x, ptOffset.y, SRCCOPY);

}

int32_t image_list::add_icon_os_data(void * pvoid)
{
   ::visual::icon icon(pvoid);
   return add(&icon);
}

int32_t image_list::add(::visual::icon * picon)
{
   int32_t iItem = m_iSize;
   if(iItem >= _get_alloc_count())
   {
      _grow();
   }

   ::draw2d::brush_sp brush(allocer(), RGB(192, 192, 192));
   m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
   m_spdib->get_graphics()->FillSolidRect(iItem * m_size.cx, 0, m_size.cx, m_size.cy, 0);
   //COLORREF crMask = m_spdib->get_graphics()->GetPixel(iItem * m_size.cx, 0);


#ifdef METROWIN
   m_spdib->get_graphics()->DrawIcon(iItem * m_size.cx, 0, picon, m_size.cx, m_size.cy, 0, NULL, 0);
#else
   m_spdib->get_graphics()->DrawIcon(iItem * m_size.cx, 0, picon, m_size.cx, m_size.cy, 0, NULL, DI_IMAGE);
#endif

   //::draw2d::dib_sp dibAlpha(get_app());
   //dibAlpha->create(m_size.cx, m_size.cy);

   //dibAlpha->Fill(255, 255, 255);
   //dibAlpha->SetIconMask(picon, m_size.cx, m_size.cy);

 //  ::draw2d::graphics_sp dcAlpha;
//   dcAlpha.CreateCompatibleDC(NULL);
//   dcAlpha.SelectObject(dibAlpha->m_hbitmap);

/*  m_dcAlpha.BitBlt(
      iItem * m_size.cx, 0,
      m_size.cx, m_size.cy,
      &dcAlpha,
      0, 0,
      SRCCOPY);*/


   /*::draw2d::dib_sp dibIcon;
   dibIcon.create(m_size.cx, m_size.cy);
   ::draw2d::graphics_sp dcIcon;
   dcIcon.CreateCompatibleDC(NULL);
   dcIcon.SelectObject(dibIcon.m_hbitmap);

   DrawIconEx(dcIcon, 0, 0, hicon, m_size.cx, m_size.cy,
      0, NULL, DI_MASK);

   GdiFlush();

   dibIcon.Invert();

   m_dcAlpha.BitBlt(
      iItem * m_size.cx, 0,
      m_size.cx, m_size.cy,
      &dcIcon,
      0, 0,
      SRCCOPY);*/
   
   m_iSize++;

   return iItem;

}


int32_t image_list::add_icon(const char * psz)
{

   ::visual::icon icon;

#ifdef WINDOWSEX

   int32_t iSize = MIN(m_size.cx, m_size.cy);
   
   icon.m_picon = (void *) (HICON) ::LoadImage(NULL, psz, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);

#endif

   return add(&icon);

}


int32_t image_list::add_matter_icon(const char * pszMatter)
{

   return add_icon(Application.dir().matter(pszMatter));

}


int32_t image_list::add_file(const char * lpcsz)
{

   ::visual::dib_sp dib(allocer());

   if(!dib.load_from_file(lpcsz))
      return -1;

   int32_t iItem = m_iSize;
   if(iItem >= _get_alloc_count())
   {
      _grow();
   }

   //m_spdib->get_graphics()->FillSolidRect(iItem * m_size.cx, 0, m_size.cx, m_size.cy, RGB(192, 192, 192));

   m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

   m_spdib->get_graphics()->BitBlt(iItem * m_size.cx, 0, m_size.cx, m_size.cy, dib->get_graphics(), 0, 0, SRCCOPY);

   m_iSize++;
   return iItem;
}

int32_t image_list::add_matter(const char * lpcsz, sp(::aura::application) papp)
{
   if(papp == NULL)
   {
      return add_file(Application.dir().matter(lpcsz));
   }
   else
   {
      return add_file(Sess(papp).dir().matter(lpcsz));
   }
}

int32_t image_list::add_std_matter(const char * lpcsz)
{
   return add_file(Application.dir().matter(lpcsz));
}

int32_t image_list::_get_alloc_count()
{
   if(m_size.cx == 0)
      return 0;
   else
      return m_spdib->m_size.cx / m_size.cx;
}

bool image_list::_grow()
{
   int32_t cx = m_size.cx;
   int32_t cy = m_size.cy;

   int32_t iAllocSize = _get_alloc_count() + m_iGrow;

   if(_get_alloc_count() == 0)
   {
      m_spdib->create(cx * iAllocSize, cy);
   }
   else
   {
      ::draw2d::dib_sp spdib(allocer());
      //::draw2d::dib_sp dibAlpha(allocer());

      spdib->Paste(m_spdib);

      m_spdib->create(cx * iAllocSize, cy);

      m_spdib->from(point(0, 0), spdib, point(0, 0), spdib->size());

      //m_spdib->defer_realize(spdib->get_graphics());

      //m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

      //m_spdib->get_graphics()->BitBlt(0, 0, spdib->cx, spdib->cy, spdib->get_graphics(), 0, 0, SRCCOPY);

   }

   return true;
}

bool image_list::get_image_info(int32_t nImage, info * pinfo) const
{

   try
   {

      ASSERT(pinfo != NULL);

      if(nImage < 0 || nImage >= get_image_count())
         return FALSE;


      if(m_spdib.is_null())
         return FALSE;

      if(const_cast < ::draw2d::dib_sp & > (m_spdib)->get_bitmap().is_null())
         return FALSE;

      if((HBITMAP) const_cast < ::draw2d::dib_sp & > (m_spdib)->get_bitmap()->get_os_data() == NULL)
         return FALSE;

      pinfo->m_rect.left      = nImage * m_size.cx;
      pinfo->m_rect.right     = pinfo->m_rect.left + m_size.cx;
      pinfo->m_rect.top       = 0;
      pinfo->m_rect.bottom    = m_size.cy;
      pinfo->m_pdib           = ((image_list *) this)->m_spdib;
//      pImageInfo->hbmMask           = NULL;

      return TRUE;

   }
   catch(...)
   {
      return FALSE;
   }

}

void image_list::remove_all()
{
   m_iSize = 0;
}
