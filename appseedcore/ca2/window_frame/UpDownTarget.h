#pragma once

namespace window_frame
{

   class CLASS_DECL_ca UpDownTarget
   {
   public:

      virtual void Attach(CWorkSetDownUpInterface * pupdown) = 0;
      virtual void Detach(CWorkSetDownUpInterface * pupdown) = 0;

   };

} // namespace window_frame