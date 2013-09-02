#pragma once

class CLASS_DECL_ca2 simple_status_bar :
   public ::user::status_bar
{
public:
   simple_status_bar(sp(::application) papp);

   virtual void _001OnDraw(::draw2d::graphics * pdc);
   virtual ~simple_status_bar();

};
