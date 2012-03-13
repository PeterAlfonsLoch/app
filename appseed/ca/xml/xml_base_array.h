#pragma once

namespace xml
{

template < int m_iNodeNameIndex, class TYPE, class ARG_TYPE = const TYPE &, class ARRAY = array_ptr_alloc < TYPE, ARG_TYPE > >
class base_array :
   public ARRAY,
   public exportable,
   public importable
{
public:
   base_array();
   base_array(const base_array & xmla);
   virtual void xml_export(output_tree & xmlof);
   virtual void xml_import(input_tree & xmlif);
};

template < int m_iNodeNameIndex, class TYPE, class ARG_TYPE, class ARRAY >
base_array<m_iNodeNameIndex, TYPE, ARG_TYPE, ARRAY>::
base_array()
{
}

template < int m_iNodeNameIndex, class TYPE, class ARG_TYPE, class ARRAY >
base_array<m_iNodeNameIndex, TYPE, ARG_TYPE, ARRAY>::
base_array(const base_array & xmla) :
ARRAY (xmla)
{
}



template < int m_iNodeNameIndex, class TYPE, class ARG_TYPE, class ARRAY >
void
base_array<m_iNodeNameIndex, TYPE, ARG_TYPE, ARRAY>::
xml_export(output_tree & xmlof)
{
   xmlof.set_attr("count", this->get_size());
   for(int i = 0; i < this->get_size(); i++)
   {
      node * pnode = xmlof.export_node(xmlof.get_node_name(m_iNodeNameIndex), this->element_at(i));
      pnode->add_attr("array_index", i);
   }
}


template < int m_iNodeNameIndex, class TYPE, class ARG_TYPE, class ARRAY >
void
base_array<m_iNodeNameIndex, TYPE, ARG_TYPE, ARRAY>::
xml_import(input_tree & xmlif)
{
   int iSize;
   xmlif.get_attr("count", iSize);
   ARRAY::set_size(iSize);
   for(int i = 0; i < this->get_size(); i++)
   {
      attr_array attra(get_app());
      attra.add("array_index", i);
      xmlif.import_node(xmlif.get_node_name(m_iNodeNameIndex), attra, this->element_at(i));
   }
}



} // namespace xml
