#pragma once


namespace visual
{


   class CLASS_DECL_CORE graphics_extension :
      virtual public ::object
   {
   public:
      
      
      graphics_extension(sp(::base::application) papp);
      virtual ~graphics_extension();
      void GetTextExtent(::draw2d::graphics * pdc, const char * lpcwsz, array < size > & sizea);
      void GetTextExtent(::draw2d::graphics * pdc, const char * lpcwsz, size & size);
      void GetTextExtent(::draw2d::graphics * pdc, const char * lpcwsz, strsize iCount, size & size);

      bool TextOut(::draw2d::graphics * pdc, int32_t x, int32_t y, const char * lpcwsz, strsize iCount);
      
      void FillSolidRect(HDC hdc, const __rect64 * lpRect, COLORREF clr);
      void FillSolidRect(HDC hdc, LPCRECT lpRect, COLORREF clr);
      void FillSolidRect(HDC hdc, int32_t x, int32_t y, int32_t cx, int32_t cy, COLORREF clr);

      //static int32_t _FindPrefixV1(const wchar_t * lpcsz);

   };


} // namespace visual



