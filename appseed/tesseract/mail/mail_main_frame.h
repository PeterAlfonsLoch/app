#pragma once


namespace tesseract
{

namespace mail
{

   class CLASS_DECL_CA2_TESSERACT main_frame : 
      virtual public simple_frame_window
   {
   public:
      main_frame(::ca::application * papp);
      virtual ~main_frame();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   };

   } // namespace mail


} // namespace tesseract


