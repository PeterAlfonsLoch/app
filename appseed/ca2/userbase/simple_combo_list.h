#pragma once


class CLASS_DECL_ca2 simple_combo_list : 
   virtual public ::userbase::combo_list
{
public:


   simple_combo_list(::ca::application * papp);
   virtual ~simple_combo_list();


   virtual void install_message_handling(::ca::message::dispatch * pdispatch);


   virtual void _001OnDraw(::ca::graphics * pdc);



};



