#pragma once

class CLASS_DECL_CORE simple_child_frame :
   public simple_frame_window
{
public:
   simple_child_frame(sp(::base::application) papp);
   virtual ~simple_child_frame();

   virtual bool _001OnCmdMsg(::base::cmd_msg * pcmdmsg); 
   virtual bool pre_create_window(CREATESTRUCT& cs);
};

