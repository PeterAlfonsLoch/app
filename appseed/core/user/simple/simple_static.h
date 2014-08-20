#pragma once

class image_list;

class CLASS_DECL_CORE simple_static : 
   public ::user::static_control
{
public:
   bool                 m_bTransparent;
   ::draw2d::brush_sp       m_brushBkg;
   sp(image_list)         m_pimagelist;

   simple_static(sp(::axis::application) papp);

   virtual void pre_subclass_window();
   
   virtual void _001OnDraw(::draw2d::graphics * pdc);
   virtual ~simple_static();

   LRESULT OnSetIcon(WPARAM wparam, LPARAM lparam);
};

