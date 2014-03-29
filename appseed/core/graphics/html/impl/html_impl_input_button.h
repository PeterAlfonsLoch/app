#pragma once


namespace html
{


   namespace impl
   {


      class CLASS_DECL_CORE input_button : public elemental
      {
      public:

         int32_t m_iFont;
         ::user::button * m_pbutton;
         input_button(data * pdoc);
         virtual ~input_button();
         void _001OnDraw(data * pdoc);
         virtual void implement_phase1(data * pdoc, ::html::elemental * pelemental);
         virtual void layout_phase1(data * pdoc);
         virtual void layout_phase3(data * pdoc);
         void on_change_layout(data * pdoc);
      };


   } // namespace impl


} // namespace html




