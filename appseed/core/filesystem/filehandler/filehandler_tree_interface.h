#pragma once


namespace filehandler
{


   class CLASS_DECL_CORE tree_interface :
      virtual public ::data::tree
   {
   public:


      tree_interface(::aura::application * papp);
      virtual ~tree_interface();


      void update_list();


   };


} // namespace filehandler







