#pragma once

namespace xml
{

class importable;
class attribute_array;

class CLASS_DECL_ca2 input_tree :
   public tree_base
{
public:
   virtual node * import_node(const char * lpcszName, importable & importable);
   virtual node * import_node(const char * lpcszName, attr_array & attributea, importable & importable);
   virtual node * import_node(const char * lpcszName, var & var);
   input_tree(::ca::application * papp);
   input_tree(::ca::application * papp, tree_schema * pschema);
   virtual ~input_tree();

   virtual bool get_attr(const char * lpcszName, string & strValue);
   virtual bool get_attr(const char * lpcszName, int & iValue);
   virtual void get_value(string & strValue);

   document * m_pdocument;
   node * m_pnode;
};


} // namespace xml
