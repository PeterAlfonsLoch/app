#pragma once

namespace xml
{

   class CLASS_DECL_ca tree_base :
      virtual public ::ca::object
   {
   protected:


      var_exchange   m_varexchange;


   public:


      //The schema of the tree
      tree_schema * m_pschema;


      tree_base(::ca::application * papp, tree_schema * pschema);
      tree_base(::ca::application * papp);
      virtual ~tree_base();

      string get_node_name(int32_t iNameIndex);

      void set_schema(tree_schema * pschema);
      tree_schema & get_schema();

   };

} // namespace xml