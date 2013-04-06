#pragma once


class CLASS_DECL_ca2 html_child_frame : public simple_child_frame
{
   // // DECLARE_DYNCREATE(html_child_frame)
public:
   html_child_frame(sp(::ca::application) papp);
   virtual ~html_child_frame();

   simple_toolbar        m_toolbar;


   sp(html_document) get_document();
   html_view * get_view();

};