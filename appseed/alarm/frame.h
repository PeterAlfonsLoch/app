#pragma once

namespace alarm
{

   class CLASS_DECL_CA2_ALARM frame : 
      virtual public simple_frame_window
   {
   public:


	   frame(::ca::application * papp);
      virtual ~frame();


	   
   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context& dc) const;
   #endif


   };

} // namespace alarm