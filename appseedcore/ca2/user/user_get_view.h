#pragma once

namespace user
{

   class CLASS_DECL_ca get_view :
      virtual ::radix::object
   {
   public:
      get_view();
      virtual ~get_view();

      virtual id get_view_id();
      virtual ::user::interaction * get_view_uie();
      virtual document * get_view_document();
   };

} // namespace user