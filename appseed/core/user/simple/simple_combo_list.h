#pragma once


class CLASS_DECL_ca2 simple_combo_list : 
   virtual public ::user::combo_list
{
public:


   simple_combo_list(sp(base_application) papp);
   virtual ~simple_combo_list();


   virtual void install_message_handling(::ca2::message::dispatch * pdispatch);


   virtual void _001OnDraw(::draw2d::graphics * pdc);



};



