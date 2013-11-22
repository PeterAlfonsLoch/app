#pragma once


namespace simple_ui
{



   class CLASS_DECL_BASE password :
      virtual public edit_box
   {
   public:


      password(sp(base_application) papp);
      virtual ~password();


      virtual void draw_this(::draw2d::graphics * pgraphics);


   };






} // namespace simple_ui





