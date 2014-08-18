#pragma once


namespace simple_ui
{


   class CLASS_DECL_BASE label :
      virtual public interaction
   {
   public:


      label(sp(::base::application) papp);
      virtual ~label();


      virtual void _001OnDraw(::draw2d::graphics * pgraphics);



   };


} // namespace simple_ui




