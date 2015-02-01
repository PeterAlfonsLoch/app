#pragma once


class CLASS_DECL_CORE simple_child_frame :
   public simple_frame_window
{
public:
   
   
   simple_child_frame(::aura::application * papp);
   virtual ~simple_child_frame();

   
   virtual bool _001OnCmdMsg(::aura::cmd_msg * pcmdmsg); 
   virtual bool pre_create_window(::user::create_struct& cs);


   virtual void _001OnDraw(::draw2d::graphics * pdc);

   virtual bool get_translucency(::user::ETranslucency & etranslucency);

};

