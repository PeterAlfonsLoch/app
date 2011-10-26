#pragma once

namespace hellomultiverse
{
   class pane_view;

   class CLASS_DECL_CA2_HELLOMULTIVERSE frame :
      public simple_frame_window
   {
   public:


      frame(::ca::application * papp);
      virtual ~frame();


      window_frame::FrameSchema * create_frame_schema();
	   
   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif


   };

} // namespace hellomultiverse