#pragma once


namespace simple_ui
{



   class CLASS_DECL_BASE password :
      virtual public edit_box
   {
   public:


      password(sp(::axis::application) papp);
      virtual ~password();


      virtual void _001OnDraw(::draw2d::graphics * pgraphics);


   };






} // namespace simple_ui





