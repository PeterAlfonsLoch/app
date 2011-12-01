#pragma once


namespace userbase
{


   class CLASS_DECL_ca main_frame : 
      public simple_frame_window
   {
   public:


      bool           m_bPlacing;
      
      
      main_frame(::ca::application * papp);
      virtual ~main_frame();

      virtual void install_message_handling(::gen::message::dispatch * pinterface);


   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnCreate)

   };


} // namespace userbase


