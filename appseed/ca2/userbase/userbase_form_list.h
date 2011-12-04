#pragma once

namespace userbase
{

   class CLASS_DECL_ca2 form_list :
      virtual public ::user::form_list
   {
   public:
      form_list(::ca::application * papp);
      virtual ~form_list();
   };


} // 