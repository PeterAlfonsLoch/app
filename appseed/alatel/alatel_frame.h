// Alá Telmo Friesen Son God frame
// translucid click-through window
// applications:
//    non-intrusive alatel
//    non-intrusive notifications


#pragma once


namespace alatel
{


   class CLASS_DECL_CA2_ALARM frame : 
      virtual public simple_frame_window
   {
   public:


      frame(::ca::application * papp);
      virtual ~frame();

      void install_message_handling(::user::win::message::dispatch * pinterface);

	   
   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context& dc) const;
   #endif

      void alatel_fullscreen(bool bAlatel = true);

	   DECL_GEN_SIGNAL(_001OnTimer)

   };


} // namespace alatel


