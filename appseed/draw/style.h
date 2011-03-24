#pragma once


namespace html
{
   class style
   {
   public:
      gen::PropertySet  m_propertyset;
      void parse(const char * psz);

      COLORREF parse_color(const char * psz);
      bool get_background_color(COLORREF & cr);
   };

} // namespace html