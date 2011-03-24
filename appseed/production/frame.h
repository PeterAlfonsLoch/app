#pragma once

namespace production
{

   class CLASS_DECL_CA2_PRODUCTION frame : 
      public simple_frame_window
   {
   public:
	   frame(::ca::application * papp);
   public:
	   virtual ~frame();
   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

      void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      DECL_GEN_SIGNAL(_001OnCreate)
   };

} // namespace production