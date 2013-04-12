#pragma once

namespace libcompress
{


   class CLASS_DECL_ca2 set_coder_mt_interface :
      virtual public ::ca::object
   {
   public:
      virtual ::ca::HRes SetNumberOfThreads(uint32_t numThreads) = 0;
   };

} // namespace libcompress
