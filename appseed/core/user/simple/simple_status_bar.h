#pragma once

class CLASS_DECL_CORE simple_status_bar :
   public ::user::status_bar
{
public:
   simple_status_bar(::aura::application * papp);

   virtual void _001OnDraw(::draw2d::graphics * pgraphics);
   virtual ~simple_status_bar();

};
