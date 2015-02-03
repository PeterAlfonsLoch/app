#pragma once


namespace html
{


   class CLASS_DECL_HTML border :
      public box
   {
   public:

      enum e_style
      {

         style_solid,

      };


      COLORREF    crLeft;
      COLORREF    crTop;
      COLORREF    crRight;
      COLORREF    crBottom;
      
      e_style     styleLeft;
      e_style     styleTop;
      e_style     styleRight;
      e_style     styleBottom;

      
   };


} // namespace html




