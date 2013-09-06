#pragma once

namespace ca2
{

   class CLASS_DECL_ca2 contact_list :
      public smart_pointer_array < ::user::profile *, ::user::profile * >
   {
   public:
      contact_list();
      virtual ~contact_list();
   };

} // namespace ca2
