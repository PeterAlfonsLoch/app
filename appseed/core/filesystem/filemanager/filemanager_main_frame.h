#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE main_frame :
      virtual public simple_frame_window
   {
   public:


      main_frame(sp(::aura::application) papp);
      virtual ~main_frame();

      virtual bool on_create_bars();

      DECL_GEN_SIGNAL(_001OnCreate);

   };



} // namespace filemanager



