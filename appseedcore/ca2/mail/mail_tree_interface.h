#pragma once

namespace mail
{

   class CLASS_DECL_ca tree_interface :
      virtual public ::user::tree,
      virtual public ::mail::tree_data
   {
   public:
      
      tree_interface(::ca::application * papp);
      virtual ~tree_interface();


      virtual bool initialize();

      void update_list();


   };

} // namespace mail