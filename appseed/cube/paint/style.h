#pragma once


namespace paint
{
   class style
   {
   public:
      gen::property_set  m_propertyset;
      void parse(const char * psz);

      COLORREF parse_color(const char * psz);
      bool get_background_color(COLORREF & cr);
   };

} // namespace paint