#pragma once

namespace imedia
{

   class CLASS_DECL_ca time_array :
      virtual public numeric_array < time >
   {
   public:
      time_array();
      time_array(const time_array & base_array);

   };

   class CLASS_DECL_ca time_2darray :
      public array_ptr_alloc < time_array, const time_array &>
   {
   };

}
