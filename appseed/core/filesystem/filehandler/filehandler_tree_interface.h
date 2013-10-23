#pragma once


namespace filehandler
{


   class CLASS_DECL_CORE tree_interface :
      virtual public ::data::tree
   {
   public:


      tree_interface(sp(base_application) papp);
      virtual ~tree_interface();


      sp(::filehandler::tree_data) get_filehandler_tree_data();

      void update_list();


   };


} // namespace filehandler







