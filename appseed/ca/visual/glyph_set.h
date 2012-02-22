#pragma once


namespace visual
{


   class glyph_set : 
      public base_array<glyph , glyph &>
   {
   public:


      
      glyph_set();
      virtual ~glyph_set();


      virtual index add(glyph & glyph);

      void QuickSort();
      
      index find_first(UINT user);
      
      glyph * GetGlyph(UINT user);


   };


} // namespace visual


