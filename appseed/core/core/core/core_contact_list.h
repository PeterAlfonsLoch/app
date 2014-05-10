#pragma once

namespace core
{

   class CLASS_DECL_CORE contact_list :
      public smart_pointer_array < ::user::profile *, ::user::profile * >
   {
   public:
      contact_list();
      virtual ~contact_list();
   };

} // namespace core
