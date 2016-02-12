#pragma once


namespace html
{


   namespace impl
   {


      class CLASS_DECL_HTML input_text : public elemental,
         virtual public ::calculator::plain_edit_view::callback
      {
      public:
         
         
         int32_t m_iFont;
         string m_strUnit;
         string m_strType;
         sp(::user::plain_edit) m_pedit;


         input_text(data * pdoc,const string & strType = "",const string & strUnit = "");
         virtual ~input_text();


         void _001OnDraw(data * pdoc);


         virtual void implement_phase1(data * pdoc, ::html::elemental * pelemental);
         virtual void layout_phase1(data * pdoc);
         virtual void layout_phase3(data * pdoc);
         void on_change_layout(data * pdoc);

      };


   } // namespace impl


} // namespace html





