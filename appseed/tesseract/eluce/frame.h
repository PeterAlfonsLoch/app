#pragma once


namespace eluce
{


   class CLASS_DECL_CA2_TESSERACT frame :
      virtual public simple_frame_window
   {
   public:


      frame(::ca::application * papp);
      virtual ~frame();


   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      virtual void install_message_handling(::user::win::message::dispatch * pdispatch);

      DECL_GEN_SIGNAL(_001OnCreate);


   };


} // namespace eluce

