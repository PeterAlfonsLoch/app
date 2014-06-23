#pragma once


namespace draw2d_direct2d
{


   class CLASS_DECL_DRAW2D_DIRECT2D font : 
      virtual public ::draw2d_direct2d::object,
      virtual public ::draw2d::font
   {
   public:

      
      Microsoft::WRL::ComPtr<IDWriteTextFormat>                  m_pformat;


      font(::base::application * papp);
      virtual ~font();


      virtual IDWriteTextFormat * get_os_font(::draw2d_direct2d::graphics * pgraphics) const;


/*      virtual void construct(const ::draw2d::font & fontParam);

      virtual bool CreateFontIndirect(const LOGFONTW* lpLogFont);
      virtual bool CreateFont(int nHeight, int nWidth, int nEscapement,
            int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline,
            BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision,
            BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily,
            const char * lpszFacename);
      virtual bool CreatePointFont(int nPointSize, const char * lpszFaceName, ::draw2d::graphics * pgraphics = NULL);
      virtual bool CreatePointFontIndirect(const LOGFONTW* lpLogFont, ::draw2d::graphics * pgraphics = NULL);

      virtual int GetLogFont(LOGFONTW* pLogFont);*/

      virtual void dump(dump_context & dumpcontext) const;

      virtual bool destroy();


   };


} // namespace draw2d_direct2d




