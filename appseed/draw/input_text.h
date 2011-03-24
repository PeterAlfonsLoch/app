#pragma once


namespace html
{

namespace impl
{

   class input_text : public elemental
   {
   public:
      int m_iFont;
      Ex1EditPlainTextInterface * m_pedit;
      input_text();
      virtual ~input_text();
      void _001OnDraw(document * pdoc);
      void implement(document * pdoc, ::html::elemental * pelemental);
      void on_change_layout(document * pdoc);
   };

} // namespace visual

} // namespace html