#pragma once


namespace filehandler
{


   class CLASS_DECL_ca2 tree_interface :
      virtual public ::ca2::tree
   {
   public:
      

      tree_interface(sp(::ca2::application) papp);
      virtual ~tree_interface();


      sp(::filehandler::tree_data) get_filehandler_tree_data();

      void update_list();


   };


} // namespace filehandler







