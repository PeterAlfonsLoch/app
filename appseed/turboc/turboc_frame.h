#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC frame :
      virtual public simple_frame_window
   {
   public:


      frame(::aura::application * papp);
      virtual ~frame();


	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;


      virtual bool get_translucency(::user::ETranslucency & etranslucency);
      virtual sp(::user::wndfrm::frame::frame) create_frame_schema();


   };


} // namespace turboc












