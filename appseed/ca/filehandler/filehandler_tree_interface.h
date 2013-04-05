#pragma once


namespace filehandler
{


   class CLASS_DECL_ca tree_interface :
      virtual public ::ca::tree
   {
   public:
      

      tree_interface(::ca::applicationsp papp);
      virtual ~tree_interface();


      ::filehandler::tree_data * get_filehandler_tree_data();

      virtual bool initialize();

      void update_list();


   };


} // namespace filehandler







