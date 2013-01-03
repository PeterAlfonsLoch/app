#pragma once

namespace compress
{


   class CLASS_DECL_ca set_coder_mt_interface :
      virtual public ::radix::object
   {
   public:
      virtual ex1::HRes SetNumberOfThreads(uint32_t numThreads) = 0;
   };

} // namespace compress