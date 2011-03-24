#pragma once

namespace veiev
{

   class CLASS_DECL_CA2_VEIEV tree_interface :
      virtual public ::user::tree,
      virtual public ::veiev::tree_data
   {
   public:
      
      tree_interface(::ca::application * papp);
      virtual ~tree_interface();


      virtual bool initialize();

      void update_list();


   };

} // namespace veiev