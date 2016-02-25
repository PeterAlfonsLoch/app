#pragma once


namespace simple_ui
{


   class CLASS_DECL_BASE label :
      virtual public interaction
   {
   public:


      label(::aura::application * papp);
      virtual ~label();


      virtual void _001OnDraw(::draw2d::dib * pdib);



   };


} // namespace simple_ui




