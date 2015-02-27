#pragma once


namespace xml
{


   class importable;
   class attribute_array;


   class CLASS_DECL_AURA input_tree :
      public tree_base
   {
   public:


      ::xml::document      m_document;
      ::xml::node          m_node;


      input_tree(::aura::application * papp);
      input_tree(::aura::application * papp, tree_schema * pschema);
      virtual ~input_tree();


      virtual node import_node(const char * lpcszName, importable & importable);
      virtual node import_node(const char * lpcszName, array < ::xml::attribute > & attributea, importable & importable);
      virtual node import_node(const char * lpcszName, var & var);

      virtual bool get_attr(const char * lpcszName, string & strValue);
      virtual bool get_attr(const char * lpcszName, int32_t & iValue);
      virtual void get_value(string & strValue);

   };


} // namespace xml





