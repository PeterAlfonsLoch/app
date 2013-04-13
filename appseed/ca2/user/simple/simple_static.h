#pragma once

class image_list;

class CLASS_DECL_ca2 simple_static : 
   public ::user::base_static
{
public:
   bool                 m_bTransparent;
   ::ca::brush_sp       m_brushBkg;
   sp(image_list)         m_pimagelist;

   simple_static(sp(::ca::application) papp);

   virtual void pre_subclass_window();
   
   virtual void _001OnDraw(::ca::graphics * pdc);
   virtual ~simple_static();

   LRESULT OnSetIcon(WPARAM wparam, LPARAM lparam);
};

