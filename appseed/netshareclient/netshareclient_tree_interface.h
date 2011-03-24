#pragma once

namespace netshareclient
{

   class CLASS_DECL_CA2_NETSHARECLIENT tree_interface :
      virtual public ::user::tree,
      virtual public ::netshareclient::tree_data
   {
   public:
      
      tree_interface(::ca::application * papp);
      virtual ~tree_interface();


      virtual bool initialize();

      void update_list();


   };

} // namespace netshareclient