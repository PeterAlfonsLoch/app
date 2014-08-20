#pragma once


class CLASS_DECL_CORE simple_combo_list : 
   virtual public ::user::combo_list
{
public:


   simple_combo_list(sp(::axis::application) papp);
   virtual ~simple_combo_list();


   virtual void install_message_handling(::message::dispatch * pdispatch);


   virtual void _001OnDraw(::draw2d::graphics * pdc);



};



