//#include "framework.h"
//#include "draw2d_object.h"
//#include "draw2d_bitmap.h"


namespace draw2d
{


   bitmap::bitmap()
   {

#ifdef WINDOWSEX

      m_hbitmapGet            = NULL;

#endif

      m_iStride               = 0;

   }


   bitmap::~bitmap()
   {

#ifdef WINDOWSEX

      // Implementators (derived classes) should have released or at last nulled m_hbitmapGet to
      // indicate it is correctly Released through ReleaseHBITMAP

      if(m_hbitmapGet != NULL)
      {

         ReleaseHBITMAP(m_hbitmapGet);

      }

#endif

   }


   bool bitmap::CreateBitmap(::draw2d::graphics * pdc,int32_t nWidth,int32_t nHeight,UINT nPlanes,UINT nBitcount,const void * lpBits,int32_t stride)
   {
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      UNREFERENCED_PARAMETER(nPlanes);
      UNREFERENCED_PARAMETER(nBitcount);
      UNREFERENCED_PARAMETER(lpBits);
      UNREFERENCED_PARAMETER(stride);
      ::exception::throw_not_implemented(get_app());
      return false;
   }

   bool bitmap::CreateBitmapIndirect(::draw2d::graphics * pdc,LPBITMAP lpBitmap)
   {
      UNREFERENCED_PARAMETER(lpBitmap);
      ::exception::throw_not_implemented(get_app());
      return false;
   }

   bool bitmap::CreateDIBSection(::draw2d::graphics * pdc,const BITMAPINFO * lpbmi,UINT usage,void **ppvBits,int * stride,HANDLE hSection,uint32_t offset)
   {
      UNREFERENCED_PARAMETER(pdc);
      UNREFERENCED_PARAMETER(lpbmi);
      UNREFERENCED_PARAMETER(usage);
      UNREFERENCED_PARAMETER(ppvBits);
      UNREFERENCED_PARAMETER(stride);
      UNREFERENCED_PARAMETER(hSection);
      UNREFERENCED_PARAMETER(offset);
      ::exception::throw_not_implemented(get_app());
      return false;
   }
   bool bitmap::CreateDIBitmap(::draw2d::graphics * pdc,const BITMAPINFOHEADER *pbmih,uint32_t flInit,const void *pjBits,const BITMAPINFO *pbmi,UINT iUsage)
   {
      UNREFERENCED_PARAMETER(pdc);
      UNREFERENCED_PARAMETER(pbmih);
      UNREFERENCED_PARAMETER(flInit);
      UNREFERENCED_PARAMETER(pjBits);
      UNREFERENCED_PARAMETER(pbmi);
      UNREFERENCED_PARAMETER(iUsage);
      ::exception::throw_not_implemented(get_app());
      return false;
   }

   uint32_t bitmap::SetBitmapBits(uint32_t dwCount,const void * lpBits)
   {
      UNREFERENCED_PARAMETER(dwCount);
      UNREFERENCED_PARAMETER(lpBits);
      ::exception::throw_not_implemented(get_app());
      return 0;
   }
   uint32_t bitmap::GetBitmapBits(uint32_t dwCount,LPVOID lpBits) const
   {
      UNREFERENCED_PARAMETER(dwCount);
      UNREFERENCED_PARAMETER(lpBits);
      ::exception::throw_not_implemented(get_app());
      return 0;
   }

   bool bitmap::CreateCompatibleBitmap(::draw2d::graphics * pgraphics,int32_t nWidth,int32_t nHeight)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      ::exception::throw_not_implemented(get_app());
      return false;
   }
   bool bitmap::CreateDiscardableBitmap(::draw2d::graphics * pgraphics,int32_t nWidth,int32_t nHeight)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      ::exception::throw_not_implemented(get_app());
      return false;
   }

   void ::draw2d::bitmap::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      ::exception::throw_interface_only(get_app());
   }


   class size bitmap::SetBitmapDimension(int32_t nWidth,int32_t nHeight)
   {
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      ::exception::throw_not_implemented(get_app());
      return ::size(0,0);
   }


   bool bitmap::attach(void * posdata)
   {
      UNREFERENCED_PARAMETER(posdata);
      ::exception::throw_interface_only(get_app());
      return false;
   }

   void * bitmap::detach()
   {
      ::exception::throw_interface_only(get_app());
      return NULL;
   }

   class size bitmap::set_size(class size size)
   {


      return SetBitmapDimension(size.cx,size.cy);


   }

   class size bitmap::GetBitmapDimension() const
   {


      ::exception::throw_not_implemented(get_app());
      class size sizeRet(0,0);
      return sizeRet;


   }

   class size bitmap::get_size() const
   {


      return GetBitmapDimension();


   }

   class size bitmap::size() const
   {


      return GetBitmapDimension();


   }


   void copy_colorref(int cxParam,int cyParam,COLORREF * pcolorrefDst,int iStrideDst,COLORREF * pcolorrefSrc,int iStrideSrc)
   {

      if(iStrideSrc <= 0)
      {

         iStrideSrc = cxParam * sizeof(COLORREF);

      }

      if(iStrideDst == iStrideSrc)
      {

         memcpy(pcolorrefDst,pcolorrefSrc,cyParam * iStrideDst);

      }
      else
      {

         int wsrc = iStrideSrc / sizeof(COLORREF);
         int wdst = iStrideDst / sizeof(COLORREF);
         int cw = cxParam * sizeof(COLORREF);


         COLORREF * psrc = pcolorrefSrc;
         COLORREF * pdst = pcolorrefDst;

         for(int i = 0; i < cyParam; i++)
         {

            memcpy(pdst,psrc,cw);

            pdst += wdst;

            psrc += wsrc;

         }

      }

   }

   void copy_colorref(int xParam, int yParam, int cxParam,int cyParam,COLORREF * pcolorrefDst,int iStrideDst,COLORREF * pcolorrefSrc,int iStrideSrc)
   {

      if(iStrideSrc <= 0)
      {

         iStrideSrc = cxParam * sizeof(COLORREF);

      }

      int wsrc = iStrideSrc / sizeof(COLORREF);
      int wdst = iStrideDst / sizeof(COLORREF);
      int cw = cxParam * sizeof(COLORREF);


      COLORREF * psrc = &pcolorrefSrc[xParam + yParam * iStrideSrc / sizeof(COLORREF)];
      COLORREF * pdst = &pcolorrefDst[xParam + yParam * iStrideDst / sizeof(COLORREF)];

      for(int i = 0; i < cyParam; i++)
      {

         memcpy(pdst,psrc,cw);

         pdst += wdst;

         psrc += wsrc;

      }


   }

} // namespace draw2d




