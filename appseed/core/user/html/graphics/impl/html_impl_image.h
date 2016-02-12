#pragma once


namespace html
{


   namespace impl
   {


      class image : public elemental
      {
      public:
      
         
         int32_t        m_iImage;
         rect           m_rect;


         void _001OnDraw(data * pdoc);
         void implement_phase1(data * pdoc, ::html::elemental * pelemental);
         void layout_phase1(data * pdoc);
         void layout_phase3(data * pdoc);

      };


   } // namespace impl


} // namespace html




