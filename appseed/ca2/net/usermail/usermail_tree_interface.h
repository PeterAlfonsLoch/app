#pragma once


namespace usermail
{


   class CLASS_DECL_ca2 tree_interface :
      public ::user::tree,
      public ::usermail::tree_data
   {
   public:
      
   
      tree_interface(sp(::application) papp);
      virtual ~tree_interface();


      void update_list();


   };


} // namespace usermail


