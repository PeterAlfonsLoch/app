#pragma once


namespace xml
{


   class importable;
   class attribute_array;


   class CLASS_DECL_AURA input_tree :
      public tree_base
   {
   public:


      sp(::xml::document)     m_pdocument;
      sp(::xml::node)         m_pnode;


      input_tree(::aura::application * papp);
      input_tree(::aura::application * papp, tree_schema * pschema);
      virtual ~input_tree();


      virtual node * import_node(const char * lpcszName, importable & importable);
      virtual node * import_node(const char * lpcszName, attr_array & attributea, importable & importable);
      virtual node * import_node(const char * lpcszName, var & var);

      template < typename STREAMABLE >
      node * import_streamable(const char * lpcszName, STREAMABLE & streamable);

      virtual bool get_attr(const char * lpcszName, string & strValue);
      virtual bool get_attr(const char * lpcszName, int32_t & iValue);
      virtual void get_value(string & strValue);

      virtual var attr(const char * lpcszName);

   };


   template < typename STREAMABLE >
   node * input_tree::import_streamable(const char * lpcszName, STREAMABLE & streamable)
   {
      node * pnodePrev = m_pnode;
      if (m_pnode == NULL)
      {
         m_pnode = m_pdocument->get_root();
         string strName;
         strName = m_pnode->get_name();
         if (strName != lpcszName)
         {
            m_pnode = NULL;
            throw "Node not found";
         }
         *this >> streamable;
         return m_pdocument->get_root();
      }
      else
      {
         node * pnode = m_pnode->get_child(lpcszName);
         m_pnode = pnode;
         *this >> streamable;
         m_pnode = pnodePrev;
         return pnode;
      }
   }


} // namespace xml






