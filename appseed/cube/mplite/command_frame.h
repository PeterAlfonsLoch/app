#pragma once

namespace mplite
{

   class CLASS_DECL_CA2_CUBE command_frame :
      public simple_frame_window
   {
   public:

      command_frame(::ca::application * papp);
      virtual ~command_frame();

      
      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pdispatch);

      DECL_GEN_SIGNAL(_001OnClose)

      
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      window_frame::FrameSchema * create_frame_schema();

   };

} // namespace mplite