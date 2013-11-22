#pragma once


namespace simple_ui
{



   class CLASS_DECL_BASE password :
      virtual public interaction
   {
   public:


      password();
      virtual ~password();


      virtual void _001OnDraw(::draw2d::graphics * pgraphics);


   };






} // namespace simple_ui





