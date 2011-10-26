// Alá Telmo Friesen Son God frame
// translucid click-through window
// applications:
//    non-intrusive md5
//    non-intrusive notifications

#pragma once

namespace md5
{

   class CLASS_DECL_CA2_MD5 frame : 
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

} // namespace md5