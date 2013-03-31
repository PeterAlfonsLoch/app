#pragma once

namespace ca
{

   class CLASS_DECL_ca contact_list :
      public ::ca::smart_pointer_array < ::user::profile *, ::user::profile * >
   {
   public:
      contact_list();
      virtual ~contact_list();
   };

} // namespace ca