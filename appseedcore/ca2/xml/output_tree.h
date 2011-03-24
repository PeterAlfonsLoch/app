#pragma once

namespace xml
{



class CLASS_DECL_ca output_tree :
   public tree_base
{
public:
   void set_attr(const char * lpcszName, const char * lpcszValue);
   void set_attr(const char * lpcszName, int iValue);
   void set_value(const char * lpcszValue);
   virtual node * export_node(exportable & exportable);
   virtual node * export_node(const char * lpcszName, exportable & exportable);
   virtual node * export_node(const char * lpcszName, var var);

   virtual void SetNodeName(const char * lpcszName);

   output_tree(::ca::application * papp, tree_schema * pschema);
   output_tree(::ca::application * papp);
   virtual ~output_tree();

   //The pointer to the xml document
   document * m_pdocument;
   //The current node
   node * m_pnode;


};

}   // namespace xml