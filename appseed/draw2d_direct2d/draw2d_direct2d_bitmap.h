#pragma once


namespace draw2d_direct2d
{


   class CLASS_DECL_DRAW2D_DIRECT2D bitmap : 
      virtual public ::draw2d_direct2d::object,
      virtual public ::draw2d::bitmap
      
   {
   public:

      Microsoft::WRL::ComPtr<ID2D1Bitmap>    m_pbitmap;
      Microsoft::WRL::ComPtr<ID2D1Bitmap1>   m_pbitmap1;
      D2D1_MAPPED_RECT        m_map;
      primitive::memory       m_memory;
      //      ::Gdiplus::Bitmap *  m_pbitmap;
      //    void *               m_pdata;


      enum e_data
      {
         data_bitmap,
         data_bitmap1,
      };

      bitmap(sp(::axis::application) papp);
      virtual ~bitmap();

      virtual void * get_os_data() const;
      virtual void * get_os_data_ex(int i) const;



      bool LoadBitmap(const char * lpszResourceName);
      bool LoadBitmap(UINT nIDResource);
      bool LoadOEMBitmap(UINT nIDBitmap); // for OBM_/OCR_/OIC_

#ifndef ___NO_AFXCMN_SUPPORT
      //      bool LoadMappedBitmap(UINT nIDBitmap, UINT nFlags = 0,
      //       LPCOLORMAP lpColorMap = NULL, int nMapSize = 0);
#endif

      virtual bool CreateBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight, UINT nPlanes, UINT nBitcount, const void * lpBits, int stride);
      virtual bool CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP lpBitmap);
      virtual bool CreateCompatibleBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight);
      virtual bool CreateDiscardableBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight);
      virtual bool CreateDIBSection(::draw2d::graphics * pgraphics, const BITMAPINFO * lpbmi, UINT usage, void **ppvBits, int * stride, HANDLE hSection, uint32_t offset);
      virtual bool CreateDIBitmap(::draw2d::graphics * pgraphics, const BITMAPINFOHEADER *pbmih, uint32_t flInit, const void *pjBits, const BITMAPINFO *pbmi, UINT iUsage);

      virtual bool attach(void * posdata);
      virtual void * detach();

      uint32_t SetBitmapBits(uint32_t dwCount, const void * lpBits);
      uint32_t GetBitmapBits(uint32_t dwCount, LPVOID lpBits) const;
      class size SetBitmapDimension(int nWidth, int nHeight);
      class size GetBitmapDimension() const;

      virtual void dump(dump_context & dumpcontext) const;


//      virtual bool Attach(HBITMAP hbitmap);


      virtual bool destroy();

#ifdef WINDOWSEX

      virtual HBITMAP _GetHBITMAP();
      virtual void _ReleaseHBITMAP(HBITMAP hbitmap);

#endif


   };


} // namespace draw2d_direct2d

