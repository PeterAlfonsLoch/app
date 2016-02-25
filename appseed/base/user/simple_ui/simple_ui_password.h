#pragma once


namespace simple_ui
{



   class CLASS_DECL_BASE password :
      virtual public edit_box
   {
   public:


      password(::aura::application * papp);
      virtual ~password();


      virtual void _001OnDraw(::draw2d::dib * pdib);


   };






} // namespace simple_ui





