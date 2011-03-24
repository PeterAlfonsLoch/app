#pragma once

namespace mail
{

   class CLASS_DECL_ca child_frame : 
      public simple_child_frame
   {
   public:
      child_frame(::ca::application * papp);
      virtual ~child_frame();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   };

} // namespace mail