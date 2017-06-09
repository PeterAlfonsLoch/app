#pragma once


namespace xml
{


   class CLASS_DECL_AURA output_tree :
      public tree_base
   {
   public:

      // root xml node - document
      sp(::xml::document)     m_pdocument;
      // current xml node
      sp(node)                m_pnode;


      output_tree(::aura::application * papp, tree_schema * pschema);
      output_tree(::aura::application * papp);
      virtual ~output_tree();


      void set_attr(const char * lpcszName, const char * lpcszValue);
      void set_attr(const char * lpcszName, int64_t iValue);
      void set_value(const char * lpcszValue);

      virtual void attr(const char * lpcszName, const var & varValue);

      virtual node * export_node(exportable & exportable);
      virtual node * export_node(const char * lpcszName, exportable & exportable);
      virtual node * export_node(const char * lpcszName, var var);

      template < typename STREAMABLE >
      node * export_streamable(const char * lpcszName, const STREAMABLE & streamable);


      virtual void SetNodeName(const char * lpcszName);




   };


   template < typename STREAMABLE >
   node * output_tree::export_streamable(const char * lpcszName, const STREAMABLE & streamable)
   {
      if (m_pnode == NULL)
      {
         if (m_pdocument == NULL)
         {
            throw "Cannot output to a NULL document";
         }
         m_pnode = m_pdocument->get_root();
         m_pnode->set_name(lpcszName);
         *this << streamable;
         return m_pdocument->get_root();
      }
      else
      {
         node * pnodePrev = m_pnode;
         node * pnode = m_pnode->add_child(lpcszName);
         m_pnode = pnode;
         *this << streamable;
         m_pnode = pnodePrev;
         return pnode;
      }
   }


}   // namespace xml




