#pragma once


namespace xml
{


   class CLASS_DECL_AURA output_tree :
      public tree_base
   {
   public:

      // root xml node - document
      ::xml::document     m_document;
      // current xml node
      node                m_node;


      output_tree(::aura::application * papp, tree_schema * pschema);
      output_tree(::aura::application * papp);
      virtual ~output_tree();


      void set_attr(const char * lpcszName, const char * lpcszValue);
      void set_attr(const char * lpcszName, int64_t iValue);
      void set_value(const char * lpcszValue);
      virtual node export_node(exportable & exportable);
      virtual node export_node(const char * lpcszName, exportable & exportable);
      virtual node export_node(const char * lpcszName, var var);

      virtual void SetNodeName(const char * lpcszName);




   };


}   // namespace xml


