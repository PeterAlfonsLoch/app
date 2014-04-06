#pragma once


namespace user
{


   inline oswindow interaction::get_safe_handle()
   {
      if (((byte *)this) < (byte *)(((byte *)NULL) + (16 * 1024))) // consider invalid
      {
         return NULL;
      }
      return get_handle();
   }


} // namespace user



