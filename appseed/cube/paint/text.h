#pragma once

namespace paint
{

   namespace impl
   {
      class text : public elemental
      {
      public:
         int m_iFont;
         text();
         void _001OnDraw(document * pdoc);
         void implement(document * pdoc, ::paint::elemental * pelemental);
      };

   } // namespace visual

} // namespace html_impl

