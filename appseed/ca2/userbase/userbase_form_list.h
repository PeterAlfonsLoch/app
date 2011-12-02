#pragma once

namespace userbase
{

   class CLASS_DECL_ca form_list :
      virtual public ::user::form_list
   {
   public:
      form_list(::ax::application * papp);
      virtual ~form_list();
   };


} // 