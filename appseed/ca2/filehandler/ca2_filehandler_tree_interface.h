#pragma once


namespace ca2
{


   namespace filehandler
   {


      class CLASS_DECL_ca2 tree_interface :
         virtual public ::ex1::tree
      {
      public:
      

         tree_interface(::ca::application * papp);
         virtual ~tree_interface();


         ::ca2::filehandler::tree_data * get_filehandler_tree_data();

         virtual bool initialize();

         void update_list();


      };


   } // namespace filehandler


} // namespace mail


