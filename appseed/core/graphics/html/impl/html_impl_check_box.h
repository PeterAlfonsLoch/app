#pragma once


namespace html
{


   namespace impl
   {


      class CLASS_DECL_CORE input_check_box : public elemental
      {
      public:


         sp(::user::check_box) m_pcheckbox;


         input_check_box(data * pdoc);
         virtual ~input_check_box();
         void _001OnDraw(data * pdoc);
         virtual void implement_phase1(data * pdoc, ::html::elemental * pelemental);
         virtual void layout_phase1(data * pdoc);
         virtual void layout_phase3(data * pdoc);
         void on_change_layout(data * pdoc);


      };


   } // namespace impl


} // namespace html



