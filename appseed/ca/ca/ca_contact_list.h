#pragma once

namespace ca
{

   class CLASS_DECL_ca contact_list :
      public array_ptr_alloc < ::user::profile *, ::user::profile * >
   {
   public:
      contact_list();
      virtual ~contact_list();
   };

} // namespace ca