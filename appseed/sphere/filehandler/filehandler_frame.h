#pragma once


namespace filehandler
{


   class CLASS_DECL_sphere frame : public simple_frame_window
   {
   
   public:
      frame(sp(::base::application) papp);
      // // DECLARE_DYNCREATE(frame)

   public:
   
   public:
      virtual ~frame();
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif


   protected:


   };


} // namespace filehandler


