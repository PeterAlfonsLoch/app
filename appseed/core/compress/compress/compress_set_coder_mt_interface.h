#pragma once

namespace libcompress
{


   class CLASS_DECL_CORE set_coder_mt_interface :
      virtual public ::object
   {
   public:
      virtual HRes SetNumberOfThreads(uint32_t numThreads) = 0;
   };

} // namespace libcompress
