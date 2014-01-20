#pragma once

namespace libcompress
{


   class CLASS_DECL_CORE set_coder_mt_interface :
      virtual public ::ca::object
   {
   public:
      virtual ::ca::HRes SetNumberOfThreads(uint32 numThreads) = 0;
   };

} // namespace libcompress
