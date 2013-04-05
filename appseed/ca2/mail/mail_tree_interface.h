#pragma once


namespace mail
{


   class CLASS_DECL_ca2 tree_interface :
      public ::user::tree,
      public ::mail::tree_data
   {
   public:
      
   
      tree_interface(::ca::applicationsp papp);
      virtual ~tree_interface();


      virtual bool initialize();

      void update_list();


   };


} // namespace mail


