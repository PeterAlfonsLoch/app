#pragma once

class image_list;

class CLASS_DECL_ca2 simple_static : 
   public ::user::static_control
{
public:
   bool                 m_bTransparent;
   ::ca2::brush_sp       m_brushBkg;
   sp(image_list)         m_pimagelist;

   simple_static(sp(::ca2::application) papp);

   virtual void pre_subclass_window();
   
   virtual void _001OnDraw(::ca2::graphics * pdc);
   virtual ~simple_static();

   LRESULT OnSetIcon(WPARAM wparam, LPARAM lparam);
};

