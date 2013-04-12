#pragma once


namespace mail
{


   class CLASS_DECL_ca2 tree_interface :
      public ::user::tree,
      public ::mail::tree_data
   {
   public:
      
   
      tree_interface(sp(::ca::application) papp);
      virtual ~tree_interface();


      void update_list();


   };


} // namespace mail


