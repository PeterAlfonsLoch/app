#pragma once


namespace simple_ui
{



   class CLASS_DECL_AXIS password :
      virtual public edit_box
   {
   public:


      password(sp(::aura::application) papp);
      virtual ~password();


      virtual void _001OnDraw(::draw2d::graphics * pgraphics);


   };






} // namespace simple_ui





