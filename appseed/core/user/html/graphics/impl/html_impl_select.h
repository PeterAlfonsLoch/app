#pragma once


namespace html
{


   namespace impl
   {


      class CLASS_DECL_CORE select : public elemental
      {
      public:


         int32_t                    m_iFont;
         sp(::user::combo_box)     m_pcombo;


         select(data * pdoc);
         virtual ~select();
         
         
         void _001OnDraw(data * pdoc);
         virtual void implement_phase1(data * pdoc, ::html::elemental * pelemental);
         
         
         virtual void layout_phase1(data * pdoc);
         virtual void layout_phase3(data * pdoc);

         
         virtual void layout_phase1_end(data * pdata);


         void on_change_layout(data * pdoc);

         void set_pos(data * pdoc,float x,float y,float cx,float cy);

      };


   } // namespace impl


} // namespace html



