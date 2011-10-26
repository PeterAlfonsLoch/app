#pragma once


namespace visual
{

   class CLASS_DECL_ca graphics_extension :
      virtual public ::radix::object
   {
   public:
      
      graphics_extension(::ca::application * papp);
      virtual ~graphics_extension();
      void GetTextExtent(::ca::graphics * pdc, const char * lpcwsz, base_array < size > & sizea);
      void GetTextExtent(::ca::graphics * pdc, const char * lpcwsz, size & size);
      void GetTextExtent(::ca::graphics * pdc, const char * lpcwsz, int iCount, size & size);

      BOOL TextOut(::ca::graphics * pdc, int x, int y, const char * lpcwsz, int iCount);
      int _DrawText(::ca::graphics * pdc, const char * lpcsz, LPCRECT lpcrect, UINT uiFormat, ::ca::font * pfontUnderline = NULL);
      
      int _EncodeV033(string & str);


      void FillSolidRect(HDC hdc, const __rect64 * lpRect, COLORREF clr);
      void FillSolidRect(HDC hdc, LPCRECT lpRect, COLORREF clr);
      void FillSolidRect(HDC hdc, int x, int y, int cx, int cy, COLORREF clr);

      //static int _FindPrefixV1(const wchar_t * lpcsz);

   };

} // namespace visual

