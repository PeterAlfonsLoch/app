#pragma once


namespace xml
{


   class CLASS_DECL_ca2 output_tree :
      public tree_base
   {
   public:

      // root xml node - document
      document * m_pdocument;
      // current xml node
      node * m_pnode;


      output_tree(::ca::application * papp, tree_schema * pschema);
      output_tree(::ca::application * papp);
      virtual ~output_tree();


      void set_attr(const char * lpcszName, const char * lpcszValue);
      void set_attr(const char * lpcszName, int64_t iValue);
      void set_value(const char * lpcszValue);
      virtual node * export_node(exportable & exportable);
      virtual node * export_node(const char * lpcszName, exportable & exportable);
      virtual node * export_node(const char * lpcszName, var var);

      virtual void SetNodeName(const char * lpcszName);




   };


}   // namespace xml


