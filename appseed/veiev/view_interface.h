#pragma once

namespace veiev
{

   class CLASS_DECL_CA2_VEIEV view_interface :
      virtual public ::userbase::view
   {
   public:


      view_interface(::ca::application * papp);
      virtual ~view_interface();


   };

} // namespace veiev
