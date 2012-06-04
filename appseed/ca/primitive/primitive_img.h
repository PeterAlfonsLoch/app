#pragma once

namespace visual
{
   namespace rgba
   {
      enum echannel
      {
         channel_red = 0,
         channel_green = 1,
         channel_blue = 2,
         channel_alpha = 3,
      };
   } // namespace rgba
} // namespace visual


#define rgb_get_r_value(rgb)      (LOBYTE(rgb))
#define rgb_get_g_value(rgb)      (LOBYTE((rgb)>>8))
#define rgb_get_b_value(rgb)      (LOBYTE((rgb)>>16))
#define rgb_get_a_value(rgb)      (LOBYTE((rgb)>>24))

#define bgr_get_b_value(bgr)      (LOBYTE(bgr))
#define bgr_get_g_value(bgr)      (LOBYTE((bgr)>>8))
#define bgr_get_r_value(bgr)      (LOBYTE((bgr)>>16))
#define bgr_get_a_value(bgr)      (LOBYTE((bgr)>>24))


